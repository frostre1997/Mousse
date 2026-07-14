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
    // Initialize CCLayer
    if (!CCLayer::init()) return false;
    
    m_visible = true;
    setVisible(true);
    
    // Set touch priority
    this->setTouchPriority(-500);
    this->setTouchMode(ccTouchesMode::kCCTouchesOneByOne);
    
    // REMOVED: setIsRelativeAnchorPoint - doesn't exist!
    
    log::info("[Mousse] CursorNode initialized!");
    
    return true;
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCLayer::setVisible(visible);
}

void CursorNode::draw() {
    if (!m_visible) {
        log::info("[Mousse] Cursor is hidden, skipping draw");
        return;
    }
    
    auto pos = getPosition();
    log::info("[Mousse] Drawing cursor at position: {}x{}", pos.x, pos.y);
    
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
    log::info("[Mousse] Touch began!");
    return true;
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    auto pos = touch->getLocation();
    auto winSize = CCDirector::get()->getWinSize();
    pos.x = std::max(0.0f, std::min(winSize.width, pos.x));
    pos.y = std::max(0.0f, std::min(winSize.height, pos.y));
    setPosition(pos);
    log::info("[Mousse] Touch moved to: {}x{}", pos.x, pos.y);
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    log::info("[Mousse] Touch ended");
}

void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
    log::info("[Mousse] Touch cancelled");
}
