#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <FormTypes.hpp>

#include <cstdint>
using std::uint8_t;

class EXPIMP Pixel final {
public:

	union rgba {

		uint8_t bgra[4];

		struct {

			uint8_t b;
			uint8_t g;
			uint8_t r;
			uint8_t a;

		};

	};

	rgba rgba_ = { 0 };

	

	explicit Pixel(uint8_t r, uint8_t g, uint8_t b)noexcept;

	explicit Pixel()noexcept;

	explicit Pixel(const Pixel& copy_pixel) = default;
	explicit Pixel(Pixel&& move_pixel)noexcept;
	

	Pixel& operator=(Pixel&& move_pixel)noexcept;
	Pixel& operator=(const Pixel& copy_pixel) = default;

	~Pixel()noexcept = default;

};

using Color = Pixel;

#endif //PIXEL_HPP