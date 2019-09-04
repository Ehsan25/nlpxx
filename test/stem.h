// Copyright (C) 2019 Shahriar Rezghi, Ehsan Alizadeh
// Copyright (C) 2001-2019 NLTK Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <gtest/gtest.h>
#include "../src/nlpxx.h"

using namespace nlpxx::utils;
using namespace nlpxx::stem;

TEST(Stem, ISRI)
{
    ISRI stemmer;

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
