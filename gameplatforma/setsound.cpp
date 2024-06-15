#include <SFML/Audio.hpp>
#include "setsound.hpp"

setSound::setSound()
{
    s1.loadFromFile("build/Sound/shooting.ogg");
    s2.loadFromFile("build/Sound/dieenemy.ogg");
    s3.loadFromFile("build/Sound/smert.ogg");
    s4.loadFromFile("build/Sound/med.ogg");

    shooting.setBuffer(s1);
    dieenemy.setBuffer(s2);
    smert.setBuffer(s3);
    med.setBuffer(s4);

    music[0].openFromFile("build/Sound/Play.ogg");
    for (int i = 0; i < 2; i++)
    {
        music[i].setVolume(3);
        music[i].setLoop(true);
    }
}
