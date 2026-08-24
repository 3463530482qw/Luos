namespace Gnik_luos {
    Scene& Scene::remove(std::string_view function_name) {
        if (current_scene == function_name.data()) {
            return *this;
        }

        data.erase(function_name.data());

        auto it = private_data.find(function_name.data());
        if (it != private_data.end()) {
            FreeLibrary(it->second);
            private_data.erase(it);
        }

        return *this;
    }
}