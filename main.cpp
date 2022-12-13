# include <Siv3D.hpp>
# include <stdio.h>
# include <string.h>
using namespace std;
int calendar_jg(int year, int month);
bool uru(int year, int month);
int mousejg(int month, int h);
int calendar_x1 = 0, calendar_y1 = 80, calendar_x2 = 714, calendar_y2 = 450;
int set_x1=460, set_x2=254, set_y2=180,set_y1 = calendar_y2 - set_y2;
int temp;
TextEditState t_name;
TextEditState t_year;
TextEditState t_month;
TextEditState t_day;
class schedule
{
public:
	int year;
	int month;
	int day;
	String name;
	int num;
	bool shouhi;
};
void Main()
{
	schedule sche[100];
	// 背景色を ColorF{ 0.3, 0.6, 1.0 } に設定
	Scene::SetBackground(Palette::White);
	int i = 0, j = 1, h = 0;
	const Font font10{ 10, Typeface::Bold },font13{ 13 }, fontBold{ 13, Typeface::Bold }, fontBold25{ 25, Typeface::Bold }, fontBold17{ 17, Typeface::Bold }, fontBold18{ 18, Typeface::Bold }, fontM{ 15, Typeface::Medium }, font18{ 18 }, font21{ 21 }, font11{ 11 }, fontM13{ 13, Typeface::Medium };
	const Date date = Date::Today();
	h = calendar_jg(date.year, date.month);
	int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int m = date.month, y = date.year;
	int count = 0,scheco=0,d_cli=1;
	String text = U"日月火水木金土", s;
	const String cancel = U"キャンセル",save=U"保存";
	Vec2 pos{ 20, 20 };
	
	Window::Resize(714, 600);
	while (System::Update())
	{
		ClearPrint();

		Print << Cursor::Pos(); // 現在のマウスカーソル座標を表示

		Print << U"X: " << Cursor::Pos().x; // X 座標だけを表示

		Print << U"Y: " << Cursor::Pos().y; // Y 座標だけを表示
		Print << temp; // Y 座標だけを表示
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

		if (MouseL.down() && temp==0)
		{
			d_cli=mousejg(month[m], h);
		}
		if (temp == 1)
		{
			int y1, m1, d1;
			string sy,sm,sd;
			RoundRect{ 460, 304, 254,350,10 }.draw(Palette::Orange);
			Rect{ 460, 354, 254,350 }.draw(Palette::Whitesmoke);
			size_t index0 = 0;
			sy=to_string(y);
			sm = to_string(m);
			sd = to_string(d_cli);
			t_year.text = Unicode::Widen(sy);
			t_month.text = Unicode::Widen(sm);
			t_day.text = Unicode::Widen(sd);
			SimpleGUI::TextBox(t_name, Vec2{ 510, 384 }, 204);
			SimpleGUI::TextBox(t_year, Vec2{ 510, 429 }, 100, 4);
			SimpleGUI::TextBox(t_month, Vec2{ 608, 429 }, 54, 2);
			SimpleGUI::TextBox(t_day, Vec2{ 660, 429 }, 54, 2);
			Rect{ 510, 474, 80, 36 }.draw(Palette::White).drawFrame(2, 0, Palette::Gray);
			SimpleGUI::RadioButtons(index0, { U"賞味期限", U"消費期限" }, Vec2{ 580, 519 });
			fontM(U"食品名").draw(463, 388, Palette::Black);
			fontM(U"期限日").draw(463, 388 + 45, Palette::Black);
			fontM(U"個数").draw(470, 388 + 45 * 2, Palette::Black);
			font21(count).draw(517, 476, Palette::Black);
			fontBold18(U"新しい予定").draw(540, 315, Palette::White);
			fontM13(cancel).draw(465, 321, Palette::White);
			fontM13(save).draw(670, 322, Palette::White);
			if (SimpleGUI::Button(U"+", Vec2{ 600, 474 }, 40)) count++;
			if (SimpleGUI::Button(U"-", Vec2{ 650, 474 }, 40) && 0<count) count--;
			if (KeyR.down())
			{
				sy = t_year.text.narrow();
				sm = t_month.text.narrow();
				sd = t_day.text.narrow();
				y1 = stoi(sy);
				m1 = stoi(sm);
				d1 = stoi(sd);
				sche[scheco].year = y1;
				sche[scheco].month = m1;
				sche[scheco].day = d1;
				sche[scheco].name = t_name.text;
				sche[scheco].num = count;
				sche[scheco].shouhi = index0;
				scheco++;
				temp = 0;
			}
		}
		for (i = 0; i < scheco; i++)
		{
			if (y == sche[i].year && m == sche[i].month)
			{
				Rect rect1{ calendar_x2/7 * ((sche[i].day + h -1) %7)+1, calendar_y2/6*((sche[i].day-1)/7)+calendar_y1+20, 100, 15};
				rect1.draw(Palette::Skyblue);
				font10(sche[i].name).draw(rect1, Palette::White);
				Print << sche[i].name <<h;
			}
		}
		/*Rect rect1{1 , 48, 97, 15};
		rect1.draw(Palette::Skyblue);
		font10(U"キャベツ").draw(Rect { 100, 48, 97, 15 }, Palette::White);*/
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
		if (year % 400==0) {
			return true;
		}
		else if (year % 100 == 0) {
			return false;
		}
		if (year % 4 == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}
int mousejg(int month, int h)
{
	int i = 0, j = 0, x, y;
	x = Cursor::Pos().x;
	y = Cursor::Pos().y;
	for (i = 1; i <= month; i++)
	{
		if (x > calendar_x1 + (calendar_x2 / 7) * ((i + h - 1) % 7) && x <= calendar_x1 + (calendar_x2 / 7) * ((i + h - 1) % 7 + 1) && y > calendar_y1 + (calendar_y2 / 6) * j && y <= calendar_y1 + (calendar_y2 / 6) * (j + 1))
		{

			temp = 1;

			return i;
		}
		if ((i + h) % 7 == 0)j++;
	}
	return 0;
}

