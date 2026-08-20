namespace Gnik_luos {
    void Scene::load(const std::string& dll_path, const std::string& function_name) {
        auto it = private_data.find(function_name);
        if (it != private_data.end()) {
            FreeLibrary(it->second);
            private_data.erase(it);
        }
        auto handle = LoadLibraryA(dll_path.c_str());
        if (!handle) {
            std::cerr << "Failed to load DLL: " << dll_path << std::endl;
            return;
        }
        auto function = reinterpret_cast<void(*)()>(GetProcAddress(handle, function_name.c_str()));
        if (function) {
            data[function_name] = function;
            private_data[function_name] = handle;
        } else {
            std::cerr << "Function " << function_name << " not found in " << dll_path << std::endl;
            FreeLibrary(handle);
        }
    }

    void Scene::batch_load(const rapidjson::Document& json, const std::string& type) {
        if (!json.IsObject()) {
            std::cerr << "batch_load: JSON is not an object" << std::endl;
            return;
        }
        // 从顶层对象中取出对应 type 的一组映射（函数名 -> DLL 路径）
        auto type_it = json.FindMember(type.c_str());
        if (type_it == json.MemberEnd() || !type_it->value.IsObject()) {
            std::cerr << "batch_load: type \"" << type << "\" not found or not an object" << std::endl;
            return;
        }
        for (const auto& entry : type_it->value.GetObject()) {
            if (!entry.value.IsString()) {
                std::cerr << "batch_load: path for \"" 
                    << entry.name.GetString()
                    << "\" is not a string" << std::endl;
                continue;
            }
            load(entry.value.GetString(), entry.name.GetString());
        }
    }
}