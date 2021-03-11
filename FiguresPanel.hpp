#pragma once
#ifndef FIGURESPANEL_HPP
#define FIGURESPANEL_HPP

#include <cstdint>
using std::uint64_t;

#include <vector>
#include <string>
#include <Button.hpp>
#include <functional>

//using ProcessFigureSelect = std::function<void(AbstractFigure*)>;

namespace fs = std::filesystem;
#include "FigurePlugin.hpp"

class FiguresPanel {
private:

	class FigureButton final : public Button {
	public:

		using ProcessFigureSelection = std::function<void(FigurePlugin& selected_plugin)>;

	private:

		FigurePlugin plugin_;
		ProcessFigureSelection process_selection_;

	private:

		using Button::Create;
		using Button::Button;
		using Button::Destroy;
		using Button::SetProcessFunction;
		using Button::Show;
		using Button::ChangeStyle;
		
	public:

		explicit FigureButton(const HWND parent_hWnd, FigurePlugin&& plugin):
			Button::Button{}, plugin_{ std::move(plugin) },
			process_selection_{ [](FigurePlugin& selected_plugin)noexcept->void {} }{

			Button::Create(parent_hWnd);
			Button::Show(SW_SHOW);

		}

		explicit FigureButton(const FigureButton& copy_button)noexcept = delete;

		explicit FigureButton(FigureButton&& move_button)noexcept:
			Button::Button{ std::move(move_button) },
			plugin_{ fs::path{} },
			process_selection_{ [](FigurePlugin& selected_plugin)noexcept->void {} }{

			std::swap(plugin_, move_button.plugin_);
			std::swap(process_selection_, move_button.process_selection_);

			Button::SetProcessFunction([this](Message& message)noexcept->bool {

				if (message.GetAction() == Action::ButtonClicked) {

					process_selection_(plugin_);

					return true;

				}

				return false;

				});

		}

		FigureButton& operator=(const FigureButton& copy_button)noexcept = delete;

		FigureButton& operator=(FigureButton&& move_button)noexcept{
			
			if (this == &move_button)return *this;

			Button::operator=(std::move(move_button));
			std::swap(plugin_, move_button.plugin_);
			std::swap(process_selection_, move_button.process_selection_);

			Button::SetProcessFunction([this](Message& message)noexcept->bool {

				if (message.GetAction() == Action::ButtonClicked) {

					process_selection_(plugin_);

					return true;

				}

				return false;

				});

			return *this;

		}

		~FigureButton()noexcept = default;

		inline void SetProcessButtonClick(ProcessFigureSelection process_selection)noexcept {

			process_selection_ = process_selection;

		}

	};

	FigurePlugin* current_plugin_;
	const HWND parent_hWnd_;
	std::vector<FigureButton> buttons_;

private:

	void LoadPlugins(const fs::path& plugins_path) noexcept{

		if (!exists(plugins_path)) return;

		for (auto& plugin : fs::directory_iterator{ plugins_path }) {

			fs::path plugin_path = plugin.path();
			const std::string file_extention = plugin_path.extension().string();

			if (file_extention == FigurePlugin::extension) {

				try {

					FigurePlugin plugin{ plugin_path };
					plugin.Load();
					std::string pluging_name = std::move(plugin.GetName()) ;
					
					std::string image_name{ pluging_name + FigurePlugin::image_extension };
					fs::path image_path{ plugins_path / image_name };

					buttons_.push_back(FigureButton{ parent_hWnd_, std::move(plugin) });
					FigureButton& button = buttons_.back();
					button.Image(image_path);

					button.SetProcessButtonClick([this](FigurePlugin& plugin)noexcept->void {

						current_plugin_ = &plugin;

						});

				} catch (const PluginException& exception) { continue; }

			}

		}

	}

public:

	explicit FiguresPanel(const HWND hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height):
		current_plugin_{ nullptr },
		parent_hWnd_{ hWnd },
		buttons_{ }{

		fs::path plugins_path{ fs::current_path() / u8"plugins" };

		LoadPlugins(plugins_path);

		uint64_t button_height = height / buttons_.size();
		if (button_height > 80)button_height = 80;
		uint64_t button_offset = y;

		for (auto& button : buttons_) {

			button.ChangeSize(width, button_height);
			button.ChangePosition(x, button_offset);
			button_offset += button_height;

		}

	}

	[[nodiscard]] AbstractFigure* GetFigure()noexcept {

		return current_plugin_->GetFigureObjectPointer();

	}

};

#endif //FIGURESPANEL_HPP