#pragma once
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
class textgen
{
public:
    map<deque<string>, map<string, size_t>> get_base();
    string TextGenerator(size_t SizeOfText, size_t StrWordsCount);
    textgen(size_t SizeOfPrefix) : SizeOfPrefix(SizeOfPrefix), DataEntry(0) {}
    void StreamDatEntry(const string& StreamFile);
    void DatEntry(const vector<string>& words);
    void DataBasePrint();
    
private:
    map<deque<string>, map<string, size_t>> DataBase;
    size_t DataEntry;
    size_t SizeOfPrefix;
};
template<typename t>
vector<string> InputFromStream(t& stream)
{
    string word = "";
    vector<string> result;
    unsigned char sym = stream.get();
    while (!stream.eof())
    {
       if ( sym > 64 &&  sym < 91)
        {
             sym += 32;
        }    
        if (sym > 191 && sym < 224)
        {
            sym += 32;
        }        
        if (( sym > 223 &&  sym <= 255) || ( sym > 96 &&  sym <= 123))
        {
            word += sym;
        }
        else if (word.size() > 0)
        {
            result.push_back(word);
            word = "";
        }
         sym = stream.get();
    }
    if (word.length())
    {
        result.push_back(word);
    }
    return result;
}

