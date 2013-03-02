package com.kingstargroup.conference.util;

import com.kingstargroup.conference.dao.DbconfigureDAO;

public class DbconfigUtil {
	
	public static String getDbconfigure() {
		DbconfigureDAO dao = DbconfigureDAO.getInstance();
		return dao.getDbconfigure();
	}

}
