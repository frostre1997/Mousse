#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

// Global pointer so we can access it anywhere
CursorNode* g_cursor = nullptr;

// Hook every scene to make sure the cursor is always present
class $modify(CursorSceneHook, CCScene) {
    bool init() {
        if (!CCScene::init()) return false;
        ensureCursor();
        return true;
    }

    void onEnter() {
        CCScene::onEnter();
        ensureCursor();
    }

    void ensureCursor() {
        if (!g_cursor) {
            // Create cursor for the first time
            g_cursor = CursorNode::create();
            g_cursor->setZOrder(9999); // On top of everything
            this->addChild(g_cursor);
            g_cursor->setVisible(false); // Start hidden

            // Show it after 1.5 seconds
            Loader::get()->queueInMainThread([]() {
                if (g_cursor) {
                    g_cursor->setVisible(true);
                }
            }, 1.5f);
        } 
        else if (g_cursor->getParent() != this) {
            // If cursor exists but is not in this scene, move it here
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            this->addChild(g_cursor);
            g_cursor->release();
        }
    }
};

// Optional: Log that the mod loaded successfully
$on_mod(Loaded) {
    log::info("Mousse mod loaded! Cursor will appear in 1.5s.");
}
