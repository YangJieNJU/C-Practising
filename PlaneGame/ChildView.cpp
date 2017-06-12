
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��ʱ���������ú�Ƚ����  
#define TIMER_PAINT 1  
#define TIMER_HEROMOVE 2  

// CChildView

CChildView::CChildView()
{
	type = 0;
	//���õ�ͼ��ʼ������˿�ʼ��ʾ  
	m_yMapEnd = 0;
	time_background = 0;
	num_bullet = 0;
	time_enemy = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	//���ر���  
	m_background.Load(L"Background.jpg");

	//���طɻ�ͼƬ  
	m_plane.Load(L"Plane.png");
	//TransparentPNG(&m_plane);

	//�����ӵ�ͼƬ
	m_bullet.Load(L"Bullet.png");

	//���ص���ͼƬ
	m_enemy.Load(L"Enemy.png");

	//���ص����ӵ�ͼƬ
	m_ebullet.Load(L"Bullet2.png");

	return TRUE;
}

void CChildView::OnPaint() 
{	
	//��ʱϵͳ
	time_background++;
	time_enemy++;

	// TODO:  �ڴ˴������Ϣ����������
	CDC *cDC = this->GetDC();   //��õ�ǰ���ڵ�DC     
	GetClientRect(&m_client);   //��ô��ڵĳߴ�  
	//��������DC  
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC, m_client.Width(), m_client.Height());
	m_cacheDC.SelectObject(&m_cacheCBitmap);

	//������
	if (m_yMapEnd < 7153)
		//m_background.Draw(m_cacheDC, 0, 100, 1024, 900, 0, 0, 1024, 900);
		m_background.Draw(m_cacheDC, 0, 0, 1024, 900, 0, 7153 - m_yMapEnd, 1024, 900);
	else{
		m_background.Draw(m_cacheDC, 0, 0, 1024, m_yMapEnd - 7153, 0, 15206 - m_yMapEnd, 1024, m_yMapEnd - 7153);
		m_background.Draw(m_cacheDC, 0, m_yMapEnd - 7153, 1024, 8053 - m_yMapEnd, 0, 0, 1024, 8053 - m_yMapEnd);
	}

	if (type == 1){
		//���ɻ� 
		m_planePos.left = player.p_x;
		m_planePos.right = player.p_x + player.p_width;
		m_planePos.top = player.p_y;
		m_planePos.bottom = player.p_y + player.p_height;
		m_plane.Draw(m_cacheDC, m_planePos);

		//���ӵ�
		for (vector<MyBullet>::iterator t = MyBullets.begin(); t != MyBullets.end();){
			m_bulletPos.left = t->b_x;
			m_bulletPos.right = t->b_x + t->b_width;
			m_bulletPos.top = t->b_y;
			m_bulletPos.bottom = t->b_y + t->b_height;
			m_bullet.Draw(m_cacheDC, m_bulletPos);

			++t;
		}

		//������
		for (vector<Enemy>::iterator t = Enemys.begin(); t != Enemys.end();){
			m_enemyPos.left = t->e_x;
			m_enemyPos.right = t->e_x + t->e_width;
			m_enemyPos.top = t->e_y;
			m_enemyPos.bottom = t->e_y + t->e_height;
			m_enemy.Draw(m_cacheDC, m_enemyPos);

			++t;
		}

		//�������ӵ�
		for (vector<EnemyBullet>::iterator t = EnemyBullets.begin(); t != EnemyBullets.end();){
			m_ebulletPos.left = t->b_x;
			m_ebulletPos.right = t->b_x + t->b_width;
			m_ebulletPos.top = t->b_y;
			m_ebulletPos.bottom = t->b_y + t->b_height;
			m_ebullet.Draw(m_cacheDC, m_ebulletPos);

			++t;
		}

		//д��
		//CDC *pDC = GetDC();
		m_cacheDC.SetBkMode(TRANSPARENT);
		m_cacheDC.SetTextColor(RGB(255, 255, 255));
		CString first("Plane War");
		m_cacheDC.TextOutW(20, 50, first);
		CString a("�������ֵ��");
		CString b;
		b.Format(_T("%d"), player.p_blood);
		CString second = a + b;
		m_cacheDC.TextOutW(20, 80, second);
		CString c("���������Ŀ��");
		CString d;
		d.Format(_T("%d"), player.killenemy);
		CString thrid = c + d;
		m_cacheDC.TextOutW(20, 110, thrid);
		CString e("����ͻ�Ʒ�����Ŀ��");
		CString f;
		f.Format(_T("%d"), player.enemywin);
		CString forth = e + f;
		m_cacheDC.TextOutW(20, 140, forth);

		//�ӵ������߼�
		for (vector<MyBullet>::iterator t = MyBullets.begin(); t != MyBullets.end();){
			t->MoveUp();
			int y = t->b_y;
			if (y < 1){
				t = MyBullets.erase(t);
			}
			else
				++t;
		}

		//���˼������ӵ������߼�
		for (vector<EnemyBullet>::iterator t = EnemyBullets.begin(); t != EnemyBullets.end();){
			t->MoveDown();
			int y = t->b_y;
			if (y < 1){
				t = EnemyBullets.erase(t);
			}
			else
				++t;
		}
		if (time_enemy % 10 == 0){
			for (vector<Enemy>::iterator t1 = Enemys.begin(); t1 != Enemys.end();){
				if (time_enemy == 100){
					int ifbullet = rand() % 3;
					if (ifbullet == 0){
						EnemyBullet b(t1->e_x + t1->e_width / 2 - 20, t1->e_y + 40);
						EnemyBullets.push_back(b);
					}
				}
				if (time_enemy == 100){
					int nextmove = rand() % 3 + 1;
					if (nextmove == 1)
						t1->ToLeft();
					else if (nextmove == 2)
						t1->ToRight();
					else if (nextmove > 2)
						t1->ToDown();
				}
				else
					t1->ToDown();
				t1++;

			}
			if (time_enemy == 100){
				int enemy_x = rand() % (1000) - 30;
				int enemy_y = 40;
				Enemy e(enemy_x, enemy_y);
				Enemys.push_back(e);
				time_enemy = 0;
			}
		}


		//�������ӵ��򵽵з��ӵ�
		for (vector<MyBullet>::iterator t = MyBullets.begin(); t != MyBullets.end();){
			int flag = 0;
			for (vector<EnemyBullet>::iterator t1 = EnemyBullets.begin(); t1 != EnemyBullets.end();){
				if ((abs(t1->b_x - t->b_x) <= t1->b_width / 2) && (abs(t1->b_y - t->b_y) <= t1->b_height)){
					flag = 1;
					t1 = EnemyBullets.erase(t1);
					break;
				}
				else
					++t1;
			}
			if (flag == 1)
				t = MyBullets.erase(t);
			else
				++t;
		}

		//�������ӵ��򵽵���
		for (vector<Enemy>::iterator t = Enemys.begin(); t != Enemys.end();){
			int flag = 0;
			if (t->e_y >= 860){
				flag = 1;
				player.bloodmin(10);
				player.enemywin++;
			}
			else{
				for (vector<MyBullet>::iterator t1 = MyBullets.begin(); t1 != MyBullets.end();){
					if ((abs(t1->b_x - t->e_x) <= t1->b_width) && (abs(t1->b_y - t->e_height) <= t->e_height)){
						flag = 1;
						t1 = MyBullets.erase(t1);
						player.killenemy++;
						player.bloodmin(-10);

						CRect m_boomPos;    //������Ч��λ��  
						CImage m_boom;   //��Ч
						m_boom.Load(L"boom.png");
						m_boomPos.left = t->e_x;
						m_boomPos.right = t->e_x + t->e_width;
						m_boomPos.top = t->e_y;
						m_boomPos.bottom = t->e_y + t->e_height;
						m_boom.Draw(m_cacheDC, m_boomPos);
						break;
					}
					else
						++t1;
				}
			}
			if (flag == 1)
				t = Enemys.erase(t);
			else
				++t;
		}

		//��������ӵ�����
		for (vector<EnemyBullet>::iterator t1 = EnemyBullets.begin(); t1 != EnemyBullets.end();){
			if ((abs(t1->b_x - player.p_x) <= t1->b_width) && (abs(t1->b_y - player.p_y) <= t1->b_height)){
				t1 = EnemyBullets.erase(t1);
				player.bloodmin(10);
				break;
			}
			else
				++t1;
		}

		//����л�ײ����
		for (vector<Enemy>::iterator t1 = Enemys.begin(); t1 != Enemys.end();){
			if ((abs(t1->e_x - player.p_x) <= t1->e_width) && (abs(t1->e_y - player.p_y) <= t1->e_height)){
				t1 = Enemys.erase(t1);
				player.bloodmin(30);
				player.killenemy++;
				break;
			}
			else
				++t1;
		}
	}
	
	//���������߼�
	if (time_background == 5){
		if (m_yMapEnd < 8053)
			m_yMapEnd += 10;
		else
			m_yMapEnd = 0;
		time_background = 0;
	}

	if (player.p_blood <= 0)
		type = 3;

	if (type == 0){
		CRect m_startPos;    //������Ч��λ��  
		CImage m_start;   //��Ч
		m_start.Load(L"start.png");
		m_startPos.left = 250;
		m_startPos.right = 250 + 440;
		m_startPos.top = 200;
		m_startPos.bottom = 200 + 106;
		m_start.Draw(m_cacheDC, m_startPos);

		m_cacheDC.SetBkMode(TRANSPARENT);
		m_cacheDC.SetTextColor(RGB(255, 255, 255));
		CString first("W S A D �������������ƶ���K �����ӵ�");
		m_cacheDC.TextOutW(330, 330, first);
		CString second("�� K ������Ϸ");
		m_cacheDC.TextOutW(440, 370, second);

		CString third("����������");
		m_cacheDC.TextOutW(450, 420, third);
		CRect m_donPos;    //������Ч��λ��  
		CImage m_don;   //��Ч
		m_don.Load(L"donate.jpg");
		m_donPos.left = 350;
		m_donPos.right = 350 + 300;
		m_donPos.top = 450;
		m_donPos.bottom = 450 + 300;
		m_don.Draw(m_cacheDC, m_donPos);
	}

	if (type == 3){
		m_cacheDC.SetBkMode(TRANSPARENT);
		m_cacheDC.SetTextColor(RGB(255, 255, 255));
		CString first("Plane War");
		m_cacheDC.TextOutW(20, 50, first);
		CString a("�������ֵ��");
		CString b;
		b.Format(_T("%d"), player.p_blood);
		CString second = a + b;
		m_cacheDC.TextOutW(20, 80, second);
		CString c("���������Ŀ��");
		CString d;
		d.Format(_T("%d"), player.killenemy);
		CString thrid = c + d;
		m_cacheDC.TextOutW(20, 110, thrid);
		CString e("����ͻ�Ʒ�����Ŀ��");
		CString f;
		f.Format(_T("%d"), player.enemywin);
		CString forth = e + f;
		m_cacheDC.TextOutW(20, 140, forth);
		CString fifth("�� K ���¿�ʼ��Ϸ");
		m_cacheDC.TextOutW(20, 170, fifth);
		CRect m_overPos;    //������Ч��λ��  
		CImage m_over;   //��Ч
		m_over.Load(L"gameover.png");
		m_overPos.left = 250;
		m_overPos.right = 250 + 515;
		m_overPos.top = 400;
		m_overPos.bottom = 400 + 99;
		m_over.Draw(m_cacheDC, m_overPos);
	}



	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);
	//�ڻ�����ͼ��,ʹ��������Ч  
	ValidateRect(&m_client);
	//�ͷŻ���DC  
	m_cacheDC.DeleteDC();
	//�ͷŶ���  
	m_cacheCBitmap.DeleteObject();
	//�ͷŴ���DC  
	ReleaseDC(cDC);
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}

//������Ӧ����  
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//nChar��ʾ���µļ�ֵ  
	switch (nChar)
	{
	case 'd': 
	case 'D':
		if (m_planePos.right < 1035){
			m_planePos.left += 10;    //�����ƶ�10�����صĵ�λ  
			m_planePos.right += 10;   //��ߺ��ұ߶�Ҫ�ƶ�Ŷ
			player.right();
		}
		break;
	case 'a':
	case 'A':
		if (m_planePos.left > -30){
			m_planePos.left -= 10;
			m_planePos.right -= 10;
			player.left();
		}
		break;
	case 'w':
	case 'W':
		if (m_planePos.top > 40){
			m_planePos.top -= 10;
			m_planePos.bottom -= 10;
			player.up();
		}
		break;
	case 's':
	case 'S':
		if (m_planePos.bottom < 865){
			m_planePos.top += 10;
			m_planePos.bottom += 10;
			player.down();
		}
		break;
	case 'k':
	case 'K':
		if (type == 1){
			num_bullet++;
			MyBullet b((m_planePos.left + m_planePos.right) / 2 - 20, m_planePos.top - 40);
			MyBullets.push_back(b);
		}
		else if (type == 0){
			type = 1;
			num_bullet = 0;
			time_enemy = 0;
		}
		else if (type == 3){
			num_bullet = 0;
			time_enemy = 0;
			type = 1;
			player.p_x = 480;
			player.p_y = 600;
			player.p_width = 137;
			player.p_height = 137;
			player.p_blood = 100;
			player.killenemy = 0;
			player.enemywin = 0;
			MyBullets.clear();
			Enemys.clear();
			EnemyBullets.clear();
		}
		break;
	}
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CWnd::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case TIMER_PAINT:OnPaint(); break;  //�����ػ涨ʱ������ִ��OnPaint����  
	case TIMER_HEROMOVE:               //���������ƶ��Ķ�ʱ��  
		m_planePos.left += 10;
		m_planePos.right += 10;
		break;
	}
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������  

	//����һ��10�������һ����Ϣ�Ķ�ʱ��  
	SetTimer(TIMER_PAINT, 10, NULL);

	return 0;
}
