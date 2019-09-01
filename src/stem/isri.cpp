#include "isri.h"

using namespace nlpxx::stem;

std::vector<std::string> Isri::prefix1 = {
    "\u0644", "\u0628", "\u0641", "\u0633", "\u0648", "\u064a", "\u062a", "\u0646", "\u0627",
};
std::vector<std::string> Isri::prefix2 = {"\u0627\u0644", "\u0644\u0644"};
std::vector<std::string> Isri::prefix3 = {
    "\u0643\u0627\u0644",
    "\u0628\u0627\u0644",
    "\u0648\u0644\u0644",
    "\u0648\u0627\u0644",
};

std::vector<std::string> Isri::suffix1 = {"\u0629", "\u0647", "\u064a", "\u0643",
                                          "\u062a", "\u0627", "\u0646"};
std::vector<std::string> Isri::suffix2 = {

    "\u0648\u0646", "\u0627\u062a", "\u0627\u0646", "\u064a\u0646", "\u062a\u0646", "\u0643\u0645",
    "\u0647\u0646", "\u0646\u0627", "\u064a\u0627", "\u0647\u0627", "\u062a\u0645", "\u0643\u0646",
    "\u0646\u064a", "\u0648\u0627", "\u0645\u0627", "\u0647\u0645",
};
std::vector<std::string> Isri::suffix3 = {

    "\u062a\u0645\u0644", "\u0647\u0645\u0644", "\u062a\u0627\u0646",
    "\u062a\u064a\u0646", "\u0643\u0645\u0644",
};

std::vector<std::vector<std::string>> Isri::pattern4 = {
    {"\u0645"},
    {"\u0627"},
    {"\u0627", "\u0648", "\u064A"},
    {"\u0629"},
};
std::vector<std::vector<std::string>> Isri::pattern53 = {
    {"\u0627", "\u062a"},           {"\u0627", "\u064a", "\u0648"}, {"\u0627", "\u062a", "\u0645"},
    {"\u0645", "\u064a", "\u062a"}, {"\u0645", "\u062a"},           {"\u0627", "\u0648"},
    {"\u0627", "\u0645"},
};

std::regex Isri::short_vowels = std::regex("[\u064B-\u0652]");
std::regex Isri::hamza = std::regex("[\u0621\u0624\u0626]");
std::regex Isri::initial_hamza = std::regex("^[\u0622\u0623\u0625]");

std::vector<std::string> Isri::stop_words = {
    "\u064a\u0643\u0648\u0646",
    "\u0648\u0644\u064a\u0633",
    "\u0648\u0643\u0627\u0646",
    "\u0643\u0630\u0644\u0643",
    "\u0627\u0644\u062a\u064a",
    "\u0648\u0628\u064a\u0646",
    "\u0639\u0644\u064a\u0647\u0627",
    "\u0645\u0633\u0627\u0621",
    "\u0627\u0644\u0630\u064a",
    "\u0648\u0643\u0627\u0646\u062a",
    "\u0648\u0644\u0643\u0646",
    "\u0648\u0627\u0644\u062a\u064a",
    "\u062a\u0643\u0648\u0646",
    "\u0627\u0644\u064a\u0648\u0645",
    "\u0627\u0644\u0644\u0630\u064a\u0646",
    "\u0639\u0644\u064a\u0647",
    "\u0643\u0627\u0646\u062a",
    "\u0644\u0630\u0644\u0643",
    "\u0623\u0645\u0627\u0645",
    "\u0647\u0646\u0627\u0643",
    "\u0645\u0646\u0647\u0627",
    "\u0645\u0627\u0632\u0627\u0644",
    "\u0644\u0627\u0632\u0627\u0644",
    "\u0644\u0627\u064a\u0632\u0627\u0644",
    "\u0645\u0627\u064a\u0632\u0627\u0644",
    "\u0627\u0635\u0628\u062d",
    "\u0623\u0635\u0628\u062d",
    "\u0623\u0645\u0633\u0649",
    "\u0627\u0645\u0633\u0649",
    "\u0623\u0636\u062d\u0649",
    "\u0627\u0636\u062d\u0649",
    "\u0645\u0627\u0628\u0631\u062d",
    "\u0645\u0627\u0641\u062a\u0626",
    "\u0645\u0627\u0627\u0646\u0641\u0643",
    "\u0644\u0627\u0633\u064a\u0645\u0627",
    "\u0648\u0644\u0627\u064a\u0632\u0627\u0644",
    "\u0627\u0644\u062d\u0627\u0644\u064a",
    "\u0627\u0644\u064a\u0647\u0627",
    "\u0627\u0644\u0630\u064a\u0646",
    "\u0641\u0627\u0646\u0647",
    "\u0648\u0627\u0644\u0630\u064a",
    "\u0648\u0647\u0630\u0627",
    "\u0644\u0647\u0630\u0627",
    "\u0641\u0643\u0627\u0646",
    "\u0633\u062a\u0643\u0648\u0646",
    "\u0627\u0644\u064a\u0647",
    "\u064a\u0645\u0643\u0646",
    "\u0628\u0647\u0630\u0627",
    "\u0627\u0644\u0630\u0649",
};

std::string Isri::norm(std::string word, Isri::Normalization normalization)
{
    if (normalization == NormalizeDiacritics || normalization == NormalizeBoth)
        word = std::regex_replace(word, short_vowels, "");
    if (normalization == NormalizeInitialHamza || normalization == NormalizeBoth)
        return std::regex_replace(word, initial_hamza, "\u0627");
    return word;
}

std::string Isri::pre32(const std::string &word)
{
    if (word.size() >= 6)
        for (auto prefix : prefix3)
            if (std::equal(prefix.begin(), prefix.end(), word.begin())) return word.substr(3);

    if (word.size() >= 5)
        for (auto prefix : prefix2)
            if (std::equal(prefix.begin(), prefix.end(), word.begin())) return word.substr(2);

    return word;
}
