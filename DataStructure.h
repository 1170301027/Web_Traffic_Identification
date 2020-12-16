/**************************************************************
 * FileName : DataStructure
 * Description : 定义解析阶段的数据结构
 * Author : lenovo 
 * Date : 2020/12/15.
 *************************************************************/

#ifndef WEB_TRAFFIC_IDENTIFICATION_DATASTRUCTURE_H
#define WEB_TRAFFIC_IDENTIFICATION_DATASTRUCTURE_H

#endif //WEB_TRAFFIC_IDENTIFICATION_DATASTRUCTURE_H
#include <string>
#include <utility>
#include <vector>
#include <list>
using namespace std;
// 标签类
class Tag {
public:
    explicit Tag(string name) : name(std::move(name)) {}
    string getName() { return this->name; }

    bool operator==(const Tag &rhs) const {
        return name == rhs.name;
    }

    bool operator!=(const Tag &rhs) const {
        return !(rhs == *this);
    }

private:
    string name;
};

// 属性类
class Attribute {
public:
    Attribute(string key, string value) : key(std::move(key)), value(std::move(value)) {}

    const string &getKey() const {
        return key;
    }

    const string &getValue() const {
        return value;
    }

private:
    string key;
    string value;
};

// 所有节点
class Node {
public:
    Node() {this->depth = 0; this->index = 0;}
    Node(int depth, const Node &father , int index) {
        this->depth = depth;
        Father = father;
        this->index = index;
    }
    static Node getFather() { return Father; }
    int getDepth() const { return this->depth; }

    bool operator==(const Node &rhs) const {
        return depth == rhs.depth &&
               index == rhs.index;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }

    int getIndex() const { return this->index; }
private:
    int depth;
    static Node Father;
    int index;
};

// 文本节点, 没有子节点的
class TextNode : Node {
public:
    TextNode(int depth, const Node &father, int index, const string &content) : Node(depth, father, index) {
        this->content = content;
    }

    bool operator==(const TextNode &rhs) const {
        return static_cast<const Node &>(*this) == static_cast<const Node &>(rhs) &&
               content == rhs.content;
    }

    bool operator!=(const TextNode &rhs) const {
        return !(rhs == *this);
    }

    const string &getContent() const {
        return content;
    }

private:
    string content;
};

// 元素节点
class Element : Node {
public:
    Element(int depth, const Node &father, int index, Tag tag) : Node(depth, father, index), tag(std::move(tag)) {}

    bool appendChild(const Node &child) {
        this->children.push_back(child);
    }

    bool appendAttr(const Attribute &attribute) {
        this->attrs.push_back(attribute);
    }

    const Tag &getTag() const {
        return tag;
    }

    const list <Node> &getChildren() const {
        return children;
    }

    const vector<Attribute> &getAttrs() const {
        return attrs;
    }

    int getChildrenSize() {
        return children.size();
    }

    bool operator==(const Element &rhs) const {
        return static_cast<const Node &>(*this) == static_cast<const Node &>(rhs) &&
               tag == rhs.tag &&
               children == rhs.children &&
               attrs == rhs.attrs;
    }

    bool operator!=(const Element &rhs) const {
        return !(rhs == *this);
    }

private:
    Tag tag;
    list<Node> children;
    vector<Attribute> attrs;
};