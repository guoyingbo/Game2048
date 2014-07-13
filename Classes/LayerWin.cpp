#include "LayerWin.h"
#include "Config.h"
#include "NumberCell.h"
USING_NS_CC;

LayerWin::LayerWin(void)
{
}


LayerWin::~LayerWin(void)
{
}

bool LayerWin::init()
{
    bool bRet = false;

    do
    {

        int curTitle = Global::shareGlobal()->curTitle;

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


        CC_BREAK_IF(!initWithColor(ccc4(250, 248, 239,255)));

        CCLabelTTF* label = CCLabelTTF::create(curTitle == 11 ? "YOU WIN!" : "GREAT!","Arial Bold",32,
            CCSize(visibleSize.width,visibleSize.height*0.7),kCCTextAlignmentCenter);

        CC_BREAK_IF(!label);

        label->setColor(ccc3(119,110,101));
        label->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

        this->addChild(label);

        float rectX = visibleSize.width*0.75;
        float rectY = rectX*0.45;
        ColorRect* pRect = ColorRect::create(ccc4(236, 196, 0, 255),rectX,rectY);

        pRect->setPosition(origin.x + (visibleSize.width-rectX)/2,origin.y+(visibleSize.height)/2);

        this->addChild(pRect);


        CCString *ssv = CCString::createWithFormat("%d",1 << curTitle);
        CCLabelTTF* scoreValue = CCLabelTTF::create(ssv->getCString(),"Arial Bold",32,CCSize(rectX,rectY),
            kCCTextAlignmentCenter);

        this->addChild(scoreValue);
        scoreValue->setPosition(ccp(pRect->getPositionX()+rectX*0.5,pRect->getPositionY()+rectY*0.3));

        CCString *sst = CCString::createWithFormat("SCORE:%d",Global::shareGlobal()->curScore);
        CCLabelTTF* score = CCLabelTTF::create(sst->getCString(),"Arial Bold",8,CCSize(rectX,rectY*0.5),
            kCCTextAlignmentCenter);
        this->addChild(score);
        score->setPosition(ccp(pRect->getPositionX()+rectX*0.5,pRect->getPositionY()));

        
        float menuX = rectX*0.45;
        float menuY = menuX*0.3;


        TitleRect *titleBack = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,"Back");
        CCMenuItemLabel *MenuBack = CCMenuItemLabel::create(titleBack,this,menu_selector(LayerWin::menuBack));

        TitleRect *titleAgain = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,"Try again");
        CCMenuItemLabel *MenuAgain = CCMenuItemLabel::create(titleAgain,this,menu_selector(LayerWin::menuAgain));

        CCMenu *menu = CCMenu::create(MenuBack,MenuAgain,NULL);

        menu->alignItemsHorizontallyWithPadding(rectX*0.1);

        menu->setPositionY(origin.y+visibleSize.height*0.2);

        this->addChild(menu);


        bRet = true;
    }while(0);

    return bRet;
}

cocos2d::CCScene* LayerWin::scene()
{
    CCScene* scene = CCScene::create();

    LayerWin* layer = LayerWin::create();

    scene->addChild(layer);

    return scene;
}

void LayerWin::menuAgain( cocos2d::CCObject *pSender )
{
    CCDirector::sharedDirector()->popScene();
    CCObject* caller = Global::shareGlobal()->caller;
    SEL_CallFunc func = Global::shareGlobal()->func;
    (caller->*func)();
}

void LayerWin::menuBack( cocos2d::CCObject *pSender )
{
    CCDirector::sharedDirector()->popScene();
}
