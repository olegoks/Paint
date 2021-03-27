#pragma once

#include <filesystem>
#include <AbstractComponent.hpp>

class ButtonImplementation : public AbstractComponent {
private:

	HBITMAP hBitmap_;

public:

	ButtonImplementation():
		AbstractComponent::AbstractComponent{},
		hBitmap_{ NULL }{

		try {

			AbstractComponent::ChangeStyle(NULL, BS_DEFPUSHBUTTON | WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER);
		
		}
		catch  (const ComponentException&) {

			throw ComponentException{ u8"Set button style exception." };

		}

	}

	void Image(const std::wstring& bitmap_path) {

		if (!WasCreated()) 
			throw ComponentException{ u8"Button was no created." };

		hBitmap_ = (HBITMAP)LoadImage(NULL, bitmap_path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

		if (hBitmap_ == NULL)
			throw ComponentException{ u8"LoadImage error." };
		
		DWORD current_style = AbstractComponent::GetStyle();
		DWORD current_ex_style = AbstractComponent::GetExtendedStyle();
			
		try {
			
			AbstractComponent::ChangeStyle(current_ex_style, current_ex_style | BS_BITMAP );
			
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Changing button style for loading image error." };

		}

		SendMessageA(GetHandle(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap_);
		AbstractComponent::ShowComponent();
		
	}

	void ChangeText(const std::wstring& text) {

		try {
		
			AbstractComponent::ChangeText(text);
			
		} catch (ComponentException& exception) {
			 
			throw ComponentException{ std::move(exception) };

		}

	}

	void Create(const HWND parent_hWnd = NULL)override {
		
		try {
		
			AbstractComponent::CreateComponent(parent_hWnd, L"Button");
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Creating button error." };

		}

		if (hBitmap_ != NULL) {
		
			LRESULT result = SendMessage(AbstractComponent::GetHandle(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap_);
		
		}
	}

	HWND GetHandle()const noexcept {

		return AbstractComponent::GetHandle();

	}

	void Show(int nCmdShow = SW_SHOWNORMAL)override {

		ShowWindow(AbstractComponent::GetHandle(), nCmdShow);

	}

	void Destroy()override {

		try {
		
			AbstractComponent::DestroyComponent();
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Destroying button error." };

		}

	}

};