#pragma once

#ifndef BASICPLUGIN_HPP
#define BASICPLUGIN_HPP

#include <cstdint>
using std::uint64_t;

#include<filesystem>
namespace fs = std::filesystem;

#include <any>
#include <string>
#include <memory>

#include "DLL.hpp"
#include "Exception.hpp"
#include "AbstractFigure.hpp"

using PluginException = Exception;
using std::shared_ptr;
using std::string;

class Plugin {
public:

	using GetPluginName = std::string_view(*)();
	using GetPluginObject = AbstractFigure*(*)();

private:

	
	GetPluginName get_name_;
	GetPluginObject get_object_;
	fs::path dll_path_;
	DLL dll_;

public:

	shared_ptr<AbstractFigure> GetFigure()const noexcept {

		return shared_ptr<AbstractFigure>(get_object_());

	}

	static const inline string extension = DLL::extension;
	static const inline string image_extension{ u8".bmp" };

	explicit Plugin(const fs::path& plugin_path):
		get_name_{ nullptr },
		get_object_{ nullptr },
		dll_path_{ plugin_path },
		dll_{ dll_path_.string() }{ }

	explicit Plugin(const Plugin& copy_plugin)noexcept = delete;
	Plugin& operator=(const Plugin& copy_plugin)noexcept = delete;

	Plugin(Plugin&& move_plugin)noexcept:
		Plugin{ fs::path{} } {

		std::swap(dll_, move_plugin.dll_);
		std::swap(get_name_, move_plugin.get_name_);
		std::swap(get_object_, move_plugin.get_object_);
		std::swap(dll_path_, move_plugin.dll_path_);

	}


	Plugin& operator=(Plugin&& move_plugin)noexcept {

		if (this == &move_plugin) return *this;

		std::swap(dll_, move_plugin.dll_);
		std::swap(get_name_, move_plugin.get_name_);
		std::swap(get_object_, move_plugin.get_object_);
		std::swap(dll_path_, move_plugin.dll_path_);

		return *this;

	}

	void Load() {

		if (!fs::exists(dll_path_))
			throw PluginException{ u8"Plugin path isn't exist." };

		try {

			dll_.Load();

			get_name_ = (GetPluginName)dll_.GetFunction(u8"GetPluginName");
			get_object_ = (GetPluginObject)dll_.GetFunction(u8"GetPluginObject");

		}catch (const DLLException& exception) {

			throw PluginException{ u8"Loading dll error." };

		}

	}

	std::string_view GetName()const {

		if(dll_.Loaded())
			return get_name_();

		throw PluginException{ u8"Plugin didn't load." };

	}

	void Unload()noexcept {

		dll_.Unload();

	}

	~Plugin()noexcept {

		if(dll_.Loaded())
			dll_.Unload();

	}

};

#endif //BASICPLUGIN_HPP