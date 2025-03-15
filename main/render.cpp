#include "include/game.h"
#include <graphics.h>  // 确保包含图形库
#include <tchar.h>     


// 全局变量存储图片
IMAGE bgImage;      // 背景图片
IMAGE wallImage;    // 墙壁图片
IMAGE floorImage;   // 地板图片
IMAGE playerImage[4];  // 玩家图片
IMAGE itemImages[20]; // 物品图片数组s
IMAGE DOOR[3]; // 门图片
IMAGE SKELETON; // 骷髅图片
IMAGE SLIME; // 史莱姆图片
IMAGE WIZARD; // 巫师图片
IMAGE BEAST; // 野兽图片
IMAGE portalImage; // 传送门图片
IMAGE merchantImage; // 商人图片
IMAGE princessImage;
IMAGE bossImage;


// 加载所有图片资源
void loadResources() {
    //加载背景图片
    loadimage(&bgImage, "resources/images/background.png");
    //加载墙壁图片
    loadimage(&wallImage, "resources/images/wall.png");
    //加载地板图片
    loadimage(&floorImage, "resources/images/floor.png");
    //加载玩家图片
    loadimage(&playerImage[0], "resources/images/player.png");
    loadimage(&playerImage[1], "resources/images/player_left.png");
    loadimage(&playerImage[2], "resources/images/player_right.png");
    loadimage(&playerImage[3], "resources/images/player_up.png");
    //加载物品图片
    loadimage(&itemImages[ITEM_SWORD], "resources/images/sword.png");
    loadimage(&itemImages[ITEM_SHIELD], "resources/images/shield.png");
    loadimage(&itemImages[ITEM_RED_POTION], "resources/images/red_potion.png");
    loadimage(&itemImages[ITEM_BLUE_POTION], "resources/images/blue_potion.png");
    loadimage(&itemImages[ITEM_KEY_YELLOW], "resources/images/key_yellow.png");
    loadimage(&itemImages[ITEM_KEY_BLUE], "resources/images/key_blue.png");
    loadimage(&itemImages[ITEM_KEY_RED], "resources/images/key_red.png");
    loadimage(&itemImages[ITEM_RED_POTION], "resources/images/potion_red.png");
    loadimage(&itemImages[ITEM_BLUE_POTION], "resources/images/potion_blue.png");
    //加载门图片
    loadimage(&DOOR[0], "resources/images/door_yellow.png");
    loadimage(&DOOR[1], "resources/images/door_blue.png");
    loadimage(&DOOR[2], "resources/images/door_red.png");

    //加载怪物图片
    loadimage(&SKELETON, "resources/images/skeleton.png");
    loadimage(&SLIME, "resources/images/slime.png");
    loadimage(&WIZARD, "resources/images/wizard.png");
    loadimage(&BEAST, "resources/images/beast.png");
    //加载传送门图片
    loadimage(&portalImage, "resources/images/portal.png");
    //加载商人图片
    loadimage(&merchantImage, "resources/images/merchant.png");
    //加载公主图片
    loadimage(&princessImage, "resources/images/princess.png");
    //加载魔王图片
    loadimage(&bossImage, "resources/images/boss.png");
    // 加载物品图片...
    
    // 检查图片是否加载成功
    if (bgImage.getwidth() == 0) {
        MessageBox(GetHWnd(), "背景图片加载失败！", "错误", MB_OK | MB_ICONERROR);
    }
}

// 绘制地图
void drawMap(GameState* state) {
    // 先绘制背景
    putimage(0, 0, &bgImage);
    
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int screenX = MAP_OFFSET_X + x * GRID_SIZE;
            int screenY = MAP_OFFSET_Y + y * GRID_SIZE;
            
            // 直接绘制图片
            switch (state->map[state->currentFloor][y][x]) {
                case WALL:
                    putimage(screenX, screenY, &wallImage);
                    break;
                case EMPTY:
                    putimage(screenX, screenY, &floorImage);
                    break;
                case ITEM_SWORD:
                    putimage(screenX, screenY, &itemImages[ITEM_SWORD]);
                    break;
                case ITEM_SHIELD:
                    putimage(screenX, screenY, &itemImages[ITEM_SHIELD]);
                    break;
                case ITEM_RED_POTION:
                    putimage(screenX, screenY, &itemImages[ITEM_RED_POTION]);
                    break;
                case ITEM_BLUE_POTION:
                    putimage(screenX, screenY, &itemImages[ITEM_BLUE_POTION]);
                    break;
                case ITEM_KEY_YELLOW:
                    putimage(screenX, screenY, &itemImages[ITEM_KEY_YELLOW]);
                    break;
                case ITEM_KEY_BLUE:
                    putimage(screenX, screenY, &itemImages[ITEM_KEY_BLUE]);
                    break;
                case ITEM_KEY_RED:
                    putimage(screenX, screenY, &itemImages[ITEM_KEY_RED]);
                    break;

                case DOOR_YELLOW:
                    putimage(screenX, screenY, &DOOR[0]);
                    break;
                case DOOR_BLUE:
                    putimage(screenX, screenY, &DOOR[1]);
                    break;
                case DOOR_RED:
                    putimage(screenX, screenY, &DOOR[2]);
                    break;

                case MONSTER_SKELETON:
                    putimage(screenX, screenY, &SKELETON);
                    break;
                case MONSTER_SLIME:
                    putimage(screenX, screenY, &SLIME);
                    break;
                case MONSTER_WIZARD:
                    putimage(screenX, screenY, &WIZARD);
                    break;
                case MONSTER_BEAST:
                    putimage(screenX, screenY, &BEAST);
                    break;

                case MERCHANT:
                    putimage(screenX, screenY, &merchantImage);
                    break;

                case PRINCESS:
                    putimage(screenX, screenY, &princessImage);
                    break;

                case PORTAL_UP:
                    putimage(screenX, screenY, &portalImage);
                    break;
                case PORTAL_DOWN:
                    putimage(screenX, screenY, &portalImage);
                    break;
                case MONSTER_KING:
                    putimage(screenX, screenY, &bossImage);
                    break;
                case MONSTER_KING_FAKE:
                    putimage(screenX, screenY, &bossImage);
                    break;
                default:
                    putimage(screenX, screenY, &floorImage);
                    break;

            }
        }
    }
}

// 绘制玩家
void drawPlayer(Player* player) {
    putimage(MAP_OFFSET_X + player->x * GRID_SIZE, 
             MAP_OFFSET_Y + player->y * GRID_SIZE, 
             &playerImage[player->direction]);
}

// 绘制用户界面
void drawUI(GameState* state) {
    // 设置文本样式
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    
    // 设置字体
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 12;
    _tcscpy(f.lfFaceName, _T("宋体"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    
    char info[200];
    int x_pos = 40;
    int y_pos = 85;
    int Y_OFFSET = 18;

    int Rx_pos = 550;
    int Ry_pos = 25;
    // 显示当前楼层
    sprintf(info, "当前楼层：%d", state->currentFloor + 1);
    outtextxy(Rx_pos, Ry_pos, info);

    // 显示基本属性
    sprintf(info, "生命值：%d", state->player.hp);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    
    sprintf(info, "攻击力：%d", state->player.attack);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    
    sprintf(info, "防御力：%d", state->player.defense);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    
    sprintf(info, "金币：%d", state->player.gold);
    outtextxy(x_pos, y_pos, info);
    y_pos += 40;
    
    // 显示钥匙
    sprintf(info, "黄钥匙：%d", state->player.keys[0]);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    
    sprintf(info, "蓝钥匙：%d", state->player.keys[1]);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    
    sprintf(info, "红钥匙：%d", state->player.keys[2]);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    
    // 显示等级
    sprintf(info, "等级：%d", state->player.level);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;
    //显示经验
    sprintf(info, "经验：%d/%d", state->player.exp, state->player.expToLevelUp);
    outtextxy(x_pos, y_pos, info);
    y_pos += 24;

    
    // 显示战斗消息（在地图下方）
    for(int i = 0; i < state->msgCount; i++)
    {
        //字体使用11
        settextstyle(12, 0, _T("宋体"));
        outtextxy(MAP_OFFSET_X+20, MAP_OFFSET_Y + MAP_HEIGHT * GRID_SIZE + Y_OFFSET, (const char*)state->battleMsg[i]);
        Y_OFFSET += 16;
    }

    // 绘制怪物信息
    if(state->inBattle)
    {
        Ry_pos = 105;
        Monster monsterType = state->currentMonster;
        const char*Mosternam = getMonsterName(monsterType.type);
        sprintf(info, "怪物：%s", Mosternam);
        outtextxy(Rx_pos, Ry_pos, info);
        Ry_pos += 40;
        sprintf(info, "生命值：%d", monsterType.hp);
        outtextxy(Rx_pos, Ry_pos, info);
        Ry_pos += 24;
        sprintf(info, "攻击力：%d", monsterType.attack);
        outtextxy(Rx_pos, Ry_pos, info);
        Ry_pos += 24;
        sprintf(info, "防御力：%d", monsterType.defense);
        outtextxy(Rx_pos, Ry_pos, info);
        Ry_pos += 24;
    }
    if(state->isShopping)
    {
        //绘制商店

        Ry_pos = 105;
        sprintf(info, "商人");
        outtextxy(Rx_pos+20, Ry_pos, info);
        Ry_pos += 40;
        settextstyle(11, 0, _T("宋体"));
        sprintf(info, "欢迎光临商店！");
        outtextxy(Rx_pos-25, Ry_pos, info);
        Ry_pos += 40;
        sprintf(info, "请选择要购买的商品：");
        outtextxy(Rx_pos-25, Ry_pos, info);
        Ry_pos += 40;
        sprintf(info, "1: 购买剑 100金币");
        outtextxy(Rx_pos-25, Ry_pos, info);
        Ry_pos += 30    ;
        sprintf(info, "2: 购买盾 150金币");
        outtextxy(Rx_pos-25, Ry_pos, info);
        Ry_pos += 30;
        sprintf(info, "3: 购买药水 50金币");
        outtextxy(Rx_pos-25, Ry_pos, info);
        Ry_pos += 30;
        sprintf(info, "请输入要购买的商品编号");
        outtextxy(Rx_pos-25, Ry_pos, info);
        Ry_pos += 30;
        sprintf(info, "0: 退出商店");
        outtextxy(Rx_pos-25, Ry_pos, info);
    }


}


void drawGame(GameState* state) {
    cleardevice();

    drawMap(state);
    
    drawPlayer(&state->player);
    
    drawUI(state);

    // 获取鼠标位置
    POINT mousePos;
    GetCursorPos(&mousePos);
    ScreenToClient(GetHWnd(), &mousePos);
    
    // 计算鼠标所在的格子
    int gridX = (mousePos.x - MAP_OFFSET_X) / GRID_SIZE;
    int gridY = (mousePos.y - MAP_OFFSET_Y) / GRID_SIZE;
    
    // 如果鼠标在地图范围内且在玩家相邻格子上
    if (gridX >= 0 && gridX < MAP_WIDTH && gridY >= 0 && gridY < MAP_HEIGHT) {
        if ((abs(gridX - state->player.x) == 1 && gridY == state->player.y) ||
            (gridX == state->player.x && abs(gridY - state->player.y) == 1)) {
            // 绘制高亮效果
            setlinecolor(YELLOW);
            rectangle(MAP_OFFSET_X + gridX * GRID_SIZE, 
                     MAP_OFFSET_Y + gridY * GRID_SIZE,
                     MAP_OFFSET_X + (gridX + 1) * GRID_SIZE - 1,
                     MAP_OFFSET_Y + (gridY + 1) * GRID_SIZE - 1);
        }
    }
}

void drawBestiary(GameState* state) {
    // 清屏
    setbkcolor(WHITE);
    cleardevice();
    // 设置文本样式
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    
    // 绘制标题
    settextstyle(24, 0, "宋体");
    outtextxy(280, 20, "怪物图鉴");
    
    // 绘制怪物列表
    settextstyle(16, 0, "宋体");
    for (int i = 0; i < MONSTER_COUNT; i++) {
        // 如果是当前选中的怪物，使用不同颜色
        if (i == state->bestiarySelection) {
            settextcolor(RED);
        } else {
            settextcolor(BLACK);
        }
        
        // 绘制怪物名称（左侧）
        outtextxy(50, 80 + i * 30, MONSTER_INFO[i].name);
    }
    
    // 绘制选中怪物的详细信息（右侧）
    const MonsterInfo* selected = &MONSTER_INFO[state->bestiarySelection];
    settextcolor(BLACK);
    
    char info[256];
    int startY = 80;
    
    // 绘制描述
    outtextxy(250, startY, selected->description);
    
    // 绘制属性
    sprintf(info, "生命值：%d", selected->hp);
    outtextxy(250, startY + 30, info);
    
    sprintf(info, "攻击力：%d", selected->attack);
    outtextxy(250, startY + 60, info);
    
    sprintf(info, "防御力：%d", selected->defense);
    outtextxy(250, startY + 90, info);
    
    sprintf(info, "经验值：%d", selected->exp);
    outtextxy(250, startY + 120, info);
    
    sprintf(info, "金币：%d", selected->gold);
    outtextxy(250, startY + 150, info);
    
    // 绘制操作提示
    settextstyle(12, 0, "宋体");
    outtextxy(50, 360, "W/S: 选择怪物  I/ESC: 返回游戏");
}

void gameRender(GameState* state, void* userData) {
    if (state->isViewingBestiary) {
        drawBestiary(state);
    } else {
        drawGame(state);
    }
}

