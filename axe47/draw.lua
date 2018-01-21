-- draw.lua
drawLine(0, 0, 300, 300)

drawLine(100, 0, 300, 300)

for i = 1, 10 do
    drawLine(i*20, 200, i*10, 300)
end

for i = 1, 10 do
    drawPoint(i*3)
end

drawRect(50, 50, 50, 80)

fillRect = function(x, y, w, h)
    -- drawRect(x, y, w, h)
    for i = x, x + w do
      drawLine(x + i, y, x + i, y + h)
    end
end

fillRect(100, 50, 50, 80)

setColor(100, 100, 100, 100)

fillRect(150, 50, 50, 80)


-- 实际上这样写代码是不对的，应该有一个唯一入口才好
