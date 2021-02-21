#pragma once

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <Windows.h>

#include <string>
#include <string_view>
#include "Library/FormTypes.hpp"

class FormImpl final{
private:

	class Parametrs final {

	public:

		size_t width_;
		size_t height_;
		size_t x_;
		size_t y_;
		std::wstring title_;
		DWORD dwStyle_;
		DWORD ex_dwStyle_;
		std::wstring sz_class_name_;

		explicit Parametrs()noexcept :
			width_{ FormImpl::kDefaultWidth },
			height_{ FormImpl::kDefaultHeight },
			x_{ FormImpl::kDefaultX },
			y_{ FormImpl::kDefaultY },
			title_{ FormImpl::kDefaultTitle },
			dwStyle_{ FormImpl::kDefaultStyle },
			ex_dwStyle_{ FormImpl::kDefaultExStyle },
			sz_class_name_{ FormImpl::kClassName }{

		}

	};

	static const std::wstring kClassName;
	
	BITMAPINFO frame_info_;
	void InitFrameInfo(const size_t width, const size_t height)noexcept(true);

	HWND self_hWnd_;
	mutable HINSTANCE hInstance_;
	mutable HWND parent_hWnd_;
	HDC device_context_;
	Parametrs params_;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam);
	FormProc form_proc_;
	bool WasCreated()const noexcept(true);
	void RegisterFormClass(const std::wstring& class_name)noexcept(false);
	WPARAM StartMessageLoop()const noexcept(false);

public:

	//Window class constants
	static const std::wstring kDefaultTitle;
	static const std::size_t  kDefaultWidth;
	static const std::size_t  kDefaultHeight;
	static const std::size_t  kDefaultX;
	static const std::size_t  kDefaultY;
	static const DWORD		  kDefaultStyle;
	static const DWORD		  kDefaultExStyle;

public:

	explicit FormImpl()noexcept(true);
	~FormImpl()noexcept(true);

public:

	void Create(const std::wstring& class_name, const HWND parent_hWnd = NULL)noexcept(false);
	void Show(int nCmdShow)noexcept(false);
	void Run()noexcept(false);
	void Destroy()noexcept(false);

	void Caption(const std::wstring& caption)noexcept(false);
	const HWND Handle()const noexcept(true);
	void InitFormProc(FormProc messages_processing)noexcept(true);
	void Position(const int x, const int y)noexcept(false);
	void Size(const size_t width, const size_t height)noexcept(false);
	
	int Width()const noexcept(true);
	int Height()const noexcept(true);
	int X()const noexcept(true);
	int Y()const noexcept(true);

	void Style(DWORD ex_dwStyle, DWORD dwStyle)noexcept(false);
	void ShowFrame(const void* const frame)noexcept(false);

};

#endif // !_WINDOW_HPP_