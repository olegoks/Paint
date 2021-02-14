#include <Form.hpp>
#include <Canvas.hpp>

class MyForm :public Form {
private:

	Canvas canvas_;

public:

	explicit MyForm(const HINSTANCE hInstance)noexcept(true) :
		Form::Form{ hInstance },
		canvas_{ hInstance, 900, 600 }{


	}

	void Run(int nCmdShow)noexcept(false) {

		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::InitFormProc([this](Message& message)->bool {

			if (message.key_type.message_ == WM_CREATE) {
				//canvas_.Create(this->Handle());

				return true;
			}

			return false;

			});

		Form::Run(nCmdShow);


	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	MyForm form{ hInstance };

	try {

		form.Run(SW_MAXIMIZE);

	} catch (const FormExcep& exception) {

		MessageBoxA(NULL, exception.What().data(), u8"Error!", MB_OK );

	}

	return EXIT_SUCCESS;
}