namespace Gnik_luos {
    // 每帧把相机的可见矩形交给绘制器:外部填充按它留洞,绘制器不必认识相机
    void Window::sync_draw() {
        drawer.set_view(camera.rect());
    }
}
