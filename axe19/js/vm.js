var pc = 0
var x, y, z, f
var c1 = -1

const run = function(memory) {
    // 这是一个虚拟机程序
    // run 函数将 memory 数组视为内存，可以执行这个内存
    log('old memory', memory)
    while (pc < memory.length) {
        func_d[memory[pc]](memory)
    }
    // memory = enhance_memory(memory, 512)
    colorscreen(memory)
    log('new memory', memory)
}

const colorscreen = function(memory){
    let list = memory.slice(512, 1024)
    let canvas = _e('#id-canvas')
    let context = canvas.getContext('2d')
    let pixels = context.getImageData(0, 0, 32, 16)
    let data = pixels.data
    for (var i = 0; i < 512; i += 4) {
        r = trans_to_RGBA(list[i / 4], 0, 4)
        g = trans_to_RGBA(list[i / 4], 4, 8)
        b = trans_to_RGBA(list[i / 4], 8, 12)
        a = trans_to_RGBA(list[i / 4], 12, 16)
        data[i] = r
        data[i + 1] = g
        data[i + 2] = b
        data[i + 3] = a
    }
    context.putImageData(pixels, 0, 0)
}
