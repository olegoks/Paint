#include "PluginsManager.hpp"
#include <algorithm>

PluginsManager::PluginsManager()noexcept:
	loaded_plugins_{ }{ }

PluginsManager::~PluginsManager()noexcept{ }

PluginsManager& PluginsManager::Access() {

	static PluginsManager* unique_plugins_manager{ nullptr };

	try {
	
		if (!unique_plugins_manager)
			unique_plugins_manager = new PluginsManager{};
	
	} catch (const std::bad_alloc&) {

		throw PluginsManagerException{ u8"Allocation memeory exception" };

	}

	return *unique_plugins_manager;

}

const uint64_t PluginsManager::LoadedPluginsNumber() const noexcept{

    return loaded_plugins_.size();
}

const map<string_view, Plugin>& PluginsManager::AllPlugins() const noexcept{

	return loaded_plugins_;

}

Plugin& PluginsManager::operator[](const string_view plugin_name){

	try {
	
		return loaded_plugins_.at(plugin_name);
	
	} catch (const std::out_of_range& incorrect_index) {

		throw PluginsManagerException{ u8"There is no plugin with such name." };

	}

}

void PluginsManager::Load() noexcept{

	try {

		for (auto& maybe_plugin : fs::directory_iterator{ plugins_path_ }) {

			//if file doesn't have Plugin extension, check next
			if (maybe_plugin.path().extension() != Plugin::extension)continue;

			Plugin plugin{ maybe_plugin.path() };

			try {

				plugin.Load();
			
			//Plugin loaded error. Maybe plugin doesn't have requared functions.
			} catch (const PluginException& exception) { continue; }

			loaded_plugins_.insert({ plugin.GetName(), std::move(plugin) });

		}

	//Directory constructor exception. Plugins path does no exist.
	//Number of loaded plugins: 0;
	} catch (const std::filesystem::filesystem_error& incorrect_path) {

		return;

	}

}

void PluginsManager::Unload()noexcept{

	loaded_plugins_.clear();

}
