
// ChildView.h : CChildView ��Ľӿ�
//

#pragma once
#include "Player.h"
#include "MyBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include <string>
#include<vector>
#include<math.h>
#include <iomanip>
using namespace std;

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
	int type;//0����˵���1��ʼ��Ϸ��2��ͣ��3����

	CDC m_cacheDC;   //����DC  
	CBitmap m_cacheCBitmap;//����λͼ
	CRect m_client;    //����ͻ�����С  
	CImage m_background;      //����ͼƬ 
	int m_yMapEnd;     //y�����ϵ�ͼ���յ�  
	int time_background;

	Player player;
	CRect m_planePos;    //����ɻ���λ��  
	CImage m_plane;   //�ɻ�

	vector <MyBullet> MyBullets;
	int num_bullet;
	CRect m_bulletPos;    //�����ӵ���λ��  
	CImage m_bullet;   //�ӵ�

	vector<Enemy> Enemys;
	CRect m_enemyPos;    //������˵�λ��  
	CImage m_enemy;   //����
	int time_enemy;

	vector <EnemyBullet> EnemyBullets;
	CRect m_ebulletPos;    //�����ӵ���λ��  
	CImage m_ebullet;   //�ӵ�

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

