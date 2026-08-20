namespace Gnik_luos {
    Scene& Scene::remove(const std::string& function_name) {
        if (current_scene == function_name) {
            return *this;
        }

        data.erase(function_name);

        auto it = private_data.find(function_name);
        if (it != private_data.end()) {
            FreeLibrary(it->second);
            private_data.erase(it);
        }

        return *this;
    }
}