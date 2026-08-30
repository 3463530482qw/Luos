namespace Gnik_luos {
    bool Key_board::press(int key) {
        for (int i = 0; i < before_key_index; i++) {
            if (save_key[current_key_index][i] == key) {
                return false;
            }
        }
        for (int i = 0; i < before_key; i++) {
            if (save_key[current_key][i] == key) {
                return true;
            }
        }
        if(GetAsyncKeyState(key) & 0x8000) {
            save_key[current_key][before_key] = key;
            before_key += 1;
            return true;
        } else {
            return false;
        }
    }
}