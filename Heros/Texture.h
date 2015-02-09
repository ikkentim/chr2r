#pragma once

struct Texture {
    int left;
    int top;
    int width;
    int height;

    Texture(int l, int t, int w, int h)
        :left(l), top(t), width(w), height(h) {
    }

};