#pragma once

#ifndef ABSTRACTFIGURE_HPP
#define ABSTRACTFIGURE_HPP

#include "Types.hpp"
class PaintCanvas;

class AbstractFigure {
public:

	explicit AbstractFigure()noexcept;

	virtual std::string_view GetPluginName()const noexcept = 0;

	virtual void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info) = 0;
	virtual void Draw(PaintCanvas& canvas, const UIInfo& ui_info) = 0;
	virtual void EndDrawing() = 0;
	
	virtual ~AbstractFigure()noexcept = default;

};

#endif //ABSTRACTFIGURE_HPP