#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <mmsystem.h>
#include "include/game.h"
#include "include/event_system.h"
#pragma comment(lib, "winmm.lib")

// 音频相关函数
void playBGM() {
    if (!PlaySound("resources/sound/bgm.wav", NULL, 
        SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT)) {
        DWORD error = GetLastError();
        char msg[256];
        sprintf(msg, "音乐播放失败！错误代码：%lu", error);
        MessageBox(GetHWnd(), msg, "错误", MB_OK | MB_ICONERROR);
    }
}

void stopBGM() {
    PlaySound(NULL, NULL, 0);
}

void handleInput(GameState* state, void* userData) {
            if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {  // 左键点击
                // 计算点击的格子坐标
                int gridX = (msg.x - MAP_OFFSET_X) / GRID_SIZE;
                int gridY = (msg.y - MAP_OFFSET_Y) / GRID_SIZE;
                
                // 检查是否在地图范围内且在玩家相邻格子上
                if (gridX >= 0 && gridX < MAP_WIDTH && gridY >= 0 && gridY < MAP_HEIGHT) {
                    if ((abs(gridX - state->player.x) == 1 && gridY == state->player.y) ||
                        (gridX == state->player.x && abs(gridY - state->player.y) == 1)) {
                        // 移动到点击的格子
                        if (canMove(state, gridX, gridY)) {
                            // 更新玩家朝向
                            if (gridX > state->player.x) state->player.direction = 1;      // 右
                            else if (gridX < state->player.x) state->player.direction = 2; // 左
                            else if (gridY < state->player.y) state->player.direction = 3; // 上
                            else if (gridY > state->player.y) state->player.direction = 0; // 下
                            
                            // 移动到新位置
                            state->player.x = gridX;
                            state->player.y = gridY;
                        }
                    }
                }
            }
        }
        
    if (_kbhit()) {
        char key = _getch();
        
        // 如果在查看图鉴
        if (state->isViewingBestiary) {
            switch (key) {
                case 'w': case 'W':  // 上选择
                    if (state->bestiarySelection > 0) {
                        state->bestiarySelection--;
                    }
                    break;
                    
                case 's': case 'S':  // 下选择
                    if (state->bestiarySelection < MONSTER_COUNT - 1) {
                        state->bestiarySelection++;
                    }
                    break;
                    
                case 'i': case 'I': case 27:  // I或ESC退出图鉴
                    state->isViewingBestiary = 0;
                    break;
            }
            return;
        }
        
        // 如果在战斗中，只处理ESC键
        if (state->inBattle) {
            if (key == 27) {  // ESC键
                state->isGameOver = 1;
            }
            return;  // 战斗中忽略其他所有输入
        }
        
        // 如果在商店中，处理商店相关的按键
        if (state->isShopping) {
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
                    
                case 27:  // ESC键
                    state->isGameOver = 1;
                    break;
            }
            return;
        }
        
        // 正常游戏状态下处理移动等操作
        int newX = state->player.x;
        int newY = state->player.y;
        
        switch (key) {
            case 'w': case 'W': newY--; state->player.direction = 3; break;
            case 's': case 'S': newY++; state->player.direction = 0; break;
            case 'a': case 'A': newX--; state->player.direction = 2; break;
            case 'd': case 'D': newX++; state->player.direction = 1; break;
            case 'm': case 'M': saveGame(state); return;
            case 'l': case 'L': loadGame(state); return;
            case 27: state->isGameOver = 1; break;
        }
        
        if (canMove(state, newX, newY)) {
            state->player.x = newX;
            state->player.y = newY;
        }
        
        // 添加打开图鉴的按键
        if (key == 'i' || key == 'I') {
            state->isViewingBestiary = 1;
            state->bestiarySelection = 0;
            return;
        }

    }
}

// 游戏更新回调
void gameUpdate(GameState* state, void* userData) {
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
    }}



int main() {
    GameState gameState;
    // 注册回调函数，使用新的函数名
    GameCallbacks callbacks = {
        .onInput = handleInput,
        .onUpdate = gameUpdate,    
        .onRender = gameRender,   
        .onBattle = handleBattle,
        .onShop = handleShop,
        .userData = NULL
    };
    
    initgraph(644, 404 + 88);
    setbkcolor(WHITE);
    cleardevice();
    
    HWND hwnd = GetHWnd();
    SetWindowText(hwnd, "稽塔");


    loadResources();
    playBGM();
    
    initGame(&gameState);
    registerCallbacks(&callbacks);
    
    BeginBatchDraw();
    while (!gameState.isGameOver) {
        processEvents(&gameState);
        Sleep(16);
    }
    EndBatchDraw();
    
    stopBGM();
    closegraph();
    return 0;
}