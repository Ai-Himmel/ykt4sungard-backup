/**
 * 
 */
package org.king.classmanage.web.action;

import java.io.OutputStream;
import java.sql.Date;
import java.sql.Time;
import java.sql.Timestamp;
import java.sql.Types;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.StringUtils;
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
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.StuAdddelhis;
import org.king.classmanage.domain.StudentSharedb;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.dao.MyQuery;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.service.AccountService;
import org.king.security.service.SecurityService;
import org.king.utils.DateUtil;

/**
 * @author Margaret
 *
 */
public class StuAddDelAction extends BaseAction {

	private StudentService studentService;
	
    private AccountService accountService;
	
	private SecurityService securityService;
	
	private ManagerService managerService;
	
    private CheckinmanageService checkinmanageservice;
    
	public static SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy");	
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}

	/**
	 * @param studentService
	 *            The studentService to set.
	 */
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
	public void setSecurityService(SecurityService securityService) {
		this.securityService = securityService;
	}

	/**
	 * @param accountService The accountService to set.
	 */
	public void setAccountService(AccountService accountService) {
		this.accountService = accountService;
	}
	
	public void setManagerService(ManagerService managerservice) {
		this.managerService = managerservice;
	}
	
	public ActionForward load4addstu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		return mapping.findForward("addstu");
	}
	
	//从共享数据库中查找新生
	public ActionForward findstuinfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			 if(studentService==null)
				 System.out.println("service is null");
			 			 			 
                //生源地
				List provinceList = studentService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
				if(provinceList!=null&&provinceList.size()>0)
				    request.setAttribute("arealist", provinceList);		
		        //国籍
				List countryList=studentService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
				if(countryList!=null&&countryList.size()>0)
					request.setAttribute("countrylist",countryList);
		        //专业
				List majorList=studentService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList); 
							
//				String datebuf = sdf1.format(new java.util.Date());//当前年份		
				
				String sqlstring="select new Map(s.studentNo as studentNo," +
												"s.enrollYear as enrollYear," +
												"s.stuName as stuName," +
												"s.gender as gender," +
												"s.majorin as majorin," +
												"s.fromProvince as fromProvince," +
												"s.nationality as nationality) from StudentSharedb s " +
												"where s.studentNo='"+request.getParameter("studentNo")+"' ";
			 				 
			    List stuinfoList=studentService.find(sqlstring);
			    
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 request.setAttribute("stuinfo",stuinfoList);
				 return mapping.findForward("addstu");				 
			 }
			 
			 else{
				 request.setAttribute("msg","-1");
				 return mapping.findForward("addstu"); 
			 }
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward addstu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		StuAdddelhis stuAdddelhis = (StuAdddelhis)aform.get("stuAdddelhis");
		
        String msg="";
		try {
			if(studentService==null)
			     System.out.println("service is null");
			
			 //生源地
			List provinceList = studentService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
			if(provinceList!=null&&provinceList.size()>0)
			    request.setAttribute("arealist", provinceList);		
	        //国籍
			List countryList=studentService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
			if(countryList!=null&&countryList.size()>0)
				request.setAttribute("countrylist",countryList);
	        //专业
			List majorList=studentService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
			if(majorList!=null&&majorList.size()>0)
				request.setAttribute("majorinlist",majorList); 
			
			String studentNo=stuAdddelhis.getStudentNo();
			
			String sqlstring="select new Map(s.studentNo as studentNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,s.nationality as nationality) from Studentmodel s where s.studentNo='"+studentNo+"'";
			
			List stuList=studentService.find(sqlstring);
			
			if(stuList!=null&&stuList.size()>0){
				request.setAttribute("stuinfo",stuList);
				msg="1";
			}
			else{
			     List originstu=studentService.find("select new Map(s.studentNo as studentNo,s.enterenceNo as enterenceNo,s.examNo as examNo,s.idCard as idCard,s.birthday as birthday,s.homeTelephone as homeTelephone,s.nation as nation,s.midSchCode as midSchCode,s.midSchName as midSchName,s.polityBg as polityBg,s.department as department,s.specIntrst as specIntrst,s.studentType as studentType,s.curGrade as curGrade,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,s.nationality as nationality) from StudentSharedb s where s.studentNo='"+studentNo+"'");
			     
			     if(originstu!=null&&originstu.size()>0){
			    	 
			         studentService.addstu(originstu);
			         
			         Account manager=(Account)session.getAttribute("accountPerson");	            
			         String managerNo=manager.getPerson().getPersonName();	//获取登录者的姓名					
					
				     	stuAdddelhis.setAddOrDel("1");//1- 添加；2- 删除			
				    	stuAdddelhis.setOperatorId(managerNo);
					    stuAdddelhis.setOperateTime(new Timestamp(System.currentTimeMillis()));		    
				    
					 studentService.saveAddStu(stuAdddelhis);	
			         msg="0";
			     }
		    	
			}
			
			 request.setAttribute("msg",msg);
			 return mapping.findForward("addstu");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("add error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward delstu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		String[] ids=request.getParameterValues("cbgroup");
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 
				 Studentmodel sm = studentService.findbyStuId(ids[i]);
		    
 		         // 数据库验证
		   
			     if(studentService==null)
				     System.out.println("service is null");
			     if(sm!=null)
			    	 studentService.deleteStu(sm);
			     
			     Account manager=(Account)session.getAttribute("accountPerson");	            
		         String managerNo=manager.getPerson().getPersonName();	//获取登录者的姓名	
		         			     
			     StuAdddelhis stuAdddelhis =new StuAdddelhis();
			     stuAdddelhis.setStudentNo(sm.getStudentNo());
			     stuAdddelhis.setAddOrDel("2");
			     stuAdddelhis.setOperatorId(managerNo);
			     stuAdddelhis.setOperateTime(new Timestamp(System.currentTimeMillis()));
			     
			     studentService.saveAddStu(stuAdddelhis);
			     
			     request.setAttribute("msg","0");
			     
		    } catch (Exception e) {
			     e.printStackTrace();
			     System.out.println("delete error");
			     return mapping.findForward("faile");
		    }
		}
		return mapping.findForward("success");
	}


	public ActionForward list(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();
		
		// 生源地
		List provinceList = studentService.getfromProvinceList();
		if(provinceList!=null&&provinceList.size()>0)
		    request.setAttribute("arealist", provinceList);		
        //国籍
		List countryList= studentService.getcountryList();
		if(countryList!=null&&countryList.size()>0)
			request.setAttribute("countrylist",countryList);
        //专业
		List majorList=studentService.getmajorList();
		if(majorList!=null&&majorList.size()>0)
			request.setAttribute("majorinlist",majorList);
		
		

		return mapping.findForward("stuadddellist");
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
			 if(studentService==null)
				 System.out.println("service is null");
			 
                //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			    Studentmodel stuinfo=new Studentmodel();
				
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));
				stuinfo.setGender(request.getParameter("hgender"));
				stuinfo.setStuName(request.getParameter("hstuName"));
				stuinfo.setMajorin(request.getParameter("hmajorin"));
				stuinfo.setFromProvince(request.getParameter("hfromProvince"));
				stuinfo.setNationality(request.getParameter("hnationality"));
			 
				// 生源地
				List provinceList = studentService.getfromProvinceList();
				if(provinceList!=null&&provinceList.size()>0)
				    request.setAttribute("arealist", provinceList);		
		        //国籍
				List countryList= studentService.getcountryList();
				if(countryList!=null&&countryList.size()>0)
					request.setAttribute("countrylist",countryList);
		        //专业
				List majorList=studentService.getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);
			 
			 List stuarriveinfoList=null;
				 
				 String sqlstring="select new Map(s.studentId as id," +
										 		"s.studentNo as studentNo," +
										 		"s.enrollYear as enrollYear," +
										 		"s.stuName as stuName," +
										 		"s.gender as gender," +
										 		"s.majorin as majorin," +
										 		"s.fromProvince as fromProvince," +
										 		"s.nationality as nationality," +
										 		"s.dormId as dormId) " +
										 		"from Studentmodel s where s.majorin<>'623' ";
				 
					String datebuf = sdf1.format(new java.util.Date());//当前年份
					
					sqlstring=sqlstring+" and s.curGrade='"+datebuf+"' ";
					
			    if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				    sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			    if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				   sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			    if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				   sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
			 
			    if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				   sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			    if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
			       sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
			    
			    if(request.getParameter("hnationality")!=null&&request.getParameter("hnationality").length()!=0)
				       sqlstring=sqlstring+" and s.nationality='"+request.getParameter("hnationality")+"'";
			 	
			    sqlstring=sqlstring+" order by s.studentNo";
			 
			    //System.out.println(sqlstring);
			 
			    stuarriveinfoList=studentService.find(sqlstring);
	       			 
			 
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){					 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuarriveinfoList;
				 else if((Integer.parseInt(offset))<stuarriveinfoList.size()||(Integer.parseInt(offset))==stuarriveinfoList.size())
					 resultList=stuarriveinfoList.subList((Integer.parseInt(offset)),stuarriveinfoList.size());
				 
				 request.setAttribute("stuinfo",stuinfo);
				 request.setAttribute("stuinfolist",resultList);
				 request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));
				 //System.out.println("find success");
				 return mapping.findForward("stuadddellist");				 
			 }
			 
			 else
				 return mapping.findForward("stuadddellist"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward hisfind(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		try {
		  if(studentService==null)
				 System.out.println("service is null");
			 			 
		  if(request.getParameter("hbeginDate")!=null&&request.getParameter("hbeginDate").length()!=0){
			 
		     
			  String beginDate=request.getParameter("hbeginDate");
			  String endDate=request.getParameter("hendDate");
			  String userName=request.getParameter("huserName");
			  String trueName=request.getParameter("htrueName");
				 request.setAttribute("beginDate",beginDate);
				 request.setAttribute("endDate",endDate);
				 request.setAttribute("userName",userName);
				 request.setAttribute("trueName",trueName);
	
			 List sl=new ArrayList();
			 List tl=new ArrayList();
			 
			 SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
			 java.util.Date sd=sdf.parse(beginDate);
			 java.util.Date ed=sdf.parse(endDate);
			 MyQuery myQuery = new MyQuery();
			 
			 if(!sd.after(ed)){
	
				 //给定时段的访问量
				 String sqlstring="select new Map(sh.id as id,sh.studentNo as studentNo,s.stuName as stuName,sh.addOrDel as addOrDel,sh.operatorId as operatorId,sh.operateTime as operateTime) from StuAdddelhis sh,StudentSharedb s where sh.studentNo=s.studentNo and sh.operateTime between '"+beginDate+" 00:00:00"+"' and '"+endDate+" 23:59:59"+"'";
			     
				 if(request.getParameter("huserName")!=null&&request.getParameter("huserName").length()!=0)
					 sqlstring=sqlstring+" and sh.studentNo like ?";
				 
				 if(request.getParameter("htrueName")!=null&&request.getParameter("htrueName").length()!=0)
					 sqlstring=sqlstring+" and s.stuName like ?";
				 
				if (StringUtils.isNotEmpty(userName)) {
					myQuery.addPara("%" + userName + "%", Types.VARCHAR);
				}	
				if (StringUtils.isNotEmpty(trueName)) {
					myQuery.addPara("%" + trueName + "%", Types.VARCHAR);
				}					
				 sqlstring=sqlstring+" order by sh.operateTime desc";
				 
				myQuery.setQueryString(sqlstring);				 
				 sl=studentService.find(myQuery);
				 
			 }
			
			 if(sl!=null&&sl.size()!=0){
				 request.setAttribute("tjlist",sl);
					request.setAttribute("listcount", new Integer(sl.size()));

				 
				 return mapping.findForward("stuadddelhis");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("stuadddelhis");
			 } 
	  }	
	  else
			return mapping.findForward("stuadddelhis");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action tongji list error");
			return mapping.findForward("faile");
		}

	}
	
//	从共享数据库中查找非学历新生
	public ActionForward findnotfudan(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			if(studentService==null)
				 System.out.println("service is null");
			 
               //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			    StudentSharedb stuinfo=new StudentSharedb();
				
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));				
				stuinfo.setStuName(request.getParameter("hstuName"));
				stuinfo.setGender(request.getParameter("hgender"));
				stuinfo.setIdType(request.getParameter("hidType"));
				stuinfo.setIdCard(request.getParameter("hidCard"));
				stuinfo.setDepartment(request.getParameter("hdepartment"));
				stuinfo.setMajorin(request.getParameter("hmajorin"));
				stuinfo.setFromProvince(request.getParameter("hfromProvince"));
				stuinfo.setNation(request.getParameter("hnation"));
				stuinfo.setNationality(request.getParameter("hnationality"));
				stuinfo.setPolityBg(request.getParameter("hpolityBg"));
				stuinfo.setCultureMode(request.getParameter("hcultureMode"));
				stuinfo.setStudentChar(request.getParameter("hstudentChar"));
				stuinfo.setStudentType(request.getParameter("hstudentType"));
				stuinfo.setHomeTelephone(request.getParameter("hhomeTelephone"));
				stuinfo.setBirthday(request.getParameter("hbirthday"));
				stuinfo.setAdminCollege(request.getParameter("hadminCollege"));
			 
				// 生源地
				List provinceList = studentService.getfromProvinceList();
				if(provinceList!=null&&provinceList.size()>0)
				    request.setAttribute("arealist", provinceList);	
								
				List departList=studentService.find("select distinct new Map(b.deptCode as deptCode,b.deptName as deptName) " +
						"from StudentSharedb a,Department b " +
						"where a.department=b.deptCode and a.studentChar in ('070001', '070002', '070008') and a.curGrade='"+DateUtil.getNow("yyyy")+"' and a.schoolornot=1 and a.checkornot=0");
				if(departList!=null&&departList.size()>0)
				    request.setAttribute("departlist", departList);
				
				List admincolList=studentService.find("select distinct new Map(b.deptCode as deptCode,b.deptName as deptName) " +
						"from StudentSharedb a,Department b " +
						"where a.adminCollege=b.deptCode and a.studentChar in ('070001', '070002', '070008') and a.curGrade='"+DateUtil.getNow("yyyy")+"' and a.schoolornot=1 and a.checkornot=0");
				if(admincolList!=null&&admincolList.size()>0)
				    request.setAttribute("admincollist", admincolList);
				
				List polityList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 4 order by a.id.dictValue");
				if(polityList!=null&&polityList.size()>0)
				    request.setAttribute("politylist", polityList);	
				
				List nationList=studentService.getnationList();
				if(nationList!=null&&nationList.size()>0)
				    request.setAttribute("nationlist", nationList);	
				
				List cultureList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 26 order by a.id.dictValue");
				if(cultureList!=null&&cultureList.size()>0)
				    request.setAttribute("culturelist", cultureList);	
				
				List stucharList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 27 order by a.id.dictValue");
				if(stucharList!=null&&stucharList.size()>0)
				    request.setAttribute("stucharlist", stucharList);	
				
				List stutypeList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 15 order by a.id.dictValue");
				if(stutypeList!=null&&stutypeList.size()>0)
				    request.setAttribute("stutypelist", stutypeList);	
				
				List idtypeList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
						+ "from Dictionary a where a.id.dictNo= 29 order by a.id.dictValue");
				if(idtypeList!=null&&idtypeList.size()>0)
				    request.setAttribute("idtypelist", idtypeList);
				
				//国籍
				List countryList= studentService.getcountryList();
				if(countryList!=null&&countryList.size()>0)
					request.setAttribute("countrylist",countryList);
		        //专业
				List majorList=studentService.getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);
				
				String order=request.getParameter("horder");
			    String odr="asc";
			    if(order!=null&&order.length()>0&&order.equals("d"))
			    	 odr="desc";
				String orderby=request.getParameter("orderby");
				
				String sqlstring="select new Map(s.studentNo as studentNo," +												
												"s.stuName as stuName," +
												"s.gender as gender," +
												"s.idType as idType," +
												"s.idCard as idCard," +
												"s.birthday as birthday," +
												"s.homeTelephone as homeTelephone," +
												"s.nation as nation," +
												"s.nationality as nationality," +
												"s.fromProvince as fromProvince," +
												"s.polityBg as polityBg," +
												"s.department as department," +												
												"s.majorin as majorin," +												
												"s.studentType as studentType," +
												"s.cultureMode as cultureMode," +
												"s.studentChar as studentChar," +
												"s.adminCollege as adminCollege" +	
												") from StudentSharedb s " +
												"where s.studentChar in ('070001', '070002', '070008') and s.curGrade='"+DateUtil.getNow("yyyy")+"' and s.schoolornot=1 and s.checkornot=0 ";
			 
				if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				    sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
				
				if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
					   sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
				
			    if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				   sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
			    
			    if(request.getParameter("hdepartment")!=null&&request.getParameter("hdepartment").length()!=0)
					   sqlstring=sqlstring+" and s.department='"+request.getParameter("hdepartment")+"'";
						
			    if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				   sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
			    
			    if(request.getParameter("hidType")!=null&&request.getParameter("hidType").length()!=0)
					   sqlstring=sqlstring+" and s.idType='"+request.getParameter("hidType")+"'";
			    
			    if(request.getParameter("hidCard")!=null&&request.getParameter("hidCard").length()!=0)
					   sqlstring=sqlstring+" and s.idCard like '%"+request.getParameter("hidCard")+"%'";
			 
			    if(request.getParameter("hnation")!=null&&request.getParameter("hnation").length()!=0)
					   sqlstring=sqlstring+" and s.nation='"+request.getParameter("hnation")+"'";
			    
			    if(request.getParameter("hnationality")!=null&&request.getParameter("hnationality").length()!=0)
				       sqlstring=sqlstring+" and s.nationality='"+request.getParameter("hnationality")+"'";
			 
			    if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
			       sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
			    
			    if(request.getParameter("hpolityBg")!=null&&request.getParameter("hpolityBg").length()!=0)
				       sqlstring=sqlstring+" and s.polityBg='"+request.getParameter("hpolityBg")+"'";
			    
			    if(request.getParameter("hcultureMode")!=null&&request.getParameter("hcultureMode").length()!=0)
				       sqlstring=sqlstring+" and s.cultureMode='"+request.getParameter("hcultureMode")+"'";
			    
			    if(request.getParameter("hstudentChar")!=null&&request.getParameter("hstudentChar").length()!=0)
				       sqlstring=sqlstring+" and s.studentChar='"+request.getParameter("hstudentChar")+"'";
			    
			    if(request.getParameter("hstudentType")!=null&&request.getParameter("hstudentType").length()!=0)
				       sqlstring=sqlstring+" and s.studentType='"+request.getParameter("hstudentType")+"'";
			    
			    if(request.getParameter("hadminCollege")!=null&&request.getParameter("hadminCollege").length()!=0)
				       sqlstring=sqlstring+" and s.adminCollege='"+request.getParameter("hadminCollege")+"'";
			    
			    if(request.getParameter("hhomeTelephone")!=null&&request.getParameter("hhomeTelephone").length()!=0)
				       sqlstring=sqlstring+" and s.homeTelephone like '%"+request.getParameter("hhomeTelephone")+"%'";
			    
			    if(request.getParameter("hbirthday")!=null&&request.getParameter("hbirthday").length()!=0)
				       sqlstring=sqlstring+" and s.birthday like '%"+request.getParameter("hbirthday")+"%'";
			 	
			    if(orderby==null||orderby.length()==0)
	            	 sqlstring=sqlstring+" order by s.studentNo";
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
	                 sqlstring=sqlstring+" order by s.studentNo"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("gender"))
	                 sqlstring=sqlstring+" order by s.gender"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("idType"))
	                 sqlstring=sqlstring+" order by s.idType"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("idCard"))
	                 sqlstring=sqlstring+" order by s.idCard"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("department"))
	                 sqlstring=sqlstring+" order by s.department"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("majorin"))
	                 sqlstring=sqlstring+" order by s.majorin"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("nation"))
	                 sqlstring=sqlstring+" order by s.nation"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("nationality"))
	                 sqlstring=sqlstring+" order by s.nationality"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("fromProvince"))
	                 sqlstring=sqlstring+" order by s.fromProvince"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("polityBg"))
	                 sqlstring=sqlstring+" order by s.polityBg"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentType"))
	                 sqlstring=sqlstring+" order by s.studentType"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("cultureMode"))
	                 sqlstring=sqlstring+" order by s.cultureMode"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentChar"))
	                 sqlstring=sqlstring+" order by s.studentChar"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("adminCollege"))
	                 sqlstring=sqlstring+" order by s.adminCollege"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("birthday"))
	                 sqlstring=sqlstring+" order by s.birthday"+" "+odr;
	             else if(orderby!=null&&orderby.length()>0&&orderby.equals("homeTelephone"))
	                 sqlstring=sqlstring+" order by s.homeTelephone"+" "+odr;
						    
			 List stuinfoList=studentService.find(sqlstring);
			  
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 
				 if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName")){
	                	Comparator comp1 = new Comparator() { 
	       				 public int compare(Object o1, Object o2){ 
	       				 Map m1 = (Map)o1; 
	       				 Map m2 = (Map)o2; 
	       				 String columnName1 = "";
	       				 String columnName2 ="";
	       				 if(m1.get("stuName")!=null)
	       				     columnName1=(String)m1.get("stuName"); 
	       				 if(m2.get("stuName")!=null)
	      				     columnName2 = (String)m2.get("stuName");      				

	      				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
	      				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(columnName1);
	      				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(columnName2);
	                    return collator.compare(c1.getSourceString(),c2.getSourceString());
	       				 } 
	       				} ;
	       				Comparator comp2 = new Comparator() { 
	          				 public int compare(Object o1, Object o2){ 
	          				 Map m1 = (Map)o1; 
	          				 Map m2 = (Map)o2; 
	          				 String columnName1 = "";
		       				 String columnName2 ="";
		       				 if(m1.get("stuName")!=null)
		       				     columnName1=(String)m1.get("stuName"); 
		       				 if(m2.get("stuName")!=null)
		      				     columnName2 = (String)m2.get("stuName");
	          				
	          				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
	          				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(columnName1);
	          				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(columnName2);
	                        return collator.compare(c2.getSourceString(),c1.getSourceString());	          				 
	          				 } 
	          				} ;
	       			 if(odr.equals("asc"))	
	       		         Collections.sort(stuinfoList, comp1);
	       			 else
	       				 Collections.sort(stuinfoList, comp2);
	       		     
	                }
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuinfoList;
				 else if((Integer.parseInt(offset))<stuinfoList.size()||(Integer.parseInt(offset))==stuinfoList.size())
					 resultList=stuinfoList.subList((Integer.parseInt(offset)),stuinfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 ChangetoValue(resultList);
				 }
				 request.setAttribute("stuinfo",stuinfo);
				 request.setAttribute("stuinfolist",resultList);
				 request.setAttribute("listcount",new Integer(stuinfoList.size()));
				 request.setAttribute("order",order);
				 
if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 
	                  ChangetoValue(stuinfoList);
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/新生入学信息一览.xls");
						String	fileName="notfudanstulist.xls";
						// Create the Sheet with the name of the Table
						HSSFWorkbook wb = new HSSFWorkbook();
						
		                //设置显示的字体以及相关的样式
				 		HSSFFont font = wb.createFont();
				 		    font.setFontHeightInPoints((short)8);
				 		    //font.setFontName("宋体");
				 		    font.setItalic(false);
				 		    font.setStrikeout(false);
				 		   
				 		//设置标题栏单元格的样式
				 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
				 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				 		    cellHeadStyle.setBorderLeft((short)1);
				 		    cellHeadStyle.setBorderRight((short)1);
				 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				 		//设置数据行的字体以及以及相关的对齐方式
				 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
				 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellDataStyle.setFont(font);
						
						HSSFSheet sheet1 = wb.createSheet("Sheet1");
			 		    
						// Grab & populate the Column Names
						HSSFRow row = sheet1.createRow((short)0);
						
		               //Populate the first row of the spreadsheet with the column names
						List columnNames =new ArrayList();
																		
						columnNames.add(0,"学号");
						columnNames.add(1,"姓名");
						columnNames.add(2,"性别");
						columnNames.add(3,"录取院系");
						columnNames.add(4,"录取专业");						
						columnNames.add(5,"民族");
						columnNames.add(6,"国籍");
						columnNames.add(7,"生源地");
						columnNames.add(8,"证件类型");
						columnNames.add(9,"证件号码");
						columnNames.add(10,"培养层次");
						columnNames.add(11,"学生性质");						
						columnNames.add(12,"学生类别");
						columnNames.add(13,"政治面貌");
						columnNames.add(14,"生日");
						columnNames.add(15,"家庭电话");
						columnNames.add(16,"管理院系");
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = stuinfoList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)stuinfoList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentNo"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("stuName"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("genderName"));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("departmentName"));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("majorinName"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("nationName"));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("nationalityName"));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("fromProvinceName"));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("idTypeName"));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("idCard"));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("cultureModeName"));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentCharName"));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentTypeName"));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("polityBgName"));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("birthday"));
								
								ctitle=row.createCell((short)15);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("homeTelephone"));
								
								ctitle=row.createCell((short)16);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("adminCollegeName"));
								
								
								//System.out.println(columnData);
								currentCell++;

						}			
						// clean up resources
					   	//wb.write(fileOut);
				 	 	//fileOut.close();
						
						response.setContentType("application/x-msdownload");
						response.setHeader("Content-Disposition", "attachment;"
								+ " filename="
								+ new String(fileName.getBytes(), "ISO-8859-1"));

		                OutputStream os = response.getOutputStream();
		                wb.write(os);
				    /*-----------------------------------------------------------------------*/ 
					 
					 return null;
					 
				 }
				 else
			 		 return mapping.findForward("notfudanstulist");				 
			 }
			 
			 else{
				 request.setAttribute("msg","-1");
				 return mapping.findForward("notfudanstulist"); 
			 }
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public void ChangetoValue(List list){
		String[][] ar={{"1","男"},{"2","女"}};
		List departList=studentService.find("select new Map(d.deptCode as deptCode,d.deptName as deptName) from Department d");
		List polityList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
				+ "from Dictionary a where a.id.dictNo= 4 ");
		List majorList=studentService.getmajorList();		
		List provinceList=studentService.getfromProvinceList();
		List nationList=studentService.getnationList();
		List countryList=studentService.getcountryList();		
		List cultureList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
				+ "from Dictionary a where a.id.dictNo= 26 ");
		List stucharList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
				+ "from Dictionary a where a.id.dictNo= 27 ");
		List stutypeList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
				+ "from Dictionary a where a.id.dictNo= 15 ");
		List idtypeList=studentService.find("select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
				+ "from Dictionary a where a.id.dictNo= 29 ");
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("gender")!=null){
			     String mj=((String)n.get("gender")).trim();
			     for(int k=0;k<ar.length;k++){				 
				     String mj1=ar[k][0];
				     if(mj.equals(mj1)){
					     n.put("genderName",ar[k][1]);
					     break;
				     }
			     }
			 }
			 else
				 n.put("genderName","");
			 
			 if(n.get("adminCollege")!=null){
			     String mj=((String)n.get("adminCollege")).trim();
			     for(int k=0;k<departList.size();k++){
				     Map n1=(Map)departList.get(k);
				     String mj1=((String)n1.get("deptCode")).trim();
				     if(mj.equals(mj1)){
					     n.put("adminCollegeName",((String)n1.get("deptName")).trim());
					     break;
				     }
			     }
			 }
			 else
				 n.put("adminCollegeName","");
			 
			 if(n.get("polityBg")!=null){
				   String mj=((String)n.get("polityBg")).trim();
				   for(int k=0;k<polityList.size();k++){
					 Map n1=(Map)polityList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("polityBgName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("polityBgName","");
			 
			 if(n.get("department")!=null){
			     String mj=((String)n.get("department")).trim();
			     for(int k=0;k<departList.size();k++){
				     Map n1=(Map)departList.get(k);
				     String mj1=((String)n1.get("deptCode")).trim();
				     if(mj.equals(mj1)){
					     n.put("departmentName",((String)n1.get("deptName")).trim());
					     break;
				     }
			     }
			 }
			 else
				 n.put("departmentName","");
			 
			 if(n.get("majorin")!=null){
				   String mj=((String)n.get("majorin")).trim();
				   for(int k=0;k<majorList.size();k++){
					 Map n1=(Map)majorList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("majorinName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("majorinName","");
			 
			 if(n.get("fromProvince")!=null){
				   String mj=((String)n.get("fromProvince")).trim();
				   for(int k=0;k<provinceList.size();k++){
					 Map n1=(Map)provinceList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("fromProvinceName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("fromProvinceName","");
			 
			 if(n.get("nation")!=null){
				   String mj=((String)n.get("nation")).trim();
				   for(int k=0;k<nationList.size();k++){
					 Map n1=(Map)nationList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("nationName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("nationName","");
			 
			 if(n.get("nationality")!=null){
				   String mj=((String)n.get("nationality")).trim();
				   for(int k=0;k<countryList.size();k++){
					 Map n1=(Map)countryList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("nationalityName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("nationalityName","");
			 
			 if(n.get("cultureMode")!=null){
				   String mj=((String)n.get("cultureMode")).trim();
				   for(int k=0;k<cultureList.size();k++){
					 Map n1=(Map)cultureList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("cultureModeName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("cultureModeName","");
			 
			 if(n.get("studentChar")!=null){
				   String mj=((String)n.get("studentChar")).trim();
				   for(int k=0;k<stucharList.size();k++){
					 Map n1=(Map)stucharList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("studentCharName",((String)n1.get("dictCaption")).trim());					 
						 break;
					 }
				   }
				 }
				 else
					 n.put("studentCharName","");
			 
			 if(n.get("studentType")!=null){
				   String mj=((String)n.get("studentType")).trim();
				   for(int k=0;k<stutypeList.size();k++){
					 Map n1=(Map)stutypeList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("studentTypeName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("studentTypeName",""); 
			 
			 if(n.get("idType")!=null){
				   String mj=((String)n.get("idType")).trim();
				   for(int k=0;k<idtypeList.size();k++){
					 Map n1=(Map)idtypeList.get(k);
					 String mj1=((String)n1.get("dictValue")).trim();
					 if(mj.equals(mj1)){
						 n.put("idTypeName",((String)n1.get("dictCaption")).trim());
						 break;
					 }
				   }
				 }
				 else
					 n.put("idTypeName",""); 
		 }		
	}
	
}
