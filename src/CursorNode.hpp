#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CursorNode : public CCNode, public CCTouchDelegate {
protected:
    bool m_visible;
    CCPoint m_cursorPos;
    float m_radius;

public:
    static CursorNode* create();
    bool init() override;
    void setVisible(bool visible) override;   // now override
    void draw() override;

    void onEnter() override;                  // register touch
    void onExit() override;                   // unregister

    void updatePosition(const CCPoint& pos);
    CCPoint getCursorPos() const { return m_cursorPos; }

    // Touch handling – no override needed
    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;
};
