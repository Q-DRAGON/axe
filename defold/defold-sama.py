"""
1，Defold 是什么？
「开箱即用的解决方案」，登录后可以下载编辑器（目前有1、2两个版本，我下的是2），所有的操作都可在这个编辑器中进行。在该编辑器还可直接创建新手指引项目。脚本用 Lua 语言编写。

2，网页上有几个小例子：对象移动、用户输入、消息传递、GUI、粒子效果、物理效果等等。

3，Lua 写的 script 中主要有以下几种函数：
init() 对象的初始化
update() 每 dt 时间一次的更新
on_input() 键盘鼠标输入的处理入口
on_message() 接收到消息的处理入口
以上几个函数似乎是在特定情况被自动调用的，有待进一步了解。
go.animate() 设置对象的动画，接收若干参数
go 对象有一些方法（例如获取位置），以及一些枚举类型的常量（例如动画的种类）

4，相当一部分操作（动画、声音、按键绑定、物理效果）是在 Defold 编辑器中设置的，而不是直接写在脚本中。

----

如何添加对象：
1，在 Assets 列表 右键 - New - Game Object ： 创建出 *.go 文件
2，在 Outline 列表 右键 - Add Component - Sprite ：为对象添加图形
3，点击上一步添加的 Sprite ，在下面 Properties 选择 Image （只能在 *.atlas  中选）
4，选择 Default Animation ，也是在 atlas 中预先定义的。
5，按 F 键使图形显示到最佳位置
6，在 Outline 列表 右键 - Add Component - Collision Object ：为对象添加碰撞模型，在 Properties 设置 Type 为 Kinematic（碰撞模型随对象移动）
7，右键点击上一步的 Collision Object - Add Shape - Sphere ：点击中央屏幕上的三个按钮调整碰撞模型的位置、角度、大小。
8，在 Outline 列表 右键 - Add Component File ：选择 *.script（这里面是该对象的具体行为）
9，创建对象的工厂模式（如果需要）：在 factory.go 的 Outline 列表，右键 - Add Component - Factory，设置 id，选择 Prototype 为之前创建的 *.go
10，工厂对象的脚本（如果需要）：在 factory.script 编写
component = "#*_factory"
factory.create(component, pos)
"""
