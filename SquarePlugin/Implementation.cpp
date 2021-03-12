#include "Interface.hpp"

void SquareFigure::SetParametrs(const FigureInfo& info) {

	Coordinats left_top{ info.left_bottom_.X(), info.right_top_.Y() };
	Coordinats right_top{ info.right_top_ };
	Coordinats right_bottom{ info.right_top_.X() , info.left_bottom_.Y() };

	try {

		ClearCommandsBuffer();
		Command(new SolidLineCanvasCommand{ info.left_bottom_, left_top, info.color_ });
		Command(new SolidLineCanvasCommand{ left_top, right_top, info.color_ });
		Command(new SolidLineCanvasCommand{ right_top, right_bottom, info.color_ });
		Command(new SolidLineCanvasCommand{ right_bottom, info.left_bottom_, info.color_ });

	}
	catch (const std::bad_alloc& exception) {

		ClearCommandsBuffer();

		throw 1;

	}

}