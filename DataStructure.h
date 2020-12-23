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
#include <memory>
#include "Hash.h"

using namespace std;
using std::shared_ptr;
// 标签类
class Tag {
public:
    explicit Tag(string name) : name(std::move(name)) {init();}
    Tag() {init();}

    Tag(string name, int id) : name(std::move(name)), id(id) {init();}

    void init() {
        string TAGS[] = {
                // "<!-- -->",
                "!DOCTYPE",
                "a",          // 定义超文本链接
                "abbr",       // 定义缩写
                "acronym",    // 定义只取首字母的缩写，不支持HTML5
                "address",    // 定义文档作者或拥有者的联系信息
                "area",       // 定义图像映射内部的区域
                "article",    // 定义一个文章区域
                "aside",      // 定义页面的侧边栏内容
                "audio",      // 定义音频内容
                "b",          // 定义文本粗体
                "base",       // 定义页面中所有链接的默认地址或默认目标
                "basefont",   // HTML5不支持，不赞成使用。定义页面中文本的默认字体、颜色或尺寸
                "bdi",        // 允许您设置一段文本，使其脱离其父元素的文本方向设置
                "bdo",        // 定义文字方向
                "bgsound",    // 背景音乐
                "big",        // 定义大号文本，HTML5不支持
                "blockquote", // 定义长的引用
                "body",       // 定义文档的主体
                "br",         // 定义换行
                "button",     // 定义一个点击按钮
                "canvas",     // 定义图形，比如图表和其他图像,标签只是图形容器，您必须使用脚本来绘制图形
                "caption",    // 定义表格标题
                "cite",       // 定义引用(citation)
                "code",       // 定义计算机代码文本
                "col",        // 定义表格中一个或多个列的属性值
                "colgroup",   // 定义表格中供格式化的列组
                "command",    // 定义命令按钮，比如单选按钮、复选框或按钮
                "datalist",   // 定义选项列表。请与 input 元素配合使用该元素，来定义 input 可能的值
                "del",        // 定义被删除文本
                "details",    // 用于描述文档或文档某个部分的细节
                "dfn",        // 定义定义项目
                "dialog",     // 定义对话框，比如提示框
                "dd",         // 定义定义列表中项目的描述
                "div",        // 定义文档中的节
                "dl",         // 定义列表详情
                "dt",         // 定义列表中的项目
                "em",         // 定义强调文本
                "embed",      // 定义嵌入的内容，比如插件
                "fieldset",   // 定义围绕表单中元素的边框
                "figcaption", // 定义<figure> 元素的标题
                "figure",     // 规定独立的流内容（图像、图表、照片、代码等等）
                "font",       // HTML5不支持，不赞成使用。定义文字的字体、尺寸和颜色
                "footer",     // 定义 section 或 document 的页脚
                "form",       // 定义了HTML文档的表单
                "frame",      // 定义框架集的窗口或框架
                "frameset",   // 定义框架集
                "h1",         // to <h6>	定义 HTML 标题
                "h2",         //
                "h3",         //
                "h4",         //
                "h5",         //
                "h6",         //
                "head",       // 定义关于文档的信息
                "header",     // 定义了文档的头部区域
                "hgroup",     //
                "hr",         // 定义水平线
                "html",       // 定义 HTML 文档
                "i",          // 定义斜体字
                "iframe",     // 定义内联框架
                "img",        // 定义图像
                "input",      // 定义输入控件
                "ins",        // 定义被插入文本
                "kbd",        // 定义键盘文本
                "keygen",     // 规定用于表单的密钥对生成器字段
                "label",      // 定义 input 元素的标注
                "legend",     // 定义 fieldset 元素的标题
                "li",         // 定义列表的项目
                "link",       // 定义文档与外部资源的关系
                "main",       //
                "math",       //
                "map",        // 定义图像映射
                "mark",       // 定义带有记号的文本。请在需要突出显示文本时使用 <m> 标签
                "menu",       // 不赞成使用。定义菜单列表
                "menuitem",   //
                "meta",       // 定义关于 HTML 文档的元信息
                "meter",      // 定义度量衡。仅用于已知最大和最小值的度量
                "nav",        // 定义导航链接的部分
                "noframes",   // 定义针对不支持框架的用户的替代内容。HTML5不支持
                "noscript",   // 定义针对不支持客户端脚本的用户的替代内容
                "object",     // 定义内嵌对象
                "ol",         // 定义有序列表
                "optgroup",   // 定义选择列表中相关选项的组合
                "option",     // 定义选择列表中的选项
                "output",     // 定义不同类型的输出，比如脚本的输出
                "p",          // 定义段落
                "param",      // 定义对象的参数
                "plaintext",  //
                "pre",        // 定义预格式文本
                "progress",   // 定义运行中的进度（进程）
                "q",          // 定义短的引用
                "rp",         // <rp> 标签在 ruby 注释中使用，以定义不支持 ruby 元素的浏览器所显示的内容
                "rt",         // <rt> 标签定义字符（中文注音或字符）的解释或发音
                "ruby",       // <ruby> 标签定义 ruby 注释（中文注音或字符）
                "s",          // 不赞成使用。定义加删除线的文本
                "samp",       // 定义计算机代码样本
                "script",     // 定义客户端脚本
                "section",    // <section> 标签定义文档中的节（section、区段）。比如章节、页眉、页脚或文档中的其他部分
                "select",     // 定义选择列表（下拉列表）
                "small",      // 定义小号文本
                "source",     // <source> 标签为媒介元素（比如 <video> 和 <audio>）定义媒介资源
                "span",       // 定义文档中的节
                "strong",     // 定义强调文本
                "style",      // 定义文档的样式信息
                "sub",        // 定义下标文本
                "summary",    // <summary> 标签包含 details 元素的标题，"details" 元素用于描述有关文档或文档片段的详细信息
                "sup",        // 定义上标文本
                "svg",        //
                "table",      // 定义表格
                "tbody",      // 定义表格中的主体内容
                "td",         // 定义表格中的单元
                "template",   //
                "textarea",   // 定义多行的文本输入控件
                "tfoot",      // 定义表格中的表注内容（脚注）
                "th",         // 定义表格中的表头单元格
                "thead",      // 定义表格中的表头内容
                "time",       // 定义日期或时间，或者两者
                "title",      // 定义文档的标题
                "tr",         // 定义表格中的行
                "track",      // <track> 标签为诸如 video 元素之类的媒介规定外部文本轨道
                "tt",         // 定义打字机文本
                "u",          // 不赞成使用。定义下划线文本
                "ul",         // 定义无序列表
                "var",        // 定义文本的变量部分
                "video",      // <video> 标签定义视频，比如电影片段或其他视频流
                "wbr"         // 规定在文本中的何处适合添加换行符。
        };
        for (const string& str : TAGS) {
            TAGS_MAP.insert(pair<string, Tag>(str, Tag(str)));
        }
        string TAGS_WITH_ID[] = {
                "a", "article", "aside", "b", "blockquote", "body", "br", "button", "canvas", "code", "del", "dd",
                "div", "dl", "dt", "em", "footer", "form", "frame", "frameset", "h1", "h2", "h3", "h4", "h5", "h6",
                "header", "hr", "i", "iframe", "img", "input", "label", "li", "main", "menu", "menuitem", "nav",
                "noframes", "noscript", "ol", "option", "p", "pre", "script", "section", "select", "source", "span",
                "strong", "style", "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "tr", "tt", "u", "ul",
                // ############################上半部分标签在 body 里经常出现：共62个，不要修改############################
                "abbr", "acronym", "address", "area", "audio", "base", "basefont", "bdi", "bdo", "bgsound", "big",
                "caption", "cite", "col", "colgroup", "command", "datalist", "details", "dfn", "dialog", "embed",
                "fieldset", "figcaption", "figure", "font", "head", "hgroup", "html", "ins", "kbd", "keygen", "legend",
                "link", "map", "mark", "math", "meta", "meter", "object", "optgroup", "output", "param", "plaintext",
                "progress", "q", "rp", "rt", "ruby", "s", "samp", "small", "sub", "summary", "sup", "svg", "template",
                "time", "title", "track", "var", "video", "wbr"
        };
        for (const string& str : TAGS_WITH_ID) {
            Tag tag = TAGS_MAP[str];
            tag.id++;
        }
        string EMPTY_TAGS[] = {
                "area", "base", "basefont", "bgsound", "br", "col", "command", "embed", "frame", "hr", "img", "input",
                "keygen", "link", "menuitem", "meta", "param", "source", "track", "wbr"
        };
        for(const string& str : EMPTY_TAGS) {
            Tag tag = TAGS_MAP[str];
            tag.empty = true;
        }
        string BLOCK_TAGS[] = {
                "address", "article", "aside", "audio", "blockquote", "body", "canvas", "caption", "col", "colgroup",
                "dd", "del", "details", "div", "dl", "dt", "fieldset", "figcaption", "figure", "footer", "form",
                "frame", "frameset", "h1", "h2", "h3", "h4", "h5", "h6", "head", "header", "hgroup", "hr", "html",
                "ins", "li", "link", "main", "math", "menu", "meta", "nav", "noframes", "noscript", "ol", "p",
                "plaintext", "pre", "script", "section", "style", "svg", "table", "tbody", "td", "template", "tfoot",
                "th", "thead", "title", "tr", "ul", "video"
        };
        for(const string& str : BLOCK_TAGS) {
            Tag tag = TAGS_MAP[str];
            tag.block = true;
        }
        string INLINE_TAGS[] = {
                "a", "abbr", "acronym", "area", "b", "base", "basefont", "bdi", "bdo", "bgsound", "big", "br", "button",
                "cite", "code", "command", "datalist", "dfn", "dialog", "em", "embed", "font", "i", "iframe", "img",
                "input", "kbd", "keygen", "label", "legend", "map", "mark", "menuitem", "meter", "object", "optgroup",
                "option", "output", "param", "progress", "q", "rp", "rt", "ruby", "s", "samp", "select", "small",
                "source", "span", "strong", "sub", "summary", "sup", "textarea", "time", "track", "tt", "u", "var",
                "wbr"
        };
        for(const string& str : INLINE_TAGS) {
            Tag tag = TAGS_MAP[str];
            tag.inLine = true;
        }
        string TAGS_IN_HEAD[] = {
                "meta", "title", "link", "base", "style", "script", "noscript"
        };
        for(const string& str : TAGS_IN_HEAD) {
            Tag tag = TAGS_MAP[str];
            tag.inHead = true;
        }
        string TAGS_WITH_RESOURCE[] = {
                "link", "a", // href 属性
                "img", "script", "audio", "bgsound", "embed", "iframe", "source", // src 属性
                "object", // data 属性 TODO 对这些特殊标签做特殊提取，放大其在指纹中位置
        };
        for(const string& str : TAGS_WITH_RESOURCE) {
            Tag tag = TAGS_MAP[str];
            tag.res = true;
        }
        string NOT_ALLOW_SUB_TAGS[] = {
                "script", "style"
        };
        for(const string& str : NOT_ALLOW_SUB_TAGS) {
            Tag tag = TAGS_MAP[str];
            tag.noSubTag = true;
        }
        string CONTENT_LEVEL_TAGS[] = {
                "h1", "h2", "h3", "h4", "h5", "h6", "pre", "p", "section", "blockquote"
        };
        for(const string& str : CONTENT_LEVEL_TAGS) {
            Tag tag = TAGS_MAP[str];
            tag.contentLevel = true;
        }
    }

    Tag getTag(const string& str) {
        if (TAGS_MAP.find(str) == TAGS_MAP.end()) {
            return Tag(str, (byte)(0x80));
        }
        Tag tag = TAGS_MAP[str];

    }
    bool operator==(const Tag &rhs) const {
        return name == rhs.name;
    }

    bool operator!=(const Tag &rhs) const {
        return !(rhs == *this);
    }

    bool is(const string &str) {return strcmp(str.c_str(), name.c_str());}

    string getName() { return this->name; }

    int getId() const {
        return id;
    }

    const vector<string> &getAction() const {
        return action;
    }

    static const map<string, Tag> &getTagsMap() {
        return TAGS_MAP;
    }

    bool isEmpty() const {
        return empty;
    }

    bool isBlock() const {
        return block;
    }

    bool isInLine() const {
        return inLine;
    }

    bool isInHead() const {
        return inHead;
    }

    bool isRes() const {
        return res;
    }

    bool isNoSubTag() const {
        return noSubTag;
    }

    bool isContentLevel() const {
        return contentLevel;
    }

private:
    string name;
    int id;
    vector<string> action; // xingwei
    static map<string,Tag> TAGS_MAP;
    bool empty = false;
    bool block = false;
    bool inLine = false;
    bool inHead = false;
    bool res = false;
    bool noSubTag = false;
    bool contentLevel = false;
    // HTML 标签，目前共有 124 个

};

typedef std::map<string , Tag> MAP_STRING_TAG;

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

    bool operator==(const Attribute &rhs) const {
        return key == rhs.key &&
               value == rhs.value;
    }

    bool operator!=(const Attribute &rhs) const {
        return !(rhs == *this);
    }

    bool isKey(const string &str) {
        return strcmp(key.c_str(),str.c_str());
    }
private:
    string key;
    string value;
};

// 所有节点
class Node {
public:
    Node() {this->depth = 0; this->index = 0;}
    Node(int depth, int index) : depth(depth),index(index){}
    Node(int depth, int index, shared_ptr<Node> &father) : depth(depth), index(index), father(father){}
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
    shared_ptr<Node> father = nullptr;
    Node *sab;
    int index;
};

// 元素节点
class Element : public Node {
public:
    Element() {}
    Element(int depth, int index, const shared_ptr<Element> &father, Tag tag) : Node(depth, index), tag(std::move(tag)),father(father) {}

    Element(int depth, int index, const shared_ptr<Element> &father, string content) : Node(depth, index), content(std::move(content)), father(father), isTextnode(true){}

    void appendChild(const shared_ptr<Element> &child) {
        this->children.push_back(child);
    }

    void appendAttr(const Attribute &attribute) {
        this->attrs.push_back(attribute);
    }

    const Tag &getTag() const {
        return tag;
    }

    const list <shared_ptr<Element>> &getChildren() const {
        return children;
    }

    const vector<Attribute> &getAttrs() const {
        return attrs;
    }

    int getChildrenSize() {
        return children.size();
    }

    const shared_ptr<Element> &getFather() const {
        return father;
    }

    const string &getContent() const {
        return content;
    }

    bool isTextNode() const {
        return isTextnode;
    }

    bool isTagElement(const string &tagName) {
        return tagName == tag.getName();
    }

    bool operator==(const Element &rhs) const {
        return static_cast<const Node &>(*this) == static_cast<const Node &>(rhs) &&
               tag == rhs.tag &&
               children == rhs.children &&
               father == rhs.father &&
               attrs == rhs.attrs &&
               content == rhs.content &&
               isTextnode == rhs.isTextnode;
    }

    bool operator!=(const Element &rhs) const {
        return !(rhs == *this);
    }

private:
    Tag tag; // html 标签 <style>
    list<shared_ptr<Element>> children; // 子节点
    shared_ptr<Element> father; // 父节点
    vector<Attribute> attrs; // 节点属性集
    string content; // 如果为文本节点则有内容
    bool isTextnode = false; // 用于判断该节点是否为文本节点。
};

// 文本节点, 没有子节点的
class TextNode : public Node {
public:
    TextNode(int depth, int index, const shared_ptr<Element> &father, string content) : Node(depth, index) ,father(father),content(std::move(content)){}

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

    const shared_ptr<Element> &getFather() const {
        return father;
    }

private:
    string content;
    shared_ptr<Element> father;
};
