#pragma once

#include "PaintCanvas.hpp"

#include <memory>
#include <list>
using std::list;

#include "Exception.hpp"
using FigureException = Exception;

class Figure final {
private:

	shared_ptr<AbstractFigure> figure_ptr_;
	std::vector<UIInfo> ui_info_;
	signed int pointer_;

public:

	Figure(shared_ptr<AbstractFigure> figure)noexcept:
		figure_ptr_{ figure }, ui_info_{}, pointer_{ -1 }{

		//Start drawing ui_info and Draw ui_info - min number 
		//of ui_info's for drawing figure
		ui_info_.reserve(2);

	}

	Figure()noexcept:
		figure_ptr_{ nullptr }, 
		ui_info_{}, 
		pointer_{ -1 }{	}

	Figure& operator=(Figure&& move_figure)noexcept {

		if (&move_figure == this)return *this;

		std::swap(figure_ptr_, move_figure.figure_ptr_);
		std::swap(ui_info_, move_figure.ui_info_);
		std::swap(pointer_, move_figure.pointer_);

		return *this;

	}

	Figure(Figure&& move_figure)noexcept:
		figure_ptr_{  }, ui_info_{}, pointer_{ -1 }{

		std::swap(figure_ptr_, move_figure.figure_ptr_);
		std::swap(ui_info_, move_figure.ui_info_);
		std::swap(pointer_, move_figure.pointer_);

	}

	Figure(const Figure& copy_figure) = delete;
	Figure& operator=(const Figure& copy_figure)noexcept = delete;

	bool Empty()const noexcept {

		return pointer_ == -1;

	}

	void ReturnBack()noexcept {

		if (pointer_ > 0)
			--pointer_;

	}

	void ReturnForward()noexcept {

		if (pointer_ != ui_info_.size() - 1)
			++pointer_;

	}

	void StartDrawing(PaintCanvas& canvas, const UIInfo& ui_info)noexcept {

		if (pointer_ != -1)
			ui_info_.erase(ui_info_.begin() + pointer_ + 1, ui_info_.end());

		ui_info_.push_back(ui_info);
		++pointer_;
		figure_ptr_->StartDrawing(canvas, ui_info);

	}

	void Draw(PaintCanvas& canvas, const UIInfo& ui_info)noexcept {

		if (pointer_ != -1)
			ui_info_.erase(ui_info_.begin() + pointer_ + 1, ui_info_.end());

		ui_info_.push_back(ui_info);
		++pointer_;
		figure_ptr_->Draw(canvas, ui_info);

	}

	void EndDrawing()noexcept {

		figure_ptr_->EndDrawing();

	}

	void Draw(PaintCanvas& canvas)noexcept {

		figure_ptr_->StartDrawing(canvas, *ui_info_.begin());

		for (int i = 1; i <= pointer_; ++i)
			figure_ptr_->Draw(canvas, ui_info_[i]);

		figure_ptr_->EndDrawing();

	}

	friend std::ofstream& operator<<(std::ofstream& ser_file, Figure& figure)noexcept {

		using namespace std;

		//Saving figure name 
		string_view plugin_name = figure.figure_ptr_->GetPluginName();
		uint64_t plugin_name_length = plugin_name.size() + 1;
		ser_file.write(reinterpret_cast<const char*>(&plugin_name_length), sizeof uint64_t);
		ser_file.write(plugin_name.data(), plugin_name.size() + 1);

		const uint64_t ui_info_number = figure.ui_info_.size();

		//Saving number of UIInfo's
		ser_file.write(reinterpret_cast<const char*>(&ui_info_number), sizeof uint64_t);

		//Saving pointer position
		ser_file.write(reinterpret_cast<const char*>(&figure.pointer_), sizeof(int));

		//Saving UIInfo's for this figure
		UIInfo* ui_info_data = figure.ui_info_.data();
		ser_file.write(reinterpret_cast<const char*>(ui_info_data), sizeof UIInfo * ui_info_number);

		return ser_file;
	}

	friend std::ifstream& operator>>(std::ifstream& ser_file, Figure& figure) {

		//Reading plugin name size and plugin name 
		uint64_t plugin_name_size = 0;
		ser_file.read(reinterpret_cast<char*>(&plugin_name_size), sizeof uint64_t);

		if (ser_file.eof())
			throw FigureException{ u8"Serialization file is empty." };

		auto plugin_name = std::make_unique<char[]>(plugin_name_size);
		ser_file.read(plugin_name.get(), plugin_name_size);

		//Reading number of ui_info
		uint64_t ui_info_number = 0;
		ser_file.read(reinterpret_cast<char*>(&ui_info_number), sizeof uint64_t);

		//Reading pointer
		signed int pointer = -1;
		ser_file.read(reinterpret_cast<char*>(&pointer), sizeof(int));

		//Reading ui_info's
		std::vector<UIInfo> read_ui_info{};
		read_ui_info.reserve(ui_info_number);

		for (uint64_t i = 0; i < ui_info_number; ++i) {
			
			UIInfo ui_info{};
			ser_file.read(reinterpret_cast<char*>(&ui_info), sizeof UIInfo);
			read_ui_info.push_back(std::move(ui_info));

		}

		if (ser_file.eof())
			throw FigureException{ u8"Figure reading error." };

		Plugin& plugin = PluginsManager::Access()[plugin_name.get()];

		//if there are no such loaded plugin - error, cleaning list of loaded plugins
		//if (!plugin.has_value())
		//	throw FigureException{ u8"There are no such plugin." };

		figure.pointer_ = pointer;
		figure.ui_info_ = std::move(read_ui_info);
		figure.figure_ptr_ = plugin.GetFigure();

		return ser_file;

	}

};
