#pragma once

#include <algorithm>
#include "Form.hpp"

using Color = Pixel;

EXPIMP class Canvas : protected Form{

private:

	static inline const Color kDefaultBackgroundColor = Color{ 255, 255, 255};

	Pixel* buffer_;
	int pixels_number_;

public:

	EXPIMP explicit Canvas( const int x, const int y, const int width, const int height)noexcept(false);
	EXPIMP void Position(const int x, const int y)noexcept(true);
	EXPIMP void Fill(const Color& color)noexcept(true);
	EXPIMP void Line(int x, int y, int _x, int _y, const Color& color)noexcept(true);
	EXPIMP void SetPixel(int x, int y, const Pixel& pixel)noexcept(true);
	EXPIMP void Flush()noexcept(false);
	EXPIMP void Create(const HWND parent_hWnd)noexcept(false);
	EXPIMP void Show(int nCmdShow)noexcept(false);
	EXPIMP void InitCanvasProc(FormProc process_canvas)noexcept(true);

};