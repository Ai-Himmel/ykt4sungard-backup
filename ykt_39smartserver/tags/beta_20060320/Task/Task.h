#ifndef __TASK_H__
#define __TASK_H__

#pragma once

#ifndef SMART_API 
#define SMART_API extern "C" __declspec(dllexport)
#endif //SMART_API 

extern 	lpfnGetDBHandle	            GetDBHandle;
extern 	lpfnFreeDBHandle            FreeDBHandle;
extern 	lpfnExecuteQuery			ExecuteQuery;
extern 	lpfnCloseRecHandle			CloseRecHandle;
extern 	lpfnIsOpen					IsOpen;
extern 	lpfnIsBOF					IsBOF;
extern 	lpfnIsEOF					IsEOF;
extern 	lpfnMoveFirst				MoveFirst;
extern 	lpfnMoveLast				MoveLast;
extern 	lpfnMoveNext				MoveNext;
extern 	lpfnMovePrev				MovePrev;
extern 	lpfnGetFieldCount			GetFieldCount;
extern 	lpfnGetRecordCount			GetRecordCount;
extern 	lpfnGetFieldName			GetFieldName;
extern 	lpfnGetFieldStringValue		GetFieldStringValue;
extern 	lpfnGetFieldStringValueEx	GetFieldStringValueEx;
extern 	lpfnGetFieldLongValue		GetFieldLongValue;
extern 	lpfnGetFieldLongValueEx		GetFieldLongValueEx;
extern 	lpfnGetFieldFloatValue		GetFieldFloatValue;
extern 	lpfnGetFieldFloatValueEx	GetFieldFloatValueEx;
extern 	lpfnGetFieldDoubleValue		GetFieldDoubleValue;
extern 	lpfnGetFieldDoubleValueEx	GetFieldDoubleValueEx;
extern 	lpfnLocate					Locate;
extern 	lpfnExecuteSQL				ExecuteSQL;
extern  lpfnSendRequest             SendRequest;
extern  lpfnBroadData               BroadData;

#endif //__TASK_H__