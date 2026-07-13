#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

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
        // Safety: if the scene is being destroyed, don't add cursor
        if (!this) return;
        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(9999);
                this->addChild(g_cursor);
                g_cursor->showAfterDelay(1.5f);
            }
        }
        else if (g_cursor->getParent() != this) {
            // Move the existing cursor to this scene
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            this->addChild(g_cursor);
            g_cursor->release();
        }
    }
};

$on_mod(Loaded) {
    log::info("Mouse on Android mod loaded. Cursor will appear in 1.5s.");
}
