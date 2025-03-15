#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "game.h"

// 回调函数类型定义
typedef void (*InputCallback)(GameState* state, void* userData);
typedef void (*UpdateCallback)(GameState* state, void* userData);
typedef void (*RenderCallback)(GameState* state, void* userData);
typedef void (*BattleCallback)(GameState* state, void* userData);
typedef void (*ShopCallback)(GameState* state, void* userData);

// 回调结构体
typedef struct {
    InputCallback onInput;
    UpdateCallback onUpdate;
    RenderCallback onRender;
    BattleCallback onBattle;
    ShopCallback onShop;
    void* userData;
} GameCallbacks;

// 事件系统函数
void registerCallbacks(GameCallbacks* callbacks);
void processEvents(GameState* state);

#endif