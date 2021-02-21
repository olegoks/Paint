#include "FormImpl.hpp"

#include <chrono>
#include <Button.hpp>

//Form constants
const std::wstring FormImpl::kDefaultTitle{ L"Default Form title" };
const std::size_t  FormImpl::kDefaultWidth{ 1920 };
const std::size_t  FormImpl::kDefaultHeight{ 1080 };
const std::size_t  FormImpl::kDefaultX{ 0 };
const std::size_t  FormImpl::kDefaultY{ 0 };
const std::wstring FormImpl::kClassName{ L"Main Form class name." };
const DWORD		   FormImpl::kDefaultStyle{ WS_OVERLAPPEDWINDOW };
const DWORD		   FormImpl::kDefaultExStyle{ WS_EX_TOPMOST };

const FormProc	   kDefaultFormProc{ [](Message& message)->bool { return false; } };

FormImpl::FormImpl()noexcept(true):
	hInstance_{ GetModuleHandleW(NULL) },
	parent_hWnd_{ NULL },
	params_{ },
	device_context_{ NULL },
	frame_info_{ 0 },
	self_hWnd_{ NULL },
	form_proc_{ kDefaultFormProc }{

}

#ifdef _M_X64
#define BindPointerToForm SetWindowLongPtr
using PointerType = LONG_PTR;
using ValueType = LONG_PTR;
#else
#define BindPointerToForm SetFormLong
using PointerType = LONG;
using ValueType = LONG;
#endif

void FormImpl::InitFrameInfo(const size_t width, const size_t height) noexcept(true){

	frame_info_ = BITMAPINFO{ 0 };
	frame_info_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	frame_info_.bmiHeader.biWidth = width;
	frame_info_.bmiHeader.biHeight = -(static_cast<int>(height));
	frame_info_.bmiHeader.biPlanes = 1;
	frame_info_.bmiHeader.biBitCount = 32;
	frame_info_.bmiHeader.biCompression = BI_RGB;
	frame_info_.bmiHeader.biSizeImage = ((width * 24 + 31) & ~31) / 8 * height;

}

LRESULT CALLBACK FormImpl::WndProc(HWND hWnd, UINT message, WPARAM  wParam, LPARAM lParam)noexcept(false) {

	if (message == WM_CREATE) {

		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
		FormImpl* this_form = (FormImpl*)lpcs->lpCreateParams;
		this_form->self_hWnd_ = hWnd;
		SetLastError(NULL);
		int last_value = BindPointerToForm(hWnd, GWLP_USERDATA, reinterpret_cast<PointerType>(this_form));

		if (last_value == 0) {

			DWORD error = GetLastError();

			if (error != 0)
				throw FormExcep{ u8"BindPointerToWindow error." };
		}
		else
			throw FormExcep{ u8"BindPointerToWindow error." };

	}

	bool message_processed = false;
	Message mes{ message, wParam, lParam };

	if (message == WM_COMMAND) {
		
		LONG_PTR ptr = GetWindowLongPtr(HWND(lParam), GWLP_USERDATA);
		Button* this_button = reinterpret_cast<Button* const>(ptr);
		
		if (ptr != NULL)
			message_processed = this_button->proc_(mes);
	
	} else {

		LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
		FormImpl* this_form = reinterpret_cast<FormImpl* const>(ptr);

		if (ptr != NULL)
			message_processed = this_form->form_proc_(mes);
		
	}

	if (message_processed)
		return LRESULT{ 0 };

	switch (message) {

	case WM_CLOSE: { DestroyWindow(hWnd);break; }
	case WM_DESTROY: { PostQuitMessage(0);break; }
	default: return DefWindowProc(hWnd, message, wParam, lParam); 
		
	}

}
		
FormImpl::~FormImpl()noexcept(true) {


}

const HWND FormImpl::Handle() const noexcept(true){

	return self_hWnd_;

}

void FormImpl::InitFormProc(FormProc messages_processing) noexcept(true){

	form_proc_ = messages_processing;

}

#include <string>
#include <iostream>

void FormImpl::Position(const int x, const int y) noexcept(false){

	if (WasCreated()) {
	
		BOOL success = SetWindowPos(self_hWnd_, NULL, x, y, params_.width_, params_.height_, NULL);
		
		if (!success) 
			throw FormExcep{ u8"SetWindowPos error." };

	}
	
	params_.x_ = x;
	params_.y_ = y;

}

void FormImpl::Caption(const std::wstring& caption)noexcept(false){

	if (WasCreated()) {
	
		BOOL success = SetWindowText(self_hWnd_, caption.c_str());
		
		if (!success) 
			throw FormExcep{ u8"SetWindowText error." };

	}

	params_.title_ = caption;

}

void FormImpl::Size(const size_t width, const size_t height) noexcept(false){

	if (WasCreated()) {

		BOOL success = SetWindowPos(self_hWnd_, NULL, params_.x_, params_.y_, width, height, SWP_NOZORDER);
		
		if (!success) 
			throw FormExcep{ u8"SetWindowPos error." };

	}
	
	params_.width_ = width;
	params_.height_ = height;

	InitFrameInfo(width, height);

}

int FormImpl::Width() const noexcept(true){

	return params_.width_;
}

int FormImpl::Height() const noexcept(true){

	return params_.height_;
}

int FormImpl::X() const noexcept(true){

	return params_.x_;
}

int FormImpl::Y() const noexcept(true){

	return params_.y_;
}

void FormImpl::Style(DWORD ex_dwStyle, DWORD dwStyle) noexcept(false){

	if (WasCreated()) {
	
		BOOL success = SetWindowLongPtr(self_hWnd_, GWL_STYLE, static_cast<LONG_PTR>(params_.dwStyle_));
		
		if (!success) 
			throw FormExcep{ u8"Changing form style error." };
	
	}

	params_.ex_dwStyle_ = ex_dwStyle;
	params_.dwStyle_ = dwStyle;

}

bool FormImpl::WasCreated() const noexcept(true){

	return self_hWnd_ != NULL;
}

void FormImpl::RegisterFormClass(const std::wstring& class_name)noexcept(false) {

	params_.sz_class_name_ = class_name;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = NULL;//CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 4;
	wc.hInstance = hInstance_;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = params_.sz_class_name_.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
		throw FormExcep{ u8"RegisterClass error." };

}

void FormImpl::Create(const std::wstring& class_name, const HWND parent_hWnd)noexcept(false){
	
	FormImpl::RegisterFormClass(class_name);

	if(WasCreated()) throw FormExcep{ u8"CreateWindowEx error." };

	//Creating Form with default//installed parametrs
	self_hWnd_ = CreateWindowEx(params_.ex_dwStyle_, 
		params_.sz_class_name_.c_str(),
		params_.title_.c_str(),
		params_.dwStyle_,
		params_.x_,
		params_.y_,
		params_.width_,
		params_.height_,
		parent_hWnd,
		HMENU(NULL),
		(HINSTANCE)hInstance_,
		this);

	if (!WasCreated()) throw FormExcep{ u8"CreateWindowEx error." };

	this->parent_hWnd_ = parent_hWnd;
	SetProcessDPIAware();//Вызывая эту функцию (SetProcessDPIAware), вы сообщаете системе, что интерфейс вашего приложения умеет сам правильно масштабироваться при высоких значениях DPI (точки на дюйм). Если вы не выставите этот флаг, то интерфейс вашего приложения может выглядеть размыто при высоких значениях DPI.
	device_context_ = GetDC(self_hWnd_);

}

void FormImpl::Show(int nCmdShow) noexcept(false){

	/*if (!*/ShowWindow(self_hWnd_, nCmdShow);//)
		//throw FormExcep{ u8"ShowWindow exception." };

}

WPARAM FormImpl::StartMessageLoop()const noexcept(false) {

	MSG msg{ 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;

}

void FormImpl::Destroy() noexcept(false){
	
	try {
	
		SendMessage(self_hWnd_, WM_CLOSE, NULL, NULL);
	
	} catch (const FormExcep& exception) {

		throw FormExcep{ u8"Destroying error." };

	}

}

void FormImpl::Run()noexcept(false){
	
	StartMessageLoop();

}


void FormImpl::ShowFrame(const void* const frame_buffer)noexcept(false) {

	if (!SetDIBitsToDevice(
		FormImpl::device_context_,
		0,
		0,
		FormImpl::params_.width_,
		FormImpl::params_.height_,
		0,
		0,
		0,
		FormImpl::params_.height_,
		frame_buffer,
		&frame_info_,
		DIB_PAL_COLORS
	)) throw FormExcep{ u8"SetDIBitsToDevice exception." };

}
