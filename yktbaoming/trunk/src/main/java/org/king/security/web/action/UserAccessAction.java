/**
 * 
 */
package org.king.security.web.action;

import java.io.OutputStream;
import java.sql.Date;
import java.sql.Time;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.business.service.TestPublishService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.FirstpageAccess;
import org.king.security.domain.Role;
import org.king.security.service.UserAccessService;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

/**
 * @author jackey
 *
 */
public class UserAccessAction extends BaseAction{

	private UserAccessService userAccessService;

	public void setUserAccessService(UserAccessService userAccessService) {
		this.userAccessService = userAccessService;
	}
	
	public ActionForward saveFirst(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		try {		
						
			List noticeList=userAccessService.findFirst("select new Map(a.id as id,a.title as title,a.body as body) from BmTestPublish a where 1=1 and a.ifDisplay='9' and a.ifPublic='9' ");
			  
			 if(noticeList!=null&&noticeList.size()>0)
		         request.setAttribute("noticelist",noticeList);
			 
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("add error");			
			return mapping.findForward("faile");
		}

	}
			
	public ActionForward load4stuAlertbyWin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userName=(String)session.getAttribute(Constants.LOGIN_NAME);
		try{
		if(userName!=null){
			
			String todays=DateUtil.getNow("yyyy-MM-dd HH:mm");
			List stubmli=userAccessService.findFirst("select new Map(a.id as id,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo,(a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime) as bmEnd," +
					"a.bmTest.bmTestCat.ifFee as ifFee,a.bmTest.bmTestCat.fee as fee)" +
					" from BmStuBm a where a.ifBm='"+Constants.yesCode+"' and ((a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime)>'"+todays+"') and a.bmTest.bmTestCat.ifFee='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay<>'"+Constants.yesCode+"') and a.bmStudent.studentNo='"+userName+"'" +
							" order by a.bmTest.bmEndDate ");
			
			if(stubmli!=null&&stubmli.size()>0){
				java.text.DecimalFormat df = new java.text.DecimalFormat("####0.##"); 
				
				String[] stubminfo=new String[stubmli.size()];
				String bmendFirst="";
				for(int i=0;i<stubmli.size();i++){
					Map stubm=(Map)stubmli.get(i);						
			        String testfee=df.format(((Double)stubm.get("fee")).doubleValue());
			        String bmendtime=(String)stubm.get("bmEnd");
			        
					stubminfo[i]=(String)stubm.get("testInfo")+" 考试费用："+testfee+" 元 报名截止日期："+bmendtime;	
					if(bmendFirst.equals("")||bmendFirst.compareTo(bmendtime)>0){
						bmendFirst=bmendtime;
					}
				}
				if(!bmendFirst.equals(""))
					request.setAttribute("bmendfirst",bmendFirst);
								
				String feeTotal=null;					
				List feetotalli=userAccessService.findFirst("select sum(a.bmTest.bmTestCat.fee) as feeTotal from BmStuBm a where a.ifBm='"+Constants.yesCode+"' and ((a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime)>'"+todays+"') and a.bmTest.bmTestCat.ifFee='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay<>'"+Constants.yesCode+"') and a.bmStudent.studentNo='"+userName+"'");
				if(feetotalli!=null&&feetotalli.size()>0){
					feeTotal=df.format(((Double)feetotalli.get(0)).doubleValue());
					request.setAttribute("feetotal",feeTotal);
				}
				
				session.setAttribute("stubminfo",stubminfo);
				
				return mapping.findForward("stualert");
			}
			else
				return null;
			
		}
		else
			return null;
		}catch(Exception e){
			e.printStackTrace();
			return mapping.findForward("failealert");
		}
	}
		
	public ActionForward tongjiFirst(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
				
 		// 数据库验证
		try {
		  if(userAccessService==null)
				 System.out.println("service is null");
			 			 
		  if(request.getParameter("hbeginDate")!=null&&request.getParameter("hbeginDate")!=""&&request.getParameter("hbeginDate").length()!=0){
			 
		     
			  String beginDate=request.getParameter("hbeginDate");
			  String endDate=request.getParameter("hendDate");
	
			 List sl=new ArrayList();
			 List tl=new ArrayList();
			 
			 SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
			 java.util.Date sd=sdf.parse(beginDate);
			 java.util.Date ed=sdf.parse(endDate);
			 
			 if(!sd.after(ed)){
	
				 //给定时段的访问量
				 String sqlstring="select new Map(uai.accessDate as accessDate,count(uai.id) as accessNum) from FirstpageAccess uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"' group by uai.accessDate order by uai.accessDate";
			     sl=userAccessService.findFirst(sqlstring);
			     
			     sqlstring="select new Map(count(uai.id) as totalNum) from FirstpageAccess uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     tl=userAccessService.findFirst(sqlstring);
			     		 
			 }
			
			 if(sl!=null&&sl.size()!=0){
				 request.setAttribute("tjlist",sl);
				 request.setAttribute("tjlisttotal",tl);
				 request.setAttribute("beginDate",beginDate);
				 request.setAttribute("endDate",endDate);				
				 
				 return mapping.findForward("tongjifirst");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjifirst");
			 } 
	  }	
	  else
			return mapping.findForward("tongjifirst");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action tongji list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward firstAccessview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		try {
			 if(userAccessService==null)
				 System.out.println("service is null");
			 String viewDate=request.getParameter("viewDate");
          	
			 List firstAccessList=userAccessService.findFirst("select new Map(uai.accessDate as accessDate,uai.accessTime as accessTime,uai.accessIp as accessIp) from FirstpageAccess uai where uai.accessDate='"+viewDate+"' order by uai.accessTime");
				 
			if(firstAccessList!=null&&firstAccessList.size()!=0){
				 
				 request.setAttribute("accesslist",firstAccessList);
            
				 return mapping.findForward("accesslist");
			 }
			 else
				 return mapping.findForward("accesslist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward tongjiMain(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		try {
		  if(userAccessService==null)
				 System.out.println("service is null");
			 			 
		  if(request.getParameter("hbeginDate")!=null&&request.getParameter("hbeginDate").length()!=0){
			 
		     
			  String beginDate=request.getParameter("hbeginDate");
			  String endDate=request.getParameter("hendDate");
			  String userName=request.getParameter("huserName");
			  String trueName=request.getParameter("htrueName");
	
			 List sl=new ArrayList();
			 List tl=new ArrayList();
			 
			 SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
			 java.util.Date sd=sdf.parse(beginDate);
			 java.util.Date ed=sdf.parse(endDate);
			 
			 if(!sd.after(ed)){
	
				 //给定时段的访问量
				 String sqlstring="select new Map(uai.accessDate as accessDate,count(uai.id) as accessNum) from BmAccessInfo uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     
				 if(request.getParameter("huserName")!=null&&request.getParameter("huserName").length()!=0)
					 sqlstring=sqlstring+" and uai.userName like '%"+request.getParameter("huserName")+"%'";
				 
				 if(request.getParameter("htrueName")!=null&&request.getParameter("htrueName").length()!=0)
					 sqlstring=sqlstring+" and uai.trueName like '%"+request.getParameter("htrueName")+"%'";
				 
				 sqlstring=sqlstring+" group by uai.accessDate order by uai.accessDate";
				 
				 sl=userAccessService.findMain(sqlstring);
			     
			     sqlstring="select new Map(count(uai.id) as totalNum) from BmAccessInfo uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     
			     if(request.getParameter("huserName")!=null&&request.getParameter("huserName").length()!=0)
					 sqlstring=sqlstring+" and uai.userName like '%"+request.getParameter("huserName")+"%'";
				 
				 if(request.getParameter("htrueName")!=null&&request.getParameter("htrueName").length()!=0)
					 sqlstring=sqlstring+" and uai.trueName like '%"+request.getParameter("htrueName")+"%'";
				 
			     tl=userAccessService.findMain(sqlstring);
			     		 
			 }
			
			 if(sl!=null&&sl.size()!=0){
				 request.setAttribute("tjlist",sl);
				 request.setAttribute("tjlisttotal",tl);
				 request.setAttribute("beginDate",beginDate);
				 request.setAttribute("endDate",endDate);
				 request.setAttribute("userName",userName);
				 request.setAttribute("trueName",trueName);
				 
				 return mapping.findForward("tongjimain");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjimain");
			 } 
	  }	
	  else
			return mapping.findForward("tongjimain");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action tongji list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mainAccessview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		try {
			 if(userAccessService==null)
				 System.out.println("service is null");
			 String viewDate=request.getParameter("viewDate");
			 String userName=request.getParameter("huserName");
			 String trueName=request.getParameter("htrueName");
			 
			 String sqlstring="select new Map(uai.accessDate as accessDate,uai.accessTime as accessTime,uai.userName as userName,uai.trueName as trueName,uai.ipAddress as accessIp) from BmAccessInfo uai where uai.accessDate='"+viewDate+"'";
          	 
			 if(request.getParameter("huserName")!=null&&request.getParameter("huserName").length()!=0)
				 sqlstring=sqlstring+" and uai.userName like '%"+request.getParameter("huserName")+"%'";
			 
			 if(request.getParameter("htrueName")!=null&&request.getParameter("htrueName").length()!=0)
				 sqlstring=sqlstring+" and uai.trueName like '%"+request.getParameter("htrueName")+"%'";
			 
			 sqlstring=sqlstring+" order by uai.accessTime";
			 
			 List firstAccessList=userAccessService.findFirst(sqlstring);
			 			 
			HashMap roleMap=getRoleMap();
			
			if(firstAccessList!=null&&firstAccessList.size()!=0){
				String usernamestring="";
				String usernamestringapx="";
				for(int i=0;i<firstAccessList.size();i++){
					 Map m=(Map)firstAccessList.get(i);					 
					 if(i<4000&&m.get("userName")!=null){
						 String un=(String)m.get("userName");
						 usernamestring=usernamestring+"'"+un+"'"+",";						 
					}
					 if(i>3999&&m.get("userName")!=null){
						 String un=(String)m.get("userName");
						 usernamestringapx=usernamestringapx+"'"+un+"'"+",";						 
					}
				}				
				
				List rolers=null;
				List rolersapx=null;
				if(usernamestring.length()>0)
					usernamestring=usernamestring.substring(0,usernamestring.length()-1);
				if(usernamestringapx.length()>0)
					usernamestringapx=usernamestringapx.substring(0,usernamestringapx.length()-1);
				
				if(usernamestring.length()>0){				    				    
				    sqlstring="select distinct new Map(act.name as accountname,elements(act.roles) as accountroles) from Account act where act.name in ("+usernamestring+")";
				    rolers=userAccessService.findFirst(sqlstring);
				}
				if(usernamestringapx.length()>0){									    
				    sqlstring="select distinct new Map(act.name as accountname,elements(act.roles) as accountroles) from Account act where act.name in ("+usernamestringapx+")";
				    rolersapx=userAccessService.findFirst(sqlstring);
				}
				
				 //人员角色HashMap
				 HashMap myrolemap=new HashMap();
				 if(rolers!=null&&rolers.size()>0){					 
					 for(int i=0;i<rolers.size();i++){
						 Map curact=(Map)rolers.get(i);
						 if(curact!=null){
							    String roleName="";
							    Role accountRole  = (Role)curact.get("accountroles");						    
								if(accountRole != null){									
									if(roleMap.get(accountRole.getId())!=null)
										roleName=(String)roleMap.get(accountRole.getId());																		
								}
								if(myrolemap.get(curact.get("accountname"))!=null&&roleName.length()>0)
								    myrolemap.put(curact.get("accountname"),myrolemap.get(curact.get("accountname"))+","+roleName);
								else
									myrolemap.put(curact.get("accountname"),roleName);
						 }
					 }					 
				 }
				 if(rolersapx!=null&&rolersapx.size()>0){					 
					 for(int i=0;i<rolersapx.size();i++){
						 Map curact=(Map)rolersapx.get(i);
						 if(curact!=null){
							    String roleName="";
							    Role accountRole  = (Role)curact.get("accountroles");						    
								if(accountRole != null){									
									if(roleMap.get(accountRole.getId())!=null)
										roleName=(String)roleMap.get(accountRole.getId());																		
								}
								if(myrolemap.get(curact.get("accountname"))!=null&&roleName.length()>0){
									if(((String)myrolemap.get(curact.get("accountname"))).indexOf(roleName)==-1)
								        myrolemap.put(curact.get("accountname"),myrolemap.get(curact.get("accountname"))+","+roleName);
								}
								else
									myrolemap.put(curact.get("accountname"),roleName);
						 }
					 }					 
				 }
				 
					 for(int i=0;i<firstAccessList.size();i++){
						 Map m=(Map)firstAccessList.get(i);					 
						 if(m.get("userName")!=null){
							 String un=((String)m.get("userName")).trim();
							 
							 if(myrolemap.get(un)!=null)
								 m.put("roleNames",((String)myrolemap.get(un)).trim());
							 else
								 m.put("roleNames","");
						 }
						 else{
							 m.put("roleNames","");
						 }
					 }		

				 request.setAttribute("accesslist",firstAccessList);
            
				 return mapping.findForward("mainaccesslist");
			 }
			 else
				 return mapping.findForward("mainaccesslist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}

	public HashMap getRoleMap(){
		List roleList=userAccessService.findFirst("select new Map(a.id as roleid,a.name as rolename) from Role a ");
		HashMap roleMap=new HashMap();
		if(roleList!=null&&roleList.size()>0){
			for (int i = 0; i < roleList.size(); i++) {
				HashMap temp = (HashMap) roleList.get(i);
				roleMap.put(temp.get("roleid"), temp
						.get("rolename"));
		 }
		}
		return roleMap;
	}
	
}
