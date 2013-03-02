/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.util.ConvertXmlUtil.java
 * �������ڣ� 2006-4-26 15:40:56
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-26 15:40:56      ljf        �����ļ���ʵ�ֻ�������
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
 * Description: TODO Modify History����Change Log��: �������ͣ��������޸ĵȣ� �������� ������ �������ݼ���
 * ���� 2006-6-10 ������
 * <p>
 * 
 * @author ������
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

		// �����һ���˵���Ϊ�գ�����
		if (menuList != null && menuList.size() > 0)
			addTreeNode(menuList, menuMap, xml);

		xml = xml.append("</Root>");

		return xml.toString();
	}
	
	

	/*
	 * �ݹ�����ӽڵ�˵�xmlƬ��
	 */
	public static void addTreeNode(List menuList, Map menuMap,
			StringBuffer xmlStr) {
//		List temp;
		for (Iterator i = menuList.iterator(); i.hasNext();) {

			Classmodel classmodel = (Classmodel) i.next();
			xmlStr = xmlStr.append("<TreeNode ");
			xmlStr = xmlStr.append("Title='"
					+ XmlUtil.normalize(classmodel.getClassNo()) + "'");

//			// ������Ӳ˵�
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
				// �ҵ����ʵ�ͼƬ��ʱ�򣬼�ͼƬ
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
			// �ҵ����ʵ�ͼƬ��ʱ�򣬼�ͼƬ
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

		// �����һ���˵���Ϊ�գ�����
		if (menuList != null && menuList.size() > 0)
			addMajorinTreeNode(menuList, menuMap, xml);

		xml = xml.append("</Root>");

		return xml.toString();
	}
	/*
	 * �ݹ�����ӽڵ�˵�xmlƬ��
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
				// �ҵ����ʵ�ͼƬ��ʱ�򣬼�ͼƬ
				// xmlStr = xmlStr.append("
				// NodeImgSrc='"+menu.getMenuName()+"'");
				xmlStr = xmlStr.append(" />");
			}
		}

}
