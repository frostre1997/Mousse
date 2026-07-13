#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(CursorSceneHook, CCScene) {
    void onEnter() override {
        CCScene::onEnter();
        this->scheduleOnce(schedule_selector(CursorSceneHook::delayedManageCursor), 0.1f);
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

        // Debug label to confirm mod is loaded
        auto label = CCLabelBMFont::create("Mousse Active!", "bigFont.fnt");
        if (label) {
            label->setPosition(CCDirector::sharedDirector()->getWinSize() / 2);
            label->setPositionY(label->getPositionY() + 100);
            label->setScale(0.8f);
            label->setColor(ccc3(0, 255, 0));
            label->setZOrder(10000);
            scene->addChild(label);
        }

        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(9999);
                scene->addChild(g_cursor);
                g_cursor->setVisible(true);
                log::info("Cursor created (CCDrawNode).");
            }
        }
        else if (g_cursor->getParent() != scene) {
            g_cursor->retain();
            g_cursor->removeFromParentAndCleanup(false);
            scene->addChild(g_cursor);
            g_cursor->release();
            g_cursor->setVisible(true);
            log::info("Cursor moved.");
        }
    }
};

$on_mod(Loaded) {
    log::info("Mousse mod loaded (force show).");
}
