#include "FormsLibrary/FormsLibrary.hpp"
#include <vector>
#include <filesystem>
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

	explicit ColorsPanel(const HWND parent_hWnd)noexcept(false):
		buttons_{ } {

		for (int delta = 240, i = 0; i < 5; i++) {
		
			buttons_[i].Create(parent_hWnd, L"Button");
			buttons_[i].Position(delta, 0 );
			buttons_[i].Show();
			buttons_[i].Size(20, 20);
			delta += 20;

		}

		using namespace std::filesystem;
		path colors_panel{ current_path() / L"ColorsPanel"};

		buttons_[0].Image(path{ colors_panel / L"Yellow.bmp" });
		buttons_[1].Image(path{ colors_panel / L"Black.bmp" } );
		buttons_[2].Image(path{ colors_panel / L"White.bmp" } );
		buttons_[3].Image(path{ colors_panel / L"DarkBlue.bmp" } );
		buttons_[4].Image(path{ colors_panel / L"Green.bmp" } );

	}

};

class MyForm :public Form {
public:
	
	explicit MyForm()noexcept(false) :
		Form::Form{}{

		Form::Size(1180, 800);
		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create(L"MyForm");
		Form::Caption(L"Paint");
		Form::Show(SW_SHOW);

	}

	void Run()noexcept(false) {

		Form::Run();

	}

};

class Application :public MyForm {
private:

	Canvas canvas_;
	Button but_rect_;
	Button but_square_;
	Button but_line_;
	ColorsPanel colors_;
	Button left_;
	Button right_;
	Button thin_line_;
	Button thick_line_;

public:

	explicit Application()noexcept(false) :
		MyForm::MyForm{ },
		canvas_{ 0, 0, 1000, 600 },
		but_rect_{ },
		but_square_{  },
		but_line_{ },
		colors_{ Handle() }{



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

		but_rect_.Create(Handle());
		but_square_.Create(Handle());
		but_line_.Create(Handle());
		thin_line_.Create(Handle());
		thick_line_.Create(Handle());

		thin_line_.Show();
		thick_line_.Show();

		thin_line_.Size(80, 20);
		thick_line_.Size(80, 20);

		thin_line_.Position(340, 0);
		thick_line_.Position(340, 20);

		but_rect_.Show();
		but_rect_.Position(0, 60);
		but_square_.Show();
		but_square_.Position(0, 120);
		but_line_.Show();
		but_line_.Position(0, 180);

		left_.Create(Handle());
		left_.Show();
		left_.Position(80, 0);


		right_.Create(Handle());
		right_.Show();
		right_.Position(160, 0);

		using namespace std::filesystem;
		path figures{ current_path() };
		thick_line_.Image(path{ figures / L"ThickLine.bmp" });
		thin_line_.Image(path{ figures / L"ThinLine.bmp" });
		left_.Image(path{ figures / L"Left.bmp" });
		right_.Image(path{ figures / L"Right.bmp" } );
		but_rect_.Image(path{ figures / L"Rectangle.bmp" } );
		but_square_.Image(path{ figures / L"Square.bmp" } );
		but_line_.Image(path{ figures / L"Line.bmp" } );

		canvas_.Create(Handle());
		canvas_.Show(SW_SHOW);
		canvas_.Position(80, 60);
		
		Form::Run();

	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	try {

		Application form{  };
		form.Run(nCmdShow);

	} catch (const FormExcep exception) {

		MessageBoxA(NULL, exception.What().c_str(), u8"Error!", MB_OK );

	}

	return EXIT_SUCCESS;
}