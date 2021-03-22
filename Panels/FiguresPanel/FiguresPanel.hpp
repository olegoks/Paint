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

		uint64_t button_height = size_.Height() / manager.GetLoadedPluginsNumber();
		uint64_t button_offset = position_.Y();

		const uint64_t buttons_number = manager.GetLoadedPluginsNumber();
		buttons_.reserve(buttons_number);
		buttons_.shrink_to_fit();

		for (auto& plugin : manager.GetAllLoadedPlugins()) {

			Button button{};
			button.ChangeSize(size_.Width(), button_height);
			button.ChangePosition(position_.X(), button_offset);

			button.SetProcessFunction([&plugin, this](Message& message)noexcept->bool {

				process_selection_(plugin);

				return false;

				});

			button.Create(parent_hWnd_);

			using namespace std::string_literals;

			button.Image(manager.GetPluginsPath() / (string{ plugin.GetName() } + u8".bmp"s));
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