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
    
    // IMPORTANT: Enable touch and set priority
    this->setTouchEnabled(true);
    this->setTouchPriority(-1000);  // Very high priority (-1000)
    this->setTouchMode(ccTouchesMode::kCCTouchesOneByOne);
    
    // Important: Allow touches even if parent blocks them
    this->setSwallowTouches(false);
    
    log::info("[Mousse] CursorNode initialized with touch enabled!");
    
    return true;
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCLayer::setVisible(visible);
}

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
    log::info("[Mousse] Touch BEGAN at: {}x{}", touch->getLocation().x, touch->getLocation().y);
    return true;  // Accept the touch
}

void CursorNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    auto pos = touch->getLocation();
    auto winSize = CCDirector::get()->getWinSize();
    pos.x = std::max(0.0f, std::min(winSize.width, pos.x));
    pos.y = std::max(0.0f, std::min(winSize.height, pos.y));
    setPosition(pos);
    log::info("[Mousse] Touch MOVED to: {}x{}", pos.x, pos.y);
}

void CursorNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    log::info("[Mousse] Touch ENDED");
}

void CursorNode::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
    log::info("[Mousse] Touch CANCELLED");
}
