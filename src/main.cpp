#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Global cursor pointer
CursorNode* g_cursor = nullptr;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        // Remove old cursor if it exists (from previous MenuLayer instance)
        if (g_cursor) {
            g_cursor->removeFromParentAndCleanup(true);
            g_cursor = nullptr;
        }

        // Create NEW cursor
        g_cursor = CursorNode::create();
        if (g_cursor) {
            g_cursor->setZOrder(1000);  // High Z-order so it's on top
            g_cursor->setPosition(ccp(winSize.width / 2, winSize.height / 2));
            g_cursor->setVisible(true);
            this->addChild(g_cursor);
            
            log::info("[Mousse] Cursor created at: {}x{}", winSize.width/2, winSize.height/2);
        }

        return true;
    }
    
    // Add this to handle when layer is shown again
    void onEnter() override {
        MenuLayer::onEnter();
        log::info("[Mousse] MenuLayer onEnter called");
        
        // Make sure cursor is visible when returning
        if (g_cursor) {
            g_cursor->setVisible(true);
            g_cursor->setTouchEnabled(true);
        }
    }
};

$on_mod(Loaded) {
    log::info("[Mousse] Mousse mod loaded successfully!");
}
