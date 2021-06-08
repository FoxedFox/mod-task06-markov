#include "textgen.h"
#include <iostream>
using namespace std;
void textgen::StreamDatEntry(const  string& StreamFile)
{
     ifstream fin;
    fin.open(StreamFile);
    if (!fin)
    {
        throw( bad_exception());
    }
     vector<string> words = InputFromStream(fin);
    fin.close();
    DatEntry(words);
}
void textgen::DatEntry(const  vector<string>& words)
{
    if (words.size() < SizeOfPrefix + 1)
    {
        return;
    }
     deque<string> key;
    for (int i = 0; i < SizeOfPrefix; i++)
    {
        key.push_back(words[i]);
    }
    for (int i = SizeOfPrefix; i < words.size(); i++)
    {
        DataBase[key][words[i]]++;
        key.pop_front();
        key.push_back(words[i]);
    }
    for ( size_t i = SizeOfPrefix; i > 0; i--)
    {
        key.pop_front();
        key.push_back(words[words.size() - i]);
    }
    DataBase[key] =  map<string,  size_t>();
    DataBase[key]["."] = 1;

    DataEntry += words.size();
}
 string textgen::TextGenerator( size_t TextSize,  size_t CountStrWords)
{
    if (TextSize < SizeOfPrefix)
    {
        return "error textsize\n";
    }
     srand( time(nullptr));
     size_t pos = rand() % DataBase.size();
    auto iterator = DataBase.begin();
    for ( size_t i = 0; i < pos; i++)
    {
        ++iterator;
    }
     deque< string> key = iterator->first;
     string out = "";
    for (auto& s : key)
    {
        out = out + s + " ";
    }
     size_t VariantKey;
     string NextWord;
     size_t chance;
     size_t CalculatedChance = 0;
     size_t StrSize = SizeOfPrefix;
    
    for ( size_t i = SizeOfPrefix; i < TextSize; i++)
    {
        if (StrSize >= CountStrWords)
        {
            out += "\n";
            StrSize = 0;
        }
        VariantKey = 0;
        for (auto& m : DataBase[key])
        {
            VariantKey += m.second;
        }
        chance = rand() % (VariantKey);
        for (auto& m : DataBase[key])
        {
            if (m.second + CalculatedChance >= chance)
            {
                NextWord = m.first;
                CalculatedChance = 0;
                break;
            }
            CalculatedChance += m.second;
        }
        if (NextWord == ".")
        {
            out = out + NextWord;
            break;
        }
        out = out + NextWord + " ";
        key.pop_front();
        key.push_back(NextWord);
        ++StrSize;
    }
    return out;
}
void textgen::DataBasePrint()
{
    for (auto& up_map : DataBase)
    {
         cout << "[ ";
        for (auto& key : up_map.first)
        {
             cout << key << " ";
        }
         cout << "] { ";
        for (auto& down_map : up_map.second)
        {
             cout << down_map.first << " ";
        }
         cout << " }\n";
    }
} 
map<deque< string>,  map< string,  size_t>> textgen::get_base()
{
    return DataBase;
}
