#include "CursorNode.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

CursorNode* CursorNode::create() {
    auto ret = new CursorNode();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CursorNode::init() {
    if (!CCNode::init()) return false;

    m_visible = false;
    m_cursorPos = CCPointZero;
    m_radius = 15.0f;
    m_scale = 1.0f;
    m_sensitivity = 1.0f;
    m_color = ccc4(255, 255, 255, 255);
    m_shape = "crosshair";

    setContentSize(CCSize(40, 40));
    CCNode::setVisible(false);

    refreshSettings(); // load initial settings
    return true;
}

void CursorNode::refreshSettings() {
    auto mod = Mod::get();
    m_scale = mod->getSettingValue<float>("cursor-size");
    m_sensitivity = mod->getSettingValue<float>("sensitivity");
    m_visible = mod->getSettingValue<bool>("show-cursor");
    // color: parse hex to ccColor4B
    std::string hex = mod->getSettingValue<std::string>("color");
    if (hex.empty() || hex[0] != '#') hex = "#FFFFFF";
    // parse RGB
    unsigned int r, g, b;
    sscanf(hex.c_str() + 1, "%02x%02x%02x", &r, &g, &b);
    m_color = ccc4(r, g, b, 255);

    m_shape = mod->getSettingValue<std::string>("shape");
    if (m_shape != "crosshair" && m_shape != "dot" && m_shape != "arrow") {
        m_shape = "crosshair";
    }

    // Also update visibility
    CCNode::setVisible(m_visible);
    // Force redraw
    setNeedRedraw();
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCNode::setVisible(visible);
    setNeedRedraw();
}

void CursorNode::showMe() {
    setVisible(true);
}

void CursorNode::showAfterDelay(float delay) {
    this->runAction(CCSequence::create(
        CCDelayTime::create(delay),
        CCCallFunc::create(this, callfunc_selector(CursorNode::showMe)),
        nullptr
    ));
}

void CursorNode::onEnter() {
    CCNode::onEnter();
    CCDirector::get()->getTouchDispatcher()->addTargetedDelegate(this, -500, false);
    // Listen to setting changes to refresh
    auto mod = Mod::get();
    mod->registerSettingChangedCallback("cursor-size", [this](float) { refreshSettings(); });
    mod->registerSettingChangedCallback("sensitivity", [this](float) { refreshSettings(); });
    mod->registerSettingChangedCallback("show-cursor", [this](bool) { refreshSettings(); });
    mod->registerSettingChangedCallback("color", [this](std::string) { refreshSettings(); });
    mod->registerSettingChangedCallback("shape", [this](std::string) { refreshSettings(); });
    // Note: invert-scroll we'll handle separately if we add scrolling
}

void CursorNode::onExit() {
    CCDirector::get()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

void CursorNode::draw() {
    if (!m_visible) return;

    // Scale everything
    float r = m_radius * m_scale;
    float offset = 2 * m_scale; // shadow offset

    // Setup color
    ccDrawColor4B(m_color.r, m_color.g, m_color.b, 255);

    // Shadow (offset and darker)
    ccDrawColor4B(0, 0, 0, 100);
    glLineWidth(4.0f * m_scale);

    if (m_shape == "crosshair") {
        // Draw crosshair with circle
        ccDrawLine(
            ccp(m_cursorPos.x - r + offset, m_cursorPos.y + offset),
            ccp(m_cursorPos.x + r + offset, m_cursorPos.y + offset)
        );
        ccDrawLine(
            ccp(m_cursorPos.x + offset, m_cursorPos.y - r + offset),
            ccp(m_cursorPos.x + offset, m_cursorPos.y + r + offset)
        );
        ccDrawCircle(m_cursorPos + ccp(offset, offset), r, 0, 16, false);
    }
    else if (m_shape == "dot") {
        ccDrawCircle(m_cursorPos + ccp(offset, offset), r * 0.5, 0, 16, true);
    }
    else if (m_shape == "arrow") {
        // Simple arrow: triangle pointing up
        CCPoint p1 = ccp(m_cursorPos.x + offset, m_cursorPos.y + r + offset);
        CCPoint p2 = ccp(m_cursorPos.x - r + offset, m_cursorPos.y - r + offset);
        CCPoint p3 = ccp(m_cursorPos.x + r + offset, m_cursorPos.y - r + offset);
        ccDrawLine(p1, p2);
        ccDrawLine(p1, p3);
        ccDrawLine(p2, p3);
    }

    // Main drawing (same as above but with user color)
    ccDrawColor4B(m_color.r, m_color.g, m_color.b, 255);
    glLineWidth(2.0f * m_scale);

    if (m_shape == "crosshair") {
        ccDrawLine(
            ccp(m_cursorPos.x - r, m_cursorPos.y),
            ccp(m_cursorPos.x + r, m_cursorPos.y)
        );
        ccDrawLine(
            ccp(m_cursorPos.x, m_cursorPos.y - r),
            ccp(m_cursorPos.x, m_cursorPos.y + r)
        );
        ccDrawCircle(m_cursorPos, r, 0, 16, false);
    }
    else if (m_shape == "dot") {
        ccDrawCircle(m_cursorPos, r * 0.5, 0, 16, true);
    }
    else if (m_shape == "arrow") {
        CCPoint p1 = ccp(m_cursorPos.x, m_cursorPos.y + r);
        CCPoint p2 = ccp(m_cursorPos.x - r, m_cursorPos.y - r);
        CCPoint p3 = ccp(m_cursorPos.x + r, m_cursorPos.y - r);
        ccDrawLine(p1, p2);
        ccDrawLine(p1, p3);
        ccDrawLine(p2, p3);
    }
}

void CursorNode::updatePosition(const CCPoint& pos) {
    m_cursorPos = pos;
    setPosition(pos);
    setNeedRedraw();
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    updatePosition(touch->getLocation());
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    // nothing
}

void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
    // nothing
}
