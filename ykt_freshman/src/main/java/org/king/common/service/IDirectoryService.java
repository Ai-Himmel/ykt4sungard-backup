/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    IDirectoryService.java
 * 创建日期： 2007-6-12 14:50:00
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-12 14:50:00     王胜        创建文件，实现基本功能
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
