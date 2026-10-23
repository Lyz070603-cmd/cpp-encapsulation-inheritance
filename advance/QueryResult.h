#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

class QueryResult {
    friend std::ostream &print(std::ostream &, const QueryResult &);
public:
    using line_no = int;                                  
    using line_it = std::set<int>::const_iterator;        

    QueryResult(std::string s,
                std::shared_ptr<std::set<int>> p,         
                std::shared_ptr<std::vector<std::string>> f)
        : sought(s), lines(p), file(f) { }

    std::set<int>::size_type size() const { return lines->size(); }
    line_it begin() const { return lines->begin(); }
    line_it end()   const { return lines->end(); }
    std::shared_ptr<std::vector<std::string>> get_file() { return file; }

private:
    std::string sought;                               
    std::shared_ptr<std::set<int>> lines;             
    std::shared_ptr<std::vector<std::string>> file;   
};

std::ostream &print(std::ostream &, const QueryResult &);
#endif
