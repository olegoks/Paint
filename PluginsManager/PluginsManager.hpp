#pragma once
#ifndef PLUGINSMANAGER_HPP
#define PLUGINSMANAGER_HPP

#include <cstdint>
using std::uint64_t;
#include <optional>
using std::optional;
#include <filesystem>
namespace fs = std::filesystem;
#include <vector>
using std::vector;

#include "Plugin.hpp"

class PluginsManager final {
private:

	vector<Plugin> loaded_plugins_;
	fs::path plugins_path_;

private:
	
	static const uint64_t CheckNumbeOfPluginsInTheDirectory(const fs::path& plugins_path)noexcept;

	explicit PluginsManager()noexcept;
	~PluginsManager()noexcept;

	explicit PluginsManager(PluginsManager&& manager)noexcept;
	explicit PluginsManager(const PluginsManager& manager)noexcept = delete;

public:

	static PluginsManager& Access()noexcept;
	const uint64_t GetLoadedPluginsNumber()const noexcept;
	optional<Plugin*> GetPlugin(std::string_view plugin_name)noexcept;
	const vector<Plugin>& GetAllLoadedPlugins()const noexcept;
	const fs::path& GetPluginsPath()const noexcept;
	void Load(const fs::path& plugins_folder_path)noexcept;
	void UnloadAllPlugins();

};

#endif //PLUGINSMANAGER_HPP