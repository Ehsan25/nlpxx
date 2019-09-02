#pragma once

#include <regex>
#include <string>
#include <vector>
#include "base.h"

namespace nlpxx::stem
{
/// ISRI Arabic stemmer based on algorithm: Arabic Stemming without a root
/// dictionary. Information Science Research Institute. University of Nevada,
/// Las Vegas, USA. A few minor modifications have been made to ISRI basic
/// algorithm. See the source code of this module for more information.
/// isri.stem(token) returns Arabic root for the given token.
/// The ISRI Stemmer requires that all tokens have Unicode string types.
/// If you use Python IDLE on Arabic Windows you have to decode text first
/// using Arabic '1256' coding.
class Isri : public Stemmer
{
public:
    enum Normalization
    {
        NormalizeDiacritics,
        NormalizeInitialHamza,
        NormalizeBoth
    };

private:
    /// length 1,2,3 prefixes
    static std::vector<utils::string> prefix1, prefix2, prefix3;
    /// length 1,2,3 suffixes
    static std::vector<utils::string> suffix1, suffix2, suffix3;
    /// groups of length four patterns and groups of length five patterns and length three roots
    static std::vector<std::vector<utils::string>> pattern4, pattern53;

    /// regexes
    static utils::regex short_vowels, hamza, initial_hamza;

    /// stop words
    static std::vector<utils::string> stop_words;

    utils::string norm(utils::string word, Normalization normalization);

    /// remove length three and length two prefixes in this order
    utils::string pre32(const utils::string &word);

    /// remove length three and length two suffixes in this order
    utils::string suf32(const utils::string &word);

    /// remove connective ‘و’ if it precedes a word beginning with ‘و’
    utils::string waw(const utils::string &word);

public:
    Isri() {}
    utils::string stem(const utils::string &token) override {}
};

}  // namespace nlpxx::stem
