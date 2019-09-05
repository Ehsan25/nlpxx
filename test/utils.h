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

#include <gtest/gtest.h>
#include <nlpxx.h>

using namespace nlpxx::utils;

TEST(Utils, Regex)
{
    regex R1(U"[a-z]");
    string text1 = U"a";
    string text2 = U"A";

    EXPECT_EQ(R1.match(text1), true);
    EXPECT_EQ(R1.match(text2), false);

    regex R2(U"hi");
    EXPECT_EQ(R2.replace(U"hie", U"bye"), U"byee");
    EXPECT_EQ(R2.replace(U"hoe", U"bye"), U"hoe");
    EXPECT_EQ(R2.replace(U"hihie", U"by"), U"bybye");
}
