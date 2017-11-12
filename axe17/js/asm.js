const clarify = function(asm){
    // 处理注释, 并转换为列表
    asm_nospace = asm.trim()
    asm_hang = asm_nospace.split('\n')
    asm_noquote = []
    asm_hang.map(function(e, index){
        asm_i = e.split(';')[0].trim()
        asm_noquote.push(asm_i)
    })
    asm_string = asm_noquote.join(' ')
    asm_hang_nospace = asm_string.trim()
    asm = asm_hang_nospace.split(' ')
    return asm
}

const assembler = function(asm_code) {
    // asm_code 是汇编字符串
    // 将汇编语言转成机器语言
    log('old asm:\n', asm_code)
    asm = clarify(asm_code)
    asm.map(function(e, i){
        if (e in asm_d) {
            asm[i] = asm_d[e]
        }else if (e.constructor == String && e.slice(0,1) == '@') {
            asm[i] = Number(e.slice(1,))
        }else{
            asm[i] = Number(e)
        }
    })
    log('new asm:\n', asm)
    return asm
}
