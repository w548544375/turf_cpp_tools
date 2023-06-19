
local M = {}
-- CLient Login Message
function CLogin(ad)
    local m = {
        id = nil,
        version = nil,
        key = nil
    }
    m.id = 0x3EE
    ad:Seek(7)
    m.version = ad:GetByte()
    m.key = ad:GetString()
    return m
end

M.CLogin = CLogin

return M