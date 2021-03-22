#include "Types.hpp"

Coordinats::Coordinats(const uint64_t x, const uint64_t y)noexcept :
	x_{ x }, y_{ y }{}

Coordinats::Coordinats(const Coordinats& coordinats)noexcept :
	x_{ coordinats.x_ }, y_{ coordinats.y_ }{}

Coordinats::Coordinats(Coordinats&& coordinats)noexcept:
	x_{ coordinats.x_ }, y_{ coordinats.y_ }{

	coordinats.x_ = 0;
	coordinats.y_ = 0;

}

Coordinats::Coordinats()noexcept :
	Coordinats{ 0, 0 } {}

Coordinats& Coordinats::operator=(Coordinats&& move_coordinats)noexcept {

	if (this == &move_coordinats) return *this;

	x_ = 0;
	y_ = 0;
	std::swap(x_, move_coordinats.x_);
	std::swap(y_, move_coordinats.y_);

	return *this;

}

Coordinats& Coordinats::operator=(const Coordinats& copy_coordinats)noexcept {

	if (this == &copy_coordinats) return *this;

	x_ = copy_coordinats.x_;
	y_ = copy_coordinats.y_;

	return *this;
}

const uint64_t Coordinats::X()const noexcept { return x_; };
const uint64_t Coordinats::Y()const noexcept { return y_; };

Size::Size(const uint64_t width, const uint64_t height)noexcept :
	width_{ width }, height_{ height }{}

Size::Size(const Size& size)noexcept :
	width_{ size.width_ }, height_{ size.height_ }{}

Size::Size(Size&& size)noexcept :
	width_{ size.width_ }, height_{ size.height_ }{

	size.width_ = 0;
	size.height_ = 0;

}

Size::Size()noexcept :
	Size::Size{ 0, 0 } {}

Size& Size::operator=(Size&& move_size)noexcept {

	if (this == &move_size) return *this;

	width_ = 0;
	height_ = 0;

	std::swap(width_, move_size.width_);
	std::swap(height_, move_size.height_);

	return *this;

}

Size& Size::operator=(const Size& copy_size)noexcept {

	if (this == &copy_size) return *this;

	width_ = copy_size.width_;
	height_ = copy_size.height_;

	return *this;
}

const uint64_t Size::Height()const noexcept { return height_; };
const uint64_t Size::Width()const noexcept { return width_; };

FigureParametrs::FigureParametrs(const Coordinats & left_bottom, const Coordinats & right_top, const Color & color)noexcept :
	left_bottom_{ left_bottom }, right_top_{ right_top }, color_{ color } {}

FigureParametrs::FigureParametrs()noexcept :
	FigureParametrs{ Coordinats{ 0, 0 }, Coordinats{ 0, 0 }, Color{ 0, 0 ,0 } } {}

UIInfo::UIInfo()noexcept :
	mouse_click_{ 0, 0 },
	border_thickness_{ 1 },
	border_color_{ 0, 0, 0 },
	fill_color_{ 0, 0, 0 } {}

