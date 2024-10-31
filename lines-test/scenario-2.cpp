#include <catch2/catch_amalgamated.hpp>
#include "helpers.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE("Lines with one point inside and one point outside the surface", "[clip]") {
    Surface surface(200, 200);
    surface.clear();

    SECTION("Horizontal line extending off right edge") {
        draw_line_solid(surface, {10.f, 100.f}, {300.f, 100.f}, {255, 255, 255});
        auto pixel_count = max_row_pixel_count(surface);

        // Ensure that the line is clipped at the right boundary
        REQUIRE(pixel_count > 0);
        REQUIRE(pixel_count <= surface.get_width());
    }

    SECTION("Horizontal line extending off left edge") {
        surface.clear();
        draw_line_solid(surface, {-100.f, 50.f}, {150.f, 50.f}, {255, 255, 255});
        auto pixel_count = max_row_pixel_count(surface);

        REQUIRE(pixel_count > 0);
        REQUIRE(pixel_count <= surface.get_width());
    }

    SECTION("Vertical line extending off top edge") {
        surface.clear();
        draw_line_solid(surface, {50.f, -50.f}, {50.f, 150.f}, {255, 255, 255});
        auto pixel_count = max_col_pixel_count(surface);

        REQUIRE(pixel_count > 0);
        REQUIRE(pixel_count <= surface.get_height());
    }

    SECTION("Vertical line extending off bottom edge") {
        surface.clear();
        draw_line_solid(surface, {100.f, 50.f}, {100.f, 250.f}, {255, 255, 255});
        auto pixel_count = max_col_pixel_count(surface);

        REQUIRE(pixel_count > 0);
        REQUIRE(pixel_count <= surface.get_height());
    }

    SECTION("Diagonal line extending off top-left corner") {
        surface.clear();
        draw_line_solid(surface, {-50.f, -50.f}, {150.f, 150.f}, {255, 255, 255});
        auto counts = count_pixel_neighbours(surface);

        REQUIRE(counts[0] == 0);      // No isolated pixels
        REQUIRE(counts[1] == 2);       // Two end pixels with one neighbor
        REQUIRE(counts[2] > 0);        // Line should have connected pixels with two neighbors
        REQUIRE(counts[3] == 0);       // No pixels with three neighbors or more
    }

    SECTION("Diagonal line extending off bottom-right corner") {
        surface.clear();
        draw_line_solid(surface, {50.f, 50.f}, {300.f, 300.f}, {255, 255, 255});
        auto counts = count_pixel_neighbours(surface);

        REQUIRE(counts[0] == 0);      // No isolated pixels
        REQUIRE(counts[1] == 2);       // Two end pixels with one neighbor
        REQUIRE(counts[2] > 0);        // Line should have connected pixels with two neighbors
        REQUIRE(counts[3] == 0);       // No pixels with three neighbors or more
    }

    SECTION("Diagonal line extending off top-right corner") {
        surface.clear();
        draw_line_solid(surface, {150.f, -50.f}, {-50.f, 250.f}, {255, 255, 255});
        auto counts = count_pixel_neighbours(surface);

        REQUIRE(counts[0] == 0);      // No isolated pixels
        REQUIRE(counts[1] == 2);       // Two end pixels with one neighbor
        REQUIRE(counts[2] > 0);        // Line should have connected pixels with two neighbors
        REQUIRE(counts[3] == 0);       // No pixels with three neighbors or more
    }
}
