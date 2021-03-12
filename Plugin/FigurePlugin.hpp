#pragma once

#ifndef FIGUREPLUGIN_HPP
#define FIGUREPLUGIN_HPP

#include <memory>
#include "AbstractFigure.hpp"
#include "BasicPlugin.hpp"

class FigurePlugin : public Plugin {
private:
public:

	explicit FigurePlugin(const fs::path& plugin_path) :
		Plugin{ plugin_path } {}

	AbstractFigure* GetFigureObjectPointer() {

		std::any ptr = Plugin::GetObjectPointer();

		try {

			return std::any_cast<AbstractFigure*>(ptr);
		
		} catch (const std::bad_any_cast& cast_error) {

			throw PluginException{ u8"Pointer casting error." };

		}

	 }

};

#endif //FIGUREPLUGIN_HPP