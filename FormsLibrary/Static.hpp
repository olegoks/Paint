#pragma once

#ifndef STATIC_HPP
#define STATIC_HPP

#include <any>
#include <Windows.h>
#include <string>
#include <FormTypes.hpp>

class EXPIMP Static {
private:

	std::any impl_;

public:

	explicit Static();
	~Static()noexcept;
	void Create(const HWND parent_hWnd);
	void Show(int nCmdShow = SW_SHOW);
	void ChangeText(const std::wstring& text);
	void ChangePosition(const int x, const int y);
	void ChangeSize(const int width, const int height);
	int GetX()const noexcept;
	int GetY()const noexcept;
	int GetWidth()const noexcept;
	int GetHeight()const noexcept;

	void Destroy();

};

#endif //STATIC_HPP