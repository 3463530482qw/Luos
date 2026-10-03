namespace Gnik_luos {
    Line& Draw::line() {
        frame_lines.emplace_back();   // 登记序就是绘制序:先登记的顶点排在前面
        return frame_lines.back();
    }

    Line& Draw::keep() {
        keep_lines.emplace_back();   // 常驻的排在当帧之前,之后不再动
        return keep_lines.back();
    }
}
