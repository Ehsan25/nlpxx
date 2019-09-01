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
    static std::vector<std::string> prefix1, prefix2, prefix3;
    /// length 1,2,3 suffixes
    static std::vector<std::string> suffix1, suffix2, suffix3;
    /// groups of length four patterns and groups of length five patterns and length three roots
    static std::vector<std::vector<std::string>> pattern4, pattern53;

    /// regexes
    static std::regex short_vowels, hamza, initial_hamza;

    /// stop words
    static std::vector<std::string> stop_words;

    std::string norm(std::string word, Normalization normalization);

    /// remove length three and length two prefixes in this order
    std::string pre32(const std::string &word);

    /// remove length three and length two suffixes in this order
    std::string suf32(const std::string &word)
    {
        if (word.size() >= 6)
            for (auto suffix : suffix3)
                if (std::equal(suffix.begin(), suffix.end(), word.end() - suffix.size()))
                    return word.substr(word.size() - 3);

        if (word.size() >= 5)
            for (auto suffix : suffix2)
                if (std::equal(suffix.begin(), suffix.end(), word.end() - suffix.size()))
                    return word.substr(word.size() - 2);

        return word;
    }

    /// remove connective ‘و’ if it precedes a word beginning with ‘و’
    std::string waw(const std::string &word)
    {
        if (word.size() >= 4 && word[0] == '\u0648' && word[1] == '\u0648') return word.substr(1);
        return word;
    }

public:
    Isri() {}
    std::string stem(const std::string &token) override {}
};

}  // namespace nlpxx::stem
