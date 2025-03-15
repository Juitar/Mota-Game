#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

// 常量定义
#define MAP_WIDTH 13
#define MAP_HEIGHT 13
#define GRID_SIZE 30    // 每个格子的像素大小
#define FLOORS_COUNT 4  // Define the number of floors
#define MAP_OFFSET_X 127
#define MAP_OFFSET_Y 8   // 添加垂直偏移
#define BATTLE_MSG_LINES 4  // 显示消息的行数



// 游戏对象类型
enum ObjectType {
    EMPTY,//空地
    WALL,//墙
    PLAYER,//玩家
    MONSTER_SLIME,//史莱姆
    MONSTER_SKELETON,//骷髅
    MONSTER_WIZARD,//法师
    MONSTER_BEAST,//野兽
    MONSTER_KING,//魔王
    MONSTER_KING_FAKE,//魔王假身
    ITEM_SWORD,//剑
    ITEM_SHIELD,//盾
    ITEM_RED_POTION,//红药水
    ITEM_BLUE_POTION,//蓝药水
    ITEM_KEY_YELLOW,//黄钥匙
    ITEM_KEY_BLUE,//蓝钥匙
    ITEM_KEY_RED,//红钥匙
    DOOR_YELLOW,//黄门
    DOOR_BLUE,//蓝门
    DOOR_RED,//红门
    PORTAL_UP,//上层传送门
    PORTAL_DOWN,//下层传送门
    MERCHANT,//商人
    PRINCESS,//公主
};

enum BattleResult {
    BATTLE_CONTINUE,
    BATTLE_WIN,
    BATTLE_LOSE
};

// 玩家结构
typedef struct {
    int x, y;          // 位置
    int floor;         // 当前楼层
    int hp;           // 生命值
    int attack;        // 攻击力
    int defense;       // 防御力
    int gold;          // 金币
    int keys[3];      // 钥匙（黄蓝红）
    int exp;           // 经验值
    int level;         // 等级
    int expToLevelUp;  // 升级所需经验值
    int direction;     // 方向
} Player;


// 怪物结构体
typedef struct {
    int type;
    int hp;
    int attack;
    int defense;
    int exp;
    int gold;
    int x;  // 添加坐标
    int y;  // 添加坐标
} Monster;

// 怪物信息结构体
typedef struct {
    const char * name;
    const char * description;
    int type;
    int hp;
    int attack;
    int defense;
    int exp;
    int gold;
} MonsterInfo;

// 游戏状态结构体
typedef struct {
    Player player;
    int map[FLOORS_COUNT][MAP_HEIGHT][MAP_WIDTH];
    int MAPX[FLOORS_COUNT];
    int MAPY[FLOORS_COUNT];
    int lastPortal_X[FLOORS_COUNT];
    int lastPortal_Y[FLOORS_COUNT];
    int currentFloor;
    int isGameOver;
    char battleMsg[BATTLE_MSG_LINES][256];
    int msgCount;
    int inBattle;         // 新增：是否在战斗中
    int isShopping;       // 新增：是否在商店中
    int isViewingBestiary; // 新增：是否在查看怪物图鉴
    int bestiarySelection; // 新增：怪物图鉴索引
    Monster currentMonster; // 新增：当前战斗的怪物
} GameState;



// 函数声明
// 初始化相关
void initGame(GameState* state);
void initPlayer(Player* player, GameState* state);
void loadResources();

// 游戏逻辑相关
void handleInput(GameState* state);
void updateGame(GameState* state);
int canMove(GameState* state, int newX, int newY);
void battle(Player* player, Monster* monster);
void useItem(Player* player, int itemType);
void openShop(Player* player);
void addBattleMessage(GameState* state, const char* message);
BattleResult battleTurn(GameState* state, Monster* monster);
Monster getMonsterStats(int monsterType);
const char* getMonsterName(int monsterType);


// 渲染相关
void gameRender(GameState* state, void* userData);
void initGraphics();
void render(GameState* state);
void drawMap(GameState* state);
void drawPlayer(Player* player);
void drawUI(GameState* state);
void drawBattleScene(Player* player, Monster* monster);
void drawGame(GameState* state);
void drawBestiary(GameState* state); 

// 存档相关
void saveGame(GameState* state);
void loadGame(GameState* state);
// 在原有声明的基础上添加：
void handleBattle(GameState* state, void* userData);
void handleShop(GameState* state, void* userData);

extern const MonsterInfo MONSTER_INFO[];
extern const int MONSTER_COUNT;
#endif // GAME_H