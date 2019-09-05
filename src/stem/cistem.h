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


#include <string>
#include <unordered_set>
#include <vector>
#include "../utils/utils.h"
#include "base.h"

namespace nlpxx::stem
{
//CISTEM Stemmer for German

//This is the official Python implementation of the CISTEM stemmer.
//It is based on the paper
//Leonie Weissweiler, Alexander Fraser (2017). Developing a Stemmer for German
//Based on a Comparative Analysis of Publicly Available Stemmers.
//In Proceedings of the German Society for Computational Linguistics and Language
//Technology (GSCL)
//which can be read here:
//http://www.cis.lmu.de/~weissweiler/cistem/

//In the paper, we conducted an analysis of publicly available stemmers,
//developed two gold standards for German stemming and evaluated the stemmers
//based on the two gold standards. We then proposed the stemmer implemented here
//and show that it achieves slightly better f-measure than the other stemmers and
//is thrice as fast as the Snowball stemmer for German while being about as fast
//as most other stemmers.

//case_insensitive is a a boolean specifying if case-insensitive stemming
//should be used. Case insensitivity improves performance only if words in the
//text may be incorrectly upper case. For all-lowercase and correctly cased
//text, best performance is achieved by setting case_insensitive for false.

//:param case_insensitive: if True, the stemming is case insensitive. False by default.
//:type case_insensitive: bool


class cistem : public Stemmer
{

private:
    static utils::regex strip_ge(U"^ge(.{4,})");
    static utils::string repl_xx;
    static utils::string strip_emr;
    static utils::string strip_nd;
    static utils::string strip_t;
    static utils::string strip_esn;
    static utils::string repl_xx_back;

    void replace_to(utils::string& word) const;
    void replace_back(utils::string& word) const;


public:
    cistem();
    utils::string stem(utils::string token) const override;
};

} // namespace nlpxx::stem
