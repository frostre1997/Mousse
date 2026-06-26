#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>

using namespace geode::prelude;

class $modify(MyAppDelegate, AppDelegate) {
    void trySaveApp(bool a) {
        AppDelegate::trySaveApp(a);
        log::info("Mouse on Android mod loaded successfully!");
    }
};
