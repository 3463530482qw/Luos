namespace Gnik_luos {
    void Window_time::youklx_frame_time() {
        dt = youk_target_time / ((private_frame_accum + 1.0f) * (private_frame_accum + 2.0f));
    }
}
