def response(a):
    b = a.split('\r\n')[0].split(' ')[1]
    # print("dssssss", b)
    if b == '/':
        s = "HTTP/1.0 200 OK\r\nContent-Length: 11\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nHello World\r\n"
    else:
        s = "HTTP/1.0 404 NOT FOUND\r\nContent-Length: 3\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n404\r\n"
    return (s,)
