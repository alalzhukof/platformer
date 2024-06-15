#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "build/_deps/doctest-src/doctest/doctest.h"
#include "setmenu.hpp"

TEST_CASE("Constructor initializes setMenu correctly")
{
    setMenu sm;

    SUBCASE("pusklever array is initialized correctly")
    {
        for (int i = 0; i < 5; ++i)
        {
            CHECK_FALSE(sm.pusklever[i]);
        }
    }

    SUBCASE("blv array is initialized correctly")
    {
        CHECK(sm.blv[0]);
        for (int i = 1; i < 5; ++i)
        {
            CHECK_FALSE(sm.blv[i]);
        }
    }
}

TEST_CASE("Setting and checking pusklever array in setMenu")
{
    setMenu sm;

    sm.pusklever[2] = true;

    CHECK_FALSE(sm.pusklever[0]);
    CHECK_FALSE(sm.pusklever[1]);
    CHECK(sm.pusklever[2]);
    CHECK_FALSE(sm.pusklever[3]);
    CHECK_FALSE(sm.pusklever[4]);
}

TEST_CASE("Setting and checking blv array in setMenu")
{
    setMenu sm;

    sm.blv[3] = true;

    CHECK(sm.blv[0]);
    CHECK_FALSE(sm.blv[1]);
    CHECK_FALSE(sm.blv[2]);
    CHECK(sm.blv[3]);
    CHECK_FALSE(sm.blv[4]);
}
