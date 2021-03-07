#pragma once

#ifndef COLORSPANEL_HPP
#define COLORSPANEL_HPP

#include <array>
#include <functional>
#include <Button.hpp>

class ColorsPanel {
public:

	enum class PanelColor : uint8_t {

		YELLOW = 0,
		BLACK,
		WHITE,
		GREEN,
		DARK_BLUE

	};

	using ProcessFunction = std::function<void(PanelColor color)>;

private:

	std::array<Button, 5> buttons_;
	ProcessFunction user_select_color_;

public:

	explicit ColorsPanel(const HWND parent_hWnd)noexcept(false) :
		buttons_{ Button{} } {

		for (int delta = 240, i = 0; i < 5; i++) {

			buttons_[i].Create(parent_hWnd, L"Button");
			buttons_[i].Position(delta, 0);
			buttons_[i].Show();
			buttons_[i].Size(20, 20);
			delta += 20;

		}

		using namespace std::filesystem;
		path colors_panel{ current_path() / L"ColorsPanel" };

		buttons_[0].Image(path{ colors_panel / L"Yellow.bmp" });
		buttons_[1].Image(path{ colors_panel / L"Black.bmp" });
		buttons_[2].Image(path{ colors_panel / L"White.bmp" });
		buttons_[3].Image(path{ colors_panel / L"DarkBlue.bmp" });
		buttons_[4].Image(path{ colors_panel / L"Green.bmp" });

		buttons_[0].InitButtonProc([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				user_select_color_(PanelColor::YELLOW);

				return true;

			}

			return false;

			});

		buttons_[1].InitButtonProc([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				user_select_color_(PanelColor::BLACK);

				return true;

			}

			return false;

			});

		buttons_[2].InitButtonProc([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				user_select_color_(PanelColor::YELLOW);

				return true;

			}

			return false;

			});

		buttons_[3].InitButtonProc([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				user_select_color_(PanelColor::WHITE);

				return true;

			}

			return false;

			});

		buttons_[4].InitButtonProc([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				user_select_color_(PanelColor::GREEN);

				return true;

			}

			return false;

			});

	}

	inline void InitProcessFunction(ProcessFunction user_select_color)noexcept {

		user_select_color_ = user_select_color;

	}

};


#endif //COLORSPANEL_HPP