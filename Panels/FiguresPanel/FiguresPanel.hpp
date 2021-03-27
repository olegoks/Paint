#pragma once
#ifndef FIGURESPANEL_HPP
#define FIGURESPANEL_HPP

#include <cstdint>
using std::uint64_t;

#include <vector>
using std::vector;

#include <string>
#include <Button.hpp>
#include <functional>
#include <optional>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

#include <memory>
using std::shared_ptr;
using std::weak_ptr;

#include "PluginsManager.hpp"

class FiguresPanel {

public:

	using ProcessFigureSelection = std::function<void(const Plugin& selected_plugin)>;

private:

	const HWND parent_hWnd_;
	vector<Button> buttons_;

	ProcessFigureSelection process_selection_;
	Position position_;
	Size size_;
	static const inline std::uint64_t max_button_height = 60;

public:

	explicit FiguresPanel(const HWND hWnd, Position position, Size size):
		parent_hWnd_{ hWnd },
		buttons_{ },
		process_selection_{ [](const Plugin& plugin)noexcept->void { } },
		position_{ position },
		size_{ size }{

	}

	void Show()noexcept {

		PluginsManager& manager = PluginsManager::Access();

		//Number of buttons equals number of plugins
		const uint64_t plugins_number = manager.LoadedPluginsNumber();
		const uint64_t buttons_number = plugins_number;

		uint64_t button_height = FiguresPanel::size_.Height() / buttons_number;

		if (button_height > max_button_height)
			button_height = max_button_height;

		uint64_t button_offset = FiguresPanel::position_.Y();

		buttons_.reserve(buttons_number);
		buttons_.shrink_to_fit();

		for (auto& [name, plugin] : manager.AllPlugins()) {

			Button button{};
			button.ChangeSize(size_.Width(), button_height);
			button.ChangePosition(position_.X(), button_offset);
			
			const Plugin& selected_plugin = plugin;
			
			button.SetProcessFunction([&selected_plugin, this](Message& message)noexcept->bool {
				
				if (message.GetAction() == Action::ButtonClicked) {
				
					process_selection_(selected_plugin);

					return true;

				}

				return false;

				});

			button.Create(parent_hWnd_);

			using namespace std::string_literals;

			button.Image(PluginsManager::plugins_path_ / (string{ plugin.GetName() } + Plugin::image_extension));
			button.Show();

			buttons_.push_back(std::move(button));
			button_offset += button_height;

		}

	}

	void ChangeProcessFigureSelectionFunction(ProcessFigureSelection process_selection)noexcept{
	
		process_selection_ = process_selection;
	
	}

};

#endif //FIGURESPANEL_HPP