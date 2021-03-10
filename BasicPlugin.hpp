#pragma once

#ifndef BASICPLUGIN_HPP
#define BASICPLUGIN_HPP

#include "DLL.hpp"
#include <string>
#include <cstdint>
using std::uint64_t;

enum class PluginType : uint64_t {

	NOTHING = 0,
	FIGURE,
	COLOR

};

using GetPluginType	  = PluginType(*)();
using GetPluginName   = std::string(*)();
using GetPluginObject = std::any(*)();

#include<filesystem>
namespace fs = std::filesystem;
#include <any>
#include "Exception.hpp"

using PluginException = Exception;

class Plugin {
private:

	DLL dll_;

	GetPluginName get_name_;
	GetPluginType get_type_;
	GetPluginObject get_object_;

protected:
	
	std::any GetObjectPointer()noexcept {

		return std::any{ get_object_() };

	}

public:

	static const inline std::string extension = DLL::extension;
	static const inline std::string image_extension{ u8".bmp" };

	explicit Plugin(const fs::path& plugin_path):
		dll_{}, get_name_{ nullptr }, get_type_{ nullptr }{
		
		if (!fs::exists(plugin_path))
			throw PluginException{ u8"Plugin path isn't exist." };

		dll_ = std::move(DLL{ plugin_path.string() });
	
	}

	void Load() {

		try {

			dll_.Load();

			get_type_	= (GetPluginType)dll_.GetFunction(u8"GetPluginType");
			get_name_	= (GetPluginName)dll_.GetFunction(u8"GetPluginName");
			get_object_ = (GetPluginObject)dll_.GetFunction(u8"GetPluginObject");

		} catch (const DLLException& exception) {

			throw PluginException{ u8"Loading dll error." };

		}

	}

	PluginType GetType()noexcept {
	
		return get_type_();
		
	}

	std::string GetName()noexcept {

		return get_name_();

	}

	void Unload() {

		try {
		
			dll_.Unload();
		
		} catch (const DLLException& exception) {

			throw PluginException{ u8"Dll unloading error." };

		}

	}

	~Plugin()noexcept {

		try {

			dll_.Unload();

		} catch (const DLLException& exception) { }

	}

};

#endif //BASICPLUGIN_HPP