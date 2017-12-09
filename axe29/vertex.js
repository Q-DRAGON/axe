class GuaVertex extends GuaObject {
    // 表示顶点的类, 包含 GuaVector 和 GuaColor
    // 表示了一个坐标和一个颜色
    constructor(position, color, texture) {
        super()
        this.position = position
        this.color = color
        this.texture = texture
    }
    interpolate(other, factor) {
        let a = this
        let b = other
        let p = a.position.interpolate(b.position, factor)
        let c = a.color.interpolate(b.color, factor)
        let t = a.texture.interpolate(b.texture, factor)
        return GuaVertex.new(p, c, t)
    }
}
