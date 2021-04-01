#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <memory>
#include <any>
#include <string>
#include <string_view>

#include "PaintCanvas.hpp"

class __declspec(dllexport) TrapezoidFigure : public AbstractFigure {
private:

	Coordinats first_side_first_point_{};
	Coordinats first_side_second_point_{};

	Coordinats second_side_point_{};

	Color border_color_;
	std::uint64_t border_thickness_;

public:

	static const inline std::string plugin_name = u8"Trapezoid";

	explicit TrapezoidFigure()noexcept:
		AbstractFigure{ } { }

	std::string_view GetPluginName()const noexcept override;
	void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info)override;
	bool Draw(PaintCanvas& canvas, const UIInfo& ui_info)override;
	void EndDrawing()override;

};

extern "C"  __declspec(dllexport) AbstractFigure* GetPluginObject()noexcept {

	try {
	
		return reinterpret_cast<AbstractFigure*>(new TrapezoidFigure{});
	
	} catch (const std::bad_alloc&) {

		return nullptr;

	}

}

extern "C" __declspec(dllexport) std::string_view  GetPluginName()noexcept {

	return TrapezoidFigure::plugin_name;

}

//extern "C" __declspec(dllexport) Plugin::Type  GetPluginType()noexcept {
//
//	return Plugin::Type::FIGURE;
//
//}

#endif //INTERFACE_HPP