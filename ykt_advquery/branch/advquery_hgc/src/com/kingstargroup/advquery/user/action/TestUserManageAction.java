/**
 * 
 */
package com.kingstargroup.advquery.user.action;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.hibernate.Transaction;

import com.kingstargroup.advquery.common.Encryptor;
import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
import com.kingstargroup.advquery.hibernate.dao.UserDAO;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryOperator;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TestUserManageAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class TestUserManageAction extends Action {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		Transaction t = HibernateSessionFactory.currentSession().beginTransaction();
		UserDAO dao = UserDAO.getInstance();
		TLeadqueryOperator operator = new TLeadqueryOperator();
		operator.setOperCode("admin");
		operator.setOperName("admin");
		operator.setOperPwd(Encryptor.digest("test"));
		operator.setIsShopOwner("0");
		dao.saveOrUpdate(operator);
		t.commit();
		return null;
	}

	

}
