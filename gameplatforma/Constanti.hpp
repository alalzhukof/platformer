#ifndef CONSTANTIhpp
#define CONSTANTIhpp
#include "setsound.hpp"

/**
 * @brief Класс, содержащий глобальные константы и переменные для игры.
 *
 * Этот класс используется для хранения глобальных констант, переменных и настроек игры, таких как карты тайлов, звуки, состояние игры и другие параметры.
 */
class Constanti
{
public:
	setSound sound; ///< Объект, содержащий звуковые эффекты.

	float offsetX = 0; ///< Смещение по оси X для камеры.
	float offsetY = 0; ///< Смещение по оси Y для камеры.

	static const int H = 18; ///< Высота карты в тайлах.
	static const int W = 66; ///< Ширина карты в тайлах.

	static const int vr = 60; ///< Примерная частота кадров (возможно, для скорости игры).
	int lv = 1;				  ///< Текущий уровень.

	/**
	 * @brief Карта тайлов.
	 *
	 * Карта, представляющая игровое поле, где каждый символ соответствует определённому типу тайла.
	 */
	String TileMap[18] = {
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
		"A        A   A            3            A            5           BA",
		"A        AC  A            3            A   A       A5          C A",
		"AAAAA    AA  A   A       AAA        A  A  AAAAAAAAAAAAAA      AAAA",
		"A            A  AAAAAAAAAAAAAAAAAAAAA  A   BBB      AB          BA",
		"A          A AA           A            AAAAAAAAAA   A C        C A",
		"A    A  A    A     CCC    A            A            AAXA      AAAA",
		"A  AAAXXAAAAAAAAAAAAAAAA  A A         AA           AAB          BA",
		"A            A           AA AAAAAAAAAAAA   A   CB   A C        C A",
		"A   BBB      A   BB   B   A            A  AAAXXAAXXAAAAA      AAXA",
		"AXAAAAAAAAX  AA  AA A X A A            A            AB          BA",
		"A            A    A       A   X  X  X  AA BBBBB     A C        C A",
		"A            A    A       AAAAAAAAAAA  A       A    AAAA      AAAA",
		"A  A        AA   AA       A            AAAAAAAAAA   AB          BA",
		"A  AAAAAAAAAAAA   A       ABBBB  BBBB  A            A C        C A",
		"A            2    A       A            4 C         AAAAA      AAAA",
		"A      C     2   AAXXXXXXXA         A  4 A          AAAAXXXXXXAAAA",
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	};
	bool play = false, game = false, menu = true, puskgame = false, pob = false, die = false, pause = false;
};

#endif