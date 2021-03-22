#pragma once

#ifndef TYPES_HPP
#define TYPES_HPP

#define COMPILING_DLL

#ifdef COMPILING_DLL
#define EXPIMP __declspec(dllexport)
#else
#define EXPIMP __declspec(dllimport)
#endif

#include <cstdint>
using std::uint64_t;

#include <memory>

class Coordinats final {
private:
	
	uint64_t x_;
	uint64_t y_;

public:

	explicit Coordinats(const uint64_t x, const uint64_t y)noexcept;
	explicit Coordinats(const Coordinats& coordinats)noexcept;
	explicit Coordinats(Coordinats&& coordinats)noexcept;
	explicit Coordinats()noexcept;
	Coordinats& operator=(Coordinats&& move_coordinats)noexcept;
	Coordinats& operator=(const Coordinats& copy_coordinats)noexcept;
	~Coordinats()noexcept = default;
	const uint64_t X()const noexcept;
	const uint64_t Y()const noexcept;

};

class Size final {

private:

	uint64_t width_;
	uint64_t height_;

public:

	explicit Size(const uint64_t width, const uint64_t height)noexcept;
	explicit Size(const Size& size)noexcept;
	explicit Size(Size&& size)noexcept;
	explicit Size()noexcept;
	Size& operator=(Size&& move_size)noexcept;
	Size& operator=(const Size& copy_size)noexcept;
	~Size()noexcept = default;
	const uint64_t Width()const noexcept;
	const uint64_t Height()const noexcept;

};
using Position = Coordinats;

#include <Pixel.hpp>

class FigureParametrs final {
public:

	Coordinats left_bottom_;
	Coordinats right_top_;
	Color color_;

	explicit FigureParametrs(const FigureParametrs& pos_size)noexcept = default;
	explicit FigureParametrs(FigureParametrs&& pos_size)noexcept = default;

	FigureParametrs& operator=(const FigureParametrs& pos_size) = default;
	FigureParametrs& operator=(FigureParametrs&& pos_size) = default;

	explicit FigureParametrs(const Coordinats& left_bottom, const Coordinats& right_top, const Color& color)noexcept;
	explicit FigureParametrs()noexcept;

	~FigureParametrs()noexcept = default;

};


class UIInfo final {
public:

	Coordinats mouse_click_;
	uint64_t border_thickness_;
	Color border_color_;
	Color fill_color_;
	
public:

	explicit UIInfo(const UIInfo& pos_size)noexcept = default;
	explicit UIInfo(UIInfo&& pos_size)noexcept = default;

	UIInfo& operator=(const UIInfo& pos_size) = default;
	UIInfo& operator=(UIInfo&& pos_size) = default;

	explicit UIInfo()noexcept;

	~UIInfo()noexcept = default;

};

#endif // TYPES_HPP