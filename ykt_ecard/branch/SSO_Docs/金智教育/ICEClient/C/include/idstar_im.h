#ifndef _IDSTAR_IM_H
#define _IDSTAR_IM_H

#if 0
#ifdef LIBIDSTAR_EXPORT
#       define IDSTAR_API __declspec(dllexport)
#else
#       define IDSTAR_API __declspec(dllimport)
#endif

#endif

#ifndef IDSTAR_API
#define IDSTAR_API 
#endif

#ifndef __cplusplus
#define bool int 
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct _tagIdsGroup {
	char *id;
	char *name;	
};
typedef struct _tagIdsGroup IdsGroup ; 

//Ìí¼Ó lah
struct _tagAttrMap{
	char *attrName;
	char **attrValues;
};
typedef struct _tagAttrMap AttrMap;

struct _tagIdsIdentity{
	char *orgName;
	char *figure;
};
typedef struct _tagIdsIdentity  IdsIdentity;

struct _tagIdsSSOToken{
	char * userId;
	char * tokenValue;
};
typedef struct _tagIdsSSOToken IdsSSOToken;

struct _tagIdsAttribute{
		char * name;
		char ** values;
};
typedef struct _tagIdsAttribute IdsAttribute;

IDSTAR_API void ids_Init(const char * config);
IDSTAR_API void ids_Destory();

IDSTAR_API void ids_FreeString(char *);
IDSTAR_API void ids_FreeStringArray( char **);
IDSTAR_API void ids_FreeGroup(IdsGroup *);
IDSTAR_API void ids_FreeGroupArray( IdsGroup ** );
//Ìí¼Ó lah
IDSTAR_API void ids_FreeMap( AttrMap *);
IDSTAR_API void ids_FreeMapArray( AttrMap ** );

IDSTAR_API void ids_FreeIdentity( IdsIdentity *);
IDSTAR_API void ids_FreeIdentityArray( IdsIdentity ** );

IDSTAR_API void ids_FreeSSOToken( IdsSSOToken *);
IDSTAR_API void ids_FreeSSOTokenArray( IdsSSOToken ** );

IDSTAR_API void ids_FreeAttribute( IdsAttribute * g);
IDSTAR_API char* ids_GetUserNameByID(char *);
IDSTAR_API int ids_IsUserExist(char *);
IDSTAR_API char** ids_GetUserAttribute(char * id, char * attr);
IDSTAR_API int ids_CheckPassword(char * id, char* password);
IDSTAR_API IdsGroup** ids_GetUserGroup(char*);
IDSTAR_API IdsGroup** ids_GetGroups();
IDSTAR_API IdsGroup* ids_GetRootGroup();
IDSTAR_API IdsGroup** ids_GetSubGroups(char * );
IDSTAR_API IdsGroup** ids_GetGroupByName(char *);
IDSTAR_API IdsGroup* ids_GetGroupByID(char*);
IDSTAR_API char** ids_GetUserByGroup(char*);
IDSTAR_API char** ids_GetUserNameByGroup( char * );

IDSTAR_API char* ids_GetCurrentUser( char * );
IDSTAR_API char* ids_GetLoginURL();
IDSTAR_API char* ids_GetLogoutURL();

IDSTAR_API char** ids_GetEntryAttribute(char*dn, char*attrName);

//Ìí¼Ó lah
IDSTAR_API AttrMap** ids_GetUserAttributes(char* id, char** attrNames);
IDSTAR_API IdsIdentity** ids_GetUserIdentities(char* id);
IDSTAR_API IdsIdentity*  ids_GetUserFirstIdentity(char* id);
IDSTAR_API IdsSSOToken*  ids_CreateSSOToken(char* id, char* password);
IDSTAR_API bool ids_DestroySSOToken(char* tokenValue);
IDSTAR_API IdsSSOToken*  ids_ValidateToken(char* tokenValue);
IDSTAR_API bool ids_UpdateUserAttribute(char* id , char * attrName, char * oldV, char * newV);
IDSTAR_API IdsGroup** ids_GetOrgFirstLevelGroups(char * );
IDSTAR_API IdsGroup** ids_GetOrgAllGroups(char * );
IDSTAR_API char** ids_GetOrgAttribute(char * id, char * attr);

IDSTAR_API bool ids_AddUserAttribute(char * id, IdsAttribute* attr);
IDSTAR_API bool ids_DeleteUserAttribute(char * id, IdsAttribute* attr);
IDSTAR_API bool ids_IsUserInGroup(char * id, IdsGroup* group);
IDSTAR_API bool ids_AddUserToGroup(char * id, IdsGroup* group);
IDSTAR_API bool ids_DeleteUserFromGroup(char * id, IdsGroup* group);
IDSTAR_API bool ids_AddUsersToGroup(char ** id, IdsGroup* group);
IDSTAR_API bool ids_DeleteUsersFromGroup(char ** id, IdsGroup* group);
IDSTAR_API bool ids_AddGroupToContainer( IdsGroup* group,char* container);
IDSTAR_API bool ids_DeleteGroupFromContainer( IdsGroup* group);

#ifdef __cplusplus
}
#endif


#endif

