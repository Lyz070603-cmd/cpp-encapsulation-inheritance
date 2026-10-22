#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <ostream>
using namespace std;

class QueryResult{
    friend ostream & print(ostream & ,const QueryResult &);
public:

    QueryResult(string s,
                shared_ptr<vector<string>> f,
                shared_ptr<set<int>> p)
        :sought(s),file(f),lines(p){}

    size_t size() const{return lines->size();}
    set<int>::const_iterator begin() const{return lines->begin();}
    set<int>::const_iterator end() const{return lines->end();}
    shared_ptr<vector<string>> get_file() const{return file;}

private:
    string sought;  //查询的单词
    shared_ptr<vector<string>> file; //源文件
    shared_ptr<set<int>> lines;  //行号
    

};
    ostream & print(ostream & ,const QueryResult &);

#endif
