#pragma once
#ifndef WINDOW_TYPES_HPP
#define WINDOW_TYPES_HPP

#include <windows.h>
#include <Windowsx.h>
#include <functional>
#include <exception>

#define CALLBACK __stdcall

#define COMPILING_DLL

#ifdef COMPILING_DLL
#define EXPIMP __declspec(dllexport)
#else
#define EXPIMP __declspec(dllimport)
#endif

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
		ButtonClicked

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

	public:

		explicit Message(UINT Message, WPARAM wParam, LPARAM lParam)noexcept(true);

	public:

		void Coordinats(int x, int y)noexcept(true) {

			x_ = x;
			y_ = y;

		}
		
		Action GetAction()const noexcept(true) { return key_action_.action_; };
		Key GetKey()const noexcept(true) { return key_action_.key_; };
		HWND GethWnd()const noexcept(true) { return hWnd_; };
		int GetControlId()const noexcept(true) { return control_id_; };

		int GetX()const noexcept(true) { return x_; }
		int GetY()const noexcept(true) { return y_; }

	};

	class FormExcep final : protected std::exception {
	private:

		std::string message_;

	public:

		explicit FormExcep(std::string&& message)noexcept(true) :
			std::exception{ },
			message_{ std::move( message ) } {

		

		}

		explicit FormExcep(const std::string& message)noexcept(true):
			std::exception{},
			message_{ message }{


		}

		const std::string& What()const noexcept(true) { return message_; };

	};

	using FormProc = std::function<bool(Message&)>;

	class Pixel final {
	public:

		explicit Pixel(unsigned char r, unsigned char g, unsigned char b)noexcept(true) :
			rgba_{ 0 } {

			rgba_.r = r;
			rgba_.g = g;
			rgba_.b = b;

		}

		explicit Pixel()noexcept(true) :
			Pixel{ 0, 0, 0 } {

		}

		union rgba {

			unsigned char bgra[4];
			
			struct {
				
				unsigned char b;
				unsigned char g;
				unsigned char r;
				unsigned char a;

			};

		};

		rgba rgba_ = { 0 };

	};

#endif //WINDOW_TYPES_HPP