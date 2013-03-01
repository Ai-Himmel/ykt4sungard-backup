package com.kingstargroup.advquery.register.action;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.hibernate.util.DictionaryUtil;

public class RegisterInitAction extends Action {
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		    
		    req.getSession().setAttribute("register",null);
		    String cmd= req.getParameter("cmd");
		    String fd="";
		    if("registerQuery".equals(cmd)){
		        fd="register.query";
		    }
		    if("registerReport".equals(cmd)){
		        fd="register.report";	
		    }
		    if("feeQuery".equals(cmd)){
		    	fd="fee.query";
		    }
		    if("feeReport".equals(cmd)){
		    	fd="fee.report";
		    }
		    if("noregstudent".equals(cmd)){
		    	fd ="register.noregister";
		    }
		    if("registercomeQuery".equals(cmd)){
		    	fd = "register.come";
		    }
		    List result = new ArrayList();
		    Map temp = new HashMap();
		    temp.put("code","0");
		    temp.put("name","未报到");
			result.add(temp);
			Map temp2 = new HashMap();	
			temp2.put("code","1");
			temp2.put("name","已报到");
			result.add(temp2);
			
			List isregisterList = new ArrayList();
			Map isregisterMap1  = new HashMap();
			isregisterMap1.put("code","0");
			isregisterMap1.put("name","未注册");
			isregisterList.add(isregisterMap1);
			
			Map isregisterMap2  = new HashMap();
			isregisterMap2.put("code","1");
			isregisterMap2.put("name","已注册");
			isregisterList.add(isregisterMap2);
			
			
		    req.getSession().setAttribute("isregisterList",isregisterList);
			req.getSession().setAttribute("comeList",result);
		    List TermList = DictionaryUtil.getTermList();
		    req.getSession().setAttribute("TermList",TermList);
		    return mapping.findForward(fd);
	}
}
