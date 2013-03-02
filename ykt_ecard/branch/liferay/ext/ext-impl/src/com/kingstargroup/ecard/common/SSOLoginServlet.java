/**
 * 
 */
package com.kingstargroup.ecard.common;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.sungard.Verify.IVerify;
import com.sungard.Verify.VerifyManager;

/**
 * @author jeffxiao
 * 
 */
public class SSOLoginServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
			throws IOException, ServletException {
			String un="";
			com.sungard.beans.User ssouser = new com.sungard.beans.User();
			try {
				IVerify verify = (IVerify)VerifyManager.CreateVerify();			
				if(!verify.CheckLogin(ssouser, req)){
					System.out.println(req.getParameter("Verify"));
					
					if (req.getParameter("Verify") != null
							&& req.getParameter("Verify").equals("False")) {
					//Login 失败自行处理
						System.out.println("No Verify checkLogin fail.");
						throw new UserIdException();
				    }
				    else
				    {
				    	verify.Login(ssouser, null, req, res);		    	
				    }
				}else{
					un= ssouser.get_account()==null?"":ssouser.get_account().trim();
					System.out.println("stuempno："+un+"relogin ecard sys. visa sso");				
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
			if(!"".equals(un))
			{
				try {
					String path = PropsValues.DEFAULT_LANDING_PAGE_PATH;
					path = "/web/guest/home?p_p_id=ext_login_png&p_p_action=1&p_p_state=normal&p_p_mode=view&_ext_login_png_struts_action=%2Fext%2Fextloginview&_ext_login_png_cmd=sso";
					res.sendRedirect(path);
				} catch (Exception e) {
					e.printStackTrace();
				}				
				
			}
			
			System.out.println("sso check end.stuempno:"+un+"login ecard sys. visa sso");
	}

	private static final Log _log = LogFactory.getLog(SSOLoginServlet.class);
}
