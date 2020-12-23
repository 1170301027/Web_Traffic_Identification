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
    Element n;
    shared_ptr<Element> n1(&n);
    Node node;
    shared_ptr<Node> n2(&node);
    Node *e = dynamic_cast<Node * >(&n);
//    Element *element = dynamic_cast<Element *>(&node);
    TextNode t1(0,0,shared_ptr<Element>(&n),"emm");
    TextNode t2(0,0,n1,"emm");
//    cout<<(t1 == t2);
    MD5 md5;
    md5.printK();
}

int main() {
//    testWebCrawl();
//    testWriteFile();
    testDataStructure();
}