/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.web.listener.CheckCodeImage.java
 * �������ڣ� 2006-5-16 15:42:02
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-5-16 15:42:02      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.classmanage.web.servlet;

import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpSession;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.service.StudentService;
import org.king.dictionary.YKTDictionary;
import org.king.utils.GetPropertiesUtil;
import org.springframework.context.ApplicationContext;
import org.springframework.web.context.support.WebApplicationContextUtils;

import Glacier.Session;

/**
 * <p> CheckCodeImage.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="CheckCodeImage.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-5-16
 * 
 *
 */
public class DictionaryInitServlet extends HttpServlet {

	private static Log log = LogFactory.getLog(DictionaryInitServlet.class);
	
	public DictionaryInitServlet() {
	}
	
	public void init() throws ServletException {
		try{
		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		List dic_to_load =config.getList("Dictionary.init");
		Iterator iter = dic_to_load.iterator();
		 ApplicationContext ctx = 
	            WebApplicationContextUtils.getRequiredWebApplicationContext(this.getServletContext());
	       StudentService studentService =(StudentService) ctx.getBean("studentService");
	       studentService.getDiction("1");
		while(iter.hasNext()){
			String initDic = iter.next().toString();
			YKTDictionary.getInstance().registeDictionary(initDic);
		}
		} catch (Exception e) {
			System.out.println("Dictionary init Fail!");
		}

		
	}
	
}
