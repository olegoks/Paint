#pragma once
#ifndef PAINTFORM_HPP
#define PAINTFORM_HPP

#include <FormsLibrary.hpp>
#include "FiguresPanel.hpp"
#include "PaintCanvas.hpp"
#include "Types.hpp"
class MyForm : public Form {
private:

	using Form::Create;
	using Form::Destroy;
	using Form::Show;

public:

	explicit MyForm(const std::wstring& caption, const Position& position, const Size& size)noexcept :
		Form::Form{}{

		Form::ChangePosition(position.X(), position.Y());
		Form::ChangeSize(size.Width(), size.Height());
		Form::ChangeStyle(WS_EX_TOPMOST, WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CLIPCHILDREN);
		Form::Create();
		Form::ChangeCaption(caption.c_str());
		Form::Show(SW_SHOW);

	}
	
};

#include <cstdint>
using std::uint64_t;
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
#include "PluginsManager.hpp"

class PaintForm : private MyForm {
private:

	static const fs::path inline plugins_path_{ fs::current_path() / u8"plugins" };

	PaintCanvas canvas_;
	FiguresPanel figures_panel_;

	Button return_back_;
	Button return_forward_;

	static const inline uint64_t button_width = 80;
	static const inline uint64_t button_height = 60;
	static const inline uint64_t caption_height = 41;

public:

	explicit PaintForm(const std::wstring& caption, const Coordinats& position, const Size& size) :
		MyForm::MyForm{ caption.c_str(), position, size },
		canvas_{ GetHandle() },
		figures_panel_{ GetHandle(), Position{ 0, button_height }, Size{ button_width, MyForm::GetHeight() - caption_height - 2 * button_height } }{
	
		PluginsManager& manager = PluginsManager::Access();
		manager.Load(plugins_path_);

		figures_panel_.Show();

		if (manager.GetLoadedPluginsNumber() == 0)
			MessageBoxA(MyForm::GetHandle(), u8"Отсутствуют плагины фигур!", u8"Предупреждение!", MB_OK | MB_ICONWARNING);


		const Position canvas_pos{ button_width, button_height };
		const Size canvas_size{ MyForm::GetWidth() - 2 * button_width, MyForm::GetHeight() - caption_height - 2 * button_height };
		
		canvas_.ChangeSize(canvas_size.Width(), canvas_size.Height());
		canvas_.ChangePosition(canvas_pos.X(), canvas_pos.Y());

		return_back_.ChangePosition(button_width, 0);
		return_back_.ChangeSize(button_width, button_height);

		return_back_.SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				canvas_.ReturnBack();
				canvas_.Flush();
				return true;

			}

			return false;

		});

		return_back_.Create(GetHandle());
		return_back_.Image(L"Left.bmp");
		return_back_.Show();

		return_forward_.ChangePosition(2 * button_width, 0);
		return_forward_.ChangeSize(button_width, button_height);
		return_forward_.SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				canvas_.ReturnForward();
				canvas_.Flush();
				
				return true;

			}

			return false;

			});

		return_forward_.Create(GetHandle());
		return_forward_.Image(L"Right.bmp");
		return_forward_.Show();

		figures_panel_.ChangeProcessFigureSelectionFunction([this](const Plugin& plugin)noexcept->void {
			
			canvas_.ChangeFigureToDraw(plugin);
			
			});

		canvas_.SetProcessActionsFunction([this, canvas_pos](PaintCanvas& canvas, Message& message)->bool {

			static Coordinats figure_position{ 0, 0 };
			static UIInfo ui_info{};

			switch (message.GetAction()) {
			case Action::PositionChanging: {

				auto pos_size = (WINDOWPOS*)message.GetLParam();
				
				pos_size->x = canvas_pos.X();
				pos_size->y = canvas_pos.Y();

				const uint64_t form_width = MyForm::GetWidth();
				const uint64_t form_height = MyForm::GetHeight();

				if (pos_size->cx > form_width - 2 * button_width)
					pos_size->cx = form_width - 2 * button_width;

				if (pos_size->cy > form_height - 2 * button_width + caption_height)
					pos_size->cy = form_height - 2 * button_width + caption_height;

				return true;
			}

			case Action::LMouseDown: {
				
				if (!canvas.ThereIsFigureToDraw())return true;

				if (!figure_position.X() && !figure_position.Y()) {

					figure_position = Coordinats{ (uint64_t)message.GetX(), (uint64_t)message.GetY() };
					ui_info.mouse_click_ = figure_position;
					canvas_.StartDraw(ui_info);
					canvas_.Flush();

				} else {

					figure_position = Coordinats{ (uint64_t)message.GetX(), (uint64_t)message.GetY() };
					ui_info.mouse_click_ = figure_position;
					canvas_.Draw(ui_info);
					canvas_.Flush();
				
				}

				return true;
		
			}

			case Action::MouseMove: {

				if (!figure_position.X() && !figure_position.Y())
					return true;

				Coordinats left_bottom{ figure_position.X(), figure_position.Y() };
				Coordinats mouse_pos_{ (uint64_t)message.GetX(), (uint64_t)message.GetY() };

				ui_info.mouse_click_ = mouse_pos_;

				canvas.ReturnBackFigureDrawing();
				canvas.Draw(ui_info);
				canvas.Flush();
				
				return true;
	
			}

			case Action::RMouseDown: {

				//Figure drawing ended
				figure_position = Coordinats{ 0, 0 };

				canvas_.ReturnBackFigureDrawing();
				canvas_.EndDraw();
				canvas.Flush();

				return true;

			}
			
			case Action::Repaint: {

				canvas_.Flush();

				return true;
			}

			};

			return false;

			});


		SetProcessFunction([this](Message& message)noexcept->bool {

			switch (message.GetAction()) {
			case Action::Resized: {
				
				const uint64_t new_width = LOWORD(message.GetLParam());
				const uint64_t new_height = HIWORD(message.GetLParam());
				if (new_width == 0 && new_height == 0)return true;
				if (new_width < canvas_.GetWidth() + 2 * button_width ||
					new_height < canvas_.GetHeight() + 2 * button_height)
					canvas_.ChangeSize(new_width - 2 * button_width, new_height - 2 * button_height);

				return true;
			}
			case Action::Close: {

				int user_decision = IDYES;
				user_decision = MessageBoxA(MyForm::GetHandle(), "Сохранить текущее состояние?", "Предупреждение!", MB_YESNO);
				if (user_decision == IDYES) {
					
					canvas_.Serialize(std::filesystem::current_path() / "ser");

					MessageBoxA(MyForm::GetHandle(), "Состояние сохранено!", "", MB_OK);
					return false;
				}

				return true;
			}
			};

			return false;

			});


		try {

			canvas_.Deserialize(std::filesystem::current_path() / "ser");

		}
		catch (const PaintCanvasException& deserialization_error) {

			MessageBoxA(NULL, deserialization_error.What().c_str(), u8"Notification!", MB_OK);

		}

		canvas_.Flush();

	}

	void Run() {

		MyForm::Run();

	}

};

#endif //PAINTFORM_HPP