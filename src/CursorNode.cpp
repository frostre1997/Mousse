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

    // Create a simple 50x50 red square using a texture of a 1x1 pixel
    auto texture = CCTextureCache::sharedTextureCache()->addImage("square.png");
    if (!texture) {
        // If the image doesn't exist, create a colored sprite from a 1x1 texture
        // We'll just draw a colored sprite using a simple 1x1 texture created in code
        // Simpler: use a CCLayerColor? Actually we can create a CCSprite with a custom texture.
        // Easiest: use a CCRect with a solid color via CCSprite::createWithSpriteFrameName?
        // Let's create a 1x1 pixel texture using CCTexture2D::create(int width, int height) - not available.
        // Alternative: use CCLayerColor but it's a node that doesn't support positioning like a sprite.
        // Fallback: use a CCLabelTTF with a filled block character: "█"
        auto label = CCLabelTTF::create("█", "Arial", 50);
        label->setColor(ccc3(255, 0, 0));
        label->setPosition(ccp(0, 0)); // relative to this node
        this->addChild(label);
        m_sprite = label; // store as CCObject*
    } else {
        auto sprite = CCSprite::createWithTexture(texture);
        sprite->setScale(50);
        sprite->setColor(ccc3(255, 0, 0));
        sprite->setPosition(ccp(0, 0));
        this->addChild(sprite);
        m_sprite = sprite;
    }

    setPosition(m_cursorPos);
    CCNode::setVisible(true);

    log::info("CursorNode initialized with sprite.");
    return true;
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
