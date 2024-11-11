#include "draw-ex.hpp"

#include <algorithm>

#include <cstring> // for std::memcpy()

#include "image.hpp"
#include "surface-ex.hpp"

// Used Bresenham's line algorithm from this resource: https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
void draw_ex_line_solid(SurfaceEx& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor) {
    // Convert floating-point coordinates to integer
    int x0 = static_cast<int>(aBegin.x);
    int y0 = static_cast<int>(aBegin.y);
    int x1 = static_cast<int>(aEnd.x);
    int y1 = static_cast<int>(aEnd.y);

    // Calculate differences and steps
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1; // Step direction for x
    int sy = (y0 < y1) ? 1 : -1; // Step direction for y

    int err = dx - dy; // Initial error

    while (true) {
        // Plot the current point
        aSurface.set_pixel_srgb(x0, y0, aColor);

        // Check if we've reached the end point
        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


void blit_ex_solid(SurfaceEx& aSurface, ImageRGBA const& aImage, Vec2f aPosition) {
    // Get the dimensions of the image (unsigned, as they represent sizes)
    unsigned int imageWidth = aImage.get_width();
    unsigned int imageHeight = aImage.get_height();

    // Calculate the top-left corner of the blitting area (signed integers, but make sure to compare with unsigned values later)
    int startX = static_cast<int>(aPosition.x - imageWidth / 2);
    int startY = static_cast<int>(aPosition.y - imageHeight / 2);

    // Get surface dimensions for bounds checking (unsigned, as they represent sizes)
    unsigned int surfaceWidth = aSurface.get_width();
    unsigned int surfaceHeight = aSurface.get_height();

    // Iterate over each pixel of the image
    for (unsigned int y = 0; y < imageHeight; ++y) {
        for (unsigned int x = 0; x < imageWidth; ++x) {
            // Calculate the target position on the surface (signed, but to compare with unsigned dimensions later)
            int targetX = startX + x;
            int targetY = startY + y;

            // Check if the target position is within the bounds of the surface
            // Ensure that comparisons between signed and unsigned are handled correctly
            if (targetX >= 0 && static_cast<unsigned int>(targetX) < surfaceWidth &&
                targetY >= 0 && static_cast<unsigned int>(targetY) < surfaceHeight) {
                // Get the pixel from the image
                ColorU8_sRGB_Alpha pixelColor = aImage.get_pixel(x, y);
                // Convert to ColorU8_sRGB
                ColorU8_sRGB rgbColor = { pixelColor.r, pixelColor.g, pixelColor.b }; // Assuming direct mapping
                // Set the pixel on the surface
                aSurface.set_pixel_srgb(targetX, targetY, rgbColor);
            }
        }
    }
}



#include <cstring> // For std::memcpy

void blit_ex_memcpy(SurfaceEx& aSurface, ImageRGBA const& aImage, Vec2f aPosition) {
    // Get the dimensions of the image (unsigned, as they represent sizes)
    unsigned int imageWidth = aImage.get_width();
    unsigned int imageHeight = aImage.get_height();

    // Calculate the top-left corner of the blitting area (signed integers, but make sure to compare with unsigned values later)
    int startX = static_cast<int>(aPosition.x - imageWidth / 2);
    int startY = static_cast<int>(aPosition.y - imageHeight / 2);

    // Get surface dimensions for bounds checking (unsigned, as they represent sizes)
    unsigned int surfaceWidth = aSurface.get_width();
    unsigned int surfaceHeight = aSurface.get_height();

    // Iterate over each row of the image
    for (unsigned int y = 0; y < imageHeight; ++y) {
        // Calculate the target position for the row on the surface (signed, but we'll cast to unsigned later)
        int targetY = startY + y;

        // Check if the target row is within the bounds of the surface
        if (targetY >= 0 && static_cast<unsigned int>(targetY) < surfaceHeight) {
            // Calculate the start position for this row on the surface
            int targetX = startX;

            // Check if the entire row fits within the bounds of the surface
            if (targetX >= 0 && static_cast<unsigned int>(targetX + imageWidth) <= surfaceWidth) {
                // Copy the entire row using std::memcpy, converting pixel colors
                for (unsigned int x = 0; x < imageWidth; ++x) {
                    ColorU8_sRGB_Alpha pixelColor = aImage.get_pixel(x, y);
                    ColorU8_sRGB rgbColor = { pixelColor.r, pixelColor.g, pixelColor.b }; // Assuming direct mapping

                    // Set pixel on surface
                    aSurface.set_pixel_srgb(targetX + x, targetY, rgbColor);
                }
            } else {
                // If the row doesn't fit entirely, copy pixel by pixel
                for (unsigned int x = 0; x < imageWidth; ++x) {
                    int targetX = startX + x;
                    if (targetX >= 0 && static_cast<unsigned int>(targetX) < surfaceWidth) {
                        // Copy the pixel using set_pixel_srgb
                        ColorU8_sRGB pixelColor = { aImage.get_pixel(x, y).r, aImage.get_pixel(x, y).g, aImage.get_pixel(x, y).b };
                        aSurface.set_pixel_srgb(targetX, targetY, pixelColor);
                    }
                }
            }
        }
    }
}



