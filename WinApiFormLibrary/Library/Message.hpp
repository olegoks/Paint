#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <windows.h>
#include <windowsx.h>
#include <cstdint>

#define VK_A 65
#define VK_B 66
#define VK_D 68
#define VK_W 87
#define VK_S 83

enum class Key : unsigned int {

	Nothing = 0,
	ArrowLeft,
	ArrowRight,
	ArrowUp,
	ArrowDown,
	WheelDown,
	WheelUp,
	MouseLeft,
	MouseRight,
	A,
	S,
	D,
	W

};

enum class Action : unsigned int {

	Nothing = 0,
	KeyDown,
	KeyUp,
	MouseMove,
	LMouseDown,
	LMouseUp,
	RMouseDown,
	RMouseUp,
	MenuControlAccel,
	ButtonClicked,
	Resized,
	PositionChanged,
	PositionChanging,
	Repaint,
	Close
	

};

enum class ActionType :unsigned int {

	Mouse = 0,
	Keyboard,
	Menu,
	Control,
	Accelerator,
	Nothing

};

class KeyAction final {
public:

	Key key_;
	Action action_;

	explicit KeyAction()noexcept(true);

	explicit KeyAction(Key key, Action action)noexcept(true);

};

struct Message {

private:

	KeyAction key_action_;

	UINT message_;
	WPARAM wParam_;
	LPARAM lParam_;

	int x_;
	int y_;
	int control_id_;
	HWND hWnd_;
	ActionType action_type_;

public:

	explicit Message(UINT Message, WPARAM wParam, LPARAM lParam)noexcept(true);

public:

	void Coordinats(int x, int y)noexcept(true) {

		x_ = x;
		y_ = y;

	}

	ActionType GetActionType()const noexcept { return action_type_; };
	Action GetAction()const noexcept(true) { return key_action_.action_; };
	Key GetKey()const noexcept(true) { return key_action_.key_; };
	HWND GethWnd()const noexcept(true) { return hWnd_; };
	int GetControlId()const noexcept(true) { return control_id_; };
	std::uint64_t GetLParam()const noexcept { return lParam_; };
	std::uint64_t GetWParam()const noexcept { return wParam_; }
	int GetX()const noexcept(true) { return x_; }
	int GetY()const noexcept(true) { return y_; }

};

#include <functional>

using ProcessMessage = std::function<bool(Message&)>;


#endif //MESSAGE_HPP