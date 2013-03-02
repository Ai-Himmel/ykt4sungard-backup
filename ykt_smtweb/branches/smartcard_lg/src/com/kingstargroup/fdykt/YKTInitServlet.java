package com.kingstargroup.fdykt;

import org.apache.log4j.Logger;

import java.sql.SQLException;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dao.YKTDictionary;

public class YKTInitServlet extends HttpServlet {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(YKTInitServlet.class);

	public void destroy() {
		super.destroy();
	}

	public void init() throws ServletException {
		YKTDictionary dict = YKTDictionary.getInstance();
		KSDaoSessionFactory.createSession();
		try{
			Enumeration e = KSConfiguration.getInstance().getParameterNames();
			while(e.hasMoreElements()){
				String prop = (String)e.nextElement();
				if(prop != null && prop.startsWith("diction_")){
					String clazz = KSConfiguration.getInstance().getProperty(prop);
					if(clazz != null && !"".equals(clazz))
						dict.registeDictionary(clazz.trim());
				}
			}
			
			KSDaoSessionFactory.commit();
		}catch(SQLException e){
			logger.error("初始化数据字典");
		}
		super.init();
	}
	
}
