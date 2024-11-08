#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"


//Reference - https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-acceleration-structure/grid.html
void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

    float x0 = aBegin.x;
    float y0 = aBegin.y;
    float x1 = aEnd.x;
    float y1 = aEnd.y;	

	// Calculate differences in x and y
    float dx = x1 - x0;
    float dy = y1 - y0;


	// Determine the number of steps required, based on the maximum of dx or dy
    int steps = static_cast<int>(std::max(std::abs(dx), std::abs(dy)));

	// If there's nothing to draw (the start and end points are the same)
    if (steps == 0) {
        if (x0 >= 0 && x0 < aSurface.get_width() && y0 >= 0 && y0 < aSurface.get_height()) {
            aSurface.set_pixel_srgb(static_cast<int>(x0), static_cast<int>(y0), aColor); // Draw the single pixel
        }
        return;
    }

	// Calculate increments for x and y at each step
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

	// Start at the initial point
    float x = x0;
    float y = y0;

	// Draw each pixel along the line
    for (int i = 0; i <= steps; ++i) {
        // Convert to integer pixel coordinates and check if the point is within the surface bounds
        int xi = static_cast<int>(std::round(x));
        int yi = static_cast<int>(std::round(y));

        // Set the pixel if it's within the surface's bounds
        if (xi >= 0 && xi < aSurface.get_width() && yi >= 0 && yi < aSurface.get_height()) {
            aSurface.set_pixel_srgb(xi, yi, aColor);
        }

        // Increment the x and y values by the calculated step size
        x += xIncrement;
        y += yIncrement;
    }



	// //TODO: remove the following when you start your implementation
	// (void)aSurface; // Avoid warnings about unused arguments until the function
	// (void)aBegin;   // is properly implemented.
	// (void)aEnd;
	// (void)aColor;
}

void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}


//The resource I used for the formula - https://codeplea.com/triangular-interpolation
void draw_triangle_interp(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2) {
    // Compute the bounding box for the triangle
    float minX = std::min({aP0.x, aP1.x, aP2.x});
    float minY = std::min({aP0.y, aP1.y, aP2.y});
    float maxX = std::max({aP0.x, aP1.x, aP2.x});
    float maxY = std::max({aP0.y, aP1.y, aP2.y});

    // Clip the bounding box to the surface bounds
    int minXInt = std::max(0, static_cast<int>(std::floor(minX)));
    int minYInt = std::max(0, static_cast<int>(std::floor(minY)));
    int maxXInt = std::min(static_cast<int>(aSurface.get_width() - 1), static_cast<int>(std::ceil(maxX)));
    int maxYInt = std::min(static_cast<int>(aSurface.get_height() - 1), static_cast<int>(std::ceil(maxY)));

    // Precompute the denominator for barycentric coordinates
    float denom = (aP1.y - aP2.y) * (aP0.x - aP2.x) + (aP2.x - aP1.x) * (aP0.y - aP2.y);

    // Iterate through each pixel in the bounding box
    for (int y = minYInt; y <= maxYInt; ++y) {
        for (int x = minXInt; x <= maxXInt; ++x) {
            // Create a point for the current pixel
            Vec2f P = {(float)x, (float)y};

            // Calculate barycentric coordinates (weights)
            float w1 = ((aP1.y - aP2.y) * (P.x - aP2.x) + (aP2.x - aP1.x) * (P.y - aP2.y)) / denom;
            float w2 = ((aP2.y - aP0.y) * (P.x - aP2.x) + (aP0.x - aP2.x) * (P.y - aP2.y)) / denom;
            float w3 = 1.0f - w1 - w2;

            // If the point is inside the triangle, interpolate color
            if (w1 >= 0 && w2 >= 0 && w3 >= 0) {
                // Interpolate color based on barycentric coordinates
                float colorPr = w1 * aC0.r + w2 * aC1.r + w3 * aC2.r;
                float colorPg = w1 * aC0.g + w2 * aC1.g + w3 * aC2.g;
                float colorPb = w1 * aC0.b + w2 * aC1.b + w3 * aC2.b;

                // Convert to sRGB and set the pixel color
                uint8_t r = linear_to_srgb(colorPr);
                uint8_t g = linear_to_srgb(colorPg);
                uint8_t b = linear_to_srgb(colorPb);

                aSurface.set_pixel_srgb(x, y, {r, g, b});
            }
        }
    }
}



void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
