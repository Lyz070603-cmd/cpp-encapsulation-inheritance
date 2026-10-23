#include "TextQuery.h"
#include <sstream>

using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

// 读文件，建「单词 → 行号集合」倒排表（行号用 int）
TextQuery::TextQuery(std::ifstream &is) : file(new vector<string>) {
    string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        int n = int(file->size()) - 1;          
        std::istringstream line(text);
        string word;
        while (line >> word) {
            auto &lines = wm[word];             
            if (!lines)
                lines.reset(new set<int>);      
            lines->insert(n);                   
        }
    }
}

QueryResult TextQuery::query(const string &sought) const {
    static shared_ptr<set<int>> nodata(new set<int>);   
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << (qr.lines->size() == 1 ? "time" : "times") << "\n";
    for (auto num : *qr.lines)                  
        os << "\t(line " << num + 1 << ") "     // int + 1，OK
           << *(qr.file->begin() + num) << "\n"; // int 偏移，OK
    return os;
}
