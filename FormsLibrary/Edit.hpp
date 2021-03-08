#pragma once

#ifndef EDIT_HPP
#define EDIT_HPP

#include <any>
#include <FormTypes.hpp>

class EXPIMP Edit {
private:

	std::any impl_;

public:

	explicit Edit();
	~Edit()noexcept;

	void SetProcessFunction(ProcessMessage process_message)noexcept;
	std::string GetText()const;
	void ChangeText(const std::wstring& text);
	void ChangeSize(const int width, const int height);
	void ChangePosition(const int x, const int y);
	int GetHeight()const noexcept;
	int GetWidth()const noexcept;
	int GetX()const noexcept;
	int GetY()const noexcept;
	void Create(const HWND parent_hWnd = NULL);
	void Show(int nCmdShow = NULL);
	void Destroy();

};

#endif //EDIT_HPP