
// Player.cpp : Player ���ʵ��
//

#include "stdafx.h"
#include"Player.h"

void Player::up(){
	p_y -= 10;
}
void Player::down(){
	p_y += 10;
}

void Player::left(){
	p_x -= 10;
}

void Player::right(){
	p_x += 10;
}

void Player::bloodmin(int x){
	p_blood -= x;
}