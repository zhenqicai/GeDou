#include "ChooseHero.h"
#include "HeroSelectLayer.h"

#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace cocostudio;


Scene * ChooseHero::createScene(){
	auto scene = Scene::create();
	auto layer = ChooseHero::create();
	scene->addChild(layer);
	return scene;
}

bool ChooseHero::init(){
	if (!Layer::init()){
		return false;
	}
	m_nRoleID = 1;

	//创建主场景UI层
	
	auto pCreateNinja = GUIReader::getInstance()->widgetFromJsonFile("CreateNinja.json");
	addChild(pCreateNinja, 100, enTagStudioMainUiLayer);
	pCreateNinja->setName("CreateNinjaLayer");
	pCreateNinja->setSize(getContentSize());

	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/xiaoyin.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/NewProject.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/minren1.ExportJson");

	////获取开始按钮
	Button *pBtn_Create_Team = dynamic_cast<Button*>(pCreateNinja->getChildByName("MainUi")->getChildByName("Btn_Create_Team"));
	pBtn_Create_Team->addTouchEventListener(this, toucheventselector(ChooseHero::OnGameStartPage));

	////获取输入框
	TextField* pTextField = dynamic_cast<TextField*>(pCreateNinja->getChildByName("MainUi")->getChildByName("Team_Name_TextField"));
	//CC_BREAK_IF(pTextField == NULL);
	pTextField->setTouchEnabled(true);
	//pTextField->addEventListenerTextField(this, textfieldeventselector(CNFTeamCreateLayer::textFieldEvent));
	pTextField->setText("");

	//获取人物按钮
	pBtn_Role = static_cast<Button*>(pCreateNinja->getChildByName("MainUi")->getChildByName(String::createWithFormat("Btn_Char_%d", 0 + 1)->getCString()));
	pBtn_Role2 = static_cast<Button*>(pCreateNinja->getChildByName("MainUi")->getChildByName(String::createWithFormat("Btn_Char_%d", 1 + 1)->getCString()));
	pBtn_Role3 = static_cast<Button*>(pCreateNinja->getChildByName("MainUi")->getChildByName(String::createWithFormat("Btn_Char_%d", 2 + 1)->getCString()));

	pSelect_Img = static_cast<ImageView*>(pBtn_Role->getChildByName("Select_Img"));
	pSelect_Img2 = static_cast<ImageView*>(pBtn_Role2->getChildByName("Select_Img"));
	pSelect_Img3 = static_cast<ImageView*>(pBtn_Role3->getChildByName("Select_Img"));

	pBtn_Role->addTouchEventListener(this, toucheventselector(ChooseHero::OnRoleSelect));
	pBtn_Role2->addTouchEventListener(this, toucheventselector(ChooseHero::OnRoleSelect2));
	pBtn_Role3->addTouchEventListener(this, toucheventselector(ChooseHero::OnRoleSelect3));
		
	pSelect_Img->setVisible(true);
	
	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/xiaoyin.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/NewProject.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/minren1.ExportJson");

	char cName[3][256] = { "minren1", "xiaoyin", "NewProject" };

	Armature *pRole = Armature::create(cName[0]);
	pRole->setPosition(ccp(640/ 2, 210));
	pRole->setAnchorPoint(ccp(pRole->getAnchorPoint().x, 0));
	pRole->getAnimation()->play("hold");
	addChild(pRole, 100000, enTagRole);

	return true;

}
//创建人物
void ChooseHero::OnGameStartPage(Object *pSender, Widget::TouchEventType type){
	auto heroScene = HeroSelectLayer::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.f, heroScene));
}

void ChooseHero::textFieldEvent(Object* pSender, Event type)
{

}

void ChooseHero::OnRoleSelect(CCObject *pSender, Widget::TouchEventType type){
	if (pBtn_Role == pSender){
		pSelect_Img2->setVisible(false);
		pSelect_Img3->setVisible(false);
		pSelect_Img->setVisible(true);
		m_nRoleID = 1;

		removeChildByTag(enTagRole);

		char cName[3][256] = { "minren1", "xiaoyin", "NewProject" };

		Armature *pRole = Armature::create(cName[0]);
		pRole->setPosition(ccp(640 / 2, 210));
		pRole->setAnchorPoint(ccp(pRole->getAnchorPoint().x, 0));
		pRole->getAnimation()->play("hold");
		addChild(pRole, 100000, enTagRole);
	}
	else{
		pSelect_Img->setVisible(false);
	}
}

void ChooseHero::OnRoleSelect3(CCObject *pSender, Widget::TouchEventType type){
	if (pBtn_Role3 == pSender){
		pSelect_Img->setVisible(false);
		pSelect_Img2->setVisible(false);
		pSelect_Img3->setVisible(true);
		m_nRoleID = 3;

		removeChildByTag(enTagRole);

		char cName[3][256] = { "minren1", "xiaoyin", "NewProject" };

		Armature *pRole = Armature::create(cName[2]);
		pRole->setPosition(ccp(640 / 2, 210));
		pRole->setAnchorPoint(ccp(pRole->getAnchorPoint().x, 0));
		pRole->getAnimation()->play("hold");
		addChild(pRole, 100000, enTagRole);


	}
	else{
		pSelect_Img3->setVisible(false);
	}
}

//角色选择界面
void ChooseHero::OnRoleSelect2(CCObject *pSender, Widget::TouchEventType type){
	if (pBtn_Role2 == pSender){
		pSelect_Img->setVisible(false);
		pSelect_Img3->setVisible(false);
		pSelect_Img2->setVisible(true);
		m_nRoleID = 2;

		removeChildByTag(enTagRole);

		char cName[3][256] = { "minren1", "xiaoyin", "NewProject" };

		Armature *pRole = Armature::create(cName[1]);
		pRole->setPosition(ccp(640 / 2, 210));
		pRole->setAnchorPoint(ccp(pRole->getAnchorPoint().x, 0));
		pRole->getAnimation()->play("hold");
		addChild(pRole, 100000, enTagRole);
	}
	else{
		pSelect_Img2->setVisible(false);
	}
}