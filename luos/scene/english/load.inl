namespace Gnik_luos {
    void Scene::load(std::string_view dll_path, std::string_view function_name) {
        auto it = private_data.find(function_name.data());
        if (it != private_data.end()) {
            FreeLibrary(it->second);
            private_data.erase(it);
        }
        auto handle = LoadLibraryA(dll_path.data()); //.c_str()
        if (!handle) {
            throw std::runtime_error(std::string("Scene::load => Failed to load DLL: ") + dll_path.data());
            return;
        }
        auto function = reinterpret_cast<void(*)()>(GetProcAddress(handle, function_name.data()));//.c_str()
        if (function) {
            data[function_name.data()] = function;
            private_data[function_name.data()] = handle;
        } else {
            throw std::runtime_error(std::string("Scene::load => Function ") + function_name.data() + std::string(" not found in ") + dll_path.data());
            FreeLibrary(handle);
            std::cerr << "Function " << function_name.data() << " not found in " << dll_path.data() << std::endl;
        }
    }

    void Scene::batch_load(const simdjson::dom::element& json, std::string_view type) {
        simdjson::dom::object top;
        if (json.get_object().get(top)) {
            std::cerr << "batch_load: JSON is not an object" << std::endl;
            return;
        }

        simdjson::dom::element group;
        if (top.at_key(type.data()).get(group) || !group.is_object()) {
            throw std::runtime_error(std::string("Scene::batch_load => batch_load: type \"") + type.data() + std::string("\" not found or not an object"));
            return;
        }
        for (auto field : group.get_object()) {
            std::string_view path;
            if (field.value.get_string().get(path)) {
                throw std::runtime_error(
                    std::string("Scene::batch_load => batch_load: path for \"") + 
                    field.key.data() + 
                    std::string("\" is not a string")
                );
                continue;
            }
            load(std::string(path), field.key);
        }
    }
}