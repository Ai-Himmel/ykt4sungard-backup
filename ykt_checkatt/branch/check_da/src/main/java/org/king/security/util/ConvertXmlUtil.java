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
package org.king.security.util;

import java.util.*;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.domain.Department;
import org.king.security.domain.Menu;

/**
 * <p> ConvertXmlUtil.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="ConvertXmlUtil.java.html"><i>�鿴Դ����</i></a></p>  
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
		
		//�����һ���˵���Ϊ�գ�����
		if(menuList!=null && menuList.size()>0)
			addTreeNode(menuList,menuMap,xml);
		
		
		xml= xml.append("</Root>");
		
		return xml.toString();
	  }
	
	/*
	 * �ݹ�����ӽڵ�˵�xmlƬ��
	 */
	public static void addTreeNode(List menuList,Map menuMap,StringBuffer xmlStr) {
		List temp;
		for(Iterator i = menuList.iterator();i.hasNext();){
			
			   Menu menu = (Menu)i.next();
			   xmlStr = xmlStr.append("<TreeNode ");
			   xmlStr = xmlStr.append("Title='"+menu.getName()+"'");
			
			
			   //������Ӳ˵�
			   temp = (List)menuMap.get(menu.getId());
			   if(temp!=null && temp.size()>0){
				   
				   xmlStr = xmlStr.append(" CheckData=\""+menu.getId()+"\"");
				   xmlStr = xmlStr.append(" Checked=\"false\"");
				   xmlStr = xmlStr.append(" >");
				   addTreeNode(temp,menuMap,xmlStr);
				   xmlStr = xmlStr.append(" </TreeNode>");
			   }else{
				   xmlStr = xmlStr.append(" CheckData=\""+menu.getId()+"\"");
				   xmlStr = xmlStr.append(" Checked=\"false\"");
				   //�ҵ����ʵ�ͼƬ��ʱ�򣬼�ͼƬ
				   //xmlStr = xmlStr.append(" NodeImgSrc='"+menu.getMenuName()+"'");
				   xmlStr = xmlStr.append(" />");
			   }
				
		   }
	}
	
	
	public static String convertToTreeXml(Map deptMap){
		
		StringBuffer xml = new StringBuffer("<?xml version='1.0' encoding='gb2312'?>");
		xml = xml.append("<Root>");
		
	  	String xmlStr = "<?xml version='1.0' encoding='gb2312'?>";
		xmlStr = xmlStr + "<Root>";
	  	
		String rootId = "-1";
		List deptList = (List)deptMap.get(rootId);
		
		//�����һ���˵���Ϊ�գ�����
		if(deptList!=null && deptList.size()>0)
			addDeptTreeNode(deptList,deptMap,xml);
		
		
		xml= xml.append("</Root>");
		
		return xml.toString();
	}
	
	/*
	 * �ݹ�����ӽڵ�˵�xmlƬ��
	 */
	public static void addDeptTreeNode(List deptList,Map deptMap,StringBuffer xmlStr) {
		List temp;
		for(Iterator i = deptList.iterator();i.hasNext();){
			
			Department dept = (Department)i.next();
			   xmlStr = xmlStr.append("<TreeNode ");
			   xmlStr = xmlStr.append("Title='"+dept.getName()+"'");
			
			
			   //������Ӳ˵�
			   temp = (List)deptMap.get(dept.getId());
			   if(temp!=null && temp.size()>0){
				   
				   xmlStr = xmlStr.append(" CheckData=\""+dept.getId()+"\"");
				   xmlStr = xmlStr.append(" Checked=\"false\"");
				   xmlStr = xmlStr.append(" >");
				   addDeptTreeNode(temp,deptMap,xmlStr);
				   xmlStr = xmlStr.append(" </TreeNode>");
			   }else{
				   xmlStr = xmlStr.append(" CheckData=\""+dept.getId()+"\"");
				   xmlStr = xmlStr.append(" Checked=\"false\"");
				   //�ҵ����ʵ�ͼƬ��ʱ�򣬼�ͼƬ
				   //xmlStr = xmlStr.append(" NodeImgSrc='"+dept.getMenuName()+"'");
				   xmlStr = xmlStr.append(" />");
			   }
				
		   }
	}

    public static String generateDepartmentTreeXml(List result){
        if (result == null || result.size() == 0) {
            return "";
        }
        StringBuffer xml = new StringBuffer("<?xml version='1.0' encoding='UTF-8'?>");
        xml.append("<Root>");

        Map row;
        Stack stack = new Stack();
        for (int i = 0; i < result.size(); i++) {
            row = (Map) result.get(i);
            
            xml.append("<TreeNode ");
            xml.append("Title='").append(row.get("dept_name")).append("'");
            Object accountId = row.get("oper_id");
            if(accountId!=null && StringUtils.isNotBlank(accountId.toString())){
                xml.append(" CheckedData=\"").append(row.get("dept_id")).append("\"");
            } else {
                xml.append(" CheckData=\"").append(row.get("dept_id")).append("\"");
            }

            xml.append(" >");
            if (hasChild(result, i)) {
                stack.push(row.get("dept_id"));
            } else {
                xml.append(" </TreeNode>");
                if (!hasUnvisitBrother(result, i)) {
                    //���ýڵ��Ѿ������һ���ڵ㣬Ϊstack��Ӧ�Ķ������ɽ�����ǩ
                    if (i == result.size() - 1) {
                        while (!stack.isEmpty()) {
                            stack.pop();
                            xml.append(" </TreeNode>");
                        }
                    } else {
                        //���ýڵ���нڵ㣬�ҵ������ڵ�ĸ��ڵ�id����ջ��Ԫ�س�ջ��ֱ�����������ڵ�ĸ��ڵ�id
                        Object nextFdeptid = ((Map) result.get(i + 1)).get("dept_parentid");
                        while (!stack.isEmpty()) {
                            if (nextFdeptid.equals(stack.peek())) {
                                break;
                            }
                            xml.append(" </TreeNode>");
                            stack.pop();
                        }
                    }
                }
            }
        }
        xml.append("</Root>");
        return xml.toString();
    }

/**
     * �ж��ڵ�ǰindex�����Ƿ����ӽڵ�
     *
     * @param list         .
     * @param currentIndex .
     * @return
     */
    private static boolean hasChild(List list, int currentIndex) {
        if (currentIndex == list.size() - 1) {
            return false;
        }
        Object currentDeptid = ((Map) list.get(currentIndex)).get("dept_id");
        Object nextFdeptid = ((Map) list.get(currentIndex + 1)).get("dept_parentid");
        return currentDeptid.equals(nextFdeptid);
    }

    /**
     * �ж��ڵ�ǰindex�����Ƿ����ֵܽڵ�
     *
     * @param list         .
     * @param currentIndex .
     * @return
     */
    private static boolean hasUnvisitBrother(List list, int currentIndex) {
        if (currentIndex == list.size() - 1) {
            return false;
        }
        Object currentFdeptid = ((Map) list.get(currentIndex)).get("dept_parentid");
        Object nextFdeptid = ((Map) list.get(currentIndex + 1)).get("dept_parentid");
        return currentFdeptid.equals(nextFdeptid);
    }
}
