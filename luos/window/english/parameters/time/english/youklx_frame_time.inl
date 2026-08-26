namespace Gnik_luos {
    void Window_time::youklx_frame_time() {
        youk_frame_time += dt;
        youk_frame_time = youk_target_time / ((youk_frame_time + 1.0f) * (youk_frame_time + 2.0f));
    }
}