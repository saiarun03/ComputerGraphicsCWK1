#include <catch2/catch_amalgamated.hpp>
#include "helpers.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE("Identical lines from p0 to p1 and p1 to p0", "[line-symmetry]") {
    Surface surface(200, 200);

    SECTION("Horizontal line symmetry") {
        surface.clear();
        draw_line_solid(surface, {10.f, 50.f}, {100.f, 50.f}, {255, 255, 255});
        auto pixels_forward = max_row_pixel_count(surface);

        surface.clear();
        draw_line_solid(surface, {100.f, 50.f}, {10.f, 50.f}, {255, 255, 255});
        auto pixels_reverse = max_row_pixel_count(surface);

        REQUIRE(pixels_forward == pixels_reverse);
    }

    SECTION("Vertical line symmetry") {
        surface.clear();
        draw_line_solid(surface, {50.f, 10.f}, {50.f, 100.f}, {255, 255, 255});
        auto pixels_forward = max_col_pixel_count(surface);

        surface.clear();
        draw_line_solid(surface, {50.f, 100.f}, {50.f, 10.f}, {255, 255, 255});
        auto pixels_reverse = max_col_pixel_count(surface);

        REQUIRE(pixels_forward == pixels_reverse);
    }

    SECTION("Diagonal line symmetry (45 degrees)") {
        surface.clear();
        draw_line_solid(surface, {10.f, 10.f}, {100.f, 100.f}, {255, 255, 255});
        auto forward_counts = count_pixel_neighbours(surface);

        surface.clear();
        draw_line_solid(surface, {100.f, 100.f}, {10.f, 10.f}, {255, 255, 255});
        auto reverse_counts = count_pixel_neighbours(surface);

        REQUIRE(forward_counts == reverse_counts);
    }

    SECTION("Steep diagonal line symmetry") {
        surface.clear();
        draw_line_solid(surface, {10.f, 10.f}, {50.f, 100.f}, {255, 255, 255});
        auto forward_counts = count_pixel_neighbours(surface);

        surface.clear();
        draw_line_solid(surface, {50.f, 100.f}, {10.f, 10.f}, {255, 255, 255});
        auto reverse_counts = count_pixel_neighbours(surface);

        REQUIRE(forward_counts == reverse_counts);
    }

    SECTION("Shallow diagonal line symmetry") {
        surface.clear();
        draw_line_solid(surface, {10.f, 50.f}, {100.f, 60.f}, {255, 255, 255});
        auto forward_counts = count_pixel_neighbours(surface);

        surface.clear();
        draw_line_solid(surface, {100.f, 60.f}, {10.f, 50.f}, {255, 255, 255});
        auto reverse_counts = count_pixel_neighbours(surface);

        REQUIRE(forward_counts == reverse_counts);
    }

    SECTION("Slanted line symmetry") {
        surface.clear();
        draw_line_solid(surface, {20.f, 30.f}, {80.f, 120.f}, {255, 255, 255});
        auto forward_counts = count_pixel_neighbours(surface);

        surface.clear();
        draw_line_solid(surface, {80.f, 120.f}, {20.f, 30.f}, {255, 255, 255});
        auto reverse_counts = count_pixel_neighbours(surface);

        REQUIRE(forward_counts == reverse_counts);
    }
}
