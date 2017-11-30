class GuaVector extends GuaObject {
    // 表示顶点的类, 包含 GuaVector 和 GuaColor
    // 表示了一个坐标和一个颜色
    constructor(x, y, z) {
        super()
        this.x = x
        this.y = y
        this.z = z
    }
    add(e){
        let x = this.x + e.x
        let y = this.y + e.y
        let z = this.z + e.z
        return GuaVector.new(x, y, z)
    }
    sub(e){
        let x = this.x - e.x
        let y = this.y - e.y
        let z = this.z - e.z
        return GuaVector.new(x, y, z)
    }
    mul(e){
        let x = this.x * e
        let y = this.y * e
        let z = this.z * e
        return GuaVector.new(x, y, z)
    }
    length(){
        return Math.sqrt(this.x ** 2 + this.y ** 2 + this.z ** 2)
    }
    normalize(){
        let self = this
        let l = self.length()
        if (l == 0) {
            return self
        }else {
            let factor = 1 / l
            return self.mul(factor)
        }
    }
    dot(v){
        let self = this
        return self.x * v.x + self.y * v.y + self.z * v.z
    }
    cross(v){
        let self = this
        let x = self.y * v.z - self.z * v.y
        let y = self.z * v.x - self.x * v.z
        let z = self.x * v.y - self.y * v.x
        return GuaVector.new(x, y, z)
    }
}
let Vector = GuaVector
