#include "Interface.hpp"

#include <cmath>

std::string_view Elipse::GetPluginName() const noexcept{

	return plugin_name;
}

void Elipse::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info){

	start_ = ui_info.mouse_click_;
	border_color_ = ui_info.border_color_;
	border_thickness_ = ui_info.border_thickness_;

}

bool Elipse::Draw(PaintCanvas& canvas, const UIInfo& ui_info){
	
	end_ = ui_info.mouse_click_;

	float width = std::abs((int)end_.X() - (int)start_.X());

	if (width < 0.1f)
		return false;

	float height = std::abs((int)end_.Y() - (int)start_.Y());

	if (height < 0.1f)
		return false;
	
	const float a = width / 2.0f;
	const float b = height / 2.0f;
	
	//
	// (x - xc)^2	(y - yc)^ 2
	// --------- + ----------	= 1
	//	  a^2		  b^2
	//

	float center_x = 0;//start_.X() + a;
	float center_y = 0;//start_.Y() + b;
	
	if (start_.Y() < end_.Y()) {

		center_y = start_.Y() + b;

	} else {

		center_y = start_.Y() - b;

	}

	if (start_.X() < end_.X()) {

		center_x = start_.X() + a;

	} else {

		center_x = start_.X() - a;

	}

	Coordinats left{ (uint64_t)center_x, (uint64_t)center_y - (uint64_t)b };
	Coordinats right{ left };

	std::uint64_t start_y = start_.Y();
	std::uint64_t end_y = end_.Y();

	if (start_y > end_y) {

		std::swap(start_y, end_y);

	}

	for(uint64_t y = start_y; y < end_y; y += 5){

		const float value = abs(a) * sqrt((1 -  pow(static_cast<float>(y) - center_y, 2) / pow(b, 2)));
		
		const float first_x = value + center_x;
		const float second_x = -value + center_x;

		canvas.Line(left.X(), left.Y(), (uint64_t)first_x, y, border_thickness_, border_color_);
		canvas.Line(right.X(), right.Y(), (uint64_t)second_x, y, border_thickness_, border_color_);

		left = Coordinats{ (uint64_t)first_x, y };
		right = Coordinats{ (uint64_t)second_x, y };
		
	}

	canvas.Line(left.X(), left.Y(), (uint64_t)center_x, (uint64_t)center_y + (uint64_t)b, border_thickness_, border_color_);
	canvas.Line(right.X(), right.Y(), (uint64_t)center_x, (uint64_t)center_y + (uint64_t)b, border_thickness_, border_color_);

	return false;

}

void Elipse::EndDrawing(){

}
