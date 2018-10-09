/************************************************************
//   This File: base64.cpp
// Description: Implementation of standard Base 64 encoding. 
//              The encoded string does NOT contain new lines.
//  
// THIS CODE IS PROVIDED "AS IS". THERE IS NO WARRANTY OF ANY
// FORM. IT CAN BE USED OR REDISTRIBUTED WITH NO MODIFICATION
// FREELY AS LONG AS THIS NOTICE IS INCLUDED.
//
//        xTy Technology (http://www.xtytech.com/)
//              All rights reserved, 2001
**************************************************************/
//This is the customized version of Base64 encode, with
//no new line.
#include "base64.h"
#define XTY62  '+'
#define XTY63  '/'
#define XTYPAD '='
 
//assume input != NULL.
unsigned char *Base64Decode(const char *pcszInput, unsigned int *puOutLen){
	char map[256] = {0};
	char i, c, *pBuf=new char[strlen(pcszInput)+1];
    unsigned int j, uBufLen;

    memset(map,0XFF,sizeof(map));
    for(i='A',map['A']=0; i<'Z'; map[i+1]=map[i]+1,i++);
    for(i='a',map['a']=26; i<='z'; map[i+1]=map[i]+1,i++);
    for(i='0',map['0']=52; i<='9'; map[i+1]=map[i]+1,i++);
    map[XTY62]=62; map[XTY63]=63;

    uBufLen=0; c=pcszInput[0];
    while(c!='\0' && c!=XTYPAD)
	{
        pBuf[uBufLen]=map[c];

        if(pBuf[uBufLen]>=0)
            uBufLen++;
        c=*(++pcszInput);
    };
    pBuf[uBufLen]='\0';

    unsigned int uSegCnt=uBufLen/4;
    unsigned char *pRet=new unsigned char[(uSegCnt+1)*3], *pTmp=pRet;

    //full segments.
    char *ptr=pBuf;
    for(j=0; j<uSegCnt; j++){
        *pTmp++=((ptr[0]<<2)|(ptr[1]>>4));
        *pTmp++=((ptr[1]<<4)|(ptr[2]>>2));
        *pTmp++=((ptr[2]<<6)|ptr[3]);
        ptr+=4;
    };
    *puOutLen=uSegCnt*3;

    unsigned int uTailCnt=uBufLen%4;
    if(uTailCnt==2){
        *pTmp++=((ptr[0]<<2)|(ptr[1]>>4));
        (*puOutLen)++;
    }else if(uTailCnt==3){
        *pTmp++=((ptr[0]<<2)|(ptr[1]>>4));
        *pTmp++=((ptr[1]<<4)|(ptr[2]>>2));
        (*puOutLen)+=2;
    };

    delete[] pBuf;
    return pRet;
}


/****************************************************************

  From RFC 1341:

  The  Base64   Content-Transfer-Encoding   is   designed   to
  represent  arbitrary  sequences  of octets in a form that is
  not humanly readable.  The encoding and decoding  algorithms
  are simple, but the encoded data are consistently only about
  33 percent larger than the unencoded data.  This encoding is
  based on the one used in Privacy Enhanced Mail applications,
  as defined in RFC 1113.   The  base64  encoding  is  adapted
  from  RFC  1113, with one change:  base64 eliminates the "*"
  mechanism for embedded clear text.
  
  A 65-character subset of US-ASCII is used, enabling  6  bits
  to  be  represented per printable character. (The extra 65th
  character, "=", is used  to  signify  a  special  processing
  function.)
  
  NOTE:  This subset has the important  property  that  it  is
  represented   identically   in  all  versions  of  ISO  646,
  including US ASCII, and all characters  in  the  subset  are
  also  represented  identically  in  all  versions of EBCDIC.
  Other popular encodings, such as the encoding  used  by  the
  UUENCODE  utility  and the base85 encoding specified as part
  of Level 2 PostScript, do not share  these  properties,  and
  thus  do  not  fulfill the portability requirements a binary
  transport encoding for mail must meet.
  
  The encoding process represents 24-bit groups of input  bits
  as  output  strings of 4 encoded characters. Proceeding from
  left  to  right,  a  24-bit  input  group   is   formed   by
  concatenating  3  8-bit input groups. These 24 bits are then
  treated as 4 concatenated 6-bit groups,  each  of  which  is
  translated  into a single digit in the base64 alphabet. When
  encoding a bit stream  via  the  base64  encoding,  the  bit
  stream  must  be  presumed  to  be  ordered  with  the most-
  significant-bit first.  That is, the first bit in the stream
  will be the high-order bit in the first byte, and the eighth
  bit will be the low-order bit in the first byte, and so on.
  
  Each 6-bit group is used as an index into  an  array  of  64
  printable  characters. The character referenced by the index
  is placed in the output string. These characters, identified
  in  Table  1,  below,  are  selected so as to be universally
  representable,  and  the  set   excludes   characters   with
  particular  significance to SMTP (e.g., ".", "CR", "LF") and
  to the encapsulation boundaries  defined  in  this  document
  (e.g., "-").

                      Table 1: The Base64 Alphabet
 
       Val/Enc        Val/Enc         Val/Enc         Val/Enc
       0 A            17 R            34 i            51 z
       1 B            18 S            35 j            52 0
       2 C            19 T            36 k            53 1
       3 D            20 U            37 l            54 2
       4 E            21 V            38 m            55 3
       5 F            22 W            39 n            56 4
       6 G            23 X            40 o            57 5
       7 H            24 Y            41 p            58 6
       8 I            25 Z            42 q            59 7
       9 J            26 a            43 r            60 8
      10 K            27 b            44 s            61 9
      11 L            28 c            45 t            62 +
      12 M            29 d            46 u            63 /
      13 N            30 e            47 v
      14 O            31 f            48 w         (pad) =
      15 P            32 g            49 x
      16 Q            33 h            50 y

  The output stream (encoded bytes)  must  be  represented  in
  lines  of  no more than 76 characters each.  All line breaks
  or other characters not found in Table 1 must be ignored  by
  decoding  software.   In  base64 data, characters other than
  those in  Table  1,  line  breaks,  and  other  white  space
  probably  indicate  a  transmission  error,  about  which  a
  warning  message  or  even  a  message  rejection  might  be
  appropriate under some circumstances.
  
  Special processing is performed if fewer than  24  bits  are
  available  at  the  end  of  the data being encoded.  A full
  encoding quantum is always completed at the end of  a  body.
  When  fewer  than  24  input  bits are available in an input
  group, zero bits  are  added  (on  the  right)  to  form  an
  integral number of 6-bit groups.  Output character positions
  which are not required to represent actual  input  data  are
  set  to  the  character  "=".   Since all base64 input is an
  integral number of octets,  only  the  following  cases  can
  arise:  (1)  the  final  quantum  of  encoding  input  is an
  integral multiple of  24  bits;  here,  the  final  unit  of
  encoded  output will be an integral multiple of 4 characters
  with no "=" padding, (2) the final quantum of encoding input
  is  exactly  8  bits; here, the final unit of encoded output
  will  be  two  characters  followed  by  two   "="   padding
  characters,  or  (3)  the final quantum of encoding input is
  exactly 16 bits; here, the final unit of encoded output will
  be three characters followed by one "=" padding character.
  
  Care must be taken to use the proper octets for line  breaks
  if base64 encoding is applied directly to text material that
  has not been converted to  canonical  form.  In  particular,
  text  line  breaks  should  be converted into CRLF sequences
  prior to base64 encoding. The important  thing  to  note  is
  that this may be done directly by the encoder rather than in
  a prior canonicalization step in some implementations.

 ****************************************************************/

/*
 * Base64 encoder function 
 */
#define	BASE64_PAD	"="
static	char	base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"BASE64_PAD;

 int ToB64Enc(const char *szStr, char *s , int iLen )
 {
   char szEnc[4096] ;
   int i, j ;
   j = 0 ;

   memset( (char *) szEnc , 0 , sizeof(szEnc) ) ;
   /* Encode 3 bytes at a time. */
   for ( i = 0; i < (iLen - (iLen % 3 )) ; i += 3 )
   {
     szEnc[j] = base64_table[ (szStr[i] & 0xfc) >> 2 ] ;
     szEnc[j+1] = base64_table[ ((szStr[i] & 0x03) << 4) | ((szStr[i+1] & 0xf0) >> 4) ];
     szEnc[j+2] = base64_table[ ((szStr[i+1] & 0x0f) << 2) | ((szStr[i+2] & 0xc0) >> 6) ];
     szEnc[j+3] = base64_table[ (szStr[i+2] & 0x3f) ];
     j += 4 ;
   }

   i = iLen - (iLen % 3 ) ; /* Where we left off before  */
   switch (iLen % 3 )
   {
	   case 2 : /* need to padding 1 character */
	   {
	     szEnc[j] = base64_table[ (szStr[i] & 0xfc) >> 2 ];
	     szEnc[j+1] = base64_table[ ((szStr[i] & 0x03) << 4 ) | ((szStr[i+1] & 0xf0) >> 4) ] ;
	     szEnc[j+2] = base64_table[ (szStr[i+1] & 0x0f) << 2 ] ;
	     szEnc[j+3] = base64_table[64] ;
	     break ;
	   }
           case 1 : /* need to padding 2 character */
	   {
	     szEnc[j] = base64_table[ (szStr[i] & 0xfc) >> 2 ];
	     szEnc[j+1] = base64_table[ (szStr[i] & 0x03) << 4 ] ;
	     szEnc[j+2] = base64_table[64] ; /* Pad */
	     szEnc[j+3] = base64_table[64] ; /* Pad */
	     break ;
	   }
   }

   szEnc[j+4] = '\0' ;
   strncpy( s, szEnc, strlen(szEnc) );
   s[ strlen(szEnc)]=0;
   return (0);
}

