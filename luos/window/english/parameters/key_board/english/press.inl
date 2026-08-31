namespace Gnik_luos {
    bool Key_board::press(int key) {
        if (GetAsyncKeyState(key) & 0x8000) {
            for (int i = 0; i < before_key_index; i++) {
                if (key == save_key[before_key][i]) {
                    for (int i = 0; i < current_key_index; i++) {
                        if (key == save_key[current_key][i]) {
                            return false;
                        }
                    }
                    save_key[current_key][current_key_index] = key;
                    current_key_index += 1;
                    return false;
                }
            }
            for (int i = 0; i < current_key_index; i++) {
                if (key == save_key[current_key][i]) {
                    return false;
                }
            }
            save_key[current_key][current_key_index] = key;
            current_key_index += 1;
            return true;
        } else {
            for (int i = 0; i < current_key_index; i++) {
                if (key == save_key[current_key][i]) {
                    return false;
                }
            }
            save_key[current_key][current_key_index] = key;
            current_key_index += 1;
            return false;
        }
    }
}