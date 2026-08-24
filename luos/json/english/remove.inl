namespace Gnik_luos {
    void Json::remove(std::string_view name) {
        data.erase(name.data());
    }
}
