class GuaCanvas extends GuaObject {
    constructor(selector) {
        super()
        var canvas = _e(selector)
        this.canvas = canvas
        this.context = canvas.getContext('2d')
        this.w = canvas.width
        this.h = canvas.height
        this.pixels = this.context.getImageData(0, 0, this.w, this.h)
        this.bytesPerPixel = 4
        this.data = null
        this.penColor = GuaColor.black()
    }
    render() {
        // 执行这个函数后, 才会实际地把图像画出来
        // ES6 新语法, 取出想要的属性并赋值给变量, 不懂自己搜「ES6 新语法」
        let {pixels, context} = this
        context.putImageData(pixels, 0, 0)
    }
    _setPixel(x, y, color) {
        // color: GuaColor
        // 这个函数用来设置像素点, _ 开头表示这是一个内部函数, 这是我们的约定
        // 浮点转 int
        let int = Math.floor
        x = int(x)
        y = int(y)
        // 用座标算像素下标
        let i = (y * this.w + x) * this.bytesPerPixel
        // 设置像素
        let p = this.pixels.data
        let {r, g, b, a} = color
        // 一个像素 4 字节, 分别表示 r g b a
        p[i] = r
        p[i+1] = g
        p[i+2] = b
        p[i+3] = a
    }
    drawPoint(point, color=GuaColor.black()) {
        let {w, h} = this
        let p = point
        if (p.x >= 0 && p.x <= w) {
            if (p.y >= 0 && p.y <= h) {
                this._setPixel(p.x, p.y, color)
            }
        }
    }
    drawScanline(v1, v2){
        // v1 v2 是 y 相等的 2 个 GuaVertex
        // 画有颜色的直线
        let [a, b] = [v1, v2].sort(function(a,b){
            return a.position.x - b.position.x;
        })
        let x1 = int(a.position.x)
        let x2 = int(b.position.x)
        let y = int(a.position.y)
        var sign = 0
        sign = (x2 > x1) ? 1 : -1
        let factor = 0
        for (var i = x1; i <= x2 + sign * 1; i += sign) {
            if (x1 != x2) {
                factor = (i - x1) / (x2 - x1)
            }
            var color = interpolate(a.color, b.color, factor)
            var vector = GuaVector.new(i, y)
            this.drawPoint(vector, color)
        }
        this.render()
    }
    drawTriangle(v1, v2, v3){
        // v1 v2 v3 都是 GuaVertex
        // 作为三角形的 3 个顶点
        let [a, b, c] = [v1, v2, v3].sort(function(a,b){
            return a.position.y - b.position.y;
        })
        let middle_factor = 0
        if (c.position.y - a.position.y != 0) {
            middle_factor = (b.position.y - a.position.y) / (c.position.y - a.position.y)
        }
        let middle = interpolate(a, c, middle_factor)
        let start_y = int(a.position.y)
        let end_y = int(b.position.y)
        for (var i = start_y; i < end_y + 1; i++) {
            let factor = 0
            if (end_y != start_y) {
                factor = (i - start_y) / (end_y - start_y)
            } else {
                factor = 0
            }
            let va = interpolate(a, b, factor)
            let vb = interpolate(a, middle, factor)
            this.drawScanline(va, vb)
        }
        start_y = int(b.position.y)
        end_y = int(c.position.y)
        for (var j = start_y; j < end_y + 1; j++) {
            let factor = 0
            if (end_y != start_y) {
                factor = (j - start_y) / (end_y - start_y)
            } else {
                factor = 0
            }
            let va = interpolate(b, c, factor)
            let vb = interpolate(middle, c, factor)
            this.drawScanline(va, vb)
        }
        this.render()
    }
}
