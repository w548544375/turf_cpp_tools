package.cpath = "./build/?.so;" .. package.cpath
print(package.cpath)
local buf = require("buffer")

local b = buf.new()
b:PutDouble(1.0)
local d = b:GetDouble()
print("double value is " .. d)
print(b:ToString())
