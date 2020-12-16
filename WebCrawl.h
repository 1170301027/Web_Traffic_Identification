//
// Created by lenovo on 2020/12/9.
//
#include "winsock2.h"
#include <vector> // ��װ�˶�̬��С�����˳��������
#include <map>
#include <cstring>
#include "FileHandle.h"

#define MAX_PAGE_SIZE 65535
using namespace std;
//����URL������������������Դ��
bool parseUrl(const string & url, string & host, string & resource){
    if ( strlen(url.c_str()) > 2000 ) {
        return false;
    }

    const char * pos;
    if (url.find("http://") != string::npos) {
        pos = strstr(url.c_str(), "http://");
        pos += strlen("http://");
    } else if (url.find("https://") != string::npos) {
        pos = strstr(url.c_str(), "https://");
        pos += strlen("https://");
    }
    if( pos==nullptr ) pos = url.c_str();

    if( strstr( pos, "/")==nullptr ) {
        string temp = pos;
        temp.append("/");
        pos = temp.c_str();
    }

//    string temp = pos;
//    host = temp.substr(0,temp.find('/'));
//    cout<<"host :: "<<host<<endl<<endl;

    char pHost[100];
    char pResource[2000];
    sscanf( pos, "%[^/]%s", pHost, pResource );
    host = pHost;
    resource = pResource;

    return true;
}

//ʹ��Get���󣬵õ���Ӧ
bool getHttpResponse(const string & url, char * &response, int &bytesRead ){
    string host, resource;

    if(!parseUrl(url, host, resource)){
        cout << "Can not parse the url"<<endl;
        return false;
    }

    //����socket
    struct hostent * hp= gethostbyname( host.c_str() );
    if( hp==nullptr ){
        cout<< "Can not find host address"<<endl;
        return false;
    }

    SOCKET sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( sock == -1 || sock == -2 ){
        cout << "Can not create sock."<<endl;
        return false;
    }

    //������������ַ
    SOCKADDR_IN sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons( 80 );
    //char addr[5];
    //memcpy( addr, hp->h_addr, 4 );
    //sa.sin_addr.s_addr = inet_addr(hp->h_addr);
    memcpy( &sa.sin_addr, hp->h_addr, 4 );

    //��������
    if( 0!= connect( sock, (SOCKADDR*)&sa, sizeof(sa) ) ){
        cout << "Can not connect: "<< url <<endl;
        closesocket(sock);
        return false;
    };

    //׼����������
    string request = "GET " + resource + " HTTP/1.1\r\nHost:" + host + "\r\nConnection:Close\r\n\r\n";
//    cout<<request<<endl;

    //��������
    if( SOCKET_ERROR ==send( sock, request.c_str(), request.size(), 0 ) ){
        cout << "send error" <<endl;
        closesocket( sock );
        return false;
    }

    //��������
    int m_nContentLength = MAX_PAGE_SIZE;
    char *pageBuf = (char *)malloc(m_nContentLength);
    memset(pageBuf, 0, m_nContentLength);

    bytesRead = 0;
    int ret = 1;
    cout <<"Read: ";
    while(ret > 0){
        ret = recv(sock, pageBuf + bytesRead, m_nContentLength - bytesRead, 0);

        if(ret > 0)
        {
            bytesRead += ret;
        }

        if( m_nContentLength - bytesRead<100){
            cout << "\nRealloc memorry"<<endl;
            m_nContentLength *=2;
            pageBuf = (char*)realloc( pageBuf, m_nContentLength);       //���·����ڴ�
        }
        cout << ret <<" ";
    }
    cout <<endl;

    pageBuf[bytesRead] = '\0';
    response = pageBuf;
    closesocket( sock );
    return true;
    //cout<< response <<endl;
}

string getResponseFromUrl(const string& url)
{
    WSADATA wsaData;
    if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0 ){
        return "";
    }
    char* result;
    int byteLength;
    if (!getHttpResponse(url, result, byteLength)) {
        cout<<"Error ��"<<url<<endl;
    }
    WSACleanup();
    return result;
}

// ������Ӧ���ģ�������Ӧͷ������Ӧ���塣
vector<string> parseResponse(const string & response)
{
    vector<string> result;
    string response_head = response.substr(0,response.find("\r\n\r\n"));
    string response_data = strstr(response.c_str(), "\r\n\r\n");
    cout << response_head << endl;
    return result;
}

// ������Ӧͷ������ȡ��ֵ��
auto parseResponseHeader(const string& head) {
    vector<string*> keys;
    string rearString = head;
    int pos = 0;
    while ((pos = rearString.find("\r\n")) != 0) {
        int front = 0;
        string line = rearString.substr(front,pos);
        rearString = rearString.substr(pos + strlen("\r\n"));
        if (line.find("HTTP") != string::npos) {
            continue;
        }
        auto *key_to_value = new string[2];
        key_to_value[0] = line.substr(0,line.find(": "));
        key_to_value[1] = line.substr(line.find(": ") + strlen(": "));
        keys.push_back(key_to_value);
    }
    return keys;
}
