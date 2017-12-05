class GuaCamera extends GuaObject {
    constructor() {
        super()
        this.position = GuaVector.new(0, 0, -10)
        this.target = GuaVector.new(0, 0, 0)
        this.up = GuaVector.new(0, 1, 0)
    }
}

class GuaCanvas extends GuaObject {
    constructor(selector) {
        super()
        let canvas = _e(selector)
        this.canvas = canvas
        this.context = canvas.getContext('2d')
        this.w = canvas.width
        this.h = canvas.height
        this.pixels = this.context.getImageData(0, 0, this.w, this.h)
        this.bytesPerPixel = 4
        // this.pixelBuffer = this.pixels.data
        this.camera = GuaCamera.new()
        this.zbuffer = []
    }
    render() {
        // 执行这个函数后, 才会实际地把图像画出来
        // ES6 新语法, 取出想要的属性并赋值给变量, 不懂自己搜「ES6 新语法」
        let {pixels, context} = this
        context.putImageData(pixels, 0, 0)
    }
    clear(color=GuaColor.transparent()) {
        // color GuaColor
        // 用 color 填充整个 canvas
        // 遍历每个像素点, 设置像素点的颜色
        let {w, h} = this
        for (let x = 0; x < w; x++) {
            for (let y = 0; y < h; y++) {
                this._setPixel(x, y, 1000000, color)
            }
        }
        this.render()
    }
    _getPixel(x, y) {
        let int = Math.floor
        x = int(x)
        y = int(y)
        // 用座标算像素下标
        let i = (y * this.w + x) * this.bytesPerPixel
        // 设置像素
        let p = this.pixels.data
        return GuaColor.new(p[i], p[i+1], p[i+2], p[i+3])
    }
    _setPixel(x, y, z, color) {
        // color: GuaColor
        // 这个函数用来设置像素点, _ 开头表示这是一个内部函数, 这是我们的约定
        // 浮点转 int
        let int = Math.round
        x = int(x)
        y = int(y)
        z = Number(z)
        // 用座标算像素下标
        let i = (y * this.w + x) * this.bytesPerPixel
        // 设置像素
        let p = this.pixels.data
        let {r, g, b, a} = color
        // 一个像素 4 字节, 分别表示 r g b a
        p[i] = int(r)
        p[i+1] = int(g)
        p[i+2] = int(b)
        p[i+3] = int(a)

        let index = y * this.w + x
        this.zbuffer[index] = z
    }
    drawPoint(point, color=GuaColor.black()) {
        // point: GuaPoint
        let {w, h} = this
        let p = point
        let newindex = Math.round(p.y) * w + Math.round(p.x)
        if (p.z <= this.zbuffer[newindex]) {
            if (p.x >= 0 && p.x <= w) {
                if (p.y >= 0 && p.y <= h) {
                    this._setPixel(p.x, p.y, p.z, color)
                }
            }
        }
    }
    // drawLine(v1, v2, color=GuaColor.black()) {
        // v1 v2 分别是起点和终点
        // color GuaColor
        // 使用 drawPoint 函数来画线
    //     let [x1, y1, z1, x2, y2, z2] = [v1.x, v1.y, v1.z, v2.x, v2.y, v2.z]
    //     let dx = x2 - x1
    //     let dy = y2 - y1
    //     let dz = z2 - z1
    //
    //     if(Math.abs(dx) > Math.abs(dy)) {
    //         let xmin = Math.min(x1, x2)
    //         let xmax = Math.max(x1, x2)
    //         let zmin = Math.min(z1, z2)
    //         let zmax = Math.max(z1, z2)
    //         let ratioyx = dx == 0 ? 0 : dy / dx
    //         let ratiozx = dx == 0 ? 0 : dz / dx
    //         let ratioxz = dz == 0 ? 0 : dx / dz
    //         let ratioyz = dz == 0 ? 0 : dy / dx
    //         if (Math.abs(dx) > Math.abs(dz)) {
    //             for(let x = xmin; x < xmax; x++) {
    //                 let y = y1 + (x - x1) * ratioyx
    //                 let z = z1 + (x - x1) * ratiozx
    //                 this.drawPoint(GuaVector.new(x, y, z), color)
    //             }
    //         }else {
    //             for(let z = zmin; z < zmax; z++) {
    //                 let y = y1 + (z - z1) * ratioyz
    //                 let x = x1 + (z - z1) * ratioxz
    //                 this.drawPoint(GuaVector.new(x, y, z), color)
    //             }
    //         }
    //     } else {
    //         let ymin = Math.min(y1, y2)
    //         let ymax = Math.max(y1, y2)
    //         let zmin = Math.min(z1, z2)
    //         let zmax = Math.max(z1, z2)
    //         let ratioxy = dy == 0 ? 0 : dx / dy
    //         let ratiozy = dy == 0 ? 0 : dz / dy
    //         let ratioxz = dz == 0 ? 0 : dx / dz
    //         let ratioyz = dz == 0 ? 0 : dy / dz
    //         if (Math.abs(dy) > Math.abs(dz)) {
    //             for(let y = ymin; y < ymax; y++) {
    //                 let x = x1 + (y - y1) * ratioxy
    //                 let z = z1 + (y - y1) * ratiozy
    //                 this.drawPoint(GuaVector.new(x, y, z), color)
    //             }
    //         }else {
    //             for(let z = zmin; z < zmax; z++) {
    //                 let x = x1 + (z - z1) * ratioxz
    //                 let y = y1 + (z - z1) * ratioyz
    //                 this.drawPoint(GuaVector.new(x, y, z), color)
    //             }
    //         }
    //     }
    // }
    drawLine(v1, v2, color=GuaColor.black()) {
        // v1 v2 分别是起点和终点
        // color GuaColor
        // 使用 drawPoint 函数来画线
        let [x1, y1, x2, y2] = [v1.x, v1.y, v2.x, v2.y]
        let dx = x2 - x1
        let dy = y2 - y1

        if(Math.abs(dx) > Math.abs(dy)) {
            let xmin = Math.min(x1, x2)
            let xmax = Math.max(x1, x2)
            let ratio = dx == 0 ? 0 : dy / dx
            for(let x = xmin; x < xmax; x++) {
                let y = y1 + (x - x1) * ratio
                let factor = 0
                if (x2 != x1) {
                    factor = (x - x1) / (x2 - x1);
                }
                let v = v1.interpolate(v2, factor)
                v.z -= 0.0001
                this.drawPoint(v, color)
            }
        } else {
            let ymin = Math.min(y1, y2)
            let ymax = Math.max(y1, y2)
            let ratio = dy == 0 ? 0 : dx / dy
            for(let y = ymin; y < ymax; y++) {
                let x = x1 + (y - y1) * ratio
                let factor = 0
                if (y2 != y1) {
                    factor = (y - y1) / (y2 - y1);
                }
                let v = v1.interpolate(v2, factor)
                v.z -= 0.0001
                this.drawPoint(v, color)
            }
        }
    }
    drawScanline(v1, v2) {
        let [a, b] = [v1, v2].sort((va, vb) => va.position.x - vb.position.x)
        let y = a.position.y
        let x1 = a.position.x
        let x2 = b.position.x
        for (let x = x1; x <= x2; x++) {
            let factor = 0
            if (x2 != x1) {
                factor = (x - x1) / (x2 - x1);
            }
            let color = a.color.interpolate(b.color, factor)
            let newvector = a.position.interpolate(b.position, factor)
            this.drawPoint(newvector, color)
        }
    }
    drawTriangle(v1, v2, v3) {
        let [a, b, c] = [v1, v2, v3].sort((va, vb) => va.position.y - vb.position.y)
        // log(a, b, c)
        let middle_factor = 0
        if (c.position.y - a.position.y != 0) {
            middle_factor = (b.position.y - a.position.y) / (c.position.y - a.position.y)
        }
        let middle = a.interpolate(c, middle_factor)
        let start_y = a.position.y
        let end_y = b.position.y
        for (let y = start_y; y <= end_y; y++) {
            let factor = 0
            if (end_y != start_y) {
                factor = (y - start_y) / (end_y - start_y)
            }
            let va = a.interpolate(middle, factor)
            let vb = a.interpolate(b, factor)
            // log(va.position, vb.position)
            this.drawScanline(va, vb)
        }
        start_y = b.position.y
        end_y = c.position.y
        for (let y = start_y; y <= end_y; y++) {
            let factor = 0
            if (end_y != start_y) {
                factor = (y - start_y) / (end_y - start_y)
            }
            let va = middle.interpolate(c, factor)
            let vb = b.interpolate(c, factor)
            // log(va.position, vb.position)
            this.drawScanline(va, vb)
        }
    }
    drawImage(guaimage){
        let list = guaimage.split('\n').join(' ').split(' ')
        this.width = Number(list[2])
        this.height = Number(list[3])
        let data = []
        for (var i = 4; i < list.length; i++) {
            data.push(Number(list[i]))
        }
        // this.pixels.data = data
        

    }
    // drawTriangleLine
    project(coordVector, transformMatrix) {
        let {w, h} = this
        let [w2, h2] = [w/2, h/2]
        let point = transformMatrix.transform(coordVector.position)
        let x = point.x * w2 + w2
        let y = - point.y * h2 + h2

        let v = GuaVector.new(x, y, point.z)
        return GuaVertex.new(v, coordVector.color)
    }
    drawMesh(mesh) {
        let self = this
        // camera
        let {w, h} = this
        let {position, target, up} = self.camera
        const view = Matrix.lookAtLH(position, target, up)
        const projection = Matrix.perspectiveFovLH(0.8, w / h, 0.1, 1)

        const rotation = Matrix.rotation(mesh.rotation)
        const translation = Matrix.translation(mesh.position)

        const world = rotation.multiply(translation)
        const transform = world.multiply(view).multiply(projection)

        for (let t of mesh.indices) {
            let [a, b, c] = t.map(i => mesh.vertices[i])
            let [v1, v2, v3] = [a, b, c].map(v => self.project(v, transform))
            self.drawTriangle(v1, v2, v3)
            self.drawLine(v1.position, v2.position)
            self.drawLine(v1.position, v3.position)
            self.drawLine(v2.position, v3.position)
        }
    }
}
