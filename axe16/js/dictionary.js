const d = {
    0b00010000: function(i){
        if (i == undefined) {
            return x
        }else {
            x = i
        }
    },
    0b00100000: function(i){
        if (i == undefined) {
            return y
        }else {
            y = i
        }
    },
    0b00110000: function(i){
        if (i == undefined) {
            return z
        }else {
            z = i
        }
    },
}

const func_d = {
    0b00000000: set,
    0b00000001: load,
    0b00000010: add,
    0b00000011: save,
    0b00000111: save_from_register,
    0b11111111: stop
}
