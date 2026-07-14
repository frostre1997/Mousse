#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        // Create and center the cursor
        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(1000);  // High Z-order so it's on top
                this->addChild(g_cursor);
                g_cursor->setPosition(ccp(winSize.width / 2, winSize.height / 2));
                g_cursor->setVisible(true);
                log::info("[Mousse] Cursor created at position: {}x{}", winSize.width/2, winSize.height/2);
            } else {
                log::error("[Mousse] Failed to create cursor!");
            }
        }

        return true;
    }
};

$on_mod(Loaded) {
    log::info("[Mousse] Mousse mod loaded successfully!");
}
