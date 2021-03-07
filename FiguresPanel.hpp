#pragma once
#ifndef FIGURESPANEL_HPP
#define FIGURESPANEL_HPP

#include <cstdint>
using std::uint64_t;
#include <vector>
#include <string>
#include <Button.hpp>
#include "DLL.hpp"

class FiguresPanel {
private:

	std::vector<Button> figures_buttons_;
	std::vector<DLL>	figures_plugins_;

public:

	explicit FiguresPanel(const HWND hWnd, const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height):
		figures_buttons_{} {

		using namespace std::filesystem;
		path plugins_path{ current_path() / u8"plugins" };

		//for (auto&& dll_it : directory_iterator{ plugins_path }) {

		//	std::string dll_path = dll_it.path().string();
		//	figures_plugins_.push_back(DLL{ std::move(dll_path) });
		//	figures_plugins_.back().Load();
		//	figures_buttons_.push_back(Button{ });

		//}

		figures_buttons_.push_back(Button{ });
		Button& preinstall_rectangle = figures_buttons_[0];

		const uint64_t button_height = height / figures_buttons_.size();



		path figures{ current_path() };
		preinstall_rectangle.Image(path{ figures / L"Rectangle.bmp" });
		preinstall_rectangle.Size(width, button_height);
		preinstall_rectangle.Position(x, y);
		preinstall_rectangle.Create(hWnd);
		preinstall_rectangle.Show();

	}


};

#endif //FIGURESPANEL_HPP