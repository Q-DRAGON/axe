class GuaVector extends GuaObject {
    // 表示顶点的类, 包含 GuaVector 和 GuaColor
    // 表示了一个坐标和一个颜色
    constructor(x, y) {
        super()
        this.x = x
        this.y = y
    }
    add(e){
        let x = this.x + e.x
        let y = this.y + e.y
        return GuaVector.new(x, y)
    }
    sub(e){
        let x = this.x - e.x
        let y = this.y - e.y
        return GuaVector.new(x, y)
    }
    mul(e){
        let x = this.x * e
        let y = this.y * e
        return GuaVector.new(x, y)
    }
}
