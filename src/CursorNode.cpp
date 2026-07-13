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
    m_visible = true;
    setVisible(true);
    
    // Enable touch - NO manual dispatcher registration!
    this->setTouchEnabled(true);
    this->setTouchPriority(-500);
    
    return true;
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCNode::setVisible(visible);
}

// COMPLETELY REMOVE onEnter() - causes crash!
// void CursorNode::onEnter() {
//     CCNode::onEnter();
//     CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, false);
// }

// COMPLETELY REMOVE onExit() - causes crash!
// void CursorNode::onExit() {
//     CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//     CCNode::onExit();
// }

void CursorNode::draw() {
    if (!m_visible) return;
    auto pos = getPosition();
    
    // Red circle with white crosshair – very visible
    ccDrawColor4B(255, 0, 0, 255);
    glLineWidth(3.0f);
    ccDrawCircle(pos, 25.0f, 0, 20, false);
    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(2.0f);
    ccDrawLine(ccp(pos.x - 30, pos.y), ccp(pos.x + 30, pos.y));
    ccDrawLine(ccp(pos.x, pos.y - 30), ccp(pos.x, pos.y + 30));
}

bool CursorNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    auto pos = touch->getLocation();
    auto winSize = CCDirector::get()->getWinSize();
    pos.x = std::max(0.0f, std::min(winSize.width, pos.x));
    pos.y = std::max(0.0f, std::min(winSize.height, pos.y));
    setPosition(pos);
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {}
void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {}
