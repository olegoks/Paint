#pragma once

#ifndef BASICPLUGIN_HPP
#define BASICPLUGIN_HPP

#include "DLL.hpp"
#include "Exception.hpp"
using PluginException = Exception;

#include <cstdint>
using std::uint64_t;

#include<filesystem>
namespace fs = std::filesystem;

#include <any>
#include <string>

class Plugin {
public:

	enum class Type : uint64_t {

		NOTHING = 0,
		FIGURE,
		COLOR

	};

	using GetPluginType = Type(*)();
	using GetPluginName = std::string(*)();
	using GetPluginObject = std::any(*)();

private:

	DLL dll_;

	GetPluginName get_name_;
	GetPluginType get_type_;
	GetPluginObject get_object_;
	fs::path dll_path_;

protected:

	Type GetType()noexcept {

		return get_type_();

	}
	
	std::any GetObjectPointer()noexcept {

		return std::move(get_object_());

	}

public:

	static const inline std::string extension = DLL::extension;
	static const inline std::string image_extension{ u8".bmp" };

	explicit Plugin(const fs::path& plugin_path):
		dll_{}, 
		get_name_{ nullptr }, 
		get_type_{ nullptr },
		get_object_{ nullptr },
		dll_path_{ plugin_path }{

		dll_ = std::move(DLL{ dll_path_.string() });
	
	}

	explicit Plugin(const Plugin& copy_plugin)noexcept = delete;

	explicit Plugin(Plugin&& move_plugin)noexcept :
		Plugin{ fs::path{} } {


		std::swap(dll_, move_plugin.dll_);
		std::swap(get_name_, move_plugin.get_name_);
		std::swap(get_type_, move_plugin.get_type_);
		std::swap(get_object_, move_plugin.get_object_);
		std::swap(dll_path_, move_plugin.dll_path_);
	}

	Plugin& operator=(const Plugin& copy_plugin)noexcept = delete;

	Plugin& operator=(Plugin&& move_plugin)noexcept {

		if (this == &move_plugin) return *this;

		std::swap(dll_, move_plugin.dll_);
		std::swap(get_name_, move_plugin.get_name_);
		std::swap(get_type_, move_plugin.get_type_);
		std::swap(get_object_, move_plugin.get_object_);

		return *this;

	}

	void Load() {

		try {

			if (!fs::exists(dll_path_))
				throw PluginException{ u8"Plugin path isn't exist." };

			dll_.Load();

			get_type_	= (GetPluginType)dll_.GetFunction(u8"GetPluginType");
			get_name_	= (GetPluginName)dll_.GetFunction(u8"GetPluginName");
			get_object_ = (GetPluginObject)dll_.GetFunction(u8"GetPluginObject");

		} catch (const DLLException& exception) {

			throw PluginException{ u8"Loading dll error." };

		}

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