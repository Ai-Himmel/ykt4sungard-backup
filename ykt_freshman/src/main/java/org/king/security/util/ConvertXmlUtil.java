/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.util.ConvertXmlUtil.java
 * 创建日期： 2006-4-26 15:40:56
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-26 15:40:56      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.util;


import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.security.domain.Menu;

import org.king.utils.XmlUtil;

/**
 * <p> ConvertXmlUtil.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ConvertXmlUtil.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-26
 * 
 *
 */
public class ConvertXmlUtil {
	//~ Static fields/initializers =============================================

	  private static Log log = LogFactory.getLog(ConvertXmlUtil.class);

	  //~ Methods ================================================================

	  public static String convertMenuListToXml(Map menuMap) {
	  	StringBuffer xml = new StringBuffer("<?xml version='1.0' encoding='gb2312'?>");
		xml = xml.append("<Root>");
		
	  	String xmlStr = "<?xml version='1.0' encoding='gb2312'?>";
		xmlStr = xmlStr + "<Root>";
	  	
		String rootId = "-1";
		List menuList = (List)menuMap.get(rootId);
		
		//如果第一级菜单不为空，继续
		if(menuList!=null && menuList.size()>0)
			addTreeNode(menuList,menuMap,xml);
		
		
		xml= xml.append("</Root>");
		
		return xml.toString();
	  }
	
	/*
	 * 递归添加子节点菜单xml片断
	 */
	public static void addTreeNode(List menuList,Map menuMap,StringBuffer xmlStr) {
		List temp;
		for(Iterator i = menuList.iterator();i.hasNext();){
			
			   Menu menu = (Menu)i.next();
			   xmlStr = xmlStr.append("<TreeNode ");
			   xmlStr = xmlStr.append("Title='"+XmlUtil.normalize(menu.getName())+"'");
			
			
			   //如果有子菜单
			   temp = (List)menuMap.get(menu.getId());
			   if(temp!=null && temp.size()>0){
				   
				   xmlStr = xmlStr.append(" CheckData=\""+XmlUtil.normalize(menu.getId())+"\"");
				   xmlStr = xmlStr.append(" Checked=\"false\"");
				   xmlStr = xmlStr.append(" >");
				   addTreeNode(temp,menuMap,xmlStr);
				   xmlStr = xmlStr.append(" </TreeNode>");
			   }else{
				   xmlStr = xmlStr.append(" CheckData=\""+XmlUtil.normalize(menu.getId())+"\"");
				   xmlStr = xmlStr.append(" Checked=\"false\"");
				   //找到合适的图片的时候，加图片
				   //xmlStr = xmlStr.append(" NodeImgSrc='"+menu.getMenuName()+"'");
				   xmlStr = xmlStr.append(" />");
			   }
				
		   }
	}
}
