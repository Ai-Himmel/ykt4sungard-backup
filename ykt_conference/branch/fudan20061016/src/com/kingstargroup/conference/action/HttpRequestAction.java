package com.kingstargroup.conference.action;


import java.util.List;

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
import com.kingstargroup.conference.util.ConferenceUtil;
import com.kingstargroup.conference.util.OperatorUtil;
import com.kingstargroup.conference.util.XMLGenerateUtil;

public class HttpRequestAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		String cmd = request.getParameter("cmd");
		
		if("login".equals(cmd)){
			
			String username = request.getParameter("username");
			String password = request.getParameter("password");
			if (username==null||password==null||!OperatorUtil.login(username, password)) {
				//nologin
				String XMLStr = XMLGenerateUtil.XMLGenerateJD("1111", "用户名或者密码错", null);
				XMLGenerateUtil.XMLSendOut(request, response, XMLStr);
			}else{
				//login
				List result = ConferenceUtil.getAvailableConfByUser(username);
				String XMLStr = XMLGenerateUtil.XMLGenerateJD("0000", "登陆成功", result);
				XMLGenerateUtil.XMLSendOut(request, response, XMLStr);
			}
			
		}else{
			//sign
			String cardno = request.getParameter("cardno");
			String username = request.getParameter("username");
			String conid = request.getParameter("conid");
			System.out.println(conid+"*******"+cardno);
			try {
				if(null!=cardno&&!"".equals(cardno)){
					Transaction tx = null;
					Session session = HibernateSessionFactory.currentSession();
					tx = session.beginTransaction();
					ConferenceDAO confdao = ConferenceDAO.getInstance();
					SignDAO signdao = SignDAO.getInstance();
					TConference conf = null;
					if(conid!=null&&!"".equals(conid)){
						conf = confdao.getConference(Integer.parseInt(conid));
					}else{
						if(null!=username&&!"".equals(username)){
							conf= confdao.getConIdByTime(username);
						}else{
							conf= confdao.getConIdByTime("");
						}
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
		}
		
		
		return null;
	}

}
