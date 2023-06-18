local skynet = require "skynet"
local socket = require "skynet.socket"
local sep = require "sephiroth"
local response = require "response"
local cfg = require "runcfg"
require("skynet.manager")
local cryptors = {} -- 保存fd 对应的cryptor
local COMMANDS = {}

local function RandomSeed()
    local seed = {}
    if not cfg.isCrypt then
        for i = 1, 10, 1 do
            seed[i] = 0
        end
    else
        for i = 1, 10, 1 do
            seed[i] = (math.random(512) % 50 + 20) & 0xFF
        end
    end
    return seed
end

COMMANDS.init = function(source, fd)
    local cryptor = sep.Cryptor(cfg.isCrypt)
    cryptors[fd] = cryptor
    local seed = RandomSeed()
    local seedStr = string.pack("BBBBBBBBBB", table.unpack(seed))
    cryptor:Feed(seedStr)
    local roundBegin = (math.random(512) % 40 + 40) & 0xFF
    cryptor:SetRoundBegin(0, roundBegin)
    local roundBounds = (math.random(1, 512) % 40 - 55) & 0xFF
    cryptor:SetRoundBounds(0, roundBounds)
    local str = string.pack("Bc10BBBB", cfg.isCrypt and 1 or 0, seedStr, roundBegin, 0, roundBounds, 0)
    local data = sep.RSAEncrypt(str)
    return response.Success(data)
end

COMMANDS.feed = function(source, fd, buf)
    if nil == cryptors[fd] then
        return response.Error(400, "cryptor not found")
    end
    local cryptor = cryptors[fd]
    local plain = sep.RSADecrypt(buf)
    if string.len(plain) ~= 12 then
        return response.Error(400, "error decrypt client data")
    end
    --skynet.error("client random:" .. sep.toHexString(plain))
    local clientSeed = string.sub(plain, 1, 10)
    cryptor:Feed(clientSeed)
    local round2Begin = string.unpack("B", string.sub(plain, 11))
    cryptor:SetRoundBegin(1, round2Begin)
    local round2End = string.unpack("B", string.sub(plain, 12))
    cryptor:SetRoundBounds(1, round2End)
    return response.Success("")
end


COMMANDS.auth = function(source, fd)
    socket.start(fd)
    local cryptor = sep.Cryptor(cfg.isCrypt)
    local seed = RandomSeed()
    local seedStr = string.pack("BBBBBBBBBB", table.unpack(seed))
    cryptor:Feed(seedStr)
    local roundBegin = (math.random(512) % 40 + 40) & 0xFF
    cryptor:SetRoundBegin(0, roundBegin)
    local roundBounds = (math.random(1, 512) % 40 - 55) & 0xFF
    cryptor:SetRoundBounds(0, roundBounds)
    local str = string.pack("Bc10BBBB", cfg.isCrypt and 1 or 0, seedStr, roundBegin, 0, roundBounds, 0)
    local data = sep.RSAEncrypt(str)
    -- local res = ""
    -- for i = 1, 10, 1 do
    --    res = res .. string.format("%02X ",seed[i])
    -- end
    -- res = res .. string.format("%03X ",roundBegin) .. string.format("%03d",roundBounds) .. " " .. (roundBounds - roundBegin)
    --print("server random is :\n" .. res)
    socket.write(fd, data, 256)
    if not cfg.isCrypt then -- 如果不加密就直接认证成功
        socket.abandon(fd)
        skynet.send(source, "lua", "client_vertified", fd, { code = 200 })
        return 0
    end
    local readBuf = socket.read(fd, 256)
    if not readBuf then
        socket.abandon(fd)
        local m = { code = 400, msg = "error read buf" }
        skynet.send(source, "lua", "client_failed", fd, m)
        return -1
    end
    -- print("recv client: \n" .. sep.toHexString(readBuf))
    local plain = sep.RSADecrypt(readBuf)
    if string.len(plain) ~= 12 then
        socket.abandon(fd)
        local m = { code = 400, msg = "error decrypt client data" }
        skynet.send(source, "lua", "client_failed", fd, m)
        return -1
    end
    --skynet.error("client random:" .. sep.toHexString(plain))
    local clientSeed = string.sub(plain, 1, 10)
    cryptor:Feed(clientSeed)
    local round2Begin = string.unpack("B", string.sub(plain, 11))
    cryptor:SetRoundBegin(1, round2Begin)
    local round2End = string.unpack("B", string.sub(plain, 12))
    cryptor:SetRoundBounds(1, round2End)
    cryptors[fd] = cryptor

    socket.abandon(fd)
    skynet.send(source, "lua", "client_vertified", fd, { code = 200 })
    return 0
end

COMMANDS.decrypt = function(source, fd, msg)
    local cryptor = cryptors[fd]
    if not cryptor then
        return response.Error(400, "cryptor not found for fd " .. fd)
    end
    local decryptd = cryptor:Decrypt(msg)
    return response.Success(decryptd)
end

COMMANDS.encrypt = function(source, fd, msg)
    local cryptor = cryptors[fd]
    if not cryptor then
        return response.Error(400, "cryptor not found for fd " .. fd)
    end
    local encrypted = cryptor:Encrypt(msg)
    return response.Success(encrypted)
end



local traceback = function(err)
    skynet.error(tostring(err))
    skynet.error(debug.traceback())
end

local dispatch = function(session, source, cmd, ...)
    skynet.error("crypto服务收到消息 " .. source .. " CMD:" .. cmd)
    local fun = COMMANDS[cmd]
    if not fun then
        skynet.retpack(response.Error(404,"handler for " .. cmd .. " not found"))
        return
    end
    local ret = table.pack(xpcall(fun, traceback, source, ...))
    local isOk = ret[1]
    if not isOk then
        skynet.retpack(response.Error(503,"handler for " .. cmd .. " run failed"))
        return
    end
    skynet.retpack(table.unpack(ret, 2))
end

skynet.start(function()
    skynet.register(".crypto")
    skynet.dispatch("lua", dispatch)
    skynet.error("服务地址:" .. skynet.self())
end)
