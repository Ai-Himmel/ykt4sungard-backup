/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    IQuartersNoticeService.java
 * �������ڣ� 2007-6-14 10:13:59
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-14 10:13:59     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.quarters.service;

import java.util.List;

public interface IQuartersNoticeService {
	

	public int searchStudents(List res,String uId,NoticeInfo con,int pageNo,int pageSize);
	//
	public List getNoticeDataSource(String uId,List stuIds);
	
}
