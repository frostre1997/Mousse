#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>
#include <Geode/modify/CCEGLView.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

// Initialize settings
static bool getSettingBool(const std::string& key, bool defaultValue = true) {
    return Mod::get()->getSettingValue<bool>(key).value_or(defaultValue);
}

static float getSettingFloat(const std::string& key, float defaultValue = 1.0f) {
    return Mod::get()->getSettingValue<double>(key).value_or(defaultValue);
}

// Main mod class - modifies the app delegate
class $modify(MyAppDelegate, AppDelegate) {
    void trySaveApp(bool a) {
        AppDelegate::trySaveApp(a);
        
        log::info("Mouse on Android initialized!");
        log::info("Settings loaded:");
        log::info("- Cursor Size: {}", getSettingFloat("cursor-size", 1.0f));
        log::info("- Sensitivity: {}", getSettingFloat("sensitivity", 1.0f));
        log::info("- Show Cursor: {}", getSettingBool("show-cursor", true));
        log::info("- Invert Scroll: {}", getSettingBool("invert-scroll", false));
    }
};

// Optional: Modify the view to handle mouse input
class $modify(MyCCEGLView, CCEGLView) {
    void update(float dt) {
        CCEGLView::update(dt);
        
        // Your mouse handling logic here
        // You would need to implement actual cursor movement
        // using Android's input system
    }
};
