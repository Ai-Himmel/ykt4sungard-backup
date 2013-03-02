package com.kingstargroup.conference.action;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.SignDAO;
import com.kingstargroup.conference.hibernate.HibernateSessionFactory;
import com.kingstargroup.conference.hibernate.form.TConference;

public class HttpRequestAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		String cardno = request.getParameter("cardno");
		String username = request.getParameter("username");
		try {
			if(null!=cardno&&!"".equals(cardno)){
				Transaction tx = null;
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				ConferenceDAO confdao = ConferenceDAO.getInstance();
				SignDAO signdao = SignDAO.getInstance();
				TConference conf = null;
				if(null!=username&&!"".equals(username)){
					conf= confdao.getConIdByTime(username);
				}else{
					conf= confdao.getConIdByTime("");
				}
				
				if (null==conf) {
					// 没到会议时间
					System.out.println("=====No such meeting===");
					response.getWriter().write("0001");
				} else {
					if("0".equals(conf.getPreplan1())){
						if (signdao.getCustbyidandPhyNo(conf.getConId().intValue(), cardno)) {
							signdao.updatecheckFlag(conf.getConId().intValue(), cardno);
							response.getWriter().write("0000");
						}else{
							//记录信息
							System.out.println("=====No one in this meeting===");
							signdao.recordHis(conf.getConId(),cardno);
							response.getWriter().write("0000");
						}
					}else{
						if (signdao.getCustbyidandPhyNo(conf.getConId().intValue(), cardno)) {
							signdao.updatecheckFlag(conf.getConId().intValue(), cardno);
							response.getWriter().write("0000");
						}else{
							System.out.println("=====No one in this meeting===");
							signdao.recordHis(conf.getConId(),cardno);
							response.getWriter().write("0002");
						}
					}
				}
				
				tx.commit();
			}else{
				response.getWriter().write("6666");
			}		
		} catch (Exception e) {
			e.printStackTrace();
			response.getWriter().write("7777");
		}
		
		return null;
	}

}
