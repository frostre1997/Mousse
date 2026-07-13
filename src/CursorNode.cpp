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
    m_radius = 30.0f; // larger for visibility
    setContentSize(CCSize(100, 100));
    CCNode::setVisible(true);

    log::info("CursorNode initialized.");
    return true;
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

    auto pos = getPosition();

    // Draw a big red dot with white outline
    ccDrawColor4B(255, 0, 0, 255); // red
    glLineWidth(4.0f);
    ccDrawCircle(pos, m_radius, 0, 20, false);

    ccDrawColor4B(255, 255, 255, 255); // white
    glLineWidth(2.0f);
    ccDrawCircle(pos, m_radius - 5, 0, 20, false);
    ccDrawLine(ccp(pos.x - m_radius * 0.7f, pos.y),
               ccp(pos.x + m_radius * 0.7f, pos.y));
    ccDrawLine(ccp(pos.x, pos.y - m_radius * 0.7f),
               ccp(pos.x, pos.y + m_radius * 0.7f));
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    setPosition(touch->getLocation());
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {}
void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {}
