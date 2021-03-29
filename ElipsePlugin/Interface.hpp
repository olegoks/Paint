#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <memory>
#include <any>
#include <string>
#include <string_view>

#include "AbstractFigure.hpp"
#include "PaintCanvas.hpp"
#include "FormTypes.hpp"

class __declspec(dllexport) Elipse: public AbstractFigure {
private:

	Coordinats start_;
	Coordinats end_;
	Color border_color_;
	uint64_t border_thickness_;

public:

	static const inline std::string plugin_name = u8"Elipse";

	explicit Elipse()noexcept:
		AbstractFigure{ } { }

	std::string_view GetPluginName()const noexcept override;
	void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info)override;
	bool Draw(PaintCanvas& canvas, const UIInfo& ui_info)override;
	void EndDrawing()override;

};

extern "C"  __declspec(dllexport) AbstractFigure* GetPluginObject()noexcept {

	try {
	
		return reinterpret_cast<AbstractFigure*>(new Elipse);
	
	} catch (const std::bad_alloc&) {

		return nullptr;

	}

}

extern "C" __declspec(dllexport) std::string_view  GetPluginName()noexcept {

	return Elipse::plugin_name;

}



#endif //INTERFACE_HPP