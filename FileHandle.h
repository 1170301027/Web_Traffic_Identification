//
// Created by lenovo on 2020/12/10.
//
#include <fstream>
#include <iostream>

using namespace std;
const string source_data_dir = "E:\\JetBrains\\CLion 2020.2.5\\workspace\\Web_Traffic_Identification\\data\\";
void writefile(const string& file, const string& content); // 不写这个定义还有问题。 报错是函数多重定义

void writefile(const string& file, const string& content)
{
    string filename = source_data_dir + file;
    ofstream out_file;
    out_file.open(filename);
    if (!out_file) {
        cout<<"File '" + filename + "' will be created."<<endl;
        out_file.open(filename);
    }
    if (!out_file.is_open()) {
        cout<<"Fail to open file."<<endl;
        exit(EXIT_FAILURE);
    }
    out_file<<content;
    out_file.close();
}