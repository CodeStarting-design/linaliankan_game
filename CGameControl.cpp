#include "pch.h"
#include "CGameControl.h"
#include"CGameLogic.h"
#include"global.h"

CGameControl::CGameControl(void)
{
	m_nGrade = 0;
	m_nProp = 0;
}

CGameControl::~CGameControl(void)
{
}


int CGameControl::GetElement(int nRow, int nCol)
{
	int index = nRow * COL_NUM + nCol;
	return m_graph.GetVertex(index);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}
int CGameControl::GetGrade()
{
	return m_nGrade;
}
bool  CGameControl::PropLink()
{
	CGameLogic gameLogic;
	Vertex v1, v2;
	for (int i = 0; i < m_graph.GetVexnum(); i++)
	{
		for (int j = 0; j < m_graph.GetVexnum(); j++)
		{
			if (i != j && m_graph.GetVertex(i) != BLANK)
			{
				if (m_graph.GetVertex(j) == m_graph.GetVertex(i))
				{
					v1.col = i % COL_NUM;
					v1.row = i / COL_NUM;
					v2.col = j % COL_NUM;
					v2.row = j / COL_NUM;
					if (gameLogic.IsLink(m_graph, v1, v2))
					{
						m_nGrade += 10;
						m_nProp--;
						gameLogic.Clear(m_graph, v1, v2);
						return true;
					}
				}
			}
		}
	}
	return false;
}
void CGameControl::PlusGrade(int time)
{
	m_nGrade += time;
}
void CGameControl::MinusGrade()
{
	m_nGrade -= 10;
}
int  CGameControl::GetnProp()
{
	return m_nProp;
}
bool CGameControl::Link(Vertex avPath[], int& nVertex)
{

	//�ж��Ƿ�Ϊͬһ��ͼƬ

	//�ж��Ƿ�Ϊͬһ��ͼƬ
	if (m_ptSelFirst.col == m_ptSelSec.col && m_ptSelFirst.row == m_ptSelSec.row) {

		return false;

	}

	if (m_graph.GetVertex(m_ptSelFirst.row*COL_NUM+ m_ptSelFirst.col)!= m_graph.GetVertex(m_ptSelSec.row * COL_NUM + m_ptSelSec.col)) {

		return false;

	}

	CGameLogic gameLogic;

	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {//�ж��Ƿ�������
		//��������
		nVertex = gameLogic.GetVexPath(avPath);
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		return true;

	}


	return false;
}

void CGameControl::SetGameFlag(FLAG flag)
{
	m_flag = flag;
}

FLAG CGameControl::GetGameFlag()
{
	return m_flag;
}

BOOL CGameControl::IsWin(int nTime)
{
	CGameLogic logic;
	if (nTime <= 0) {
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	if (logic.IsBLANK(m_graph)) {//ȫ����������
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::Help(Vertex anPath[], int& nVertexNum)//����������Ӧ��·���Ͷ������
{
	//�����µ�logic���󣬱����˴洢�����ͷŵ�����
	CGameLogic logic;
	//�ж�ͼ�Ƿ�Ϊ��
	if (logic.IsBLANK(m_graph)) {
		return false;
	}
	if (logic.SearchValidPath(m_graph)) {
		nVertexNum = logic.GetVexPath(anPath);
	}
	return false;
}

void CGameControl::ResetGame()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}


void CGameControl::plusnProp()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	m_nProp++;
}
