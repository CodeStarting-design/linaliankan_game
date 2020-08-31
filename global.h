#pragma once

typedef struct tagVertex {
	int row;           //行
	int col;           //列
	int info;
}Vertex;
typedef struct tagFlag
{
	bool bTimer;//是否计时
	bool bProp;//道具
	bool bScore;//积分
	CString szTitle;//对话框标题
}FLAG;
#define BLANK -1
#define ROW_NUM 10
#define COL_NUM 16
#define MAX_VERTEX_NUM 160
#define MAX_PIC_NUM 16//图片花色
#define REPEAT_NUM 10//每种花色图片个数
#define PLAY_TIMER_ID 1//计时器
#define GAME_LOSE -1//游戏失败
#define GAME_SUCCESS 0//游戏胜利
#define GAME_PLAY 1//游戏还可以继续

