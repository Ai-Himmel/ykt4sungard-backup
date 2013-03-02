/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.List;

import com.kingstargroup.advquery.hibernate.dao.CutTypeDAO;

public class CutTypeUtil extends BasicUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AccountUtil����������ϸ<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-5-15  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getCutType() {
		CutTypeDAO dao = CutTypeDAO.getInstance();
		try {
			List account = dao.getCutType();
			return account;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
}
