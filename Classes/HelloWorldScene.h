#ifndef __Board_SCENE_H__
#define __Board_SCENE_H__

#include "cocos2d.h"

#include "JumpingHippo.h"
#include "Chips.h"
#include "Drow.h"
#include "Gluttony.h"
#include "Stacking.h"
#include "Counting.h"

#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;
using namespace ui;
using namespace std;

typedef Scene* (*SceneConstructors) ();

class Board : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void initTiles();
    void initPlayer();
    void initClickListener();
    void startDice();
    void stopDice();
    
    int actualNumber = 1;
    
    Sprite* playerSprite;

    vector<string> sceneConstructors =
            {
                    "Jumping Hippo",
                    "Chips",
                    "Drow",
                    "Gluttony",
                    "Stacking",
                    "Counting"
            };
    vector<string> sceneNames =
    {
        "Jumping Hippo",
        "Chips",
        "Drow",
        "Gluttony",
        "Stacking",
        "Counting"
    };
    
    void stopDiceAndMove();
    
    Vec2 firstTilePosition;
    Size firstTileSize;
    
    CREATE_FUNC(Board);
};

#endif // Chips
