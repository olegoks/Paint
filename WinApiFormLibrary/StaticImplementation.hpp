#pragma once

#ifndef STATICIMPLEMENTATION_HPP
#define STATICIMPLEMENTATION_HPP

#include <AbstractComponent.hpp>

class StaticImplementation : public AbstractComponent {

public:

	explicit StaticImplementation():
		AbstractComponent::AbstractComponent{}{

		try {
		
			AbstractComponent::ChangeStyle(NULL, WS_CHILD | WS_VISIBLE);
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Static changing style exception." };

		}

	}

	void Create(const HWND parent_hWnd)override {

		try {
		
			AbstractComponent::CreateComponent(parent_hWnd, L"Static");
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Creating static error." };

		}

	}

	void Show(int nCmdShow = SW_SHOW)override {

		try {
		
			AbstractComponent::ShowComponent(nCmdShow);
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Show static error." };

		}

	}
	

	void Destroy()override {

		try {
		
			AbstractComponent::DestroyComponent();
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Destroying static error." };

		}

	}

};

#endif //STATICIMPLEMENTATION_HPP