/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.web.listener.CheckCodeImage.java
 * 创建日期： 2006-5-16 15:42:02
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-5-16 15:42:02      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="CheckCodeImage.java.html"><i>查看源代码</i></a></p>  
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
