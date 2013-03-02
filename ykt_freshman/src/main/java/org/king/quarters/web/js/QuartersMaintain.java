/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QuartersMaintain.java
 * 创建日期： 2007-6-12 16:17:43
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-12 16:17:43     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.web.js;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.directwebremoting.WebContext;
import org.directwebremoting.WebContextFactory;
import org.directwebremoting.proxy.dwr.Util;
import org.king.common.service.IDirectoryService;

public class QuartersMaintain {

	IDirectoryService directoryService;

	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}
	
	private List getEmptyList(){
		List l = new ArrayList();
		Map t = new HashMap();
		t.put("id", "");
		t.put("name", "-----------------------");
		l.add(t);
		return l;
	}
	public void setLocations(String id){
		List locations = directoryService.getLocations(id);
		WebContext context = WebContextFactory.get();
		Util util = new Util(context.getScriptSession());
		//
		util.removeAllOptions("location");
		util.removeAllOptions("dormitory");
		//
		List emptyList = getEmptyList();
		util.addOptions("location", emptyList, "id", "name");
		util.addOptions("dormitory", emptyList, "id", "name");
		//
		if (locations != null && !locations.isEmpty()){
			
			util.addOptions("location", locations, "id", "name");
		}
		
	}
	public void setDormitory(String id){
		List dormitorys = directoryService.getDormitory(id);
		WebContext context = WebContextFactory.get();
		Util util = new Util(context.getScriptSession());
		//
		util.removeAllOptions("dormitory");
		//
		List emptyList = getEmptyList();
		util.addOptions("dormitory", emptyList, "id", "name");
		if (dormitorys != null && !dormitorys.isEmpty()){
			util.addOptions("dormitory", dormitorys, "id", "name");
		}
		
	}
	public void setMajors(String id){
		List majors = directoryService.getMajors(id);
		WebContext context = WebContextFactory.get();
		Util util = new Util(context.getScriptSession());
		//
		util.removeAllOptions("majors");
		//
		List emptyList = getEmptyList();
		util.addOptions("majors", emptyList, "id", "name");
		if (majors != null && !majors.isEmpty()){
			util.addOptions("majors", majors, "id", "name");
		}
		
	}
	
}
