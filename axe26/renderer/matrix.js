class Matrix extends GuaObject{
    constructor(matrix_list){
        super()
        if (matrix_list != undefined) {
            this.m = matrix_list
        }else {
            this.m = [
                [0, 0, 0, 0],
                [0, 0, 0, 0],
                [0, 0, 0, 0],
                [0, 0, 0, 0],
            ]
        }
    }
    getitem(item){
        let [i, j] = item
        return this.m[i][j]
    }
    setitem(key, value){
        let [i, j] = key
        this.m[i][j] = value
    }
    eq(other){
        return this.str() == other.str()
    }
    str(){
        let s = ''
        for (var i = 0; i < 16; i++) {
            s += this.m[Math.floor(i / 4)][i % 4].toFixed(3)
            if (i % 4 == 3) {
                s += '\n'
            }else {
                s += ' '
            }
        }
        return s
    }
    mul(other){
        let m1 = this
        let m2 = other
        let m = Matrix.new()
        for (var index = 0; index < 16; index++) {
            let i = Math.floor(index / 4)
            let j = index % 4
            m.setitem([i, j], m1.getitem([i, 0]) * m2.getitem([0, j]) + m1.getitem([i, 1]) * m2.getitem([1, j]) + m1.getitem([i, 2]) * m2.getitem([2, j]) + m1.getitem([i, 3]) * m2.getitem([3, j]))
        }
        return m
    }
    static zero(){
        return Matrix.new()
    }
    static identity(){
        let m = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]
        return Matrix.new(m)
    }
    static lookAtLH(eye, target, up){
        // Builds a left-handed look-at matrix.
        // :type eye: Vector
        // :type target: Vector
        // :type up: Vector
        // :rtype : Matrix
        let zaxis = (target.sub(eye)).normalize()
        let xaxis = up.cross(zaxis).normalize()
        let yaxis = zaxis.cross(xaxis).normalize()

        let ex = -xaxis.dot(eye)
        let ey = -yaxis.dot(eye)
        let ez = -zaxis.dot(eye)

        let m = [
            [xaxis.x, yaxis.x, zaxis.x, 0],
            [xaxis.y, yaxis.y, zaxis.y, 0],
            [xaxis.z, yaxis.z, zaxis.z, 0],
            [ex, ey, ez, 1]
        ]
        return Matrix.new(m)
    }
    static perspectiveFovLH(field_of_view, aspect, znear, zfar){
        // Builds a left-handed perspective projection matrix based on a field of view.
        // :type field_of_view: float
        // :type aspect: float
        // :type znear: float
        // :type zfar: float
        // :rtype: Matrix
        let h = 1 / Math.tan(field_of_view / 2)
        let w = h / aspect
        let m = [
            [w, 0, 0, 0],
            [0, h, 0, 0],
            [0, 0, zfar / (zfar - znear), 1],
            [0, 0, (znear * zfar) / (znear - zfar), 0],
        ]
        return Matrix.new(m)
    }
    static rotationX(angle){
        let s = Math.sin(angle)
        let c = Math.cos(angle)
        let m = [
            [1, 0,  0, 0],
            [0, c,  s, 0],
            [0, -s, c, 0],
            [0, 0,  0, 1],
        ]
        return Matrix.new(m)
    }
    static rotationY(angle){
        let s = Math.sin(angle)
        let c = Math.cos(angle)
        let m = [
            [c, 0, -s, 0],
            [0, 1, 0,  0],
            [s, 0, c,  0],
            [0, 0, 0,  1],
        ]
        return Matrix.new(m)
    }
    static rotationZ(angle){
        let s = Math.sin(angle)
        let c = Math.cos(angle)
        let m = [
            [c,  s, 0, 0],
            [-s, c, 0, 0],
            [0,  0, 1, 0],
            [0,  0, 0, 1],
        ]
        return Matrix.new(m)
    }
    static rotation(angle){
        let x1 = Matrix.rotationZ(angle.z)
        let x2 = Matrix.rotationX(angle.x)
        let x3 = Matrix.rotationY(angle.y)
        let matrix = x1.mul(x2.mul(x3))
        return matrix
    }
    static translation(vector){
        let v = vector
        let x = v.x
        let y = v.y
        let z = v.z
        let m = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [x, y, z, 1],
        ]
        return Matrix.new(m)
    }
    transformVector(vector){
        let v = vector
        let m = this
        let x = v.x * m.getitem([0, 0]) + v.y * m.getitem([1, 0]) + v.z * m.getitem([2, 0]) + m.getitem([3, 0])
        let y = v.x * m.getitem([0, 1]) + v.y * m.getitem([1, 1]) + v.z * m.getitem([2, 1]) + m.getitem([3, 1])
        let z = v.x * m.getitem([0, 2]) + v.y * m.getitem([1, 2]) + v.z * m.getitem([2, 2]) + m.getitem([3, 2])
        let w = v.x * m.getitem([0, 3]) + v.y * m.getitem([1, 3]) + v.z * m.getitem([2, 3]) + m.getitem([3, 3])
        return Vector.new(x / w, y / w, z / w)
    }
}
