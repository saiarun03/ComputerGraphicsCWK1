#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

// Scenario 3: Testing lines with both endpoints outside of the surface.
// This scenario checks if the clipping correctly discards lines completely
// outside the drawable surface, ensuring no pixels are drawn.
TEST_CASE("Both points offscreen", "[clip][!mayfail]") {
    Surface surface(100, 100);
    surface.clear();  // Clear surface to ensure no previous pixels affect the test results.

    // Test case: Line entirely to the left of the drawable surface
    SECTION("Left of screen") {
        draw_line_solid(surface,
                        { -20.f, 10.f },  // Start point (outside, left)
                        { -10.f, 30.f },  // End point (outside, left)
                        { 255, 255, 255 }); // Color (white)

        // Verify that no pixels are drawn, as the line is fully offscreen.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Line entirely to the right of the drawable surface
    SECTION("Right of screen") {
        draw_line_solid(surface,
                        { 120.f, 10.f },   // Start point (outside, right)
                        { 130.f, 40.f },   // End point (outside, right)
                        { 255, 255, 255 });

        // No pixels should be drawn for lines fully offscreen.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Line entirely above the drawable surface
    SECTION("Above screen") {
        draw_line_solid(surface,
                        { 10.f, -20.f },   // Start point (outside, above)
                        { 20.f, -30.f },   // End point (outside, above)
                        { 255, 255, 255 });

        // Ensure the line does not appear on the surface.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Line entirely below the drawable surface
    SECTION("Below screen") {
        draw_line_solid(surface,
                        { 10.f, 120.f },   // Start point (outside, below)
                        { 20.f, 130.f },   // End point (outside, below)
                        { 255, 255, 255 });

        // Assert that no pixels are drawn for fully offscreen lines.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Diagonal line offscreen from top-left to bottom-right
    SECTION("Diagonal offscreen (top-left to bottom-right)") {
        draw_line_solid(surface,
                        { -20.f, -20.f },  // Start point (outside, top-left)
                        { -10.f, -10.f },  // End point (outside, top-left)
                        { 255, 255, 255 });

        // The line should not appear on the surface.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Diagonal line offscreen from bottom-left to top-right
    SECTION("Diagonal offscreen (bottom-left to top-right)") {
        draw_line_solid(surface,
                        { -20.f, 120.f },  // Start point (outside, bottom-left)
                        { -10.f, 130.f },  // End point (outside, bottom-left)
                        { 255, 255, 255 });

        // Verify the line is clipped completely, with no pixels drawn.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Diagonal line offscreen from top-right to bottom-left
    SECTION("Diagonal offscreen (top-right to bottom-left)") {
        draw_line_solid(surface,
                        { 120.f, -20.f },  // Start point (outside, top-right)
                        { 130.f, -10.f },  // End point (outside, top-right)
                        { 255, 255, 255 });

        // Ensure the line does not draw any pixels on the surface.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }

    // Test case: Diagonal line offscreen from bottom-right to top-left
    SECTION("Diagonal offscreen (bottom-right to top-left)") {
        draw_line_solid(surface,
                        { 120.f, 120.f },  // Start point (outside, bottom-right)
                        { 130.f, 130.f },  // End point (outside, bottom-right)
                        { 255, 255, 255 });

        // Confirm no pixels are drawn on the surface.
        auto const pixels = max_row_pixel_count(surface);
        REQUIRE(0 == pixels);
    }
}
