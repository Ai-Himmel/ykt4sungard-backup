/*
 * =====================================================================================
 * 
 *        Filename:  cal_key.h
 * 
 *     Description:  ����KeyA����
 * 
 *         Version:  1.0
 *         Created:  2005-08-18 09:20:29
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  �Ž�
 *         Company:  �������˴﹫˾
 *           Email:  jian.wen@kingstargroup.com
 * 
 * =====================================================================================
 */

/* 
 * ===  FUNCTION  ======================================================================
 * 
 *         Name:	CalKeyA  
 * 
 *  Description:	����KeyA����
 * 
 * - PARAMETER -------------------------------------------------------------------------
 *      Mode   Type             Name            Description
 * -------------------------------------------------------------------------------------
 *        in:  unsigned char*	ucSerialNo 		�����к�,4�ֽ�
 *        in:  unsigned char*	ucWorkKey		������Կ,8�ֽ�
 *    in-out: 
 *       out:  unsigned char*	ucKeyA 			��д������ԿKeyA,6�ֽ�
 *    return:  void
 * -------------------------------------------------------------------------------------
 *    Author:  �Ž�
 *   Created:  2005-08-18 09:22:48
 *  Revision:  none
 * =====================================================================================
 */
void CalKeyA(unsigned char* ucSerialNo,unsigned char* ucWorkKey,unsigned char* ucKeyA);
