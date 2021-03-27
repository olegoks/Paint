#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <any>
#include <FormTypes.hpp>
#include <cstdint>
using std::uint64_t;
class EXPIMP::std::any;

class EXPIMP Button {
private:

	std::any impl_;

public:

	explicit Button();
	~Button()noexcept;

	explicit Button(const Button& copy_button)noexcept = delete;
	explicit Button(Button&& move_button)noexcept;

public:

	Button& operator=(const Button& copy_button)noexcept = delete;
	Button& operator=(Button&& move_button)noexcept;

	void SetProcessFunction(ProcessMessage messages_processing)noexcept;
	void ChangeSize(const uint64_t width, const uint64_t height);
	void ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle);
	void ChangePosition(const uint64_t x, const uint64_t y);
	bool WasCreated()const noexcept;
	
	HWND GetHandle()const noexcept;
	int GetHeight()const noexcept;
	int GetWidth()const noexcept;
	int GetX()const noexcept;
	int GetY()const noexcept;

	void Image(const std::wstring& bitmap_path);
	void ChangeText(const std::wstring& text);
	void Create(const HWND parent_hWnd = NULL);
	void Show(int nCmdShow = SW_SHOWNORMAL);
	void Destroy();

};

#endif //BUTTON_HPP