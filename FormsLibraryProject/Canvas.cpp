#include <Canvas.hpp>

EXPIMP Canvas::Canvas(const int x, const int y, const int width, const int height)noexcept(false) :
	Form::Form{  },
	buffer_{ nullptr },
	pixels_number_{ width * height }{

	try {

		Form::Position(x, y);
		Form::Size(width, height);

		buffer_ = new Pixel[pixels_number_];

	} catch (std::bad_alloc& new_exception) {

		throw FormExcep{ std::string{ u8"Bad allocation memory: " }
			+ std::string{ new_exception.what() } };

	}
	catch (const FormExcep& form_exception) {

		throw FormExcep{ u8"Canvas constructor error." };

	}

}

EXPIMP void Canvas::Position(const int x, const int y)noexcept(true) {

	try {

		Form::Position(x, y);

	}
	catch (const FormExcep& exception) {

		throw;

	}

}


EXPIMP void Canvas::Fill(const Color& color)noexcept(true) {

	std::for_each(buffer_, buffer_ + pixels_number_, [&color](Pixel& pixel)noexcept->void {

		pixel = color;

		});

}

EXPIMP void Canvas::Line(int x, int y, int _x, int _y, const Color& color)noexcept(true) {

	const int deltaX = abs(_x - x);
	const int deltaY = abs(_y - y);
	const int signX = x < _x ? 1 : -1;
	const int signY = y < _y ? 1 : -1;

	int error = deltaX - deltaY;

	SetPixel(x, y, color);

	while (x != _x || y != _y) {

		const int error2 = error * 2;

		SetPixel(x, y, color);

		if (error2 > -deltaY) {

			error -= deltaY;
			x += signX;

		}

		if (error2 < deltaX) {

			error += deltaX;
			y += signY;

		}

	}

}


EXPIMP void Canvas::SetPixel(int x, int y, const Pixel& pixel)noexcept(true) {

	int index = y * Form::Width() + x;

	if (0 < index && index <= this->pixels_number_)
		buffer_[index] = pixel;

}

EXPIMP void Canvas::Flush()noexcept(false) {

	try {

		ShowFrame(buffer_);

	}
	catch (const FormExcep& exception) {

		throw;

	}

}

EXPIMP void Canvas::Create(const HWND parent_hWnd)noexcept(false) {

	try {

		Form::Style(NULL, WS_CHILD | WS_BORDER);
		Form::Create(L"Canvas", parent_hWnd);
		Canvas::Fill(kDefaultBackgroundColor);

	}
	catch (const FormExcep& exception) {

		throw;

	}
}

EXPIMP void Canvas::Show(int nCmdShow)noexcept(false) {

	try {

		Form::Show(SW_SHOW);
		Flush();

	}
	catch (const FormExcep& exception) {

		throw;

	}

}

EXPIMP void Canvas::InitCanvasProc(FormProc process_canvas)noexcept(true) {

	Form::InitFormProc(process_canvas);

}