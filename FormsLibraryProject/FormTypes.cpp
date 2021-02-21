#include "Library/FormTypes.hpp"

#define VK_A 65
#define VK_B 66
#define VK_D 68
#define VK_W 87
#define VK_S 83

ActionType TypeOfAction(Action action, LPARAM lParam)noexcept(true) {

	if (action == Action::KeyDown || action == Action::KeyUp) {

		return ActionType::Keyboard;
	}

	if (action == Action::LMouseDown || action == Action::LMouseUp
		|| action == Action::RMouseDown || action == Action::RMouseUp
		|| action == Action::MouseMove) {

		return ActionType::Mouse;

	}

	if (action == Action::MenuControlAccel) {
		
		WORD high_word = HIWORD(lParam);
		switch (high_word) {
		case 0:
			return ActionType::Menu;

		case 1:
			return ActionType::Accelerator;

		default:
			return ActionType::Control;

		};
		
	}

	return ActionType::Nothing;
}

Key ConvertWParamToKey(UINT wParam)noexcept(true) {

	switch (wParam) {

	case VK_UP: return Key::ArrowUp;
	case VK_DOWN: return Key::ArrowDown;
	case VK_LEFT: return Key::ArrowLeft;
	case VK_RIGHT: return Key::ArrowRight;
	case VK_A: return Key::A;
	case VK_D: return Key::D;
	case VK_S: return  Key::S;
	case VK_W: return Key::W;
	default: return Key::Nothing;

	}

}

Action ConvertMessageToAction(UINT message)noexcept(true) {

	switch (message) {

	case WM_MOUSEMOVE: return Action::MouseMove;
	case WM_KEYUP: return Action::KeyUp;
	case WM_KEYDOWN: return Action::KeyDown;
	case WM_LBUTTONDOWN: return Action::LMouseDown;
	case WM_LBUTTONUP: return Action::LMouseUp;
	case WM_RBUTTONDOWN: return Action::RMouseDown;
	case WM_RBUTTONUP: return Action::RMouseUp;
	case WM_COMMAND: return Action::MenuControlAccel;
	default:return Action::Nothing;

	}

}

KeyAction::KeyAction()noexcept(true) :
	key_{ Key::Nothing },
	action_{ Action::Nothing }{}

KeyAction::KeyAction(Key key, Action action)noexcept(true) :
	key_{ key },
	action_{ action }{}

Message::Message(UINT Message, WPARAM wParam, LPARAM lParam) noexcept(true):
	key_action_{ },
	message_{ Message },
	wParam_{ wParam },
	lParam_{ lParam },
	x_{ 0 }, y_{ 0 },
	control_id_{ -1 },
	hWnd_{ NULL }  {

	Action action = ConvertMessageToAction(Message);
	key_action_.action_ = action;

	ActionType action_type = TypeOfAction(action, lParam_);

	switch (action_type) {
	case ActionType::Keyboard:

		key_action_.key_ = ConvertWParamToKey(wParam_);

		break;

	case ActionType::Menu:

		//...

		break;

	case ActionType::Mouse:

		x_ = GET_X_LPARAM(lParam_);
		y_ = GET_Y_LPARAM(lParam_);

		break;

	case ActionType::Accelerator:

		//...
		
		break;


	case ActionType::Control:

		hWnd_ = (HWND)lParam_;
		control_id_ = LOWORD(wParam_);
		
		WORD button_action = HIWORD(wParam_);

		switch (button_action) {
		case BN_CLICKED:
			
			key_action_.action_ = Action::ButtonClicked;

			break;
		
		default:
			key_action_.action_ = Action::Nothing;

		};

		break;

	};
}
