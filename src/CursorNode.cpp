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

    m_visible = true;
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    m_cursorPos = ccp(winSize.width / 2, winSize.height / 2);
    m_radius = 20.0f;

    m_drawNode = CCDrawNode::create();
    m_drawNode->setZOrder(100);
    this->addChild(m_drawNode);

    setPosition(m_cursorPos);
    CCNode::setVisible(true);
    this->scheduleUpdate();

    log::info("CursorNode initialized at center.");
    return true;
}

void CursorNode::update(float dt) {
    if (!m_visible || !m_drawNode) return;
    m_drawNode->clear();

    // Draw a white crosshair + dot
    float r = m_radius;
    m_drawNode->drawDot(m_cursorPos, r * 0.5f, ccc4f(1, 1, 1, 1));
    m_drawNode->drawSegment(ccp(m_cursorPos.x - r, m_cursorPos.y),
                            ccp(m_cursorPos.x + r, m_cursorPos.y),
                            2.0f, ccc4f(1, 1, 1, 1));
    m_drawNode->drawSegment(ccp(m_cursorPos.x, m_cursorPos.y - r),
                            ccp(m_cursorPos.x, m_cursorPos.y + r),
                            2.0f, ccc4f(1, 1, 1, 1));
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
