#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CursorNode : public CCNode, public CCTouchDelegate {
protected:
    bool m_visible;
    CCPoint m_cursorPos;
    float m_radius;
    float m_scale;            // size multiplier
    float m_sensitivity;      // not used yet (for relative movement)
    ccColor4B m_color;        // color from hex
    std::string m_shape;      // "crosshair", "dot", "arrow"

public:
    static CursorNode* create();
    bool init() override;
    void setVisible(bool visible) override;
    void draw() override;

    void onEnter() override;
    void onExit() override;

    void showAfterDelay(float delay);
    void showMe();

    // Called when settings change to update stored values
    void refreshSettings();

    void updatePosition(const CCPoint& pos);
    CCPoint getCursorPos() const { return m_cursorPos; }

    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;
};
