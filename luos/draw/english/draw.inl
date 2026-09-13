namespace Gnik_luos {
    void Draw::draw(Draw_line_cmd& cmd) {
        if (cmd.cmd_update) {
            cmd.update();
            cmd.cmd_update = false;
        }
        if (private_vertex_sink != nullptr) {
            private_vertex_sink->insert(private_vertex_sink->end(), cmd.vertex().begin(), cmd.vertex().end());
        }
    }
}
