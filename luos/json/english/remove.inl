namespace Gnik_luos {
    void Json::remove(std::string name) {
        // erase 立即销毁该 Document,精确释放内存
        data.erase(name);
    }
}
