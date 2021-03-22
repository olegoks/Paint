#include "PaintForm.hpp"

class PaintApplication final{
private:
	
	PaintForm main_form_;

public:

	explicit PaintApplication():
		main_form_{ L"Paint", Coordinats{ 0, 0 }, Size{ 500, 400 } } { }

	void Run(int nCmdShow){

		main_form_.Run();

	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	try {

		PaintApplication app{ };
		app.Run(nCmdShow);

	} catch (const ComponentException& exception) {

		MessageBoxA(NULL, exception.What().c_str(), u8"Error!", MB_OK);

	}

	return EXIT_SUCCESS;
}