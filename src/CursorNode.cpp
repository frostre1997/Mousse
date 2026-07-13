#include "CursorNode.hpp"

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
    m_cursorPos = CCDirector::sharedDirector()->getWinSize() / 2;
    m_prevTouchPos = CCPointZero;
    m_radius = 15.0f;
    m_scale = 1.0f;
    m_sensitivity = 1.0f;
    m_color = ccc4(255, 255, 255, 255);
    m_shape = "crosshair";

    setContentSize(CCSize(40, 40));
    CCNode::setVisible(false);

    refreshSettings();
    setPosition(m_cursorPos);
    return true;
}

void CursorNode::refreshSettings() {
    auto mod = Mod::get();
    if (!mod) return;

    m_scale = mod->getSettingValue<double>("cursor-size");
    m_sensitivity = mod->getSettingValue<double>("sensitivity");
    m_visible = mod->getSettingValue<bool>("show-cursor");

    std::string hex = mod->getSettingValue<std::string>("color");
    if (hex.empty() || hex[0] != '#') hex = "#FFFFFF";
    unsigned int r, g, b;
    sscanf(hex.c_str() + 1, "%02x%02x%02x", &r, &g, &b);
    m_color = ccc4(r, g, b, 255);

    m_shape = mod->getSettingValue<std::string>("shape");
    if (m_shape != "crosshair" && m_shape != "dot" && m_shape != "arrow") {
        m_shape = "crosshair";
    }

    // Show immediately if settings say visible
    CCNode::setVisible(m_visible);
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCNode::setVisible(visible);
}

void CursorNode::onEnter() {
    CCNode::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, false);
}

void CursorNode::onExit() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

void CursorNode::draw() {
    if (!m_visible) return;

    float r = m_radius * m_scale;
    float offset = 2 * m_scale;

    // Shadow
    ccDrawColor4B(0, 0, 0, 100);
    glLineWidth(4.0f * m_scale);

    if (m_shape == "crosshair") {
        ccDrawLine(ccp(m_cursorPos.x - r + offset, m_cursorPos.y + offset),
                   ccp(m_cursorPos.x + r + offset, m_cursorPos.y + offset));
        ccDrawLine(ccp(m_cursorPos.x + offset, m_cursorPos.y - r + offset),
                   ccp(m_cursorPos.x + offset, m_cursorPos.y + r + offset));
        ccDrawCircle(m_cursorPos + ccp(offset, offset), r, 0, 16, false);
    }
    else if (m_shape == "dot") {
        ccDrawCircle(m_cursorPos + ccp(offset, offset), r * 0.5, 0, 16, true);
    }
    else if (m_shape == "arrow") {
        CCPoint p1 = ccp(m_cursorPos.x + offset, m_cursorPos.y + r + offset);
        CCPoint p2 = ccp(m_cursorPos.x - r + offset, m_cursorPos.y - r + offset);
        CCPoint p3 = ccp(m_cursorPos.x + r + offset, m_cursorPos.y - r + offset);
        ccDrawLine(p1, p2);
        ccDrawLine(p1, p3);
        ccDrawLine(p2, p3);
    }

    // Main drawing
    ccDrawColor4B(m_color.r, m_color.g, m_color.b, 255);
    glLineWidth(2.0f * m_scale);

    if (m_shape == "crosshair") {
        ccDrawLine(ccp(m_cursorPos.x - r, m_cursorPos.y),
                   ccp(m_cursorPos.x + r, m_cursorPos.y));
        ccDrawLine(ccp(m_cursorPos.x, m_cursorPos.y - r),
                   ccp(m_cursorPos.x, m_cursorPos.y + r));
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

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    m_prevTouchPos = touch->getLocation();
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint currentPos = touch->getLocation();
    float dx = (currentPos.x - m_prevTouchPos.x) * m_sensitivity;
    float dy = (currentPos.y - m_prevTouchPos.y) * m_sensitivity;

    m_cursorPos.x += dx;
    m_cursorPos.y += dy;

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    m_cursorPos.x = std::max(0.0f, std::min(winSize.width, m_cursorPos.x));
    m_cursorPos.y = std::max(0.0f, std::min(winSize.height, m_cursorPos.y));

    setPosition(m_cursorPos);
    m_prevTouchPos = currentPos;
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {}
void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {}
