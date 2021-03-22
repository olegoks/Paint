#include "Interface.hpp"
#include "Types.hpp"

std::string_view SquareFigure::GetPluginName() const noexcept{

	return plugin_name;
}

void SquareFigure::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info) {

	left_bottom_ = ui_info.mouse_click_;

}

void SquareFigure::Draw(PaintCanvas& canvas, const UIInfo& ui_info){

	right_top_ = ui_info.mouse_click_;
	border_color_ = ui_info.border_color_;
	border_thickness_ = ui_info.border_thickness_;
	fill_color_ = ui_info.fill_color_;

	canvas.Line(left_bottom_.X(), left_bottom_.Y(), left_bottom_.X(), right_top_.Y(), border_color_);
	canvas.Line(left_bottom_.X(), right_top_.Y(), right_top_.X(), right_top_.Y(), border_color_);
	canvas.Line(right_top_.X(), right_top_.Y(), right_top_.X(), left_bottom_.Y(), border_color_);
	canvas.Line(right_top_.X(), left_bottom_.Y(), left_bottom_.X(), left_bottom_.Y(), border_color_);

}

void SquareFigure::EndDrawing() {

}
