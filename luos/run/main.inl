namespace Gnik_luos {
    Run::Run() {
        private_start = [this]() {
            router();
        };
    }
}