#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	void InitMap(CGraph& m_graph);
	bool IsLink(CGraph m_graph, Vertex v1, Vertex v2);
	void Clear(CGraph& m_graph, Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[]);
	void UpdateArc(CGraph& G, int nRow, int nCol);//更新地图边
	bool SearchPath(CGraph& g, int v0, int v1);//利用图中的深度优先遍历判断是否可连
	bool IsBLANK(CGraph& g);//判断是否都被消除
	bool SearchValidPath(CGraph& g);//查找可连通的两点
	void ResetGraph(CGraph& g);//重排功能
protected:

	Vertex m_avPath[MAX_VERTEX_NUM];    //保存两点间路径
	int pVertexNum;                     //路径中的顶点个数
	int nVertexNum;                    //顶点个数
	int  m_anPath[MAX_VERTEX_NUM];   //保存连通路径顶点索引
	int nCornerNum;                  //记录拐点数
	void AddVertex(Vertex v);
	void DeleteVertex();
	void PushVertex(int nV);//添加一个路径顶点nV
	void PopVertex();//取出一个顶点
	bool isExist(int nV);//判断是否被访问
	bool isCorner();//判断连续三点之间是否存在拐点，利用直线点索引成等差数列的特性
};

