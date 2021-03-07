#include "FormsLibrary/FormsLibrary.hpp"
#include <vector>
#include <filesystem>
#include <array>
#include <cstdint>
#include "AbstractFigure.hpp"
#include "ColorsPanel.hpp"
#include "FiguresPanel.hpp"

class MyForm :public Form {

private:

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
typedef AbstractFigure* (*get_object)(void);

class Application :public MyForm {
private:

	Canvas canvas_;
	ColorsPanel colors_;
	FiguresPanel figures_;

public:

	explicit Application()noexcept(false) :
		MyForm::MyForm{ },
		canvas_{ 0, 0, 1000, 600 },
		colors_{ Handle() },
		figures_{ Handle(), 0, 100, 200, 300 }{



	}

	typedef AbstractFigure* (*GetFigureObject)(void);

	void Run(int nCmdShow)noexcept(false) {

		canvas_.InitCanvasProc([this](Message& message)noexcept(true)->bool {

			switch (message.GetAction()) {
			case Action::MouseMove: {

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
			}
			case Action::LMouseDown: {

				DLL square_plugin{ u8"SquarePlugin.dll" };
				square_plugin.Load();

				GetFigureObject get_object = (GetFigureObject)square_plugin.GetFunction(u8"GetFigureObject");
				AbstractFigure* square = get_object();

				uint64_t x = message.GetX();
				uint64_t y = message.GetY();
				FigureInfo info{ x, y, 100 ,100, Color{ 100, 100 ,100 } };
				square->Draw(canvas_,info );

				return true;
			}

			};

			return false;

			});

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