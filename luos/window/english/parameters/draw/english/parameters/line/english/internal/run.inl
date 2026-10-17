namespace Gnik_luos {
    void Line::private_run_route() {
        for (auto& fun : private_route) {
            fun();
        }
    }
}
