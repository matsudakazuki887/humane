# include <Siv3D.hpp>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
#include <tchar.h>

using namespace std;
int calendar_jg(int year, int month);
bool uru(int year, int month);
int mousejg(int month, int h);
bool typecheck();
bool typecheck2();
void classsort(int n);
void sortup(int n);
int calendar_x1 = 0, calendar_y1 = 80, calendar_x2 = 714, calendar_y2 = 450;
int  set_x2 = 254, set_x1 = calendar_x2 - set_x2, set_y2 = 246, set_y1 = 282;
int  set2_x2 = 254, set2_x1 = calendar_x2 - set2_x2, set2_y1 = 532, set2_y2 = 282;
int  set3_x2 = 254, set3_x1 = calendar_x2 - set3_x2, set3_y2 = 246, set3_y1 = 532;
int temp = 0, temp2 = 0, temp3 = 0, temp2_0 = 0, temp2_1 = 0, temp2_2 = 0, temp2_3 = 0,temp4=0,temp4_2=0;
int scene = 0;
int yotei = 0,yoteiosita=0;
int keikokuco = 0;
TextEditState t_name;
TextEditState t_year;
TextEditState t_month;
TextEditState t_day;
TextEditState t_money;
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
	int type;
};
class shuppi
{
public:
	int year;
	int month;
	int day;
	int num;
};
schedule sche[100], taihi;
shuppi money[2210];
void Main()
{
	JSON json = JSON::Load(U"a.json");
	const Date date = Date::Today();
	if(json[U"now"][U"year"]!=date.year || json[U"now"][U"month"] != date.month || json[U"now"][U"day"] != date.day)
	{
		system("rakutenapi.exe");
		json[U"now"][U"year"] = date.year;
		json[U"now"][U"month"] = date.month;
		json[U"now"][U"day"] = date.day;
		json.save(U"a.json");
	}
	JSON jsonninki[4] = { JSON::Load(U"recipe_niku.json"),JSON::Load(U"recipe_sakana.json"),JSON::Load(U"recipe_yasai.json"),JSON::Load(U"recipe_ninki.json") };
	String title[4][4], image;
	FilePath ninki[4][4] = { {U"niku1.png",U"niku2.png",U"niku3.png",U"niku4.png"}, { U"sakana1.png",U"sakana2.png",U"sakna3.png",U"sakna4.png" }, { U"yasai1.png",U"yasai2.png",U"yasai3.png",U"yasai4.png" },{ U"ninki1.png",U"ninki2.png",U"ninki3.png",U"ninki4.png" } };
	Texture ninkiima[4][4];
	String taihis,setumei[4][4];
	string foodURL[4][4];
	bool check = false;
	int moneycheck = 0;
	// 背景色を ColorF{ 0.3, 0.6, 1.0 } に設定
	Scene::SetBackground(Palette::White);
	int i = 0, j = 1, h = 0;
	const Font font10{ 10, Typeface::Bold }, font13{ 13 }, fontBold{ 13, Typeface::Bold }, fontBold25{ 25, Typeface::Bold }, fontBold17{ 17, Typeface::Bold }, fontBold18{ 18, Typeface::Bold }, fontM{ 15, Typeface::Medium }, font18{ 18 }, font21{ 21 }, font11{ 11 }, fontM13{ 13, Typeface::Medium }, FontR25{ 25,Typeface::Regular }, FontR20{ 18,Typeface::Regular }, fontBold20{ 20, Typeface::Bold }, fontBold27{ 27, Typeface::Bold };
	Font iconFont{ FontMethod::MSDF, 40, Typeface::Icon_MaterialDesign };
	h = calendar_jg(date.year, date.month);
	int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int m = date.month, y = date.year;
	int count = 0, scheco = 0, d_cli = 1,scheout=0,scheout1=0,schelist=0;
	int schearr[32];
	String text = U"日月火水木金土", jsonum[2201], windowTitle;
	const String cancel = U"キャンセル", save = U"保存";
	Texture foodfish{ 0xf578_icon, 30 };
	Texture foodwater{ 0xf804_icon, 30 };
	Texture foodmeat{ 0xF141F_icon, 30 };
	Texture foodveg{ 0xf787_icon, 30 };
	Texture foodsalt{ 0xf816_icon, 30 };
	Texture fontup{ 0xF0063_icon, 20 };
	Texture fontdown{ 0xF004B_icon, 20 };
	Texture fontURL{ 0xf57d_icon, 30 };
	Texture fontcaret{ 0xf0d7_icon, 22 };
	RoundRect arrowR{ 570, calendar_y2 + 100 , 80,30,20 };
	RoundRect arrowL{ 450, calendar_y2 + 100 , 80,30,20 };
	RoundRect arrowR2{ 570, calendar_y2 + 50 , 80,30,20 };
	RoundRect arrowL2{ 450, calendar_y2 + 100 , 80,30,20 };
	RectF rectsave = fontM13(save).region(set2_x1 + set2_x2 - 45, set_y1 - 32);
	RectF updown = { 26, 35, 68,30 };
	int up = 1;
	RectF choice[43];
	int choicenow = 1;
	for (i = 0; i < 42; i++)
	{
		choice[i + 1] = { calendar_x2 / 7 * (i % 7), calendar_y2 / 6 * (i / 7) + calendar_y1, calendar_x2 / 7, (calendar_y2 / 6) };
	}

	int toguruS = 1;
	Rect toguru1{ calendar_x2 - 250,30,200 / 2,30 }, toguru2{ calendar_x2 - 150,30,200 / 2,30 };
	int listnow = 0;
	Vec2 pos{ 20, 20 };
	int y1, m1, d1, money1;
	string sy, sm, sd, s1, smoney;
	size_t index0 = 0, index1=-1;
	int random=0;
	Rect keikoku{ Arg::center(357, 200), 200, 35 };
	for (i = 0; i < 2200; i++)
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
		sche[i].type = json[U"schedule"][jsonum[i]][U"type"].get<int32>();
		sche[i].whatday = (sche[i].year - 1) * 365 + month[sche[i].month] + sche[i].day;
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			title[i][j] = jsonninki[i][U"recipeTitle"][jsonum[j]].getString();
			setumei[i][j]= jsonninki[i][U"recipeDescription"][jsonum[j]].getString();
			taihis = jsonninki[i][U"recipeUrl"][jsonum[j]].getString();
			foodURL[i][j] = taihis.narrow();
			image = jsonninki[i][U"foodImageUrl"][jsonum[j]].getString();
			if ((json[U"now"][U"year"] != date.year || json[U"now"][U"month"] != date.month || json[U"now"][U"day"] != date.day))
			{
				ninkiima[i][j] = Texture{ninki[i][j]};
			}
			else
			{
				if (SimpleHTTP::Save(image, ninki[i][j]).isOK())
				{
					ninkiima[i][j] = Texture{ ninki[i][j] };
				}
			}
		}
	}
	Window::Resize(714, 600);
	while (System::Update())
	{
		ClearPrint();
		Print << temp;
		Print << d_cli;
		Print << h;
		Print << choicenow;
		if (scene == 0)
		{
			if (up == 0) {
				sortup(scheco);
				up++;
			}
			//--------------------------トグルボタン--------------------------------------------
			Rect{ 0, 0, calendar_x2, calendar_y1 }.draw(ColorF{ 0, 0, 0, 0.05 });
			fontBold25(m, U"月").draw(300, 20, Palette::Black);
			fontBold18(y).draw(370, 25, Palette::Silver);
			if (toguru1.leftClicked() && temp == 0 && temp2_0 == 0) toguruS = 0;
			if (toguru2.leftClicked() && temp == 0 && temp2_0 == 0) toguruS = 1;
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
			//--------------------------トグルボタン--------------------------------------------------



			//---------------------------カレンダー-----------------------------------------------------
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
			//-------------------------------------------カレンダー--------------------------------------------------------------



			// ------------------------------------------月移動------------------------------------------------------------------
			if (KeyLeft.down() && y>=1950 && temp == 0)
			{
				m--;
				if (m == 0)
				{
					m = 12;
					y--;
				}
				h = calendar_jg(y, m);
			}
			if (KeyRight.down() && y<=2100 && temp == 0)
			{
				m++;
				if (m == 13)
				{
					m = 1;
					y++;
				}
				h = calendar_jg(y, m);
			}
			//-------------------------------------------月移動--------------------------------------------------------------------------

			//-------------------------------------------スケジュール出力----------------------------------------------------------------

			if (toguruS)
			{
				for (i = 0; i < scheco; i++)
				{
					if (y == sche[i].year && m == sche[i].month && schearr[sche[i].day] < 3)
					{
						Rect rect1{ calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 1, calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 20 + 17 * schearr[sche[i].day], 100, 15 };
						sche[i].shouhi ? rect1.draw(Palette::Orange) : rect1.draw(Palette::Skyblue);
						font10(sche[i].name).draw(rect1, Palette::White);
						schearr[sche[i].day]++;
					}
					else if (y == sche[i].year && m == sche[i].month)
					{
						schearr[sche[i].day]++;
						s3d::Triangle::value_type tri1 = calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 101, tri2 = calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 23 + 17 * 3;
						s3d::Triangle::value_type tri3 = calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 101, tri4 = calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 17 * 3;
						s3d::Triangle::value_type tri5 = calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 70, tri6 = calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 23 + 17 * 3;
						Triangle tri{ tri1,tri2,tri3,tri4,tri5,tri6 };
						tri.draw(Color{ 255,0,0,90 });
						if (schearr[sche[i].day] <= 9)
						{
							fontBold(U"+", schearr[sche[i].day]-3).draw(calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 82, calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 6 + 17 * 3, Palette::White);
						}
						else
						{
							fontBold(9, U"+").draw(calendar_x2 / 7 * ((sche[i].day + h - 1) % 7) + 82, calendar_y2 / 6 * ((sche[i].day + h - 1) / 7) + calendar_y1 + 6 + 17 * 3, Palette::White);
						}
					}
				}
			}
			else
			{
				
				if (uru(y, m))month[m]++;
				int mtaihi,moneysum=0;
				for (i = 1; i <= month[m]; i++)
				{
					mtaihi = json[jsonum[y]][jsonum[m]][jsonum[i]].get<int32>();
					if (mtaihi != 0)
					{
						Rect rect1{ calendar_x2 / 7 * ((i + h - 1) % 7) + 1, calendar_y2 / 6 * ((i + h - 1) / 7) + calendar_y1 + 20 , 100, 15 };
						rect1.draw(Palette::Teal);
						font10(mtaihi,U"円").draw(rect1, Palette::White);
						moneysum += mtaihi;
					}
				}
				fontBold25(moneysum, U"円").draw(150, 20, Palette::Red);
				if (uru(y, m))month[m]--;
			}
			for (i = 0; i < 32; i++)schearr[i] = 0;

			//-------------------------------------------スケジュール出力-----------------------------------------------------------------

			choice[choicenow].drawFrame(3, 0, Palette::Red);
			//-------------------------------------------クリックした日付判定-------------------------------------------------------------
			if (MouseL.down() && temp == 0)
			{
				d_cli = mousejg(month[m], h);
				if (uru(y, m))month[m]++;
				if (d_cli + h == choicenow && month[m] >= d_cli)
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
				if (uru(y, m))month[m]--;
				Rect arrowR3{ set3_x1, set3_y1 + 70-40,300, 70 };
				if (d_cli != -10 && !arrowR3.leftClicked())
				{
					choicenow = d_cli + h;
					schelist = 0;
					temp4 = 0;
					temp4_2 = 0;
					yoteiosita = 0;
					set3_y1 = 532;
				}
			}

			//-------------------------------------------クリックした日付判定-------------------------------------------------------------

			//-------------------------------------------------予定表示-------------------------------------------------------------------

			for (i = 0; i < scheco; i++)
			{
				if (y == sche[i].year && m == sche[i].month && choicenow == sche[i].day)
				{
					scheout++;
				}
			}
			if (scheout > 0&&!yoteiosita)yotei = 1;
			else yotei = 0;
			if (toguruS && yotei)
			{
				RoundRect{ set_x1, set3_y1+80 - 50, set3_x2,set3_y2-80,10 }.draw(Palette::Orange);
				Rect{ set3_x1, set3_y1+80, set3_x2,set3_y2-80 }.draw(Palette::Whitesmoke);
				if(temp4==0)set3_y1 -= (Scene::DeltaTime() * 1000);
				if (set3_y1 <= 282)
				{
					temp4 = 1;
					set3_y1 = 282;
				}
				if (temp4_2 == 1)
				{
					set3_y1 += (Scene::DeltaTime() * 1000);
					if (set3_y1 >= 532)
					{
						yotei = 0;
						yoteiosita = 1;
						temp4 = 0;
						temp4_2 = 0;
					}
				}
				FontR25(y, U"/", m, U"/", choicenow).draw(set3_x1+2, set3_y1 + 37, Palette::Black);
				for (i = 1; i <= 2; i++)
				{
					Line{ set3_x1+1,  set3_y1+80+ ((set3_y2 - 80)/3*i), set3_x1+set3_x2+2,  set3_y1 + 80 + ((set3_y2 - 80) / 3 * i) }.draw(Palette::Black); //横の線
				}
				for (i = 0; i < scheco; i++)
				{
					if (y == sche[i].year && m == sche[i].month && scheout > 0)
					{
						
						scheout1++;
						if (schelist * 3 < scheout1 && (schelist+1) * 3 >= scheout1)
						{
							if (sche[i].shouhi)
							{
								Circle{ set3_x1 + 25, set3_y1 + 105 + ((set3_y2 - 80) / 3 * ((scheout1 - 1) % 3)), 18 }.draw(Palette::Orange);
								fontBold20(U"費").draw(set3_x1 + 16, set3_y1 + 91 + ((set3_y2 - 80) / 3 * ((scheout1 - 1) % 3)), Palette::White);
							}
							else
							{

								Circle{ set3_x1+25, set3_y1 + 105 + ((set3_y2 - 80) / 3 * ((scheout1 - 1) % 3)), 18 }.draw(Palette::Skyblue);
								fontBold20(U"味").draw(set3_x1 + 16, set3_y1 + 91 + ((set3_y2 - 80) / 3 * ((scheout1 - 1) % 3)), Palette::White);

							}
							fontBold27(sche[i].name.substr(0,8)).draw(set3_x1+45, set3_y1 + 87 + ((set3_y2 - 80) / 3 * ((scheout1-1)%3)), Palette::Black);
							if(sche[i].name.size()>8)fontBold27(U"...").draw(set3_x1 + 170, set3_y1 + 87 + ((set3_y2 - 80) / 3 * ((scheout1 - 1) % 3)), Palette::Black);
							
						}
					}
					
				}
				//if (arrowR.leftClicked())listnow++;
				Rect arrowR3{ set3_x1 + 190, set3_y1 + 80 - 40 ,30, 30 };
				Rect arrowL3{ set3_x1 + 140, set3_y1 + 80 - 40 ,30, 30 };
				Rect arrowcaret{ set3_x1 + 230, set3_y1 + 35 ,20, 20 };

				if (arrowR3.leftClicked() && scheout>(schelist+1)*3)
				{
					schelist++;
				}
				if (arrowL3.leftClicked() && scheout > schelist * 3 && schelist!=0)
				{
					schelist--;
				}
				if (arrowcaret.leftClicked())
				{
					temp4_2 = 1;
				}
				fontcaret.draw(set3_x1 + 230, set3_y1 + 35);
				Print << choicenow;
				fontBold18(U">").draw(set3_x1 + 190, set3_y1 + 80 - 40 ,scheout > (schelist + 1) * 3?(Palette::White): (Palette::Gray));
				fontBold18(U"<").draw(set3_x1+140, set3_y1 + 80-40, scheout > schelist * 3 && schelist != 0? (Palette::White): (Palette::Gray));
			}
			scheout = 0;
			scheout1 = 0;
			//-------------------------------------------出費が選ばれている場合-----------------------------------------------------------
			if (!toguruS)
			{
				int mtaihi2;
				string mtaihis2;
				String mtaihiS2;
				if (d_cli != 0 && temp == 1)
				{
					mtaihi2 = json[jsonum[y]][jsonum[m]][jsonum[d_cli]].get<int32>();
					mtaihis2 = to_string(mtaihi2);
					mtaihiS2 = Unicode::Widen(mtaihis2);
					if (!moneycheck)
					{
						t_money.text = mtaihiS2;
						moneycheck = 1;
					}
					if (temp2 == 0)set_y1 -= (Scene::DeltaTime() * 1000);
					if (set_y1 <= 382)
					{
						temp2 = 1;
						set_y1 = 382;
					}

					RectF rectcancel = fontM13(cancel).region(set_x1 + 10, set_y1 - 33);
					RectF rectsave = fontM13(save).region(set2_x1 + set2_x2 - 45, set_y1 - 32);
					RoundRect{ set_x1, set_y1 - 50, set_x2,set_y2,10 }.draw(Palette::Teal);
					Rect{ set_x1, set_y1, set_x2,set_y2 }.draw(Palette::Whitesmoke);
					Vec2 Vmoney{ set_x1 + 50, set_y1 + 30 };
					Vec2 Vyear{ set_x1 + 50, set_y1 + 70 };
					Vec2 Vmonth{ set_x1 + 148, set_y1 + 70 };
					Vec2 Vday{ set_x1 + 200, set_y1 + 70 };
					fontBold18(U"新しい出費").draw(set_x1 + (set_x2 / 2 - 45), set_y1 - 39, Palette::White);
					if (temp2_0 == 0)
					{
						SimpleGUI::TextBox(t_money, Vmoney, 204, 10);
						SimpleGUI::TextBox(t_year, Vyear, 100, 4);
						SimpleGUI::TextBox(t_month, Vmonth, 54, 2);
						SimpleGUI::TextBox(t_day, Vday, 54, 2);
						fontM(U"金額").draw(set_x1 + 8, set_y1 + 34, Palette::Black);
						fontM(U"出費日").draw(set_x1 + 3, set_y1 + 34 + 45, Palette::Black);
						fontM(U"円").draw(set_x1 + 235, set_y1 + 39, Palette::Black);
						fontM(U"年").draw(set_x1 + 125, set_y1 + 79, Palette::Black);
						fontM(U"月").draw(set_x1 + 183, set_y1 + 79, Palette::Black);
						rectcancel.draw(ColorF(0, 0, 0, 0.0));
						rectsave.draw(Color{ 0, 0, 0, 0 });
						fontM(U"日").draw(set_x1 + 235, set_y1 + 79, Palette::Black);
						check = typecheck2();
						fontM13(cancel).draw(set_x1 + 10, set_y1 - 33, Palette::White);
						if (check)fontM13(save).draw(set_x1 + set_x2 - 45, set_y1 - 32, Palette::White);
						else fontM13(save).draw(set_x1 + set_x2 - 45, set_y1 - 32, ColorF(0, 0, 0, 0.2));
						if (rectsave.leftClicked() && check)
						{
							smoney = t_money.text.narrow();
							sy = t_year.text.narrow();
							sm = t_month.text.narrow();
							sd = t_day.text.narrow();
							y1 = stoi(sy);
							m1 = stoi(sm);
							d1 = stoi(sd);
							money1 = stoi(smoney);
							json[jsonum[y1]][jsonum[m1]][jsonum[d1]] = money1;
							json.save(U"a.json");
							temp2 = 0;
							temp3 = 1;
						}
						if (rectcancel.leftClicked())
						{
							temp3 = 1;
						}
						if (temp3 == 1)
						{
							set_y1 += (Scene::DeltaTime() * 1000);
							if (set_y1 >= 552)
							{
								temp3 = 0;
								temp2 = 0;
								temp = 0;
								set_y1 = 532;
								t_money.clear();
								t_year.clear();
								t_month.clear();
								t_money.clear();
								moneycheck = 0;
							}
						}
					}
				}
			}
			//-------------------------------------------出費が選ばれている場合-----------------------------------------------------------

			//-------------------------------------------期限が選ばれている場合-----------------------------------------------------------
			else if (scheco == 100 && d_cli != 0 && temp == 1)
			{
				keikokuco+= (Scene::DeltaTime() * 1000);
				if (keikokuco >= 1000)
				{
					keikokuco = 0;
					temp = 0;
				}
				keikoku.draw(Palette::Orange);
				fontBold18(U"これ以上追加できません").draw(keikoku, ColorF{ 0.25 });
			}
			else
			{
				if (d_cli != 0 && temp == 1)
				{
					if (temp2 == 0)set_y1 -= (Scene::DeltaTime() * 1000);
					if (set_y1 <= 282)
					{
						temp2 = 1;
						set_y1 = 282;
					}
					RectF rectcancel = fontM13(cancel).region(set_x1 + 10, set_y1 - 33);
					RectF rectsave = fontM13(save).region(set2_x1 + set2_x2 - 45, set_y1 - 32);
					Vec2 Vname{ set_x1 + 50, set_y1 + 30 };
					Vec2 Vyear{ set_x1 + 50, set_y1 + 70 };
					Vec2 Vmonth{ set_x1 + 148, set_y1 + 70 };
					Vec2 Vday{ set_x1 + 200, set_y1 + 70 };
					RoundRect{ set_x1, set_y1 - 50, set_x2,set_y2,10 }.draw(Palette::Orange);
					Rect{ set_x1, set_y1, set_x2,set_y2 }.draw(Palette::Whitesmoke);
					if (temp2_0 == 0)
					{
						SimpleGUI::TextBox(t_name, Vname, 204,9);
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
						if (rectcancel.leftClicked() && temp2_1 == 0 && temp2 == 1)
						{
							temp3 = 1;
						}
						if (temp3 == 1)
						{
							set_y1 += (Scene::DeltaTime() * 1000);
							if (set_y1 >= 552)
							{
								temp3 = 0;
								temp2 = 0;
								temp = 0;
								set_y1 = 532;
								t_name.clear();
								t_year.clear();
								t_month.clear();
								t_day.clear();
								count = 0;
							}
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
						if (temp2_2 == 0)
						{
							set2_y1 -= (Scene::DeltaTime() * 1200);
							if (set2_y1 <= 252)
							{
								temp2_0 = 1;
								temp2_2 = 1;
								set2_y1 = 252;

							}
						}
						RectF rectcancel2 = fontM13(cancel).region(set_x1 + 10, set2_y1 - 33);
						RoundRect{ set2_x1, set2_y1 - 50, set2_x2,set2_y2,10 }.draw(Palette::Blue);
						Rect{ set2_x1, set2_y1, set2_x2,set2_y2 }.draw(Palette::Whitesmoke);
						SimpleGUI::RadioButtons(index1, { U"肉", U"魚" ,U"野菜" ,U"調味料",U"飲料",U"レトルト",U"その他"}, Vec2{set2_x1+50, set2_y1 + 1});
						Print << index1;
						fontM13(U"戻る").draw(set2_x1 + 20, set2_y1 - 33, Palette::White);
						rectcancel2.draw(Color{ 0, 0, 0, 0 });
						if (rectcancel2.leftClicked())
						{
							temp2_0 = 0;
							temp2_3 = 1;
						}
						if (temp2_3 == 1)
						{
							set2_y1 += (Scene::DeltaTime() * 1200);
							if (set2_y1 >= 552)
							{
								temp2_3 = 0;
								temp2_2 = 0;
								temp2_1 = 0;
								set2_y1 = 552;
							}
						}

					}
					check = typecheck();
					if (!(index1 <= 6 && index1 >= 0))check = false;
					if (count==0)check = false;
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
						sche[scheco].type = index1;
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
							json[U"schedule"][jsonum[i]][U"type"] = sche[i].type;
						}
						json[U"count"] = scheco + 1;
						json.save(U"a.json");
						scheco++;
						temp2 = 0;
						temp3 = 1;
						count = 0;


					}
				}
			}
		}
		//-------------------------------------------期限が選ばれている場合-----------------------------------------------------------



		//-----------------------------------------------一覧-------------------------------------------------------------------------
		else if (scene == 1)
		{
			Rect{ 0, 0, calendar_x2, calendar_y1 }.draw(ColorF{ 0, 0, 0, 0.05 });
			Rect{ calendar_x1 - 1, calendar_y1, calendar_x2 + 2, calendar_y2 } //カレンダー出力　座標(x1,y1)を左上の基準にして幅x2,高さy2の長方形をかく //適当にやってるのは後で直す
			.drawFrame(1, 0,Palette::Black);

			for (i = 1; i <= 9; i++)
			{
				Line{ calendar_x1, (calendar_y2) / 10 * i + calendar_y1 , calendar_x2 + calendar_x1 ,(calendar_y2) / 10 * i + calendar_y1 }.draw(0.5, Palette::Silver); //横の線
			}
			FontR25(U"日付").draw(26, 35, Palette::Black);
			FontR25(U"種類").draw(110, 35, Palette::Black);
			FontR25(U"名前").draw(200, 35, Palette::Black);
			if (updown.leftClicked())
			{
				sortup(scheco);
				if (up == 1)up = 0;
				else up = 1;
			}
			up ? fontup.draw(76, 45, Palette::Black) : fontdown.draw(76, 45, Palette::Black);
			for (i = listnow * 10; i < scheco; i++)
			{
				FontR20(sche[i].year, U"/", sche[i].month, U"/", sche[i].day).draw(1, calendar_y1 + 10 + (calendar_y2) / 10 * (i % 10), Palette::Black);
				FontR25(sche[i].name).draw(180, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::Black);
				
				Rect iconrect{ 670, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10) , 30, 30 };
				iconrect.mouseOver() ? iconFont(U"\U000F0A7A").draw(30, 670, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::Indianred) : iconFont(U"\U000F0A7A").draw(30, 670, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), Palette::Red);
				if (sche[i].type == 0)foodmeat.draw(630, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), ColorF{ 0.25 });
				if (sche[i].type == 1)foodfish.draw(630, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), ColorF{ 0.25 });
				if (sche[i].type == 2)foodveg.draw(630, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), ColorF{ 0.25 });
				if (sche[i].type == 3)foodsalt.draw(630, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), ColorF{ 0.25 });
				if (sche[i].type == 4)foodwater.draw(630, calendar_y1 + 8 + (calendar_y2) / 10 * (i % 10), ColorF{ 0.25 });
				
				if (iconrect.leftClicked())
				{
					for (j = i + 1; j < scheco; j++)
					{
						json[U"schedule"][jsonum[j - 1]][U"name"] = sche[j].name;
						json[U"schedule"][jsonum[j - 1]][U"year"] = sche[j].year;
						json[U"schedule"][jsonum[j - 1]][U"month"] = sche[j].month;
						json[U"schedule"][jsonum[j - 1]][U"day"] = sche[j].day;
						json[U"schedule"][jsonum[j - 1]][U"shouhi"] = sche[j].shouhi;
						json[U"schedule"][jsonum[j - 1]][U"num"] = sche[j].num;
						json[U"schedule"][jsonum[j - 1]][U"type"] = sche[j].type;
						sche[j - 1].year = sche[j].year;
						sche[j - 1].month = sche[j].month;
						sche[j - 1].day = sche[j].day;
						sche[j - 1].name = sche[j].name;
						sche[j - 1].num = sche[j].num;
						sche[j - 1].shouhi = sche[j].shouhi;
						sche[j - 1].type = sche[j].type;
						sche[j - 1].whatday = sche[j].whatday;
					}
					scheco--;
					json[U"count"] = scheco;
					json.save(U"a.json");
				}
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
		if (scene == 2)
		{
			Rect{ 0, 0, calendar_x2, calendar_y1 }.draw(ColorF{ 0, 0, 0, 0.05 });
			Rect{ calendar_x1 - 1, calendar_y1, calendar_x2 + 2, calendar_y2 } //カレンダー出力　座標(x1,y1)を左上の基準にして幅x2,高さy2の長方形をかく //適当にやってるのは後で直す
			.drawFrame(1, 0, Palette::Black);
			fontBold25(U"おすすめレシピ").draw(270, 20, Palette::Black);
			for (i = 1; i <= 3; i++)
			{
				Line{ calendar_x1, (calendar_y2) / 4 * i + calendar_y1 , calendar_x2 + calendar_x1 ,(calendar_y2) / 4 * i + calendar_y1 }.draw(0.5, Palette::Silver); //横の線
			}
			for (i = 0; i < 4; i++)
			{
				Rect{ 3, calendar_y1 + 5 + (calendar_y2) / 4 * i ,104,104}.drawFrame(2, 0, Palette::Orange);
				FontR20(U"【",title[random][i], U"】").draw(110, calendar_y1 + 12 + (calendar_y2) / 4 * i, Palette::Black);
				ninkiima[random][i].resized(100,100).draw(5, calendar_y1  +7+ (calendar_y2) / 4 * i);
				Rect URL{ 670, calendar_y1 + 80 + (calendar_y2) / 4 * i ,30,30 };
				fontURL.draw(670, calendar_y1 + 80 + (calendar_y2) / 4 * i, URL.mouseOver() ? Palette::Darkcyan : Palette::Gray);
				if (URL.leftClicked())
				{
					system(("start chrome.exe "+foodURL[random][i]).c_str());
				}
				if (URL.mouseOver())fontBold(U"webページを開く").draw(610, calendar_y1 + 55 + (calendar_y2) / 4 * i,Palette::Red);
			}
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
			scene = 2;
			random = rand() % 4;
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

// クリックした日付を返す
int mousejg(int month, int h)
{
	int i = 0, j = 0, x, y;
	x = Cursor::Pos().x;
	y = Cursor::Pos().y;
	for (i = 1; i <= 42 - h; i++)
	{
		if (x > calendar_x1 + (calendar_x2 / 7) * ((i + h - 1) % 7) && x <= calendar_x1 + (calendar_x2 / 7) * ((i + h - 1) % 7 + 1) && y > calendar_y1 + (calendar_y2 / 6) * j && y <= calendar_y1 + (calendar_y2 / 6) * (j + 1))
		{


			return i;
		}
		if ((i + h) % 7 == 0)j++;
	}
	return -10;
}
bool typecheck()
{
	int i, size_y, size_m, size_d, size_n, ny, nm, nd;
	int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
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
	ny = stoi(sy);
	nm = stoi(sm);
	nd = stoi(sd);

	if (ny < 1900 || ny>2100)return false;
	for (i = 0; i < size_y; i++)
	{
		if (!isdigit(sy[i]))return false;
	}

	if (nm < 1 || nm>12)return false;
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

	if (uru(ny, nm))month[nm]++;
	if (nd<1 || nd>month[nm])return false;
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
bool typecheck2()
{
	int i, size_y, size_m, size_d, size_money, ny, nm, nd;
	int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	string sy, sm, sd, smoney;
	size_y = t_year.text.size();
	size_m = t_month.text.size();
	size_d = t_day.text.size();
	size_money = t_money.text.size();
	if (size_y == 0 || size_m == 0 || size_d == 0 || size_money == 0)
	{
		return false;
	}
	sy = t_year.text.narrow();
	sm = t_month.text.narrow();
	sd = t_day.text.narrow();
	smoney = t_money.text.narrow();
	ny = stoi(sy);
	nm = stoi(sm);
	nd = stoi(sd);
	if (ny < 1900 || ny>2100)return false;
	for (i = 0; i < size_y; i++)
	{
		if (!isdigit(sy[i]))return false;
		if (size_y == 1 && sy[0] == '0')return false;
		if (i == 1 && sy[0] == '0' && sy[1] == '0') return false;
		if (i == 1 && sy[0] == '0' && isalpha(sy[1]) && sy[1] != '0')
		{

			t_month.text.erase(1, 1);
		}
	}

	if (nm < 1 || nm>12)return false;
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
	if (uru(ny, nm))month[nm]++;
	if (nd<1 || nd>month[nm])return false;
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
	for (i = 0; i < size_money; i++)
	{
		if (!isdigit(smoney[i]))return false;
		if (size_money == 1 && smoney[0] == '0')return true;
		if (i == 1 && smoney[0] == '0' && smoney[1] == '0')return false;
		if (i == 1 && smoney[0] == '0' && isalpha(smoney[1]) && smoney[1] != '0')
		{
			t_money.text.erase(1, 1);
		}
	}
	return true;
}
void classsort(int n)
{
	int i, j;
	taihi = sche[n];
	for (i = 0; i < n; i++)
	{
		if (taihi.whatday < sche[i].whatday)
		{
			for (j = n - 1; j >= i;)
			{
				sche[j + 1] = sche[j];
				j--;
			}
			sche[i] = taihi;
			break;
		}
	}
}
void sortup(int n)
{
	int i, j;
	n;
	for (i = 0; i < n/2; i++)
	{
		taihi = sche[i];
		sche[i] = sche[n - i-1];
		sche[n - i-1] = taihi;
	}
}
