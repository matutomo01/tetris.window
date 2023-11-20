#include"DxLib.h"


//�R���g���[���[����̓��͏����擾����R�[�h
enum e_But
{
	But_Dow,
	But_Lef,
	But_Rig,
	But_Up,
	But_A,
	But_B,
	But_X,
	But_Y,
	But_L,
	But_R,
	But_Sel,
	But_Sta,
	But_L3,
	But_R3,
	But_Total
};

//�R���g���[���[�̓��͏���ێ�����ϐ�
int Pad_Inp;

//�R���g���[���[�̓��͏��̉񐔂��J�E���g����ϐ�
int Pad_Cou[e_But::But_Total];

bool Pad_Read()
{
	//���͂��ꂽ�����i�[
	Pad_Inp = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//���ׂẴ{�^���ŏ���
	for (int b = 0; b < e_But::But_Total; b++)
	{
		if (Pad_Inp & (1 << b))
		{
			Pad_Cou[b] = Pad_Cou[b] + 1;
		}
		else Pad_Cou[b] = 0;
	}

	return false;
}


//�u���b�N�Ɋւ����`
#define BLOCK_NUM_X (10)
#define BLOCK_NUM_Y (20)
#define BLOCK_EDGE	(30)

//�u���b�N�̍\���̂̒�`
struct BLOCK
{
	int x;		//x���W
	int y;		//y���W
	int c;		//�F
};

enum  e_Color
{
	Col_No,
	Col_Red,
	Col_Blue,
	Col_Green,
	Col_Yellow,
	Col_Total
};



//�u���b�N�̒�`
BLOCK block[BLOCK_NUM_X][BLOCK_NUM_Y];

//�u���b�N�̏W�܂�̍\���̂̒�`
struct GATHER
{
	BLOCK block[4];		//�u���b�N
	int t;				//�`��
	int r;				//��]
};

//�u���b�N�̏W�܂�̃^�C�v���e�g���~�m�Ƃ��Ē�`
enum e_Type
{
	Typ_squ,	//�l�p�`
	Typ_str,	//�X�g���[�g
	Typ_2to2,	//2to2
	Typ_mid,	//blo_mid
	Typ_end,	//blo_end
	Typ_Total
};

//�u���b�N�̏W�܂�̒�`
GATHER move;

//���Ɍ����u���b�N�̏W�܂�̒�`
GATHER next[5];

//�e�g���~�m�Ɋւ���ϐ����
GATHER Move_Sub(GATHER m, int x, int y)
{
	//�`��ƐF�̑��
	switch (m. t)
	{
	case e_Type::Typ_squ:

		m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
		m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
		m.block[2] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 0 + y,m.block[2].c };
		m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

		break;

	case e_Type::Typ_str:

		switch (m.r)
		{
		case 0:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 2 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 3 + y,m.block[3].c };

			break;

		case 1:
			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 0 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 2 + x,BLOCK_EDGE * 0 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 3 + x,BLOCK_EDGE * 0 + y,m.block[3].c };

			break;

		case 2:
			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 2 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 3 + y,m.block[3].c };

			break;

		case 3:
			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 0 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * -2 + x,BLOCK_EDGE * 0 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * -3 + x,BLOCK_EDGE * 0 + y,m.block[3].c };

			break;
		}

		break;

	case e_Type::Typ_2to2:

		switch (m.r)
		{
		case 0:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 1 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 2 + y,m.block[3].c };

			break;

		case 1:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 1 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 0 + y,m.block[3].c };

			break;

		case 2:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 1 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 2 + y,m.block[3].c };

			break;

		case 3:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 0 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

			break;
		}

		break;

	case e_Type::Typ_mid:

		switch (m.r)
		{
		case 0:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 2 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

			break;

		case 1:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

			break;

		case 2:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 2 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

			break;

		case 3:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 0 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 0 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

			break;
		}

		break;

	case e_Type::Typ_end:

		switch (m.r)
		{
		case 0:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 2 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 2 + y,m.block[3].c };

			break;

		case 1:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * -1 + x,BLOCK_EDGE * 1 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * -2 + x,BLOCK_EDGE * 1 + y,m.block[3].c };

			break;

		case 2:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 0 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 1 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 2 + y,m.block[3].c };

			break;

		case 3:

			m.block[0] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 0 + y,m.block[0].c };
			m.block[1] = { BLOCK_EDGE * 0 + x,BLOCK_EDGE * 1 + y,m.block[1].c };
			m.block[2] = { BLOCK_EDGE * 1 + x,BLOCK_EDGE * 0 + y,m.block[2].c };
			m.block[3] = { BLOCK_EDGE * 2 + x,BLOCK_EDGE * 0 + y,m.block[3].c };

			break;
		}

		break;
	}
	return m;

}

//�e�g���~�m��������
void Move_Ini(int n)
{

	//�F�����_���Ō���
	unsigned int c =
		GetRand(e_Color::Col_Total - e_Color::Col_Red - 1)
		+ e_Color::Col_Red;

	//�F���
	for (int i = 0; i < 4; i = i++)
	{
		next[n].block[i].c = c;
	}
	

	//�e�g���~�m�������_���Ō���
	next[n].t = GetRand(e_Type::Typ_Total - 1);

	//next���
	next[n] = Move_Sub(
		next[n],
		BLOCK_EDGE * 4,
		BLOCK_EDGE * 0);

	//move�̑��
	move = next[0];
}




//�F�̒�`
unsigned int Color(int c)
{
	//�e�F�̒�`
	switch (c) {
	case e_Color::Col_No://White
		c = GetColor(255, 255, 255);
		break;

	case e_Color::Col_Red://Red
		c = GetColor(255, 0, 0);
		break;

	case e_Color::Col_Blue://Blue
		c = GetColor(0, 0, 255);
		break;

	case e_Color::Col_Green://Green
		c = GetColor(0, 255, 0);
		break;

	case e_Color::Col_Yellow://Yellow
		c = GetColor(255, 255, 0);
		break;
	}

	return c;
}


//�J�E���g������
int Cou;


//�Q�[���J�n��
void Game_Ini() 
{
	//�u���b�N�̏�����
	for (int y = 0; y < BLOCK_NUM_Y; y++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			block[x][y] = {
				x * BLOCK_EDGE,
				y * BLOCK_EDGE,
				e_Color::Col_No,
			};
		}
	}

	//�u���b�N�̏W�܂��������
	for (int i = 0; i < 5; i++)
	{
		Move_Ini(i);
	}

	//next�����炷
	for (int i = 0; i < 5 - 1; i++)
	{
		next[i] = next[i + 1];
	}

}

//�e�g���~�m�͈̔͂̒�`
enum e_Move_Lim
{
	e_�͈͓�,
	e_x��0����,
	e_x��300�ȏ�,
	e_y��600�ȏ�,
};

//�e�g���~�m�̓����蔻��

//�ǂƏ��̓����蔻��
int Move_Lim()
{
	for (int i = 0; i < 4; i++)
	{
		//���̕ǂ̓����蔻��
		if (move.block[i].x < 0)
		{
			return e_Move_Lim::e_x��0����;
		}

		//�E�̕ǂ̓����蔻��
		if (move.block[i].x >= 300)
		{
			return e_Move_Lim::e_x��300�ȏ�;
		}

		//���̓����蔻��
		if (move.block[i].y >= 600)
		{
			return e_Move_Lim::e_y��600�ȏ�;
		}
	}

	return e_Move_Lim::e_�͈͓�;
}

//�e�g���~�m���m�̓����蔻��
bool Hit(int xs, int ys)
{
	for (int y = 0; y < BLOCK_NUM_Y; y++)
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			for (int i = 0; i < 4; i++)
			{
				//�z��͈̔͊O�̎�
				if (x + xs < 0 ||
					x + xs == BLOCK_NUM_X ||
					y + ys == BLOCK_NUM_Y)
				{
					return false;
				}

				//���W�ɂ��łɃe�g���~�m�����鎞
				if (move.block[i].x == block[x][y].x &&
					move.block[i].y == block[x][y].y &&
					move.block[i].c != e_Color::Col_No &&
					block[x + xs][y + ys].c != e_Color::Col_No)
				{
					return true;
				}
			}
		}

	return false;
}

//moveY�����v�Z
bool Move_Ycal()
{
	//�J�E���^�v�Z
	Cou = Cou + 1;

	//���W�X�V
	move = Move_Sub(
		move,
		move.block[0].x,
		BLOCK_EDGE * (int)(Cou / 35));

	//�e�g���~�m��y���W�͈̔�
	if (Move_Lim() == e_Move_Lim::e_y��600�ȏ� ||
		Hit(0, 0) == true)
	{

		//�ЂƂO�̏�Ԃɖ߂�
		move = Move_Sub(
			move,
			move.block[0].x,
			move.block[0].y - BLOCK_EDGE);

		//�e�g���~�m���ڐG�����ꍇ�w�i�Ƃ���
		for (int y = 0; y < BLOCK_NUM_Y; y++)
		{
			for (int x = 0; x < BLOCK_NUM_X; x++)
			{
				for (int i = 0; i < 4; i++)
				{
					if (block[x][y].x == move.block[i].x &&
						block[x][y].y == move.block[i].y)
					{
						block[x][y].c = move.block[i].c;
					}
				}
			}
		}

		//�J�E���g������
		Cou = 0;

		//�u���b�N�̏������邩�̔��f
		bool del = true;		
		int del_row = 0;		//���������̐�
		int del_y;				//���������
		for (int y = 0; y < BLOCK_NUM_Y; y++)
		{

			//������
			del = true;

			for (int x = 0; x < BLOCK_NUM_X; x++)
			{

				//�����ɋ󔒂�����ꍇ
				if (block[x][y].c == e_Color::Col_No)
				{
					//�������Ȃ�
					del = false;
				}
			}

			if (del == true)
			{
				//�����Ă������J�E���g
				del_row = del_row + 1;

				//�ǂ�����������̂�
				del_y = y;

				//��������
				for (int x = 0; x < BLOCK_NUM_X; x++)
				{
					block[x][y].c = e_Color::Col_No;
				}
			}
		}

		//������̓���(���ɋl�߂�)
		if (del_row != 0)
		{
			for (int y = BLOCK_NUM_Y - 1; y > 0; y--)
			{

				//���������񕪃u���b�N���ړ�
				if (y == del_y)
				{

					//�u���b�N�̂������烋�[�v
					for (int y = del_y; y != del_row; y--)
					{
						for (int x = 0; x < BLOCK_NUM_X; x++)
						{
							block[x][y].c = block[x][y - del_row].c;
							block[x][y - del_row].c = e_Color::Col_No;
						}
					}

					break;
				}
			}
		}

		//�e�g���~�m�̏�����
		Move_Ini(5 - 1);

		//next�����炷
		for (int i = 0; i < 5 - 1; i++)
		{
			next[i] = next[i + 1];
		}		

		return true;	//�ڐG

	}

	return false;//��ڐG
}


//�Q�[���I����
bool Game_End() 
{
	for (int x = 0; x < BLOCK_NUM_X; x++)
	{
		//��ԏ�̗�Ƀu���b�N�����݂��Ă��邩���f
		if (block[x][0].c != e_Color::Col_No)
		{

			//�Q�[���I��
			return true;
		}
	}

	return false;

}

//�Q�[���̏���
void Game_Cal()
{
	//�u���b�N�̉�]�̏���

	//����]
	if (Pad_Cou[e_But::But_R] == 1)
	{
		move.r = move.r + 1;
	}
	//�E��]
	else if (Pad_Cou[e_But::But_L] == 1)
	{
		move.r = move.r - 1;
	}

	//�e�g���~�m�̉�]�͈�
	if (move.r < 0)
	{
		move.r = 3;
	}
	else if (move.r > 3)
	{
		move.r = 0;
	}

	//�ǂ̓����蔻��
	if (Hit(0, 0) == true || Move_Lim() != e_Move_Lim::e_�͈͓�)
	{

		//�ЂƂO�̏�Ԃɖ߂�
		move.r = move.r - 1;
	}

	//�e�g���~�m�̉E�����ւ̈ړ�
	if(Pad_Cou[e_But::But_Rig] == 1)
	{
		//�ړ��������̏���
		move = Move_Sub(
			move,
			move.block[0].x + BLOCK_EDGE,
			move.block[0].y);

		//�e�g���~�m���͈͊O�ɂ����Ȃ��悤�ɂ��鏈��
		if (Hit(+1, 0) == true ||
			Move_Lim() == e_Move_Lim::e_x��300�ȏ�) //�E�ɐi�ނ���+1
		{

			//�ЂƂO�̏�Ԃɖ߂�
			move = Move_Sub(
				move,
				move.block[0].x - BLOCK_EDGE,
				move.block[0].y);
		}
	}

	//�e�g���~�m�̍������ւ̈ړ�
	if (Pad_Cou[e_But::But_Lef] == 1)
	{
		//�ړ��������̏���
		move = Move_Sub(
			move,
			move.block[0].x - BLOCK_EDGE,
			move.block[0].y);

		//�e�g���~�m���͈͊O�ɂ����Ȃ��悤�ɂ��鏈��
		if (Hit(-1, 0) == true ||
			Move_Lim() == e_Move_Lim::e_x��0����) //���ɐi�ނ���-1
		{

			//�ЂƂO�̏�Ԃɖ߂�
			move = Move_Sub(
				move,
				move.block[0].x + BLOCK_EDGE,
				move.block[0].y);
		}
	}

	//�e�g���~�m���������ֈړ�
	bool y_fla = false;
	if (Pad_Cou[e_But::But_Dow] == 1)
	{
		while (1)
		{
			//�ڐG����܂�
			if (Move_Ycal() == true)
			{
				break;
			}
		}

	}

	//�u���b�N�̗���
	Move_Ycal();

	//�Q�[���I�[�o�[�̔��f
	if (Game_End() == true)
	{
		Game_Ini();
	}

}

//�Q�[���̕\��
void Game_Draw() 
{ 
	//x���W�̕�
	for (int x = 0; x < BLOCK_NUM_X + 2; x++)
	{
		DrawBox(
			x * BLOCK_EDGE,
			BLOCK_EDGE * BLOCK_NUM_Y,
			x * BLOCK_EDGE + BLOCK_EDGE,
			BLOCK_EDGE * BLOCK_NUM_Y + BLOCK_EDGE,
			GetColor(100, 100, 100),
			TRUE);
	}

	//y���W�̕�
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < BLOCK_NUM_Y; y++)
		{
			DrawBox(
				x * (BLOCK_NUM_X + 1) * BLOCK_EDGE,
				y * BLOCK_EDGE,
				x * (BLOCK_NUM_X + 1) * BLOCK_EDGE + BLOCK_EDGE,
				y * BLOCK_EDGE + BLOCK_EDGE,
				GetColor(100, 100, 100),
				TRUE);
		}
	}

	

	//�`��p�V�t�g���̍��W
	const int shi_x = BLOCK_EDGE;

	//Block
	for (int y = 0; y < BLOCK_NUM_Y; y++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			DrawBox(
				shi_x + block[x][y].x,
				block[x][y].y,
				shi_x + block[x][y].x + BLOCK_EDGE,
				block[x][y].y + BLOCK_EDGE,
				Color(block[x][y].c), TRUE);
		}
	}
	//move
	for (int i = 0; i < 4; i++)
	{
		DrawBox(
			shi_x + move.block[i].x,
			move.block[i].y,
			shi_x +move.block[i].x + BLOCK_EDGE,
			move.block[i].y + BLOCK_EDGE,
			Color(move.block[i].c), TRUE);

		//String
		DrawFormatString(
			shi_x + move.block[i].x + 25,
			move.block[i].y + 20,
			GetColor(0, 0, 0),
			"%d", move.block[i].c);
	}

	//�Ԗڂ�String
	for (int y = 0; y < BLOCK_NUM_Y; y++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{

			//�Ԗ�
			DrawBox(
				x * BLOCK_EDGE + BLOCK_EDGE,
				y * BLOCK_EDGE,
				x * BLOCK_EDGE + 2 * BLOCK_EDGE,
				y * BLOCK_EDGE + BLOCK_EDGE,
				GetColor(0, 0, 0),
				false);

			//String
			DrawFormatString(
				shi_x + block[x][y].x + 15,
				block[x][y].y + 10,
				GetColor(0, 0, 0),
				"%d", block[x][y].c);
		}
	}

	//Next
	for (int i = 0; i < 5 - 1; i = i++)
	{
		for (int j = 0; j < 4; j++)
		{
			DrawBox(
				300 + next[i].block[j].x,
				i * 150 + next[i].block[j].y,
				300 + next[i].block[j].x + BLOCK_EDGE,
				i * 150 + next[i].block[j].y + BLOCK_EDGE,
				Color(next[i].block[j].c), TRUE);


			DrawBox(
				300 + next[i].block[j].x,
				i * 150 + next[i].block[j].y,
				300 + next[i].block[j].x + BLOCK_EDGE,
				i * 150 + next[i].block[j].y + BLOCK_EDGE,
				GetColor(0, 0, 0), false);

		}
	}
}



int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)

{
	
	

	//�E�C���h�E�̏�����
	ChangeWindowMode(TRUE);
	SetMainWindowText("�e�g���X");
	SetWindowInitPosition(0, 0);		//�w�i��ʂ̏����ʒu
	SetGraphMode(1000, 700, 32);		//�w�i��ʂ̕��ƍ���
	SetBackgroundColor(0, 0, 0);		//�w�i��ʂ̐F
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	//�ϐ�������
	Game_Ini();

	//1�b�Ԃ�60�񃋁[�v
	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0 &&
		Pad_Read() == false)
	{
		Game_Cal();
		Game_Draw();
	}

	DxLib_End();
	return 0;
}
