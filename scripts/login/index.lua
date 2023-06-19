local skynet = require "skynet"
local sep = require "sephiroth"
local response = require "response"
local cmsg = require "messages.sepclient"
require("skynet.manager")

local COMMANDS = {}


local function sureLogin(source,fd)
    local appData = sep.AppData(22)
    appData:PutShort(0x1403)
    appData:PutShort(4)
    appData:Seek(16)
    appData:PutShort(0x1403 ~ 4 ~ 0)
    appData:PutInt(0x10001)
    skynet.send(source,"lua","send_by_fd",fd,appData:Data())
end

-- 告诉客户端可以开始登录了
COMMANDS.request_login = function (source,fd,msg)
    if msg.type == 0x1401 then
        sureLogin(source,fd)
    elseif msg.type == 0x1409 then
        local ad = sep.AppData(msg.data)
        local id = ad:GetShort()
        if id == 0x3EE then
            local login = cmsg.CLogin(ad)
            print("login" .. login.id .. " ".. login.key .. " " .. login.version)
        end
    end
end

local traceback = function (err)
    skynet.error(tostring(err))
    skynet.error(debug.traceback())
end

local function dispatch(session,source,cmd,...)
    skynet.error("login服务收到消息 ".. source .. " CMD:" .. cmd)
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

skynet.start(function ()
    skynet.register(".login")
    skynet.dispatch("lua",dispatch)
end)