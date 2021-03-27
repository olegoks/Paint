#pragma once

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <Windows.h>
#include "Library/FormTypes.hpp"
#include "AbstractComponent.hpp"

class FormImplementation : public AbstractComponent{
private:

	WPARAM StartMessageLoop()const noexcept(false);

public:

	explicit FormImplementation()noexcept;
	~FormImplementation()noexcept;

public:

	HWND GetHandle()const noexcept;
	void ChangeCaption(const std::wstring& new_caption);
	void Create(const HWND parent_hWnd = NULL)override;
	void Show(int nCmdShow = SW_SHOWNORMAL)override;
	void Destroy()override;
	void Run();

};

#endif // !_WINDOW_HPP_