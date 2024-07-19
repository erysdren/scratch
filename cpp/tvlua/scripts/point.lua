
local p0 = TPoint.new()
local p1 = TPoint.new()
local p3 = TPoint.new()

p0.x = 32
p0.y = 64

p1.x = 256
p1.y = 1024

p3.x = 128
p3.y = 512

local r0 = TRect.new(0, 0, 80, 25)
local r1 = TRect.new(p0, p1)

print(r1:contains(p3))

print(p0.x, p0.y)
print(p1.x, p1.y)
print(r0.a.x, r0.a.y, r0.b.x, r0.b.y)
print(r1.a.x, r1.a.y, r1.b.x, r1.b.y)

r0:move(32, 32)

print(r0.a.x, r0.a.y, r0.b.x, r0.b.y)
