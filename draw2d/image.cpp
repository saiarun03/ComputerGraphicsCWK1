#include "image.hpp"

#include <memory>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <stb_image.h>

#include "surface.hpp"

#include "../support/error.hpp"

namespace
{
	struct STBImageRGBA_ : public ImageRGBA
	{
		STBImageRGBA_( Index, Index, std::uint8_t* );
		virtual ~STBImageRGBA_();
	};
}

ImageRGBA::ImageRGBA()
	: mWidth( 0 )
	, mHeight( 0 )
	, mData( nullptr )
{}

ImageRGBA::~ImageRGBA() = default;


std::unique_ptr<ImageRGBA> load_image( char const* aPath )
{
	assert( aPath );

	stbi_set_flip_vertically_on_load( true );

	int w, h, channels;
	stbi_uc* ptr = stbi_load( aPath, &w, &h, &channels, 4 );
	if( !ptr )
		throw Error( "Unable to load image \"%s\"", aPath );

	return std::make_unique<STBImageRGBA_>(
		ImageRGBA::Index(w),
		ImageRGBA::Index(h),
		ptr
	);
}

void blit_masked( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

    // Get the image dimensions
    int imageWidth = aImage.get_width();
    int imageHeight = aImage.get_height();

    // Calculate the top-left corner of the blitting area, as aPosition is the center of the image
    int startX = static_cast<int>(aPosition.x - imageWidth / 2);
    int startY = static_cast<int>(aPosition.y - imageHeight / 2);

    // Get surface dimensions for bounds checking
    int surfaceWidth = aSurface.get_width();
    int surfaceHeight = aSurface.get_height();

    // Iterate over the pixels of the image
    for (int y = 0; y < imageHeight; ++y)
    {
        for (int x = 0; x < imageWidth; ++x)
        {
            // Get the source pixel from the image
            ColorU8_sRGB_Alpha pixelColor = aImage.get_pixel(x, y);

            // Discard the pixel if its alpha value is less than 128 (transparent)
            if (pixelColor.a < 128) continue;

            // Calculate the corresponding position on the surface
            int targetX = startX + x;
            int targetY = startY + y;

            // Check if the position is within the bounds of the surface
            if (targetX >= 0 && targetX < surfaceWidth &&
                targetY >= 0 && targetY < surfaceHeight)
            {
                // Set the pixel on the surface with the RGB values from the image, ignoring alpha
                aSurface.set_pixel_srgb(targetX, targetY, { pixelColor.r, pixelColor.g, pixelColor.b });
            }
        }
    }

	// (void)aSurface;  // Avoid warnings about unused arguments until the
	// (void)aImage;    // function is properly implemented.
	// (void)aPosition;
}

namespace
{
	STBImageRGBA_::STBImageRGBA_( Index aWidth, Index aHeight, std::uint8_t* aPtr )
	{
		mWidth = aWidth;
		mHeight = aHeight;
		mData = aPtr;
	}

	STBImageRGBA_::~STBImageRGBA_()
	{
		if( mData )
			stbi_image_free( mData );
	}
}
