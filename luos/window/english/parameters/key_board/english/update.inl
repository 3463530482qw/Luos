namespace Gnik_luos {
    void Key_board::update() {
        std::lock_guard lock(save_key_mutex);
        std::swap(current_key, before_key);
        for (int i = 0; i < 256; i++) {
            save_key[current_key][i] = false;
        }
        save_press.fill(false);
        save_release.fill(false);
    }
}