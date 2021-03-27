#include "AbstractComponent.hpp"

bool AbstractComponent::CallProcessMessage(Message& message) {

	return process_messages_(message);
}

void AbstractComponent::RegisterComponentClass(const std::wstring& class_name){

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = NULL;//CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ComponentProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 4;
	wc.hInstance = hInstance_;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = class_name.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
		throw ComponentException{ u8"RegisterClass error." };

	class_name_ = class_name;

}

void AbstractComponent::ShowComponent(int nCmdShow){

	ShowWindow(self_hWnd_, nCmdShow);

}

bool AbstractComponent::WasCreated() const noexcept{

	return self_hWnd_ != NULL;
}

DWORD AbstractComponent::GetStyle() const noexcept{

	return dwStyle_;
}

DWORD AbstractComponent::GetExtendedStyle() const noexcept{

	return ex_dwStyle_;
}

const HWND AbstractComponent::GetHandle() const noexcept {

	return self_hWnd_;
}

void AbstractComponent::DestroyComponent(){

	try {

		SendMessage(self_hWnd_, WM_CLOSE, NULL, NULL);

	}
	catch (const ComponentException&) {

		throw ComponentException{ u8"Destroying error." };

	}

}

AbstractComponent::AbstractComponent(){

	hInstance_ = GetModuleHandle(NULL);

}

AbstractComponent::~AbstractComponent(){


}

void AbstractComponent::SetProcessFunction(ProcessMessage messages_processing) noexcept {

	process_messages_ = [this, messages_processing](Message& message)noexcept->bool {

		switch (message.GetAction()) {
		case Action::PositionChanged: {

			auto rect = (LPWINDOWPOS)message.GetLParam();
			x_ = rect->x;
			y_ = rect->y;

			break;
		}

		case Action::Resized: {

			width_ = LOWORD(message.GetLParam());
			height_ = HIWORD(message.GetLParam());

			break;
		}

		};

		return messages_processing(message);

	};

}

void AbstractComponent::ChangePosition(const uint64_t x, const uint64_t y) noexcept(false) {

	if (WasCreated()) {

		BOOL success = SetWindowPos(self_hWnd_, NULL, x, y, width_, height_, NULL);

		if (!success)
			throw ComponentException{ u8"SetWindowPos error." };

	}

	x_ = x;
	y_ = y;
}

void AbstractComponent::ChangeSize(const uint64_t width, const uint64_t height) {

	if (WasCreated()) {

		BOOL success = SetWindowPos(self_hWnd_, NULL, x_, y_, width, height, SWP_NOZORDER);

		if (!success)
			throw ComponentException{ u8"SetWindowPos error." };

	}

	width_ = width;
	height_ = height;

}

void AbstractComponent::ChangeText(const std::wstring& text) {

	if (WasCreated()) {

		BOOL success = SetWindowText(self_hWnd_, text.c_str());

		if (!success)
			throw ComponentException{ u8"SetWindowText error." };

	}

	text_ = text;

}

int AbstractComponent::GetWidth() const noexcept{

	return width_;
}

const std::uint64_t AbstractComponent::GetClientHeight() const noexcept{

	RECT client_rect{ 0 };
	GetClientRect(self_hWnd_, &client_rect);

	return client_rect.bottom;
}

const std::uint64_t AbstractComponent::GetClientWidth() const noexcept{

	RECT client_rect{ 0 };
	GetClientRect(self_hWnd_, &client_rect);

	return client_rect.right;
}

int AbstractComponent::GetHeight() const noexcept {

	return height_;
}

int AbstractComponent::GetX() const noexcept {

	return x_;
}

int AbstractComponent::GetY() const noexcept {

	return y_;
}

#ifdef _M_X64
	using PointerType = LONG_PTR;
	using ValueType = LONG_PTR;
#else
#define BindPointerToForm SetFormLong
	using PointerType = LONG;
	using ValueType = LONG;
#endif

void AbstractComponent::CreateComponent(const HWND parent_hWnd, const std::wstring& class_name){

	if (WasCreated()) throw ComponentException{ u8"CreateWindowEx error." };
	
	if (class_name != kDefaultClassName)
		class_name_ = class_name;

	self_hWnd_ = CreateWindowEx(ex_dwStyle_,
		class_name_.c_str(),
		text_.c_str(),
		dwStyle_,
		x_,
		y_,
		width_,
		height_,
		parent_hWnd,
		HMENU(NULL),
		(HINSTANCE)hInstance_,
		this);


	if (!WasCreated()) throw ComponentException{ u8"CreateWindowEx error." };

	parent_hWnd_ = parent_hWnd;

	SetLastError(NULL);
	LONG_PTR last_value = SetWindowLongPtr(GetHandle(), GWLP_USERDATA, (PointerType)this);

	if (last_value == 0) {

		DWORD error = GetLastError();

		if (error != 0)
			throw ComponentException{ u8"BindPointerToWindow error." };

	} else
		throw ComponentException{ u8"BindPointerToWindow error." };

	SetProcessDPIAware();

}

void AbstractComponent::ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle) {

	ex_dwStyle_ = ex_dwStyle;
	dwStyle_ = dwStyle;
	
	if (WasCreated()) {

		SetWindowLongPtr(GetHandle(), GWL_STYLE, dwStyle_ );
		SetWindowLongPtr(GetHandle(), GWL_EXSTYLE, ex_dwStyle_);
	
	}

}

LRESULT CALLBACK AbstractComponent::ComponentProc(HWND hWnd, UINT message, WPARAM  wParam, LPARAM lParam) {

	bool message_processed = false;
	AbstractComponent* component = nullptr;
	
	Message new_message{ message, wParam, lParam };

	if(new_message.GetActionType() == ActionType::Control)
		component = (AbstractComponent*)GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
	else	
		component = (AbstractComponent*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (component != nullptr)
		message_processed = component->CallProcessMessage(new_message);

	if (message_processed)
		return LRESULT{ 0 };

	switch (message) {

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}
