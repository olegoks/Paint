#include "PluginsManager.hpp"

const uint64_t PluginsManager::CheckNumbeOfPluginsInTheDirectory(const fs::path& plugins_path) noexcept{

	using std::error_code;
	using fs::directory_iterator;

	error_code fs_error{};
	directory_iterator plugins_dir_it{ plugins_path, fs_error};

	if (fs_error)return 0;

	uint64_t plugins_number = 0;

	for (auto& maybe_plugin : plugins_dir_it)
		if (maybe_plugin.path().extension() == Plugin::extension)
			++plugins_number;

	return plugins_number;

}

PluginsManager::PluginsManager() noexcept:
	loaded_plugins_{ },
	plugins_path_{ } {

}

PluginsManager::~PluginsManager() noexcept{

}

PluginsManager& PluginsManager::Access() noexcept {

	using std::unique_ptr;
	using std::make_unique;

	static PluginsManager* unique_plugins_manager{ nullptr };

	if (!unique_plugins_manager)
		unique_plugins_manager = new PluginsManager{};

	return *unique_plugins_manager;

}

const uint64_t PluginsManager::GetLoadedPluginsNumber() const noexcept{

    return loaded_plugins_.size();
}

optional<Plugin*> PluginsManager::GetPlugin(std::string_view plugin_name) noexcept{

	for (auto& plugin : loaded_plugins_)
		if (plugin.GetName() == plugin_name)
			return &plugin;

	return optional<Plugin*>{};
}

const vector<Plugin>& PluginsManager::GetAllLoadedPlugins() const noexcept{

	return loaded_plugins_;
   
}

const fs::path& PluginsManager::GetPluginsPath() const noexcept{

	return plugins_path_;
}

void PluginsManager::Load(const fs::path& plugins_folder_path) noexcept{

	uint64_t plugins_number = CheckNumbeOfPluginsInTheDirectory(plugins_folder_path);
	if (plugins_number == 0)return;

	loaded_plugins_.reserve(plugins_number);
	loaded_plugins_.shrink_to_fit();

	using std::error_code;
	using fs::directory_iterator;

	error_code fs_error{ };
	directory_iterator plugins_dir_it{ plugins_folder_path };
	if (fs_error)return;

	plugins_path_ = plugins_folder_path;

	for (auto& maybe_plugin : plugins_dir_it) {

		try {

			if (maybe_plugin.path().extension() != Plugin::extension)continue;

			Plugin plugin{ maybe_plugin.path() };
			plugin.Load();
			loaded_plugins_.push_back(std::move(plugin));

		} catch (const PluginException& exception) { continue; }

	}

}

void PluginsManager::UnloadAllPlugins(){

	loaded_plugins_.clear();

}
