const stop = function(){
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
        // log('test', a, x)
        list.push(a)
    }
    return list
}

const enhance_memory = function(memory, l){
    while (memory.length < l) {
        memory.push(parseInt(0, 2))
    }
}

const trans_to_string = function(value){
    let s = ''
    value = value.toString(2)
    if (value.length <= 8) {
        for (var i = 0; i < 8 - value.length; i++) {
            s += '0'
        }
        s += value
    }
    return s
}

const trans_to_RGBA = function(list_i, begin, end){
    return parseInt(trans_to_string(list_i).slice(begin, end)) * 64
}
