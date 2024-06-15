#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "build/_deps/doctest-src/doctest/doctest.h"
#include "Player.hpp"
#include "Constanti.hpp"
#include <SFML/Graphics.hpp>
#include "setsound.hpp"
using namespace sf;

// Глобальная переменная для использования в тестах
Constanti luboe;

TEST_CASE("Player update function test")
{
    sf::Texture texture;
    // Поскольку у нас нет реальной текстуры, просто создадим текстуру заглушку
    texture.create(77, 65);

    Player player(texture);
    player.rect = sf::FloatRect(0, 0, 50, 50);
    player.dx = 0;
    player.dy = 0;

    // Настройка макета карты тайлов без препятствий
    for (int i = 0; i < Constanti::H; i++)
    {
        for (int j = 0; j < Constanti::W; j++)
        {
            luboe.TileMap[i][j] = ' ';
        }
    }

    SUBCASE("Player not on ground")
    {
        player.onGround = false;
        float initialY = player.rect.top;
        float time = 1000; // миллисекунды

        player.update(time);

        // Проверка, что игрок смещается вниз
        CHECK(player.rect.top > initialY);
        // Проверка, что флаг onGround остается false
        CHECK(player.onGround == false);
    }
}
