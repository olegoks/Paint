#include "Library/Form.hpp"
#include "FormImpl.hpp"

Form::Form() noexcept(true):
	impl_{ nullptr } {

	try {

		impl_ = new FormImpl{};

	} catch (const std::bad_alloc& exception) { }

}

Form::~Form()noexcept(true){

	if (std::any_cast<FormImpl*>(impl_) != nullptr)
		delete std::any_cast<FormImpl*>(impl_);
	
}
void Form::Create(const std::wstring& class_name, const HWND parent_hWnd) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Create(class_name, parent_hWnd);

}

void Form::Show(int nCmdShow) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Show(nCmdShow);

}

void Form::Run() noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Run();

}

void Form::Destroy() noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Destroy();

}

void Form::ShowFrame(const void* const frame_buffer) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->ShowFrame(frame_buffer);

}

void Form::Caption(const std::wstring& caption) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Caption(caption);

}

const HWND Form::Handle() const noexcept(true){
	
	return std::any_cast<FormImpl*>(impl_)->Handle();

}

void Form::InitFormProc(FormProc messages_processing) noexcept(true){

	std::any_cast<FormImpl*>(impl_)->InitFormProc(messages_processing);

}

void Form::Size(const size_t width, const size_t height) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Size(width, height);

}

EXPIMP int Form::Width() const noexcept(true){

	return std::any_cast<FormImpl*>(impl_)->Width();
}

EXPIMP int Form::Height() const noexcept(true)
{
	return std::any_cast<FormImpl*>(impl_)->Height();
}

EXPIMP int Form::X() const noexcept(true)
{
	return std::any_cast<FormImpl*>(impl_)->X();
}

EXPIMP int Form::Y() const noexcept(true)
{
	return std::any_cast<FormImpl*>(impl_)->Y();
}

void Form::Style(DWORD ex_dwStyle, DWORD dwStyle) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Style(ex_dwStyle, dwStyle);

}

EXPIMP void Form::Position(int x, int y) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Position(x, y);

}

