#include "LayerOptions.h"
#include "NumberCell.h"
#include "Config.h"

LayerOptions::LayerOptions(void)
{
}


LayerOptions::~LayerOptions(void)
{
}

void LayerOptions::keyBackClicked( void )
{
	CCDirector::sharedDirector()->popScene();
}

CCScene* LayerOptions::scene()
{
	CCScene* scene = CCScene::create();

	LayerOptions* layer = LayerOptions::create();

	scene->addChild(layer);

	return scene;

}

bool LayerOptions::init()
{
	bool bRet = false;
	do 
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


		CC_BREAK_IF(!initWithColor(ccc4(250, 248, 239,255)));

		CCLabelTTF* label = CCLabelTTF::create("OPTIONS","Arial Bold",32,
			CCSize(visibleSize.width,visibleSize.height*0.7),CCTextAlignment::kCCTextAlignmentCenter);

		CC_BREAK_IF(!label);

		label->setColor(ccc3(119,110,101));
		label->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

		this->addChild(label);


		float menuX = visibleSize.width*0.4;
		float menuY = menuX*0.3;


		TitleRect *titleContinue = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,"Continue");
		CCMenuItemLabel *MenuContinue = CCMenuItemLabel::create(titleContinue,this,menu_selector(LayerOptions::menuContinue));

		TitleRect *titleExit = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,"Exit");
		CCMenuItemLabel *MenuExit = CCMenuItemLabel::create(titleExit,this,menu_selector(LayerOptions::menuExit));


		TitleRect *titleSound = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,Config::shareConfig()->bSound?"Sound on":"Sound off");
		CCMenuItemLabel *MenuSound = CCMenuItemLabel::create(titleSound,this,menu_selector(LayerOptions::menuSound));

		CCString *textMax = CCString::createWithFormat("Max:%d",1 << Config::shareConfig()->maxTitle);

		TitleRect *titleMax = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,textMax->getCString());
		CCMenuItemLabel *MenuMax = CCMenuItemLabel::create(titleMax,this,menu_selector(LayerOptions::menuContinue));

		MenuMax->setEnabled(false);

		CCMenu *menu = CCMenu::create(MenuContinue,MenuExit,MenuSound,MenuMax,NULL);

		menu->alignItemsVerticallyWithPadding(menuY*0.5);

		this->addChild(menu);

		this->setKeypadEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void LayerOptions::menuContinue( CCObject *pSender )
{
	CCDirector::sharedDirector()->popScene();
}

void LayerOptions::menuExit( CCObject *pSender )
{
	CCDirector::sharedDirector()->end();
}

void LayerOptions::menuSound( CCObject *pSender )
{
	bool &bSound = Config::shareConfig()->bSound;
	
	bSound = !bSound;
	
	TitleRect *title = (TitleRect*)(((CCMenuItemLabel*)pSender)->getLabel());

	title->SetTitle(bSound?"Sound on":"Sound off");
	
}
