#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CursorNode : public CCNode {
protected:
    bool m_visible;
    
public:
    static CursorNode* create();
    bool init() override;
    void setVisible(bool visible) override;
    void draw() override;
    
    // REMOVE onEnter() and onExit() - they cause crashes!
    // void onEnter() override;
    // void onExit() override;
    
    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;
};
