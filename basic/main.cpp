#include <iostream>
#include <fstream>
#include <string>
#include "Query.h"
using namespace std;

int main()
{
    //判断用户输入的文件名
    string filename;
    cout << "请输入要查询的文件" << endl;
    ifstream ifs;
    while (true){
        cin >> filename;
        ifs.open(filename);
        if (!ifs){
            cout << "文件不存在或文件名错误"  << endl;
            cout << "请重新输入" << endl;
            ifs.clear();
        }
        else {
            break;
        }

    }


    TextQuery textQuery(ifs);
    cout << "请输入要查询的单词" << endl;
    string word;
    while (cin >> word){
        Query query(word);
        print(cout, query.eval(textQuery));
        cout << "请输入要查询的单词（按 Ctrl+Z 结束）" << endl;
    }
}

