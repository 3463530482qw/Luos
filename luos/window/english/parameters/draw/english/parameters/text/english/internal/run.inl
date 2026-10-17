namespace Gnik_luos {
    void Text::private_run_route() {
        for (auto& fun : private_route) {
            fun();
        }
    }
}
