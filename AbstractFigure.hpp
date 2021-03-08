#pragma once

#ifndef ABSTRACTFIGURE_HPP
#define ABSTRACTFIGURE_HPP

#include "CanvasCommand.hpp"

class FigureInfo final {
private:
public:

	Coordinats left_bottom_;
	Coordinats right_top_;
	const Color color_;

	explicit FigureInfo(const FigureInfo& pos_size)noexcept = default;
	explicit FigureInfo(FigureInfo&& pos_size)noexcept = delete;
	FigureInfo& operator=(const FigureInfo& pos_size) = default;
	FigureInfo& operator=(FigureInfo&& pos_size) = delete;

	explicit FigureInfo(const Coordinats& left_bottom, const Coordinats& right_top, const Color& color)noexcept:
		left_bottom_{ left_bottom }, right_top_{ right_top }, color_{ color } {}
	
	explicit FigureInfo()noexcept:
		FigureInfo{ Coordinats{ 0, 0 }, Coordinats{ 0, 0 }, Color{ 0, 0 ,0 } } {}

	~FigureInfo()noexcept = default;

};

#include <memory>
using CommandsBuffer = std::vector<AbstractCanvasCommand*>;

class AbstractFigure {
private:

	CommandsBuffer commands_;

protected:

	void Command(AbstractCanvasCommand* const command)noexcept {

		commands_.push_back(command);

	}

	void ClearCommandsBuffer()noexcept {

		for (auto command_ptr : commands_)
			if (command_ptr != nullptr)
				delete command_ptr;

	}

public:

	explicit AbstractFigure()noexcept { }

	CommandsBuffer& GetCommands()noexcept { return commands_; }
	virtual void SetParametrs(const FigureInfo& info) = 0;

	void Draw(Canvas& canvas) {

		for (auto& command : commands_)
			command->Execute(canvas);

	}

};

class SolidRectangleFigure : public AbstractFigure {
private:


public:

};

#include <array>

class RectangleFigure : public AbstractFigure {
private:
public:

	explicit RectangleFigure(const FigureInfo& info):
		AbstractFigure::AbstractFigure{}{ 

		Coordinats left_top{ info.left_bottom_.X(), info.right_top_.Y() };
		Coordinats right_bottom{ info.right_top_.X(), info.left_bottom_.Y() };

		try {

			Command(new SolidLineCanvasCommand{ info.left_bottom_, left_top, info.color_ });
			Command(new SolidLineCanvasCommand{ left_top, info.right_top_, info.color_ });
			Command(new SolidLineCanvasCommand{ info.right_top_, right_bottom, info.color_ });
			Command(new SolidLineCanvasCommand{ right_bottom, info.left_bottom_, info.color_ });

		} catch (const std::bad_alloc& exception) {

			ClearCommandsBuffer();

			throw 1;

		}
	
	}

	virtual void SetParametrs(const FigureInfo& info) = 0;

};

enum class PluginType : uint64_t {

	NOTHING = 0,
	FIGURE,
	COLOR

};

#endif //ABSTRACTFIGURE_HPP