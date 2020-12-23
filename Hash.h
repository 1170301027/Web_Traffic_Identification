/**************************************************************
 * FileName : Hash
 * Description : hash函数，MD5算法
 * Author : lenovo 
 * Date : 2020/12/17.
 *************************************************************/

#ifndef WEB_TRAFFIC_IDENTIFICATION_HASH_H
#define WEB_TRAFFIC_IDENTIFICATION_HASH_H

#endif //WEB_TRAFFIC_IDENTIFICATION_HASH_H
#include <iostream>
using namespace std;
class MD5 {
public:
    void printK() {
        for (int i : K) {
            cout<<hex<<i<<endl;
        }
    }
private:
    signed int K[64] = {
            static_cast<int>(0xd76aa478), static_cast<int>(0xe8c7b756), 0x242070db, static_cast<int>(0xc1bdceee), static_cast<int>(0xf57c0faf), 0x4787c62a, static_cast<int>(0xa8304613), static_cast<int>(0xfd469501), 0x698098d8,
            static_cast<int>(0x8b44f7af), static_cast<int>(0xffff5bb1), static_cast<int>(0x895cd7be), 0x6b901122, static_cast<int>(0xfd987193), static_cast<int>(0xa679438e), 0x49b40821, static_cast<int>(0xf61e2562), static_cast<int>(0xc040b340),
            0x265e5a51, static_cast<int>(0xe9b6c7aa), static_cast<int>(0xd62f105d), 0x02441453, static_cast<int>(0xd8a1e681), static_cast<int>(0xe7d3fbc8), 0x21e1cde6, static_cast<int>(0xc33707d6), static_cast<int>(0xf4d50d87),
            0x455a14ed, static_cast<int>(0xa9e3e905), static_cast<int>(0xfcefa3f8), 0x676f02d9, static_cast<int>(0x8d2a4c8a), static_cast<int>(0xfffa3942), static_cast<int>(0x8771f681), 0x6d9d6122, static_cast<int>(0xfde5380c),
            static_cast<int>(0xa4beea44), 0x4bdecfa9, static_cast<int>(0xf6bb4b60), static_cast<int>(0xbebfbc70), 0x289b7ec6, static_cast<int>(0xeaa127fa), static_cast<int>(0xd4ef3085), 0x04881d05, static_cast<int>(0xd9d4d039),
            static_cast<int>(0xe6db99e5), 0x1fa27cf8, static_cast<int>(0xc4ac5665), static_cast<int>(0xf4292244), 0x432aff97, static_cast<int>(0xab9423a7), static_cast<int>(0xfc93a039), 0x655b59c3, static_cast<int>(0x8f0ccc92),
            static_cast<int>(0xffeff47d), static_cast<int>(0x85845dd1), 0x6fa87e4f, static_cast<int>(0xfe2ce6e0), static_cast<int>(0xa3014314), 0x4e0811a1, static_cast<int>(0xf7537e82), static_cast<int>(0xbd3af235), 0x2ad7d2bb,
            static_cast<int>(0xeb86d391)
    };
    int SHIFT[65] = {
            7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
            14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15,
            21, 6, 10, 15, 21
    };
    int varA = 0x67452301;
    int varB = static_cast<int>(0xefcdab89);
    int varC = static_cast<int>(0x98badcfe);
    int varD = 0x10325476;

    int shift(int num, int shift){
        return (num << shift) | ((unsigned int)num >> (32 - shift));
    }

};