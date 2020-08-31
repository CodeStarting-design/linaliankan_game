#include "pch.h"
#include "CBasicGame.h"
#include"CGameLogic.h"
#include"CGraph.h"

CBasicGame::CBasicGame()
{
}


CBasicGame::~CBasicGame()
{
}

void CBasicGame::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}
