#pragma once

#ifndef ABSTRACTFIGURE_HPP
#define ABSTRACTFIGURE_HPP

#include "Types.hpp"
class PaintCanvas;

class AbstractFigure {
public:

	explicit AbstractFigure()noexcept;

	virtual std::string_view GetPluginName()const noexcept = 0;


	//Начало рисования. Пользователь кликнул первый раз по канве
	virtual void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info) = 0;

	//Дальнейшие тыки по канве. Возвращаемое значени - дорисована ли фигура
	virtual bool Draw(PaintCanvas& canvas, const UIInfo& ui_info) = 0;
	virtual void EndDrawing() = 0;
	
	virtual ~AbstractFigure()noexcept = default;

};

#endif //ABSTRACTFIGURE_HPP