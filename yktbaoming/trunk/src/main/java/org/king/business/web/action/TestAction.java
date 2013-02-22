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
import org.king.business.domain.BmTest;
import org.king.business.domain.BmTestCat;
import org.king.business.service.TestCategoryService;
import org.king.business.service.TestService;
import org.king.framework.web.action.BaseAction;
import org.king.utils.CommonUtil;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class TestAction extends BaseAction {

	private TestService testService;
	public void setTestService(TestService testService) {
		this.testService = testService;
	}
	
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
		    li=testService.getnewaddList(mm);
		   
	    }
	    else
	    	li=testService.getList(m);
		
	    if(li!=null&&li.size()>0){
	    	 List resultList=new ArrayList();
             //起始页设置
			 if(offset.equals("0"))
			     resultList=li;
			 else if((Integer.parseInt(offset))<li.size()||(Integer.parseInt(offset))==li.size())
				 resultList=li.subList((Integer.parseInt(offset)),li.size());
			 
			 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("testlist",resultList);
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
 		         
			     List li=testService.get4View(id);
			    
			     request.setAttribute("testlist",li);
			     
				 return mapping.findForward("testview");
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
			 Map m=new HashMap();
			 m.put("search_state",Constants.isUsingCode);
			 m.put("operator", session.getAttribute("userName"));
			 List testcatList=testCategoryService.getList(m);
			 if(testcatList!=null&&testcatList.size()>0)
				 request.setAttribute("tclist",testcatList);
			 return mapping.findForward("test");
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
		BmTest bmTest = (BmTest)aform.get("bmTest");
		
		String testcatid=request.getParameter("testCatId");
		BmTestCat bmTestCat=testCategoryService.getDetail(testcatid);
		bmTest.setBmTestCat(bmTestCat);
		String msg="";
		try {
			boolean flag=testService.check4Save(bmTest);//检查是否存在相同的考试
			if(flag){					
				bmTest.setUpdator(userId);
			    bmTest.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));		
	 				 
				if (isTokenValid(request, true)) {
					msg="0";
					testService.save(bmTest);
				}
				else{
					msg="9";
					saveToken(request);
				}	
				
				request.setAttribute("listNum","1");
				request.setAttribute("newid",bmTest.getId());
				request.setAttribute("msg",msg);
				return mapping.findForward("testlist");
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
			 
			 List testList=testService.get4Update(updateid);	
			
		     request.setAttribute("testlist",testList);
		     		     		     
		     Map m=new HashMap();
		     m.put("search_state",Constants.isUsingCode);
		     m.put("operator", session.getAttribute("userName"));
		     BmTest bmTest=testService.getDetail(updateid);
			 m.put("search_includeid",bmTest.getBmTestCat().getId());
		     List testcatList=testCategoryService.getList(m);
			 if(testcatList!=null&&testcatList.size()>0)
				 request.setAttribute("tclist",testcatList);
			 return mapping.findForward("testedit");
			 
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
		BmTest bmTest = (BmTest)aform.get("bmTest");
        
		String testcatid=request.getParameter("testCatId");
		BmTestCat bmTestCat=testCategoryService.getDetail(testcatid);
		bmTest.setBmTestCat(bmTestCat);
		String msg="";
		try {
			
			boolean flag=testService.check4Save(bmTest);//检查是否存在相同的考试
			if(flag){				
				bmTest.setUpdator(userId);
			    bmTest.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
 		     
			    testService.update(bmTest);
			    msg="0";
			    request.setAttribute("msg",msg);				
			    return mapping.findForward("testlist");
			}
			else{			
				msg="2";
				request.setAttribute("msg",msg);
				List testList=testService.get4Update(bmTest.getId());	
				
			    request.setAttribute("testlist",testList);
			    Map m=new HashMap();
				m.put("search_state",Constants.isUsingCode);
				m.put("operator", session.getAttribute("userName"));
				BmTest bt=testService.getDetail(bmTest.getId());
				 m.put("search_includeid",bt.getBmTestCat().getId());
			    List testcatList=testCategoryService.getList(m);
				if(testcatList!=null&&testcatList.size()>0)
					request.setAttribute("tclist",testcatList);
				return mapping.findForward("testedit");
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
				 String nottoDelName=testService.check4Delete(ids[i]);
				 if(nottoDelName!=null)
					 nottoDelete=nottoDelete+nottoDelName+",";
				 else{
				     BmTest bmTest = findbyId(ids[i]);	
				     if(bmTest!=null)
				         testService.delete(bmTest);	
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
		return mapping.findForward("testlist");
	}
	
	public  BmTest findbyId(String id) throws Exception {
		
       try {	
    	   
    	  BmTest bmTest=testService.getDetail(id);	 		
	      return bmTest;
	      
      } catch (Exception e) {
	    e.printStackTrace();
      }
      return null;

      }


}
