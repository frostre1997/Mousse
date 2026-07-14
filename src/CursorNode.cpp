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
    if (!CCLayer::init()) return false;
    m_visible = true;
    setVisible(true);
    return true;
}

void CursorNode::setVisible(bool visible) {
    m_visible = visible;
    CCLayer::setVisible(visible);
}

void CursorNode::draw() {
    if (!m_visible) return;

    auto pos = getPosition();

    ccDrawColor4B(255, 0, 0, 255);
    glLineWidth(3.0f);
    ccDrawCircle(pos, 25.0f, 0, 20, false);

    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(2.0f);
    ccDrawLine(ccp(pos.x - 30, pos.y), ccp(pos.x + 30, pos.y));
    ccDrawLine(ccp(pos.x, pos.y - 30), ccp(pos.x, pos.y + 30));
}
