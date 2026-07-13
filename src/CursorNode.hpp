#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CursorNode : public CCNode, public CCTouchDelegate {
protected:
    bool m_visible;
    CCPoint m_cursorPos;
    CCPoint m_prevTouchPos;   // for delta calculation
    float m_radius;
    float m_scale;
    float m_sensitivity;
    ccColor4B m_color;
    std::string m_shape;

public:
    static CursorNode* create();
    bool init() override;
    void setVisible(bool visible) override;
    void draw() override;

    void onEnter() override;
    void onExit() override;

    void showAfterDelay(float delay);
    void showMe(CCObject* sender);

    void refreshSettings();   // safe, no callbacks

    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;
};
