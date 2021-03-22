#include "Interface.hpp"


std::string_view BrokenLine::GetPluginName() const noexcept{

	return plugin_name;
}

void BrokenLine::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info){

	start_ = ui_info.mouse_click_;

}




void BrokenLine::Draw(PaintCanvas& canvas, const UIInfo& ui_info){
	
	end_ = ui_info.mouse_click_;

	canvas.Line(start_.X(), start_.Y(), end_.X(), end_.Y(), border_color_);

	start_ = end_;

}

void BrokenLine::EndDrawing(){

}
