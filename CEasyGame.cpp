#include"pch.h"
#include "CEasyGame.h"
#include"CGameLogic.h"
#include"CGraph.h"

CEasyGame::CEasyGame()
{
}


CEasyGame::~CEasyGame()
{
}
void CEasyGame::StartGame()
{
	CGameLogic gameLogic;

	gameLogic.InitMap(m_graph);
}

BOOL CEasyGame::IsWin(int nTime)
{
	CGameLogic logic;
	if (logic.IsBLANK(m_graph)) {//全部都消除了
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CEasyGame::Help(Vertex anPath[], int& nVertexNum)
{
	CGameLogic logic;
	//判断图是否为空
	if (logic.IsBLANK(m_graph)) {
		return false;
	}
	if (logic.SearchValidPath(m_graph)) {
		nVertexNum = logic.GetVexPath(anPath);
	}
	return false;
}

void CEasyGame::ResetGame()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}
