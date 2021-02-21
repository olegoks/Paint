#pragma once

#include "FormTypes.hpp"
#include <filesystem>

EXPIMP class Button  {
private:
	
	static const inline std::wstring kDefaultText = L"Click me!";

	const HINSTANCE hInstance_;
	HWND self_hWnd_;
	HWND parent_hWnd_;
	std::wstring text_;
	int pos_x_;
	int pos_y_;
	int width_;
	int height_;
	FormProc proc_;
	HBITMAP hBitmap_;

public:

	EXPIMP Button(Button&& button)noexcept(true) = default;

	EXPIMP Button()noexcept(true):
		hInstance_{ GetModuleHandleW(NULL) },
		self_hWnd_{ NULL },
		parent_hWnd_{ NULL },
		pos_x_{ 0 },
		pos_y_{ 0 },
		width_{ 80 },
		height_{ 60 },
		proc_{ [](Message& message)noexcept->bool { return false; } },
		hBitmap_{ NULL }{

	}

	Button& operator=(Button&& button)noexcept(true) = default;

	EXPIMP void Position(const int x, const int y)noexcept(true) {

		if (self_hWnd_ != NULL) {

			BOOL success = SetWindowPos(self_hWnd_, NULL, x, y, width_, height_, NULL);

			if (!success)
				throw FormExcep{ u8"SetWindowPos error." };

		}

		pos_x_ = x;
		pos_y_ = y;

	}

	EXPIMP void Size(const int width, const int height)noexcept(false) {

		if (self_hWnd_ != NULL) {

			BOOL success = SetWindowPos(self_hWnd_, NULL, pos_x_, pos_y_, width, height, SWP_NOZORDER);

			if (!success)
				throw FormExcep{ u8"SetWindowPos error." };

		}

		width_ = width;
		height_ = height;

	}

	EXPIMP void Text(const std::wstring& text)noexcept(false) {

		if (self_hWnd_ != NULL) {

			BOOL success = SetWindowText(self_hWnd_, text.c_str());

			if (!success)
				throw FormExcep{ u8"SetWindowText error." };

		}

		text_ = text;

	}

	EXPIMP void Image(const std::wstring& bitmap_path)noexcept(false) {

		hBitmap_ = (HBITMAP)LoadImage(NULL, bitmap_path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

		if (hBitmap_ == NULL)
			throw FormExcep{ u8"LoadImage error." };

		if (self_hWnd_ != NULL)
			SendMessage(self_hWnd_, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap_);

	}

	EXPIMP void Create(const HWND parent_hWnd, const std::wstring text = kDefaultText)noexcept(false) {

		self_hWnd_ = CreateWindow(L"Button", text.c_str(), BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | BS_BITMAP,
			pos_x_, pos_y_, width_, height_,
			parent_hWnd, NULL, hInstance_, NULL);

		if (self_hWnd_ == NULL)
			throw FormExcep{ u8"Creating button exception." };
		
		#ifdef _M_X64
			#define BindPointerToForm SetWindowLongPtr
			using PointerType = LONG_PTR;
			using ValueType = LONG_PTR;	
		#else
			#define BindPointerToForm SetFormLong
			using PointerType = LONG;
			using ValueType = LONG;
		#endif

			SetLastError(NULL);
			int last_value = BindPointerToForm(self_hWnd_, GWLP_USERDATA, reinterpret_cast<PointerType>(this));

			//Pointer linked to the Form
			//SetFormLongPtr return previous value or zero, if error, but if last value is 0, we should check last error

			if (last_value == 0) {

				DWORD error = GetLastError();

				if (error != 0)
					throw FormExcep{ u8"Creating button exception." };

			}

			if(hBitmap_ != NULL)
				SendMessage(self_hWnd_, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap_);

	}

	EXPIMP void Show()noexcept(false) {

		ShowWindow(self_hWnd_, SW_SHOWNORMAL);

	}

	EXPIMP void InitButtonProc(FormProc process_messages)noexcept(true) {

		proc_ = process_messages;

	}

	friend class FormImpl;

};