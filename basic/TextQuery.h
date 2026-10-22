#ifndef  __TEXTQUERY_H__
#define  __TEXTQUERY_H__
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <string>
#include "QueryResult.h"
using namespace std;
class TextQuery{
public:
    TextQuery(ifstream &);
    QueryResult query(const string & )const;

private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<int>>> wm;
};
#endif
