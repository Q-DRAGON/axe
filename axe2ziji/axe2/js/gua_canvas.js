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
        this.start = null
        this.end = null
        this.listenMouse()
        this.enableDraw = false
        this.data = null
        this.drawStyle = 'line'
        this.penColor = GuaColor.black()
    }
    render() {
        // 执行这个函数后, 才会实际地把图像画出来
        // ES6 新语法, 取出想要的属性并赋值给变量, 不懂自己搜「ES6 新语法」
        let {pixels, context} = this
        context.putImageData(pixels, 0, 0)
    }
    clear(color=GuaColor.white()) {
        // color GuaColor
        // 用 color 填充整个 canvas
        // 遍历每个像素点, 设置像素点的颜色
        let {w, h} = this
        for (let x = 0; x < w; x++) {
            for (let y = 0; y < h; y++) {
                this._setPixel(x, y, color)
            }
        }
        this.render()
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
    listenMouse(){
        var self = this
        self.canvas.addEventListener('mousedown', function(event) {
            self.enableDraw = true
            var x = event.offsetX
            var y = event.offsetY
            self.start = GuaPoint.new(x, y)
            self.data = new Uint8ClampedArray(self.pixels.data)
        })
        this.canvas.addEventListener('mousemove', function(event) {
            if (self.enableDraw == true) {
                var x = event.offsetX
                var y = event.offsetY
                self.end = GuaPoint.new(x, y)
                self.pixels.data.set(self.data)
                if (self.drawStyle == 'line') {
                    self.drawLine(self.start, self.end, self.penColor)
                }else if (self.drawStyle == 'rect') {
                    var size = GuaSize.new(self.end.x - self.start.x, self.end.y - self.start.y)
                    self.drawRect(self.start, size, null, self.penColor)
                }
                self.render()
            }
        })
        this.canvas.addEventListener('mouseup', function(event) {
            self.enableDraw = false
            var x = event.offsetX
            var y = event.offsetY
            self.end = GuaPoint.new(x, y)
        })

    }
    drawPoint(point, color=GuaColor.black()) {
        // point: GuaPoint
        let {w, h} = this
        let p = point
        if (p.x >= 0 && p.x <= w) {
            if (p.y >= 0 && p.y <= h) {
                this._setPixel(p.x, p.y, color)
            }
        }
    }
    drawLine(p1, p2, color=GuaColor.black()) {
        // p1 p2 分别是起点和终点, GuaPoint 类型
        // color GuaColor
        // 使用 drawPoint 函数来画线
        let dx = p2.x - p1.x
        let dy = p2.y - p1.y
        if (Math.abs(dy) > Math.abs(dx)) {
            let y = p1.y
            while (y !== p2.y) {
                let x = dx / dy * (y - p1.y) + p1.x
                let point = GuaPoint.new(x, y)
                this.drawPoint(point, color)
                let i = dy > 0 ? 1 : -1
                y += i
            }
        }else{
            let x = p1.x
            while (x !== p2.x) {
                let y = dx == 0 ? p1.y : dy / dx * (x - p1.x) + p1.y
                let point = GuaPoint.new(x, y)
                this.drawPoint(point, color)
                let i = dx > 0 ? 1 : -1
                x += i
            }
        }
    }
    drawRect(upperLeft, size, fillColor=null, borderColor=GuaColor.black()) {
        // upperLeft: GuaPoint, 矩形左上角座标
        // size: GuaSize, 矩形尺寸
        // fillColor: GuaColor, 矩形的填充颜色, 默认为空, 表示不填充
        // borderColor: GuaColor, 矩形的的边框颜色, 默认为黑色
        let x = upperLeft.x
        let y = upperLeft.y
        let p1 = GuaPoint.new(x, y)
        let p2 = GuaPoint.new(x + size.w, y)
        let p3 = GuaPoint.new(x + size.w, y + size.h)
        let p4 = GuaPoint.new(x, y + size.h)
        this.drawLine(p1, p2, borderColor)
        this.drawLine(p2, p3, borderColor)
        this.drawLine(p3, p4, borderColor)
        this.drawLine(p4, p1, borderColor)
        if (fillColor != null) {
            for (var j = y + 1; j < p3.y; j++) {
                this.drawLine(GuaPoint.new(x + 1, j), GuaPoint.new(p2.x, j), fillColor)
            }
        }
    }
    drawButton(upperLeft, size, fillColor=null, borderColor=GuaColor.black()){
        var self = this
        self.drawRect(upperLeft, size, fillColor, borderColor)
        self.render()
    }
    addElement(upperLeft, size, fillColor=null, borderColor=GuaColor.black()){
        var self = this
        self.drawButton(upperLeft, size, fillColor, borderColor)
    }
    __debug_draw_demo() {
        // 这是一个 demo 函数, 用来给你看看如何设置像素
        // ES6 新语法, 取出想要的属性并赋值给变量, 不懂自己搜「ES6 新语法」
        let {context, pixels} = this
        // 获取像素数据, data 是一个数组
        let data = pixels.data
        // 一个像素 4 字节, 分别表示 r g b a
        for (let i = 0; i < data.length; i += 4) {
            let [r, g, b, a] = data.slice(i, i + 4)
            r = 255
            a = 255
            data[i] = r
            data[i+3] = a
        }
        context.putImageData(pixels, 0, 0)
    }
}
