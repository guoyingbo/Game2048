#include "ModelDialog.h"
#include "NumberCell.h"

ModelDialog* ModelDialog::create( const char* title ,CCObject* caller,SEL_CallFunc func,int type )
{
	ModelDialog* pRet = new ModelDialog(caller,func);
	if (pRet && pRet->init(title,type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

ModelDialog::ModelDialog( CCObject* caller,SEL_CallFunc func )
	: m_caller(caller),m_func(func)
{

}

bool ModelDialog::init( const char* title,int type )
{
	bool bRes = false;

	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(255,255,255,100)));

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		float rectX = visibleSize.width*0.8f;
		float rectY = rectX*0.5f;
		ColorRect* rect = ColorRect::create(ccc4(187, 173, 160, 255),rectX,rectY);

		CC_BREAK_IF(!rect);

		rect->setPosition(origin.x +( visibleSize.width-rectX)/2,origin.y+(visibleSize.height-rectY)/2);

		this->addChild(rect,1);


		CCMenuItemFont* itemYes = CCMenuItemFont::create("Yes",this,menu_selector(ModelDialog::menuYes));

		CCMenuItemFont* itemNo = CCMenuItemFont::create("No",this,menu_selector(ModelDialog::menuNo));

		itemYes->setFontNameObj("Arial Bold");
		itemYes->setFontSizeObj(rectY*0.15);
		itemYes->setColor(ccc3(119,110,101));

		itemNo->setFontNameObj("Arial Bold");
		itemNo->setFontSizeObj(rectY*0.15);
		itemNo->setColor(ccc3(119,110,101));

		CCMenu *menu = CCMenu::create(itemNo,itemYes,NULL);

		CC_BREAK_IF(!itemYes || !itemNo || !menu);

		menu->setTouchPriority(kCCMenuHandlerPriority*2-1);

		this->addChild(menu,2);

		menu->setPositionY(origin.y+visibleSize.height*0.5 - rectY*0.3);


		menu->alignItemsHorizontallyWithPadding(rectX*0.4);


		CCLabelTTF *pTitle = CCLabelTTF::create(title,"Arial Bold",rectY*0.2,CCSize(rectX,rectY*0.7),CCTextAlignment::kCCTextAlignmentCenter);

		pTitle->setPosition(ccp(origin.x+(visibleSize.width)/2,origin.y+(visibleSize.height)/2));
	    //pTitle->setColor(ccc3(119,110,101));

		this->addChild(pTitle,2);
		this->setTouchEnabled(true);

		bRes = true;
	} while (0);

	return bRes;
}

void ModelDialog::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority*2,true);
}

bool ModelDialog::ccTouchBegan( CCTouch */*pTouch*/, CCEvent */*pEvent*/ )
{
	return true;
}

void ModelDialog::menuYes( CCObject* /*pSender*/ )
{
	this->removeFromParentAndCleanup(true);

	(m_caller->*m_func)();

}

void ModelDialog::menuNo( CCObject* /*pSender*/ )
{
	this->removeFromParentAndCleanup(true);
}

