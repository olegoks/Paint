#pragma once
#ifndef FIGURESPANEL_HPP
#define FIGURESPANEL_HPP

#include <cstdint>
using std::uint64_t;

#include <vector>
#include <string>
#include <Button.hpp>
#include <functional>

using ProcessFigureSelect = std::function<void(AbstractFigure*)>;

namespace fs = std::filesystem;
#include "FigurePlugin.hpp"

class FiguresPanel {
private:

	std::vector<std::pair<FigurePlugin, Button>> plugins_buttons_;
	std::unique_ptr<FigurePlugin> current_plugin_;

private:

	void LoadPlugins(const fs::path& plugins_path) {

		if (!exists(plugins_path)) return;

		for (auto& plugin : fs::directory_iterator{ plugins_path }) {

			fs::path plugin_path = plugin.path();
			const std::string file_extention = plugin_path.extension().string();

			if(file_extention == FigurePlugin::extension){
				
				try {

					FigurePlugin plugin{ plugin_path };
					plugin.Load();
					plugins_buttons_.push_back(std::pair(std::move(plugin), Button{}));

				} catch (const PluginException& exception) {

					continue;

				}

			}

		}

	}

public:

	explicit FiguresPanel(const HWND hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height):
		plugins_buttons_{} {

		fs::path plugins_path{ fs::current_path() / u8"plugins/" };

		//Creates buttons with default constructors
		LoadPlugins(plugins_path);

		for (auto& [plugin, button] : plugins_buttons_) {

			FigurePlugin& plugin_reference = plugin;

			button.SetProcessFunction([&plugin_reference, this](Message& message)noexcept->bool {
				
				static FigurePlugin& figure_plugin = plugin_reference;

				if (message.GetAction() == Action::ButtonClicked) {
				
					current_plugin_ = std::make_unique<FigurePlugin>(&figure_plugin);
					
					return true;

				}

				return false;

			});


			uint64_t button_height = height / plugins_buttons_.size();
			if (button_height > 80)button_height = 80;
			uint64_t button_offset = y;

			button.ChangeSize(width, button_height);
			button.ChangePosition(x, button_offset);
			button_offset += button_height;
			button.Create(hWnd);
			button.Show();

			std::string image_name{ plugin.GetName() + FigurePlugin::image_extension };
			fs::path image_path{ plugins_path / image_name };

			button.Image(image_path);


		}

	}

	std::unique_ptr<AbstractFigure> GetFigure()noexcept {

		return current_plugin_->GetFigureObjectPointer();

	}

};

#endif //FIGURESPANEL_HPP