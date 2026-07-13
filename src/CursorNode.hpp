#pragma once
#include <Geode/Geode.hpp>

class CursorNode : public cocos2d::CCNode {
protected:
    bool m_visible;
public:
    static CursorNode* create();
    bool init() override;
    void setVisible(bool visible) override;
    void draw() override;
    void onEnter() override;
    void onExit() override;
    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
};
