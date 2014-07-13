/*
* LayerGameOver.cpp
*
*  Created on: 2014年7月11日
*      Author: rhino
*/

#include "LayerGameOver.h"
#include "NumberCell.h"
#include "Config.h"

LayerGameOver::LayerGameOver() {
    // TODO Auto-generated constructor stub

}

LayerGameOver::~LayerGameOver() {
    // TODO Auto-generated destructor stub
}

bool LayerGameOver::init()
{
    bool bRet = false;

    do
    {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


        CC_BREAK_IF(!initWithColor(ccc4(250, 248, 239,255)));

        CCLabelTTF* label = CCLabelTTF::create("Game Over!","Arial Bold",32,
            CCSize(visibleSize.width,visibleSize.height*0.7),kCCTextAlignmentCenter);

        CC_BREAK_IF(!label);

        label->setColor(ccc3(119,110,101));
        label->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

        this->addChild(label);

        float rectX = visibleSize.width*0.75;
        float rectY = rectX*0.45;
        ColorRect* pRect = ColorRect::create(ccc4(187, 173, 160, 255),rectX,rectY);

        pRect->setPosition(origin.x + (visibleSize.width-rectX)/2,origin.y+(visibleSize.height)/2);

        this->addChild(pRect);


        CCString *ssv = CCString::createWithFormat("%d",Global::shareGlobal()->curScore);
        CCLabelTTF* scoreValue = CCLabelTTF::create(ssv->getCString(),"Arial Bold",25,CCSize(rectX*0.5,rectY*0.5),
            kCCTextAlignmentCenter);

        this->addChild(scoreValue);
        scoreValue->setPosition(ccp(pRect->getPositionX()+rectX*0.25,pRect->getPositionY()+rectY*0.35));


        CCLabelTTF* score = CCLabelTTF::create("SCORE","Arial Bold",10,CCSize(rectX*0.5,rectY*0.5),
            kCCTextAlignmentCenter);
        this->addChild(score);
        score->setPosition(ccp(pRect->getPositionX()+rectX*0.25,pRect->getPositionY()+rectY*0.6));

        CCString *stv = CCString::createWithFormat("%d",1<<Global::shareGlobal()->curTitle);
        CCLabelTTF* titleValue = CCLabelTTF::create(stv->getCString(),"Arial Bold",25,CCSize(rectX*0.5,rectY*0.5),
            kCCTextAlignmentCenter);
        this->addChild(titleValue);
        titleValue->setPosition(ccp(pRect->getPositionX()+rectX*0.75,pRect->getPositionY()+rectY*0.35));


        CCLabelTTF* title = CCLabelTTF::create("TITLE","Arial Bold",10,CCSize(rectX*0.5,rectY*0.5),
            kCCTextAlignmentCenter);
        this->addChild(title);
        title->setPosition(ccp(pRect->getPositionX()+rectX*0.75,pRect->getPositionY()+rectY*0.6));



        float menuX = rectX*0.45;
        float menuY = menuX*0.3;


        TitleRect *titleBack = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,"Back");
        CCMenuItemLabel *MenuBack = CCMenuItemLabel::create(titleBack,this,menu_selector(LayerGameOver::menuBack));

        TitleRect *titleAgain = TitleRect::create(ccc4(187, 173, 160, 255),menuX,menuY,"Try again");
        CCMenuItemLabel *MenuAgain = CCMenuItemLabel::create(titleAgain,this,menu_selector(LayerGameOver::menuAgain));

        CCMenu *menu = CCMenu::create(MenuBack,MenuAgain,NULL);

        menu->alignItemsHorizontallyWithPadding(rectX*0.1);

        menu->setPositionY(origin.y+visibleSize.height*0.2);

        this->addChild(menu);


        bRet = true;
    }while(0);

    return bRet;
}

CCScene* LayerGameOver::scene()
{
    CCScene* scene = CCScene::create();

    LayerGameOver* layer = LayerGameOver::create();

    scene->addChild(layer);

    return scene;

}


void LayerGameOver::menuAgain(CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
    CCObject* caller = Global::shareGlobal()->caller;
    SEL_CallFunc func = Global::shareGlobal()->func;
    (caller->*func)();
}
void LayerGameOver::menuBack(CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
}
