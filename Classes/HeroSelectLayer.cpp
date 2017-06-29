#include "HeroSelectLayer.h"


Scene* HeroSelectLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = HeroSelectLayer::create();
	scene->addChild(layer);
	return scene;
}


bool HeroSelectLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);
	return true;
}
