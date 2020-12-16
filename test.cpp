//
// Created by lenovo on 2020/12/9.
//
#include "WebCrawl.h"
#include "DataStructure.h"
string content = "write successfully.";
void testWebCrawl() {
//    std::string url = "https://google.com";
    std::string url = "http://news.hit.edu.cn/2020/1206/c1510a220456/page.htm";
    content = getResponseFromUrl(url);
//    std::cout<<content<<endl;
    parseResponse(content);
}

void testWriteFile() {
    string filename = "testfile";
    writefile(filename, content);
}

void testDataStructure() {
    Node n1(0, Node(), 0);
    Node n2(0, Node(), 0);
    TextNode t1(0,n1,0,"emm");
    TextNode t2(0,n1,0,"emm");
    cout<<(t1 == t2);
    t2.
}

int main() {
    testWebCrawl();
    testWriteFile();
}