/**
 * Texture.h
 * Defines the Texture structure.
 */
#pragma once

// Represents a texture in a spritesheet
struct Texture {
    // Pixels from the left edge of the sheet
    int left;

    // Pixels from the top edge of the sheet
    int top;

    // Width
    int width;

    // Height
    int height;

    //Constructor which sets the left, top, width and height values
    Texture(int l, int t, int w, int h)
        :left(l), top(t), width(w), height(h) {
    }

};