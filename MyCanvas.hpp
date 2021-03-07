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
	uint64_t pointer_;
	Color fill_color_;

private:

	void ClearNotDrawnFigures()noexcept {

		FiguresBuffer::iterator first_unused_figure = figures_.begin() + pointer_;
		for (auto it = first_unused_figure; it != figures_.end(); ++it)
			delete *it;

		figures_.erase(first_unused_figure, figures_.end());

	}

public:

	explicit MyCanvas(const HWND parent_hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height)noexcept :
		Canvas{ x, y, width, height },
		figures_{},
		pointer_{ 0 },
		fill_color_{ Color{ 255, 255, 255 } } {

		Canvas::Size(width, height);
		Canvas::Position(x, y);
		Canvas::Create(parent_hWnd);
		Canvas::Show(SW_SHOW);

	}

	void DrawFigure(AbstractFigure* figure) {

		for (auto& command : figure->GetCommands())
			command->Execute(*dynamic_cast<Canvas*>(this));

		ClearNotDrawnFigures();

		figures_.push_back(figure);
		++pointer_;
	
	}

	void ReturnBack() {

		Canvas::Fill(fill_color_);

		FiguresBuffer::iterator last = figures_.begin() + --pointer_;

		for (auto it = figures_.begin(); it != last; ++it) {

			AbstractFigure* figure = *it;
			for (auto& command : figure->GetCommands())
				command->Execute(*dynamic_cast<Canvas*>(this));

		}

		Canvas::Flush();

	}

	void ReturnForward() {

		if (pointer_ < figures_.size()) {

			AbstractFigure* figure_to_draw = figures_[++pointer_];
			for (auto& command : figure_to_draw->GetCommands())
				command->Execute(*dynamic_cast<Canvas*>(this));

		}
	
	}

	void Flush() { 
		
		Canvas::Flush();
	
	}

	~MyCanvas()noexcept {



	}

	void InitProcessActionFunction(ProcessCanvasAction process_action) {

		process_action_ = process_action;

		Canvas::InitCanvasProc([this](Message& message)noexcept->bool {

			return process_action_(*this, message);

			});

	}


};

#endif //MYCANVAS_HPP