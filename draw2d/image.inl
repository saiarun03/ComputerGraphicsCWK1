inline
ColorU8_sRGB_Alpha ImageRGBA::get_pixel( Index aX, Index aY ) const
{
	assert( aX < mWidth && aY < mHeight ); // Leave this at the top of the function.

	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

    // Get the linear index of the pixel
    Index linearIndex = get_linear_index(aX, aY);

    // Retrieve the color channels (RGBA) from the image data using the linear index
    std::uint8_t r = mData[linearIndex + 0]; // Red channel
    std::uint8_t g = mData[linearIndex + 1]; // Green channel
    std::uint8_t b = mData[linearIndex + 2]; // Blue channel
    std::uint8_t a = mData[linearIndex + 3]; // Alpha channel

    // Return the pixel color with RGB and alpha components
    return { r, g, b, a };


	// (void)aX;  // Avoid warnings about unused arguments until the function is
	// (void)aY;  // properly implemented.
	// return { 0, 0, 0, 0 }; //TODO: remove this line when you implement this
}

inline
auto ImageRGBA::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto ImageRGBA::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
std::uint8_t* ImageRGBA::get_image_ptr() noexcept
{
	return mData;
}
inline
std::uint8_t const* ImageRGBA::get_image_ptr() const noexcept
{
	return mData;
}

inline
ImageRGBA::Index ImageRGBA::get_linear_index( Index aX, Index aY ) const noexcept
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	return (aY * mWidth + aX) * 4;

	// (void)aX;  // Avoid warnings about unused arguments until the function is
	// (void)aY;  // properly implemented.
	// return 0; //TODO: remove this line when you implement this function
}
