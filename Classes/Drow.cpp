#include "Drow.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Drow::createScene()
{
    return Drow::create();
}

bool Drow::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    initComponents();
    initAnimation();
    initClickListener();
    
    return true;
}

void Drow::initComponents()
{
    auto screenSize = Director::getInstance()->getVisibleSize();
    
    barSprite = Sprite::create("flecha.png");
    circleSprite = Sprite::create("circle.png");
    
    circleSprite->setScale(0.65);
    barSprite->setScale(0.65);
    
    barSprite->setPosition(Vec2(screenSize.width/2, screenSize.height));
    circleSprite->setPosition(screenSize/2);
    
    addChild(circleSprite);
    addChild(barSprite);
}

void Drow::initAnimation()
{
    barSprite->setRotation(-45);
    
    auto rightAnim = RotateBy::create(1, 90);
    auto leftAnim = RotateBy::create(1, -90);
    
    auto rightEase = EaseSineInOut::create(rightAnim);
    auto leftEase = EaseSineInOut::create(leftAnim);
    
    auto sequence = Sequence::create(rightEase, leftEase, NULL);
    auto repeatSequence = Repeat::create(sequence, 5);
    
    barSprite->runAction(repeatSequence);
}


void Drow::initClickListener()
{
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        
        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool Drow::isTouchingTheCircle()
{
    bool flag = false;
    //if(barSprite.getPosition==circleSprite.getPosition){
      //  flag=true;
    //}
    return flag;
}

void Drow::addPunctuation()
{
    
}
