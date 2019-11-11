#include "XStr.h"
 
XStr::XStr( int hashlen, int len, int key, ... )
{
 va_list vl;
 
 va_start( vl, key );
 
 m_hashLength = hashlen;
 m_strLength  = len;
 m_key   = key;
 
 int nBytes = 0;
 int nDecryptedBytes = 0;
 
 m_charList = new DWORD_PTR[ len ];
 
 for( int i = 0; i < m_hashLength; i++ )
 {
  DWORD_PTR dwHash = va_arg( vl, DWORD_PTR );
 
  for( int j = 0; j < 4; j++ )
  {
   WORD wWord = HIWORD( dwHash );
 
   if( j >= 2 )
    wWord = LOWORD( dwHash );
    
   switch( j )
   {
   case 0:
    m_charList[ nDecryptedBytes ] = HIBYTE( wWord );
    break;
   case 1:
    m_charList[ nDecryptedBytes ] = LOBYTE( wWord );
    break;
   case 2:
    m_charList[ nDecryptedBytes ] = HIBYTE( wWord );
    break;
   case 3:
    m_charList[ nDecryptedBytes ] = LOBYTE( wWord );
    break;   
   }
 
   nDecryptedBytes++;
 
   if( nDecryptedBytes >= len )
    break;
  }  
 } 
 
 va_end( vl );
}
 
XStr::~XStr( )
{
 delete [] m_retBuf;
 
 m_retBuf = NULL;
}
 
char * XStr::c( )
{
 m_retBuf = new char[ m_strLength + 1 ];
 
 for( int i = 0; i < m_strLength; i++ )
 {
  m_retBuf[ i ] = (char)m_charList[ i ];
 
  m_retBuf[ i ] ^= m_key;
  m_key += 1;
  m_key %= 256;
 }
 
 m_retBuf[ m_strLength ] = '\0';
 
 delete [] m_charList;
 delete [] m_hashList;
 
 m_charList = NULL;
 m_hashList = NULL;
 
 return m_retBuf;
}