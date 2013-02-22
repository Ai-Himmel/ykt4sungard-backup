package org.king.business.web.action;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.business.domain.BmTestPublish;
import org.king.business.service.TestPublishService;
import org.king.framework.web.action.BaseAction;
import org.king.utils.CommonUtil;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class TestPublicAction extends BaseAction {

	private TestPublishService testPublishService;
	public void setTestPublishService(TestPublishService testPublishService) {
		this.testPublishService = testPublishService;
	}
			
	public ActionForward search4Listview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
				
		List li=new ArrayList();
		DynaActionForm curForm = (DynaActionForm) form;
		Map m=new HashMap();
		m=curForm.getMap();	
		
		m.put("search_ifdisplay",Constants.yesCode);
		m.put("search_ifpublic",Constants.yesCode);
	    li=testPublishService.getList(m);
		
	    if(li!=null&&li.size()>0){
	    	 List resultList=new ArrayList();
             //起始页设置
			 if(offset.equals("0"))
			     resultList=li;
			 else if((Integer.parseInt(offset))<li.size()||(Integer.parseInt(offset))==li.size())
				 resultList=li.subList((Integer.parseInt(offset)),li.size());
			 
			 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("testpublishlist",resultList);
				 request.setAttribute("listcount",new Integer(li.size()));		    
			 }
	    }
		       		
		return (mapping.findForward("pubsuccess"));		
		
	} 
	
	public ActionForward stuview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       		
		String id=request.getParameter("updateid");
		
			 try {
 		         
			     List li=testPublishService.get4View(id);
			    
			     request.setAttribute("testpublishlist",li);
			     
				 return mapping.findForward("pubview");
			} catch (Exception e) {
				e.printStackTrace();
				return mapping.findForward("faile");
			}

	}
	
}
