
// MyBullet.h : �ҵ��ӵ���һЩ����
//
#pragma once

class MyBullet{
public:
	int b_x;
	int b_y;
	int b_width;
	int b_height;

public:
	MyBullet(int x, int y){
		b_x = x;
		b_y = y - 10;
		b_width = 50;
		b_height = 50;
	}
	void MoveUp();
};
