local skynet = require("skynet")
-- local sep = require("sephiroth")

-- local b = sep.AppData()
-- b:PutByte(1)
-- b:PutShort(0x1409)
-- b:PutInt(100)
-- b:PutLong(100)
-- b:PutFloat(1.0)
-- b:PutDouble(1.523)
-- b:PutString("Hello")
-- print("Buffer Content: \n" .. b:ToString())
-- b:Seek(0)
-- print("GetByte" .. b:GetByte())
-- print("GetShort" .. b:GetShort())
-- print("GetInt" .. b:GetInt())
-- print("GetLong" .. b:GetLong())
-- print("GetFloat" .. b:GetFloat())
-- print("GetDouble " .. b:GetDouble())
-- print("GetString" .. b:GetString())
-- local msg = sep.ClientMsg(0, b)
-- local ad = msg:Serialize()
-- print(ad)

-- --- 测试RSA
-- sep.RSAInit("./config/pub_key.pem","./config/private_key.pem")
-- local cipher = sep.RSAEncrypt("bigz11")
-- print("加密后的字符串:" .. sep.toHexString(cipher))
-- local plain = sep.RSADecrypt(cipher)
-- print("解密: " .. plain)
-- sep.Free()
-- -- 测试加密组件
-- local crypto = sep.Cryptor()
-- local seed01 = string.pack("BBBBBBBBBB", 0x30, 0x1F, 0x3D, 0x30, 0x1E, 0x30, 0x27, 0x41, 0x25, 0x1A)
-- crypto:Feed(seed01)
-- crypto:SetRoundBounds(0, 0xE5)
-- crypto:SetRoundBegin(0, 0x29)
-- local seed02 = string.pack("BBBBBBBBBB", 0x16, 0x2D, 0x5B, 0x27, 0xDE, 0x32, 0x67, 0x19, 0x4E, 0x3A)
-- crypto:Feed(seed02)
-- crypto:SetRoundBounds(1, 0x32)
-- crypto:SetRoundBegin(1, 0x01)
-- print(crypto)
-- local data = string.pack("BBBBBBBBBBBBBBBBBB", 0x01, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
--     0x00, 0x00, 0x00, 0x00, 0x01, 0x14)
-- print("origin data:\n" .. sep.toHexString(data))
-- local encrypted = crypto:Encrypt(data)
-- print("crypted data:\n" .. sep.toHexString(encrypted))
-- local decrypted = crypto:Decrypt(encrypted)
-- print("decrypted data:\n" .. sep.toHexString(decrypted))

skynet.start(function()
    skynet.newservice("crypto")
    skynet.newservice("gated")
end)
