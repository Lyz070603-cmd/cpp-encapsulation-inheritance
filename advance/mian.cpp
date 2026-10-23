#include "Query.h"
#include "TextQuery.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::runtime_error;
using std::string;

TextQuery get_file(int argc, char **argv) {
    string filename;
    ifstream ifs;
    bool useArg = (argc == 2);

    while (true) {
        if (useArg)
            filename = argv[1];
        else {
            cout << "请输入要查询的文件：" << endl;
            if (!(cin >> filename))
                throw runtime_error("输入结束");
        }
        ifs.open(filename);
        if (ifs) break;
        cout << "文件不存在或文件名错误，请重新输入" << endl;
        ifs.clear();          
        useArg = false;
    }
    return TextQuery(ifs);
}

bool get_word(string &s1) {
    cout << "enter a word to search for, or q to quit: ";
    if (!(cin >> s1) || s1 == "q") return false;
    return true;
}

int main(int argc, char **argv) {
    TextQuery file = get_file(argc, argv);          // 建索引

    do {
        string sought;
        if (!get_word(sought)) break;                // 输入 q 或 EOF 结束

        Query name(sought);                          // 造一个单节点查询树
        const QueryResult results = name.eval(file);         // 求值
        cout << "\nExecuting Query for: " << name << endl;   // 打印表达式
        print(cout, results) << endl;                        // 打印结果
    } while (true);

    return 0;
}
