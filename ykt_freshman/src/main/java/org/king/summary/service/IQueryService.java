/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    IQueryService.java
 * �������ڣ� 2007-7-6 11:38:27
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-7-6 11:38:27     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.summary.service;

import java.util.List;

import org.king.summary.web.action.QueryInfo;

public interface IQueryService {

	public int queryGraduateInfos(List res,QueryInfo condition,int pageNo,int pageSize);
}
