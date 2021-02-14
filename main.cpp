#include <Form.hpp>
#include <Canvas.hpp>

class MyForm :public Form {
private:

	Canvas canvas_;

public:

	explicit MyForm(const HINSTANCE hInstance)noexcept(true) :
		Form::Form{ hInstance },
		canvas_{ hInstance, 900, 600, Color{ 255, 255, 255 } }{


	}

	void Run(int nCmdShow)noexcept(false) {

		Form::Size(1000, 700);
		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create(L"My form");
		Form::Show(nCmdShow);
		canvas_.InitCanvasProc([this](Message& message)noexcept->bool {
			
			switch (message.key_type.action_) {
			case Action::MouseMove:

				int x = message.X();
				int y = message.Y();
				Pixel pixel{ 0, 77, 255 };
				canvas_.SetPixel(x, y, pixel);

				return true;

			};

			return false;

			});
		canvas_.Create(Handle());
		canvas_.Show(SW_SHOW);
		Form::Run();

	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	MyForm form{ hInstance };

	try {

		form.Run(nCmdShow);

	} catch (const FormExcep& exception) {

		MessageBoxA(NULL, exception.What().data(), u8"Error!", MB_OK );

	}

	return EXIT_SUCCESS;
}