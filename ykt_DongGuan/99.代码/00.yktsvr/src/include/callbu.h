#ifndef   __CALLBU_H_
#define __CALLBU_H_

#pragma once

#include "cpack.h"
#include "svrlink.h"

/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/** 
 * @brief KSBCC֮��Զ�̴�������ģ��ṹ
 */
typedef struct 
{
	/** 
	 * @brief DRTPͨѶƽ̨�ڵ��
	 */
	int drtp_node;
	/** 
	 * @brief KSBCC���ܺ�
	 */
	int bcc_main_func;
	 /** 
	 * @brief �����������ܺ�
	 */
	int request_func_no;
	/** 
	 * @brief ���Ͱ��ֶ�(���а�ͷ)
	 */
	ST_CPACK sPack;
	/** 
	 * @brief ���ܰ��ֶ�(���а�ͷ), ��������������
	 */
	ST_CPACK aPack;
	/** 
	 * @brief ���ܵĺ�����(û�а�ͷ), ���100������
	 */
	ST_PACK ArrayPack;
	/** 
	 * @brief ��ʱʱ������
	 */
	int time_out;
}BCC_EXT_PACK;

class CBccExtPack
{
public:
//    BCC_EXT_PACK m_bcc_ext_pack;
    
public:
    CBccExtPack();
    CBccExtPack(BCC_EXT_PACK *pack);
    virtual ~CBccExtPack();
    
    int SetHeadCol(int handle, ...);
//    int ExtSetHeadCol(ST_CPACK *in_cpack, ...);
    int InitExtPack();
    int SetExtPack(BCC_EXT_PACK *pack);
    int SetExtPack(int drtp_node, int main_func, int request_func_no, BCC_EXT_PACK *ext_pack);
    int ExtCallBu();
    int SetTimeOut(int time_out = 4);
    int GetLastErr(int *error_code, char *error_msg);
    int GetOutPack(ST_PACK *out_cpack);    
    
private:
    int ExtSetHeadCol(ST_CPACK *in_cpack, ...);

private:
    BCC_EXT_PACK m_bcc_ext_pack;
    int m_error_code;
    char m_error_msg[256];
};

/*
#ifdef __cplusplus
}
#endif
*/
#endif

