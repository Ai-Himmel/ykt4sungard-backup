package com.kingstargroup.fdykt;

import java.sql.SQLException;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import org.apache.log4j.Logger;

import com.kingstar.itemconfig.ItemConfigDocument;
import com.kingstar.task.MainThreadConfig;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dao.YKTDictionary;

public class YKTInitServlet extends HttpServlet {
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
            if ("1".equals(KSConfiguration.getInstance().getProperty("hasBras", "0"))) {
                try {
                    MainThreadConfig.getIntance().ini();
                } catch (Exception e1) {
                    logger.error("初始化对账线程失败");
                    e1.printStackTrace();
                }
            }
            
            if ("1".equals(KSConfiguration.getInstance().getProperty("has_item_config", "0"))) {
                try {
                    ItemConfigDocument itemConfigDocument = ConfigItemInit.getInstance();
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
            }

		}catch(SQLException e){
			logger.error("初始化数据字典");
		}
		super.init();
	}
	
}
