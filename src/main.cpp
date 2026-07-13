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
        if (!g_cursor) {
            g_cursor = CursorNode::create();
            g_cursor->setZOrder(9999);
            this->addChild(g_cursor);
            g_cursor->setVisible(false);  // start hidden

            // Show after 1.5 seconds using a delayed action
            auto showAction = CCSequence::create(
                CCDelayTime::create(1.5f),
                CCCallFunc::create([&]() {
                    if (g_cursor) g_cursor->setVisible(true);
                }),
                nullptr
            );
            g_cursor->runAction(showAction);
        }
        else if (g_cursor->getParent() != this) {
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
