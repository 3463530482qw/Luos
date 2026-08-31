namespace Gnik_luos {
    void Key_board::update() {
        std::swap(current_key, before_key);
        before_key_index = current_key_index;
        current_key_index = 0;
        save_key[current_key][0] = 0;
    }
}