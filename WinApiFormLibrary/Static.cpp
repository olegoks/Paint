#include "Static.hpp"

#include <StaticImplementation.hpp>

Static::Static():
	impl_{ } {

	try {

		impl_ = new StaticImplementation{};

	} catch (const std::bad_alloc&) {

		throw ComponentException{ u8"Static allocation memory error." };

	}

}

Static::~Static() noexcept{

	if (std::any_cast<StaticImplementation*>(impl_) != nullptr)
		delete std::any_cast<StaticImplementation*>(impl_);

}

Static::Static(Static&& move_static) noexcept:
	impl_{ } {

	std::swap(impl_, move_static.impl_);

}

Static& Static::operator=(Static&& move_static) noexcept{

	if (&move_static == this) return *this;

	std::swap(impl_, move_static.impl_);

	return *this;

}

void Static::Create(const HWND parent_hWnd){

	std::any_cast<StaticImplementation*>(impl_)->Create(parent_hWnd);

}

void Static::Show(int nCmdShow){

	std::any_cast<StaticImplementation*>(impl_)->Show(nCmdShow);

}

void Static::ChangeText(const std::wstring& text){

	std::any_cast<StaticImplementation*>(impl_)->ChangeText(text);

}

void Static::ChangePosition(const uint64_t x, const uint64_t y){

	std::any_cast<StaticImplementation*>(impl_)->ChangePosition(x, y);

}

void Static::ChangeSize(const uint64_t width, const uint64_t height){

	std::any_cast<StaticImplementation*>(impl_)->ChangeSize(width, height);

}

int Static::GetX() const noexcept{

	return std::any_cast<StaticImplementation*>(impl_)->GetX();
}

int Static::GetY() const noexcept{

	return std::any_cast<StaticImplementation*>(impl_)->GetY();
}

int Static::GetWidth() const noexcept{

	return std::any_cast<StaticImplementation*>(impl_)->GetWidth();
}

int Static::GetHeight() const noexcept{

	return std::any_cast<StaticImplementation*>(impl_)->GetHeight();
}

void Static::Destroy(){

	std::any_cast<StaticImplementation*>(impl_)->Destroy();

}
