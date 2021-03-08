#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdint>
using std::uint8_t;

class Pixel final {
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

};


using Color = Pixel;

#endif //PIXEL_HPP