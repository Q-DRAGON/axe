// 1，实现下面的函数
const memory = ['00000000', '00010000', '00000001', '00000000', '00100000', '00000010', '00000011', '00010000', '00000000', '00000011', '00100000', '00000001', '00000001', '00000000', '00010000', '00000001', '00000001', '00100000', '00000010', '00010000', '00100000', '00110000', '00000011', '00110000', '00000010']

// string = '''
// set x 1
// set y 2
// save x @0
// save y @1
// load @0 x
// load @1 y
// add x y z
// save z @2
// '''
// parseInt(memory[0],2)
const d = {
    '0b00010000': function(i){
        if (i == undefined) {
            return x
        }else {
            x = i
        }
    },
    '0b00100000': function(i){
        if (i == undefined) {
            return y
        }else {
            y = i
        }
    },
    '0b00110000': function(i){
        if (i == undefined) {
            return z
        }else {
            z = i
        }
    },
    '0b00000000': 'set',
    '0b00000001': 'load',
    '0b00000010': 'add',
    '0b00000011': 'save'
}

const log = console.log.bind(console)

// 假设 GuaPU 有 5 个寄存器, 分别用如下的数字表示
// 00000000    ; pc(program counter) 当前指令寄存器
// 00010000    ; x
// 00100000    ; y
// 00110000    ; z
// 01000000    ; c1, 用于存储比较指令的结果 0 表示小于, 1 表示相等, 2 表示大于
// 01010000    ; f, 用于存储当前寄存器暂存状态的内存地址
//
//
// 现在有 3 个指令, 分别如下
// 00000000    ; set 指令, 用于往寄存器中存一个数字
// 00000001    ; load 指令, 用于从内存中载入一个数据到寄存器中
// 00000010    ; 这是 add 指令,
// 00000011    ; save 指令, 用于把寄存器里面的数据放到内存中
// 00000100    ; compare, 比较指令, 比较的是 x 和 y 的大小, 这个结果存在寄存器 c1 里面
// 00000101    ; jump, 设置 pc 寄存器的值
//             ; jump 100
// 00000110    ; jump_when_less
// 00000111    ; save_from_register
//             ; 把寄存器里面的数据保存到寄存器里面的内存地址中

var pc = 0
var x, y, z, c1, f

const run = function(memory) {
    /*
    这是一个虚拟机程序

    之前作业的 assembler.py 可以生成一个包含数字的数组
    参数 memory 就是那个数组

    run 函数将 memory 数组视为内存，可以执行这个内存
    你需要用变量来模拟寄存器，模拟程序的执行

    稍后会给出一个用于测试的 memory 例子并更新在 #general
    你现在可以用自己生成的内容来测试

    注意，memory 目前只能支持 256 字节
    因为 pc 寄存器只有 8 位（1 字节）
    */
    log(memory)
    while (pc < memory.length) {
        // let inner_pc = parseInt(memory[pc],2)
        if (inner_pc == '0b00000000') {
            set(memory[pc + 1], memory[pc + 2])
        }else if (inner_pc == '0b00000001') {
            load(memory[pc + 1], memory[pc + 2])
        }else if (inner_pc == '0b00000011') {
            save(memory[pc + 1], memory[pc + 2])
        }else if (inner_pc == '0b00000010') {
            add(memory[pc + 1], memory[pc + 2],  memory[pc + 3])
        }
    }
    log(memory)
}

const set = function(variable, value){
    d[variable](value)
    pc += 3
}

const load = function(m, variable){
    index = int(m[1:])
    value = memory[index]
    d[variable](value)
    pc += 3
}

const save = function(variable, m){
    index = int(m[1:])
    memory[index] = d[variable]
    pc += 3
}

const add = function(x1, x2, x3){
    x1 = d[x1]
    x2 = d[x2]
    d[x3](x1 + x2)
    pc += 4
}
// // 2，实现下面的功能
// 让上面的虚拟机程序支持显示屏， 显示屏的像素是 10 x10
// 因此内存的最后 100 个字节用于表示屏幕上的内容， 每个字节表示一个像素， 从左到右从上到下
// 每个像素可表示 255 个颜色
//
// 用一个 10 x10 的 canvas 来模拟这个显示屏
