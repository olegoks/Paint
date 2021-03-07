#include "FormsLibrary/FormsLibrary.hpp"
#include <vector>
#include <filesystem>
#include <array>
#include <cstdint>
#include "AbstractFigure.hpp"
#include "ColorsPanel.hpp"
#include "FiguresPanel.hpp"
#include "MyCanvas.hpp"

class MyForm : private Form {
public:
	
	explicit MyForm(const std::wstring& caption, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height)noexcept:
		Form::Form{}{

		Form::Position(x, y);
		Form::Size(width, height);
		Form::Style(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create(L"MyForm");
		Form::Caption(caption.c_str());
		Form::Show(SW_SHOW);

	}
	
	void Run() { Form::Run(); }
	HWND Handle() { return Form::Handle(); }

};

class MainForm : private MyForm {
private:

	MyCanvas canvas_;
	ColorsPanel colors_;
	FiguresPanel figures_;
	Color current_color_;

public:

	explicit MainForm():
		MyForm::MyForm{ L"Paint", 100, 100, 1000, 800 },
		canvas_{ Handle(), 100 , 100, 400, 300 },
		colors_{ Handle() },
		figures_{ Handle(), 0, 100, 100, 300 }{
	
		figures_.InitProcFigureSelect([this](AbstractFigure* figure)noexcept->void {
			
		
			
			});

		canvas_.InitProcessActionFunction([this](MyCanvas& canvas, Message& message)->bool {
			
			static Coordinats last_click{ 0, 0 };

			if (message.GetAction() == Action::LMouseDown) {

				uint64_t x = message.GetX();
				uint64_t y = message.GetY();
				AbstractFigure* figure_to_draw = figures_.GetFigure();
				figure_to_draw->SetParametrs(FigureInfo{ Coordinats{ x, y }, Coordinats{ x + 100, y + 100 }, current_color_ });
				canvas.DrawFigure(figure_to_draw);
				canvas.Flush();

				return true;

			}
			
			return false;

			});
	}

	void Run()noexcept(false) {

		MyForm::Run();

	}

};

class Application {
private:
	
	MainForm main_form_;

public:

	explicit Application()noexcept(false) :
		main_form_{} { }

	void Run(int nCmdShow)noexcept(false) {

		//canvas_.InitCanvasProc([this](Message& message)noexcept(true)->bool {

		//	switch (message.GetAction()) {
		//	case Action::MouseMove: {

		//		static int prev_x = 0;
		//		static int prev_y = 0;

		//		int x = message.GetX();
		//		int y = message.GetY();

		//		Pixel pixel{ 0, 77, 255 };

		//		if (prev_x && prev_y) {

		//			canvas_.Line(x, y, prev_x, prev_y, Color{ 255, 0, 0 });
		//			canvas_.Flush();

		//		}

		//		prev_x = x;
		//		prev_y = y;

		//		return true;
		//	}
		//	case Action::LMouseDown: {

		//		DLL square_plugin{ u8"SquarePlugin.dll" };
		//		square_plugin.Load();

		//	/*	GetFigureObject get_object = (GetFigureObject)square_plugin.GetFunction(u8"GetFigureObject");
		//		AbstractFigure* square = get_object();*/

		//		//uint64_t x = message.GetX();
		//		//uint64_t y = message.GetY();
		//		//FigureInfo info{ x, y, 100 ,100, Color{ 100, 100 ,100 } };
		//		//square->Draw(canvas_,info );

		//		return true;
		//	}

		//	};

		//	return false;

		//	});

		//canvas_.Create(Handle());
		//canvas_.Show(SW_SHOW);
		//canvas_.Position(80, 60);
		//
		main_form_.Run();

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