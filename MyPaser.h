//
// Created by lenovo on 2020/12/10.
//

#ifndef WEB_TRAFFIC_IDENTIFICATION_PASER_H
#define WEB_TRAFFIC_IDENTIFICATION_PASER_H

#endif //WEB_TRAFFIC_IDENTIFICATION_PASER_H
#include <iostream>
#include <cstring>
#include <map>
#include "DataStructure.h"

using namespace std;

// 流量解析
class TrafficParser {
private:

};

// HTML解析器
class MyParser {
public:
    MyParser(const string &url, const string &host, const string &content) : url(url),host(host),content(content) {
        this->html = Element(1,Node(),0,)
    }

private:
    string url;
    string host;
    const int MAX_PARSING_DEPTH = 6; // 最大解析深度
    string content; // html文章内容
    Element html; // html 根元素
    MAP_STRING_TAG localTags; // 字符串到标签的映射

    Tag getTag(const string &str) {
        if(localTags.find(str) != localTags.end()) {
            return localTags[str];
        }
        Tag tag = Tag.getTag;
    }
};
