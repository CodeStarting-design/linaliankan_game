#pragma once

#include"global.h"
class CGraph   //ͼ�Ĵ洢�ṹ��
{
public:
	CGraph(void);
	~CGraph(void);

	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    
	typedef int Vertices[MAX_VERTEX_NUM];
	int AddVertex(int info);//��Ӷ��㣨�����д洢��ţ�
	void AddArc(int nIndex1,int  nIndex2);//��ӱ�
	void InitGraph();
	int GetVertex(int nIndex);//��ȡһά�����е�ֵ
	bool GetArc(int nIndex1, int nIndex2);//��ȡͼ�е�ĳ����
	void UpdateVertex(int nIndex,int info);//�Զ���������и���
	int GetVexnum();
	void ClearGraph();//ͨ�������ͼ
	
protected:
	Vertices m_Vertices;   //��������
	int m_nVertexNum;      //�������
	AdjMatrix m_AdjMatrix;  //�洢�ߵĶ�ά����
	int m_nArcNum;        //�ߵ�����
	

};

