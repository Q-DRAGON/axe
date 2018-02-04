bmih = 20

for j = 1, 4 do
    for i = 1, 2 do
        -- print("logging")
        num = j .. '-' .. i
        drawButton(20 + i * bmih, 20 + j * bmih, bmih, bmih)
        drawText(20 + i * bmih + 2, 20 + j * bmih + 2, num)
    end
end

setColor(100, 100, 100, 100)

fillRect(80 + 2, 40, 300, 200)
