#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "AbstractFigure.hpp"
#include "BasicPlugin.hpp"

#include <memory>

class __declspec(dllexport) SquareFigure : public AbstractFigure {

public:

	explicit SquareFigure()noexcept:
		AbstractFigure{ } { }

	void SetParametrs(const FigureInfo& info)override;

};

extern "C"  __declspec(dllexport) std::any GetPluginObject()noexcept {

	try {
	
		return reinterpret_cast<AbstractFigure*>(new SquareFigure);
	
	} catch (const std::bad_alloc&) {

		return std::any{};

	}

}

extern "C" __declspec(dllexport) std::string  GetPluginName()noexcept {

	return u8"Square";

}

extern "C" __declspec(dllexport) Plugin::Type  GetPluginType()noexcept {

	return Plugin::Type::FIGURE;

}

#endif //INTERFACE_HPP