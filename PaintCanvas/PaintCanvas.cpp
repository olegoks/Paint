#include "PaintCanvas.hpp"
#include "PaintFigure.hpp"

void PaintCanvas::ChangeFigureToDraw(const Plugin& plugin) noexcept {

	current_plugin_ = &plugin;

}

bool PaintCanvas::SelectedFigure() const noexcept {

	return current_plugin_ != nullptr;
}

void PaintCanvas::Serialize(const std::filesystem::path& ser_file_path) {

	using namespace std;
	using namespace filesystem;

	if (!exists(ser_file_path.parent_path()))
		throw PaintCanvasException{ u8"Serialization path doesn't exist." };

	ofstream ser_file{ ser_file_path, ios::out | ios::binary };

	if (!ser_file.is_open())
		throw PaintCanvasException{ u8"Opening serialization file error." };

	//				  |						 Figure						 |
	// _______ _______|__________ _______ _______ ______________ ________|    _________ ______
	//|pointer|canvas |figure    |figure |UIInfo |UIInfo |UIInfo |UIInfo |	 |figure   |canvas|
	//|pos	  |size   |name size |name   |number |pointer|		 |		 |	 |name size|size  |
	//|_______|_______|__________|_______|_______|_______|_______|_______|...|_________|______|
	//

	//Saving pointer position 
	ser_file.write(reinterpret_cast<const char*>(&pointer_), sizeof(signed int));

	//Saving canvas size
	const Size canvas_size{ Canvas::GetWidth(), Canvas::GetHeight() };
	ser_file.write(reinterpret_cast<const char*>(&canvas_size), sizeof Size);

	for (auto& figure : figures_)
		ser_file << figure;

	figures_.clear();

}

void PaintCanvas::Deserialize(const std::filesystem::path& ser_file_path) {

	using namespace std;
	using namespace filesystem;

	if (!exists(ser_file_path))return;

	ifstream ser_file{ ser_file_path, ios::in | ios::binary };

	if (!ser_file.is_open())
		throw PaintCanvasException{ u8"Opening serialization file error." };

	//				  |						 Figure						 |
	// _______ _______|__________ _______ _______ ______________ ________|    _________ ______
	//|pointer|canvas |figure    |figure |UIInfo |UIInfo |UIInfo |UIInfo |	 |figure   |canvas|
	//|pos	  |size   |name size |name   |number |pointer|		 |		 |	 |name size|size  |
	//|_______|_______|__________|_______|_______|_______|_______|_______|...|_________|______|
	//

	//Reading pointer
	signed int pointer = -1;
	ser_file.read(reinterpret_cast<char*>(&pointer), sizeof(signed int));

	//Reading canvas size
	Size canvas_size{};
	ser_file.read(reinterpret_cast<char*>(&canvas_size), sizeof Size);

	while (true) {

		try {

			Figure read_figure{};
			ser_file >> read_figure;
			figures_.push_back(std::move(read_figure));

		} catch (const FigureException& error) {

			if (error.What() == u8"Serialization file is empty.") {

				pointer_ = pointer;

				break;

			} else if (error.What() == u8"Figure reading error.") {

				figures_.clear();

				throw PaintCanvasException{ u8"Incorrect file format." };

			} if (error.What() == u8"There is no plugin with such name.") {
				
				--pointer;

				continue;
			}
		}

	}

}

void PaintCanvas::AddToBufferNewFigure(Figure&& figure)noexcept {

	figures_.push_back(std::move(figure));
	pointer_ = figures_.size() - 1;

}

#include <algorithm>

void PaintCanvas::DeleteFromBufferNotDrawnFigures()noexcept {

	//If pointer idicate last element don't do anything
	if (pointer_ == figures_.size() - 1)return;

	figures_.erase(figures_.begin() + (pointer_ + 1), figures_.end());

}

PaintCanvas::PaintCanvas(const HWND parent_hWnd)noexcept :
	Canvas{ },
	figures_{  },
	pointer_{ -1 },
	fill_color_{ Color{ 255, 255, 255 } },
	current_plugin_{ nullptr } {

	Canvas::Create(parent_hWnd);
	Canvas::Show(SW_SHOW);

}

void PaintCanvas::CurrentFigureStartDrawing(const UIInfo& ui_info) {

	if (current_plugin_ == nullptr) throw PaintCanvasException{ u8"Plugin didn't select." };

	Figure figure{ current_plugin_->GetFigure() };
	DeleteFromBufferNotDrawnFigures();
	AddToBufferNewFigure(std::move(figure));
	figures_.back().StartDrawing(*this, ui_info);


}

bool PaintCanvas::CurrentFigureDrawing(const UIInfo& ui_info) noexcept {

	if (figures_.back().Empty())
		figures_.back().StartDrawing(*this, ui_info);
	else
		return figures_.back().Draw(*this, ui_info);


	return false;
}

void PaintCanvas::CurrentFigureEndDrawing() noexcept {

	figures_.back().EndDrawing();

}

void PaintCanvas::DrawAllFigures() noexcept{

	Canvas::Fill(fill_color_);

	for (signed int figure = 0; figure <= pointer_; ++figure)
		figures_[figure].Draw(*this);
	
}

void PaintCanvas::Flush() noexcept {

	Canvas::Flush();

}

void PaintCanvas::ReturnBackFigureDrawing()noexcept {

	figures_.back().ReturnBack();

}

void PaintCanvas::ReturnForwardFigureDrawing() noexcept {

	figures_.back().ReturnForward();

}

void PaintCanvas::ReturnBack()noexcept {

	if (pointer_ == -1)return;

	Canvas::Fill(fill_color_);

	for (signed int figure_it = 0; figure_it < pointer_; ++figure_it)
		figures_[figure_it].Draw(*this);

	--pointer_;

}

void PaintCanvas::ReturnForward()noexcept {

	if (pointer_ == figures_.size() - 1)return;

	figures_[++pointer_].Draw(*this);

	Canvas::Flush();

}


PaintCanvas::~PaintCanvas()noexcept { }

void PaintCanvas::SetProcessActionsFunction(ProcessAction process_action)noexcept {

	process_action_ = process_action;

	Canvas::SetCanvasProc([this](Message& message)noexcept->bool {

		if (message.GetAction() == Action::Resized) {


		}

		return process_action_(*this, message);

		});

}
