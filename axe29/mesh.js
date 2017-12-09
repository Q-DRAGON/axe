class GuaMesh extends GuaObject {
    // 表示三维物体的类
    constructor() {
        super()

        this.position = GuaVector.new(0, -2, 0)
        this.rotation = GuaVector.new(0, 0, 0)
        this.scale = GuaVector.new(1, 1, 1)
        this.vertices = null
        this.indices = null
        this.texture = undefined
    }
    static makeTexture(guaimage){
        let list = guaimage.split('\n').join(' ').split(' ')
        let data = []
        for (let i = 4; i < list.length; i++) {
            data.push(GuaColor.from32torgba(Number(list[i])))
        }
        data.width = Number(list[2])
        data.height = Number(list[3])
        return data
    }
    static fromGua3d(gua3dString, image){
        let texture = this.makeTexture(image)
        let list = gua3dString.split('\n').join(' ').split(' ')
        let vertices = []
        let num_of_vertices = Number(list[4])
        let num_of_vertices_end = 7 + num_of_vertices * 8
        for (let i = 7; i < num_of_vertices_end; i += 8) {
            let v = GuaVector.new(Number(list[i]), Number(list[i + 1]), Number(list[i + 2]))
            let c = GuaColor.randomColor()
            let t = GuaVector.new(Number(list[i + 6]), Number(list[i + 7]))
            // let c = GuaColor.green()
            vertices.push(GuaVertex.new(v, c, t))
        }
        let indices = []
        for (let i = num_of_vertices_end; i < list.length; i += 3) {
            indices.push([Number(list[i]), Number(list[i + 1]), Number(list[i + 2])])
        }
        let m = this.new()
        m.vertices = vertices
        m.indices = indices
        m.texture = texture
        return m
    }
    static cube() {
        // 8 points
        let points = [
            -1, 1,  -1,     // 0
            1,  1,  -1,     // 1
            -1, -1, -1,     // 2
            1,  -1, -1,     // 3
            -1, 1,  1,      // 4
            1,  1,  1,      // 5
            -1, -1, 1,      // 6
            1,  -1, 1,      // 7
        ]

        let vertices = []
        for (let i = 0; i < points.length; i += 3) {
            let v = GuaVector.new(points[i], points[i+1], points[i+2])
            let c = GuaColor.randomColor()
            // let c = GuaColor.red()
            vertices.push(GuaVertex.new(v, c))
        }

        // 12 triangles * 3 vertices each = 36 vertex indices
        let indices = [
            // 12
            [0, 1, 2],
            [1, 3, 2],
            [1, 7, 3],
            [1, 5, 7],
            [5, 6, 7],
            [5, 4, 6],
            [4, 0, 6],
            [0, 2, 6],
            [0, 4, 5],
            [5, 1, 0],
            [2, 3, 7],
            [2, 7, 6],
        ]
        let m = this.new()
        m.vertices = vertices
        m.indices = indices
        return m
    }
}
