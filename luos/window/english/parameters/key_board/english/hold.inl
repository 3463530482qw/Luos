namespace Gnik_luos {
    bool Key_board::hold(int key) {
        std::lock_guard lock(save_key_mutex);
        if (key < 0 || key >= 256) {
            return false;
        }
        if (GetAsyncKeyState(key) & 0x8000) {
            save_key[current_key][key] = true;
            return true;
        }
        return save_key[before_key][key] || save_key[current_key][key];
    }
}
