/************************************************************
//   This File: base64.h
// Description: Header file for the standard Base 64 encoding. 
//              The encoded string does NOT contain new lines.
//  
// THIS CODE IS PROVIDED "AS IS". THERE IS NO WARRANTY OF ANY
// FORM. IT CAN BE USED OR REDISTRIBUTED WITH NO MODIFICATION
// FREELY AS LONG AS THIS NOTICE IS INCLUDED.
//
//        xTy Technology (http://www.xtytech.com/)
//              All rights reserved, 2001
**************************************************************/
#ifndef _base64_h_
#define _base64_h_

#include <string.h>


/* This API is borrowed from ISUX3.x */
extern "C" 
int ToB64Enc(const char *szStr, char *s, int iLen);

/* comments added by Kent Wu, no modification of signature or any
source code to fulfill license agreement */

/* pcszInput is the source string to decode, puOutLen is the length of 
the returned string. Note: the retuned string might be longer than the
real data, user should get its content up to puOutLen only. User should
"delete []" the returned string after the usage. See tst_base64.cpp for 
sample code */
extern "C" 
unsigned char *Base64Decode(const char *pcszInput, unsigned int *puOutLen);
 
#endif
