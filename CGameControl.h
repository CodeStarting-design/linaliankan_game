#pragma once
#include"global.h"
#include"CGraph.h"
class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);
	int m_nGrade;//积分
	int m_nProp;//道具数量
	int GetGrade();//获取积分
	bool  PropLink();//使用道具
	void PlusGrade(int time);//消子后加分
	void MinusGrade();//使用提示后减分
	int  GetnProp();//获取当前道具数
	virtual void StartGame() = 0;//定义为纯虚函数
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[], int& nVertex);//连接消子，并返回对应的点个数
	void SetGameFlag(FLAG flag);//设置游戏标志
	FLAG GetGameFlag();//获取游戏标志
	//子类中实现的特有函数
	virtual BOOL IsWin(int nTime);//判断胜负
    virtual bool Help(Vertex anPath[],int& nVertexNum);//提示函数
	virtual void ResetGame();//重排
protected:
	CGraph m_graph;      //存储游戏地图
	Vertex m_ptSelFirst;   //选中的第一个点
	Vertex m_ptSelSec;     //选中的第二个点

private:
	FLAG m_flag;
public:
	void plusnProp();
};
