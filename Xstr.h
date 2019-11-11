#ifndef XSTR_H
#define XSTR_H
#include <windows.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <conio.h>

class XStr
{
public:
 XStr( int hashlen, int strlen, int key, ... );
 virtual ~XStr( );
 char * c();
 
private:
 DWORD_PTR * m_charList;
 DWORD_PTR * m_hashList;
 char * m_retBuf;
 int m_strLength;
 int m_hashLength;
 int m_key;
};
 
#endif