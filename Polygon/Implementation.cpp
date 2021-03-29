#include "Interface.hpp"
#include "Types.hpp"

std::string_view PolygonFigure::GetPluginName() const noexcept{

	return plugin_name;
}

void PolygonFigure::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info) {

	second_ = Coordinats{};
	third_ = Coordinats{};
	border_thickness_ = ui_info.border_thickness_;

	first_ = ui_info.mouse_click_;

}

bool PolygonFigure::Draw(PaintCanvas& canvas, const UIInfo& ui_info){

	if (!second_.X() && !second_.Y()) {
		second_ = ui_info.mouse_click_;
		canvas.Line(first_.X(), first_.Y(), second_.X(), second_.Y(), border_thickness_, border_color_);
	} else if (!third_.X() && !third_.Y()){

		third_ = ui_info.mouse_click_;

		border_color_ = ui_info.border_color_;
		border_thickness_ = ui_info.border_thickness_;
		fill_color_ = ui_info.fill_color_;

		canvas.Line(second_.X(), second_.Y(), third_.X(), third_.Y(), border_thickness_, border_color_);
		canvas.Line(third_.X(), third_.Y(), first_.X(), first_.Y(), border_thickness_, border_color_);
	
	} else {

		first_ = second_;
		second_ = third_;
		third_ = ui_info.mouse_click_;

		canvas.Line(second_.X(), second_.Y(), third_.X(), third_.Y(), border_thickness_, border_color_);
		canvas.Line(third_.X(), third_.Y(), first_.X(), first_.Y(), border_thickness_, border_color_);

	}

	return true;

}

void PolygonFigure::EndDrawing() {

}
