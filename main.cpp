
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include "server_connection.h"
#include "minecraft.h"


bool close = false;

void reloadPlugins();
void loadPlugins();
void unloadPlugins();

#ifdef _WIN32
using PluginHandle = HMODULE;
#else
#include <dlfcn.h>
    using PluginHandle = void*;
#endif


std::unordered_set<PluginHandle> plugins;

int main() {

    if(!startupServerNetwork()) {
        printInfo("Unable to startup server connection. See errors above.");
        return -1;
    }

    printInfo("Network setup completed. ");


    loadPlugins();

    std::string inputText;


    printInfo("Server has been successfully loaded, to list available commands type /help");
    while(!close) {
        std::cin >> inputText;

        if(inputText == "stop")
            break;

        Minecraft::getServer().setMOTD(inputText);
        printInfo("MOTD changed to ",   Minecraft::getServer().getMOTD());
    }

    unloadPlugins();

    printInfo("Closing server...");
    closeServerSocket();
    return 0;
}

void unloadPlugins() {

    for(const auto& plugin : plugins)  {

#ifdef _WIN32
        FreeLibrary(plugin);
#else
        dlclose(plugin);
#endif
    }
}
void loadPlugins() {


    printInfo("Loading plugins...");

    using namespace std::filesystem;

    const path pluginsFolder = "plugins";

    if(!exists(pluginsFolder) || !is_directory(pluginsFolder)) {
        create_directory(pluginsFolder);
        return;
    }

    for(const auto& entry : directory_iterator(pluginsFolder)) {

        std::string pathname = entry.path().string();
#ifdef _WIN32

        if (!pathname.ends_with(".dll"))
            continue;

        auto handle = LoadLibraryA(pathname.c_str());

#else
        if (!pathname.ends_with(".so"))
            continue;

        auto handle = dlopen(pathname.c_str(), RTLD_NOW);
#endif

        if(handle == nullptr) {
            printInfo("Unable to load ", pathname, " is this a valid Shared Library?");
            return;
        }

        plugins.emplace(handle);

    }

}

