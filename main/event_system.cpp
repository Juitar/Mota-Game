#include "include/event_system.h"
#include <graphics.h>

static GameCallbacks g_callbacks = {0};  // 初始化为0

void registerCallbacks(GameCallbacks* callbacks) {
    if (callbacks) {
        g_callbacks = *callbacks;
    }
}

void processEvents(GameState* state) {
    // 处理输入
    if (g_callbacks.onInput) {
        g_callbacks.onInput(state, g_callbacks.userData);
    }
    
    // 更新游戏状态
    if (g_callbacks.onUpdate) {
        g_callbacks.onUpdate(state, g_callbacks.userData);
    }
    
    // 处理战斗
    if (state->inBattle && g_callbacks.onBattle) {
        g_callbacks.onBattle(state, g_callbacks.userData);
    }
    
    // 处理商店
    if (state->isShopping && g_callbacks.onShop) {
        g_callbacks.onShop(state, g_callbacks.userData);
    }
    
    // 渲染
    if (g_callbacks.onRender) {
        g_callbacks.onRender(state, g_callbacks.userData);
    }
    
    FlushBatchDraw();
}