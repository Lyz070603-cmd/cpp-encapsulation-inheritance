#include "TextQuery.h"
#include <sstream>

TextQuery::TextQuery(ifstream &is)
:file(new vector<string>){

    string text;
    while(getline(is,text)){
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word){
           auto &lines = wm[word]; 
           if (!lines){
               lines.reset(new set<int>);
           }
           lines->insert(n);
        }
    }
}


QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<int>> nodata(new set<int>);   
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, file, nodata);
    else
        return QueryResult(sought, file, loc->second);
}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << (qr.lines->size() == 1 ? "time" : "times") << "\n";

    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") "                  
           << *(qr.file->begin() + num) << "\n";             

    return os;
}

