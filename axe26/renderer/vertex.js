class GuaVertex extends GuaObject {
    // 表示顶点的类, 包含 GuaVector 和 GuaColor
    // 表示了一个坐标和一个颜色
    constructor(position, color) {
        super()
        this.position = position
        this.color = color
    }
    add(e){
        let position = this.position.add(e.position)
        let color = this.color.add(e.color)
        return GuaVertex.new(position, color)
    }
    sub(e){
        let position = this.position.sub(e.position)
        let color = this.color.sub(e.color)
        return GuaVertex.new(position, color)
    }
    mul(e){
        let position = this.position.mul(e)
        let color = this.color.mul(e)
        return GuaVertex.new(position, color)
    }
}
