#pragma once
#ifndef PLUGINSMANAGER_HPP
#define PLUGINSMANAGER_HPP

#include <cstdint>
using std::uint64_t;

#include <filesystem>
namespace fs = std::filesystem;

#include <map>
using std::map;

#include <string_view>
using std::string_view;

#include "Plugin.hpp"
#include "Exception.hpp"

using PluginsManagerException = Exception;

class PluginsManager final {
private:

	map<string_view, Plugin> loaded_plugins_;

private:
	
	explicit PluginsManager()noexcept;
	~PluginsManager()noexcept;

public:

	static PluginsManager& Access();
	static const fs::path inline plugins_path_{ fs::current_path() / u8"plugins" };

	const uint64_t LoadedPluginsNumber()const noexcept;
	const map<string_view, Plugin>& AllPlugins()const noexcept;
	Plugin& operator[](const string_view plugin_name);
	void Load()noexcept;
	void Unload()noexcept;

};

#endif //PLUGINSMANAGER_HPP