#pragma once

#ifndef FIGUREPLUGIN_HPP
#define FIGUREPLUGIN_HPP

#include <memory>
#include "AbstractFigure.hpp"
#include "BasicPlugin.hpp"

class FigurePlugin : public Plugin {
private:
public:

	explicit FigurePlugin(const std::filesystem::path plugin_path) :
		Plugin{ plugin_path } {}

	std::unique_ptr<AbstractFigure> GetFigureObjectPointer() {

		using namespace std;

		any ptr = Plugin::GetObjectPointer();

		try {
		
			return make_unique<AbstractFigure>(any_cast<AbstractFigure*>(ptr));
		
		} catch (const bad_any_cast& cast_error) {

			throw PluginException{ u8"Pointer casting error." };

		}

	 }

};

#endif //FIGUREPLUGIN_HPP