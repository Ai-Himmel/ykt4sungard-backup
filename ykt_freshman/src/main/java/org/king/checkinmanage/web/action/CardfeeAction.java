/**
 * 
 */
package org.king.checkinmanage.web.action;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;

/**
 * @author jackey
 *
 */
public class CardfeeAction extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		StuCardfeeInfo stucardfeeinfo = (StuCardfeeInfo)aform.get("stucardfeeinfo");
        
		try {
			 
			 stucardfeeinfo.setEcardPayed(request.getParameter("ecardPayed"+request.getParameter("updateid")));
			 stucardfeeinfo.setBathcardPayed(request.getParameter("bathcardPayed"+request.getParameter("updateid")));
			 stucardfeeinfo.setBathcardNo(request.getParameter("bathcardNo"+request.getParameter("updateid")));
	      	 stucardfeeinfo.setStudentNo(request.getParameter("studentNo"+request.getParameter("updateid")));	      	 
	      	 stucardfeeinfo.setEnrollYear(request.getParameter("enrollYear"+request.getParameter("updateid")));
	      	 stucardfeeinfo.setEcardPhoto(request.getParameter("ecardPhoto"+request.getParameter("updateid")));
	      	 stucardfeeinfo.setUpdatorId(request.getParameter("updatorId"+request.getParameter("updateid")));
	      	 stucardfeeinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      		      	 
		     stucardfeeinfo.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stucardfeeinfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			request.setAttribute("msg","1");
			return list(mapping, form, request, response);
		}

	}
	
	public ActionForward updateall(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		boolean flag=false;
		
		String[] ids=request.getParameterValues("cbgroup");
		for(int i=0;i<ids.length;i++){
		    DynaValidatorForm aform = (DynaValidatorForm) form;	        
		    StuCardfeeInfo stucardfeeinfo = new StuCardfeeInfo();
        
		    try {
			 
		    	 stucardfeeinfo.setEcardPayed(request.getParameter("ecardPayed"+ids[i]));
		         stucardfeeinfo.setBathcardPayed(request.getParameter("bathcardPayed"+ids[i]));	
		         stucardfeeinfo.setBathcardNo(request.getParameter("bathcardNo"+ids[i]));
		      	 stucardfeeinfo.setStudentNo(request.getParameter("studentNo"+ids[i]));		      	 
		      	 stucardfeeinfo.setEnrollYear(request.getParameter("enrollYear"+ids[i]));
		         stucardfeeinfo.setEcardPhoto(request.getParameter("ecardPhoto"+ids[i]));
		      	 stucardfeeinfo.setUpdatorId(request.getParameter("updatorId"+ids[i]));
		      	 stucardfeeinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
		      		      	 
			     stucardfeeinfo.setId(ids[i]);

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stucardfeeinfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 flag=true;
			 
		    } catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			flag=false;
			request.setAttribute("msg","1");
		    return list(mapping, form, request, response);
			
		    }
		}
		if(flag)
		    return mapping.findForward("success");
		else{
			request.setAttribute("msg","1");
		    return list(mapping, form, request, response);
		}

	}
	
	public ActionForward find(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
                //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			    Studentmodel stuinfo=new Studentmodel();
				stuinfo.setEnterenceNo(request.getParameter("henrollNo"));
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));
				stuinfo.setGender(request.getParameter("hgender"));
				stuinfo.setStuName(request.getParameter("hstuName"));
				stuinfo.setMajorin(request.getParameter("hmajorin"));
				stuinfo.setFromProvince(request.getParameter("hfromProvince"));
			 
             //国籍
				List areaList=getcountryList();
				if(areaList!=null&&areaList.size()>0)
					request.setAttribute("arealist",areaList);
             //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList); 
			 
			 List stuarriveinfoList=null;
			 String classNo="";			 
			 Account manager=(Account)session.getAttribute("accountPerson");	            
	         String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
	         List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"'");
	         if(managerclassList!=null&&managerclassList.size()>0){
	        	 
				 classNo=(String)managerclassList.get(0);
				 
				 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from StuCardfeeSubmit cs where cs.classNo='"+classNo+"'";
				 
			     List cardfeesubmitList=checkinmanageservice.find(sqlstring);
			 
			     if(cardfeesubmitList!=null&&cardfeesubmitList.size()>0)
				     request.setAttribute("cardfeesubmit",cardfeesubmitList);
			 
			     sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.nationality as nationality,c.classNo as classNo,ci.ecardPayed as ecardPayed,ci.bathcardPayed as bathcardPayed,ci.bathcardNo as bathcardNo,ci.updatorId as updatorId,ci.updateTime as updateTime) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId";
			 
			    if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				    sqlstring=sqlstring+" and s.enterenceNo like '%"+request.getParameter("henrollNo")+"%'";
			 
			    if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				    sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			    if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				   sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			    if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				   sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
			 
			    if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				   sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			    if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
			       sqlstring=sqlstring+" and s.nationality='"+request.getParameter("hfromProvince")+"'";
			 			 
			    sqlstring=sqlstring+" and c.classNo='"+classNo+"'";//班级条件,要从session中获取
			    sqlstring=sqlstring+" order by ci.studentNo";
			 
			    //System.out.println(sqlstring);
			 
			    stuarriveinfoList=checkinmanageservice.find(sqlstring);
	         }			 
			 
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){					 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuarriveinfoList;
				 else if((Integer.parseInt(offset))<stuarriveinfoList.size()||(Integer.parseInt(offset))==stuarriveinfoList.size())
					 resultList=stuarriveinfoList.subList((Integer.parseInt(offset)),stuarriveinfoList.size());
				 
				 request.setAttribute("stuinfo",stuinfo);
				 request.setAttribute("checkinlist",resultList);
				 request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));
				 //System.out.println("find success");
				 return mapping.findForward("cardfeefindlist");				 
			 }
			 
			 else
				 return mapping.findForward("cardfeefindlist"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward list(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 //指定班级的新生档案袋信息列表,classNo要从session中取得
			 List stucheckininfoList=null;
             String classNo="";			 
			 Account manager=(Account)session.getAttribute("accountPerson");	            
	         String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
	         List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and m.managerNo='"+managerNo+"'");
	         if(managerclassList!=null&&managerclassList.size()>0){
				 classNo=(String)managerclassList.get(0);
	             stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.nationality as nationality,c.classNo as classNo,ci.ecardPayed as ecardPayed,ci.bathcardPayed as bathcardPayed,ci.bathcardNo as bathcardNo,ci.updatorId as updatorId,ci.updateTime as updateTime) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+classNo+"'");
	         }         
			 			 
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 //国籍
				 List areaList=getcountryList();
				 if(areaList!=null&&areaList.size()>0)
					 request.setAttribute("arealist",areaList);
	             //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList); 
				 request.setAttribute("checkinlist",stucheckininfoList);
				 request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 System.out.println("list success");
				 return mapping.findForward("cardfeelist");
			 }
			 else
				 return mapping.findForward("cardfeelist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}

	public List getmajorList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
		
		Comparator comp1 = new Comparator() { 
				public int compare(Object o1, Object o2){ 
				Map m1 = (Map)o1; 
				Map m2 = (Map)o2; 
				String dictCaption1 = (String)m1.get("dictCaption"); 
				String dictCaption2 = (String)m2.get("dictCaption");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
                //注意,返回值是比较的结果>0,=0,或者<0
			    return collator.compare(c1.getSourceString(),c2.getSourceString());				
				 } 
		} ;				
			 
		Collections.sort(majorList, comp1);		
		
		return majorList;
	}
	
	public List getcountryList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
		Comparator comp1 = new Comparator() { 
			public int compare(Object o1, Object o2){ 
			Map m1 = (Map)o1; 
			Map m2 = (Map)o2; 
			String dictCaption1 = (String)m1.get("dictCaption"); 
			String dictCaption2 = (String)m2.get("dictCaption");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
            //注意,返回值是比较的结果>0,=0,或者<0
		    return collator.compare(c1.getSourceString(),c2.getSourceString());				
			 } 
	    } ;				
		 
	    Collections.sort(majorList, comp1);
		return majorList;
	}

}
