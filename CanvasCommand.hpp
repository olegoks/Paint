#pragma once
#ifndef CANVASCOMMAND_HPP
#define CANVASCOMMAND_HPP

#include <cstdint>
using std::uint64_t;

#include <FormsLibrary.hpp>

class Coordinats final {
private:

	const uint64_t x_;
	const uint64_t y_;

public:

	explicit Coordinats(const uint64_t x, const uint64_t y)noexcept :
		x_{ x }, y_{ y }{}

	explicit Coordinats()noexcept :
		Coordinats{ 0, 0 } {}

	~Coordinats()noexcept = default;

	inline const uint64_t X()const noexcept { return x_; };
	inline const uint64_t Y()const noexcept { return y_; };

};

enum class CommandType : uint64_t {

	NOTHING = 0,
	LINE,
	FILL,
	POINT

};

class AbstractCanvasCommand {
private:

	const uint64_t command_size_;
	CommandType command_;

public:

	explicit AbstractCanvasCommand(const uint64_t command_size, const CommandType& command)noexcept :
		command_size_{ command_size }, command_{ command } {};

	virtual void Execute(Canvas& canvas)const = 0;

};

class SolidLineCanvasCommand : public AbstractCanvasCommand {
private:

	Coordinats begin_;
	Coordinats end_;
	Color color_;

public:

	explicit SolidLineCanvasCommand(const Coordinats& begin, const Coordinats& end, const Color& color)noexcept :
		AbstractCanvasCommand{ sizeof SolidLineCanvasCommand, CommandType::LINE },
		begin_{ begin }, end_{ end }, color_{ color }{}

	virtual void Execute(Canvas& canvas)const override {
	
		const uint64_t width = canvas.GetWidth();
		const uint64_t height = canvas.GetHeight();

		canvas.Line(begin_.X(), begin_.Y(), end_.X(), end_.Y(), color_);

	}

	~SolidLineCanvasCommand()noexcept = default;

};

class PointCanvasCommand : public AbstractCanvasCommand {
private:

	Coordinats coord_;
	Color color_;

public:

	explicit PointCanvasCommand(const Coordinats& begin, const Color color)noexcept :
		AbstractCanvasCommand{ sizeof PointCanvasCommand, CommandType::POINT }, color_{ color }{}

	virtual void Execute(Canvas& canvas)const override {

		canvas.SetPixel(coord_.X(), coord_.Y(), color_);

	}

};

class FillCanvasCommand : public AbstractCanvasCommand {
private:

	Color color_;

public:

	explicit FillCanvasCommand(const Color& color)noexcept :
		AbstractCanvasCommand{ sizeof FillCanvasCommand, CommandType::FILL },
		color_{ color }{}

	void Execute(Canvas& canvas)const noexcept {

		canvas.Fill(color_);

	}

};


#endif CANVASCOMMAND_HPP