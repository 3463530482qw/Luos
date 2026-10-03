namespace Gnik_luos {
    // 每帧由窗口调用:绘制器检查本轮登记的命令,只重算脏的,顶点按登记序铺给渲染端
    Window& Window::draw() {
        drawer.draw();
        return *this;
    }
}
