#pragma once
#ifndef WINDOW_INTERFACE_HPP
#define WINDOW_INTERFACE_HPP

#include <windows.h>
#include <any>

#include "FormTypes.hpp"

class EXPIMP Form{
private:

	std::any impl_;

public:

	explicit Form();
	~Form()noexcept;

protected:

	void Create(const HWND parent_hWnd = NULL);
	void Show(int nCmdShow);
	void Run();
	void Destroy();

public:

	void ChangeCaption(const std::wstring& caption);
	const HWND GetHandle()const noexcept;
	void SetProcessFunction(ProcessMessage messages_processing)noexcept;
	void ChangeSize(const int width, const int height);
	int GetWidth()const noexcept;
	int GetHeight()const noexcept;
	int GetX()const noexcept;
	int GetY()const noexcept;

	void ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle);
	void ChangePosition(int x, int y);

};

#endif //WINDOW_INTERFACE_HPP