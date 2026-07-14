#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

// Global cursor pointer
CursorNode* g_cursor = nullptr;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        // Remove old cursor if it exists
        if (g_cursor) {
            g_cursor->removeFromParentAndCleanup(true);
            g_cursor = nullptr;
        }

        // Create NEW cursor
        g_cursor = CursorNode::create();
        if (g_cursor) {
            g_cursor->setZOrder(1000);
            g_cursor->setPosition(ccp(winSize.width / 2, winSize.height / 2));
            g_cursor->setVisible(true);
            this->addChild(g_cursor);
            
            log::info("[Mousse] Cursor created at: {}x{}", winSize.width/2, winSize.height/2);
        }

        // Enable touch on this layer so we can track touches
        this->setTouchEnabled(true);
        this->setTouchPriority(-1000);
        
        return true;
    }
    
    // Track touches on MenuLayer and move the cursor
    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override {
        if (g_cursor) {
            auto pos = touch->getLocation();
            g_cursor->setPosition(pos);
            log::info("[Mousse] Touch began - moving cursor to: {}x{}", pos.x, pos.y);
        }
        return MenuLayer::ccTouchBegan(touch, event);
    }
    
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        if (g_cursor) {
            auto pos = touch->getLocation();
            g_cursor->setPosition(pos);
            log::info("[Mousse] Touch moved - cursor at: {}x{}", pos.x, pos.y);
        }
        MenuLayer::ccTouchMoved(touch, event);
    }
    
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        log::info("[Mousse] Touch ended");
        MenuLayer::ccTouchEnded(touch, event);
    }
    
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override {
        log::info("[Mousse] Touch cancelled");
        MenuLayer::ccTouchCancelled(touch, event);
    }
    
    // Handle returning from online
    void onEnter() override {
        MenuLayer::onEnter();
        log::info("[Mousse] MenuLayer onEnter called");
        
        if (g_cursor) {
            g_cursor->setVisible(true);
        }
    }
};

$on_mod(Loaded) {
    log::info("[Mousse] Mousse mod loaded successfully!");
}
