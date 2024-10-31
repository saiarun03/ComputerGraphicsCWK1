#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

// Scenario 4: Testing multiple connected lines with no gaps.
// This scenario checks if consecutive lines drawn from point-to-point
// connect seamlessly, regardless of line length.

TEST_CASE("Connected lines with no gaps", "[connect][!mayfail]") {
    Surface surface(200, 200);
    surface.clear(); // Clear the surface to start with a blank canvas.

    // SECTION: Two consecutive lines, connecting at point p1.
    SECTION("Two connected lines") {
        draw_line_solid(surface,
                        { 10.f, 10.f },    // Start of the first line (p0)
                        { 50.f, 50.f },    // End of the first line and start of the second (p1)
                        { 255, 255, 255 }); // Color (white)

        draw_line_solid(surface,
                        { 50.f, 50.f },    // Start of the second line (same as end of first)
                        { 90.f, 90.f },    // End of the second line (p2)
                        { 255, 255, 255 });

        // Count pixels and ensure connectivity.
        auto const counts = count_pixel_neighbours(surface);
        
        REQUIRE(2 == counts[1]);      // Two endpoints should have one neighbour (p0 and p2).
        REQUIRE(counts[2] > 0);       // Internal pixels should have two neighbours.
        REQUIRE(0 == counts[0]);      // No isolated pixels.

        // Ensure there are no pixels with more than two neighbours, confirming no overlap.
        for (std::size_t i = 3; i < counts.size(); ++i) {
            REQUIRE(0 == counts[i]);
        }
    }

    // SECTION: Testing a longer sequence of connected lines with small segments.
    SECTION("Multiple connected lines with short segments") {
        draw_line_solid(surface, { 20.f, 20.f }, { 22.f, 22.f }, { 255, 255, 255 });
        draw_line_solid(surface, { 22.f, 22.f }, { 24.f, 24.f }, { 255, 255, 255 });
        draw_line_solid(surface, { 24.f, 24.f }, { 26.f, 26.f }, { 255, 255, 255 });
        draw_line_solid(surface, { 26.f, 26.f }, { 28.f, 28.f }, { 255, 255, 255 });

        // Verify connectivity for short lines.
        auto const counts = count_pixel_neighbours(surface);

        REQUIRE(2 == counts[1]);      // Two endpoints should have one neighbour.
        REQUIRE(counts[2] > 0);       // Internal pixels should have two neighbours.
        REQUIRE(0 == counts[0]);      // No isolated pixels.

        for (std::size_t i = 3; i < counts.size(); ++i) {
            REQUIRE(0 == counts[i]);
        }
    }

    // SECTION: Test case with alternating long and short line segments.
    SECTION("Mixed length connected lines") {
        draw_line_solid(surface, { 30.f, 30.f }, { 60.f, 60.f }, { 255, 255, 255 });
        draw_line_solid(surface, { 60.f, 60.f }, { 62.f, 62.f }, { 255, 255, 255 });
        draw_line_solid(surface, { 62.f, 62.f }, { 90.f, 90.f }, { 255, 255, 255 });

        // Check connectivity across mixed line lengths.
        auto const counts = count_pixel_neighbours(surface);

        REQUIRE(2 == counts[1]);      // Two endpoints should have one neighbour.
        REQUIRE(counts[2] > 0);       // Internal pixels should have two neighbours.
        REQUIRE(0 == counts[0]);      // No isolated pixels.

        for (std::size_t i = 3; i < counts.size(); ++i) {
            REQUIRE(0 == counts[i]);
        }
    }
}
