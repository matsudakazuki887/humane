# include <Siv3D.hpp>
# include <stdio.h>

int calendar_jg(int year, int month);
bool uru(int year, int month);
int mousejg(int month, int h);
int calendar_x1 = 0, calendar_y1 = 80, calendar_x2 = 714, calendar_y2 = 450;
void Main()
{
	// 背景色を ColorF{ 0.3, 0.6, 1.0 } に設定
	Scene::SetBackground(Palette::White);
	int i = 0, j = 1, h = 0;
	String text = U"日月火水木金土";
	const Date date = Date::Today();
	h = calendar_jg(date.year, date.month);
	int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int m = date.month, y = date.year;
	const Texture texture{ U"example/133540.png" };
	const Font font13{ 13 }, fontBold{ 13, Typeface::Bold }, fontBold25{ 25, Typeface::Bold }, fontBold17{ 17, Typeface::Bold }, fontBold18{ 18, Typeface::Bold };
	Window::Resize(714, 600);

	while (System::Update())
	{
		ClearPrint();

		Print << Cursor::Pos(); // 現在のマウスカーソル座標を表示

		Print << U"X: " << Cursor::Pos().x; // X 座標だけを表示

		Print << U"Y: " << Cursor::Pos().y; // Y 座標だけを表示
		Print << h; // Y 座標だけを表示
		Rect{ 0, 0, calendar_x2, calendar_y1 }.draw(ColorF{ 0, 0, 0, 0.05 });
		fontBold25(m, U"月").draw(300, 20, Palette::Black);
		fontBold18(y).draw(370, 25, Palette::Silver);
		Rect{ calendar_x1 - 1, calendar_y1, calendar_x2 + 2, calendar_y2 } //カレンダー出力　座標(x1,y1)を左上の基準にして幅x2,高さy2の長方形をかく //適当にやってるのは後で直す
		.drawFrame(1, 0, Palette::Black);
		for (i = 1; i <= 6; i++)
		{
			Line{ calendar_x2 / 7 * i + calendar_x1, calendar_y1 + 1, calendar_x2 / 7 * i + calendar_x1 ,calendar_y1 + calendar_y2 - 1 }.draw(0.5, Palette::Silver); //縦の線
		}
		for (i = 1; i <= 5; i++)
		{
			Line{ calendar_x1, calendar_y2 / 6 * i + calendar_y1 , calendar_x2 + calendar_x1 ,calendar_y2 / 6 * i + calendar_y1 }.draw(0.5, Palette::Silver); //横の線
		}
		if (uru(y, m))month[2]++;
		for (i = 1; i <= month[m]; i++)
		{
			fontBold(i).draw(calendar_x2 / 7 * ((i + h - 1) % 7) + calendar_x1 + 4, calendar_y2 / 6 * j + calendar_y1 + 2, Palette::Black); //日付
			if ((i + h) % 7 == 0)j++;
		}
		j = 0;
		if (uru(y, m))month[2]--;
		for (i = 1; i <= 7; i++)
		{
			if (i == 1) fontBold(text[i - 1]).draw(calendar_x2 / 7 * i + calendar_x1 - 57, calendar_y1 - 20, Palette::Red); // 曜日表示
			else if (i == 7) fontBold(text[i - 1]).draw(calendar_x2 / 7 * i + calendar_x1 - 57, calendar_y1 - 20, Palette::Blue);
			else fontBold(text[i - 1]).draw(calendar_x2 / 7 * i + calendar_x1 - 57, calendar_y1 - 20, Palette::Black);
		}
		if (MouseL.down())
		{
			mousejg(month[m], h);
		}
		if (KeyLeft.down())
		{
			m--;
			if (m == 0)
			{
				m = 12;
				y--;
			}
			h = calendar_jg(y, m);
		}
		if (KeyRight.down())
		{
			m++;
			if (m == 13)
			{
				m = 1;
				y++;
			}
			h = calendar_jg(y, m);
		}
		/*Rect{41, 48, 97, 13}.draw(Palette::Skyblue);
		font10(U"キャベツ").draw(41, 45, Palette::White);*/
	}
}

int calendar_jg(int year, int month) {

	/*要求通りの変数を確保 よく分からない変数は使っていません*/
	if (month == 1)
	{
		month = 13;
		year--;
	}
	if (month == 2)
	{
		month = 14;
		year--;
	}
	int h = 0;

	/*月初の曜日Kを求める*/
	h = (year + (year / 4) - (year / 100) + (year / 400) + ((month * 13 + 8) / 5) + 1) % 7;

	return h;
}
bool uru(int year, int month)
{
	if (month != 2)
	{
		return false;
	}
	else
	{
		/*閏年(month)の計算*/
		if (year % 4) {
		}
		else if (year % 100) {
			return true;
		}
		else if (year % 400) {
			return false;
		}
		else {
			return true;
		}
	}
}
int mousejg(int month,int h)
{
	int i = 0,j=0,x,y;
	x = Cursor::Pos().x;
	y = Cursor::Pos().y;
	for (i = 1; i <= month; i++)
	{
		if (x>calendar_x1+(calendar_x2/7)* ((i + h - 1) % 7) && x<=calendar_x1+(calendar_x2/7)* ((i + h - 1) % 7+1) && y>calendar_y1+ (calendar_y2/6)*j && y<= calendar_y1 + (calendar_y2 / 6) * (j+1))
		{
			return i;
		}
		if ((i + h) % 7 == 0)j++;
	}
}
