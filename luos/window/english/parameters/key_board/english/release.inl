namespace Gnik_luos {
    bool Key_board::release(int key) {
        std::lock_guard lock(save_key_mutex);
        if (key < 0 || key >= 256) {
            return false;
        }
        if (GetAsyncKeyState(key) & 0x8000) {
            save_key[current_key][key] = true;
            return false;
        }
        if (!save_key[before_key][key]) {
            return false;
        }
        if (save_release[key]) {
            return false;
        }
        save_release[key] = true;
        return true;
    }
}
