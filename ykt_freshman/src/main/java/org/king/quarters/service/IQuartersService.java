/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    IQuartersService.java
 * �������ڣ� 2007-6-5 ����02:25:34
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-5 ����02:25:34     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.quarters.service;

import java.io.File;
import java.util.List;

import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.quarters.domain.TabSsDept;

public interface IQuartersService {

	public int importQuarters(String userId,File excelFile);
	public int getQuartersList(String userId,List res,int pageNo,int pageSize,QuartersModel conditions);
	public int getQuartersListAll(String userId,List res,QuartersModel conditions);
	public boolean  addOrUpdateQuarters(Dormitorymodel quarters);
	public Dormitorymodel  getQuarters(String quartersId);
	
	public TabSsDept  getManageDept(String userId);
	
}
