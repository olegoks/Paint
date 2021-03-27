#pragma once



#ifndef EDITIMPLEMENTATION_HPP
#define EDITIMPLEMENTATION_HPP

#include <string>
#include <AbstractComponent.hpp>

class EditImplementation : public AbstractComponent {
public:
	
	explicit EditImplementation(){

		try {
		
			AbstractComponent::ChangeStyle(NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER | ES_LEFT);
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Changing style for edit error." };

		}

	}

	void Create(const HWND parent_hWnd = NULL)override {

		try {

			AbstractComponent::CreateComponent(parent_hWnd, L"edit");
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Creating edit exception." };

		}

	}

	void Show(int nCmdShow = SW_SHOW)override {
		
		try {
		
			AbstractComponent::ShowComponent(SW_SHOW);
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Edit show error." };

		}

	}

	std::string GetText()const {

		char text[256];

		int success = GetWindowTextA(AbstractComponent::GetHandle(), text, 256);

		if (!success)
			throw ComponentException{ u8"GetWindowText error." };

		return std::string{ text };

	}

	void Destroy()override {

		try {
			
			AbstractComponent::DestroyComponent();

		} catch (const ComponentException&) {

			throw ComponentException{ u8"Destroying edit error." };

		}

	}

};

#endif //EDITIMPLEMENTATION_HPP