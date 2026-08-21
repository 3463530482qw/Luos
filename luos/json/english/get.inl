namespace Gnik_luos {
    simdjson::dom::element Json::get(const std::string& name) {
        // 按名查找配置,找不到就报错
        auto it = data.find(name);
        if (it == data.end())
            throw std::runtime_error("配置文件不存在: " + name);
        return it->second.root;
    }
}