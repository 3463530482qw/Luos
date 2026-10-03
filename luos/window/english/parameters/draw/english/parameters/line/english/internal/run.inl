namespace Gnik_luos {
    void Line::private_run_route() {
        for (size_t index = 0; index < route.count; index++) {
            (this->*(route.step[index]))();
        }
    }
}
