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

    m_visible = false;          // Hidden at startup
    m_cursorPos = CCPointZero;
    m_radius = 15.0f;

    setContentSize(CCSize(40, 40));
    setTouchEnabled(true);      // Enable touch listening
    setTouchMode(kCCTouchesOneByOne);

    return true;
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCNode::setVisible(visible);
}

void CursorNode::draw() {
    if (!m_visible) return;

    // Shadow (offset)
    ccDrawColor4B(0, 0, 0, 100);
    glLineWidth(4.0f);
    ccDrawLine(
        ccp(m_cursorPos.x - m_radius + 2, m_cursorPos.y + 2),
        ccp(m_cursorPos.x + m_radius + 2, m_cursorPos.y + 2)
    );
    ccDrawLine(
        ccp(m_cursorPos.x + 2, m_cursorPos.y - m_radius + 2),
        ccp(m_cursorPos.x + 2, m_cursorPos.y + m_radius + 2)
    );
    ccDrawCircle(m_cursorPos + ccp(2, 2), m_radius, 0, 16, false);

    // Main white
    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(2.0f);
    ccDrawLine(
        ccp(m_cursorPos.x - m_radius, m_cursorPos.y),
        ccp(m_cursorPos.x + m_radius, m_cursorPos.y)
    );
    ccDrawLine(
        ccp(m_cursorPos.x, m_cursorPos.y - m_radius),
        ccp(m_cursorPos.x, m_cursorPos.y + m_radius)
    );
    ccDrawCircle(m_cursorPos, m_radius, 0, 16, false);
}

void CursorNode::updatePosition(const CCPoint& pos) {
    m_cursorPos = pos;
    setPosition(pos);
}

void CursorNode::registerWithTouchDispatcher() {
    // Priority -500, and `false` means we do NOT swallow touches
    CCDirector::get()->getTouchDispatcher()->addTargetedDelegate(this, -500, false);
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true; // We want to receive move/end events
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    auto pos = touch->getLocation();
    updatePosition(pos);
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    // Nothing – game gets the click because we don't swallow
}

void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
    // Nothing
}
