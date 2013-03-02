/*-
 * Copyright (c) 2008 The Regents of the KingStar.
 * All rights reserved.
 *
 */
#ifndef _THIRD_MAC_H_
#define _THIRD_MAC_H_

#ifdef __cplusplus
extern "C" {
#endif 
void Caculate_Session_MAC(char *account, char *prs_first, char *prs_next, char *string, char *mac);
void Caculate_String_MAC(char *string, char *key, char *mac);
void Caculate_FS_MAC(char *string, char *file, char *key, char *mac);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _THIRD_MAC_H_
