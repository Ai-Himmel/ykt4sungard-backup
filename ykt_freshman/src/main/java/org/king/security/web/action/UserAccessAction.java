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
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;


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
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.security.domain.FirstpageAccess;
import org.king.security.domain.Menu;
import org.king.security.domain.Role;
import org.king.security.service.UserAccessService;

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
		FirstpageAccess firstpageAccess=new FirstpageAccess();
		try {
			java.util.Date now = new java.util.Date();
			SimpleDateFormat formatter1 = new SimpleDateFormat ("yyyy-MM-dd");
			SimpleDateFormat formatter2 = new SimpleDateFormat ("HH':'mm':'ss");
			
			String dateStr = formatter1.format(now);
			String timeStr=formatter2.format(now);
			
			firstpageAccess.setAccessDate(new java.sql.Date(Integer.parseInt(dateStr.substring(0,4))-1900,Integer.parseInt(dateStr.substring(5,7))-1,Integer.parseInt(dateStr.substring(8))));		    
			firstpageAccess.setAccessTime(new Time(Integer.parseInt(timeStr.substring(0,2)),Integer.parseInt(timeStr.substring(3,5)),0));
		    firstpageAccess.setAccessIp(request.getRemoteAddr());
			
 		    // 数据库验证
		
			 if(userAccessService==null)
				 System.out.println("service is null");
			
			 userAccessService.saveFirst(firstpageAccess);
			 
			 List noticeList=userAccessService.findFirst("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.ifDeleted='9'");
			  
			 if(noticeList!=null&&noticeList.size()>0)
		         request.setAttribute("noticelist",noticeList);
			 
			 //System.out.println("add success");			 
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("add error");			
			return mapping.findForward("faile");
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
	
	public ActionForward tongjiMainSimple(ActionMapping mapping, ActionForm form,
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
				 String sqlstring="select new Map(uai.accessDate as accessDate,count(uai.id) as accessNum) from MainpageAccess uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     
				 if(request.getParameter("huserName")!=null&&request.getParameter("huserName").length()!=0)
					 sqlstring=sqlstring+" and uai.userName like '%"+request.getParameter("huserName")+"%'";
				 
				 if(request.getParameter("htrueName")!=null&&request.getParameter("htrueName").length()!=0)
					 sqlstring=sqlstring+" and uai.trueName like '%"+request.getParameter("htrueName")+"%'";
				 
				 sqlstring=sqlstring+" group by uai.accessDate order by uai.accessDate";
				 
				 sl=userAccessService.findMain(sqlstring);
			     
			     sqlstring="select new Map(count(uai.id) as totalNum) from MainpageAccess uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     
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
				 
				 return mapping.findForward("tongjimainsimple");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjimainsimple");
			 } 
	  }	
	  else
			return mapping.findForward("tongjimainsimple");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action tongji list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mainAccessviewSimple(ActionMapping mapping, ActionForm form,
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
			 
			 String sqlstring="select new Map(uai.accessDate as accessDate,uai.accessTime as accessTime,uai.userName as userName,uai.trueName as trueName,uai.ipAddress as accessIp) from MainpageAccess uai where uai.accessDate='"+viewDate+"'";
          	 
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
					 else if(i>3999&&m.get("userName")!=null){
						 String un=(String)m.get("userName");
						 usernamestringapx=usernamestringapx+"'"+un+"'"+",";
					 }
				}
				List rs=null;
				List rsapx=null;
				List rolers=null;
				if(usernamestring.length()>0)
					usernamestring=usernamestring.substring(0,usernamestring.length()-1);
				if(usernamestringapx.length()>0)
					usernamestringapx=usernamestringapx.substring(0,usernamestringapx.length()-1);
				
				if(usernamestring.length()>0){					
				    sqlstring="select distinct new Map(ac.name as userName,s.fromProvince as fromProvince) from Studentmodel s,Account ac,Person ps where ac.id=ps.id and ps.personCode=s.studentNo and ac.name in ("+usernamestring+")";
				    rs=userAccessService.findFirst(sqlstring);
				    
//				    sqlstring="select distinct new Map(act.name as accountname,elements(act.roles) as accountroles) from Account act where act.name in ("+usernamestring+")";
//				    rolers=userAccessService.findFirst(sqlstring);
				}
				if(usernamestringapx.length()>0){
					sqlstring="select distinct new Map(ac.name as userName,s.fromProvince as fromProvince) from Studentmodel s,Account ac,Person ps where ac.id=ps.id and ps.personCode=s.studentNo and ac.name in ("+usernamestringapx+")";
				    rsapx=userAccessService.findFirst(sqlstring);
				}
				//生源地HashMap
				 HashMap myhashmap=new HashMap();
				 if(rs!=null&&rs.size()>0){
					 for (int i = 0; i < rs.size(); i++) {
							HashMap temp = (HashMap) rs.get(i);
							myhashmap.put(temp.get("userName"), temp
									.get("fromProvince"));
					 }
				 }
				 if(rsapx!=null&&rsapx.size()>0){
					 for(int i=0;i<rsapx.size();i++){
						 HashMap temp = (HashMap) rsapx.get(i);
						 if(myhashmap.get(temp.get("userName"))==null)
							myhashmap.put(temp.get("userName"), temp
									.get("fromProvince"));
					 }
				 }
				 //人员角色HashMap
//				 HashMap myrolemap=new HashMap();
//				 if(rolers!=null&&rolers.size()>0){					 
//					 for(int i=0;i<rolers.size();i++){
//						 Map curact=(Map)rolers.get(i);
//						 if(curact!=null){
//							    String roleName="";
//							    Role accountRole  = (Role)curact.get("accountroles");						    
//								if(accountRole != null){									
//									if(roleMap.get(accountRole.getId())!=null)
//										roleName=(String)roleMap.get(accountRole.getId());																		
//								}
//								if(myrolemap.get(curact.get("accountname"))!=null&&roleName.length()>0)
//								    myrolemap.put(curact.get("accountname"),myrolemap.get(curact.get("accountname"))+","+roleName);
//								else
//									myrolemap.put(curact.get("accountname"),roleName);
//						 }
//					 }					 
//				 }
				 
					 for(int i=0;i<firstAccessList.size();i++){
						 Map m=(Map)firstAccessList.get(i);					 
						 if(m.get("userName")!=null){
							 String un=((String)m.get("userName")).trim();
							 if(myhashmap.get(un)!=null)
						         m.put("fromProvince",((String)myhashmap.get(un)).trim());
							 else
								 m.put("fromProvince","");
//							 if(myrolemap.get(un)!=null)
//								 m.put("roleNames",((String)myrolemap.get(un)).trim());
//							 else
//								 m.put("roleNames","");
						 }
						 else{
							 m.put("fromProvince","");
//							 m.put("roleNames","");
						 }
					 }
				     
				
//				 for(int i=0;i<firstAccessList.size();i++){
//					 Map m=(Map)firstAccessList.get(i);
//					 String un=(String)m.get("userName");
//					 
//					 String fp="";
//					 if(rs!=null&&rs.size()>0){
//						 int j=0;
//					     for(j=0;j<rs.size();j++){
//					    	 Map n=(Map)rs.get(j);
//					    	 String un2=(String)n.get("userName");
//					    	 if(un2.equals(un)){
//					             m.put("fromProvince",n.get("fromProvince"));
//					             break;
//					    	 }
//					     }
//					     if(j==rs.size()||j>rs.size())
//					    	 m.put("fromProvince","");
//					 }
//				 }
				 
				 ChangeProvinceValue(firstAccessList);
				 request.setAttribute("accesslist",firstAccessList);
            
				 return mapping.findForward("mainaccesslistsimple");
			 }
			 else
				 return mapping.findForward("mainaccesslistsimple");
			 
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
				 String sqlstring="select new Map(uai.accessDate as accessDate,count(uai.id) as accessNum) from MainpageAccess uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     
				 if(request.getParameter("huserName")!=null&&request.getParameter("huserName").length()!=0)
					 sqlstring=sqlstring+" and uai.userName like '%"+request.getParameter("huserName")+"%'";
				 
				 if(request.getParameter("htrueName")!=null&&request.getParameter("htrueName").length()!=0)
					 sqlstring=sqlstring+" and uai.trueName like '%"+request.getParameter("htrueName")+"%'";
				 
				 sqlstring=sqlstring+" group by uai.accessDate order by uai.accessDate";
				 
				 sl=userAccessService.findMain(sqlstring);
			     
			     sqlstring="select new Map(count(uai.id) as totalNum) from MainpageAccess uai where uai.accessDate between '"+beginDate+"' and '"+endDate+"'";
			     
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
			 
			 String sqlstring="select new Map(uai.accessDate as accessDate,uai.accessTime as accessTime,uai.userName as userName,uai.trueName as trueName,uai.ipAddress as accessIp) from MainpageAccess uai where uai.accessDate='"+viewDate+"'";
          	 
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
//					 Account curact=(Account)m.get("act");
//					 if(curact!=null){
//						    Set accountRoles  = curact.getRoles();						    
//							if(accountRoles != null){
//								String roleNames="";
//								for(Iterator iterator = accountRoles.iterator();iterator.hasNext();){
//									Role role = (Role)iterator.next();
//									if(roleMap.get(role.getId())!=null)
//										roleNames=roleNames+roleMap.get(role.getId())+",";											
//								 }								
//								if(roleNames.length()>0){
//									roleNames=roleNames.substring(0,roleNames.length()-1);
//									m.put("roleNames",roleNames);
//								}
//								else
//									m.put("roleNames","");
//							}
//					 }
				}
				List rs=null;
				List rsapx=null;
				List rolers=null;
				List rolersapx=null;
				if(usernamestring.length()>0)
					usernamestring=usernamestring.substring(0,usernamestring.length()-1);
				if(usernamestringapx.length()>0)
					usernamestringapx=usernamestringapx.substring(0,usernamestringapx.length()-1);
				
				if(usernamestring.length()>0){					
				    sqlstring="select distinct new Map(ac.name as userName,s.fromProvince as fromProvince) from Studentmodel s,Account ac,Person ps where ac.id=ps.id and ps.personCode=s.studentNo and ac.name in ("+usernamestring+")";
				    rs=userAccessService.findFirst(sqlstring);
				    
				    sqlstring="select distinct new Map(act.name as accountname,elements(act.roles) as accountroles) from Account act where act.name in ("+usernamestring+")";
				    rolers=userAccessService.findFirst(sqlstring);
				}
				if(usernamestringapx.length()>0){
					sqlstring="select distinct new Map(ac.name as userName,s.fromProvince as fromProvince) from Studentmodel s,Account ac,Person ps where ac.id=ps.id and ps.personCode=s.studentNo and ac.name in ("+usernamestringapx+")";
				    rsapx=userAccessService.findFirst(sqlstring);
				    
				    sqlstring="select distinct new Map(act.name as accountname,elements(act.roles) as accountroles) from Account act where act.name in ("+usernamestringapx+")";
				    rolersapx=userAccessService.findFirst(sqlstring);
				}
				//生源地HashMap
				 HashMap myhashmap=new HashMap();
				 if(rs!=null&&rs.size()>0){
					 for (int i = 0; i < rs.size(); i++) {
							HashMap temp = (HashMap) rs.get(i);
							myhashmap.put(temp.get("userName"), temp
									.get("fromProvince"));
					 }
				 }
				 if(rsapx!=null&&rsapx.size()>0){
					 for(int i=0;i<rsapx.size();i++){
						 HashMap temp = (HashMap) rsapx.get(i);
						 if(myhashmap.get(temp.get("userName"))==null)
							myhashmap.put(temp.get("userName"), temp
									.get("fromProvince"));
					 }
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
							 if(myhashmap.get(un)!=null)
						         m.put("fromProvince",((String)myhashmap.get(un)).trim());
							 else
								 m.put("fromProvince","");
							 if(myrolemap.get(un)!=null)
								 m.put("roleNames",((String)myrolemap.get(un)).trim());
							 else
								 m.put("roleNames","");
						 }
						 else{
							 m.put("fromProvince","");
							 m.put("roleNames","");
						 }
					 }
				     
				
//				 for(int i=0;i<firstAccessList.size();i++){
//					 Map m=(Map)firstAccessList.get(i);
//					 String un=(String)m.get("userName");
//					 
//					 String fp="";
//					 if(rs!=null&&rs.size()>0){
//						 int j=0;
//					     for(j=0;j<rs.size();j++){
//					    	 Map n=(Map)rs.get(j);
//					    	 String un2=(String)n.get("userName");
//					    	 if(un2.equals(un)){
//					             m.put("fromProvince",n.get("fromProvince"));
//					             break;
//					    	 }
//					     }
//					     if(j==rs.size()||j>rs.size())
//					    	 m.put("fromProvince","");
//					 }
//				 }
				 
				 ChangeProvinceValue(firstAccessList);
				 request.setAttribute("accesslist",firstAccessList);
            
				 return mapping.findForward("mainaccesslist");
			 }
			 else
				 return mapping.findForward("mainaccesslist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public void ChangeProvinceValue(List list){
//		List majorList=getprovinceList();
//		for(int j=0;j<list.size();j++){
//			 Map n=(Map)list.get(j);
//			 if(n.get("fromProvince")!=null){
//			   String mj=((String)n.get("fromProvince")).trim();
//			   for(int k=0;k<majorList.size();k++){
//				 Map n1=(Map)majorList.get(k);
//				 String mj1=((String)n1.get("dictValue")).trim();
//				 if(mj.equals(mj1)){
//					 n.put("fromProvinceName",((String)n1.get("dictCaption")).trim());
//				 }
//			   }
//			 }
//			 else
//				 n.put("fromProvinceName","");
//		 }
		HashMap Hash_fromprovince = new HashMap();
		List Temp_fromprovince =getprovinceList();
		for (int i = 0; i < Temp_fromprovince.size(); i++) {
			HashMap temp = (HashMap) Temp_fromprovince.get(i);
			Hash_fromprovince.put(temp.get("dictValue"), temp
					.get("dictCaption"));
		}
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("fromProvince")!=null&&!n.get("fromProvince").equals("")){
			     String mj=((String)n.get("fromProvince")).trim();
			     n.put("fromProvinceName",((String)Hash_fromprovince.get(mj)).trim());
			 }
			 else
				 n.put("fromProvinceName","");
		}
	}
	
	public List getprovinceList(){
		List provinceList=userAccessService.findFirst("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
		return provinceList;
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
