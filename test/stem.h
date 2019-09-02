#pragma once

#include <gtest/gtest.h>
#include "../src/nlpxx.h"

using namespace nlpxx::utils;
using namespace nlpxx::stem;

TEST(Stem, Isri)
{
    Isri stemmer;
    ASSERT_EQ(stemmer.stem(U"فقالوا"), U"قال");
}
