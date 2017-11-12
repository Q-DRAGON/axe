const asm_d = {
    'pc': 0b0000000000000000,
    'x': 0b0000000100000000,
    'y': 0b0000001000000000,
    'z': 0b0000001100000000,
    'c1': 0b0000010000000000,
    'f': 0b0000010100000000,
    'set': 0b0000000000000000,
    'load': 0b0000000100000000,
    'add': 0b0000001000000000,
    'save': 0b0000001100000000,
    'compare': 0b0000010000000000,
    'jump': 0b0000010100000000,
    'jump_when_less': 0b0000011000000000,
    'save_from_register': 0b0000011100000000,
    'stop': 0b1111111111111111,
}

const asm_code = `
set y 55536                ; 左上角第一个像素
set z 404                  ; 用于斜方向设置像素，每两排设置一个
set x 61455                ; 红色
save_from_register x y     ; 设置像素点
add y z y
save_from_register x y     ; 设置像素点
add y z y
save_from_register x y     ; 设置像素点
add y z y
save_from_register x y     ; 设置像素点
add y z y
save_from_register x y     ; 设置像素点
stop                       ; 停止
`
