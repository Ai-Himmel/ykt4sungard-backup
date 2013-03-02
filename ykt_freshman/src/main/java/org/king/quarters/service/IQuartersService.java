/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    IQuartersService.java
 * 创建日期： 2007-6-5 下午02:25:34
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-5 下午02:25:34     王胜        创建文件，实现基本功能
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
