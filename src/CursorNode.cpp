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
    m_cursorPos = CCPointZero;
    m_radius = 15.0f;

    setContentSize(CCSize(40, 40));
    CCNode::setVisible(false);
    return true;
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCNode::setVisible(visible);
}

void CursorNode::showMe(CCObject* sender) {
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
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, false);
}

void CursorNode::onExit() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

void CursorNode::draw() {
    if (!m_visible) return;

    float r = m_radius;
    float offset = 2.0f;

    // Shadow
    ccDrawColor4B(0, 0, 0, 100);
    glLineWidth(4.0f);
    ccDrawLine(ccp(m_cursorPos.x - r + offset, m_cursorPos.y + offset),
               ccp(m_cursorPos.x + r + offset, m_cursorPos.y + offset));
    ccDrawLine(ccp(m_cursorPos.x + offset, m_cursorPos.y - r + offset),
               ccp(m_cursorPos.x + offset, m_cursorPos.y + r + offset));
    ccDrawCircle(m_cursorPos + ccp(offset, offset), r, 0, 16, false);

    // Main
    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(2.0f);
    ccDrawLine(ccp(m_cursorPos.x - r, m_cursorPos.y),
               ccp(m_cursorPos.x + r, m_cursorPos.y));
    ccDrawLine(ccp(m_cursorPos.x, m_cursorPos.y - r),
               ccp(m_cursorPos.x, m_cursorPos.y + r));
    ccDrawCircle(m_cursorPos, r, 0, 16, false);
}

void CursorNode::updatePosition(const CCPoint& pos) {
    m_cursorPos = pos;
    setPosition(pos);
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    updatePosition(touch->getLocation());
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {}
void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {}
