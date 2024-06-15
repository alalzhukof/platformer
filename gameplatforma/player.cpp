#include "Player.hpp"
#include "setsound.hpp"
#include "Constanti.hpp"
extern Constanti luboe;

Player::Player(Texture &image)
{
    sprite.setTexture(image);
    rect = FloatRect(77, 77 * 2, 77 * 0.9, 65 * 0.9);
    sprite.setTextureRect(IntRect(0, 0, 77, 65));
    sprite.setScale(0.9, 0.9);

    dx = dy = 0;
    curFrame = 0;
    l = 3;
    life = true;
};

/**
 * @brief Обновляет состояние объекта.
 *
 * Эта функция обновляет положение и состояние объекта на основе прошедшего времени.
 * Обрабатывает движение, гравитацию, столкновения, анимацию и состояние жизни объекта.
 *
 * @param time Прошедшее время с момента последнего обновления.
 */
void Player::update(float time)
{
    // Обновление позиции по оси X с учетом времени и скорости
    rect.left += dx * time;
    Collision(0);

    // Если игрок не на земле, увеличиваем скорость падения (гравитация)
    if (!onGround)
        dy += 0.0005 * time;

    // Обновление позиции по оси Y с учетом времени и скорости
    rect.top += dy * time;
    onGround = false; // Сбрасываем флаг на земле
    Collision(1);

    // Если игрок жив
    if (life)
    {
        // Если количество жизней меньше или равно нулю, устанавливаем флаг жизни в false
        if (l <= 0)
            life = false;

        // Обновляем текущий кадр анимации
        curFrame += 0.01 * time;
        if (curFrame > 7)
            curFrame -= 7;

        // Обработка анимации в зависимости от направления движения и состояния прыжка
        if (dx > 0)
        {
            if (dy == 0)
                sprite.setTextureRect(IntRect(77 * int(curFrame), 0, 77, 65));
            else
                sprite.setTextureRect(IntRect(0, 81, 45, 65));

            rig = true; // Игрок направлен вправо
        }
        if (dx < 0)
        {
            if (dy == 0)
                sprite.setTextureRect(IntRect(77 * int(curFrame) + 77, 0, -77, 65));
            else
                sprite.setTextureRect(IntRect(45, 81, -45, 65));

            rig = false; // Игрок направлен влево
        }
    }
    else // Если игрок мертв
    {
        if (rig)
            sprite.setTextureRect(IntRect(156, 104, 82, 30));
        else
            sprite.setTextureRect(IntRect(238, 104, -82, 30));

        luboe.play = false; // Останавливаем игру
        luboe.die = true;   // Устанавливаем флаг смерти
    }

    if (luboe.pob) // Если установлен флаг победы
        sprite.setTextureRect(IntRect(0, 0, 77, 65));

    // Обновление позиции спрайта с учетом смещения карты
    sprite.setPosition(rect.left - luboe.offsetX, rect.top - luboe.offsetY);

    // Сброс скорости по оси X
    dx = 0;
};
/**
 * @brief Обрабатывает столкновения объекта с игровыми тайлами.
 *
 * Эта функция проверяет столкновения объекта с различными тайлами на карте и соответствующим образом обновляет его положение и состояние.
 *
 * @param dir Направление проверки столкновений (0 для горизонтальных, 1 для вертикальных).
 */
void Player::Collision(int dir)
{
    for (int i = rect.top / 77; i < (rect.top + rect.height) / 77; i++)
        for (int j = rect.left / 77; j < (rect.left + rect.width) / 77; j++)
        {
            if (luboe.TileMap[i][j] == 'A' || luboe.TileMap[i][j] == 'K')
            {
                if (dx > 0 && dir == 0)
                    rect.left = j * 77 - rect.width;
                if (dx < 0 && dir == 0)
                    rect.left = j * 77 + 77;
                if (dy > 0 && dir == 1)
                {
                    rect.top = i * 77 - rect.height;
                    dy = 0;
                    onGround = true;
                }
                if (dy < 0 && dir == 1)
                {
                    rect.top = i * 77 + 77;
                    dy = 0;
                }
            }

            if (luboe.TileMap[i][j] == 'B')
                luboe.TileMap[i][j] = ' ';

            if (luboe.TileMap[i][j] == 'C')
            {
                luboe.sound.med.play();
                luboe.TileMap[i][j] = ' ';

                l++;
            }

            if (luboe.TileMap[i][j] == '2' || luboe.TileMap[i][j] == '3' || luboe.TileMap[i][j] == '4' || luboe.TileMap[i][j] == '5')
            {
                rect.left += 77 + 77;

                for (int z = 0; z < luboe.H; z++)
                    luboe.TileMap[z][j] = 'A';

                luboe.pob = true;
                luboe.play = false;
            }

            if (luboe.TileMap[i][j] == 'X')
            {
                if ((dx > 0 && dir == 0) || (dx < 0 && dir == 0) ||
                    (dy > 0 && dir == 1) || (dy < 0 && dir == 1))
                {
                    luboe.sound.smert.play();
                    l--;

                    if (l > 0)
                    {
                        if (i == 10 && j == 10)
                        {
                            if (dy < 0 && dir == 1)
                            {
                                rect.left = 931.7;
                                rect.top = 942.5;
                            }

                            else if (dy > 0 && dir == 1)
                            {
                                rect.left = 584.22;
                                rect.top = 711.5;
                            }
                        }

                        if (i == 16 && j >= 19 && j <= 25)
                        {
                            rect.left = 1362.86;
                            rect.top = 711.5;
                        }

                        if (i == 11 && (j == 30 || j == 33 || j == 36))
                        {
                            rect.left = 2173.41;
                            rect.top = 865.5;
                        }

                        if (i == 9 && (j == 45 || j == 46 || j == 49 || j == 50))
                        {
                            if (dy < 0 && dir == 1)
                            {
                                rect.left = 3626.1;
                                rect.top = 865.5;
                            }

                            else if (dy > 0 && dir == 1)
                            {
                                rect.left = 3311.82;
                                rect.top = 557.5;
                            }
                        }

                        if (i == 16 && j >= 56 && j <= 61)
                        {
                            rect.left = 4081;
                            rect.top = 172.5;
                            luboe.offsetY = 0;
                        }
                    }
                }
            }
        }
}
