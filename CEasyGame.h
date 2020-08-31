#pragma once

#include "CGameControl.h"
class CEasyGame :
	public CGameControl
{
public:
	CEasyGame();
	~CEasyGame();
	void StartGame();
	BOOL IsWin(int nTime);
	bool Help(Vertex anPath[], int& nVertexNum);
	void ResetGame();//жьее
};
