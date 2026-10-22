#ifndef __QUERY_H__
#define __QUERY_H__
#include <ostream>
#include <string>
#include <memory>
#include "TextQuery.h"
using namespace std;

class WorkQuery{
public:
    WorkQuery(const string &s)
    :query_word(s){

    }

    string rep() const {return query_word;}
    QueryResult eval(const TextQuery &t) const {return t.query(query_word);}



private:
    string query_word;
};


class Query{       //对外的把手，也就是通过这个来操纵外面
public:

    Query(const string &s)
    :q(new WorkQuery(s)){}

    string rep() const {return q->rep();}
    QueryResult eval(const TextQuery &t) const {return q->eval(t);}


private:
    shared_ptr<WorkQuery> q;

};

inline ostream& operator<<(ostream& is , const Query &query){
    is << query.rep() << endl;
    return is;
}

#endif
