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

public class TestPublishAction extends BaseAction {

	private TestPublishService testPublishService;
	public void setTestPublishService(TestPublishService testPublishService) {
		this.testPublishService = testPublishService;
	}
	
	public ActionForward search4List(ActionMapping mapping, ActionForm form,
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
		m.put("operator", (String)session.getAttribute("userName"));					    
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
		       		
		return (mapping.findForward("success"));		
		
	} 
	
	public ActionForward view(ActionMapping mapping, ActionForm form,
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
			     
				 return mapping.findForward("testpublishview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
				return mapping.findForward("faile");
			}

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
		m.put("operator", (String)session.getAttribute("userName"));
		//m.put("search_ifpublic",Constants.yesCode);
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
		       		
		return (mapping.findForward("successview"));		
		
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
			     
				 return mapping.findForward("testpublishstuview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
				return mapping.findForward("faile");
			}

	}

	
	public ActionForward load4add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		try {
			 saveToken(request);
			 return mapping.findForward("testpublish");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmTestPublish bmTestPublish = (BmTestPublish)aform.get("bmTestPublish");
		String msg="";
		try {			
				bmTestPublish.setCreator(userId);
			    bmTestPublish.setCreateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				bmTestPublish.setUpdator(userId);
			    bmTestPublish.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));		
	 				 
				if (isTokenValid(request, true)) {
					msg="0";
					testPublishService.save(bmTestPublish);
				}
				else{
					msg="9";
					saveToken(request);
				}	
				
				request.setAttribute("msg",msg);
				return mapping.findForward("testpublishlist");			
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return load4add(mapping, form, request, response);
		}

	}

	public ActionForward load4update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		DynaValidatorForm aform = (DynaValidatorForm) form;
		String updateid=request.getParameter("updateid");
 		
		try {
			 
			 List testpublishList=testPublishService.get4Update(updateid);			 
		     request.setAttribute("testpublishlist",testpublishList);
			 return mapping.findForward("testpublishedit");
			 
		} catch (Exception e) {
			e.printStackTrace();
			return load4update(mapping, form, request, response);
		}

	}

	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmTestPublish bmTestPublish = (BmTestPublish)aform.get("bmTestPublish");
        
		String msg="";
		try {
							
				bmTestPublish.setUpdator(userId);
			    bmTestPublish.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
 		     
			    testPublishService.update(bmTestPublish);
			    msg="0";
			    request.setAttribute("msg",msg);				
			    return mapping.findForward("testpublishlist");
						
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       	
		String[] ids=request.getParameterValues("cbgroup");
		
		String msg="";
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 
				     BmTestPublish bmTestPublish = findbyId(ids[i]);	
				     if(bmTestPublish!=null)
				         testPublishService.delete(bmTestPublish);	
				     msg="d0";				 
				 
		    } catch (Exception e) {
			     e.printStackTrace();
			     return mapping.findForward("faile");
		    }
		}
		
		request.setAttribute("msg",msg);
		return mapping.findForward("testpublishlist");
	}
	
	public  BmTestPublish findbyId(String id) throws Exception {
		
       try {	
    	   
    	  BmTestPublish bmTestPublish=testPublishService.getDetail(id);	 		
	      return bmTestPublish;
	      
      } catch (Exception e) {
	    e.printStackTrace();
      }
      return null;

      }

    //编辑登录页面的滚动文字
	public ActionForward load4edit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		 		
		try {
						
			List noticeList=testPublishService.find("select new Map(a.id as id,a.title as title,a.body as body) from BmTestPublish a where 1=1 and a.ifDisplay='9' and a.ifPublic='9' "); 
			
			if(noticeList!=null&&noticeList.size()>0)   
		         request.setAttribute("noticelist",noticeList);		
			else{
				 Map noticem=new HashMap();
				 noticem.put("id","");
				 noticem.put("title","");
				 noticem.put("body","");
				 noticeList.add(noticem);
				 request.setAttribute("noticelist",noticeList);
			}
			return mapping.findForward("loginedit");
		} catch (Exception e) {
			e.printStackTrace();
			return load4edit(mapping, form, request, response);
		}

	}
	
	public ActionForward edit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}

		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmTestPublish bmTestPublish = (BmTestPublish)aform.get("bmTestPublish");
        
		try {
			bmTestPublish.setUpdator(userId);
		    bmTestPublish.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
			
		    if(bmTestPublish.getId()!=null&&!bmTestPublish.getId().equals("")&&!bmTestPublish.getId().equals("null")){
		    	testPublishService.update(bmTestPublish);			 
				request.setAttribute("msg","0");
		    }
		    else{
		    	bmTestPublish.setCreator(userId);
			    bmTestPublish.setCreateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
		    	testPublishService.save(bmTestPublish);	
		    	request.setAttribute("msg","0");
		    }
			 return mapping.findForward("logineditsuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward del(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       	
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmTestPublish bmTP = (BmTestPublish)aform.get("bmTestPublish");
		
		String id=bmTP.getId();
		
		                
			 try {
				 BmTestPublish bmTestPublish=null;
				 if(id!=null&&!id.equals("")&&!id.equals("null"))
					 bmTestPublish = findbyId(id);
		     		         
			     if(bmTestPublish!=null){
			    	 testPublishService.delete(bmTestPublish);
			         request.setAttribute("msg","d0");
			     }   
		    } catch (Exception e) {
			     e.printStackTrace();
			     return mapping.findForward("faile");
		    }
	
		return mapping.findForward("logineditsuccess");
	}

}
