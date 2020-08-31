#include "pch.h"
#include "CGameLogic.h"
#include"CGraph.h"
#include"global.h"

CGameLogic::CGameLogic(void)
{
	nVertexNum = 0;//初始化
	pVertexNum = 0;
}

CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::InitMap(CGraph& m_graph)
{
	int anTemp[MAX_VERTEX_NUM];
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			anTemp[i * COL_NUM + j] = i;
		}
	}

	srand((int)time(NULL));
	//随机交换任意两个值
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//产生两个索引随机数
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//添加到顶点数组
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		m_graph.AddVertex(anTemp[i]);
	}
	//对边进行更新
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			UpdateArc(m_graph, i, j);
		}
	}

}

bool CGameLogic::IsLink(CGraph m_graph, Vertex v1, Vertex v2)//判断两点是否可连
{

	int nIndex1 = v1.row * COL_NUM + v1.col;//获取在数组中的索引
	int nIndex2 = v2.row * COL_NUM + v2.col;
	nCornerNum = 0;//判断前的初始化
	AddVertex(v1);//先将第一个点保存在数组中
	PushVertex(nIndex1);

	if (SearchPath(m_graph,nIndex1,nIndex2)) {//两点之间存在边
		//可以连通保存第二个点
		AddVertex(v2);
		return true;
	}
	//无法连通将保存点删除
	PopVertex();
	DeleteVertex();
	return false;
}

void CGameLogic::Clear(CGraph& m_graph, Vertex v1, Vertex v2)
{
	//获取索引
	int nIndex1 = v1.row * COL_NUM + v1.col;
	int nIndex2 = v2.row * COL_NUM + v2.col;
	//更新顶点
	m_graph.UpdateVertex(nIndex1, BLANK);
	m_graph.UpdateVertex(nIndex2, BLANK);
	//更新边
	UpdateArc(m_graph, v1.row, v1.col);
	UpdateArc(m_graph, v2.row, v2.col);
}



void CGameLogic::AddVertex(Vertex v)//增加节点
{
	m_avPath[pVertexNum++] = v;
}

void CGameLogic::DeleteVertex()//删除路径节点
{
	pVertexNum--;
}

void CGameLogic::PushVertex(int nV)
{
	m_anPath[nVertexNum++] = nV;
}

void CGameLogic::PopVertex()
{
	nVertexNum--;
}

bool CGameLogic::isExist(int nV)
{
	for (int i = 0; i < nVertexNum; i++) {
		if (m_anPath[i] == nV) {
			return true;
		}
	}
	return false;
}

bool CGameLogic::isCorner()
{
	if (nVertexNum <= 2)//元素个数不足直接返回
	{
		return false;
	}
	int index = nVertexNum-1;
	if ((m_anPath[index] + m_anPath[index - 2])/2 != m_anPath[index - 1]) {//利用等差数列的性质
		return true;
	}
	return false;
}

int CGameLogic::GetVexPath(Vertex avPath[])//获取连线路径
{
	//将类中的保护类型数组通过参数取出
	for (int i = 0; i < pVertexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return pVertexNum;
}

void CGameLogic::UpdateArc(CGraph& G, int nRow, int nCol)
{
	int nIndex1 = nRow * COL_NUM + nCol;//获取在一维数组中的索引
	//判断四个方向是否有边
	if (nCol > 0) {//非最左端列
		int nIndex2 = nIndex1 - 1;//左边元素的索引
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//判断图片是否相同，或者存在已被消除的元素
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {//两点同元素，或者任意一点被消
			G.AddArc(nIndex1, nIndex2);
		}
	}
	if (nCol < COL_NUM-1) {//非最右端
		int nIndex2 = nIndex1 + 1;//右边元素的索引
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//判断图片是否相同
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {
			G.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow > 0) {//非最上方
		int nIndex2 = nIndex1 - COL_NUM;//上方元素索引
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//判断图片是否相同
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {
			G.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow < ROW_NUM-1) {//非最下方
		int nIndex2 = nIndex1 + COL_NUM;//下方元素索引
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//判断图片是否相同
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {
			G.AddArc(nIndex1, nIndex2);
		}
	}
}
//利用图的深度优先遍历，判断两点之间是否存在路径，并保存路径索引
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	int nVexnum = graph.GetVexnum();
	Vertex v;
	if (nCornerNum <= 2)//保证当前拐点数不超过二
	{
		for (int nVi = 0; nVi < nVexnum; nVi++)
		{
			if (graph.GetArc(nV0, nVi) && !isExist(nVi))//存在边且未被访问
			{
				PushVertex(nVi);
				if (isCorner())
				{
					//将存入数组的倒数第二个节点存储在画线数组中(即为拐点)
					v.col = m_anPath[nVertexNum - 2] % COL_NUM;
					v.row = m_anPath[nVertexNum - 2] /COL_NUM;
					AddVertex(v);
					nCornerNum++;//拐点数加加
					if (nCornerNum == 3)//拐点过多，路径非法，回溯
					{
						//将当前节点删除
						nCornerNum--;
						DeleteVertex();
						PopVertex();
						continue;
					}
				}
				if (nVi != nV1)//未到达目标点，进入下一深度
				{
					if (SearchPath(graph, nVi, nV1))//改变起点，递归DFS
					{
						return true;
					}
					else
					{    //递归调用发现路径不通时，返回到上一层
						if (isCorner())//是否产生了拐点
						{
							DeleteVertex();
							nCornerNum--;
						}
						PopVertex();
						continue;
					}
				}
				else
				{   //寻找路径找到相应的目标点时，开始向上层返回
					if (graph.GetVertex(m_anPath[0]) == graph.GetVertex(nVi))//判断两点是否为同一个元素
					{
						if (nVertexNum > 2)//非两点相邻的情况
						{
							for (int i = 1; i <= nVertexNum - 2; i++)
							{
								if (graph.GetVertex(m_anPath[i]) != -1)//路径中存在非空点
								{
									if (isCorner())//构成拐点
									{
										DeleteVertex();
										nCornerNum--;
									}
									PopVertex();
									return false;//此时无法进行连通
								}
							}
							return true;
						}
						//相邻两点直接返回为真
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CGameLogic::IsBLANK(CGraph& g)//是否全部为空
{
	int nVertex = g.GetVexnum();
	for (int i = 0; i < nVertex; i++) {
		if (g.GetVertex(i) != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& g)
{
	Vertex v1, v2;
	for(int i=0;i<g.GetVexnum();i++)
		for (int j = i + 1; j < g.GetVexnum(); j++) {
			if ((g.GetVertex(i) == g.GetVertex(j)) && (g.GetVertex(i) != BLANK)) {//两点为同一种图片
				v1.col = i % COL_NUM;
				v1.row =i / COL_NUM;
				v2.col = j % COL_NUM;
				v2.row = j / COL_NUM;
				nCornerNum = 0;
				AddVertex(v1);
				PushVertex(i);
				if (SearchPath(g, i, j)) {//两点可以连通
					AddVertex(v2);
					return true;
				}
				PopVertex();
				DeleteVertex();
			}
		}

	return false;
}

void CGameLogic::ResetGraph(CGraph& g)
{
	int anTemp[MAX_VERTEX_NUM];
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
		  anTemp[i * COL_NUM + j] = g.GetVertex(i * COL_NUM + j);//从图中保存到数组中
		}
	}

	srand((int)time(NULL));
	//随机交换任意两个值
	for (int i = 0; i < MAX_VERTEX_NUM; i++)//随机交换两点值
	{
		//产生两个索引随机数
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//添加到顶点数组
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		g.UpdateVertex(i,anTemp[i]);
	}
	//对边进行更新
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}
