namespace Gnik_luos {
    Scene& Scene::clear() {
        current_scene.clear();

        data.clear();

        for (auto& [name, handle] : private_data) {
            FreeLibrary(handle);
        }
        private_data.clear();

        return *this;
    }
}