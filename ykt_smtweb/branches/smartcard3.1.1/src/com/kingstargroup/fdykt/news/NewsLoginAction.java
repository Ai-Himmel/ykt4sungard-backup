package com.kingstargroup.fdykt.news;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.util.SimpleEncoding;

public class NewsLoginAction extends Action {
	private static final Logger logger = Logger.getLogger(NewsLoginAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) {
		String forward = "success";
		
		String newsuser = request.getParameter("newsuser");
		String newspassword = request.getParameter("newspassword");
		try{
			String user = KSConfiguration.getInstance().getProperty("newsuser","admin");
			//����Ĭ��Ϊadmin
			String password = KSConfiguration.getInstance().getProperty("newspassword", "A191D10C2D64FDC9");
			if(!user.equals(newsuser)){
				throw new RuntimeException("�û�������ȷ��");
			}
			//����keyĬ����kingstar
			if(!password.equals(SimpleEncoding.byte2hex(SimpleEncoding.encode(newspassword.getBytes(), "kingstar".getBytes())))){
				throw new RuntimeException("���벻��ȷ��");
			}
			request.getSession().setAttribute("admin", "admin");
		} catch(Exception e){
			logger.error("�û���֤ʧ�ܣ�"+e.getMessage());
			request.setAttribute("newsuser", newsuser);
			request.setAttribute("newspassword", newspassword);
			request.setAttribute("error", "�û���֤ʧ�ܣ�"+e.getMessage());
			forward = "failure";
		}
		return mapping.findForward(forward);
	}
}
