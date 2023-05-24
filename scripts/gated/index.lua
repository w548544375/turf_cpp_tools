local skynet = require "skynet"
local socket = require "skynet.socket"
local sep = require "sephiroth"
local cfg = require "runcfg"

local conns = {}

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

local function validate(fd, ipaddr)
    socket.start(fd)
    local cryptor = sep.Cryptor(cfg.isCrypt)
    local seed = RandomSeed()
    local seedStr = string.pack("BBBBBBBBBB",table.unpack(seed))
    cryptor:Feed(seedStr)
    local roundBegin =  (math.random(512)%40 + 40) & 0xFF
    cryptor:SetRoundBegin(0,roundBegin)
    local roundBounds = (math.random(1,512)%40 - 55) & 0xFF
    cryptor:SetRoundBounds(0,roundBounds)
    local str = string.pack("Bc10BBBB",cfg.isCrypt and 1 or 0,seedStr,roundBegin,0,roundBounds,0)
    local data = sep.RSAEncrypt(str)
    local res = ""
    for i = 1, 10, 1 do
       res = res .. string.format("%02X ",seed[i])
    end
    res = res .. string.format("%03X ",roundBegin) .. string.format("%03d",roundBounds) .. " " .. (roundBounds - roundBegin)
    print("server random is :\n" .. res)
    socket.write(fd,data)
    local readBuf = socket.read(fd,256)
    
    if not readBuf then
        socket.close(fd)
        skynet.error("close fd ".. fd)
        return
    end
   -- print("recv client: \n" .. sep.toHexString(readBuf))
    local plain = sep.RSADecrypt(readBuf)
    skynet.error("client random:\n" .. sep.toHexString(plain))
end

skynet.start(function()
    local server = socket.listen("0.0.0.0", 2286)
    sep.RSAInit("./config/pub_key.pem", "./config/private_key.pem")
    socket.start(server, function(fd, ipaddr)
        skynet.fork(validate, fd, ipaddr)
    end)
end)
