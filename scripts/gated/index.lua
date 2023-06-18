local skynet = require "skynet"
local socket = require "skynet.socket"
local sep = require "sephiroth"
local cfg = require "runcfg"

-- fd = Conn
local conns = {}

local COMMANDS = {}


local function ClientMsg()
    local M = {
        type = nil,
        data =  nil,
    }
    return M
end

local function process_msg(fd,msg)
    skynet.error("收到客户端消息:" .. msg.type)
    if nil ~= msg.data then
        skynet.error("data: " .. sep.toHexString(msg.data))
    end
end

local function disconnect(fd)
        -- 读取数据错误之后通知移除并关闭socket
    skynet.error("error read from fd " .. fd)
    conns[fd] = nil
    socket.close(fd)
end

local  recv_loop = function(fd)
    skynet.error("recv_loop"..fd)
    while true do
        local d = socket.read(fd)
        if not d then
            disconnect(fd)
            return
        end
        local decrpyted = skynet.call(".crypto","lua","decrypt",fd,d)
        if decrpyted.code ~= 200 then
            disconnect(fd)
            return
        end
        skynet.error(sep.toHexString(decrpyted.data))
        local buf = sep.AppData(decrpyted.data)
        local type = buf:GetShort()
        local info = buf:GetShort()
        local body = buf:GetInt()
        buf:Seek(16)
        local valid = buf:GetShort()
        if type ~ info ~ body ~= valid then
            disconnect(fd)
            return
        end
        local msg = ClientMsg()
        msg.type = type
        local remain = info + body
        if remain > 0 then
            msg.data = socket.read(fd,remain)
        end
        process_msg(fd,msg)
    end
end

-- 告诉客户端可以开始登录了
local function ReadyToRoll(fd)
    local appData = sep.AppData(22)
    appData:PutShort(0x1403)
    appData:PutShort(4)
    appData:Seek(16)
    appData:PutShort(0x1403 ~ 4 ~ 0)
    appData:PutInt(0x10001)
    skynet.error(sep.toHexString(appData:Data()))
    socket.write(fd,appData:Data(),appData:Size())
    skynet.error("ReadyToRoll"..fd)
end

local function Conn(fd, addr)
    local m = {
        fd = fd,
        addr = addr
    }
    return m
end

local function intoSecondStage(fd)
    local readbuf = socket.read(fd,256)
    if not readbuf then
        disconnect(fd)
        return false
    end
    skynet.error(readbuf)
    local ret = skynet.call(".crypto","lua","feed",fd,readbuf)
    if  ret.code ~= 200 then
        disconnect(fd)
        return false
    end
    return true
end

local function connect(fd, ipaddr)
    skynet.error("gated收到客户端连接->" .. fd)
    socket.start(fd)
    local c = Conn(fd,ipaddr)
    conns[fd] = c
    local ret = skynet.call(".crypto","lua","init",fd)
    socket.write(fd,ret.data)
    if cfg.isCrypt then
        local vertified = intoSecondStage(fd)
        if not vertified then
            return
        end
    end
    skynet.fork(recv_loop,fd)
end


local traceback = function (err)
    skynet.error(tostring(err))
    skynet.error(debug.traceback())
end

local function dispatch(session,source,cmd,...)
    skynet.error("gated服务收到消息 ".. source .. " CMD:" .. cmd)
    local fun = COMMANDS[cmd]
    if not fun then
        skynet.retpack({code = 404,msg="handler for " .. cmd ..  " not found",service =  skynet.self()})
        return
    end
    local ret = table.pack(xpcall(fun,traceback,source,...))
    local isOk = ret[1]
    if not isOk then
        skynet.retpack({ code = 503, msg = "handler for " .. cmd .. " run failed", service = skynet.self() })
        return
    end
    skynet.retpack(table.unpack(ret,2))
end

skynet.start(function()
    --skynet.register(".gated")
    local server = socket.listen("0.0.0.0", 2286)
    sep.RSAInit("./config/pub_key.pem", "./config/private_key.pem")
    skynet.dispatch('lua',dispatch)
    socket.start(server,connect)
    skynet.error("gated服务地址:" .. skynet.self())
end)
