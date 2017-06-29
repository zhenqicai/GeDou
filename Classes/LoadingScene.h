#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

class Loading : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	//设置进度条
	void SetPro(float fRate);
	//资源预加载
	void LoadRec();
	//资源预加载回调函数
	void OnLoadArmatureData(float percent);
	//资源加载回调
	void OnLoadRecCallBack(Object *pObj);

    CREATE_FUNC(Loading);

protected:
	int	m_nLoadRecNum;				//资源加载数
	int	m_nLoadRecTotalNum;			//资源加载总数

	ui::LoadingBar* pProLoadRec;    //进度条
};

#endif // __LOADING_SCENE_H__
