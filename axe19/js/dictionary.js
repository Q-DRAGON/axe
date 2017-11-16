const d = {
    0b0000000100000000: function(i){
        if (i == undefined) {
            return x
        }else {
            x = i
        }
    },
    0b0000001000000000: function(i){
        if (i == undefined) {
            return y
        }else {
            y = i
        }
    },
    0b0000001100000000: function(i){
        if (i == undefined) {
            return z
        }else {
            z = i
        }
    },
    // 用于存储比较指令的结果 0 表示小于, 1 表示相等, 2 表示大于
    0b0000010000000000: function(i){
        if (i == undefined) {
            return c1
        }else {
            c1 = i
        }
    },
    // 用于存储当前寄存器暂存状态的内存地址
    0b0000010100000000: function(i){
        if (i == undefined) {
            return f
        }else {
            f = i
        }
    },
    0b0000001110000000: function(i){
        if (i == undefined) {
            return r
        }else {
            r = i
        }
    },
    0b1000001100000000: function(i){
        if (i == undefined) {
            return w
        }else {
            w = i
        }
    },
    0b1111111111111011: function(i){
        if (i == undefined) {
            return count1
        }else {
            count1 = i
        }
    },
}

const func_d = {
    0b0000000000000000: set,
    0b0000000100000000: load,
    0b0000001000000000: add,
    0b0001000000000000: mod_2,
    0b0010000000000000: divide,
    0b0000100000000000: multiply,
    0b0000001100000000: save,
    0b0000011100000000: save_from_register,
    //  比较指令, 比较的是 x 和 y 的大小, 这个结果存在寄存器 c1 里面
    0b0000010000000000: compare,
    // 设置 pc 寄存器的值
    0b0000010100000000: jump,
    0b0000011000000000: jump_when_less,
    0b1111111111111111: stop,
    0b1111111111111110: start_of_command,
    0b1111111111111101: draw_char,
    0b0000100100000000: load_from_register,
}
