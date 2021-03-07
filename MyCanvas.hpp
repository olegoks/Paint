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
	FiguresBuffer drawn_figures_;
	ProcessCanvasAction process_action_;

public:

	explicit MyCanvas(const HWND parent_hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height)noexcept :
		Canvas{ x, y, width, height },
		drawn_figures_{} {
		
		Canvas::Size(width, height);
		Canvas::Position(x, y);
		Canvas::Create(parent_hWnd);
		Canvas::Show(SW_SHOW);

	}

	void InitProcessActionFunction(ProcessCanvasAction process_action) {

		process_action_ = process_action;

		Canvas::InitCanvasProc([this](Message& message)noexcept->bool {
			
			return process_action_(*this, message);

			});

	}

	void DrawFigure(AbstractFigure* figure) {

		for (auto& command : figure->GetCommands())
			command->Execute(*dynamic_cast<Canvas*>(this));

		drawn_figures_.push_back(figure);

	}

	void Flush() { 
		
		Canvas::Flush();
	
	}

	~MyCanvas()noexcept {



	}

};

#endif //MYCANVAS_HPP