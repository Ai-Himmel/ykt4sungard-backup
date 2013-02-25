/*
 * =====================================================================================
 * 
 *        Filename:  cal_key.h
 * 
 *     Description:  计算KeyA函数
 * 
 *         Version:  1.0
 *         Created:  2005-08-18 09:20:29
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  闻剑
 *         Company:  复旦金仕达公司
 *           Email:  jian.wen@kingstargroup.com
 * 
 * =====================================================================================
 */

/* 
 * ===  FUNCTION  ======================================================================
 * 
 *         Name:	CalKeyA  
 * 
 *  Description:	计算KeyA函数
 * 
 * - PARAMETER -------------------------------------------------------------------------
 *      Mode   Type             Name            Description
 * -------------------------------------------------------------------------------------
 *        in:  unsigned char*	ucSerialNo 		卡序列号,4字节
 *        in:  unsigned char*	ucWorkKey		工作密钥,8字节
 *    in-out: 
 *       out:  unsigned char*	ucKeyA 			读写卡的密钥KeyA,6字节
 *    return:  void
 * -------------------------------------------------------------------------------------
 *    Author:  闻剑
 *   Created:  2005-08-18 09:22:48
 *  Revision:  none
 * =====================================================================================
 */
void CalKeyA(unsigned char* ucSerialNo,unsigned char* ucWorkKey,unsigned char* ucKeyA);
