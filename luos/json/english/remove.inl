namespace Gnik_luos {
    void Json::remove(const std::string& name) {
        data.erase(name);
    }
}
