#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Board::createScene()
{
    return Board::create();
}

bool Board::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    initTiles();
    initPlayer();
    initClickListener();
    startDice();
    
    return true;
}

void Board::initTiles()
{
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    float yPosition = screenSize.height/3;
    
    //First tile
    auto stoneTile = Sprite::create("stone.png");
    stoneTile->setScale(0.85, 0.5);
    
    stoneTile->setPosition(Vec2(stoneTile->getContentSize().width / 2, yPosition));
    
    addChild(stoneTile);
    
    
    firstTileSize = stoneTile->getContentSize();
    firstTilePosition = stoneTile->getPosition();
    int counter=0;
    
    //6 tiles
    for(int i = 1; i < 7; i++)
    {
        if(sceneNames[i-1] == "Drow" || sceneNames[i-1] == "Stacking"){
        counter++;
        Sprite* tile = Sprite::create("grass.png");
        
        tile->setScale(0.85, 0.5);
        
        float xPosition = screenSize.width / 3 * counter + firstTileSize.width / 2;
        tile->setPosition(Vec2(xPosition, yPosition));
        
        addChild(tile);
        
        //SceneLabel
        auto label = Label::create();
        label->setScale(1.f/0.85, 2.f);
        label->setPosition(Vec2(tile->getContentSize().width/2, 0));
        
        tile->addChild(label);
        label->setString(sceneNames[i-1]);
        }
    }
}

void Board::initPlayer()
{
    playerSprite = Sprite::create("p_stand.png");
    playerSprite->setScale(0.5);
    
    float xPosition = firstTilePosition.x;
    float yPosition = firstTilePosition.y + playerSprite->getContentSize().height/2 - 6;
    
    playerSprite->setPosition(Vec2(xPosition, yPosition));
    
    addChild(playerSprite);
}

void Board::initClickListener()
{
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        stopDiceAndMove();
        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Board::stopDiceAndMove()
{
    if(sceneNames[actualNumber-1]=="Drow" || sceneNames[actualNumber-1]=="Stacking"){
    stopDice();
    int counter=0;
    if(sceneNames[actualNumber-1]=="Drow"){
        counter=1;
    }else{
        counter=2;
    }
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    Vec2 finalPosition = Vec2(screenSize.width / 3 * counter + firstTileSize.width / 2, playerSprite->getPosition().y);
    
    auto jumps = JumpTo::create(counter * 0.6, finalPosition, 60, counter);
    
    playerSprite->runAction(jumps);

    schedule([=](float dt){
        if(sceneNames[actualNumber-1]=="Drow"){
            Director::getInstance()->pushScene(Drow::createScene());
        }else{
            Director::getInstance()->pushScene(Stacking::createScene());
        }
}, counter, 1, 0, "changeScene");
        
    }
}

void Board::startDice()
{
    Size screenSize = Director::getInstance()->getVisibleSize();
    auto diceLabel = Label::create();
    
    diceLabel->setPosition(Vec2(screenSize/3.f * 2.f));
    diceLabel->setSystemFontSize(40);
    
    addChild(diceLabel);
    
    auto diceSprite = Sprite::create("dice1.png");
    diceSprite->setPosition(Vec2(screenSize/3.f * 2.f));
    addChild(diceSprite);
    
    schedule([=](float dt){

        actualNumber %= sceneConstructors.size();
        actualNumber++;
        
        string text = "";
        text.push_back(actualNumber+'0');
        diceLabel->setString(text);
        if(actualNumber==1){
        diceSprite->setTexture("dice1.png");
        }else if(actualNumber==2){
            diceSprite->setTexture("dice2.png");
    }else if(actualNumber==3){
        diceSprite->setTexture("dice3.png");
}else if(actualNumber==4){
    diceSprite->setTexture("dice4.png");
}else if(actualNumber==5){
    diceSprite->setTexture("dice5.png");
}else if(actualNumber==6){
    diceSprite->setTexture("dice6.png");
}
        
    }, 0.1f, -1, 0, "changeDiceNumber");
    
}

void Board::stopDice()
{
    unschedule("changeDiceNumber");
}

