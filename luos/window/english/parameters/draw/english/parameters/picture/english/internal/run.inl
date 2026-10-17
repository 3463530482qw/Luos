namespace Gnik_luos {
    void Picture::private_run_route() {
        for (auto& fun : private_route) {
            fun();
        }
    }
}
