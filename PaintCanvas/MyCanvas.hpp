#pragma once

#ifndef MYCANVAS_HPP
#define MYCANVAS_HPP

#include "Canvas.hpp"
#include "AbstractFigure.hpp"
#include <functional>
extern class MyCanvas;
using ProcessCanvasAction = std::function<bool(MyCanvas& canvas, Message& message)>;

class MyCanvas : private Canvas{
private:

	using FiguresBuffer = std::vector<AbstractFigure*>;
	FiguresBuffer figures_;
	ProcessCanvasAction process_action_;
	FiguresBuffer::iterator pointer_;
	Color fill_color_;

private:

	void ClearNotDrawnFigures()noexcept {

		if (pointer_ == figures_.end() - 1)return;

		std::for_each(pointer_ + 1, figures_.end(), [](AbstractFigure* figure_ptr)noexcept->void{
			
			delete figure_ptr;
			
			});

		pointer_ = figures_.erase(++pointer_, figures_.end());

	}



public:

	explicit MyCanvas(const HWND parent_hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height)noexcept :
		Canvas{ },
		figures_{ nullptr },
		pointer_{ figures_.begin() },
		fill_color_{ Color{ 255, 255, 255 } } {

		Canvas::ChangeSize(width, height);
		Canvas::ChangePosition(x, y);
		Canvas::Create(parent_hWnd);
		Canvas::Show(SW_SHOW);

	}

	void DrawFigure(AbstractFigure* figure) {

		figure->Draw(*dynamic_cast<Canvas*>(this));
		ClearNotDrawnFigures();
		figures_.push_back(figure);
		pointer_ = figures_.end() - 1;
		Canvas::Flush();

	}

	const uint64_t GetWidth()const noexcept { return Canvas::GetWidth(); }
	const uint64_t GetHeight()const noexcept { return Canvas::GetHeight(); }

	void ReturnBack() {

		//&&
		if (*pointer_ == nullptr)return;

		Canvas::Fill(fill_color_);

		for (auto it = figures_.begin() + 1; it != pointer_; ++it)
			(*it)->Draw(*dynamic_cast<Canvas*>(this));

		--pointer_;

		Canvas::Flush();

	}

	void ReturnForward() {

		if (pointer_ == figures_.end() - 1)return;
		(*(++pointer_))->Draw(*dynamic_cast<Canvas*>(this));
		Canvas::Flush();

	}

	void Flush() { 
		
		Canvas::Flush();
	
	}

	~MyCanvas()noexcept {



	}

	void InitProcessActionFunction(ProcessCanvasAction process_action) {

		process_action_ = process_action;

		Canvas::SetCanvasProc([this](Message& message)noexcept->bool {

			return process_action_(*this, message);

			});

	}


};

#endif //MYCANVAS_HPP