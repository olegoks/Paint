#pragma once

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <any>
#include <Message.hpp>
#include <Pixel.hpp>
#include <FormTypes.hpp>

class EXPIMP::std::any;

class EXPIMP Canvas {
private:

	std::any impl_;

public:

	explicit Canvas();


	explicit Canvas(Canvas&& move_form)noexcept;
	explicit Canvas(const Canvas& copy_form)noexcept = delete;

	Canvas& operator=(Canvas&& move_form)noexcept;
	Canvas& operator=(const Canvas& copy_form)noexcept = delete;

	~Canvas()noexcept;

	const uint64_t GetWidth()const noexcept;
	const uint64_t GetHeight()const noexcept;
	const uint64_t GetX()const noexcept;
	const uint64_t GetY()const noexcept;
	Color GetDefaultBackgroundColor()const noexcept;
	void Line(uint64_t x, uint64_t y, uint64_t _x, uint64_t _y, const Color& color)noexcept;
	void Line(uint64_t x, uint64_t y, uint64_t _x, uint64_t _y, uint64_t line_thickness, const Color& color)noexcept;
	void Create(const HWND parent_hWnd);
	void SetCanvasProc(ProcessMessage process_canvas)noexcept;
	void SetPixel(const uint64_t x, const uint64_t y, uint64_t size, const Pixel& pixel)noexcept;
	void SetPixel(const uint64_t x, const uint64_t y, const Pixel& pixel)noexcept;
	void ChangeSize(const uint64_t width, const uint64_t height);
	void ChangePosition(const uint64_t x, const uint64_t y);
	void Fill(const Color& color)noexcept(true);
	void Show(int nCmdShow);
	void Destroy();
	void Flush();

};

#endif //CANVAS_HPP