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
    m_cursorPos = CCDirector::sharedDirector()->getWinSize() / 2;
    m_radius = 20.0f;

    // Create a draw node and add it as child
    m_drawNode = CCDrawNode::create();
    m_drawNode->setZOrder(100);
    this->addChild(m_drawNode);

    setPosition(m_cursorPos);
    CCNode::setVisible(true);

    // Schedule update to redraw every frame
    this->scheduleUpdate();

    log::info("CursorNode initialized with CCDrawNode.");
    return true;
}

void CursorNode::update(float dt) {
    if (!m_visible || !m_drawNode) return;

    // Clear previous drawing
    m_drawNode->clear();

    // Draw a bright red circle with a white border
    m_drawNode->drawDot(m_cursorPos, m_radius, ccc4f(255, 0, 0, 255));
    m_drawNode->drawDot(m_cursorPos, m_radius * 0.7f, ccc4f(255, 255, 255, 200));
    // Also draw a crosshair for fun
    float r = m_radius * 1.2f;
    m_drawNode->drawSegment(ccp(m_cursorPos.x - r, m_cursorPos.y),
                            ccp(m_cursorPos.x + r, m_cursorPos.y),
                            2.0f, ccc4f(255, 255, 255, 150));
    m_drawNode->drawSegment(ccp(m_cursorPos.x, m_cursorPos.y - r),
                            ccp(m_cursorPos.x, m_cursorPos.y + r),
                            2.0f, ccc4f(255, 255, 255, 150));
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
    // The draw node will redraw on the next update.
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    updatePosition(touch->getLocation());
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {}
void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {}
