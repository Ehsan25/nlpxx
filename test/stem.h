#pragma once

#include <gtest/gtest.h>
#include "../src/nlpxx.h"

using namespace nlpxx::utils;
using namespace nlpxx::stem;

TEST(Stem, Isri)
{
    Isri stemmer;

    EXPECT_EQ(stemmer.stem(U"الْعَرَبِــــــيَّة"), U"عربــــــية");
    EXPECT_EQ(stemmer.stem(U"العربية"), U"عرب");
    EXPECT_EQ(stemmer.stem(U"فقالوا"), U"فقل");
    EXPECT_EQ(stemmer.stem(U"الطالبات"), U"طلب");
    EXPECT_EQ(stemmer.stem(U"فالطالبات"), U"طلب");
    EXPECT_EQ(stemmer.stem(U"والطالبات"), U"طلب");
    EXPECT_EQ(stemmer.stem(U"الطالبون"), U"طلب");
    EXPECT_EQ(stemmer.stem(U"اللذان"), U"لذن");
    EXPECT_EQ(stemmer.stem(U"من"), U"من");
    EXPECT_EQ(stemmer.stem(U"الكلمات"), U"كلم");
}
