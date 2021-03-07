#pragma once

#ifndef ABSTRACTFIGURE_HPP
#define ABSTRACTFIGURE_HPP

#include "Canvas.hpp"

#include <cstdint>
using std::uint64_t;

class Coordinats {
private:

	const uint64_t x_;
	const uint64_t y_;

public:

	explicit Coordinats(const uint64_t x, const uint64_t y)noexcept:
		x_{ x }, y_{ y }{}

	explicit Coordinats()noexcept:
		Coordinats{ 0, 0 } {}

	~Coordinats()noexcept = default;

};

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

enum class CommandType : uint64_t {

	NOTHING = 0,
	LINE,
	FILL,
	POINT

};

//class AbstractCanvasCommand {
//private:
//
//	CommandType command_;
//
//public:
//
//	explicit AbstractCanvasCommand(CommandType command)noexcept :
//		command_{ command } {}
//
//	virtual void Execute(Canvas& canvas) = 0;
//	inline CommandType GetCommandType()const noexcept { return command_; };
//
//};

class CanvasCommand{
private:

	CommandType command_;
	Coordinats begin_;
	Coordinats end_;
	Color color_;

public:

	explicit CanvasCommand(const CommandType command, const Coordinats& begin, const Coordinats& end, const Color color)noexcept :
		begin_{ begin }, end_{ end }, color_{ color }{ }

	explicit CanvasCommand(const CommandType command, const Coordinats& coordinats, const Color color)noexcept:
		CanvasCommand::CanvasCommand{ command, coordinats, Coordinats{ 0, 0 }, color_{ color }{}

};

#include <memory>

class AbstractFigure {
private:

	std::vector<CanvasCommand> commands_;

protected:

	void Command(const CanvasCommand& command)noexcept {

		commands_.push_back(std::move(command));

	}

public:

	explicit AbstractFigure()noexcept {



	}

	//Draw figure on canvas without calling flush
	virtual void Draw(Canvas& canvas, const FigureInfo& pos_size) = 0;
	
};

#include <array>

class RectangleFigure : public AbstractFigure {
private:

public:

	explicit RectangleFigure():
		AbstractFigure::AbstractFigure{}{ }
	
	void Draw(Canvas& canvas, const FigureInfo& info)noexcept {

		

	}


};

#endif //ABSTRACTFIGURE_HPP