const log = console.log.bind(console)

const _e = (sel) => document.querySelector(sel)

const interpolate = function(a, b, factor){
    return a.add(b.sub(a).mul(factor))
}

const int = function(x){
    return parseInt(x)
}
