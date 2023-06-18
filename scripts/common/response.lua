M = {}

M.Success = function(data)
    local m = {
        code = 200,
        data = data,
        msg = nil
    }
    return m
end

M.Error = function(code,msg)
    local m = {
        code = code,
        msg = msg,
        data = nil
    }
    return m
end

return M