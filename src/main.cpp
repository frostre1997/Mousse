#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

static CursorNode* g_cursor = nullptr;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        if (g_cursor) {
            g_cursor->removeFromParentAndCleanup(true);
            g_cursor = nullptr;
        }

        g_cursor = CursorNode::create();
        if (g_cursor) {
            g_cursor->setPosition(ccp(winSize.width / 2, winSize.height / 2));
            g_cursor->setZOrder(99999);
            this->addChild(g_cursor);
        }

        return true;
    }

    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override {
        if (g_cursor) {
            auto pos = touch->getLocation();
            g_cursor->setPosition(pos);
        }
        return MenuLayer::ccTouchBegan(touch, event);
    }

    void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        if (g_cursor) {
            auto pos = touch->getLocation();
            g_cursor->setPosition(pos);
        }
        MenuLayer::ccTouchMoved(touch, event);
    }

    void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        MenuLayer::ccTouchEnded(touch, event);
    }

    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override {
        MenuLayer::ccTouchCancelled(touch, event);
    }

    void onEnter() override {
        MenuLayer::onEnter();
        if (g_cursor) {
            g_cursor->setVisible(true);
        }
    }
};

$on_mod(Loaded) {
    log::info("[Mousse] loaded");
}
