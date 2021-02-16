#include <Form.hpp>
#include <Canvas.hpp>
#include <Button.hpp>

class MyForm :public Form {
private:

	Canvas canvas_;
	Button button_;

public:

	explicit MyForm(const HINSTANCE hInstance)noexcept(false) :
		Form::Form{ hInstance },
		canvas_{ hInstance, 0, 0, 1000, 300 },
		button_{ hInstance }{


	}

	void Run(int nCmdShow)noexcept(false) {

		Form::Size(500, 700);
		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create(L"My form");
		Form::Show(nCmdShow);
		Form::Caption(L"Paint");

		canvas_.InitCanvasProc([this](Message& message)noexcept(true)->bool {
			
			switch (message.GetAction()) {
			case Action::MouseMove:

				int x = message.GetX();
				int y = message.GetY();
				Pixel pixel{ 0, 77, 255 };

				canvas_.Line(x, y, 0, 0, Color{ 255, 0, 0 });
				canvas_.Flush();

				return true;

			};

			return false;

			});

		//button_.InitButtonProc([](Message& message)noexcept->bool {
		//	
		//	Action action = message.GetAction();
		//	
		//	if (action == Action::ButtonClicked) {

		//		MessageBoxW(NULL, L"Button clicked", L"Button", MB_OK);
		//		
		//		return true;

		//	}

		//	return false;

		//	});

		button_.Create(Handle(), L"SomeText");
		button_.Show();

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

		MessageBoxA(NULL, exception.What().data(), u8"Error!", MB_OK );

	}

	return EXIT_SUCCESS;
}