/**
 * 
 */
package org.king.checkinmanage.web.action;

/**
 * @author jackey
 *
 */
import java.io.OutputStream;
import java.sql.Timestamp;
import java.sql.Time;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;
import java.sql.Date;
import java.util.List;

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
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.utils.DateUtil;


/**
 * @author jackey
 *
 */
public class GzHealthAction extends BaseAction{
	
	
	private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
//体检结果
	
	public ActionForward findstuinfo_unhealth(ActionMapping mapping, ActionForm form,
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
					 		 
		            String sqlstring=null; 		            
		            	            
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.studentNo='"+request.getParameter("stuhealthinfo.studentNo")+"'";
		            	            
		            List stuinfoList=checkinmanageservice.find(sqlstring);
		 
		            if(stuinfoList!=null&&stuinfoList.size()!=0){
		            request.setAttribute("stuinfo",stuinfoList);
		            
                    sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo) from Stuhealthinfo ci where ci.studentNo='"+request.getParameter("stuhealthinfo.studentNo")+"'";
		            List resultList=checkinmanageservice.find(sqlstring);
		            if(resultList!=null&resultList.size()>0)
		                request.setAttribute("healthrecord",resultList);
		 	        System.out.println("find student success");
		            return mapping.findForward("unhealthlist");
		       }
		       else
			        return mapping.findForward("unhealthlist");
	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }

	   }
	
	public ActionForward unhealthlist(ActionMapping mapping, ActionForm form,
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
			 
			 List classList=getClassList();
			 if(classList!=null&&classList.size()>0)
				 request.setAttribute("classlist",classList);
			 
              //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				 				 
                 //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				
				List stucheckininfoList=new ArrayList();
				
				Studentmodel stuinfo=new Studentmodel();				
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));
				stuinfo.setStuName(request.getParameter("hstuName"));
				stuinfo.setMajorin(request.getParameter("hmajorin"));
				
				String classNo=request.getParameter("hclassNo");
				String collegeId=request.getParameter("hcollegeId");
				
				String ifUnhealthy=request.getParameter("hifUnhealthy");	                 
					 
					 String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,c.yxCollege.collegeId as collegeId,ci.ifUnhealthy as ifUnhealthy,ci.ifDeleted as ifDeleted,ci.creatorId as creatorId,ci.createTime as createTime,ci.updatorId as updatorId,ci.updateTime as updateTime,cki.ifCheckedin as ifCheckedin) from Stuhealthinfo ci,Stucheckininfo cki,Studentmodel s,Classmodel c where s.studentNo=ci.studentNo and cki.studentNo=ci.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
						 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
							 sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
									 
						 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
							 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
									
						 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
							 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
						 
						 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
							 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
						 
						 if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
							 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"'";
						 
						 if(request.getParameter("hifUnhealthy")!=null&&request.getParameter("hifUnhealthy").length()!=0)
							 sqlstring=sqlstring+" and ci.ifUnhealthy='"+request.getParameter("hifUnhealthy")+"'";
						 
						 sqlstring=sqlstring+" order by c.classNo,ci.studentNo";
						 
						 List unhealthList=checkinmanageservice.find(sqlstring);	
				
						 sqlstring="select new Map(c.classNo as classNo,m.managerName as managerName,m.contact as contact) from Classmodel c,Classmanager cm,Managermodel m,Managermanagerrole mr where cm.id.classId=c.classId and cm.id.managerId=m.managerId and mr.id.managerId=m.managerId and mr.id.roleId='21'";
		    	            
				         List managerinfoList=checkinmanageservice.find(sqlstring);	
				
			 if(unhealthList!=null&&unhealthList.size()!=0){//加入辅导员信息
				 for(int i=0;i<unhealthList.size();i++){
					 Map m=(Map)unhealthList.get(i);
					 String cno=((String)m.get("classNo")).trim();
					 if(managerinfoList!=null&&managerinfoList.size()>0){
						 for(int j=0;j<managerinfoList.size();j++){
							 Map n=(Map)managerinfoList.get(j);
							 String cno2=((String)n.get("classNo")).trim();
							 if(cno.equals(cno2)){
								 m.put("managerName",n.get("managerName"));
							     m.put("contact",n.get("contact"));
							 }
						 }
					 }
					 
					 m.put("collegeName","护理学院");							     
					
					 stucheckininfoList.add(m);
				 }
				 
				 ChangeMajorValue(stucheckininfoList);
				 ChangeGenderValue(stucheckininfoList);
				 ChangeHealthValue(stucheckininfoList);
				 
			 }
			 if(stucheckininfoList!=null&&stucheckininfoList.size()>0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
					 request.setAttribute("collegeId",collegeId);
					 request.setAttribute("ifUnhealthy",ifUnhealthy);
					 
				     request.setAttribute("unhealthlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
				 
				 
				 //System.out.println("list success");
				 
				 
				 return mapping.findForward("success");
			 }
			 else{
                    return mapping.findForward("success");
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
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
			Stuhealthinfo stuhealthinfo = new Stuhealthinfo();
        
		    try {			 
	      		      	 
		    	stuhealthinfo.setStudentNo(request.getParameter("studentNo"+ids[i]));
		    	stuhealthinfo.setEnrollNo(request.getParameter("enrollNo"+ids[i]));
		    	stuhealthinfo.setEnrollYear(request.getParameter("enrollYear"+ids[i]));
		    	stuhealthinfo.setIfUnhealthy(request.getParameter("updatestate"));
		    	stuhealthinfo.setIfDeleted(request.getParameter("ifDeleted"+ids[i]));	      	 
	      	    stuhealthinfo.setUpdatorId(request.getParameter("updatorId"+ids[i]));
	      	    stuhealthinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      		      	 
	            stuhealthinfo.setId(ids[i]);

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stuhealthinfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 flag=true;
			 
		    } catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			request.setAttribute("msg","1");
			flag=false;
			return unhealthlist(mapping, form, request, response);
		    }
		}
		if(flag)
		    return mapping.findForward("unhealthlist");
		else{
			request.setAttribute("msg","1");
		    return unhealthlist(mapping, form, request, response);
		}

	}
	
	public ActionForward addunhealth(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		Stuhealthinfo stuhealthinfo = (Stuhealthinfo)aform.get("stuhealthinfo");
        
		try {
			
	      	 stuhealthinfo.setCreatorId(request.getParameter("stuhealthinfo.creatorId"));
             stuhealthinfo.setCreateTime(new Timestamp(System.currentTimeMillis()));
	      	 stuhealthinfo.setUpdatorId(request.getParameter("stuhealthinfo.updatorId"));
	      	 stuhealthinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.save(stuhealthinfo);
			 System.out.println("update success");
			 return mapping.findForward("unhealthlist");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward cancelunhealth(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		Stuhealthinfo stuhealthinfo = (Stuhealthinfo)aform.get("stuhealthinfo");
        
		try {
			
	      	 stuhealthinfo.setEnrollNo(request.getParameter("enrollNo"+request.getParameter("updateid")));
	      	 stuhealthinfo.setStudentNo(request.getParameter("studentNo"+request.getParameter("updateid")));
	      	 stuhealthinfo.setEnrollYear(request.getParameter("enrollYear"+request.getParameter("updateid")));
	      	 stuhealthinfo.setIfUnhealthy(request.getParameter("ifUnhealthy"+request.getParameter("updateid")));
			 stuhealthinfo.setIfDeleted(request.getParameter("ifDeleted"+request.getParameter("updateid")));
	      	 stuhealthinfo.setCreatorId(request.getParameter("creatorId"+request.getParameter("updateid")));
             stuhealthinfo.setCreateTime(new Timestamp(Integer.parseInt(request.getParameter("createTime"+request.getParameter("updateid")).substring(0,4))-1900,Integer.parseInt(request.getParameter("createTime"+request.getParameter("updateid")).substring(5,7)),Integer.parseInt(request.getParameter("createTime"+request.getParameter("updateid")).substring(8,10)),Integer.parseInt(request.getParameter("createTime"+request.getParameter("updateid")).substring(11,13)),Integer.parseInt(request.getParameter("createTime"+request.getParameter("updateid")).substring(14,16)),Integer.parseInt(request.getParameter("createTime"+request.getParameter("updateid")).substring(17,19)),0));
	      	 stuhealthinfo.setUpdatorId(request.getParameter("updatorId"+request.getParameter("updateid")));
	      	 stuhealthinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      	 
	      	 stuhealthinfo.setId(request.getParameter("updateid"));
  
		   
			if(checkinmanageservice==null)
				 System.out.println("service is null");
		    checkinmanageservice.delete(stuhealthinfo);
			System.out.println("delete success");			     
		    } catch (Exception e) {
			     e.printStackTrace();
			     System.out.println("delete error");
			     return mapping.findForward("faile");
		    }
		    
		return mapping.findForward("unhealthlist");
    }
	
	public ActionForward unhealthviewlist(ActionMapping mapping, ActionForm form,
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
			 
			 List classList=getClassList();
			 if(classList!=null&&classList.size()>0)
				 request.setAttribute("classlist",classList);
			 
              //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
								
                 //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				
				List stucheckininfoList=new ArrayList();
				
				Studentmodel stuinfo=new Studentmodel();				
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));
				stuinfo.setStuName(request.getParameter("hstuName"));
				stuinfo.setMajorin(request.getParameter("hmajorin"));
				
				String classNo=request.getParameter("hclassNo");
				String collegeId=request.getParameter("hcollegeId");
				
				String ifUnhealthy=request.getParameter("hifUnhealthy");
				
				String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,c.yxCollege.collegeId as collegeId,ci.ifUnhealthy as ifUnhealthy,ci.ifDeleted as ifDeleted,ci.creatorId as creatorId,ci.createTime as createTime,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stuhealthinfo ci,Studentmodel s,Classmodel c where s.studentNo=ci.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
				 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
					 sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
							 
				 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
					 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
							
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
				 
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
				 
				 if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"'";
				 
				 if(request.getParameter("hifUnhealthy")!=null&&request.getParameter("hifUnhealthy").length()!=0)
					 sqlstring=sqlstring+" and ci.ifUnhealthy='"+request.getParameter("hifUnhealthy")+"'";
				 
				 sqlstring=sqlstring+" order by c.yxCollege.collegeId,c.classNo,ci.studentNo";
				 
				 stucheckininfoList=checkinmanageservice.find(sqlstring);					
				
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 List rList=new ArrayList();
				 for(int i=0;i<stucheckininfoList.size();i++){//加入书院信息
					 Map m=(Map)stucheckininfoList.get(i);					 
					 m.put("collegeName","护理学院");					 
					 rList.add(m);
				 }
				 
				 ChangeMajorValue(rList);
				 ChangeGenderValue(rList);
				 ChangeHealthValue(rList);
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=rList;
				 else if((Integer.parseInt(offset))<rList.size()||(Integer.parseInt(offset))==rList.size())
					 resultList=rList.subList((Integer.parseInt(offset)),rList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
					 request.setAttribute("collegeId",collegeId);
					 request.setAttribute("ifUnhealthy",ifUnhealthy);
					 
				     request.setAttribute("unhealthlist",resultList);
				     request.setAttribute("listcount",new Integer(rList.size()));
				 }				 
				 
				 //System.out.println("list success");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 				 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/新生入学信息一览.xls");
						String	fileName="healthresult.xls";
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
												
						columnNames.add(0,"班级");
						columnNames.add(1,"学号");
						columnNames.add(2,"姓名");
						columnNames.add(3,"性别");						
						columnNames.add(4,"体检结果");
						
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = rList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)rList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("stuName"));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("genderName"));
																
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("ifUnhealthyName"));								
								
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
				    return mapping.findForward("success2");
			 }
			 else{
				    request.setAttribute("msg","0");
                    return mapping.findForward("success2");
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	//取复旦学院的所有书院
	public List getCollegeList(){
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 String sqlstring="select new Map(col.collegeId as id,col.collegeName as collegeName) from Collegemodel col order by col.collegeNo";
			 List collegeList=checkinmanageservice.find(sqlstring);
			 
			 if(collegeList!=null&&collegeList.size()>0)
				 return collegeList;
			 else
				 return null;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
	
	}
	//取书院和班级列表
	public String[][] getColandCls(){
		
		   List rList=new ArrayList();			   
		   String sqlstring = "";	
		   String[][] result;
		   
		   try {
				 if(checkinmanageservice==null)
					 System.out.println("service is null");		     
		     
		     sqlstring="select new Map(cls.classNo as classNo,col.collegeId as collegeId) from Collegemodel col,Classmodel cls where cls.yxCollege.collegeId=col.collegeId order by col.collegeNo";
		     
		     rList=checkinmanageservice.find(sqlstring);
		     if(rList!=null&&rList.size()>0){
		    	 result=new String[rList.size()][2];
		         for(int i=0;i<rList.size();i++){
		             result[i][0] =(String)(((Map)rList.get(i)).get("classNo"));
		             result[i][1] = (String)(((Map)rList.get(i)).get("collegeId"));
		         } 		        
		         return result;
		     }
		     else
		    	 return null;

		   }catch (Exception e){
		     e.printStackTrace();
		     return null;
		   }

		 }
	
	public void ChangeGenderValue(List list){
		String[][] ar={{"1","男"},{"2","女"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("gender")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("genderName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeMajorValue(List list){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("majorin")!=null){
			   String mj=((String)n.get("majorin")).trim();
			   for(int k=0;k<majorList.size();k++){
				 Map n1=(Map)majorList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("majorinName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("majorinName","");
		 }
		
	}
	
	public void ChangeHealthValue(List list){
		String[][] ar={{"0",""},{"1","体检合格"},{"2","需复检"},{"3","复检合格"}};		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);			 
			 String mj=((String)n.get("ifUnhealthy")).trim();
			 
			 for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("ifUnhealthyName",ar[k][1]);
				   }
			 }
			 
		 }//for
		
	}
	
	public List getmajorList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
		return majorList;
	}
	
//	取护理学院的所有班级
	public List getClassList(){
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 String sqlstring="select new Map(col.classId as id,col.classNo as classNo,col.className as className) from Classmodel col where col.yxCollege.yxSchool.schoolId='0002' and col.curYear='"+DateUtil.getNow("yyyy")+"' order by col.classNo";
			 List classList=checkinmanageservice.find(sqlstring);
			 
			 if(classList!=null&&classList.size()>0)
				 return classList;
			 else
				 return null;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
	
	}
}
