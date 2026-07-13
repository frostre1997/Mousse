#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Remove the test red layer – we no longer need it

        // Create and add the cursor
        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(99999);
                this->addChild(g_cursor);
                log::info("Cursor created on MenuLayer.");
            }
        }
        else if (g_cursor->getParent() != this) {
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            this->addChild(g_cursor);
            g_cursor->release();
            log::info("Cursor moved to new scene.");
        }

        return true;
    }
};

$on_mod(Loaded) {
    log::info("Mousse mod loaded (production version).");
}
