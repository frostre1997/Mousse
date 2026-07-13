#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(CursorSceneHook, CCScene) {
    void onEnter() override {
        CCScene::onEnter();
        this->scheduleOnce(schedule_selector(CursorSceneHook::delayedAddCursor), 0.0f);
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

    void delayedAddCursor(float dt) {
        auto scene = this;
        if (!scene) return;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint center = ccp(winSize.width / 2, winSize.height / 2);

        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(99999);
                scene->addChild(g_cursor);
                g_cursor->setPosition(center);
                g_cursor->setVisible(true);
                log::info("Cursor created and centered at (%.1f, %.1f)", center.x, center.y);
            }
        }
        else if (g_cursor->getParent() != scene) {
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            scene->addChild(g_cursor);
            g_cursor->release();
            g_cursor->setPosition(center);
            g_cursor->setVisible(true);
            log::info("Cursor moved and centered.");
        }
    }
};

$on_mod(Loaded) {
    log::info("Mousse mod loaded (centered cursor).");
}
