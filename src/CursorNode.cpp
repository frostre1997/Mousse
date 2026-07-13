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
    m_visual = nullptr;

    // Create a big "X" label – very visible
    auto label = CCLabelTTF::create("✚", "Arial", 60);
    // Or use "+" if the character doesn't render
    if (!label) {
        label = CCLabelTTF::create("+", "Arial", 60);
    }
    label->setColor(ccc3(255, 0, 0)); // bright red
    label->setPosition(ccp(0, 0));
    this->addChild(label);
    m_visual = label;

    setPosition(m_cursorPos);
    CCNode::setVisible(true);

    log::info("CursorNode initialized with label.");
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
