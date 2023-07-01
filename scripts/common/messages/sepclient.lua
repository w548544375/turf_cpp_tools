local sep = require "sephiroth"

local M = {}
-- CLient Login Message
function CLogin(ad)
    local m = {
        id = nil,
        version = nil,
        key = nil,
        userId = nil,
        A = nil,
    }
    m.id = 0x1D -- 0x3EE 老版本凯旋
    ad:Seek(7)
    m.version = ad:GetByte()
    m.key = ad:GetString()
    m.A = ad:GetString()
    m.userId = ad:GetString()
    return m
end

M.CLogin = CLogin

return M