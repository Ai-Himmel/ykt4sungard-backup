package com.kingstargroup.fdykt;

import java.sql.SQLException;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import org.apache.log4j.Logger;

import com.kingstar.console.MainThreadConfig;
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
			
			
			
//			MainThreadConfig.getIntance().ini();
			
			
			
		}catch(SQLException e){
			logger.error("初始化数据字典");
		}catch (Exception e) {
			logger.error("初始化对账线程失败");
			e.printStackTrace();
		}
		super.init();
	}
	
}
