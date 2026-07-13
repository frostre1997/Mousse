#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(CursorSceneHook, CCScene) {
    void onEnter() override {
        CCScene::onEnter();
        // Schedule after a tiny delay to ensure the scene is fully set up
        this->scheduleOnce(schedule_selector(CursorSceneHook::delayedAddCursor), 0.0f);
    }

    void onExit() override {
        // When the scene is about to be destroyed, detach and release the cursor
        if (g_cursor && g_cursor->getParent() == this) {
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            g_cursor->release();
            g_cursor = nullptr;
        }
        CCScene::onExit();
    }

    void delayedAddCursor(float dt) {
        auto scene = this;
        if (!scene) return;

        // If cursor doesn't exist, create it
        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(99999);
                scene->addChild(g_cursor);
                g_cursor->setVisible(true);
                log::info("Cursor created and added to scene.");
            }
        }
        // If cursor exists but belongs to another scene, move it here
        else if (g_cursor->getParent() != scene) {
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            scene->addChild(g_cursor);
            g_cursor->release();
            g_cursor->setVisible(true);
            log::info("Cursor moved to new scene.");
        }
    }
};

$on_mod(Loaded) {
    log::info("Mousse mod loaded (scene hook).");
}
