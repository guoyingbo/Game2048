#include "LayerBack.h"
#include "AppMacros.h"
#include "NumberCell.h"
USING_NS_CC;

#define TAG_SCORE 200
#define TAG_SCORE 201

int getRand(int a, int b)
{
	srand((unsigned int) time(NULL));

	return rand() % (b - a + 1) + a;
}


//实现部分
typedef struct
{
	float x;
	float y;

} Vector2f;


LayerBack::LayerBack()
{
	for (int i = 0; i < 16; i++)
		max[i] = 0;

	m_score = 0;
}


LayerBack::~LayerBack()
{
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


		int bestWidth = cellWidth*1.2;
		int bestHeight = cellWidth*0.8;
		ColorRect *best = ColorRect::create(ccc4(187, 173, 160, 255), bestWidth, bestHeight);
		best->setPosition(origin.x+visibleSize.width - 16 - bestWidth,origin.y+visibleSize.height-16 - bestHeight);
		this->addChild(best);
		

		CCLabelTTF* pLBest = CCLabelTTF::create("BEST", "Arial Bold", cellWidth / 6);
		pLBest->setPosition(ccp(best->getPositionX() + bestWidth / 2, best->getPositionY() + bestHeight *0.8));
		this->addChild(pLBest,3);

		CCLayerColor *score = CCLayerColor::create(ccc4(187, 173, 160, 255), bestWidth, bestHeight);
		score->setPosition(origin.x + visibleSize.width - 16-8 - bestWidth*2, origin.y + visibleSize.height - 16 - bestHeight);
		this->addChild(score);
	
		CCLabelTTF* pLScore = CCLabelTTF::create("SCORE", "Arial Bold", cellWidth / 6);
		pLScore->setPosition(ccp(score->getPositionX() + bestWidth / 2, score->getPositionY() + bestHeight *0.8));
		this->addChild(pLScore, 3);

		CCLabelTTF* pLScoreV = CCLabelTTF::create("0", "Arial Bold", cellWidth / 3);
		pLScoreV->setPosition(ccp(score->getPositionX() + bestWidth / 2, score->getPositionY() + bestHeight *0.4));
		this->addChild(pLScoreV, 3,TAG_SCORE);

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

	const float timem = 0.1f;
	const float times1 = 0.1f;
	const float times2 = 0.2f;

	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint posEnd = touch->getLocation();

	CCPoint direct = posEnd - posBegin;

	if (direct.getLength() < 0.1)
		return;

	int score = m_score;
	float angle = direct.getAngle()* 180/3.1415926;

	bool cMove = false;
	int vector;
	if (angle <= 45 && angle > -45)  //right
	{
		for (int j = 2; j >= 0; j--)
		for (int i = 0; i < 4; i++)
		{
			int title1 = max[i * 4 + j];
			
			if (title1>0)
			{
				int index = 3;
				for (int k = j + 1; k < 4; k++)
				{
					if (max[i * 4 + k] > 0)
					{
						index = k;
						break;
					}
						
				}

				int title2 = max[i * 4 + index];
				if (title1 == title2)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
					CCNode *node2 = this->getChildByTag(i * 4 + index);

					this->removeChild(node2);
					

					node1->setTag(i*4+index);
					((NumberCell*)node1)->SetTitle(title2+1);
					
					CCActionInterval*  actionMove = CCMoveTo::create(timem,position[i][index]);
					CCActionInterval*  actionTo = CCScaleTo::create(times1, 1.3);
					CCActionInterval*  actionBy = CCScaleTo::create(times2, 1);

					node1->runAction(CCSequence::create(actionMove,actionTo, actionBy, NULL));

					max[i * 4 + j] = 0;
					max[i * 4 + index] = title2 +1;
					cMove = true;
					
					score += pow((float)2, title2 + 1);
				}
				else if(title2 > 0)
				{
					if (index - 1 != j)
					{
						CCNode *node1 = this->getChildByTag(i * 4 + j);
					//	node1->setPosition(position[i][index - 1]);
						node1->runAction(CCMoveTo::create(timem,position[i][index-1]));
						node1->setTag(i * 4 + index - 1);
						max[i * 4 + j] = 0;
						max[i * 4 + index - 1] = title1;
						cMove = true;
					}

				}
				else
				if (title2 == 0)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
				//	node1->setPosition(position[i][index]);
					node1->runAction(CCMoveTo::create(timem,position[i][index]));
					node1->setTag(i * 4 + index);
					max[i * 4 + j] = 0;
					max[i * 4 + index] = title1;
					cMove = true;
				}
				
			}
		}

	}
	if (angle > 45 && angle <= 135)  //up
	{
		for (int i = 2; i >= 0; i--)
		for (int j = 0; j < 4; j++)
		{
			int title1 = max[i * 4 + j];

			if (title1>0)
			{
				int index = 3;
				for (int k = i + 1; k < 4; k++)
				{
					if (max[k * 4 + j] > 0)
					{
						index = k;
						break;
					}
						
				}

				int title2 = max[index * 4 + j];
				if (title1 == title2)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
					CCNode *node2 = this->getChildByTag(index * 4 + j);

					this->removeChild(node2);
					

					node1->setTag(index*4+j);
					((NumberCell*)node1)->SetTitle(title2+1);

					CCActionInterval*  actionMove = CCMoveTo::create(timem,position[index][j]);
					CCActionInterval*  actionTo = CCScaleTo::create(times1, 1.3);
					CCActionInterval*  actionBy = CCScaleTo::create(times2, 1);

					node1->runAction(CCSequence::create(actionMove,actionTo, actionBy, NULL));

					max[i * 4 + j] = 0;
					max[index * 4 + j] = title2 +1;
					cMove = true;
					score += pow((float)2, title2 + 1);
				}
				else if (title2 > 0)
				{
					if (index - 1 != i)
					{
						CCNode *node1 = this->getChildByTag(i * 4 + j);
					//	node1->setPosition(position[index - 1][j]);
						node1->runAction(CCMoveTo::create(timem,position[index-1][j]));
						node1->setTag((index - 1) * 4 + j);
						max[i * 4 + j] = 0;
						max[(index - 1) * 4 + j] = title1;
						cMove = true;

					}

				}
				else
				if (title2 == 0)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
				//	node1->setPosition(position[index][j]);
					node1->runAction(CCMoveTo::create(timem,position[index][j]));
					node1->setTag(index * 4 + j);
					max[i * 4 + j] = 0;
					max[index * 4 + j] = title1;
					cMove = true;
				}

			}
		}
	}
	if (angle > 135 || angle <= -135) //left
	{
		for (int j = 1; j < 4; j++)
		for (int i = 0; i < 4; i++)
		{
			int title1 = max[i * 4 + j];

			if (title1>0)
			{
				int index = 0;
				for (int k = j -1; k > 0; k--)
				{
					if (max[i * 4 + k] > 0)
					{
						index = k;
						break;
					}
				}

				int title2 = max[i * 4 + index];
				if (title1 == title2)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
					CCNode *node2 = this->getChildByTag(i * 4 + index);

					this->removeChild(node2);
					

					node1->setTag(i*4+index);
					((NumberCell*)node1)->SetTitle(title2+1);

					CCActionInterval*  actionMove = CCMoveTo::create(timem,position[i][index]);
					CCActionInterval*  actionTo = CCScaleTo::create(times1, 1.3);
					CCActionInterval*  actionBy = CCScaleTo::create(times2, 1);

					node1->runAction(CCSequence::create(actionMove,actionTo, actionBy, NULL));

					max[i * 4 + j] = 0;
					max[i * 4 + index] = title2+1;
					cMove = true;;
					score += pow((float)2, title2 + 1);
				}
				else if (title2 > 0)
				{
					if (index + 1 != j)
					{
						CCNode *node1 = this->getChildByTag(i * 4 + j);
					//	node1->setPosition(position[i][index + 1]);
						node1->runAction(CCMoveTo::create(timem,position[i][index+1]));
						node1->setTag(i * 4 + index + 1);
						max[i * 4 + j] = 0;
						max[i * 4 + index + 1] = title1;
						cMove = true;
					}

				}
				else
				if (title2 == 0)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
				//	node1->setPosition(position[i][index]);
					node1->runAction(CCMoveTo::create(timem,position[i][index]));
					node1->setTag(i * 4 + index);
					max[i * 4 + j] = 0;
					max[i * 4 + index] = title1;
					cMove = true;
				}

			}
		}
	}
	if (angle <= -45 && angle > -135) //down;
	{
		for (int i = 1; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			int title1 = max[i * 4 + j];

			if (title1>0)
			{
				int index = 0;
				for (int k = i - 1; k > 0; k--)
				{
					if (max[k * 4 + j] > 0)
					{
						index = k;
						break;
					}
						
				}

				int title2 = max[index * 4 + j];
				if (title1 == title2)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
					CCNode *node2 = this->getChildByTag(index * 4 + j);

					this->removeChild(node2);
					

					node1->setTag(index*4+j);
					((NumberCell*)node1)->SetTitle(title2+1);

					CCActionInterval*  actionMove = CCMoveTo::create(timem,position[index][j]);
					CCActionInterval*  actionTo = CCScaleTo::create(times1, 1.3);
					CCActionInterval*  actionBy = CCScaleTo::create(times2, 1);

					node1->runAction(CCSequence::create(actionMove,actionTo, actionBy, NULL));

					max[i * 4 + j] = 0;
					max[index * 4 + j] = title2 +1;
					cMove = true;
					score += pow((float)2, title2 + 1);

				}
				else if (title2 > 0)
				{
					if (index + 1 != i)
					{
						CCNode *node1 = this->getChildByTag(i * 4 + j);
					//	node1->setPosition(position[index + 1][j]);
						node1->runAction(CCMoveTo::create(timem,position[index+1][j]));
						node1->setTag((index + 1) * 4 + j);
						max[i * 4 + j] = 0;
						max[(index + 1) * 4 + j] = title1;
						cMove = true;
					}

				}
				else
				if (title2 == 0)
				{
					CCNode *node1 = this->getChildByTag(i * 4 + j);
				//	node1->setPosition(position[index][j]);
					node1->runAction(CCMoveTo::create(timem,position[index][j]));
					node1->setTag(index * 4 + j);
					max[i * 4 + j] = 0;
					max[index * 4 + j] = title1;
					cMove = true;
				}

			}
		}
	}

	if (cMove)
	{
		int count = 0;
		for (int i = 0; i < 16; i++)
		{
			if (max[i] == 0)
				count++;
		}

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

		NumberCell *cell1 = NumberCell::create(CCSize(cellWidth, cellWidth), max[index]);
		cell1->setPosition(position[index / 4][index % 4]);
		this->addChild(cell1, 4, index);
	}

	if (m_score != score)
	{
		CCLabelTTF *pLScore = (CCLabelTTF*)this->getChildByTag(TAG_SCORE);
		CCString cs;
		cs.initWithFormat("%d", score);
		pLScore->setString(cs.getCString());
		m_score = score;
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