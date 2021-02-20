#include <FormsLibrary.hpp>

#include <filesystem>


class UserInterface {
private:



public:

};
class MyForm :public Form {
private:

	Canvas canvas_;
	Button but_rect_;
	Button but_square_;

public:

	explicit MyForm(const HINSTANCE hInstance)noexcept(false) :
		Form::Form{ hInstance },
		canvas_{ hInstance, 0, 0, 1000, 300 },
		but_rect_{ hInstance },
		but_square_{ hInstance }{


	}

	void Run(int nCmdShow)noexcept(false) {

		Form::Size(500, 700);
		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create(L"My form");
		Form::Show(nCmdShow);
		Form::Caption(L"Paint");


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
		but_rect_.Show();
		but_rect_.Image(L"D:\\C++\\Paint\\Rectangle.bmp");

		canvas_.Create(Handle());
		canvas_.Show(SW_SHOW);
		canvas_.Position(100, 100);
		
		Form::Run();

	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	try {

		MyForm form{ hInstance };
		form.Run(nCmdShow);

	} catch (const FormExcep& exception) {

		MessageBoxA(NULL, exception.What().c_str(), u8"Error!", MB_OK );

	}

	return EXIT_SUCCESS;
}