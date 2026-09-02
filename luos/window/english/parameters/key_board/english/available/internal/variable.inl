std::mutex save_key_mutex;
std::array<std::array<bool, 256>, 2> save_key{};
std::array<bool, 256> save_press{};
std::array<bool, 256> save_release{};
uint8_t current_key{0};
uint8_t before_key{1};
