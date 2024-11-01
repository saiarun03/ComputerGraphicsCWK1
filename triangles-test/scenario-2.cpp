#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "Large Triangle", "[coverage]" )
{
    // Creating a surface of reasonable size
    Surface surface( 320, 240 );
    surface.clear();

    // Drawing a large triangle that spans most of the surface
    draw_triangle_interp( surface,
        { 10.f, 10.f }, { 310.f, 10.f }, { 160.f, 230.f },
        { 1.0f, 0.0f, 0.0f },   // Red
        { 0.0f, 1.0f, 0.0f },   // Green
        { 0.0f, 0.0f, 1.0f }    // Blue
    );

    // Check that the surface contains a significant red component
    auto const col = find_most_red_pixel( surface );
    REQUIRE( col.r >= 127 );  // Expect a strong red component
    REQUIRE( col.g <= 127 );  // Ensure green is not dominant
    REQUIRE( col.b <= 127 );  // Ensure blue is not dominant
}

TEST_CASE( "Edge-Aligned Triangle", "[alignment]" )
{
    // Creating a surface of reasonable size
    Surface surface( 320, 240 );
    surface.clear();

    // Drawing a triangle along the edge of the surface
    draw_triangle_interp( surface,
        { 0.f, 0.f }, { 320.f, 0.f }, { 160.f, 240.f },
        { 0.0f, 0.5f, 0.5f },   // Cyan-like
        { 0.5f, 0.0f, 0.5f },   // Magenta-like
        { 0.5f, 0.5f, 0.0f }    // Yellow-like
    );

    // Check if the triangle's colors are correctly rendered along the edges
    auto const col = find_least_red_nonzero_pixel( surface );
    REQUIRE( col.r <= 127 );  // Ensure red is not dominant
    REQUIRE( col.g >= 64 );   // Expect some green component
    REQUIRE( col.b >= 64 );   // Expect some blue component
}
