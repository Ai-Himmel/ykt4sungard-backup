/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    IDirectoryService.java
 * �������ڣ� 2007-6-12 14:50:00
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-12 14:50:00     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.common.service;

import java.util.List;

public interface IDirectoryService {

	public List getLocations(String id);
	public List getAreas();
	public List getDormitory(String id);
	public List getSexs();
	public List getLevels();
	public List getDirections();
	public List getGraduateDepartments();
	public List getMajors(String id);
	public List getGraduateMajors();
	public List getStudentTypes();
	public List getNations();
	public List getNationalitys();
	//
	public String getLocationName(String id);
	public String getAreaName(String id);
	public String getDormitoryName(String id);
	public String getSexName(String id);
	public String getLevelName(String id);
	public String getDirectionName(String id);
	//
	
}
