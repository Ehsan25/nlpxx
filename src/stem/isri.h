#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include "../utils/utils.h"
#include "base.h"

// TODO optimize slicing and remove unneeded variables. maaybe turn some of the vectors into sets
// for speed

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
class ISRI : public Stemmer
{
public:
    enum Normalization
    {
        NormalizeDiacritics,
        NormalizeInitialHamza,
        NormalizeBoth
    };

private:
    /// length 1 prefixes and suffixes
    static utils::string prefix1, suffix1;
    /// length 2,3 prefixes
    static std::vector<utils::string> prefix2, prefix3;
    /// length 2,3 suffixes
    static std::vector<utils::string> suffix2, suffix3;
    /// stop words
    static std::unordered_set<utils::string> stop_words;

    void norm(utils::string &word, Normalization normalization) const;

    /// remove length three and length two prefixes in this order
    void pre32(utils::string &word) const;
    /// remove length three and length two suffixes in this order
    void suf32(utils::string &word) const;
    /// remove connective ‘و’ if it precedes a word beginning with ‘و’
    void waw(utils::string &word) const;
    /// process length four patterns and extract length three roots
    void pro_w4(utils::string &word) const;
    /// process length five patterns and extract length three roots
    void pro_w53(utils::string &word) const;
    /// process length five patterns and extract length four roots
    void pro_w54(utils::string &word) const;
    /// ending step (word of length five)
    void end_w5(utils::string &word) const;
    /// process length six patterns and extract length three roots
    void pro_w6(utils::string &word) const;
    /// process length six patterns and extract length four roots
    void pro_w64(utils::string &word) const;
    /// ending step (word of length six)
    void end_w6(utils::string &word) const;
    /// normalize short sufix
    void suf1(utils::string &word) const;
    /// normalize short prefix
    void pre1(utils::string &word) const;

public:
    ISRI();
    utils::string stem(utils::string token) const override;
};

}  // namespace nlpxx::stem
