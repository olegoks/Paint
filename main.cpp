#include <FormsLibrary.hpp>
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

		Form::ChangePosition(x, y);
		Form::ChangeSize(width, height);
		Form::ChangeStyle(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create();
		Form::ChangeCaption(caption.c_str());
		Form::Show(SW_SHOW);

	}
	
	void Run() { Form::Run(); }
	HWND Handle() { return Form::GetHandle(); }

};

class MainForm : private MyForm {
private:

	MyCanvas canvas_;
	//ColorsPanel colors_;
	FiguresPanel figures_;
	Color current_color_;
	Button return_back_;
	Button return_forward_;

public:

	explicit MainForm():
		MyForm::MyForm{ L"Paint", 100, 100, 560, 420 + 40},
		canvas_{ Handle(), 80, 60, 400, 300 },
		figures_{ Handle(), 0, 0, 80, 300 },
		current_color_{ 0, 0, 0 }{

		return_back_.ChangePosition(80, 0);
		return_back_.ChangeSize(80, 60);
		return_back_.SetProcessFunction([this](Message& message)noexcept->bool {
			
			if (message.GetAction() == Action::ButtonClicked) {

				canvas_.ReturnBack();
				
				return true;

			}

			return false;

			});

		return_back_.Create(Handle());
		return_back_.Image(L"Left.bmp");
		return_back_.Show();

		return_forward_.ChangePosition(160, 0);
		return_forward_.ChangeSize(80, 60);
		return_forward_.SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				canvas_.ReturnForward();

				return true;

			}

			return false;

			});

		return_forward_.Create(Handle());
		return_forward_.Image(L"Right.bmp");
		return_forward_.Show();

		canvas_.InitProcessActionFunction([this](MyCanvas& canvas, Message& message)->bool {
			
			static Coordinats last_click{ 0, 0 };

			switch (message.GetAction()) {
			case Action::Repaint:

				canvas.Flush();

				return true;

			case Action::LMouseDown: {

				last_click = Coordinats{ (uint64_t)message.GetX(), (uint64_t)message.GetY()};

				std::optional<AbstractFigure*> maybe_ptr = figures_.GetFigure();

				if (!maybe_ptr.has_value()) {

					MessageBoxA(Handle(), u8"Please, select figure!", u8"Notification!", MB_OK | MB_ICONWARNING);

					return true;

				}

				AbstractFigure* figure_to_draw = maybe_ptr.value();

				uint64_t x = message.GetX();
				uint64_t y = message.GetY();

				figure_to_draw->SetParametrs(FigureInfo{ Coordinats{ last_click.X(), last_click.Y() }, Coordinats{ x + 1, y + 1 }, current_color_ });
				canvas.DrawFigure(figure_to_draw);
				canvas.Flush();

				return true;
				[[fallthrough]];
			}

			case Action::MouseMove: {

				if (!last_click.X() && !last_click.Y())return true;

				std::optional<AbstractFigure*> maybe_ptr = figures_.GetFigure();

				if (!maybe_ptr.has_value()) {

					MessageBoxA(Handle(), u8"Please, select figure!", u8"Notification!", MB_OK | MB_ICONWARNING);

					return true;

				}

				AbstractFigure* figure_to_draw = maybe_ptr.value();

				uint64_t x = message.GetX();
				uint64_t y = message.GetY();

				figure_to_draw->SetParametrs(FigureInfo{ Coordinats{ last_click.X(), last_click.Y() }, Coordinats{ x, y }, current_color_ });
				canvas.ReturnBack();
				canvas.DrawFigure(figure_to_draw);
				canvas.Flush();

				return true;
				[[fallthrough]];
			}

			case Action::LMouseUp: {

				last_click = Coordinats{ 0, 0 };

				return true;
				[[fallthrough]];
			}
			};

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

	} catch (const ComponentException& exception) {

		MessageBoxA(NULL, exception.What().c_str(), u8"Error!", MB_OK);

	}

	return EXIT_SUCCESS;
}