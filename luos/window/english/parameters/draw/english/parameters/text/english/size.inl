namespace Gnik_luos {
    Text& Text::size(float pixel_height, float line_spacing) {
        font_size = pixel_height;
        line_height = line_spacing;
        dirty = true;
        return *this;
    }

    Text& Text::spacing(float letter_gap) {
        letter_spacing = letter_gap;
        dirty = true;
        return *this;
    }
}
