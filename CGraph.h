#pragma once

#include"global.h"
class CGraph   //图的存储结构类
{
public:
	CGraph(void);
	~CGraph(void);

	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    
	typedef int Vertices[MAX_VERTEX_NUM];
	int AddVertex(int info);//添加顶点（数组中存储编号）
	void AddArc(int nIndex1,int  nIndex2);//添加边
	void InitGraph();
	int GetVertex(int nIndex);//获取一维数组中的值
	bool GetArc(int nIndex1, int nIndex2);//获取图中的某条边
	void UpdateVertex(int nIndex,int info);//对顶点数组进行更新
	int GetVexnum();
	void ClearGraph();//通过后清空图
	
protected:
	Vertices m_Vertices;   //顶点数组
	int m_nVertexNum;      //顶点个数
	AdjMatrix m_AdjMatrix;  //存储边的二维数组
	int m_nArcNum;        //边的数量
	

};

