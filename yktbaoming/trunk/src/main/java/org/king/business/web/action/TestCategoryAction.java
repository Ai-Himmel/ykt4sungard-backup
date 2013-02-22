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
import org.king.business.domain.BmTestCat;
import org.king.business.service.TestCategoryService;
import org.king.framework.web.action.BaseAction;
import org.king.utils.CommonUtil;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class TestCategoryAction extends BaseAction {

	private TestCategoryService testCategoryService;
	public void setTestCategoryService(TestCategoryService testCategoryService) {
		this.testCategoryService = testCategoryService;
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
		m.put("operator", session.getAttribute("userName"));						    
	    if(request.getAttribute("listNum")!=null&&((String)request.getAttribute("listNum")).equals("1")){
		    Map mm=new HashMap();
		    mm.put("operator",session.getAttribute("userName"));
		    //新增返回首页，且第一条记录为新增记录
		    mm.put("newidstring",request.getAttribute("newid"));
		    li=testCategoryService.getnewaddList(mm);
		   
	    }
	    else
	    	li=testCategoryService.getList(m);
		
	    if(li!=null&&li.size()>0){
	    	 List resultList=new ArrayList();
             //起始页设置
			 if(offset.equals("0"))
			     resultList=li;
			 else if((Integer.parseInt(offset))<li.size()||(Integer.parseInt(offset))==li.size())
				 resultList=li.subList((Integer.parseInt(offset)),li.size());
			 
			 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("testcatlist",resultList);
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
 		         
			     List li=testCategoryService.get4View(id);
			    
			     request.setAttribute("testcatlist",li);
			     
				 return mapping.findForward("testcatview");
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
			 return mapping.findForward("testcat");
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
		BmTestCat bmTestCat = (BmTestCat)aform.get("bmTestCat");
		String msg="";
		try {
			boolean flag=testCategoryService.check4Save(bmTestCat.getTestCatName(),null);//检查是否存在相同名称的考试类别
			if(flag){
				bmTestCat.setState(Constants.isUsingCode);	
				bmTestCat.setUpdator(userId);
			    bmTestCat.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));		
	 				 
				if (isTokenValid(request, true)) {
					msg="0";
					testCategoryService.save(bmTestCat);
				}
				else{
					msg="9";
					saveToken(request);
				}	
				
				request.setAttribute("listNum","1");
				request.setAttribute("newid",bmTestCat.getId());
				request.setAttribute("msg",msg);
				return mapping.findForward("testcatlist");
			}
			else{
				msg="2";
				request.setAttribute("msg",msg);
				return load4add(mapping, form, request, response);
			}
			
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
			 
			 List testcatList=testCategoryService.get4Update(updateid);			 
		     request.setAttribute("testcatlist",testcatList);
			 return mapping.findForward("testcatedit");
			 
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
		BmTestCat bmTestCat = (BmTestCat)aform.get("bmTestCat");
        
		String msg="";
		try {
			
			boolean flag=testCategoryService.check4Save(bmTestCat.getTestCatName(),bmTestCat.getId());//检查是否存在相同名称的考试类别
			if(flag){				
				bmTestCat.setUpdator(userId);
			    bmTestCat.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
 		     
			    testCategoryService.update(bmTestCat);
			    msg="0";
			    request.setAttribute("msg",msg);				
			    return mapping.findForward("testcatlist");
			}
			else{			
				msg="2";
				request.setAttribute("msg",msg);
				List testcatList=testCategoryService.get4Update(bmTestCat.getId());			 
			    request.setAttribute("testcatlist",testcatList);
				return mapping.findForward("testcatedit");
			}
			
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
       	String nottoDelete="";	
		String[] ids=request.getParameterValues("cbgroup");
		
		String msg="";
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 String nottoDelName=testCategoryService.check4Delete(ids[i]);
				 if(nottoDelName!=null)
					 nottoDelete=nottoDelete+nottoDelName+",";
				 else{
				     BmTestCat bmTestCat = findbyId(ids[i]);	
				     if(bmTestCat!=null)
				         testCategoryService.delete(bmTestCat);	
				     msg="d0";				         
				 }
				 
		    } catch (Exception e) {
			     e.printStackTrace();
			     return mapping.findForward("faile");
		    }
		}
		if(nottoDelete.length()>1){
			nottoDelete=nottoDelete.substring(0,nottoDelete.length()-1);
			request.setAttribute("notdel",nottoDelete);
		}
		request.setAttribute("msg",msg);
		return mapping.findForward("testcatlist");
	}
	
	public  BmTestCat findbyId(String id) throws Exception {
		
       try {	
    	   
    	  BmTestCat bmTestCat=testCategoryService.getDetail(id);	 		
	      return bmTestCat;
	      
      } catch (Exception e) {
	    e.printStackTrace();
      }
      return null;

      }


}
