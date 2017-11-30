class GuaColor extends GuaObject {
    // 表示颜色的类
    constructor(r, g, b, a) {
        super()
        this.r = r
        this.g = g
        this.b = b
        this.a = a
    }
    // 常见的几个颜色
    // 静态方法，不用传入实例，用类调用
    static black() {
        return this.new(0, 0, 0, 255)
    }
    static white() {
        return this.new(255, 255, 255, 255)
    }
    static red() {
        return this.new(255, 0, 0, 255)
    }
    static green(){
        return this.new(0, 255, 0, 255)
    }
    static blue(){
        return this.new(0, 0, 255, 255)
    }
    static cyan(){
        return this.new(0, 255, 255, 255)
    }
    static transHEXtoRGB(hex){
        let r = hex.slice(1,3)
        let g = hex.slice(3,5)
        let b = hex.slice(5,7)
        r = parseInt(r, 16)
        g = parseInt(g, 16)
        b = parseInt(b, 16)
        return this.new(r, g, b, 255)
    }
    add(e){
        let r = this.r + e.r
        let g = this.g + e.g
        let b = this.b + e.b
        let a = this.a + e.a
        return GuaColor.new(r, g, b, a)
    }
    sub(e){
        let r = this.r - e.r
        let g = this.g - e.g
        let b = this.b - e.b
        let a = this.a - e.a
        return GuaColor.new(r, g, b, a)
    }
    mul(e){
        let r = this.r * e
        let g = this.g * e
        let b = this.b * e
        let a = this.a * e
        return GuaColor.new(r, g, b, a)
    }
}
