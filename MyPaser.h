//
// Created by lenovo on 2020/12/10.
//

#ifndef WEB_TRAFFIC_IDENTIFICATION_PASER_H
#define WEB_TRAFFIC_IDENTIFICATION_PASER_H

#endif //WEB_TRAFFIC_IDENTIFICATION_PASER_H
#include <iostream>
#include <cstring>
#include <map>
#include <memory>
#include <utility>
#include <rpcndr.h>
#include "DataStructure.h"

using namespace std;

// 流量解析
class TrafficParser {
private:

};

// HTML解析器
class MyParser {
public:
    MyParser(string url, string host, string content) : url(std::move(url)),host(std::move(host)),content(std::move(content)) {
        Element e(0,0,std::make_shared<Element>(),getTag("html"));
        this->html = shared_ptr<Element>(&e);
        this->buffer = ByteBuffer(content,0,content.size());
    }

    void parse() {
        buffer.reset();

    }

    Element parseHTML(){
        Element html = Element(getTag("html"));
        shared_ptr<Element> pHtml(&html);
        int count = 0;
        boolean findHTML = false;
        while(true){
            if(!buffer.hasNext(TAG_START_FLAG))
                break;
            string name = getTagName();
            if(name.empty()){
                break;
            }else if(name != "html"){ // <html 匹配，把非HTML节点的元素加到HTML节点的子节点中
                if(name[0] == TAG_CLOSING_FLAG){
                    if(buffer.noNext(TAG_END_FLAG))
                        break;
                    continue;
                }
                shared_ptr<Tag> tag = getTag(name);
                Element e = Element(tag, pHtml, count++);
                shared_ptr<Element> ePtr(&e);
                html.appendChild(ePtr);
                e.setAttrs(getAttributesFromTag());
                if(!tag->isEmpty())
                    parse(ePtr);
                if(!buffer.canGo())
                    break;
            }else{
                findHTML = true;
                break;
            }
        }
        if(findHTML){
            html.setAttrs(getAttributesFromTag());
            parse(pHtml);
        }
        handleHTMLStructure(pHtml); // 解析HTML结构获取head和body
        return html;
    }

    boolean handleHTMLStructure(shared_ptr<Element> html){
        shared_ptr<Element> head = html->childElement("head");
        shared_ptr<Element> body = html->childElement("body");
        int size = html->getChildrenSize();
        if(size == 0)
            return false;

        if(head == nullptr){
            int index;
            if(body != nullptr && (index = body->indexOfElement("head")) >= 0){
                head = body->removeChild(index);
            }else {
                Element element(getTag("head"), html, 0);
                head = shared_ptr<Element>(&element);
            }
            html->appendChild(0, head);
            size++;
        }
        if(body == nullptr){
            int index;
            if((index = head->indexOfElement("body")) >= 0){
                body = head->removeChild(index);
            }else {
                Element element(getTag("body"), html, 0);
                body = shared_ptr<Element>(&element);
            }
            html->appendChild(html->getChildrenSize(), body);
            size++;
        }
        if(size == 2)
            return true;
//        int i=0;
        // 针对html节点下的子节点，除了head和body节点的其他节点加入到对应的head和body节点下。
        vector<shared_ptr<Element>> children = html->getChildren();
        for(shared_ptr<Element> child : children){
            if(child == head || child == body){
                continue;
            }
//            System.out.println(i++);
//            if (child instanceof Element) {
//                System.out.println(((Element)child).getTag());
//            }
            if(!child->isTextNode() && child->getTag()->isInHead()){
                cout<<("add to head")<<endl;
                head->appendChild(child);
                child->setParent(head);
            }else{
                body->appendChild(child);
                child->setParent(body);
            }
            child->updateIndex();
            html->removeChild(child);
        }
        if(body->getIndex() == 0){
            html->appendChild(html->removeChild(body));
            body->updateIndex();
        }
        head->updateIndex();
        return true;
    }


    shared_ptr<Tag> parse(shared_ptr<Element> parent){
        shared_ptr<Tag> pTag = parent->getTag();
        if(pTag->isNoSubTag() || pTag->getName() == "script"){ // 标签不允许有子标签或者是文本节点
            return parseTextTag(parent);
        }
        bool parseAll = parent->getDepth() < maxParsingDepth; // 判断是否解析到最大解析深度
        while(true){
            if(!buffer.canGo()) // 判断是否有下一个标签或文本
                break;
            int siblings = parent->getChildrenSize();
            if(parseAll){ // 允许解析
                int textFrom = buffer.getPosition();
                buffer.moveToUnblankChar();
                if(buffer.get() != TAG_START_FLAG){ // 将文本节点添加到父节点的子节点列表中
                    Element text = Element(buffer.copyOfRange(textFrom, buffer.moveTo(TAG_START_FLAG)), parent, siblings++);
                    parent->appendChild(shared_ptr<Element>(&text));
                }
            }else{ // 移动到下一个标签的开始部分
                buffer.moveToUnblankChar();
                if(buffer.get() != TAG_START_FLAG){ // 文本节点
                    buffer.moveTo(TAG_START_FLAG);
                }
            }
            string name = getTagName(); // 获取标签名
            if(name[0] == TAG_CLOSING_FLAG){ // 标签为关闭标签
                buffer.moveTo(TAG_END_FLAG);
                string tag = name.substr(1);
                if(tag == pTag->getName()) // 为当前父节点的结束标签，返回空
                    return nullptr;
                else{
                    shared_ptr<Tag> errTag = getTag(tag);
                    if(parent->getParentByTag(errTag) != nullptr)
                        return errTag;
                }
            }
            // 未遇到结束标签，遇到新的开始标签，继续解析
            shared_ptr<Tag> tag = getTag(name), endTag = nullptr;
            Element element(tag, parent, siblings);
            shared_ptr<Element> ePtr(&element);
            Consumer<Node> action = tag.getAction();
            if(parseAll || action != nullptr){ // 未到最大解析深度，或者tag绑定了事件，继续解析节点属性并添加子节点，否则跳过
                ePtr->setAttrs(getAttributesFromTag()); // 解析该元素的属性
                if(parseAll){
                    parent->appendChild(ePtr);
                }
            }else{
                buffer.moveTo(TAG_END_FLAG);
            }
            if(action != nullptr)
                action.accept(ePtr);
            if(!tag->isEmpty()) // 解析非自关闭标签
                endTag = parse(ePtr);
            if(endTag != nullptr){ // 解决标签闭合错误的问题
                if(endTag == parent->getTag())
                    break;
                else
                    return endTag;
            }
        }
        return nullptr;
    }

    shared_ptr<Tag> parseTextTag(shared_ptr<Element> parent){
        if(!buffer.canGo())
            return nullptr;
        int textFrom = buffer.getPosition();
        while(true){
            buffer.moveAfter(TAG_START_FLAG);
            if(buffer.get() != '/')
                continue;
            buffer.next();
            int textEnd = buffer.getPosition();
            string tagName= buffer.copyOfRange(textEnd, buffer.moveUntilBlankCharOr(TAG_END_FLAG));
            if(parent->isTagElement(tagName)){
                if(textFrom < textEnd - 2){
                    Element text(buffer.copyOfRange(textFrom, textEnd - 2), parent, 0);
                    parent->appendChild(shared_ptr<Element>(&text));
                }
                return nullptr;
            }
        }
    }

    string getTagName(){
        if(buffer.noNext(TAG_START_FLAG))
            return "";
        byte v;
        while((v = buffer.get()) == '!' || v == '?'){ // TODO 注释的解析，getTagName方法优化
            if(buffer.getNext() == '-')
                buffer.moveTo(COMMENT_END_FLAG);
            buffer.moveTo(TAG_END_FLAG); // <!--注释--> ?
            if(buffer.noNext(TAG_START_FLAG)) //没有下一个标签
                return "";
        }
        int from = buffer.moveToUnblankChar(); // 移动到非空白字符
        buffer.moveUntilBlankCharOr(TAG_END_FLAG); // >
        string bs = buffer.copyOfRange(from, buffer.getPosition());
        for(int i = 0; i < bs.size(); i++){
            v = bs[i];
            if(v >= 'A' && v <= 'Z'){
                v = (byte)(v + 32);
                bs[i] = v;
            }
        }
        return bs;
    }

    vector<shared_ptr<Attribute>> getAttributesFromTag(){
        buffer.moveToUnblankChar(); // 跳过空白字符
        vector<shared_ptr<Attribute>> result;
        if(buffer.get() == '>'){ // 标签结束，没有属性
            return result;
        }
        string arr = buffer.getBuffer();
        while(true){
            int from = buffer.moveToUnblankChar(), pos = from;
            byte c;
            while((c = arr[pos]) > 32 && c != '=' && c != '>' && c != '/') // TODO 简化
                pos++;
            if(pos == from)
                break;
            Attribute attr;
            shared_ptr<Attribute> attrPtr(&attr);
            result.push_back(attrPtr);
            attrPtr->key = buffer.copyOfRange(from, pos);

            buffer.setPosition(pos);
            pos = buffer.moveToUnblankChar();
            if((c = arr[pos]) == '>' || c == '/') // 结束标签
                break;
            if(c != '=')
                continue;
            buffer.next();
            pos = buffer.moveToUnblankChar();
            if((c = arr[pos]) == '"' || c == '\''){
                from = pos + 1;
                buffer.next();
                attrPtr->value = buffer.copyOfRange(from, buffer.moveTo(c));
                buffer.next();
            }else{
                from = pos;
                attrPtr->value = buffer.copyOfRange(from, buffer.moveUntilBlankCharOr(TAG_END_FLAG));
            }
            extractURLs(attrPtr);
        }
        buffer.moveTo(TAG_END_FLAG);
        return result;
    }

    void extractURLs(shared_ptr<Attribute> attribute) {
        if (attribute->isKey("href")) {
            string val = attribute->getValue();
            if (*(val.begin().base()) == '#') { // TODO 存疑
                return;
            }
            this->urls.push_back(val);
        }
    }

    string wrapByteArrayToString(byte byteArray[]) {
        return string(reinterpret_cast<char*>(byteArray), sizeof(byteArray));
    }

    int getMaxParsingDepth() const{
        return maxParsingDepth;
    }
    void setMaxParsingDepth(int maxParsingDepth){
        this->maxParsingDepth = maxParsingDepth;
    }

private:
    string url;
    string host;
    int maxParsingDepth = 6; // 最大解析深度
    vector<string> urls;
    string content; // html文章内容
    ByteBuffer buffer;
    shared_ptr<Element> html; // html 根元素
    MAP_STRING_TAG localTags; // 字符串到标签的映射

    shared_ptr<Tag> getTag(const string &str) {
        if(localTags.find(str) != localTags.end()) {
            return  localTags[str];
        }
        localTags[str] = Tag().getTag(str);
        return localTags[str];
    }

    byte TAG_START_FLAG = '<';
    byte TAG_END_FLAG = '>';
    byte TAG_CLOSING_FLAG = '/';
    byte COMMENT_END_FLAG[3] = {'-', '-', '>'};

};
