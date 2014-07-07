#include "LayerBack.h"
#include "AppMacros.h"
#include "NumberCell.h"
USING_NS_CC;

#define TAG_SCORE 200
#define TAG_BEST 201

int getRand(int a, int b)
{
	srand((unsigned int) time(NULL));

	return rand() % (b - a + 1) + a;
}


//ʵ�ֲ���


LayerBack::LayerBack()
{
	for (int i = 0; i < 16; i++)
		max[i] = 0;

	m_score = 0;
	m_best = CCUserDefault::sharedUserDefault()->getIntegerForKey("BestScore",0);
}


LayerBack::~LayerBack()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("BestScore", m_best);
}

LayerBack* LayerBack::create()
{
	LayerBack *pRet = new LayerBack();
	if (pRet && pRet->init())
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

void LayerBack::draw()
{
	CCLayerColor::draw();
	//CCSize size = this->getContentSize();
	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//
	//CCPoint orgin = ccp(30,visibleSize.height);
	//CCPoint dest = ccp(80, visibleSize.height - 50);



	//
	//ccDrawSolidRect(orgin,dest,ccc4f(0.92549,0.76863,0,1));

	//ccDrawColor4B(229, 190, 0, 255);
	//ccDrawRect(orgin, dest);
	
}

bool LayerBack::init()
{

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(250, 248, 239,255)));

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(LayerBack::menuCloseCallback));
		CC_BREAK_IF(!pCloseItem);

		// Place the menu item bottom-right conner.
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
			origin.y + pCloseItem->getContentSize().height / 2));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 5);



		int boardWidth = visibleSize.width - 32;
		int space = 8;
		cellWidth = (boardWidth - space * 5) / 4.0;
	
		ColorRect *title = ColorRect::create(ccc4(236, 196, 0, 255), cellWidth, cellWidth);
		title->setPosition(origin.x + 16, origin.y + visibleSize.height - cellWidth - 16);
		this->addChild(title, 2);	


		CCLabelTTF* pL2048 = CCLabelTTF::create("2048", "Arial Bold", cellWidth/3);

		// position the label on the center of the screen
		pL2048->setPosition(ccp(title->getPositionX()+cellWidth/2,title->getPositionY()+cellWidth/2));

		// add the label as a child to this layer
		this->addChild(pL2048, 3);


		int bestWidth = cellWidth*1.5;
		int bestHeight = cellWidth;
		ColorRect *best = ColorRect::create(ccc4(187, 173, 160, 255), bestWidth, bestHeight);
		best->setPosition(origin.x+visibleSize.width - 16 - bestWidth,origin.y+visibleSize.height-16 - bestHeight);
		this->addChild(best);
		

		CCLabelTTF* pLBest = CCLabelTTF::create("BEST", "Arial Bold", cellWidth / 6);
		pLBest->setPosition(ccp(best->getPositionX() + bestWidth / 2, best->getPositionY() + bestHeight *0.8));
		this->addChild(pLBest,3);

		ColorRect *score = ColorRect::create(ccc4(187, 173, 160, 255), bestWidth, bestHeight);
		score->setPosition(origin.x + visibleSize.width - 16-8 - bestWidth*2, origin.y + visibleSize.height - 16 - bestHeight);
		this->addChild(score);
	
		CCLabelTTF* pLScore = CCLabelTTF::create("SCORE", "Arial Bold", cellWidth / 6);
		pLScore->setPosition(ccp(score->getPositionX() + bestWidth / 2, score->getPositionY() + bestHeight *0.8));
		this->addChild(pLScore, 3);

		CCLabelTTF* pLScoreV = CCLabelTTF::create("0", "Arial Bold", cellWidth / 3);
		pLScoreV->setPosition(ccp(score->getPositionX() + bestWidth / 2, score->getPositionY() + bestHeight *0.4));
		this->addChild(pLScoreV, 3,TAG_SCORE);

		CCString sbest;
		sbest.initWithFormat("%d",m_best);

		CCLabelTTF* pLBestV = CCLabelTTF::create(sbest.getCString(), "Arial Bold", cellWidth / 3);
		pLBestV->setPosition(ccp(best->getPositionX() + bestWidth / 2, best->getPositionY() + bestHeight *0.4));
		this->addChild(pLBestV, 3,TAG_BEST);

		int temp = (visibleSize.height - 16  - cellWidth - boardWidth)/2;

		CCLayerColor *pan = CCLayerColor::create(ccc4(187, 173, 160, 255), boardWidth, boardWidth);
		pan->setPosition(origin.x+16,origin.y+temp);

		this->addChild(pan, 2);


		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				CCLayerColor *fang = CCLayerColor::create(ccc4(204, 192, 180, 255), cellWidth, cellWidth);
				position[i][j] = ccp(origin.x + 16 + j*(cellWidth + space) + space, origin.y + temp + i*(cellWidth + space) + space);
				fang->setPosition(position[i][j]);
				this->addChild(fang, 3);
			}

		}

		this->setTouchEnabled(true);

		initBoard();
		bRet = true;
	} while (0);
	
	return bRet;
}

void LayerBack::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#endif
}


void LayerBack::ccTouchMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->getLocation();
	
}


void LayerBack::registerWithTouchDispatcher()
{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}
int ab12[6] = { 1, 1, 1, 1, 1, 2 };
void LayerBack::ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent)
{

	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint posEnd = touch->getLocation();
	CCPoint direct = posEnd - posBegin;

	if (direct.getLength() < 0.1)
		return;

	int merge[16] = {0};
	int score = m_score;
	float angle = direct.getAngle()* 180/3.1415926;
	
	bool cMove = false;
	const static float moveDuration = 0.1f;
	const static float scaleDurationA = 0.1f;
	const static float scaleDurationB = 0.1f;
	const static float scaleZoom = 1.3f;

	int direction = 0;

	if (angle <= 45 && angle > -45) direction = 1;	 //right
	if (angle > 45 && angle <= 135)	direction = 3;	 //up
	if (angle > 135 || angle <= -135) direction = 2; //left
	if (angle <= -45 && angle > -135) direction = 4; //down

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x1,y1,x2,y2,x3,y3;
			int title1,title2;
			int index;
			switch (direction)
			{
			case 1:				//right
				{
					x1 = i;y1 = 3 - j;
					if (y1 == 3) continue;
					title1 = max[x1 * 4 + y1];
					index = 3;

					for (int k = y1 + 1; k < 4; k++)
					{
						if (max[x1 * 4 + k] > 0)
						{
							index = k;
							break;
						}
					}
					x2 = x1; y2 = index;
					x3 = x1; y3 = index - 1;
				}
				break;
			case 3:				//up
				{
					x1 = 3 - i; y1 = j;
					if (x1 == 3) continue;
					title1 = max[x1 * 4 + y1];

					index = 3;
					for (int k = x1 + 1; k < 4; k++)
					{
						if (max[k * 4 + y1] > 0)
						{
							index = k;
							break;
						}
					}
					x2 = index; y2 = y1;
					x3 = index - 1; y3 = y1;
				}
				break;
			case 2:				//left
				{
					x1 = i; y1 = j;
					if (y1 == 0) continue;
					title1 = max[x1 * 4 + y1];

					index = 0;
					for (int k = y1 - 1; k > 0; k--)
					{
						if (max[x1 * 4 + k] > 0)
						{
							index = k;
							break;
						}
					}

					x2 = x1; y2 = index;
					x3 = x1; y3 = index+1;
				}
				break;
			case 4:				//down
				{
					x1 = i; y1 = j;
					if ( x1 == 0) continue;
					title1 = max[x1 * 4 + y1];

					index = 0;
					for (int k = x1 - 1; k > 0; k--)
					{
						if (max[k * 4 + y1] > 0)
						{
							index = k;
							break;
						}
					}
					x2 = index; y2 = y1;
					x3 = index + 1; y3 = y1;
				}
				break;
			}

			if (title1 == 0) continue;
			
			title2 = max[x2 * 4 + y2];
			if (title1 == title2)
			{
				CCNode *node1 = this->getChildByTag(x1 * 4 + y1);
				CCNode *node2 = this->getChildByTag(x2 * 4 + y2);

				if (merge[x2 * 4 + y2] == 1)
				{
					node1->runAction(CCMoveTo::create(moveDuration,position[x3][y3]));
					node1->setTag(x3 * 4 + y3);
					max[x1 * 4 + y1] = 0;
					max[x3 * 4 + y3] = title1;
				} 
				else
				{
					node1->setTag(x2 * 4 + y2);
					((NumberCell*)node1)->SetTitle(title2+1);

					this->removeChild(node2);
					CCMoveTo *actionM = CCMoveTo::create(moveDuration,position[x2][y2]);
					CCScaleTo *actionA = CCScaleTo::create(scaleDurationA,scaleZoom);
					CCScaleTo *actionB = CCScaleTo::create(scaleDurationB,1);
					node1->runAction(CCSequence::create(actionM,actionA,actionB,NULL));

					max[x1 * 4 + y1] = 0;
					max[x2 * 4 + y2] = title2 + 1;
					merge[x2 * 4 + y2] = 1;
					score += (1 << (title2 + 1));
				}

				cMove = true;
			}
			else if (title2 > 0)
			{
				if (x3 != x1 || y3 != y1)
				{
					CCNode *node1 = this->getChildByTag(x1 * 4 + y1);
					node1->runAction(CCMoveTo::create(moveDuration,position[x3][y3]));
					node1->setTag(x3 * 4 + y3);
					max[x1 * 4 + y1] = 0;
					max[x3 * 4 + y3] = title1;
					cMove = true;
				}
			}
			else if (title2 == 0)
			{
				CCNode *node = this->getChildByTag(x1 * 4 + y1);
				node->runAction(CCMoveTo::create(moveDuration,position[x2][y2]));
				node->setTag(x2 * 4 + y2);
				max[x1 * 4 + y1] = 0;
				max[x2 * 4 + y2] = title1;
				cMove = true;
			}
			
		}


	}

	int count = 0;
	for (int i = 0; i < 16; i++)
	{
		if (max[i] == 0)
		{
			count++;
		}
	}
	if (cMove)
	{
		if (count == 0)
		{
			//Game over
		}
		int index = getRand(0, count - 1);
		for (int i = 0; i < 16; i++)
		{
			if (max[i] > 0)
			{
				if (index >= i)
					index++;
			}
		}

		max[index] = ab12[getRand(0, 5)];

		NumberCell *cell = NumberCell::create(CCSize(cellWidth, cellWidth), max[index]);
		cell->setPosition(position[index / 4][index % 4]);
		this->addChild(cell, 4, index);

		CCScaleTo *actionA = CCScaleTo::create(0.05,0.5);
		CCScaleTo *actionB = CCScaleTo::create(0.3,1);
		cell->runAction(CCSequence::create(actionA,actionB,NULL));

	}

	if (m_score != score)
	{
		CCLabelTTF *pLScore = (CCLabelTTF*)this->getChildByTag(TAG_SCORE);
		CCString cs;
		cs.initWithFormat("%d", score);
		pLScore->setString(cs.getCString());
		m_score = score;

		if (m_best < m_score)
		{
			m_best = m_score;
			CCLabelTTF *pLBest = (CCLabelTTF*)this->getChildByTag(TAG_BEST);
			CCString cs;
			cs.initWithFormat("%d", m_best);
			pLBest->setString(cs.getCString());
		}

	}

}

void LayerBack::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	posBegin = touch->getLocation();
}

void LayerBack::updateBoard()
{

}




void LayerBack::initBoard()
{
	for (int i = 0; i < 16; i++)
	{
		if (max[i] > 0)
		{
			CCNode *node = this->getChildByTag(i);
			if (node)
			{
				this->removeChildByTag(i);
			//	node->release();

			}
			max[i] = 0;
		}
	}

	int in1 = getRand(0, 15);

	max[in1] = ab12[getRand(0, 5)];

	NumberCell *cell1 = new NumberCell(CCSize(cellWidth, cellWidth), max[in1]);
	cell1->init();
	cell1->setPosition(position[in1/4][in1%4]);
	this->addChild(cell1, 4, in1);

	int in2 = getRand(0, 14);

	if (in2 >= in1)
	{
		in2++;
	}


	max[in2] = ab12[getRand(0, 5)];

	NumberCell *cell2 = new NumberCell(CCSize(cellWidth, cellWidth), max[in2]);
	cell2->init();
	cell2->setPosition(position[in2 / 4][in2 % 4]);
	this->addChild(cell2, 4, in2);
}