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

    // White color with a slight shadow effect (draw twice)
    ccDrawColor4B(0, 0, 0, 100);  // Shadow
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

    // Main white drawing
    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(2.0f);

    // Horizontal line
    ccDrawLine(
        ccp(m_cursorPos.x - m_radius, m_cursorPos.y),
        ccp(m_cursorPos.x + m_radius, m_cursorPos.y)
    );
    // Vertical line
    ccDrawLine(
        ccp(m_cursorPos.x, m_cursorPos.y - m_radius),
        ccp(m_cursorPos.x, m_cursorPos.y + m_radius)
    );
    // Circle around
    ccDrawCircle(m_cursorPos, m_radius, 0, 16, false);
}

void CursorNode::updatePosition(const CCPoint& pos) {
    m_cursorPos = pos;
    setPosition(pos);
}

// Touch Delegate
void CursorNode::registerWithTouchDispatcher() {
    // Priority -500 means we get touches first, but `false` means we DON'T swallow them
    CCDirector::get()->getTouchDispatcher()->addTargetedDelegate(this, -500, false);
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    // We always want to listen to moves/ends
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    auto pos = touch->getLocation();
    updatePosition(pos);
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    // Nothing needed here – game gets the click since we don't swallow
}

void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
    // Nothing needed
}
