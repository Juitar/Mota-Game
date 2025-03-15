#include "include/game.h"
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <time.h>


void initGame(GameState* state) {
    state->isGameOver = 0;
    state->currentFloor = 0;
    state->msgCount = 0;

    state->isShopping = 0;
    // 初始化所有楼层为墙
    memset(state->map, WALL, sizeof(state->map));
    // 初始化所有传送点坐标
    memset(state->MAPX, 0, sizeof(state->MAPX));
    memset(state->MAPY, 0, sizeof(state->MAPY));
    // 设置各层起始位置
    state->MAPX[0] = 6;
    state->MAPY[0] = 1;
    state->MAPX[1] = 2;
    state->MAPY[1] = 1;
    state->MAPX[2] = 1;
    state->MAPY[2] = 1;
    state->MAPX[3] = 6;
    state->MAPY[3] = 11;
    // 初始化战斗消息
    memset(state->battleMsg, 0, sizeof(state->battleMsg));
    // 初始化玩家（确保玩家初始位置与第一层起始位置一致）
    initPlayer(&state->player, state);
    // 初始化图鉴
    state->isViewingBestiary = 0;
    state->bestiarySelection = 0;

// 第一层地图数据
int floor0[MAP_HEIGHT][MAP_WIDTH] = {
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, ITEM_KEY_YELLOW, WALL, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, DOOR_YELLOW, ITEM_SWORD, WALL, EMPTY, WALL},
    {WALL, EMPTY, WALL, EMPTY, MONSTER_SLIME, MONSTER_SKELETON, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL},
    {WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, ITEM_RED_POTION, WALL, EMPTY, WALL},
    {WALL, EMPTY, MONSTER_SLIME, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL},
    {WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, MONSTER_SLIME, WALL},
    {WALL, ITEM_KEY_YELLOW, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL},
    {WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, PORTAL_UP, WALL},
    {WALL, EMPTY, WALL, EMPTY, ITEM_SHIELD, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, ITEM_BLUE_POTION, WALL},
    {WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL},
    {WALL, EMPTY, MONSTER_SKELETON, EMPTY, WALL, MONSTER_SKELETON, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
};

int floor1[MAP_HEIGHT][MAP_WIDTH] = {
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, PORTAL_DOWN, EMPTY, EMPTY, MONSTER_BEAST, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, MONSTER_SKELETON, ITEM_RED_POTION, WALL},
    {WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, DOOR_BLUE, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, ITEM_KEY_BLUE, WALL, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, DOOR_YELLOW, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, MONSTER_BEAST, MONSTER_SKELETON, ITEM_KEY_YELLOW, WALL, EMPTY, WALL},
    {WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL},
    {WALL, ITEM_KEY_RED, EMPTY, EMPTY, MONSTER_WIZARD, MONSTER_SKELETON, ITEM_SWORD, MONSTER_SLIME,MONSTER_BEAST, ITEM_SHIELD, WALL, MONSTER_WIZARD, WALL},
    {WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, PORTAL_UP, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL},
    {WALL, DOOR_BLUE, WALL, MONSTER_WIZARD, WALL, EMPTY, WALL, EMPTY, MERCHANT, EMPTY, WALL, EMPTY, WALL},
    {WALL, EMPTY, ITEM_BLUE_POTION, EMPTY, WALL, MONSTER_WIZARD, EMPTY, EMPTY, WALL, EMPTY, DOOR_YELLOW, EMPTY, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
};

int floor2[MAP_HEIGHT][MAP_WIDTH] = {
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, PORTAL_DOWN, ITEM_KEY_YELLOW, WALL, MONSTER_BEAST, EMPTY, EMPTY, WALL, EMPTY, ITEM_KEY_YELLOW, EMPTY, WALL},
    {WALL, EMPTY, ITEM_KEY_BLUE, EMPTY, WALL, MONSTER_BEAST, WALL, ITEM_RED_POTION, WALL, MONSTER_SKELETON, MONSTER_SKELETON, MONSTER_SKELETON, WALL},
    {WALL, EMPTY, MONSTER_WIZARD, EMPTY, DOOR_YELLOW, EMPTY, MONSTER_WIZARD, ITEM_SHIELD, DOOR_BLUE, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, WALL, DOOR_BLUE, WALL, WALL, WALL, DOOR_YELLOW, WALL, WALL, WALL, DOOR_YELLOW, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, ITEM_KEY_YELLOW, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, ITEM_RED_POTION, ITEM_SWORD, ITEM_RED_POTION, WALL, EMPTY, MERCHANT, EMPTY, WALL, ITEM_BLUE_POTION, ITEM_SHIELD, ITEM_BLUE_POTION, WALL},
    {WALL, MONSTER_SKELETON, EMPTY, MONSTER_SKELETON, WALL, EMPTY, ITEM_KEY_BLUE, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, WALL, MONSTER_WIZARD, WALL, WALL, WALL, MONSTER_SKELETON, WALL, WALL, WALL, DOOR_RED, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, ITEM_KEY_RED, EMPTY, WALL, EMPTY, MONSTER_KING_FAKE, EMPTY, WALL},
    {WALL, EMPTY, MONSTER_BEAST, EMPTY, DOOR_RED, EMPTY, ITEM_BLUE_POTION, EMPTY, WALL, EMPTY, PORTAL_UP, EMPTY, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
};

int floor3[MAP_HEIGHT][MAP_WIDTH] = {
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, PRINCESS, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, DOOR_RED, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, ITEM_KEY_RED, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, EMPTY, EMPTY, MONSTER_KING, EMPTY, EMPTY, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
};
    
    memcpy(state->map[0], floor0, sizeof(floor0));
    memcpy(state->map[1], floor1, sizeof(floor1));
    memcpy(state->map[2], floor2, sizeof(floor2));
    memcpy(state->map[3], floor3, sizeof(floor3));
    state->inBattle = 0;
}

void initPlayer(Player* player, GameState* state) {
    // 设置玩家初始状态

    player->x = state->MAPX[state->currentFloor];
    player->y = state->MAPY[state->currentFloor];
    player->floor = state->currentFloor;

    player->hp = 100;
    player->attack = 10;
    player->defense = 4;
    player->gold = 0;
    player->exp = 0;
    player->level = 1;
    player->direction = 0;
    player->expToLevelUp = 100;
    // 初始化钥匙数量
    player->keys[0] = 0;  // 黄钥匙
    player->keys[1] = 0;  // 蓝钥匙
    player->keys[2] = 0;  // 红钥匙
}



int canMove(GameState* state, int newX, int newY) {
    // 检查是否超出地图边界
    if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT || 
        state->currentFloor < 0 || state->currentFloor >= FLOORS_COUNT) {
        return 0;
    }
    
    // 获取目标位置的物体类型
    int objectType = state->map[state->currentFloor][newY][newX];
    
    switch (objectType) {
        case WALL:
            return 0;
            
        case MONSTER_SLIME:
        case MONSTER_SKELETON:
        case MONSTER_WIZARD:
        case MONSTER_BEAST:
        case MONSTER_KING:
            {
                Monster monster = getMonsterStats(objectType);
                monster.x = newX;
                monster.y = newY;
                char msg[256];
                sprintf(msg, "遭遇%s！", getMonsterName(objectType));
                addBattleMessage(state, msg);
                
                // 开始战斗
                state->inBattle = 1;
                state->currentMonster = monster;
                return 0;  // 不要移动到怪物位置
            }
        case MONSTER_KING_FAKE:
            {
                Monster monster = getMonsterStats(objectType);
                monster.x = newX;
                monster.y = newY;
                char msg[256];
                sprintf(msg, "遭遇%s！", getMonsterName(objectType));
                addBattleMessage(state, msg);
                addBattleMessage(state, "魔王:来吧，勇士！让我见识见识你的实力！");
                // 开始战斗
                state->inBattle = 1;
                state->currentMonster = monster;
                return 0;  // 不要移动到怪物位置
            }
        case DOOR_YELLOW:
            if (state->player.keys[0] == 0) return 0;
            state->player.keys[0]--;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "打开了黄门");
            return 0;
            
        case DOOR_BLUE:
            if (state->player.keys[1] == 0) return 0;
            state->player.keys[1]--;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "打开了蓝门");
            return 0;
            
        case DOOR_RED:
            if (state->player.keys[2] == 0) return 0;
            state->player.keys[2]--;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "打开了红门");
            return 0;
            
        case ITEM_SWORD:
            state->player.attack += 4;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "获得剑，攻击力+4！");
            return 1;
            
        case ITEM_SHIELD:
            state->player.defense += 2;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "获得盾，防御力+2！");
            return 1;
            
        case ITEM_RED_POTION:
            state->player.hp += 20;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "喝下红药水，生命值+20！");
            return 1;
            
        case ITEM_BLUE_POTION:
            state->player.hp += 50;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "喝下蓝药水，生命值+50！");
            return 1;
            
        case ITEM_KEY_YELLOW:
            state->player.keys[0]++;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "获得黄钥匙！");
            return 1;
            
        case ITEM_KEY_BLUE:
            state->player.keys[1]++;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "获得蓝钥匙！");
            return 1;
            
        case ITEM_KEY_RED:
            state->player.keys[2]++;
            state->map[state->currentFloor][newY][newX] = EMPTY;
            addBattleMessage(state, "获得红钥匙！");
            return 1;
        
        case MERCHANT:
            state->isShopping = 1;
            return 0;
        
        case PRINCESS:
            addBattleMessage(state, "公主：勇士，你终于来了！感谢你救了我，我愿意以身相许，嫁给你为妻！\n");
            system("pause");
            state->isGameOver = 1;
            return 0;
        
        case PORTAL_UP:
            if (state->currentFloor < FLOORS_COUNT - 1) {
                // 记录当前楼层的传送门位置
                state->lastPortal_X[state->currentFloor] = state->player.x;
                state->lastPortal_Y[state->currentFloor] = state->player.y;
                
                // 移动到上层
                state->currentFloor++;
                state->player.x = state->MAPX[state->currentFloor];
                state->player.y = state->MAPY[state->currentFloor];
                addBattleMessage(state, "进入上层传送门");
            }
            return 0;

        case PORTAL_DOWN:
            if (state->currentFloor > 0) {
                state->currentFloor--;
                // 使用对应楼层保存的传送门位置
                state->player.x = state->lastPortal_X[state->currentFloor];
                state->player.y = state->lastPortal_Y[state->currentFloor];
                addBattleMessage(state, "进入下层传送门");
            }
            return 0;
            state->isShopping = 1;
            return 0;

        case EMPTY:
            return 1;
            
        default:
            return 1;
    }
    
    return 1;
}



// 更新游戏状
void updateGame(GameState* state, void* userData) {
    if (!state->inBattle && !state->isShopping) {
        int currentTile = state->map[state->currentFloor][state->player.y][state->player.x];
        
        // 检查是否遇到怪物
        if (currentTile >= MONSTER_SLIME && currentTile <= MONSTER_KING) {
            state->inBattle = 1;
            state->currentMonster = getMonsterStats(currentTile);
            char msg[256];
            sprintf(msg, "遇到了%s！", getMonsterName(currentTile));
            addBattleMessage(state, msg);
        }
    }
}

void saveGame(GameState* state) {
    FILE* file = fopen("save.dat", "wb");  // 使用二进制模式打开文件
    if (file == NULL) {
        // 文件打开失败，显示错误消息
        HWND window = GetHWnd();
        MessageBox(window, "无法保存游戏！", "错误", MB_OK | MB_ICONERROR);
        return;
    }
    
    // 写入数据
    size_t written = fwrite(state, sizeof(GameState), 1, file);
    fclose(file);
    
    // 检查是否成功写入
    if (written != 1) {
        HWND window = GetHWnd();
        MessageBox(window, "保存游戏失败！", "错误", MB_OK | MB_ICONERROR);
        return;
    }
    // 保存成功提示
    addBattleMessage(state, "游戏已保存");
}

void loadGame(GameState* state) {
    FILE* file = fopen("save.dat", "rb");  // 使用二进制模式打开文件
    if (file == NULL) {
        HWND window = GetHWnd();
        MessageBox(window, "未找到存档文件！", "错误", MB_OK | MB_ICONERROR);
        return;
}
    
    // 读取整个GameState
    size_t read = fread(state, sizeof(GameState), 1, file);
    fclose(file);
    
    if (read != 1) {
        HWND window = GetHWnd();
        MessageBox(window, "读取存档失败！", "错误", MB_OK | MB_ICONERROR);
        return;
    }

    // 清除任何可能的状态
    state->inBattle = 0;  // 确保不在战斗中
    state->isShopping = 0;  // 确保不在商店中
    
    addBattleMessage(state, "游戏已读取");
}

// 根据怪物类型返回怪物属性
Monster getMonsterStats(int monsterType) {
    Monster monster;
    monster.type = monsterType;
    
    switch (monsterType) {
        case MONSTER_SLIME:
            monster.hp = 50;
            monster.attack = 8;
            monster.defense = 2;
            monster.exp = 30;
            monster.gold = 10;
            break;
            
        case MONSTER_SKELETON:
            monster.hp = 70;
            monster.attack = 9;
            monster.defense = 7;
            monster.exp = 60;
            monster.gold = 25;
            break;
            
        case MONSTER_WIZARD:
            monster.hp = 140;
            monster.attack = 25;
            monster.defense = 6;
            monster.exp = 80;
            monster.gold = 30;
            break;
        case MONSTER_KING:
            monster.hp = 500;
            monster.attack = 35;
            monster.defense = 25;
            monster.exp = 1000;
            monster.gold = 1000;
            break;
        case MONSTER_BEAST:
            monster.hp = 80;
            monster.attack = 12;
            monster.defense = 9;
            monster.exp = 70;
            monster.gold = 25;
            break;
        case MONSTER_KING_FAKE:
            monster.hp = 300;
            monster.attack = 30;
            monster.defense = 20;
            monster.exp = 300;
            monster.gold = 200;
            break;
    }
    
    return monster;
}


void addBattleMessage(GameState* state, const char* msg) {
    // 如果消息数组已满，向上移动所有消息
    if (state->msgCount >= BATTLE_MSG_LINES) {
        for (int i = 0; i < BATTLE_MSG_LINES - 1; i++) {
            strcpy(state->battleMsg[i], state->battleMsg[i + 1]);
        }
        strcpy(state->battleMsg[BATTLE_MSG_LINES - 1], msg);
    } else {
        // 否则直接添加到下一行
        strcpy(state->battleMsg[state->msgCount], msg);
        state->msgCount++;
    }
}

BattleResult battleTurn(GameState* state, Monster* monster) {
    // 玩家回合
    int damage = state->player.attack - monster->defense;
    if (damage < 1) damage = 1;
    monster->hp -= damage;
    
    char msg[256];
    sprintf(msg, "勇士攻击了%s，造成%d点伤害！", getMonsterName(monster->type), damage);
    addBattleMessage(state, msg);
    
    // 检查怪物是否死亡
    if (monster->hp <= 0) {
        state->player.exp += monster->exp;
        state->player.gold += monster->gold;
        sprintf(msg, "战斗胜利！获得%d经验，%d金币", monster->exp, monster->gold);
        addBattleMessage(state, msg);
        return BATTLE_WIN;
    }
    
    // 怪物回合
    damage = monster->attack - state->player.defense;
    if (damage < 1) damage = 1;
    state->player.hp -= damage;
    sprintf(msg, "%s反击，对勇士造成%d点伤害！", getMonsterName(monster->type), damage);
    addBattleMessage(state, msg);

    // 检查玩家是否死亡
    if (state->player.hp <= 0) {
        addBattleMessage(state, "勇士被打败了...");
        return BATTLE_LOSE;
    }
    
    return BATTLE_CONTINUE;
}

// 获取怪物名称的辅助函数
const char* getMonsterName(int monsterType) {
    switch (monsterType) {
        case MONSTER_SLIME:
            return "史莱姆";
        case MONSTER_SKELETON:
            return "骷髅";
        case MONSTER_WIZARD:
            return "法师";
        case MONSTER_KING:
            return "魔王";
        case MONSTER_BEAST:
            return "野兽";
        case MONSTER_KING_FAKE:
            return "魔王";
        default:
            return "未知怪物";
    }
}

void handleBattle(GameState* state, void* userData) {
    static clock_t lastBattleTime = 0;
    clock_t currentTime = clock();
    
    // 每隔1秒进行一次战斗回合
    if (state->inBattle && (currentTime - lastBattleTime) >= CLOCKS_PER_SEC/2) {
        lastBattleTime = currentTime;  // 更新上次战斗时间
        
        // 计算玩家对怪物的伤害
        int playerDamage = state->player.attack - state->currentMonster.defense;
        if (playerDamage < 0) playerDamage = 0;
        
        // 计算怪物对玩家的伤害
        int monsterDamage = state->currentMonster.attack - state->player.defense;
        if (monsterDamage < 0) monsterDamage = 0;
        
        // 玩家攻击
        if(playerDamage<=2)
        playerDamage=2;
        state->currentMonster.hp -= playerDamage;
        char msg[256];
        sprintf(msg, "勇士对%s发起进攻，造成%d点伤害", 
                getMonsterName(state->currentMonster.type), playerDamage);
        addBattleMessage(state, msg);
        
        // 检查怪物是否死亡
        if (state->currentMonster.hp <= 0) {
            // 获得经验和金币
            state->player.exp += state->currentMonster.exp;
            state->player.gold += state->currentMonster.gold;
            
            // 使用怪物的位置来清除怪物
            state->map[state->currentFloor][state->currentMonster.y][state->currentMonster.x] = EMPTY;
            
            sprintf(msg, "战斗胜利！获得%d经验和%d金币", 
                    state->currentMonster.exp, state->currentMonster.gold);
            addBattleMessage(state, msg);
            
            // 检查是否升级
            while (state->player.exp >= state->player.expToLevelUp) {
                state->player.level++;
                state->player.exp -= state->player.expToLevelUp;
                state->player.expToLevelUp *= 1.5;  // 每级需要更多经验
                
                // 升级加属性
                state->player.hp += 100;
                state->player.attack += 3;
                state->player.defense += 1;
                
                sprintf(msg, "升级了！等级：%d HP+100 攻击+3 防御+1", 
                        state->player.level);
                addBattleMessage(state, msg);
            }
            
            state->inBattle = 0;
            return;
        }
        
        // 怪物反击
        if(monsterDamage<=3)
        monsterDamage=3;
        state->player.hp -= monsterDamage;
        sprintf(msg, "%s对勇士发起反击，造成%d点伤害", 
                getMonsterName(state->currentMonster.type), monsterDamage);
        addBattleMessage(state, msg);
        
        // 检查玩家是否死亡
        if (state->player.hp <= 0) {
            addBattleMessage(state, "你死了！游戏结束！");
            state->isGameOver = 1;
            state->inBattle = 0;
        }
    }
}

void handleShop(GameState* state, void* userData) {
    if (state->isShopping && _kbhit()) {
        char key = _getch();
        char msg[256];
        
        switch (key) {
            case '1':
                if (state->player.gold >= 100) {
                    state->player.gold -= 100;
                    state->player.attack += 4;
                    addBattleMessage(state, "购买剑，攻击力+4！");
                } else {
                    addBattleMessage(state, "商人：穷逼你先显摆啥呢！");
                }
                break;
                
            case '2':
                if (state->player.gold >= 150) {
                    state->player.gold -= 150;
                    state->player.defense += 2;
                    addBattleMessage(state, "购买盾，防御力+2！");
                } else {
                    addBattleMessage(state, "商人：穷逼你先显摆啥呢！");
                }
                break;
                
            case '3':
                if (state->player.gold >= 50) {
                    state->player.gold -= 50;
                    state->player.hp += 20;
                    addBattleMessage(state, "购买红药水，生命值+20！");
                } else {
                    addBattleMessage(state, "商人：穷逼你先显摆啥呢！");
                }
                break;
                
            case '0':
                state->isShopping = 0;
                addBattleMessage(state, "离开商店");
                break;

        }
    }
}

const MonsterInfo MONSTER_INFO[] = {
    {
        "史莱姆",
        "弱小的粘液生物，全属性较低",
        MONSTER_SLIME,
        50,
        8,
        2,
        30,
        10
    },
    {
        "骷髅",
        "骷髅战士，攻高防中",
        MONSTER_SKELETON,
        70,
        9,
        7,
        60,
        25
    },
    {
        "野兽",
        "凶猛的野兽，攻防均高",
        MONSTER_BEAST,
        80,
        12,
        9,
        70,
        25
    },
    {
        "法师",
        "攻高防低的魔法师",
        MONSTER_WIZARD,
        140,
        25,
        6,
        80,
        30
    },
    {
        "魔王",
        "最终BOSS，全属性极高",
        MONSTER_KING,
        500,
        35,
        25,
        1000,
        1000
    }
};

const int MONSTER_COUNT = sizeof(MONSTER_INFO) / sizeof(MonsterInfo);
