#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <memory>
#include <any>
#include <string>
#include <string_view>

#include "PaintCanvas.hpp"

class __declspec(dllexport) PolygonFigure : public AbstractFigure {
private:

	
	Coordinats first_;
	Coordinats second_;
	Coordinats third_;

	Color border_color_;
	uint64_t border_thickness_;
	Color fill_color_;

public:

	static const inline std::string plugin_name = u8"PolygonPlugin";

	explicit PolygonFigure()noexcept:
		AbstractFigure{ } { }

	std::string_view GetPluginName()const noexcept override;
	void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info)override;
	void Draw(PaintCanvas& canvas, const UIInfo& ui_info)override;
	void EndDrawing()override;

};

extern "C"  __declspec(dllexport) AbstractFigure* GetPluginObject()noexcept {

	try {
	
		return reinterpret_cast<AbstractFigure*>(new PolygonFigure{});
	
	} catch (const std::bad_alloc&) {

		return nullptr;

	}

}

extern "C" __declspec(dllexport) std::string_view  GetPluginName()noexcept {

	return PolygonFigure::plugin_name;

}

//extern "C" __declspec(dllexport) Plugin::Type  GetPluginType()noexcept {
//
//	return Plugin::Type::FIGURE;
//
//}

#endif //INTERFACE_HPP