#include <windows.h>
#include <Form.hpp>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	Form form{hInstance};
	form.Show();
	return EXIT_SUCCESS;
}