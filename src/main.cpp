#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(CursorSceneHook, CCScene) {
    void onEnter() override {
        CCScene::onEnter();
        this->scheduleOnce(schedule_selector(CursorSceneHook::delayedManageCursor), 0.0f);
    }

    void onExit() override {
        if (g_cursor && g_cursor->getParent() == this) {
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            g_cursor->release();
            g_cursor = nullptr;
        }
        CCScene::onExit();
    }

    void delayedManageCursor(float dt) {
        auto scene = this;
        if (!scene) return;

        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(9999);
                scene->addChild(g_cursor);
                // Ensure it's on top and visible
                g_cursor->setVisible(true);
                log::info("Cursor created and added to scene.");
            }
        }
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
    log::info("Mousse mod loaded (debug version).");
}
