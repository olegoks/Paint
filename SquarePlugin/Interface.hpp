#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <memory>
#include <any>
#include <string>
#include <string_view>

#include "PaintCanvas.hpp"

class __declspec(dllexport) SquareFigure : public AbstractFigure {
private:

	
	Coordinats left_bottom_;
	Coordinats right_top_;
	Color border_color_;
	uint64_t border_thickness_;
	Color fill_color_;

public:

	static const inline std::string plugin_name = u8"Square";

	explicit SquareFigure()noexcept:
		AbstractFigure{ } { }

	std::string_view GetPluginName()const noexcept override;
	void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info)override;
	bool Draw(PaintCanvas& canvas, const UIInfo& ui_info)override;
	void EndDrawing()override;

};

extern "C"  __declspec(dllexport) AbstractFigure* GetPluginObject()noexcept {

	try {
	
		return reinterpret_cast<AbstractFigure*>(new SquareFigure{});
	
	} catch (const std::bad_alloc&) {

		return nullptr;

	}

}

extern "C" __declspec(dllexport) std::string_view  GetPluginName()noexcept {

	return SquareFigure::plugin_name;

}

//extern "C" __declspec(dllexport) Plugin::Type  GetPluginType()noexcept {
//
//	return Plugin::Type::FIGURE;
//
//}

#endif //INTERFACE_HPP