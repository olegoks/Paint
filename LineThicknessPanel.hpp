#pragma once

#ifndef LINETHICKNESSPANEL_HPP
#define LINETHICKNESSPANEL_HPP

#include <string>
#include <cstdint>
using std::uint64_t;

#include <algorithm>
#include <sstream>

#include <Edit.hpp>
#include <Static.hpp>

#include "Types.hpp"

class LineThicknessPanel final {
private:

	Static description_text_;
	static const inline std::wstring description_{ L"Line thickness" };
	Edit input_;
	uint64_t line_thickness_;

	static uint64_t ConvertStringToUint64_t(const std::string& string)noexcept {

		bool correct = string.find_first_not_of("0123456789") == std::wstring::npos;

		uint64_t result = 1;

		if (correct) {

			std::stringstream converter{ string };
			converter >> result;

		}

		return result;

	}

public:

	explicit LineThicknessPanel(const HWND hWnd)noexcept:
		description_text_{}, input_{}, line_thickness_{ 1 } {

		description_text_.ChangeText(description_);
		description_text_.ChangeSize(120, 30);
		description_text_.Create(hWnd);

		input_.ChangeText(L"1");
		input_.ChangeSize(120, 30);
		input_.Create(hWnd);

	}

	void ChangePosition(const Position& position)noexcept {

		description_text_.ChangePosition(position.X(), position.Y());
		description_text_.Show();

		input_.ChangePosition(position.X(), position.Y() + 30);
		input_.Show();

	}

	uint64_t GetLineThickness()const noexcept {

		try {
		
			std::string input_number_str = input_.GetText();
			return ConvertStringToUint64_t(input_number_str);
		
		} catch (const ComponentException&) {

			return 1;

		}

	}
	
};


#endif //LINETHICKNESSPANEL_HPP
