#include "isri.h"

using namespace nlpxx;
using namespace stem;

std::vector<utils::string> Isri::prefix1 = {
    U"\u0644", U"\u0628", U"\u0641", U"\u0633", U"\u0648",
    U"\u064a", U"\u062a", U"\u0646", U"\u0627",
};
std::vector<utils::string> Isri::prefix2 = {U"\u0627\u0644", U"\u0644\u0644"};
std::vector<utils::string> Isri::prefix3 = {
    U"\u0643\u0627\u0644",
    U"\u0628\u0627\u0644",
    U"\u0648\u0644\u0644",
    U"\u0648\u0627\u0644",
};

std::vector<utils::string> Isri::suffix1 = {U"\u0629", U"\u0647", U"\u064a", U"\u0643",
                                            U"\u062a", U"\u0627", U"\u0646"};
std::vector<utils::string> Isri::suffix2 = {

    U"\u0648\u0646", U"\u0627\u062a", U"\u0627\u0646", U"\u064a\u0646",
    U"\u062a\u0646", U"\u0643\u0645", U"\u0647\u0646", U"\u0646\u0627",
    U"\u064a\u0627", U"\u0647\u0627", U"\u062a\u0645", U"\u0643\u0646",
    U"\u0646\u064a", U"\u0648\u0627", U"\u0645\u0627", U"\u0647\u0645",
};
std::vector<utils::string> Isri::suffix3 = {

    U"\u062a\u0645\u0644", U"\u0647\u0645\u0644", U"\u062a\u0627\u0646",
    U"\u062a\u064a\u0646", U"\u0643\u0645\u0644",
};

std::vector<std::vector<utils::string>> Isri::pattern4 = {
    {U"\u0645"},
    {U"\u0627"},
    {U"\u0627", U"\u0648", U"\u064A"},
    {U"\u0629"},
};
std::vector<std::vector<utils::string>> Isri::pattern53 = {
    {U"\u0627", U"\u062a"},
    {U"\u0627", U"\u064a", U"\u0648"},
    {U"\u0627", U"\u062a", U"\u0645"},
    {U"\u0645", U"\u064a", U"\u062a"},
    {U"\u0645", U"\u062a"},
    {U"\u0627", U"\u0648"},
    {U"\u0627", U"\u0645"},
};

utils::regex Isri::short_vowels = utils::regex(U"[\u064B-\u0652]");
utils::regex Isri::hamza = utils::regex(U"[\u0621\u0624\u0626]");
utils::regex Isri::initial_hamza = utils::regex(U"^[\u0622\u0623\u0625]");

std::vector<utils::string> Isri::stop_words = {
    U"\u064a\u0643\u0648\u0646",
    U"\u0648\u0644\u064a\u0633",
    U"\u0648\u0643\u0627\u0646",
    U"\u0643\u0630\u0644\u0643",
    U"\u0627\u0644\u062a\u064a",
    U"\u0648\u0628\u064a\u0646",
    U"\u0639\u0644\u064a\u0647\u0627",
    U"\u0645\u0633\u0627\u0621",
    U"\u0627\u0644\u0630\u064a",
    U"\u0648\u0643\u0627\u0646\u062a",
    U"\u0648\u0644\u0643\u0646",
    U"\u0648\u0627\u0644\u062a\u064a",
    U"\u062a\u0643\u0648\u0646",
    U"\u0627\u0644\u064a\u0648\u0645",
    U"\u0627\u0644\u0644\u0630\u064a\u0646",
    U"\u0639\u0644\u064a\u0647",
    U"\u0643\u0627\u0646\u062a",
    U"\u0644\u0630\u0644\u0643",
    U"\u0623\u0645\u0627\u0645",
    U"\u0647\u0646\u0627\u0643",
    U"\u0645\u0646\u0647\u0627",
    U"\u0645\u0627\u0632\u0627\u0644",
    U"\u0644\u0627\u0632\u0627\u0644",
    U"\u0644\u0627\u064a\u0632\u0627\u0644",
    U"\u0645\u0627\u064a\u0632\u0627\u0644",
    U"\u0627\u0635\u0628\u062d",
    U"\u0623\u0635\u0628\u062d",
    U"\u0623\u0645\u0633\u0649",
    U"\u0627\u0645\u0633\u0649",
    U"\u0623\u0636\u062d\u0649",
    U"\u0627\u0636\u062d\u0649",
    U"\u0645\u0627\u0628\u0631\u062d",
    U"\u0645\u0627\u0641\u062a\u0626",
    U"\u0645\u0627\u0627\u0646\u0641\u0643",
    U"\u0644\u0627\u0633\u064a\u0645\u0627",
    U"\u0648\u0644\u0627\u064a\u0632\u0627\u0644",
    U"\u0627\u0644\u062d\u0627\u0644\u064a",
    U"\u0627\u0644\u064a\u0647\u0627",
    U"\u0627\u0644\u0630\u064a\u0646",
    U"\u0641\u0627\u0646\u0647",
    U"\u0648\u0627\u0644\u0630\u064a",
    U"\u0648\u0647\u0630\u0627",
    U"\u0644\u0647\u0630\u0627",
    U"\u0641\u0643\u0627\u0646",
    U"\u0633\u062a\u0643\u0648\u0646",
    U"\u0627\u0644\u064a\u0647",
    U"\u064a\u0645\u0643\u0646",
    U"\u0628\u0647\u0630\u0627",
    U"\u0627\u0644\u0630\u0649",
};

utils::string Isri::norm(utils::string word, Isri::Normalization normalization)
{
    if (normalization == NormalizeDiacritics || normalization == NormalizeBoth)
        word = std::regex_replace(word, short_vowels, U"");
    if (normalization == NormalizeInitialHamza || normalization == NormalizeBoth)
        return std::regex_replace(word, initial_hamza, U"\u0627");
    return word;
}

utils::string Isri::pre32(const utils::string &word)
{
    if (word.size() >= 6)
        for (auto prefix : prefix3)
            if (std::equal(prefix.begin(), prefix.end(), word.begin())) return word.substr(3);

    if (word.size() >= 5)
        for (auto prefix : prefix2)
            if (std::equal(prefix.begin(), prefix.end(), word.begin())) return word.substr(2);

    return word;
}

utils::string Isri::suf32(const utils::string &word)
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

utils::string Isri::waw(const utils::string &word)
{
    if (word.size() >= 4 && word[0] == U'\u0648' && word[1] == U'\u0648') return word.substr(1);
    return word;
}
