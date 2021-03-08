#pragma once

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <any>
#include <Message.hpp>
#include <Pixel.hpp>
#include <FormTypes.hpp>



class EXPIMP Canvas {
private:

	std::any impl_;

public:

	explicit Canvas();
	Color GetDefaultBackgroundColor()const noexcept;
	void Line(int x, int y, int _x, int _y, const Color& color)noexcept;
	void Create(const HWND parent_hWnd);
	void SetCanvasProc(ProcessMessage process_canvas)noexcept;
	void SetPixel(int x, int y, const Pixel& pixel)noexcept;
	void ChangeSize(const int width, const int height);
	void ChangePosition(const int x, const int y);
	void Fill(const Color& color)noexcept(true);
	void Show(int nCmdShow);
	void Destroy();
	void Flush();

};

#endif //CANVAS_HPP