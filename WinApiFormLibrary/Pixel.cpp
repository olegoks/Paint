#include <Pixel.hpp>

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b)noexcept:
	rgba_{ 0 } {

	rgba_.r = r;
	rgba_.g = g;
	rgba_.b = b;

}

Pixel::Pixel()noexcept:
	Pixel{ 0, 0, 0 } {

}

Pixel::Pixel(Pixel&& move_pixel)noexcept:
	rgba_{ 0 } {

	std::swap(rgba_, move_pixel.rgba_);

}

Pixel& Pixel::operator=(Pixel&& move_pixel)noexcept{

	if (this == &move_pixel)return *this;

	std::swap(rgba_, move_pixel.rgba_);
	
	return *this;
}
