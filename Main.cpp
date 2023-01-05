# include <Siv3D.hpp>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
using namespace std;
int calendar_jg(int year, int month);
bool uru(int year, int month);
int mousejg(int month, int h);
bool typecheck();
void classsort(int n);
int calendar_x1 = 0, calendar_y1 = 80, calendar_x2 = 714, calendar_y2 = 450;
int  set_x2 = 254, set_x1 = calendar_x2 - set_x2, set_y2 = 246, set_y1 = 282;
int  set2_x2 = 254, set2_x1 = calendar_x2 - set2_x2, set2_y1 = 532, set2_y2 = 282;
int temp, temp2 = 0, temp3 = 0, temp2_1 = 0, temp2_2 = 0, temp2_3 = 0;
int scene = 0;
TextEditState t_name;
TextEditState t_year;
TextEditState t_month;
TextEditState t_day;
class schedule
{
public:
	int whatday;
	int year;
	int month;
	int day;
	String name;
	int num;
	bool shouhi;
};
schedule sche[100], taihi;
void Main()
{
	JSON json=JSON::Load(U"a.json");
	bool check = false;
	// 背景色を ColorF{ 0.3, 0.6, 1.0 } に設定
	Scene::SetBackground(Palette::White);
	int i = 0, j = 1, h = 0;
	const Font font10{ 10, Typeface::Bold }, font13{ 13 }, fontBold{ 13, Typeface::Bold }, fontBold25{ 25, Typeface::Bold }, fontBold17{ 17, Typeface::Bold }, fontBold18{ 18, Typeface::Bold }, fontM{ 15, Typeface::Medium }, font18{ 18 }, font21{ 21 }, font11{ 11 }, fontM13{ 13, Typeface::Medium }, FontR25{ 25,Typeface::Regular }, FontR20{ 18,Typeface::Regular }, fontBold20{ 20, Typeface::Bold };
	const Date date = Date::Today();
	Font iconFont{ FontMethod::MSDF, 40, Typeface::Icon_MaterialDesign };
	h = calendar_jg(date.year, date.month);
	int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int m = date.month, y = date.year;
	int count = 0, scheco = 0, d_cli = 1;
	int schearr[32];
	String text = U"日月火水木金土", jsonum[101], windowTitle;
	const String cancel = U"キャンセル", save = U"保存";
	RectF rectcancel = fontM13(cancel).region(set_x1 + 10, set_y1 - 33);
	RoundRect arrowR{ 570, calendar_y2 + 100 , 80,30,20 };
	RoundRect arrowL{ 450, calendar_y2 + 100 , 80,30,20 };
	RectF rectsave = fontM13(save).region(set2_x1 + set2_x2 - 45, set_y1 - 32);
	RectF choice[43];
	int choicenow = 1;
	for (i = 0; i < 42; i++)
	{
		choice[i+1] = { calendar_x2/7*(i%7), calendar_y2/6*(i/7)+calendar_y1, calendar_x2 / 7, (calendar_y2 / 6)};
	}
	int toguruS = 0;
	Rect toguru1{ calendar_x2 - 250,30,200 / 2,30 }, toguru2{ calendar_x2 - 150,30,200 / 2,30 };
	int listnow = 0;
	Vec2 pos{ 20, 20 };
	int y1, m1, d1;
	string sy, sm, sd, s1;
	size_t index0 = 0, index1;
	for (i = 0; i < 101; i++)
	{
		s1 = to_string(i);
		jsonum[i] = Unicode::Widen(s1);
	}

	scheco = json[U"count"].get<int32>();
	for (i = 0; i < scheco; i++)
	{
		sche[i].name = json[U"schedule"][jsonum[i]][U"name"].getString();
		sche[i].year = json[U"schedule"][jsonum[i]][U"year"].get<int32>();
		sche[i].month = json[U"schedule"][jsonum[i]][U"month"].get<int32>();
		sche[i].day = json[U"schedule"][jsonum[i]][U"day"].get<int32>();
		sche[i].shouhi = json[U"schedule"][jsonum[i]][U"shouhi"].get<bool>();
		sche[i].num = json[U"schedule"][jsonum[i]][U"num"].get<int32>();
		sche[i].whatday = (sche[i].year - 1) * 365 + month[sche[i].month] + sche[i].day;
	}
	Window::Resize(714, 600);
	while (System::Update())
	{
		ClearPrint();
		

		Print << Cursor::Pos(); // 現在のマウスカーソル座標を表示

		Print << U"X: " << Cursor::Pos().x; // X 座標だけを表示

		Print << windowTitle; // Y 座標だけを表示

		if (scene == 0)
		{
			Rect{ 0, 0, calendar_x2, calendar_y1 }.draw(ColorF{ 0, 0, 0, 0.05 });
			fontBold25(m, U"月").draw(300, 20, Palette::Black);
			fontBold18(y).draw(370, 25, Palette::Silver);
			if (toguru1.leftClicked()) toguruS = 0;
			else if (toguru2.leftClicked()) toguruS = 1;
			if (toguruS == 0)
			{
				toguru2.drawFrame(2, 0, Palette::Gray);
				toguru1.drawFrame(2, 0, Palette::Salmon);
				fontM(U"支出").draw(calendar_x2 - 220, 35, Palette::Salmon);
				fontM(U"期限").draw(calendar_x2 - 120, 35, Palette::Gray);
			}
			if (toguruS == 1)
			{
				toguru1.drawFrame(2, 0, Palette::Gray);
				toguru2.drawFrame(2, 0, Palette::Salmon);
				fontM(U"支出").draw(calendar_x2 - 220, 35, Palette::Gray);
				fontM(U"期限").draw(calendar_x2 - 120, 35, Palette::Salmon);
			}
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
			choice[choicenow].drawFrame(3, 0, Palette::Red);

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
			for (i = 0; i < scheco; i++)
			{
				if (y == sche[i].year && m == sche[i].month)
				{
					Rect rect1{ calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 1, calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 20 + 17 * schearr[sche[i].day], 100, 15 };
					sche[i].shouhi? rect1.draw(Palette::Orange):rect1.draw(Palette::Skyblue);
					font10(sche[i].name).draw(rect1, Palette::White);
					schearr[sche[i].day]++;
				}
			}
			for (i = 0; i < 32; i++)schearr[i] = 0;

			if (MouseL.down() && temp == 0)
			{
				d_cli = mousejg(month[m], h);
				if (d_cli + h == choicenow)
				{
					sy = to_string(y);
					sm = to_string(m);
					sd = to_string(d_cli);
					t_year.text = Unicode::Widen(sy);
					t_month.text = Unicode::Widen(sm);
					t_day.text = Unicode::Widen(sd);
					set_y1 += set_y2 + 4;
					temp = 1;
				}
				choicenow = d_cli + h;
			}
			if (d_cli != 0 && temp2 == 0 && set_y1 > 282 && temp3 == 0)
			{
				set_y1 -= 10;
				RoundRect{ set_x1, set_y1 - 50, set_x2,set_y2,10 }.draw(Palette::Orange);
				Rect{ set_x1, set_y1, set_x2,set_y2 }.draw(Palette::Whitesmoke);
				Vec2 Vname{ set_x1 + 50, set_y1 + 30 };
				Vec2 Vyear{ set_x1 + 50, set_y1 + 70 };
				Vec2 Vmonth{ set_x1 + 148, set_y1 + 70 };
				Vec2 Vday{ set_x1 + 200, set_y1 + 70 };
				SimpleGUI::TextBox(t_name, Vname, 204);
				SimpleGUI::TextBox(t_year, Vyear, 100, 4);
				SimpleGUI::TextBox(t_month, Vmonth, 54, 2);
				SimpleGUI::TextBox(t_day, Vday, 54, 2);
				fontM(U"年").draw(set_x1 + 125, set_y1 + 79, Palette::Black);
				fontM(U"月").draw(set_x1 + 183, set_y1 + 79, Palette::Black);
				fontM(U"日").draw(set_x1 + 235, set_y1 + 79, Palette::Black);
				Rect{ set_x1 + 50, set_y1 + 120, 80, 36 }.draw(Palette::White).drawFrame(2, 0, Palette::Gray);
				SimpleGUI::RadioButtons(index0, { U"賞味期限", U"消費期限" }, Vec2{ set_x1 + 120, set_y1 + 165 });
				fontM(U"食品名").draw(set_x1 + 3, set_y1 + 34, Palette::Black);
				fontM(U"期限日").draw(set_x1 + 3, set_y1 + 34 + 45, Palette::Black);
				fontM(U"個数").draw(set_x1 + 10, set_y1 + 34 + 45 * 2, Palette::Black);
				font21(count).draw(set_x1 + 57, +set_y1 + 122, Palette::Black);
				fontBold18(U"新しい予定").draw(set_x1 + (set_x2 / 2 - 45), set_y1 - 39, Palette::White);
				fontM13(cancel).draw(set_x1 + 10, set_y1 - 33, Palette::White);
				fontM13(save).draw(set_x1 + set_x2 - 45, set_y1 - 32, Palette::White);
				if (SimpleGUI::Button(U"+", Vec2{ set_x1 + 140, set_y1 + 120 }, 40)) count++;
				if (SimpleGUI::Button(U"-", Vec2{ set_x1 + 190, set_y1 + 120 }, 40) && 0 < count) count--;
				if (set_y1 == 282)
				{
					temp2 = 1;
				}

			}
			else if (temp == 1 && temp2 == 1)
			{
				Vec2 Vname{ set_x1 + 50, set_y1 + 30 };
				Vec2 Vyear{ set_x1 + 50, set_y1 + 70 };
				Vec2 Vmonth{ set_x1 + 148, set_y1 + 70 };
				Vec2 Vday{ set_x1 + 200, set_y1 + 70 };
				RoundRect{ set_x1, set_y1 - 50, set_x2,set_y2,10 }.draw(Palette::Orange);
				Rect{ set_x1, set_y1, set_x2,set_y2 }.draw(Palette::Whitesmoke);
				if (temp2_3 == 0)
				{
					SimpleGUI::TextBox(t_name, Vname, 204);
					SimpleGUI::TextBox(t_year, Vyear, 100, 4);
					SimpleGUI::TextBox(t_month, Vmonth, 54, 2);
					SimpleGUI::TextBox(t_day, Vday, 54, 2);
					fontM(U"年").draw(set_x1 + 125, set_y1 + 79, Palette::Black);
					fontM(U"月").draw(set_x1 + 183, set_y1 + 79, Palette::Black);
					fontM(U"日").draw(set_x1 + 235, set_y1 + 79, Palette::Black);
					Rect{ set_x1 + 50, set_y1 + 120, 80, 36 }.draw(Palette::White).drawFrame(2, 0, Palette::Gray);
					SimpleGUI::RadioButtons(index0, { U"賞味期限", U"消費期限" }, Vec2{ set_x1 + 120, set_y1 + 165 });
					fontM(U"食品名").draw(set_x1 + 3, set_y1 + 34, Palette::Black);
					fontM(U"期限日").draw(set_x1 + 3, set_y1 + 34 + 45, Palette::Black);
					fontM(U"個数").draw(set_x1 + 10, set_y1 + 34 + 45 * 2, Palette::Black);
					font21(count).draw(set_x1 + 57, +set_y1 + 122, Palette::Black);
					fontBold18(U"新しい予定").draw(set_x1 + (set_x2 / 2 - 45), set_y1 - 39, Palette::White);
					fontM13(cancel).draw(set_x1 + 10, set_y1 - 33, Palette::White);
					if (check)fontM13(save).draw(set_x1 + set_x2 - 45, set_y1 - 32, Palette::White);
					else fontM13(save).draw(set_x1 + set_x2 - 45, set_y1 - 32, ColorF(0, 0, 0, 0.2));
					rectcancel.draw(Color{ 0, 0, 0, 0 });
					rectsave.draw(Color{ 0, 0, 0, 0 });
					if (rectcancel.leftClicked() && temp2_1 == 0)
					{
						temp = 0;
						temp2 = 0;
						temp3 = 1;
					}

					if (SimpleGUI::Button(U"+", Vec2{ set_x1 + 140, set_y1 + 120 }, 40)) count++;
					if (SimpleGUI::Button(U"-", Vec2{ set_x1 + 190, set_y1 + 120 }, 40) && 0 < count) count--;
					if (SimpleGUI::Button(U"種類", Vec2{ set_x1 + 35, set_y1 + 180 }, 60))
					{
						temp2_1 = 1;
					}
				}
				if (temp2_1 == 1)
				{
					if (set2_y1 >= 300 && temp2_2 == 0)
					{
						set2_y1 -= 10;
						if (set2_y1 == 292)temp2_3 = 1;
					}
					RoundRect{ set2_x1, set2_y1 - 50, set2_x2,set2_y2,10 }.draw(Palette::Blue);
					Rect{ set2_x1, set2_y1, set2_x2,set2_y2 }.draw(Palette::Whitesmoke);
					SimpleGUI::RadioButtons(index1, { U"肉", U"魚" ,U"野菜" }, Vec2{ set2_x1 + 110, set2_y1 + 80 });
					fontM13(cancel).draw(set2_x1 + 10, set2_y1 - 33, Palette::White);
					fontM13(save).draw(set2_x1 + set2_x2 - 45, set_y1 - 32, Palette::White);
					rectcancel.draw(Color{ 0, 0, 0, 0 });
					if (rectcancel.leftClicked())
					{
						temp2_2 = 1;
						temp2_3 = 0;
					}
					if (temp2_2 == 1)
					{
						set2_y1 += 10;
						if (set2_y1 == 532)
						{
							temp2_2 = 0;
							temp2_1 = 0;
						}
					}

				}
				check = typecheck();
				if (rectsave.leftClicked() && check)
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
					sche[scheco].whatday = (y1 - 1) * 365 + month[m1] + d1;
					classsort(scheco);
					for (i = 0; i <= scheco; i++)
					{
						json[U"schedule"][jsonum[i]][U"name"] = sche[i].name;
						json[U"schedule"][jsonum[i]][U"year"] = sche[i].year;
						json[U"schedule"][jsonum[i]][U"month"] = sche[i].month;
						json[U"schedule"][jsonum[i]][U"day"] = sche[i].day;
						json[U"schedule"][jsonum[i]][U"shouhi"] = sche[i].shouhi;
						json[U"schedule"][jsonum[i]][U"num"] = sche[i].num;
					}
					json[U"count"] = scheco + 1;
					json.save(U"a.json");
					scheco++;
					temp = 0;
					temp2 = 0;
					temp3 = 1;

					t_name.clear();
					t_year.clear();
					t_month.clear();
					t_day.clear();
				}
			}
			else if (temp3 == 1)
			{
				set_y1 += 10;
				RoundRect{ set_x1, set_y1 - 50, set_x2,set_y2,10 }.draw(Palette::Orange);
				Rect{ set_x1, set_y1, set_x2,set_y2 }.draw(Palette::Whitesmoke);
				Vec2 Vname{ set_x1 + 50, set_y1 + 30 };
				Vec2 Vyear{ set_x1 + 50, set_y1 + 70 };
				Vec2 Vmonth{ set_x1 + 148, set_y1 + 70 };
				Vec2 Vday{ set_x1 + 200, set_y1 + 70 };
				size_t index0 = 0;
				SimpleGUI::TextBox(t_name, Vname, 204);
				SimpleGUI::TextBox(t_year, Vyear, 100, 4);
				SimpleGUI::TextBox(t_month, Vmonth, 54, 2);
				SimpleGUI::TextBox(t_day, Vday, 54, 2);
				fontM(U"年").draw(set_x1 + 125, set_y1 + 79, Palette::Black);
				fontM(U"月").draw(set_x1 + 183, set_y1 + 79, Palette::Black);
				fontM(U"日").draw(set_x1 + 235, set_y1 + 79, Palette::Black);
				Rect{ set_x1 + 50, set_y1 + 120, 80, 36 }.draw(Palette::White).drawFrame(2, 0, Palette::Gray);
				SimpleGUI::RadioButtons(index0, { U"賞味期限", U"消費期限" }, Vec2{ set_x1 + 120, set_y1 + 165 });
				fontM(U"食品名").draw(set_x1 + 3, set_y1 + 34, Palette::Black);
				fontM(U"期限日").draw(set_x1 + 3, set_y1 + 34 + 45, Palette::Black);
				fontM(U"個数").draw(set_x1 + 10, set_y1 + 34 + 45 * 2, Palette::Black);
				font21(count).draw(set_x1 + 57, +set_y1 + 122, Palette::Black);
				fontBold18(U"新しい予定").draw(set_x1 + (set_x2 / 2 - 45), set_y1 - 39, Palette::White);
				fontM13(cancel).draw(set_x1 + 10, set_y1 - 33, Palette::White);
				fontM13(save).draw(set_x1 + set_x2 - 45, set_y1 - 32, Palette::White);
				if (SimpleGUI::Button(U"+", Vec2{ set_x1 + 140, set_y1 + 120 }, 40)) count++;
				if (SimpleGUI::Button(U"-", Vec2{ set_x1 + 190, set_y1 + 120 }, 40) && 0 < count) count--;
				if (set_y1 == 532)
				{
					temp3 = 0;
					set_y1 = 282;
				}
			}
		}
		else if (scene == 1)
		{
			Rect{ 0, 0, calendar_x2, calendar_y1 }.draw(ColorF{ 0, 0, 0, 0.05 });
			Rect{ calendar_x1 - 1, calendar_y1, calendar_x2 + 2, calendar_y2 } //カレンダー出力　座標(x1,y1)を左上の基準にして幅x2,高さy2の長方形をかく //適当にやってるのは後で直す
			.drawFrame(1, 0, Palette::Black);

			for (i = 1; i <= 9; i++)
			{
				Line{ calendar_x1, (calendar_y2) / 10 * i + calendar_y1 , calendar_x2 + calendar_x1 ,(calendar_y2) / 10 * i + calendar_y1 }.draw(0.5, Palette::Silver); //横の線
			}
			for (i = listnow * 10; i < scheco; i++)
			{
				FontR20(sche[i].year, U"/", sche[i].month, U"/", sche[i].day).draw(1, calendar_y1 + 10 + (calendar_y2) / 10 * (i % 10), Palette::Black);
				FontR25(sche[i].name).draw(180, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::Black);
				Circle{ 540, 530, 30 }.draw();
				iconFont(U"\U000F0A7A").draw(30, 670, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::Red);
				if (sche[i].shouhi)
				{
					Circle{ 140, calendar_y1 + 22 + (calendar_y2) / 10 * (i % 10), 18 }.draw(Palette::Orange);
					fontBold20(U"費").draw(130, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::White);
				}
				else
				{

					Circle{ 140, calendar_y1 + 21 + (calendar_y2) / 10 * (i % 10), 18 }.draw(Palette::Skyblue);
					fontBold20(U"味").draw(130, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::White);

				}
				j++;
				if (j == 10)
				{
					j = 0;
					break;
				}
			}
			j = 0;
		}
		Rect{ calendar_x1, calendar_y2 + calendar_y1, calendar_x2,100 }.draw(Palette::White);
		if (scene == 1)
		{
			if ((scheco - 1) / 10 > listnow)
			{
				arrowR.draw(Palette::Skyblue);
				if (arrowR.leftClicked())listnow++;
			}
			else
			{
				arrowR.draw(Palette::Gray);
			}
			if (listnow != 0)
			{
				arrowL.draw(Palette::Skyblue);
				if (arrowL.leftClicked())listnow--;
			}
			else
			{
				arrowL.draw(Palette::Gray);
			}
			fontBold18(U">").draw(600, calendar_y2 + 100), (Palette::White);
			fontBold18(U"<").draw(480, calendar_y2 + 100), (Palette::White);
		}
		if (SimpleGUI::Button(U"カレンダー", Vec2{ 50,550 }))
		{
			scene = 0;
		}

		if (SimpleGUI::Button(U"一覧", Vec2{ 200,550 }))
		{
			scene = 1;
		}

		if (SimpleGUI::Button(U"料理", Vec2{ 300, 550 }))
		{

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
		if (year % 400 == 0) {
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


			return i;
		}
		if ((i + h) % 7 == 0)j++;
	}
	return 0;
}
bool typecheck()
{
	int i, size_y, size_m, size_d, size_n;
	string sy, sm, sd;
	size_y = t_year.text.size();
	size_m = t_month.text.size();
	size_d = t_day.text.size();
	size_n = t_name.text.size();

	if (size_y == 0 || size_m == 0 || size_d == 0 || size_n == 0)
	{
		return false;
	}
	sy = t_year.text.narrow();
	sm = t_month.text.narrow();
	sd = t_day.text.narrow();
	for (i = 0; i < size_y; i++)
	{
		if (!isdigit(sy[i]))return false;
	}

	for (i = 0; i < size_m; i++)
	{
		if (!isdigit(sm[i]))return false;
		if (size_m == 1 && sm[0] == '0')return false;
		if (i == 1 && sm[0] == '0' && sm[1] == '0') return false;
		if (i == 1 && sm[0] == '0' && isalpha(sm[1]) && sm[1] != '0')
		{

			t_month.text.erase(1, 1);
		}
	}
	for (i = 0; i < size_d; i++)
	{
		if (!isdigit(sd[i]))return false;
		if (size_d == 1 && sd[0] == '0')return false;
		if (i == 1 && sd[0] == '0' && sd[1] == '0')return false;
		if (i == 1 && sd[0] == '0' && isalpha(sd[1]) && sd[1] != '0')
		{
			t_day.text.erase(1, 1);
		}
	}
	return true;
}
void classsort(int n)
{
	int i, j;
	taihi = sche[n];
	for (i = 0; i <n;i++)
	{
		if (taihi.whatday < sche[i].whatday)
		{
			for (j = n-1; j >= i;)
			{
				sche[j+1] = sche[j];
				j--;
			}
			sche[i] = taihi;
			break;
		}
	}
}
