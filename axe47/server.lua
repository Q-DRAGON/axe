print('log in lua')

local function strSplit(delimeter, str)
    local find, sub, insert = string.find, string.sub, table.insert
    local res = {}
    local start, start_pos, end_pos = 1, 1, 1
    while true do
        start_pos, end_pos = find(str, delimeter, start, true)
        if not start_pos then
            break
        end
        insert(res, sub(str, start, start_pos - 1))
        start = end_pos + 1
    end
    insert(res, sub(str,start))
    return res
end

function luaresponse(a)
    -- print(a)
    mid = strSplit('\r\n', a)[1]
    check = strSplit(' ', mid)[2]
    if check == '/' then
        b = "HTTP/1.0 200 OK\r\nContent-Length: 11\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nHello World\r\n"
    else
        b = "HTTP/1.0 404 NOT FOUND\r\nContent-Length: 3\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n404\r\n"
    end
    return b
end
