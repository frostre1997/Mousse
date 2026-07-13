#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "CursorNode.hpp"

using namespace geode::prelude;

CursorNode* g_cursor = nullptr;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        // 1. Full‑screen red layer – you will definitely see this
        auto redLayer = CCLayerColor::create(ccc4(255, 0, 0, 150));
        redLayer->setZOrder(99998);
        this->addChild(redLayer);

        // 2. Green label to confirm mod is loaded
        auto label = CCLabelBMFont::create("MOUSSE ACTIVE", "bigFont.fnt");
        if (label) {
            label->setScale(0.8f);
            label->setColor(ccc3(0, 255, 0));
            label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 100));
            label->setZOrder(100000);
            this->addChild(label);
        }

        // 3. Create and center the cursor
        if (!g_cursor) {
            g_cursor = CursorNode::create();
            if (g_cursor) {
                g_cursor->setZOrder(99999);
                this->addChild(g_cursor);
                g_cursor->setPosition(ccp(winSize.width / 2, winSize.height / 2));
                g_cursor->setVisible(true);
                log::info("Cursor created and centered.");
            }
        }

        return true;
    }
};

$on_mod(Loaded) {
    log::info("Mousse mod loaded (MenuLayer hook).");
}
