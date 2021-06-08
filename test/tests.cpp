// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
using namespace std;
TEST(AllTests, test1) {
    vector<string> text = {"black", "as", "coal", "night"};

    set<deque<string>> expected_prefixes = {
        {"black", "as"}, {"as", "coal"}, {"coal", "night"}
    };

    textgen tg{2};
    tg.StreamDatEntry(text);
    auto base = tg.get_base();

    set<deque<string>> actual_prefixes;
    for (auto& x : base) {
        actual_prefixes.insert(x.first);
    }

    ASSERT_EQ(expected_prefixes.size(), actual_prefixes.size());
    for (auto& x : expected_prefixes) {
        ASSERT_TRUE(actual_prefixes.find(x) != actual_prefixes.end());
    }
}

TEST(AllTests, test2) {
    vector<string> text = {"black", "as", "coal", "night"};

    textgen tg{2};
    tg.StreamDatEntry(text);
    auto base = tg.get_base();

    deque<string> list {"as"};
    auto iterator = base[deque<string>{"black", "coal"}].begin();
    for(auto& x : list)
    {
        ASSERT_EQ(iterator->first, x);
        ++iterator;
    }
}

TEST(AllTests, test3) {
    vector<string> text = {"see", "my", "heart", "red", "see", "it", "painted", "black"};

    textgen tg{3};
    tg.StreamDatEntry(text);
    string out = tg.TextGenerator(10,5);
    ASSERT_EQ(out[out.length()-1], '.');
}
