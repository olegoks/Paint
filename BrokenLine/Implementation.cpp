#include "Interface.hpp"


std::string_view BrokenLine::GetPluginName() const noexcept{

	return plugin_name;
}

void BrokenLine::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info){

	start_ = ui_info.mouse_click_;
	color_ = ui_info.border_color_;
	line_thickness_ = ui_info.border_thickness_;

}

bool BrokenLine::Draw(PaintCanvas& canvas, const UIInfo& ui_info){
	
	end_ = ui_info.mouse_click_;

	canvas.Line(start_.X(), start_.Y(), end_.X(), end_.Y(), line_thickness_, color_);

	start_ = end_;

	return true;

}

void BrokenLine::EndDrawing(){

}
