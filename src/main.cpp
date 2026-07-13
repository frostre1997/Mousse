#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace geode::prelude;

class $modify(MyAppDelegate, AppDelegate) {
    bool applicationDidFinishLaunching() {
        auto ret = AppDelegate::applicationDidFinishLaunching();

        // Write a timestamp to a file on external storage
        std::ofstream file("/storage/emulated/0/mousse_test.txt");
        if (file.is_open()) {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            file << "Mousse mod loaded at: " << std::ctime(&now_c);
            file.close();
        }

        log::info("Mousse mod loaded (file write test).");
        return ret;
    }
};

$on_mod(Loaded) {
    // Also write from this hook (which runs earlier)
    std::ofstream file("/storage/emulated/0/mousse_on_mod.txt");
    if (file.is_open()) {
        file << "on_mod hook executed!";
        file.close();
    }
}
