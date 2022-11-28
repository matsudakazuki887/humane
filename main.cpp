# include <Siv3D.hpp>

void Main()
{
	// 背景色を ColorF{ 0.3, 0.6, 1.0 } に設定
	Scene::SetBackground(Palette::White);
	int i = 0,j=1;
	int calendar_x1 = 38, calendar_y1 = 30, calendar_x2 = 714, calendar_y2 = 450;
	const Texture texture{ U"example/133540.png" };
	const Font font13{ 13 }, font10{ 12, Typeface::Black };

	while (System::Update())
	{
		Rect{ calendar_x1, calendar_y1, calendar_x2, calendar_y2 }
		.drawFrame(1, 0, Palette::Black);
		for (i = 1; i <= 6; i++)
		{
			Line{ 102 * i + 38, 31, 102 * i + 38 ,479 }.draw(0.5, Palette::Silver);
			Line{ 38, 75 * i + 30 , 714 + 38 ,75 * i + 30 }.draw(0.5, Palette::Silver);
		}

		for (i = 1; i < 30; i++)
		{
			font13(i).draw(102*((i-1)%7)+42, 75*j+32, Palette::Black);
			if (i % 7 == 0)j++;
		}
		j = 0;
		Rect{ 41, 48, 97, 13 }.draw(Palette::Skyblue);
		font10(U"キャベツ").draw(41, 45, Palette::White);
	}
}
