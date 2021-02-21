#pragma once
#ifndef WINDOW_INTERFACE_HPP
#define WINDOW_INTERFACE_HPP

#include <windows.h>
#include <any>

#include "FormTypes.hpp"

EXPIMP class Form {
private:

	std::any impl_;

public:

	EXPIMP explicit Form()noexcept(true);
	EXPIMP ~Form()noexcept(true);

protected:

	//void RegisterFormClass(const std::wstring& class_name)noexcept(false);
	EXPIMP void Create(const std::wstring& class_name, const HWND parent_hWnd = NULL)noexcept(false);
	EXPIMP void Show(int nCmdShow)noexcept(false);
	EXPIMP void Run()noexcept(false);
	EXPIMP void Destroy()noexcept(false);
	EXPIMP void ShowFrame(const void* const frame_buffer)noexcept(false);

public:

	EXPIMP void Caption(const std::wstring& caption)noexcept(false);
	EXPIMP const HWND Handle()const noexcept(true);
	EXPIMP void InitFormProc(FormProc messages_processing)noexcept(true);
	EXPIMP void Size(const size_t width, const size_t height)noexcept(false);
	EXPIMP int Width()const noexcept(true);
	EXPIMP int Height()const noexcept(true);
	EXPIMP int X()const noexcept(true);
	EXPIMP int Y()const noexcept(true);

	EXPIMP void Style(DWORD ex_dwStyle, DWORD dwStyle)noexcept(false);
	EXPIMP void Position(int x, int y)noexcept(false);

};

#endif //WINDOW_INTERFACE_HPP