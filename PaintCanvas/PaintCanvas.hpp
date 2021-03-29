#pragma once
#ifndef PAINTCANVAS_HPP
#define PAINTCANVAS_HPP

#include <functional>
#include <stack>
#include <filesystem>
namespace fs = std::filesystem;

#include <fstream>
#include <memory>
#include <Canvas.hpp>

#include "PluginsManager.hpp"
#include "Exception.hpp"
#include "PaintFigure.hpp"

using PaintCanvasException = Exception;

class PaintCanvas : public Canvas {
public:

	using ProcessAction = std::function<bool(PaintCanvas& canvas, Message& message)>;

private:

	using FiguresBuffer = std::vector<Figure>;

	FiguresBuffer figures_;
	ProcessAction process_action_;
	//FiguresBuffer::iterator pointer_;
	signed int pointer_;
	Color fill_color_;
	const Plugin* current_plugin_;

	using Canvas::Create;
	using Canvas::Destroy;
	using Canvas::SetCanvasProc;
	using Canvas::Show;
	using Canvas::Flush;

	static const inline std::string serialization_file_name = u8"ser";

private:

	void AddToBufferNewFigure(Figure&& figure)noexcept;
	void DeleteFromBufferNotDrawnFigures()noexcept;

public:

	explicit PaintCanvas(const HWND parent_hWnd)noexcept;
	
	void ChangeFigureToDraw(const Plugin& plugin)noexcept;
	bool ThereIsFigureToDraw()const noexcept;

	void StartDraw(const UIInfo& ui_info);
	bool Draw(const UIInfo& parametrs)noexcept;
	void EndDraw()noexcept;

	void Serialize(const fs::path& ser_file_path);
	void Deserialize(const fs::path& ser_file_path);

	void ReturnBackFigureDrawing()noexcept;
	void ReturnForwardFigureDrawing()noexcept;
	void ReturnBack()noexcept;
	void ReturnForward()noexcept;

	void SetProcessActionsFunction(ProcessAction process_action)noexcept;

	const uint64_t GetWidth()const noexcept { return Canvas::GetWidth(); }
	const uint64_t GetHeight()const noexcept { return Canvas::GetHeight(); }

	void Flush()noexcept;

	~PaintCanvas()noexcept;

};

#endif //PAINTCANVAS_HPP