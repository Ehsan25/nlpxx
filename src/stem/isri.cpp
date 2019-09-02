#include "isri.h"

using namespace nlpxx;
using namespace stem;

utils::string Isri::prefix1 = U"\u0644\u0628\u0641\u0633\u0648\u064a\u062a\u0646\u0627";
utils::string Isri::suffix1 = U"\u0629\u0647\u064a\u0643\u062a\u0627\u0646";

std::vector<utils::string> Isri::prefix2 = {U"\u0627\u0644", U"\u0644\u0644"};
std::vector<utils::string> Isri::prefix3 = {
    U"\u0643\u0627\u0644",
    U"\u0628\u0627\u0644",
    U"\u0648\u0644\u0644",
    U"\u0648\u0627\u0644",
};

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

std::unordered_set<utils::string> Isri::stop_words = {
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

void Isri::norm(utils::string &word, Isri::Normalization normalization) const
{
    if (normalization == NormalizeDiacritics || normalization == NormalizeBoth)
    {
        for (size_t i = 0; i < word.size(); ++i)
            if (word[i] >= U'\u064B' && word[i] <= U'\u0652')
            {
                word.erase(word.begin() + ssize_t(i));
                --i;
            }
    }
    if (normalization == NormalizeInitialHamza || normalization == NormalizeBoth)
    {
        if (word[0] == U'\u0622' || word[0] == U'\u0623' || word[0] == U'\u0625')
            word[0] = U'\u0627';
    }
}

void Isri::pre32(utils::string &word) const
{
    if (word.size() >= 6)
        for (auto prefix : prefix3)
            if (std::equal(prefix.begin(), prefix.end(), word.begin()))
            {
                word.erase(0, 3);
                return;
            }

    if (word.size() >= 5)
        for (auto prefix : prefix2)
            if (std::equal(prefix.begin(), prefix.end(), word.begin())) word.erase(0, 2);
}

void Isri::suf32(utils::string &word) const
{
    if (word.size() >= 6)
        for (auto suffix : suffix3)
            if (std::equal(suffix.begin(), suffix.end(), word.end() - suffix.size()))
            {
                word.erase(word.size() - 3);
                return;
            }

    if (word.size() >= 5)
        for (auto suffix : suffix2)
            if (std::equal(suffix.begin(), suffix.end(), word.end() - suffix.size()))
                word.erase(word.size() - 2);
}

void Isri::waw(utils::string &word) const
{
    if (word.size() >= 4 && word[0] == U'\u0648' && word[1] == U'\u0648') word.erase(word.begin());
}

void Isri::pro_w4(utils::string &word) const
{
    if (word[0] == U'\u0645')
        word.erase(word.begin());
    else if (word[1] == U'\u0627')
    {
        word.erase(word.begin() + 1);
    }
    else if (word[2] == U'\u0627' || word[2] == U'\u0648' || word[2] == U'\u064A')
    {
        word.erase(word.begin() + 2);
        word.erase(3);
    }
    else if (word[3] == U'\u0629')
        word.pop_back();
    else
    {
        suf1(word);
        if (word.size() == 4) pre1(word);
    }
}

void Isri::pro_w53(utils::string &word) const
{
    if ((word[2] == U'\u0627' || word[2] == U'\u062a') && word[0] == U'\u0627')
    {
        word.erase(word.begin());
        word.erase(word.begin() + 1);
    }
    else if ((word[3] == U'\u0627' || word[3] == U'\u064a' || word[3] == U'\u0648') &&
             word[0] == U'\u0645')
        word = utils::string() + word[1] + word[2] + word[4];
    else if ((word[0] == U'\u0627' || word[0] == U'\u062a' || word[0] == U'\u0645') &&
             word[4] == U'\u0629')
        word = word.substr(1, 3);
    else if ((word[0] == U'\u0645' || word[0] == U'\u064a' || word[0] == U'\u062a') &&
             word[2] == U'\u062a')
    {
        word.erase(word.begin());
        word.erase(word.begin() + 1);
    }
    else if ((word[0] == U'\u0645' || word[0] == U'\u062a') && word[2] == U'\u0627')
    {
        word.erase(word.begin());
        word.erase(word.begin() + 1);
    }
    else if ((word[2] == U'\u0627' || word[2] == U'\u0648') && word[4] == U'\u0629')
    {
        word.erase(word.begin() + 2);
        word.erase(3);
    }
    else if ((word[0] == U'\u0627' || word[0] == U'\u0645') && word[1] == U'\u0646')
        word.erase(0, 2);
    else if (word[3] == U'\u0627' && word[0] == U'\u0627')
        word = utils::string() + word[1] + word[2] + word[4];
    else if (word[4] == U'\u0646' and word[3] == U'\u0627')
        word.erase(3);
    else if (word[3] == U'\u064a' and word[0] == U'\u062a')
        word = utils::string() + word[1] + word[2] + word[4];
    else if (word[3] == U'\u0648' and word[1] == U'\u0627')
        word = utils::string() + word[0] + word[2] + word[4];
    else if (word[2] == U'\u0627' and word[1] == U'\u0648')
        word.erase(1, 2);
    else if (word[3] == U'\u0626' and word[2] == U'\u0627')
        word = utils::string() + word[0] + word[1] + word[4];
    else if (word[4] == U'\u0629' and word[1] == U'\u0627')
        word = utils::string() + word[0] + word[2] + word[3];
    else if (word[4] == U'\u064a' and word[2] == U'\u0627')
        word = utils::string() + word[0] + word[1] + word[3];
    else
    {
        suf1(word);
        if (word.size() == 5) pre1(word);
    }
}

void Isri::pro_w54(utils::string &word) const
{
    if (word[0] == U'\u0627' || word[0] == U'\u062a' || word[0] == U'\u0645')
        word.erase(word.begin());
    else if (word[4] == U'\u0629')
        word.erase(4);
    else if (word[2] == U'\u0627')
        word.erase(word.begin() + 2);
}

void Isri::end_w5(utils::string &word) const
{
    if (word.size() == 4)
        pro_w4(word);
    else if (word.size() == 5)
        pro_w54(word);
}

void Isri::pro_w6(utils::string &word) const
{
    if ((word[0] == U'\u0627' || word[0] == U'\u0645') && word[1] == U'\u0633' &&
        word[2] == U'\u062a')
        word.erase(0, 3);
    else if (word[0] == U'\u0645' && word[3] == U'\u0627' && word[5] == U'\u0629')
    {
        word = utils::string() + word[1] + word[2] + word[4];
    }
    else if (word[0] == U'\u0627' && word[2] == U'\u062a' && word[4] == U'\u0627')
    {
        word = utils::string() + word[1] + word[3] + word[5];
    }
    else if (word[0] == U'\u0627' && word[3] == U'\u0648' && word[2] == word[4])
    {
        word.erase(word.begin());
        word.erase(1, 2);
    }
    else if (word[0] == U'\u062a' && word[2] == U'\u0627' && word[4] == U'\u064a')
    {
        word = utils::string() + word[1] + word[3] + word[5];
    }
    else
    {
        suf1(word);
        if (word.size() == 6) pre1(word);
    }
}

void Isri::pro_w64(utils::string &word) const
{
    if (word[0] == U'\u0627' && word[4] == U'\u0627')
    {
        word.erase(word.begin());
        word.erase(word.begin() + 3);
        word.erase(4);
    }
    else if (word[0] == U'\u0645' && word[1] == U'\u062a')
        word.erase(0, 2);
}

void Isri::end_w6(utils::string &word) const
{
    if (word.size() == 5)
    {
        pro_w53(word);
        end_w5(word);
    }
    else if (word.size() == 6)
        pro_w64(word);
}

void Isri::suf1(utils::string &word) const
{
    if (suffix1.find(word.back()) != utils::string::npos) word.pop_back();
}

void Isri::pre1(utils::string &word) const
{
    if (prefix1.find(word.back()) != utils::string::npos) word.erase(word.begin());
}

Isri::Isri() {}

utils::string Isri::stem(utils::string token) const
{
    norm(token, NormalizeDiacritics);
    if (stop_words.find(token) != stop_words.end()) return token;

    pre32(token);
    suf32(token);
    waw(token);
    norm(token, NormalizeInitialHamza);

    if (token.size() == 4)
        pro_w4(token);
    else if (token.size() == 5)
    {
        pro_w53(token);
        end_w5(token);
    }
    else if (token.size() == 6)
    {
        pro_w6(token);
        end_w6(token);
    }
    else if (token.size() == 7)
    {
        suf1(token);
        if (token.size() == 7) pre1(token);
        if (token.size() == 6)
        {
            pro_w6(token);
            end_w6(token);
        }
    }

    return token;
}
