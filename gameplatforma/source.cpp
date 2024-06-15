#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "setmenu.hpp"
#include "Player.hpp"
#include "setsound.hpp"
#include "Constanti.hpp"
using namespace sf;

Constanti luboe;

/**
 * @class Pulya
 * @brief Представляет снаряд с возможностями движения и столкновения.
 *
 * Класс Pula инкапсулирует свойства и поведение снаряда в игре.
 * Он управляет положением, движением и обнаружением столкновений снаряда.
 */
class Pulya
{
public:
	float dx;		///< Горизонтальная скорость снаряда.
	float dy;		///< Вертикальная скорость снаряда.
	FloatRect rect; ///< Прямоугольник, определяющий положение и размер снаряда.
	int go;			///< Переменная состояния, указывающая на статус движения снаряда.
	Sprite sprite;	///< Спрайт, представляющий снаряд для отображения.

	/**
	 * @brief Конструктор класса Pula.
	 *
	 * Инициализирует объект Pula с заданной текстурой, устанавливая начальные скорости в 0 и go в 0.
	 *
	 * @param image Ссылка на текстуру, которая будет использоваться для спрайта снаряда.
	 */
	Pulya(Texture &image)
	{
		sprite.setTexture(image);
		dx = dy = 0;
		go = 0;
	}

	/**
	 * @brief Обновляет положение и состояние снаряда.
	 *
	 * Обновляет положение снаряда на основе его скорости и прошедшего времени.
	 * Также обрабатывает обнаружение столкновений.
	 *
	 * @param time Прошедшее время с момента последнего обновления.
	 */
	void update(float time)
	{
		rect.left += dx * time;
		Collision(0);

		rect.top += dy * time;
		Collision(1);

		sprite.setPosition(rect.left - luboe.offsetX, rect.top - luboe.offsetY);
	}

	/**
	 * @brief Обрабатывает обнаружение столкновений и реакцию на них для снаряда.
	 *
	 * Проверяет столкновения с определенными типами тайлов в карте тайлов и соответственно обновляет состояние снаряда.
	 *
	 * @param dir Направление проверки столкновений (0 для горизонтальных, 1 для вертикальных).
	 */
	void Collision(int dir)
	{
		for (int i = rect.top / 77; i < (rect.top + rect.height) / 77; i++)
			for (int j = rect.left / 77; j < (rect.left + rect.width) / 77; j++)
				if (luboe.TileMap[i][j] == 'A' || luboe.TileMap[i][j] == 'K' || luboe.TileMap[i][j] == '2' ||
					luboe.TileMap[i][j] == '3' || luboe.TileMap[i][j] == '4' || luboe.TileMap[i][j] == '5')
					if ((dx > 0 && dir == 0) || (dx < 0 && dir == 0))
						go = 0;
	}
};

/**
 * @brief Класс, представляющий врага.
 *
 * Этот класс содержит всю информацию и методы, необходимые для управления врагом в игре.
 */
class Enemy
{
public:
	float dx, dy;	///< Скорость врага по осям X и Y
	FloatRect rect; ///< Прямоугольник, представляющий границы врага
	Sprite sprite;	///< Спрайт врага
	float curFrame; ///< Текущий кадр анимации
	bool life;		///< Флаг состояния жизни врага

	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		sprite.setScale(0.38, 0.38);
		rect = FloatRect(x, y, 77, 77);

		dx = 0.3;
		curFrame = 0;
		life = false;
	}

	void update(float time)
	{
		if (!luboe.pause)
		{
			rect.left += dx * time;

			Collision();

			if (dx > 0)
				sprite.setTextureRect(IntRect(165 * int(curFrame), 0, 165, 204));
			else if (dx < 0)
				sprite.setTextureRect(IntRect(165 * int(curFrame) + 165, 0, -165, 204));
			if (!life)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
		}

		sprite.setPosition(rect.left - luboe.offsetX, rect.top - luboe.offsetY);
	}

	void Collision()
	{
		for (int i = rect.top / 77; i < (rect.top + rect.height) / 77; i++)
			for (int j = rect.left / 77; j < (rect.left + rect.width) / 77; j++)
				if (luboe.TileMap[i][j] == 'A')
				{
					if (dx > 0)
					{
						rect.left = j * 77 - rect.width;
						dx *= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 77 + 77;
						dx *= -1;
					}
				}
	}
};

/**
 * @brief Класс, представляющий босса.
 *
 * Этот класс содержит всю информацию и методы, необходимые для управления боссом в игре.
 */
class Boss
{
public:
	float dx, dy;	///< Скорость босса по осям X и Y
	FloatRect rect; ///< Прямоугольник, представляющий границы босса
	Sprite sprite;	///< Спрайт босса
	float curFrame; ///< Текущий кадр анимации
	bool life;		///< Флаг состояния жизни босса
	bool rig;		///< Направление взгляда босса (true - вправо, false - влево)
	int l;			///< Количество жизней босса
	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		sprite.setScale(1.5, 1.5);
		rect = FloatRect(x, y, 77, 77);

		dy = 0.2;
		curFrame = 0;
		life = false;
		rig = true;
		l = 10;
	}

	void update(float time)
	{
		if (!luboe.pause)
		{
			rect.top += dy * time;

			Collision();
		}

		if (life && l == 0)
		{
			life = false;

			sprite.setTextureRect(IntRect(0, 0, 0, 0));

			luboe.pob = true;
			luboe.play = false;
		}

		sprite.setPosition(rect.left - luboe.offsetX, rect.top - luboe.offsetY);
	}

	void Collision()
	{
		for (int i = rect.top / 77; i < (rect.top + rect.height) / 77; i++)
			for (int j = rect.left / 77; j < (rect.left + rect.width) / 77; j++)
				if (luboe.TileMap[i][j] == 'A')
				{
					if (dy > 0)
					{
						rect.top = i * 77 - rect.height;
						dy *= -1;
					}
					else if (dy < 0)
					{
						rect.top = i * 77 + 77;
						dy *= -1;
					}
				}
	}
};

/**
 * @brief Класс, представляющий пулю босса.
 *
 * Этот класс содержит всю информацию и методы, необходимые для управления пулей босса в игре.
 */
class PulaBoss
{
public:
	float dx, dy;	///< Скорость пули по осям X и Y.
	FloatRect rect; ///< Прямоугольник, представляющий границы пули.
	int go;			///< Направление движения пули.
	Sprite sprite;	///< Спрайт пули.

	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		dx = dy = 0;
		go = 0;
	}

	void update(float time)
	{
		if (!luboe.pause)
			rect.left += dx * time;
		Collision();

		if (!luboe.pause)
			rect.top += dy * time;

		sprite.setPosition(rect.left - luboe.offsetX, rect.top - luboe.offsetY);
	}

	void Collision()
	{
		for (int i = rect.top / 77; i < (rect.top + rect.height) / 77; i++)
			for (int j = rect.left / 77; j < (rect.left + rect.width) / 77; j++)
				if (luboe.TileMap[i][j] == 'A')
				{
					if (dx > 0)
					{
						rect.left = j * 77 - rect.width;
						go = 0;
					}
					else if (dx < 0)
					{
						rect.left = j * 77 + 77;
						go = 0;
					}
				}
	}
};

/**
 * @brief Главная функция программы.
 *
 * Функция создает окно, загружает текстуры, создает объекты игры и обрабатывает игровой цикл.
 * @return int Код завершения программы.
 */
int main()
{
	RenderWindow window(VideoMode(1000, 500), "Mega igra!");

	Texture f; /**< Текстура фона */
	f.loadFromFile("Play/fon.png");
	Sprite fon(f); /**< Спрайт фона */

	Texture Picture; /**< Текстура игрока */
	Picture.loadFromFile("Play/man.png");
	Player p(Picture); /**< Объект игрока */
	int frame = 0;	   /**< Текущий кадр анимации */

	Clock clock; /**< Часы для измерения времени между кадрами */

	Texture t2; /**< Текстура платформы */
	t2.loadFromFile("Play/plat.png");
	Sprite plat(t2); /**< Спрайт платформы */

	Texture t1; /**< Текстура пули */
	t1.loadFromFile("Play/pulya1.png");
	Pulya pu(t1); /**< Объект пули */

	Texture t3; /**< Текстура врага */
	t3.loadFromFile("Play/enemy.png");
	Enemy enemy[luboe.vr]; /**< Массив врагов */
	enemy[0].set(t3, 4 * 77, 13 * 77);
	for (int i = 1; i < 4; i++)
		enemy[i].set(t3, (18 + (i - 1)) * 77, 3 * 77);
	for (int i = 4; i < 9; i++)
		enemy[i].set(t3, (28 + (i - 4)) * 77, 3 * 77);
	for (int i = 9; i < 16; i++)
		enemy[i].set(t3, (29 + (i - 9)) * 77, 7 * 77);
	for (int i = 16; i < 26; i++)
		enemy[i].set(t3, (27 + (i - 16)) * 77, 16 * 77);
	for (int i = 26; i < 36; i++)
		enemy[i].set(t3, (42 + (i - 26)) * 77, 16 * 77);
	for (int i = 36; i < 44; i++)
		enemy[i].set(t3, (40 + (i - 36)) * 77, 12 * 77);
	for (int i = 44; i < 53; i++)
		enemy[i].set(t3, (44 + (i - 44)) * 77, 8 * 77);
	for (int i = 53; i < 60; i++)
		enemy[i].set(t3, (44 + (i - 53)) * 77, 2 * 77);

	Texture t4; /**< Текстура босса */
	t4.loadFromFile("Play/Boss.png");
	Boss boss; /**< Объект босса */
	boss.set(t4, 59 * 77, 77);

	Texture t5; /**< Текстура пули босса */
	t5.loadFromFile("Play/pulyaBoss.png");
	PulaBoss puBos; /**< Объект пули босса */
	puBos.set(t5, 59 * 77, 77);

	Sprite lifeBoss[10]; /**< Спрайты жизней босса */
	for (int i = 0; i < 10; i++)
	{
		lifeBoss[i].setTexture(t4);
		lifeBoss[i].setScale(0.5, 0.5);
		lifeBoss[i].setPosition(60 * i, 60);
	}

	Texture nl; /**< Текстура надписи над уровнем */
	nl.loadFromFile("Play/nadlev.png");
	Sprite nadlev(nl); /**< Спрайт надписи над уровнем */
	nadlev.setPosition(700, 0);

	Texture sc; /**< Текстура очков */
	sc.loadFromFile("Play/score.png");
	Sprite score(sc); /**< Спрайт очков */
	score.setTextureRect(IntRect(0, 0, 27, 36));
	score.setPosition(950, 5);

	Texture tl; /**< Текстура жизни */
	tl.loadFromFile("Play/heart.png");
	Sprite life[12]; /**< Спрайты жизней игрока */
	for (int i = 0; i < 12; i++)
	{
		life[i].setTexture(tl);
		life[i].setScale(1.5, 1.5);
		life[i].setPosition(5 + 50 * i, 5);
	}

	setMenu sm; /**< Объект меню */

	Texture m1; /**< Текстура названия */
	m1.loadFromFile("Menu/naz.png");
	Sprite naz(m1); /**< Спрайт названия */
	naz.setPosition(200, 50);

	Texture m2; /**< Текстура кнопки "Играть" */
	m2.loadFromFile("Menu/butplay.png");
	Sprite butplay(m2); /**< Спрайт кнопки "Играть" */
	butplay.setPosition(200, 235);

	Texture m3; /**< Текстура кнопки "Выход" */
	m3.loadFromFile("Menu/exit.png");
	Sprite exit(m3); /**< Спрайт кнопки "Выход" */
	exit.setPosition(600, 235);

	Texture m4; /**< Текстура названия уровней */
	m4.loadFromFile("Menu/nazurav.png");
	Sprite nazurav(m4); /**< Спрайт названия уровней */
	nazurav.setPosition(350, 10);

	Texture m5; /**< Текстура кнопок выбора уровня */
	m5.loadFromFile("Menu/butlev.png");
	Sprite butlev[5]; /**< Спрайты кнопок выбора уровня */
	for (int i = 0; i < 5; i++)
	{
		butlev[i].setTexture(m5);
		butlev[i].setPosition(150 + 150 * i, 230);
		butlev[i].setTextureRect(IntRect(0, 0, 80, 80));
	}
	butlev[0].setTextureRect(IntRect(0, 80, 80, 80));

	Texture m6; /**< Текстура кнопки "Назад" */
	m6.loadFromFile("Menu/back.png");
	Sprite back(m6); /**< Спрайт кнопки "Назад" */
	back.setPosition(150, 400);

	Texture m7; /**< Текстура экрана победы */
	m7.loadFromFile("Menu/win.png");
	Sprite win(m7); /**< Спрайт экрана победы */
	win.setPosition(300, 100);

	Texture m8; /**< Текстура экрана повышения уровня */
	m8.loadFromFile("Menu/urpro.png");
	Sprite urpro(m8); /**< Спрайт экрана повышения уровня */
	urpro.setPosition(300, 100);

	Texture m9; /**< Текстура кнопки перехода к следующему уровню */
	m9.loadFromFile("Menu/sledur.png");
	Sprite sledur(m9); /**< Спрайт кнопки перехода к следующему уровню */
	sledur.setPosition(500, 250);

	Texture m10; /**< Текстура кнопки "Начать заново" */
	m10.loadFromFile("Menu/naczan.png");
	Sprite naczan(m10); /**< Спрайт кнопки "Начать заново" */
	naczan.setPosition(200, 250);

	Texture m11; /**< Текстура кнопки меню */
	m11.loadFromFile("Menu/butmen.png");
	Sprite butmen(m11); /**< Спрайт кнопки меню */
	butmen.setPosition(400, 350);

	Texture m12; /**< Текстура кнопки выхода */
	m12.loadFromFile("Menu/ki.png");
	Sprite ki(m12); /**< Спрайт кнопки выхода */
	ki.setPosition(400, 100);

	Texture m13; /**< Текстура надписи "Пауза" */
	m13.loadFromFile("Menu/nadpause.png");
	Sprite nadpause(m13); /**< Спрайт надписи "Пауза" */
	nadpause.setPosition(400, 100);

	Texture m14; /**< Текстура кнопки продолжения игры */
	m14.loadFromFile("Menu/nadprod.png");
	Sprite nadprod(m14); /**< Спрайт кнопки продолжения игры */
	nadprod.setPosition(600, 250);

	nadprod.setScale(0.7, 0.7);

	Texture m15; /**< Текстура экрана выбора уровня */
	m15.loadFromFile("Menu/level.png");
	Sprite level(m15); /**< Спрайт экрана выбора уровня */
	level.setPosition(400, 100);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(window);

					if (luboe.menu)
					{
						if (pos.x >= 600 && pos.x <= 774 &&
							pos.y >= 235 && pos.y <= 306)
							window.close();

						if (pos.x >= 200 && pos.x <= 392 &&
							pos.y >= 235 && pos.y <= 302)
						{
							luboe.menu = false;
							luboe.game = true;
						}
					}

					else if (luboe.game)
					{
						if (pos.x >= 150 && pos.x <= 273 &&
							pos.y >= 400 && pos.y <= 448)
						{
							luboe.game = false;
							luboe.menu = true;
						}

						for (int i = 0; i < 5; i++)
							if (pos.x >= 150 + 150 * i && pos.x <= 230 + 150 * i &&
								pos.y >= 230 && pos.y <= 310 && sm.blv[i])
							{
								luboe.puskgame = true;
								sm.pusklever[i] = true;
							}
					}

					else if (luboe.pob || luboe.die || luboe.pause)
					{
						if (pos.x >= 200 && pos.x <= 428 &&
							pos.y >= 250 && pos.y <= 291)
						{
							luboe.pob = false;
							luboe.puskgame = true;
							luboe.pause = false;
						}

						if (pos.x >= 500 && pos.x <= 856 &&
							pos.y >= 250 && pos.y <= 293 && luboe.lv < 5 && !luboe.die && !luboe.pause)
						{
							luboe.pob = false;
							luboe.puskgame = true;
							luboe.die = false;

							sm.pusklever[luboe.lv - 1] = false;
							sm.pusklever[luboe.lv] = true;
						}

						if (pos.x >= 600 && pos.x <= 872 &&
							pos.y >= 250 && pos.y <= 290 && luboe.pause)
							luboe.pause = false;

						if (pos.x >= 400 && pos.x <= 685 &&
							pos.y >= 350 && pos.y <= 382)
						{
							luboe.pob = false;
							luboe.menu = true;
							luboe.play = false;
							luboe.die = false;
							luboe.pause = false;

							p.l = 3;
							p.life = true;

							p.sprite.setTextureRect(IntRect(0, 0, 77, 65));

							for (int i = 0; i < 5; i++)
								sm.pusklever[i] = false;

							luboe.offsetX = 0;
							luboe.offsetY = 0;

							p.rect.left = 77;
							p.rect.top = 172.5;
						}
					}
				}
		}

		// std::cout << enemy[0].dx << "\n";

		if (luboe.pob)
			sm.blv[luboe.lv] = true;

		if (sm.blv[1])
			butlev[1].setTextureRect(IntRect(80, 80, 80, 80));
		if (sm.blv[2])
			butlev[2].setTextureRect(IntRect(80 * 2, 80, 80, 80));
		if (sm.blv[3])
			butlev[3].setTextureRect(IntRect(80 * 3, 80, 80, 80));
		if (sm.blv[4])
			butlev[4].setTextureRect(IntRect(0, 80 * 2, 80, 80));

		if (luboe.puskgame)
		{
			luboe.sound.music[0].play();
			luboe.sound.music[0].setVolume(3);

			luboe.puskgame = false;
			luboe.game = false;
			luboe.pob = false;
			luboe.die = false;

			if (sm.pusklever[0])
			{
				luboe.lv = 1;

				luboe.offsetX = 0;
				luboe.offsetY = 0;

				p.rect.left = 77;
				p.rect.top = 172.5;

				enemy[0].life = true;

				for (int i = 4; i < 7; i++)
					luboe.TileMap[9][i] = 'B';
				luboe.TileMap[16][7] = 'C';
				for (int i = 15; i < 17; i++)
					luboe.TileMap[i][13] = '2';
			}

			if (sm.pusklever[1])
			{
				luboe.lv = 2;

				p.rect.left = 1098.39;
				p.rect.top = 1250.5;

				luboe.offsetX = p.rect.left;
				luboe.offsetY = p.rect.top - 365;

				for (int i = 1; i < 4; i++)
					enemy[i].life = true;

				for (int i = 15; i < 17; i++)
					luboe.TileMap[i][13] = 'A';
				luboe.TileMap[9][14] = 'B';
				for (int i = 17; i < 19; i++)
					luboe.TileMap[9][i] = 'B';
				luboe.TileMap[9][22] = 'B';
				for (int i = 19; i < 22; i++)
					luboe.TileMap[6][i] = 'C';
				luboe.TileMap[3][14] = 'B';
				for (int i = 1; i < 3; i++)
					luboe.TileMap[i][26] = '3';
			}

			if (sm.pusklever[2])
			{
				luboe.lv = 3;

				p.rect.left = 2079;
				p.rect.top = 172.5;

				luboe.offsetX = p.rect.left + 500;
				luboe.offsetY = 0;

				for (int i = 4; i < 9; i++)
					enemy[i].life = true;
				for (int i = 9; i < 16; i++)
					enemy[i].life = true;
				for (int i = 16; i < 26; i++)
					enemy[i].life = true;

				for (int i = 1; i < 3; i++)
					luboe.TileMap[i][26] = 'A';
				for (int i = 28; i < 30; i++)
					luboe.TileMap[2][i] = 'B';
				for (int i = 31; i < 33; i++)
					luboe.TileMap[2][i] = 'B';
				for (int i = 34; i < 36; i++)
					luboe.TileMap[2][i] = 'B';
				for (int i = 29; i < 32; i++)
					luboe.TileMap[6][i] = 'B';
				for (int i = 33; i < 36; i++)
					luboe.TileMap[6][i] = 'B';
				for (int i = 27; i < 29; i++)
					luboe.TileMap[11][i] = 'C';
				for (int i = 31; i < 33; i++)
					luboe.TileMap[11][i] = 'B';
				for (int i = 34; i < 36; i++)
					luboe.TileMap[11][i] = 'C';
				for (int i = 27; i < 31; i++)
					luboe.TileMap[14][i] = 'B';
				for (int i = 32; i < 36; i++)
					luboe.TileMap[14][i] = 'B';
				for (int i = 15; i < 17; i++)
					luboe.TileMap[i][39] = '4';
			}

			if (sm.pusklever[3])
			{
				luboe.lv = 4;

				p.rect.left = 3080;
				p.rect.top = 1250.5;

				luboe.offsetX = p.rect.left;
				luboe.offsetY = p.rect.top - 365;

				for (int i = 26; i < 36; i++)
					enemy[i].life = true;
				for (int i = 36; i < 44; i++)
					enemy[i].life = true;
				for (int i = 44; i < 53; i++)
					enemy[i].life = true;
				for (int i = 53; i < 60; i++)
					enemy[i].life = true;
				for (int i = 15; i < 17; i++)
					luboe.TileMap[i][39] = 'A';
				luboe.TileMap[15][41] = 'C';
				for (int i = 42; i < 46; i++)
					luboe.TileMap[11][i] = 'B';
				luboe.TileMap[8][47] = 'C';
				luboe.TileMap[8][48] = 'B';
				for (int i = 43; i < 46; i++)
					luboe.TileMap[4][i] = 'B';
				for (int i = 1; i < 3; i++)
					luboe.TileMap[i][52] = '5';
			}

			if (sm.pusklever[4])
			{
				luboe.lv = 5;

				boss.life = true;
				boss.l = 10;

				p.rect.left = 4112.69;
				p.rect.top = 172.5;

				for (int i = 1; i < 3; i++)
					luboe.TileMap[i][52] = 'A';
				for (int i = 0; i < 4; i++)
				{
					luboe.TileMap[4 + 3 * i][53] = 'B';
					luboe.TileMap[5 + 3 * i][54] = 'C';
				}
				for (int i = 0; i < 5; i++)
				{
					luboe.TileMap[2 + 3 * i][63] = 'C';
					luboe.TileMap[1 + 3 * i][64] = 'B';
				}
			}

			p.l = 3;
			p.life = true;

			luboe.play = true;
		}

		if (p.life && luboe.play && !luboe.pause)
		{

			if (Keyboard::isKeyPressed(Keyboard::A))
				p.dx = -0.3;
			if (Keyboard::isKeyPressed(Keyboard::D))
				p.dx = 0.3;
			if (Keyboard::isKeyPressed(Keyboard::W))
				if (p.onGround)
				{
					p.dy = -0.5;

					if (p.rig)
						p.sprite.setTextureRect(IntRect(0, 81, 45, 65));
					else if (!p.rig)
						p.sprite.setTextureRect(IntRect(45, 81, -45, 65));

					p.onGround = false;
				}
			if (Keyboard::isKeyPressed(Keyboard::Space))
				if (p.onGround && pu.go == 0)
				{
					luboe.sound.shooting.play();

					frame = 100;

					if (p.rig)
					{
						pu.go = 1;

						pu.rect.left = p.rect.left + 67;
						pu.rect.top = p.rect.top + 20;
					}
					else
					{
						pu.go = 2;

						pu.rect.left = p.rect.left - 12;
						pu.rect.top = p.rect.top + 18;
					}
				}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
				luboe.pause = true;
		}

		if (pu.go == 0)
		{
			pu.rect.left = p.rect.left;
			pu.rect.top = p.rect.top;
		}
		else if (pu.go == 1)
			pu.dx = 2;
		else if (pu.go == 2)
			pu.dx = -2;

		if (frame != 0)
			if (p.dy == 0)
			{
				if (p.rig)
					p.sprite.setTextureRect(IntRect(68, 80, 69, 61));
				else if (!p.rig)
					p.sprite.setTextureRect(IntRect(68 + 69, 80, -69, 61));

				frame--;
			}

		for (int i = 0; i < luboe.vr; i++)
			if (enemy[i].life)
			{
				if (p.rect.intersects(enemy[i].rect))
				{
					luboe.sound.smert.play();
					p.l--;

					if (p.l > 0)
					{
						if (i == 0)
						{
							p.rect.left = 931.7;
							p.rect.top = 942.5;
						}
						else if (i >= 1 && i < 4)
						{
							p.rect.left = 1312.52;
							p.rect.top = 172.5;
						}
						else if (i >= 4 && i < 9)
						{
							p.rect.left = 2093.68;
							p.rect.top = 172.5;
						}
						else if (i >= 9 && i < 16)
						{
							p.rect.left = 2933.7;
							p.rect.top = 480.5;
						}
						else if (i >= 16 && i < 26)
						{
							p.rect.left = 2775.62;
							p.rect.top = 1173.5;
						}
						else if (i >= 26 && i < 36)
						{
							p.rect.left = 3176.79;
							p.rect.top = 1173.5;
						}
						else if (i >= 36 && i < 44)
						{
							p.rect.left = 3615.72;
							p.rect.top = 865.5;
						}
						else if (i >= 44 && i < 53)
						{
							p.rect.left = 3330.41;
							p.rect.top = 557.5;
						}
						else if (i >= 53 && i < 60)
						{
							p.rect.left = 3309.64;
							p.rect.top = 95.5;
						}
					}
				}

				if (enemy[i].rect.left < pu.rect.left && enemy[i].rect.left + 10 > pu.rect.left &&
					enemy[i].rect.top < pu.rect.top && enemy[i].rect.top + 50 > pu.rect.top && pu.go != 0)
				{
					luboe.sound.dieenemy.play();
					enemy[i].life = false;

					pu.go = 0;
				}
			}

		if (!enemy[0].life)
		{
			luboe.TileMap[11][3] = ' ';
			luboe.TileMap[12][3] = ' ';
		}
		else if (enemy[0].life)
		{
			luboe.TileMap[11][3] = 'K';
			luboe.TileMap[12][3] = 'K';
		}
		if (!enemy[1].life && !enemy[2].life && !enemy[3].life)
		{
			luboe.TileMap[1][25] = ' ';
			luboe.TileMap[2][25] = ' ';
		}
		else if (enemy[1].life && enemy[2].life && enemy[3].life)
		{
			luboe.TileMap[1][25] = 'K';
			luboe.TileMap[2][25] = 'K';
		}
		if (!enemy[4].life && !enemy[5].life && !enemy[6].life && !enemy[7].life && !enemy[8].life)
		{
			luboe.TileMap[1][36] = ' ';
			luboe.TileMap[2][36] = ' ';
		}
		else if (enemy[4].life && enemy[5].life && enemy[6].life && enemy[7].life && enemy[8].life)
		{
			luboe.TileMap[1][36] = 'K';
			luboe.TileMap[2][36] = 'K';
		}
		if (!enemy[9].life && !enemy[10].life && !enemy[10].life && !enemy[11].life && !enemy[12].life &&
			!enemy[13].life && !enemy[14].life && !enemy[15].life)
		{
			luboe.TileMap[5][28] = ' ';
			luboe.TileMap[6][28] = ' ';
		}
		else if (enemy[9].life && enemy[10].life && enemy[10].life && enemy[11].life && enemy[12].life &&
				 enemy[13].life && enemy[14].life && enemy[15].life)
		{
			luboe.TileMap[5][28] = 'K';
			luboe.TileMap[6][28] = 'K';
		}
		if (!enemy[16].life && !enemy[17].life && !enemy[18].life && !enemy[19].life && !enemy[20].life &&
			!enemy[21].life && !enemy[22].life && !enemy[23].life && !enemy[24].life && !enemy[25].life)
		{
			luboe.TileMap[15][38] = ' ';
			luboe.TileMap[16][38] = ' ';
		}
		else if (enemy[16].life && enemy[17].life && enemy[18].life && enemy[19].life && enemy[20].life &&
				 enemy[21].life && enemy[22].life && enemy[23].life && enemy[24].life && enemy[25].life)
		{
			luboe.TileMap[15][38] = 'K';
			luboe.TileMap[16][38] = 'K';
		}
		if (!enemy[26].life && !enemy[27].life && !enemy[28].life && !enemy[29].life && !enemy[30].life &&
			!enemy[31].life && !enemy[32].life && !enemy[33].life && !enemy[34].life && !enemy[35].life)
		{
			luboe.TileMap[13][49] = ' ';
			luboe.TileMap[13][50] = ' ';
			luboe.TileMap[13][51] = ' ';
		}
		else if (enemy[26].life && enemy[27].life && enemy[28].life && enemy[29].life && enemy[30].life &&
				 enemy[31].life && enemy[32].life && enemy[33].life && enemy[34].life && enemy[35].life)
		{
			luboe.TileMap[13][49] = 'K';
			luboe.TileMap[13][50] = 'K';
			luboe.TileMap[13][51] = 'K';
		}
		if (!enemy[36].life && !enemy[37].life && !enemy[38].life && !enemy[39].life && !enemy[40].life &&
			!enemy[41].life && !enemy[42].life && !enemy[43].life)
		{
			luboe.TileMap[9][40] = ' ';
			luboe.TileMap[9][41] = ' ';
		}
		else if (enemy[36].life && enemy[37].life && enemy[38].life && enemy[39].life && enemy[40].life &&
				 enemy[41].life && enemy[42].life && enemy[43].life)
		{
			luboe.TileMap[9][40] = 'K';
			luboe.TileMap[9][41] = 'K';
		}
		if (!enemy[44].life && !enemy[45].life && !enemy[46].life && !enemy[47].life &&
			!enemy[48].life && !enemy[49].life && !enemy[50].life)
		{
			luboe.TileMap[5][49] = ' ';
			luboe.TileMap[5][50] = ' ';
			luboe.TileMap[5][51] = ' ';
		}
		else if (enemy[44].life && enemy[45].life && enemy[46].life && enemy[47].life &&
				 enemy[48].life && enemy[49].life && enemy[50].life)
		{
			luboe.TileMap[5][49] = 'K';
			luboe.TileMap[5][50] = 'K';
			luboe.TileMap[5][51] = 'K';
		}
		if (!enemy[53].life && !enemy[54].life && !enemy[55].life && !enemy[56].life && !enemy[57].life &&
			!enemy[58].life && !enemy[59].life)
			luboe.TileMap[1][51] = ' ';
		else if (enemy[53].life && enemy[54].life && enemy[55].life && enemy[56].life && enemy[57].life &&
				 enemy[58].life && enemy[59].life)
			luboe.TileMap[1][51] = 'K';

		score.setTextureRect(IntRect(27 * (luboe.lv - 1), 0, 27, 36));

		if (boss.life)
		{
			if (boss.rect.left < p.rect.left)
			{
				boss.sprite.setTextureRect(IntRect(0, 0, 102, 51));
				boss.rig = true;
			}
			else if (boss.rect.left > p.rect.left)
			{
				boss.sprite.setTextureRect(IntRect(102, 0, -102, 51));
				boss.rig = false;
			}

			if (boss.rect.top > p.rect.top && boss.rect.top < p.rect.top + p.rect.height &&
				puBos.go == 0 && luboe.lv == 5)
			{
				if (boss.rig)
					puBos.go = 1;
				else
					puBos.go = 2;
			}

			if (puBos.go == 0)
			{
				if (boss.rig)
				{
					puBos.rect.left = boss.rect.left + 153;
					puBos.rect.top = boss.rect.top;
				}
				else if (!boss.rig)
				{
					puBos.rect.left = boss.rect.left;
					puBos.rect.top = boss.rect.top;
				}
			}
			else if (puBos.go == 1)
				puBos.dx = 1;
			else if (puBos.go == 2)
				puBos.dx = -1;

			if (boss.rect.left < pu.rect.left && boss.rect.left + 153 > pu.rect.left && boss.life &&
				boss.rect.top < pu.rect.top && boss.rect.top + 77 > pu.rect.top && pu.go != 0)
			{
				luboe.sound.dieenemy.play();
				boss.l--;

				pu.go = 0;
			}

			if (p.rect.intersects(boss.rect))
			{
				luboe.sound.smert.play();
				p.l--;

				if (p.l > 0)
				{
					p.rect.left = 4081;
					p.rect.top = 172.5;
					luboe.offsetY = 0;
				}
			}

			if (p.rect.left < puBos.rect.left && p.rect.left + 77 > puBos.rect.left && p.life &&
				p.rect.top < puBos.rect.top && p.rect.top + 65 > puBos.rect.top && puBos.go != 0)
			{
				luboe.sound.smert.play();
				p.l--;

				p.rect.left = 4081;
				p.rect.top = 172.5;
				luboe.offsetY = 0;
			}
		}

		if (p.rect.left > 500 && p.rect.left < 4582)
			luboe.offsetX = p.rect.left - 500;
		if (p.rect.top > 250 && p.rect.top < 1135)
			luboe.offsetY = p.rect.top - 250;

		p.update(time);
		pu.update(time);
		boss.update(time);
		puBos.update(time);
		window.clear(Color::White);

		fon.setPosition(-luboe.offsetX, -luboe.offsetY);
		window.draw(fon);

		for (int i = 0; i < luboe.H; i++)
			for (int j = 0; j < luboe.W; j++)
			{
				if (luboe.TileMap[i][j] == 'A')
					plat.setTextureRect(IntRect(0, 0, 77, 77));
				if (luboe.TileMap[i][j] == 'B')
					plat.setTextureRect(IntRect(77, 0, 77, 77));
				if (luboe.TileMap[i][j] == 'C')
					plat.setTextureRect(IntRect(77 * 2, 0, 77, 77));
				if (luboe.TileMap[i][j] == 'X')
					plat.setTextureRect(IntRect(77 * 3, 0, 77, 77));
				if (luboe.TileMap[i][j] == 'K')
					plat.setTextureRect(IntRect(77 * 4, 0, 77, 77));
				if (luboe.TileMap[i][j] == '2')
					plat.setTextureRect(IntRect(0, 77, 77, 77));
				if (luboe.TileMap[i][j] == '3')
					plat.setTextureRect(IntRect(77, 77, 77, 77));
				if (luboe.TileMap[i][j] == '4')
					plat.setTextureRect(IntRect(77 * 2, 77, 77, 77));
				if (luboe.TileMap[i][j] == '5')
					plat.setTextureRect(IntRect(77 * 3, 77, 77, 77));
				if (luboe.TileMap[i][j] == ' ')
					continue;

				plat.setPosition(j * 77 - luboe.offsetX, i * 77 - luboe.offsetY);
				window.draw(plat);
			}

		window.draw(p.sprite);
		if (pu.go != 0)
			window.draw(pu.sprite);
		for (int i = 0; i < luboe.vr; i++)
			enemy[i].update(time);
		for (int i = 0; i < luboe.vr; i++)
			window.draw(enemy[i].sprite);
		window.draw(boss.sprite);
		if (puBos.go != 0)
			window.draw(puBos.sprite);
		for (int i = 0; i < boss.l; i++)
			if (luboe.lv == 5)
				window.draw(lifeBoss[i]);

		if (luboe.play || luboe.pob || luboe.die || luboe.pause)
		{
			window.draw(nadlev);
			window.draw(score);
			for (int i = 0; i < p.l; i++)
				window.draw(life[i]);

			if (luboe.pob || luboe.die || luboe.pause)
			{
				if (luboe.pob && !luboe.die && !luboe.pause)
				{
					if (luboe.lv < 5)
						window.draw(urpro);
					else
						window.draw(win);
				}
				else if (!luboe.pob && luboe.die && !luboe.pause)
					window.draw(ki);
				else if (!luboe.pob && !luboe.die && luboe.pause)
					window.draw(nadpause);

				if (luboe.lv < 5 && !luboe.die && !luboe.pause)
					window.draw(sledur);
				else if (luboe.pause)
					window.draw(nadprod);

				window.draw(naczan);
				window.draw(butmen);
			}
		}

		if (luboe.menu)
		{
			window.draw(naz);
			window.draw(butplay);
			window.draw(exit);
		}

		if (luboe.game)
		{
			window.draw(nazurav);
			for (int i = 0; i < 5; i++)
				window.draw(butlev[i]);
			window.draw(back);
		}

		window.display();
	}

	return 0;
}