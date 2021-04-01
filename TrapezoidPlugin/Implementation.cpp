#include "Interface.hpp"
#include "Types.hpp"

std::string_view TrapezoidFigure::GetPluginName() const noexcept{

	return plugin_name;
}

void TrapezoidFigure::StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info) {

	//Первое нажатие левой кнопкой мыши по канве
	first_side_second_point_ = Coordinats{};
	second_side_point_ = Coordinats{};

	border_color_ = ui_info.border_color_;
	border_thickness_ = ui_info.border_thickness_;

	first_side_first_point_ = ui_info.mouse_click_;

}
#include <sstream>

#undef max

bool TrapezoidFigure::Draw(PaintCanvas& canvas, const UIInfo& ui_info){

	//Нажали на канву левой кнопкой мыши второй раз
	if (!first_side_second_point_.X() && !first_side_second_point_.Y()) {

		first_side_second_point_ = ui_info.mouse_click_;

		canvas.Line(first_side_first_point_.X(), first_side_first_point_.Y(),
			first_side_second_point_.X(), first_side_second_point_.Y(), border_thickness_, border_color_);

		return true;
	//Третий
	}  else {

		const signed int side_width = (std::int64_t)first_side_first_point_.X() - (std::int64_t)first_side_second_point_.X();

		second_side_point_ = ui_info.mouse_click_;

		const std::uint64_t first_point_x = (std::uint64_t)((std::int64_t)second_side_point_.X() - side_width / 2u);
		const std::uint64_t second_point_x = (std::uint64_t)((std::int64_t)second_side_point_.X() + side_width / 2u);

		const Coordinats second_side_first_point{ (first_point_x > std::numeric_limits<std::uint64_t>::max() / 2u) ? (0u) : (first_point_x), first_side_first_point_.Y() };
		const Coordinats second_side_second_point{ (second_point_x > std::numeric_limits<std::uint64_t>::max() / 2u) ? (0u) : (second_point_x), first_side_second_point_.Y() };
		
		//drawing first parallel line 
		canvas.Line(first_side_first_point_.X(), first_side_first_point_.Y(), second_side_first_point.X(), second_side_first_point.Y(), border_thickness_, border_color_);
		canvas.Line(first_side_second_point_.X(), first_side_second_point_.Y(), second_side_second_point.X(), second_side_second_point.Y(), border_thickness_, border_color_);
		canvas.Line(second_side_first_point.X(), second_side_first_point.Y(), second_side_second_point.X(), second_side_second_point.Y(), border_thickness_, border_color_);
		
		return false;

	}

}

void TrapezoidFigure::EndDrawing() {



}
