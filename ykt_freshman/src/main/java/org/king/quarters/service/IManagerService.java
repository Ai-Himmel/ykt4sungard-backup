/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    IDeptService.java
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

import java.util.List;

import org.king.quarters.domain.TabSsManager;

public interface IManagerService {

	public boolean addOrUpdateDept(TabSsManager manager);
	public List getManagers();
	public TabSsManager getManager(String managerId);
	
}
