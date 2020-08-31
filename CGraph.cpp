#include "pch.h"
#include "CGraph.h"

CGraph::CGraph(void)
{
	InitGraph();
}

CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	//初始化函数
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;   //表示无顶点
	}
	for(int i = 0; i < MAX_VERTEX_NUM; i++)
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;   //表示无边
		}
	m_nVertexNum = 0;
	m_nArcNum = 0;
		
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

bool CGraph::GetArc(int nIndex1, int nIndex2)
{
	return m_AdjMatrix[nIndex1][nIndex2];
}

void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

int CGraph::GetVexnum()
{
	return  m_nVertexNum;
}

void CGraph::ClearGraph()
{
	InitGraph();
}

int  CGraph::AddVertex(int info)
{ 
	if (m_nVertexNum >= MAX_VERTEX_NUM) {
		return m_nVertexNum;
	}
	m_Vertices[m_nVertexNum++] = info;
	return m_nVertexNum;
}

void CGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = true;
	m_AdjMatrix[nIndex2][nIndex1] = true;
}
