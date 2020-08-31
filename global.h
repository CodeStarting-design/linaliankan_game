#pragma once

typedef struct tagVertex {
	int row;           //��
	int col;           //��
	int info;
}Vertex;
typedef struct tagFlag
{
	bool bTimer;//�Ƿ��ʱ
	bool bProp;//����
	bool bScore;//����
	CString szTitle;//�Ի������
}FLAG;
#define BLANK -1
#define ROW_NUM 10
#define COL_NUM 16
#define MAX_VERTEX_NUM 160
#define MAX_PIC_NUM 16//ͼƬ��ɫ
#define REPEAT_NUM 10//ÿ�ֻ�ɫͼƬ����
#define PLAY_TIMER_ID 1//��ʱ��
#define GAME_LOSE -1//��Ϸʧ��
#define GAME_SUCCESS 0//��Ϸʤ��
#define GAME_PLAY 1//��Ϸ�����Լ���

