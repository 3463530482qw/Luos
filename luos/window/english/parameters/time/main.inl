namespace Gnik_luos {
    Window_time::Window_time() {
        timeBeginPeriod(1);
        private_update.push_back([this]() { router(); });
    }
    Window_time::~Window_time() {
        timeEndPeriod(1);
    }
}