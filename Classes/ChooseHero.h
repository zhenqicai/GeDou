#ifndef __CHOOSE_HERO_H__
#define __CHOOSE_HERO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;

USING_NS_CC;

class ChooseHero : public Layer
{
public:
	static Scene * createScene();

	virtual bool init();

	void OnGameStartPage(Object *pSender, Widget::TouchEventType type);	//创建人物

	void textFieldEvent(Object* pSender, Event type);

	//void OnBackToLoginPage(Object *pSender, Event type);//返回登录界面

	void OnRoleSelect(CCObject *pSender, Widget::TouchEventType type);	//角色选择界面
	void OnRoleSelect2(CCObject *pSender, Widget::TouchEventType type);	//角色选择界面
	void OnRoleSelect3(CCObject *pSender, Widget::TouchEventType type);	//角色选择界面

	bool OnRoleSelectMy(Touch *touch, Event *event);
	CREATE_FUNC(ChooseHero);

protected:
	//标签
	enum
	{
		enTagStudioMainUiLayer,
		enTagRole,
	};

	int	m_nRoleID;	//角色ID 1.鸣人	2.小樱	3.佐助

	int btnIndex2;

	Button* pBtn_Role ;
	Button* pBtn_Role2;
	Button* pBtn_Role3;

	ImageView * pSelect_Img ;
	ImageView * pSelect_Img2;
	ImageView * pSelect_Img3;
};

#endif
