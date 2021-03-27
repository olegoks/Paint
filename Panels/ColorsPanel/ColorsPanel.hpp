#pragma once

#ifndef COLORSPANEL_HPP
#define COLORSPANEL_HPP

#include <vector>
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

	enum class ColorFocus : uint8_t {

		BACKGROUND,
		BORDER

	};

	using ProcessFunction = std::function<void(PanelColor color)>;

private:

	ColorFocus focus_;

	Button background_color_button_;
	Color background_color_;

	Button border_color_button_;
	Color border_color_;

	std::vector<Button> buttons_;

	static const inline std::string images_folder_name_ = u8"ColorsPanelImages";
	static const inline std::filesystem::path images_folder_path_ = std::filesystem::current_path() / images_folder_name_;
	static const inline std::uint64_t select_button_width = 60;
	static const inline std::uint64_t select_button_height_ = 60;

	static const inline std::uint64_t color_button_width_ = 20;
	static const inline std::uint64_t color_button_height_ = 20;

	static Color ConvertPanelColor(PanelColor panel_color) noexcept {

		switch (panel_color) {
		case PanelColor::BLACK:return Color{ 0, 0, 0 };
		case PanelColor::DARK_BLUE:return Color{ 0, 0, 255 };
		case PanelColor::GREEN:return Color{ 0, 255, 0 };
		case PanelColor::WHITE:return Color{ 255, 255, 255 };
		case PanelColor::YELLOW:return Color{ 255, 255, 0 };
		
		default:
			return Color{ 0, 0, 0 };

		};

	}

	void ChangeButtonImage(Button& button, PanelColor panel_color)noexcept {

		switch (panel_color) {
		case PanelColor::BLACK:button.Image(images_folder_path_ / u8"BlackSelected.bmp");
			break;
		case PanelColor::DARK_BLUE:button.Image(images_folder_path_ / u8"BlueSelected.bmp");
			break;
		case PanelColor::GREEN:button.Image(images_folder_path_ / u8"GreenSelected.bmp");
			break;
		case PanelColor::WHITE:button.Image(images_folder_path_ / u8"WhiteSelected.bmp");
			break;
		case PanelColor::YELLOW:button.Image(images_folder_path_ / u8"YellowSelected.bmp");
			break;

		};

	}

	void SetColor(PanelColor selected_color)noexcept {

		if (focus_ == ColorFocus::BACKGROUND) {

			background_color_ = ConvertPanelColor(selected_color);
			ChangeButtonImage(background_color_button_, selected_color);

		} else {

			border_color_ = ConvertPanelColor(selected_color);
			ChangeButtonImage(border_color_button_, selected_color);

		}

	}

public:

	explicit ColorsPanel(const HWND parent_hWnd):
		background_color_button_{},
		background_color_{ Color{ 255, 255, 255 } },
		border_color_button_{},
		border_color_{ Color{ 0, 0, 0 } },
		focus_{ ColorFocus::BORDER },
		buttons_{ } {

		background_color_button_.ChangeSize(select_button_width, select_button_height_);
		background_color_button_.Create(parent_hWnd);
		background_color_button_.Image(images_folder_path_ / u8"WhiteSelected.bmp");
		background_color_button_.SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				focus_ = ColorFocus::BACKGROUND;

			}

			return false;

			});

		background_color_button_.Show();

		border_color_button_.ChangeSize(select_button_width, select_button_height_);
		border_color_button_.Create(parent_hWnd);
		border_color_button_.Image(images_folder_path_ / u8"BlackSelected.bmp");
		border_color_button_.SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				focus_ = ColorFocus::BORDER;

			}

			return false;

			});

		border_color_button_.Show();

		buttons_.resize(5);

		for (auto& button : buttons_) {
		
			button.Create(parent_hWnd);
			button.Show();
		
		}

		buttons_[0].Image(images_folder_path_ / u8"Yellow.bmp" );
		buttons_[1].Image(images_folder_path_ / u8"Black.bmp" );
		buttons_[2].Image(images_folder_path_ / u8"White.bmp" );
		buttons_[3].Image(images_folder_path_ / u8"DarkBlue.bmp" );
		buttons_[4].Image(images_folder_path_ / u8"Green.bmp" );

		ColorsPanel::ChangePosition(Position{ 0, 0 });

		buttons_[0].SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				SetColor(PanelColor::YELLOW);

				return true;

			}

			return false;

			});

		buttons_[1].SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				SetColor(PanelColor::BLACK);

				return true;

			}

			return false;

			});

		buttons_[2].SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				SetColor(PanelColor::WHITE);

				return true;

			}

			return false;

			});

		buttons_[3].SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				SetColor(PanelColor::DARK_BLUE);

				return true;

			}

			return false;

			});

		buttons_[4].SetProcessFunction([this](Message& message)noexcept->bool {

			if (message.GetAction() == Action::ButtonClicked) {

				SetColor(PanelColor::GREEN);

				return true;

			}

			return false;

			});

	}

	void ChangePosition(const Position& new_position)noexcept {

		std::uint64_t offset = new_position.X();

		background_color_button_.ChangePosition(offset, new_position.Y());

		offset += select_button_width;

		border_color_button_.ChangePosition(offset, new_position.Y());

		offset += select_button_width;

		for (auto& button : buttons_) {

			button.ChangeSize(color_button_width_, color_button_height_);
			button.ChangePosition(offset, 0);
			offset += color_button_width_;

		}

	}
	
	void GetSelectedColors(Color& border_color, Color& background_color)const noexcept {

		border_color = border_color_;
		background_color = background_color_;

	}

};


#endif //COLORSPANEL_HPP