#include "Component.hpp"
#include "FormTypes.hpp"

Component::Component() noexcept(true):
	 { 
		
	if (message.GetAction() == Action::ButtonClicked) {
		MessageBoxA(NULL, u8"Button message", u8"Button clicked", MB_OK);
		return true;
	}
		return false; 

	} } {

}

void Component::RegClass(const std::wstring& class_name) noexcept(false){



}




void Component::Create(const HWND parent_hWnd) noexcept(false){



}

void Component::Show(int nCmdShow) noexcept(false){



}

void Component::Destroy() noexcept(false){



}

Component::~Component() noexcept(true){

}



