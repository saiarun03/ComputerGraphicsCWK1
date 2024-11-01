#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "Tiny Triangle", "[precision]" )
{
    // Creating a surface of reasonable size
    Surface surface( 320, 240 );
    surface.clear();

    // Making the triangle slightly larger
    draw_triangle_interp( surface,
        { 100.f, 100.f }, { 105.f, 100.f }, { 100.f, 105.f },
        { 1.0f, 0.0f, 0.0f },   // Red
        { 0.0f, 1.0f, 0.0f },   // Green
        { 0.0f, 0.0f, 1.0f }    // Blue
    );

    // Check if the triangle rendered correctly, and we can see the expected colors
    auto const col = find_most_red_pixel( surface );
    REQUIRE( col.r >= 127 );  // Check for some red intensity
    REQUIRE( col.g <= 127 );  // Ensure green is not dominant
    REQUIRE( col.b <= 127 );  // Ensure blue is not dominant
}
