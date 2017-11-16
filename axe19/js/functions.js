const draw_char = functions(memory, char, x, y){
    let index = (guacoding2[char] + 1) * 2
    let ele = memory[index].str(2) + memory[index + 1].str(2)
    let count = 0
    while (count < 32) {
        for (let i = 0; i < 4; i++) {
            for (let j = 0; i < 8; i++) {
                if (ele[count] == '1') {
                    memory[32 * j + i + x] = 61455
                }else {
                    memory[32 * j + i + x] = 0
                }
            }
        }
        count ++
    }
}

const start_of_command = function(memory){
    while (memory.lenth < 1024) {
        memory.push(0)
    }
    pc += 1
}

const compare = function(memory){
    let index1 = memory[pc + 1]
    let index2 = memory[pc + 2]
    let a = d[index1]()
    let b = d[index2]()
    let result
    if (a > b) {
        result = 2
    }else if (a = b) {
        result = 1
    }else if (a < b) {
        result = 0
    }
    c1 = result
    pc += 3
}

const jump = function(memory){
    pc = memory[pc + 1]
}

const jump_when_less = function(memory){
    if (c1 == 0) {
        pc = memory[pc + 1]
    }else {
        pc += 2
    }
}

const stop = function(memory){
    pc = memory.length
}

const save_from_register = function(memory){
    let value = d[memory[pc + 1]]()
    let pointer = d[memory[pc + 2]]()
    memory[pointer] = value
    pc += 3
}

const set = function(memory){
    let variable = memory[pc + 1]
    let value = memory[pc + 2]
    d[variable](value)
    pc += 3
}

const load = function(memory){
    let index = memory[pc + 1]
    let variable = memory[pc + 2]
    let value = memory[index]
    d[variable](value)
    pc += 3
}

const save = function(memory){
    let variable = memory[pc + 1]
    let index = memory[pc + 2]
    memory[index] = d[variable]()
    pc += 3
}

const add = function(memory){
    let x1 = memory[pc + 1]
    let x2 = memory[pc + 2]
    let x3 = memory[pc + 3]
    let a = d[x1]()
    let b = d[x2]()
    let sum = a + b
    d[x3](sum)
    pc += 4
}

const randomlist = function(){
    // 生成随机数组，没用了
    let list = []
    for (var i = 0; i < 256; i++) {
        let x = Math.random() * 256
        let a = trans_to_string(Math.floor(x).toString(2))
        list.push(a)
    }
    return list
}

const enhance_memory = function(memory, l){
    while (memory.length < l) {
        memory.push(parseInt(0, 2))
    }
    return memory
}

const trans_to_string = function(value){
    // 将数字转为长度16的字符串
    let s = ''
    value = value.toString(2)
    if (value.length <= 16) {
        for (var i = 0; i < 16 - value.length; i++) {
            s += '0'
        }
        s += value
    }
    return s
}

const trans_to_RGBA = function(list_i, begin, end){
    // 将切割后的二进制数分别转为rgba
    return parseInt(trans_to_string(list_i).slice(begin, end)) * 16
}
