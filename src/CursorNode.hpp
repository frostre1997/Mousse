#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CursorNode : public CCNode, public CCTouchDelegate {
protected:
    bool m_visible;
    CCPoint m_cursorPos;
    CCNode* m_visual;  // child node that represents the cursor

public:
    static CursorNode* create();
    bool init() override;
    void setVisible(bool visible) override;

    void onEnter() override;
    void onExit() override;

    void updatePosition(const CCPoint& pos);

    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;
};
