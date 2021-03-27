#include "Interface.hpp"

#include <cmath>

std::string_view Elipse::GetPluginName() const noexcept{

	return plugin_name;
}

void Elipse::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info){

	start_ = ui_info.mouse_click_;
	border_color_ = ui_info.border_color_;
	border_thickness_ = 1;//ui_info.border_thickness_;

}

void Elipse::Draw(PaintCanvas& canvas, const UIInfo& ui_info){
	
	end_ = ui_info.mouse_click_;

	float width = (int)end_.X() - (int)start_.X();
	if (width < 0.1f)return;

	float height = (int)end_.Y() - (int)start_.Y();
	if (height < 0.1f)return;
	
	const float a = width / 2.0f;
	const float b = height / 2.0f;
	
	//
	// (x - xc)^2	(y - yc)^ 2
	// --------- + ----------	= 1
	//	  a^2		  b^2
	//

	const float center_x = start_.X() + a;
	const float center_y = start_.Y() + b;
	
	Coordinats left{ start_.X() + (uint64_t)width / 2, start_.Y() };
	Coordinats right{ left };

	for(uint64_t y = start_.Y(); y < end_.Y(); y += 5){

		const float value = abs(a) * sqrt((1 -  pow(static_cast<float>(y) - center_y, 2) / pow(b, 2)));
		
		const float first_x = value + center_x;
		const float second_x = -value + center_x;

		canvas.Line(left.X(), left.Y(), (uint64_t)first_x, y, border_thickness_, border_color_);
		canvas.Line(right.X(), right.Y(), (uint64_t)second_x, y, border_thickness_, border_color_);

		left = Coordinats{ (uint64_t)first_x, y };
		right = Coordinats{ (uint64_t)second_x, y };
		
	}

	canvas.Line(left.X(), left.Y(), start_.X() + (uint64_t)width / 2, end_.Y(), border_thickness_, border_color_);
	canvas.Line(right.X(), right.Y(), start_.X() + (uint64_t)width / 2, end_.Y(), border_thickness_, border_color_);


}

void Elipse::EndDrawing(){

}
