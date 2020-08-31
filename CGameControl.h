#pragma once
#include"global.h"
#include"CGraph.h"
class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);
	int m_nGrade;//����
	int m_nProp;//��������
	int GetGrade();//��ȡ����
	bool  PropLink();//ʹ�õ���
	void PlusGrade(int time);//���Ӻ�ӷ�
	void MinusGrade();//ʹ����ʾ�����
	int  GetnProp();//��ȡ��ǰ������
	virtual void StartGame() = 0;//����Ϊ���麯��
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[], int& nVertex);//�������ӣ������ض�Ӧ�ĵ����
	void SetGameFlag(FLAG flag);//������Ϸ��־
	FLAG GetGameFlag();//��ȡ��Ϸ��־
	//������ʵ�ֵ����к���
	virtual BOOL IsWin(int nTime);//�ж�ʤ��
    virtual bool Help(Vertex anPath[],int& nVertexNum);//��ʾ����
	virtual void ResetGame();//����
protected:
	CGraph m_graph;      //�洢��Ϸ��ͼ
	Vertex m_ptSelFirst;   //ѡ�еĵ�һ����
	Vertex m_ptSelSec;     //ѡ�еĵڶ�����

private:
	FLAG m_flag;
public:
	void plusnProp();
};
