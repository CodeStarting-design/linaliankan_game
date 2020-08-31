#include "pch.h"
#include "CGameLogic.h"
#include"CGraph.h"
#include"global.h"

CGameLogic::CGameLogic(void)
{
	nVertexNum = 0;//��ʼ��
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
	//���������������ֵ
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//�����������������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//��ӵ���������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		m_graph.AddVertex(anTemp[i]);
	}
	//�Ա߽��и���
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			UpdateArc(m_graph, i, j);
		}
	}

}

bool CGameLogic::IsLink(CGraph m_graph, Vertex v1, Vertex v2)//�ж������Ƿ����
{

	int nIndex1 = v1.row * COL_NUM + v1.col;//��ȡ�������е�����
	int nIndex2 = v2.row * COL_NUM + v2.col;
	nCornerNum = 0;//�ж�ǰ�ĳ�ʼ��
	AddVertex(v1);//�Ƚ���һ���㱣����������
	PushVertex(nIndex1);

	if (SearchPath(m_graph,nIndex1,nIndex2)) {//����֮����ڱ�
		//������ͨ����ڶ�����
		AddVertex(v2);
		return true;
	}
	//�޷���ͨ�������ɾ��
	PopVertex();
	DeleteVertex();
	return false;
}

void CGameLogic::Clear(CGraph& m_graph, Vertex v1, Vertex v2)
{
	//��ȡ����
	int nIndex1 = v1.row * COL_NUM + v1.col;
	int nIndex2 = v2.row * COL_NUM + v2.col;
	//���¶���
	m_graph.UpdateVertex(nIndex1, BLANK);
	m_graph.UpdateVertex(nIndex2, BLANK);
	//���±�
	UpdateArc(m_graph, v1.row, v1.col);
	UpdateArc(m_graph, v2.row, v2.col);
}



void CGameLogic::AddVertex(Vertex v)//���ӽڵ�
{
	m_avPath[pVertexNum++] = v;
}

void CGameLogic::DeleteVertex()//ɾ��·���ڵ�
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
	if (nVertexNum <= 2)//Ԫ�ظ�������ֱ�ӷ���
	{
		return false;
	}
	int index = nVertexNum-1;
	if ((m_anPath[index] + m_anPath[index - 2])/2 != m_anPath[index - 1]) {//���õȲ����е�����
		return true;
	}
	return false;
}

int CGameLogic::GetVexPath(Vertex avPath[])//��ȡ����·��
{
	//�����еı�����������ͨ������ȡ��
	for (int i = 0; i < pVertexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return pVertexNum;
}

void CGameLogic::UpdateArc(CGraph& G, int nRow, int nCol)
{
	int nIndex1 = nRow * COL_NUM + nCol;//��ȡ��һά�����е�����
	//�ж��ĸ������Ƿ��б�
	if (nCol > 0) {//���������
		int nIndex2 = nIndex1 - 1;//���Ԫ�ص�����
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//�ж�ͼƬ�Ƿ���ͬ�����ߴ����ѱ�������Ԫ��
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {//����ͬԪ�أ���������һ�㱻��
			G.AddArc(nIndex1, nIndex2);
		}
	}
	if (nCol < COL_NUM-1) {//�����Ҷ�
		int nIndex2 = nIndex1 + 1;//�ұ�Ԫ�ص�����
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//�ж�ͼƬ�Ƿ���ͬ
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {
			G.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow > 0) {//�����Ϸ�
		int nIndex2 = nIndex1 - COL_NUM;//�Ϸ�Ԫ������
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//�ж�ͼƬ�Ƿ���ͬ
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {
			G.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow < ROW_NUM-1) {//�����·�
		int nIndex2 = nIndex1 + COL_NUM;//�·�Ԫ������
		int V1Info = G.GetVertex(nIndex1);
		int V2Info = G.GetVertex(nIndex2);
		//�ж�ͼƬ�Ƿ���ͬ
		if (V1Info == V2Info || V1Info == BLANK || V2Info == BLANK) {
			G.AddArc(nIndex1, nIndex2);
		}
	}
}
//����ͼ��������ȱ������ж�����֮���Ƿ����·����������·������
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	int nVexnum = graph.GetVexnum();
	Vertex v;
	if (nCornerNum <= 2)//��֤��ǰ�յ�����������
	{
		for (int nVi = 0; nVi < nVexnum; nVi++)
		{
			if (graph.GetArc(nV0, nVi) && !isExist(nVi))//���ڱ���δ������
			{
				PushVertex(nVi);
				if (isCorner())
				{
					//����������ĵ����ڶ����ڵ�洢�ڻ���������(��Ϊ�յ�)
					v.col = m_anPath[nVertexNum - 2] % COL_NUM;
					v.row = m_anPath[nVertexNum - 2] /COL_NUM;
					AddVertex(v);
					nCornerNum++;//�յ����Ӽ�
					if (nCornerNum == 3)//�յ���࣬·���Ƿ�������
					{
						//����ǰ�ڵ�ɾ��
						nCornerNum--;
						DeleteVertex();
						PopVertex();
						continue;
					}
				}
				if (nVi != nV1)//δ����Ŀ��㣬������һ���
				{
					if (SearchPath(graph, nVi, nV1))//�ı���㣬�ݹ�DFS
					{
						return true;
					}
					else
					{    //�ݹ���÷���·����ͨʱ�����ص���һ��
						if (isCorner())//�Ƿ�����˹յ�
						{
							DeleteVertex();
							nCornerNum--;
						}
						PopVertex();
						continue;
					}
				}
				else
				{   //Ѱ��·���ҵ���Ӧ��Ŀ���ʱ����ʼ���ϲ㷵��
					if (graph.GetVertex(m_anPath[0]) == graph.GetVertex(nVi))//�ж������Ƿ�Ϊͬһ��Ԫ��
					{
						if (nVertexNum > 2)//���������ڵ����
						{
							for (int i = 1; i <= nVertexNum - 2; i++)
							{
								if (graph.GetVertex(m_anPath[i]) != -1)//·���д��ڷǿյ�
								{
									if (isCorner())//���ɹյ�
									{
										DeleteVertex();
										nCornerNum--;
									}
									PopVertex();
									return false;//��ʱ�޷�������ͨ
								}
							}
							return true;
						}
						//��������ֱ�ӷ���Ϊ��
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CGameLogic::IsBLANK(CGraph& g)//�Ƿ�ȫ��Ϊ��
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
			if ((g.GetVertex(i) == g.GetVertex(j)) && (g.GetVertex(i) != BLANK)) {//����Ϊͬһ��ͼƬ
				v1.col = i % COL_NUM;
				v1.row =i / COL_NUM;
				v2.col = j % COL_NUM;
				v2.row = j / COL_NUM;
				nCornerNum = 0;
				AddVertex(v1);
				PushVertex(i);
				if (SearchPath(g, i, j)) {//���������ͨ
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
		  anTemp[i * COL_NUM + j] = g.GetVertex(i * COL_NUM + j);//��ͼ�б��浽������
		}
	}

	srand((int)time(NULL));
	//���������������ֵ
	for (int i = 0; i < MAX_VERTEX_NUM; i++)//�����������ֵ
	{
		//�����������������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//��ӵ���������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		g.UpdateVertex(i,anTemp[i]);
	}
	//�Ա߽��и���
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}
