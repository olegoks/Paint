#pragma once
#ifndef WINDOW_INTERFACE_HPP
#define WINDOW_INTERFACE_HPP

#include <windows.h>
#include <any>
#include "FormTypes.hpp"

class EXPIMP::std::any;

class EXPIMP Form{
private:

	std::any impl_;

public:

	explicit Form();
	~Form()noexcept;

	explicit Form(Form&& move_form)noexcept;
	explicit Form(const Form& copy_form)noexcept = delete;

	Form& operator=(Form&& move_form)noexcept;
	Form& operator=(const Form& copy_form)noexcept = delete;

protected:

	void Create(const HWND parent_hWnd = NULL);
	void Show(int nCmdShow);
	void Run();
	void Destroy();

public:

	void ChangeCaption(const std::wstring& caption);
	const HWND GetHandle()const noexcept;
	void SetProcessFunction(ProcessMessage messages_processing)noexcept;
	void ChangeSize(const uint64_t width, const uint64_t height);
	int GetWidth()const noexcept;
	int GetHeight()const noexcept;
	int GetX()const noexcept;
	int GetY()const noexcept;

	void ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle);
	void ChangePosition(uint64_t x, uint64_t y);

};

#endif //WINDOW_INTERFACE_HPP