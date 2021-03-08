#pragma once
#ifndef FIGURESPANEL_HPP
#define FIGURESPANEL_HPP

#include <cstdint>
using std::uint64_t;
#include <vector>
#include <string>
#include <Button.hpp>
#include "DLL.hpp"

using GetFigureName = std::string(*)();
using GetFigureObject = AbstractFigure*(*)();

#include <functional>
using ProcessFigureSelect = std::function<void(AbstractFigure*)>;

class FiguresPanel {
private:

	std::vector<Button> buttons_;
	std::vector<DLL>	plugins_;
	GetFigureObject current_get_object_function_;

private:

	void LoadPlugins() {

		using namespace std::filesystem;
		path plugins_path{ current_path() / u8"plugins/" };
		if (!exists(plugins_path)) return;
		for (auto& file : directory_iterator{ plugins_path }) {

			path file_path = file.path();
			const std::string file_name = file_path.filename().string();
			const std::string file_extention = file_path.extension().string();

			if(file_extention == u8".dll"){
				
				try {

					DLL plugin{ file_path.string() };
					plugin.Load();
					plugins_.push_back(plugin);

				} catch (...) {

					continue;

				}

			}

		}

	}

public:

	explicit FiguresPanel(const HWND hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height):
		buttons_{},
		plugins_{},
		current_get_object_function_{ []()->AbstractFigure* {  return nullptr; } }{

		namespace fs = std::filesystem;

		fs::path plugins_path{ fs::current_path() / u8"plugins" };
		LoadPlugins();
		
		for (auto& plugin : plugins_) {

			auto get_name = (GetFigureName)plugin.GetFunction(u8"GetFigureName");
			buttons_.push_back(Button{});

			auto get_object = (GetFigureObject)plugin.GetFunction(u8"GetFigureObject");

			fs::path image_path{ plugins_path / (get_name() + std::string{ u8".bmp" }) };
			Button& button = buttons_.back();
			button.Image(image_path);

			button.SetProcessFunction([get_object, this](Message& message)noexcept->bool {
				
				static GetFigureObject get_figure_object = get_object;

				if (message.GetAction() == Action::ButtonClicked) {
				
					current_get_object_function_ = get_object;
					
					return true;

				}

				return false;

			});

		}

		uint64_t button_height = height / buttons_.size();
		if (button_height > 80)button_height = 80;
		uint64_t button_offset = y;

		for (auto& button : buttons_) {

			button.ChangeSize(width, button_height);
			button.ChangePosition(x, button_offset);
			button_offset += button_height;
			button.Create(hWnd);
			button.Show();

		}

	}

	AbstractFigure* GetFigure()const noexcept {

		return current_get_object_function_();

	}

};

#endif //FIGURESPANEL_HPP