namespace Gnik_luos {
    Line& Line::seal(bool value) {
        use_seal = value;
        dirty = true;
        return *this;
    }
}
