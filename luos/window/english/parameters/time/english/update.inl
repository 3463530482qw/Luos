namespace Gnik_luos {
    void Window_time::update() {
        for(auto& fun : private_update) {
            fun();
        }      
    }
}