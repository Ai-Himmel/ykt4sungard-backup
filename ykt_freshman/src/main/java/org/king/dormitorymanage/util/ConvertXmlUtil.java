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
package org.king.dormitorymanage.util;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Dictionary;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.utils.XmlUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name: ConvertXmlUtil.java
 * Description: TODO Modify History（或Change Log）: 操作类型（创建、修改等） 操作日期 操作者 操作内容简述
 * 创建 2006-6-10 何林青
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class ConvertXmlUtil {
	// ~ Static fields/initializers
	// =============================================

	// ~ Methods
	// ================================================================

	public static String convertMenuListToXml(Map menuMap) {
		StringBuffer xml = new StringBuffer(
				"<?xml version='1.0' encoding='gb2312'?>");
		xml = xml.append("<Root>");

		String xmlStr = "<?xml version='1.0' encoding='gb2312'?>";
		xmlStr = xmlStr + "<Root>";

		String rootId = "-1";
		List menuList = (List) menuMap.get(rootId);

		// 如果第一级菜单不为空，继续
		if (menuList != null && menuList.size() > 0)
			addTreeNode(menuList, menuMap, xml);

		xml = xml.append("</Root>");

		return xml.toString();
	}
	
	

	/*
	 * 递归添加子节点菜单xml片断
	 */
	public static void addTreeNode(List menuList, Map menuMap,
			StringBuffer xmlStr) {
//		List temp;
		for (Iterator i = menuList.iterator(); i.hasNext();) {

			Classmodel classmodel = (Classmodel) i.next();
			xmlStr = xmlStr.append("<TreeNode ");
			xmlStr = xmlStr.append("Title='"
					+ XmlUtil.normalize(classmodel.getClassNo()) + "'");

//			// 如果有子菜单
//			temp = (List) menuMap.get(classmodel.getClassId());
//			if (temp != null && temp.size() > 0) {
//
//				xmlStr = xmlStr.append(" CheckData=\""
//						+ XmlUtil.normalize(classmodel.getClassId()) + "\"");
//				xmlStr = xmlStr.append(" Checked=\"true\"");
//				xmlStr = xmlStr.append(" >");
//				addDormTreeNode(temp, menuMap, xmlStr);
//				xmlStr = xmlStr.append(" </TreeNode>");
//			} else {
				xmlStr = xmlStr.append(" CheckData=\""
						+ XmlUtil.normalize(classmodel.getClassId()) + "\"");
				xmlStr = xmlStr.append(" Checked=\"false\"");
				// 找到合适的图片的时候，加图片
				// xmlStr = xmlStr.append("
				// NodeImgSrc='"+menu.getMenuName()+"'");
				xmlStr = xmlStr.append(" />");
//			}
		}
	}

	
	public static void addDormTreeNode(List menuList, Map menuMap,
			StringBuffer xmlStr) {
		for (Iterator i = menuList.iterator(); i.hasNext();) {

			Dormitorymodel dormitorymodel = (Dormitorymodel) i.next();
			xmlStr = xmlStr.append("<TreeNode ");
			xmlStr = xmlStr.append("Title='"
					+ XmlUtil.normalize(dormitorymodel.getLocation()
							+ dormitorymodel.getDormitory()
							+ dormitorymodel.getRoomNumber()) + "'");
			xmlStr = xmlStr.append(" CheckData=\""
					+ XmlUtil.normalize(dormitorymodel.getDormitoryId()) + "\"");
			xmlStr = xmlStr.append(" Checked=\"false\"");
			// 找到合适的图片的时候，加图片
			// xmlStr = xmlStr.append(" NodeImgSrc='"+menu.getMenuName()+"'");
			xmlStr = xmlStr.append(" />");

		}
	}
	
	
	public static String convertMajorinListToXml(Map menuMap) {
		StringBuffer xml = new StringBuffer(
				"<?xml version='1.0' encoding='gb2312'?>");
		xml = xml.append("<Root>");

		String xmlStr = "<?xml version='1.0' encoding='gb2312'?>";
		xmlStr = xmlStr + "<Root>";

		String rootId = "-1";
		List menuList = (List) menuMap.get(rootId);

		// 如果第一级菜单不为空，继续
		if (menuList != null && menuList.size() > 0)
			addMajorinTreeNode(menuList, menuMap, xml);

		xml = xml.append("</Root>");

		return xml.toString();
	}
	/*
	 * 递归添加子节点菜单xml片断
	 */
	public static void addMajorinTreeNode(List menuList, Map menuMap,
			StringBuffer xmlStr) {
		for (Iterator i = menuList.iterator(); i.hasNext();) {

			Dictionary dictionary = (Dictionary) i.next();
			xmlStr = xmlStr.append("<TreeNode ");
			xmlStr = xmlStr.append("Title='"
					+ XmlUtil.normalize(dictionary.getDictCaption()) + "'");
				xmlStr = xmlStr.append(" CheckData=\""
						+ XmlUtil.normalize(dictionary.getId().getDictValue()) + "\"");
				xmlStr = xmlStr.append(" Checked=\"false\"");
				// 找到合适的图片的时候，加图片
				// xmlStr = xmlStr.append("
				// NodeImgSrc='"+menu.getMenuName()+"'");
				xmlStr = xmlStr.append(" />");
			}
		}

}
