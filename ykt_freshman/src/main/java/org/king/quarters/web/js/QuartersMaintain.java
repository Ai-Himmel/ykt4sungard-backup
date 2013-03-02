/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    QuartersMaintain.java
 * �������ڣ� 2007-6-12 16:17:43
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-12 16:17:43     ��ʤ        �����ļ���ʵ�ֻ�������
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
