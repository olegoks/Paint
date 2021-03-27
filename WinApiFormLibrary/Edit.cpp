#include "Edit.hpp"
#include <EditImplementation.hpp>

Edit::Edit() :impl_{ } {

	try {

		impl_ = new EditImplementation{};

	} catch (const std::bad_alloc&) {
	
		throw ComponentException{ u8"Edit allocation memory exception." };
	
	}

}

Edit::~Edit() noexcept{

	if (impl_.has_value())
		delete std::any_cast<EditImplementation*>(impl_);

}

Edit::Edit(Edit&& move_edit) noexcept:
	impl_{ } {

	std::swap(impl_, move_edit.impl_);

}

Edit& Edit::operator=(Edit&& move_edit) noexcept{

	if (&move_edit == this) return *this;

	std::swap(impl_, move_edit.impl_);

	return *this;

}

void Edit::SetProcessFunction(ProcessMessage process_message) noexcept{

	std::any_cast<EditImplementation*>(impl_)->SetProcessFunction(process_message);

}

std::string Edit::GetText() const {

	return std::any_cast<EditImplementation*>(impl_)->GetText();

}

void Edit::ChangeText(const std::wstring& text){

	std::any_cast<EditImplementation*>(impl_)->ChangeText(text);

}

void Edit::ChangeSize(const uint64_t width, const uint64_t height){

	std::any_cast<EditImplementation*>(impl_)->ChangeSize(width, height);

}

void Edit::ChangePosition(const uint64_t x, const uint64_t y){

	std::any_cast<EditImplementation*>(impl_)->ChangePosition(x, y);

}

int Edit::GetHeight() const noexcept{

	return std::any_cast<EditImplementation*>(impl_)->GetHeight();
}

int Edit::GetWidth() const noexcept{

	return std::any_cast<EditImplementation*>(impl_)->GetWidth();
}

int Edit::GetX() const noexcept{

	return std::any_cast<EditImplementation*>(impl_)->GetX();
}

int Edit::GetY() const noexcept{

	return std::any_cast<EditImplementation*>(impl_)->GetY();
}

void Edit::Create(const HWND parent_hWnd){

	std::any_cast<EditImplementation*>(impl_)->Create(parent_hWnd);

}

void Edit::Show(int nCmdShow){

	std::any_cast<EditImplementation*>(impl_)->Show(nCmdShow);

}

void Edit::Destroy(){

	std::any_cast<EditImplementation*>(impl_)->Destroy();

}
