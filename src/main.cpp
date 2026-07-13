#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <fstream>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 1. Write a test file to external storage
        std::ofstream file("/storage/emulated/0/mousse_loaded.txt");
        if (file.is_open()) {
            file << "Mousse mod is running!" << std::endl;
            file.close();
        }

        // 2. Add a full‑screen red layer – you WILL see this
        auto redLayer = CCLayerColor::create(ccc4(255, 0, 0, 200)); // semi‑transparent red
        redLayer->setZOrder(99999);
        this->addChild(redLayer);

        // 3. Draw a white cursor at the center of the screen
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        auto center = ccp(winSize.width / 2, winSize.height / 2);

        // Use a CCDrawNode to draw a white dot with a crosshair
        auto drawNode = CCDrawNode::create();
        drawNode->setZOrder(100000); // above red layer
        this->addChild(drawNode);

        float radius = 20.0f;
        // White dot
        drawNode->drawDot(center, radius, ccc4f(1, 1, 1, 1));
        // White crosshair lines
        drawNode->drawSegment(ccp(center.x - radius * 1.5f, center.y),
                              ccp(center.x + radius * 1.5f, center.y),
                              2.0f, ccc4f(1, 1, 1, 1));
        drawNode->drawSegment(ccp(center.x, center.y - radius * 1.5f),
                              ccp(center.x, center.y + radius * 1.5f),
                              2.0f, ccc4f(1, 1, 1, 1));

        // 4. (Optional) Add a label to be extra sure
        auto label = CCLabelBMFont::create("MOUSSE CENTER", "bigFont.fnt");
        if (label) {
            label->setScale(0.8f);
            label->setColor(ccc3(0, 255, 0));
            label->setPosition(ccp(center.x, center.y - 100));
            label->setZOrder(100001);
            this->addChild(label);
        }

        log::info("Mousse mod injected into MenuLayer");
        return true;
    }
};

$on_mod(Loaded) {
    // Also write from this hook (earlier)
    std::ofstream file("/storage/emulated/0/mousse_onmod.txt");
    if (file.is_open()) {
        file << "on_mod_loaded called!" << std::endl;
        file.close();
    }
}
