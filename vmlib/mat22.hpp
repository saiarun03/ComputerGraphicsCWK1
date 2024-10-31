#ifndef MAT22_HPP_1F974C02_D0D1_4FBD_B5EE_A69C88112088
#define MAT22_HPP_1F974C02_D0D1_4FBD_B5EE_A69C88112088

#include <cmath>

#include "vec2.hpp"

/** Mat22f : 2x2 matrix with floats
 *
 * See comments for Vec2f for some discussion.
 *
 * The matrix is stored in row-major order.
 *
 * Example:
 *   Mat22f identity{ 
 *     1.f, 0.f,
 *     0.f, 1.f
 *   };
 */
struct Mat22f
{
	float _00, _01;
	float _10, _11;
};

// Common operators for Mat22f.
// Note that you will need to implement these yourself.

constexpr
Mat22f operator*( Mat22f const& aLeft, Mat22f const& aRight ) noexcept
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	return Mat22f{
        // First row
        aLeft._00 * aRight._00 + aLeft._01 * aRight._10,  // _00
        aLeft._00 * aRight._01 + aLeft._01 * aRight._11,  // _01
        // Second row
        aLeft._10 * aRight._00 + aLeft._11 * aRight._10,  // _10
        aLeft._10 * aRight._01 + aLeft._11 * aRight._11   // _11
    };
	

// 	//TODO: remove the following when you start your implementation
// 	(void)aLeft; // Avoid warnings about unused arguments until the function
// 	(void)aRight;  // is properly implemented.
// 	return Mat22f{ 1.f, 0.f, 0.f, 1.f };
}

constexpr
Vec2f operator*( Mat22f const& aLeft, Vec2f const& aRight ) noexcept
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

    return Vec2f{
        aLeft._00 * aRight.x + aLeft._01 * aRight.y,  // x component
        aLeft._10 * aRight.x + aLeft._11 * aRight.y   // y component
    };

	// //TODO: remove the following when you start your implementation
	// (void)aLeft; // Avoid warnings about unused arguments until the function
	// return aRight;
}

// Functions:

inline
Mat22f make_rotation_2d( float aAngle ) noexcept
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

    float cosTheta = std::cos(aAngle);
    float sinTheta = std::sin(aAngle);
    return Mat22f{
        cosTheta, -sinTheta,  // First row
        sinTheta, cosTheta    // Second row
    };


	//TODO: remove the following when you start your implementation
	// (void)aAngle; // Avoid warnings about unused arguments until the function
	//               // is properly implemented.
	// return Mat22f{ 1.f, 0.f, 0.f, 1.f };
}

#endif // MAT22_HPP_1F974C02_D0D1_4FBD_B5EE_A69C88112088
