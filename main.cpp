#include <FormsLibrary.hpp>
#include <vector>
#include <filesystem>


class UserInterface {
private:




public:

};

class MyCanvas : public Canvas {
private:




};

#include <array>
#include <cstdint>

enum class PanelColor : uint8_t {

	YELLOW = 0,
	BLACK,
	WHITE,
	GREEN, 
	DARK_BLUE

};

class ColorsPanel {
private:

	std::array<Button, 5> buttons_;

public:

	explicit ColorsPanel(const HINSTANCE hInstance, const HWND parent_hWnd)noexcept(false):
		buttons_{ } {

		for (int delta = 0, i = 0; i < 5; i++) {
		
			buttons_[i].Create(parent_hWnd, L"Button");
			buttons_[i].Position(delta, 0 );
			buttons_[i].Show();
			buttons_[i].Size(20, 20);
			delta += 20;

		}

		buttons_[0].Image(L"D:\\C++\\Paint\\ColorsPanel\\Yellow.bmp");
		buttons_[1].Image(L"D:\\C++\\Paint\\ColorsPanel\\Black.bmp");
		buttons_[2].Image(L"D:\\C++\\Paint\\ColorsPanel\\White.bmp");
		buttons_[3].Image(L"D:\\C++\\Paint\\ColorsPanel\\DarkBlue.bmp");
		buttons_[4].Image(L"D:\\C++\\Paint\\ColorsPanel\\Green.bmp");

	}

};

class MyForm :public Form {
public:
	
	explicit MyForm(const HINSTANCE hInstance)noexcept(false) :
		Form::Form{ GetModuleHandleW(NULL) }{

		Form::Size(500, 700);
		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create(L"MyForm");
		Form::Caption(L"Paint");
		Form::Show(SW_SHOW);

	}

	void Run()noexcept(false) {

		Form::Run();

	}

};

//class MyButton : public Button {
//public:
//
//	explicit MyButton(const HINSTANCE hInstance, const HWND parent_hWnd)noexcept(false):
//		Button::Button{ hInstance }{
//
//		Button::Create(parent_hWnd);
//		Button::
//
//	}
//
//};

class Application :public MyForm {
private:

	Canvas canvas_;
	Button but_rect_;
	Button but_square_;
	Button but_line_;
	ColorsPanel colors_;

public:

	explicit Application(const HINSTANCE hInstance)noexcept(false) :
		MyForm::MyForm{ hInstance },
		canvas_{ hInstance, 0, 0, 1000, 300 },
		but_rect_{ },
		but_square_{  },
		but_line_{ },
		colors_{ hInstance, Handle() }{



	}

	void Run(int nCmdShow)noexcept(false) {


		but_rect_.InitButtonProc([](Message& message)->bool {
			
			if (message.GetAction() == Action::ButtonClicked) {

				MessageBoxA(NULL, u8"Button clicked", "Button message", MB_OK);

				return true;

			}
			
				return false;

			});

		canvas_.InitCanvasProc([this](Message& message)noexcept(true)->bool {
			
			switch (message.GetAction()) {
			case Action::MouseMove:

				static int prev_x = 0;
				static int prev_y = 0;

				int x = message.GetX();
				int y = message.GetY();

				Pixel pixel{ 0, 77, 255 };

				if (prev_x && prev_y) {
				
					canvas_.Line(x, y, prev_x, prev_y, Color{ 255, 0, 0 });
					canvas_.Flush();
				
				}

				prev_x = x;
				prev_y = y;

				return true;

			};

			return false;

			});

		but_rect_.Create(Handle(), L"Button");
		but_square_.Create(Handle(), L"Button");
		but_line_.Create(Handle(), L"Button");

		but_rect_.Show();
		but_rect_.Position(0, 120);
		but_square_.Show();
		but_square_.Position(0, 180);
		but_line_.Show();
		but_line_.Position(0, 240);

		but_rect_.Image(L"D:\\C++\\Paint\\Rectangle.bmp");
		but_square_.Image(L"D:\\C++\\Paint\\Square.bmp");
		but_line_.Image(L"D:\\C++\\Paint\\Line.bmp");

		canvas_.Create(Handle());
		canvas_.Show(SW_SHOW);
		canvas_.Position(100, 100);
		
		Form::Run();

	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	try {

		Application form{ hInstance };
		form.Run(nCmdShow);

	} catch (const FormExcep& exception) {

		MessageBoxA(NULL, exception.What().c_str(), u8"Error!", MB_OK );

	}

	return EXIT_SUCCESS;
}