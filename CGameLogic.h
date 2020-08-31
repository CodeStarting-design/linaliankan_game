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
	void UpdateArc(CGraph& G, int nRow, int nCol);//���µ�ͼ��
	bool SearchPath(CGraph& g, int v0, int v1);//����ͼ�е�������ȱ����ж��Ƿ����
	bool IsBLANK(CGraph& g);//�ж��Ƿ񶼱�����
	bool SearchValidPath(CGraph& g);//���ҿ���ͨ������
	void ResetGraph(CGraph& g);//���Ź���
protected:

	Vertex m_avPath[MAX_VERTEX_NUM];    //���������·��
	int pVertexNum;                     //·���еĶ������
	int nVertexNum;                    //�������
	int  m_anPath[MAX_VERTEX_NUM];   //������ͨ·����������
	int nCornerNum;                  //��¼�յ���
	void AddVertex(Vertex v);
	void DeleteVertex();
	void PushVertex(int nV);//���һ��·������nV
	void PopVertex();//ȡ��һ������
	bool isExist(int nV);//�ж��Ƿ񱻷���
	bool isCorner();//�ж���������֮���Ƿ���ڹյ㣬����ֱ�ߵ������ɵȲ����е�����
};

