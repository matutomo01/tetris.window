#include"DxLib.h"


//コントローラーからの入力情報を取得するコード
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

//コントローラーの入力情報を保持する変数
int Pad_Inp;

//コントローラーの入力情報の回数をカウントする変数
int Pad_Cou[e_But::But_Total];

bool Pad_Read()
{
	//入力された情報を格納
	Pad_Inp = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//すべてのボタンで処理
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


//ブロックに関する定義
#define BLOCK_NUM_X (10)
#define BLOCK_NUM_Y (20)
#define BLOCK_EDGE	(30)

//ブロックの構造体の定義
struct BLOCK
{
	int x;		//x座標
	int y;		//y座標
	int c;		//色
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



//ブロックの定義
BLOCK block[BLOCK_NUM_X][BLOCK_NUM_Y];

//ブロックの集まりの構造体の定義
struct GATHER
{
	BLOCK block[4];		//ブロック
	int t;				//形状
	int r;				//回転
};

//ブロックの集まりのタイプをテトリミノとして定義
enum e_Type
{
	Typ_squ,	//四角形
	Typ_str,	//ストレート
	Typ_2to2,	//2to2
	Typ_mid,	//blo_mid
	Typ_end,	//blo_end
	Typ_Total
};

//ブロックの集まりの定義
GATHER move;

//次に現れるブロックの集まりの定義
GATHER next[5];

//テトリミノに関する変数代入
GATHER Move_Sub(GATHER m, int x, int y)
{
	//形状と色の代入
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

//テトリミノを初期化
void Move_Ini(int n)
{

	//色ランダムで決定
	unsigned int c =
		GetRand(e_Color::Col_Total - e_Color::Col_Red - 1)
		+ e_Color::Col_Red;

	//色代入
	for (int i = 0; i < 4; i = i++)
	{
		next[n].block[i].c = c;
	}
	

	//テトリミノをランダムで決定
	next[n].t = GetRand(e_Type::Typ_Total - 1);

	//next代入
	next[n] = Move_Sub(
		next[n],
		BLOCK_EDGE * 4,
		BLOCK_EDGE * 0);

	//moveの代入
	move = next[0];
}




//色の定義
unsigned int Color(int c)
{
	//各色の定義
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


//カウント初期化
int Cou;


//ゲーム開始時
void Game_Ini() 
{
	//ブロックの初期化
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

	//ブロックの集まりを初期化
	for (int i = 0; i < 5; i++)
	{
		Move_Ini(i);
	}

	//nextをずらす
	for (int i = 0; i < 5 - 1; i++)
	{
		next[i] = next[i + 1];
	}

}

//テトリミノの範囲の定義
enum e_Move_Lim
{
	e_範囲内,
	e_xが0未満,
	e_xが300以上,
	e_yが600以上,
};

//テトリミノの当たり判定

//壁と床の当たり判定
int Move_Lim()
{
	for (int i = 0; i < 4; i++)
	{
		//左の壁の当たり判定
		if (move.block[i].x < 0)
		{
			return e_Move_Lim::e_xが0未満;
		}

		//右の壁の当たり判定
		if (move.block[i].x >= 300)
		{
			return e_Move_Lim::e_xが300以上;
		}

		//床の当たり判定
		if (move.block[i].y >= 600)
		{
			return e_Move_Lim::e_yが600以上;
		}
	}

	return e_Move_Lim::e_範囲内;
}

//テトリミノ同士の当たり判定
bool Hit(int xs, int ys)
{
	for (int y = 0; y < BLOCK_NUM_Y; y++)
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			for (int i = 0; i < 4; i++)
			{
				//配列の範囲外の時
				if (x + xs < 0 ||
					x + xs == BLOCK_NUM_X ||
					y + ys == BLOCK_NUM_Y)
				{
					return false;
				}

				//座標にすでにテトリミノがある時
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

//moveY方向計算
bool Move_Ycal()
{
	//カウンタ計算
	Cou = Cou + 1;

	//座標更新
	move = Move_Sub(
		move,
		move.block[0].x,
		BLOCK_EDGE * (int)(Cou / 35));

	//テトリミノのy座標の範囲
	if (Move_Lim() == e_Move_Lim::e_yが600以上 ||
		Hit(0, 0) == true)
	{

		//ひとつ前の状態に戻す
		move = Move_Sub(
			move,
			move.block[0].x,
			move.block[0].y - BLOCK_EDGE);

		//テトリミノが接触した場合背景とする
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

		//カウント初期化
		Cou = 0;

		//ブロックの消去するかの判断
		bool del = true;		
		int del_row = 0;		//消去する列の数
		int del_y;				//消去する列
		for (int y = 0; y < BLOCK_NUM_Y; y++)
		{

			//初期化
			del = true;

			for (int x = 0; x < BLOCK_NUM_X; x++)
			{

				//横一列に空白がある場合
				if (block[x][y].c == e_Color::Col_No)
				{
					//消去しない
					del = false;
				}
			}

			if (del == true)
			{
				//揃っている列をカウント
				del_row = del_row + 1;

				//どこを消去するのか
				del_y = y;

				//消去する
				for (int x = 0; x < BLOCK_NUM_X; x++)
				{
					block[x][y].c = e_Color::Col_No;
				}
			}
		}

		//消去後の動き(下に詰める)
		if (del_row != 0)
		{
			for (int y = BLOCK_NUM_Y - 1; y > 0; y--)
			{

				//消去した列分ブロックを移動
				if (y == del_y)
				{

					//ブロックのそこからループ
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

		//テトリミノの初期化
		Move_Ini(5 - 1);

		//nextをずらす
		for (int i = 0; i < 5 - 1; i++)
		{
			next[i] = next[i + 1];
		}		

		return true;	//接触

	}

	return false;//非接触
}


//ゲーム終了時
bool Game_End() 
{
	for (int x = 0; x < BLOCK_NUM_X; x++)
	{
		//一番上の列にブロックが存在しているか判断
		if (block[x][0].c != e_Color::Col_No)
		{

			//ゲーム終了
			return true;
		}
	}

	return false;

}

//ゲームの処理
void Game_Cal()
{
	//ブロックの回転の処理

	//左回転
	if (Pad_Cou[e_But::But_R] == 1)
	{
		move.r = move.r + 1;
	}
	//右回転
	else if (Pad_Cou[e_But::But_L] == 1)
	{
		move.r = move.r - 1;
	}

	//テトリミノの回転範囲
	if (move.r < 0)
	{
		move.r = 3;
	}
	else if (move.r > 3)
	{
		move.r = 0;
	}

	//壁の当たり判定
	if (Hit(0, 0) == true || Move_Lim() != e_Move_Lim::e_範囲内)
	{

		//ひとつ前の状態に戻す
		move.r = move.r - 1;
	}

	//テトリミノの右方向への移動
	if(Pad_Cou[e_But::But_Rig] == 1)
	{
		//移動した時の処理
		move = Move_Sub(
			move,
			move.block[0].x + BLOCK_EDGE,
			move.block[0].y);

		//テトリミノが範囲外にいかないようにする処理
		if (Hit(+1, 0) == true ||
			Move_Lim() == e_Move_Lim::e_xが300以上) //右に進むから+1
		{

			//ひとつ前の状態に戻す
			move = Move_Sub(
				move,
				move.block[0].x - BLOCK_EDGE,
				move.block[0].y);
		}
	}

	//テトリミノの左方向への移動
	if (Pad_Cou[e_But::But_Lef] == 1)
	{
		//移動した時の処理
		move = Move_Sub(
			move,
			move.block[0].x - BLOCK_EDGE,
			move.block[0].y);

		//テトリミノが範囲外にいかないようにする処理
		if (Hit(-1, 0) == true ||
			Move_Lim() == e_Move_Lim::e_xが0未満) //左に進むから-1
		{

			//ひとつ前の状態に戻す
			move = Move_Sub(
				move,
				move.block[0].x + BLOCK_EDGE,
				move.block[0].y);
		}
	}

	//テトリミノを下方向へ移動
	bool y_fla = false;
	if (Pad_Cou[e_But::But_Dow] == 1)
	{
		while (1)
		{
			//接触するまで
			if (Move_Ycal() == true)
			{
				break;
			}
		}

	}

	//ブロックの落下
	Move_Ycal();

	//ゲームオーバーの判断
	if (Game_End() == true)
	{
		Game_Ini();
	}

}

//ゲームの表示
void Game_Draw() 
{ 
	//x座標の壁
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

	//y座標の壁
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

	

	//描画用シフト分の座標
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

	//網目とString
	for (int y = 0; y < BLOCK_NUM_Y; y++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{

			//網目
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
	
	

	//ウインドウの初期化
	ChangeWindowMode(TRUE);
	SetMainWindowText("テトリス");
	SetWindowInitPosition(0, 0);		//背景画面の初期位置
	SetGraphMode(1000, 700, 32);		//背景画面の幅と高さ
	SetBackgroundColor(0, 0, 0);		//背景画面の色
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	//変数初期化
	Game_Ini();

	//1秒間に60回ループ
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
