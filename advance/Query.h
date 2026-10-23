#ifndef QUERY_H
#define QUERY_H
// 基础版 · 行号类型 int：只保留「查一个单词」这一条链路
#include <iostream>
#include <memory>
#include <string>
#include "TextQuery.h"

// 抽象基类：只声明“必须会求值、必须会描述自己”
class Query_base {
    friend class Query;                    // 让 Query 能调下面的私有成员
protected:
    using line_no = TextQuery::line_no;    // ★ = int
    virtual ~Query_base() = default;       // 保护的虚析构
private:
    virtual QueryResult eval(const TextQuery &) const = 0;   // 纯虚：求值
    virtual std::string rep() const = 0;                     // 纯虚：字符串形式
};




// 接口类 / 把手：只有一个数据成员 shared_ptr
class Query {
public:
    Query(const std::string &);                                  // 造一个 WordQuery

    QueryResult eval(const TextQuery &t) const { return q->eval(t); }  // 转发
    std::string rep() const { return q->rep(); }                       // 转发

private:
    std::shared_ptr<Query_base> q;
};



// 唯一的具体类：真正查文件的就是它
class WordQuery : public Query_base {
    friend class Query;                    // 让 Query 能调私有的构造函数
    WordQuery(const std::string &s) : query_word(s) { }

    QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
    std::string rep() const { return query_word; }

    std::string query_word;
};



// Query 的构造函数只能写在 WordQuery 之后（它要 new WordQuery）
inline Query::Query(const std::string &s) : q(new WordQuery(s)) { }

inline std::ostream &operator<<(std::ostream &os, const Query &query) {
    return os << query.rep();              // Query::rep(非虚) → q->rep(虚)
}
#endif
