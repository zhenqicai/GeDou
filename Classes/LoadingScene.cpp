#include "LoadingScene.h"
#include "ChooseHero.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;

Scene* Loading::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Loading::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Loading::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size size = Director::getInstance()->getWinSize();
	/************************************************************************/
	/*				背景图片                                                */
	/************************************************************************/
	//人物图片
	auto pPersonBg = Sprite::create("ui/loading_bg.png");
	pPersonBg->setPosition(ccp(size.width*0.5f, size.height*0.5f));
	addChild(pPersonBg, 100);

	//创建logo图
	auto pLogo = Sprite::create("ui/logo_bg.png");
	pLogo->setScale(0.95f);
	pLogo->setPosition(ccp(size.width*0.5f, 410));
	addChild(pLogo, 100);

	/************************************************************************/
	/*				进度条                                                  */
	/************************************************************************/
	//创建加载进度条背景
	auto pProBg = Sprite::create("ui/loading_progress_bg.png");
	pProBg->setPosition(ccp(size.width*0.5f, 100));
	addChild(pProBg, 100000);

	pProLoadRec = ui::LoadingBar::create("ui/loading_progress_bar.png");
	pProLoadRec->setPosition(pProBg->getPosition());
	pProLoadRec->setDirection(ui::LoadingBar::Direction::LEFT);
	pProLoadRec->setPercent(0);
	addChild(pProLoadRec, 100001, 1);//同时设置Tag值为1
	
	auto pLight = Sprite::create("ui/loading_progress_light.png");
	addChild(pLight, 300000, 2);
	pLight->setPosition(ccp(pProLoadRec->getPositionX() - pProLoadRec->getContentSize().width*0.5f, pProLoadRec->getPositionY()));

	m_nLoadRecNum = 0;
	m_nLoadRecTotalNum = 16;

	//预加载本层资源
	LoadRec();
    
    return true;
}

void Loading::SetPro(float fRate)
{
	do
	{
		pProLoadRec->setPercent(fRate * 100);

		//同步光点
		auto pLight = dynamic_cast<Sprite *>(getChildByTag(2));
		if (pLight != NULL)
			pLight->setPositionX(pProLoadRec->getPositionX() + pProLoadRec->getContentSize().width*(fRate - 0.5f));

		//若加载完成
		if (fRate >= 1)
		{
			auto pDicLang = Dictionary::createWithContentsOfFile("ui_xml/loading_xml.xml");
			
			//得到加载信息label
			auto pStrLoading = dynamic_cast<String*>(pDicLang->objectForKey("loading_end"));
			auto pLabelLoading = dynamic_cast<LabelTTF *>(getChildByTag(3));
			
			//pLabelLoading->setString(pStrLoading->getCString());
		}

		return;
	} while (false);
	//CCLog("Fun CNFLoadingLayer::SetPro Error!");
}

//资源预加载
void Loading::LoadRec()
{
	TextureCache::getInstance()->addImageAsync("ui/serverselect_bg.png", CC_CALLBACK_1(Loading::OnLoadRecCallBack,this));
	
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/kulougongshou.ExportJson",this,schedule_selector(Loading::OnLoadArmatureData,this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/kulouzhanshi.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/mayi.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/bianyikunchong.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/bubing.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/xiaoyin.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/NewProject.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/minren1.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/kulou_arrow.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/naili.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/NPC_kakaxi.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/portal.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/hited_light.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/public_casting.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/skill_light_1.ExportJson", this, schedule_selector(Loading::OnLoadArmatureData, this));
}

void Loading::OnLoadArmatureData(float percent){
	m_nLoadRecNum++;

	SetPro((float)m_nLoadRecNum / (float)m_nLoadRecTotalNum);

	if (m_nLoadRecNum == m_nLoadRecTotalNum){
		//延迟1秒
		Director::getInstance()->replaceScene(ChooseHero::createScene());
		//auto callf = CallFunc::create([this](){
		//	//Director::getInstance()->replaceScene(StartLayer::createScene());
		//	Director::getInstance()->replaceScene(TransitionPageTurn::create(2, ChooseHero::createScene(), false));
		//});
		//auto seq = Sequence::create(DelayTime::create(2.f), callf, NULL);
		//this->runAction(seq);
		/*this->runAction(Sequence::create(
			DelayTime::create(2.f),
			CallFunc::create(this, callfunc_selector(CNFLoginScene::InitSceneUI)),
			NULL));*/
	}
	if (percent >= 1)
	{
		//CCLog("addArmatureFileInfoAsync over");
	}
}

void Loading::OnLoadRecCallBack(Object *pObj){
	do
	{
		m_nLoadRecNum++;

		SetPro((float)m_nLoadRecNum / (float)m_nLoadRecTotalNum);
		if (m_nLoadRecNum == m_nLoadRecTotalNum){
			//延迟1秒
			Director::getInstance()->replaceScene(ChooseHero::createScene());
			//auto callf = CallFunc::create([this](){
			//	//Director::getInstance()->replaceScene(StartLayer::createScene());
			//	Director::getInstance()->replaceScene(TransitionPageTurn::create(2, ChooseHero::createScene(), false));
			//});
			//auto seq = Sequence::create(DelayTime::create(2.f), callf, NULL);
			//this->runAction(seq);
			/*this->runAction(CCSequence::create(
				CCDelayTime::create(2.f),
				CCCallFunc::create(this, callfunc_selector(CNFLoginScene::InitSceneUI)),
				NULL));*/
		}

		return;
	} while (false);
	//CCLog("Fun CNFLoginScene::OnLoadRecCallBack Error!");
}

