#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "QueryResult.h"

class TextQuery {
public:
    using line_no = int;                                              

    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;

private:
    std::shared_ptr<std::vector<std::string>> file;                   
    std::map<std::string, std::shared_ptr<std::set<int>>> wm;         
};
#endif
