/**
 * 
 */
package org.king.yangong.checkinmanage.web.action;

import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Date;
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
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.yangong.checkinmanage.service.YgCheckinmanageService;

import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.service.YxGraduateService;

/**
 * @author jackey
 *
 */
public class StufeeinfoAction extends BaseAction{
	private YxGraduateService yxGraduateService;
    private YgCheckinmanageService ygCheckinmanageService;
	
	public void setYgCheckinmanageService(YgCheckinmanageService ygCheckinmanageService) {
		this.ygCheckinmanageService = ygCheckinmanageService;
	}
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
    //�鿴�����ɷ���Ϣ    
    public ActionForward view(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
    	HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }

	        ActionMessages errors = new ActionMessages();
	        			
	          try {
		            if(checkinmanageservice==null)
		            	 System.out.println("service is null");		            
                  
	                //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList); 
					 		 
		            String sqlstring=null;		            	            
		            
		            //����������Ϣ
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.studentNo='"+request.getParameter("updateid")+"'";
		            	            
		            List stuinfoList=checkinmanageservice.find(sqlstring);
		            
		            //����ѧ����Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='01' and sf.studentNo='"+request.getParameter("updateid")+"'";
		            
		            List tuitionList=checkinmanageservice.find(sqlstring);
		            
		            //����ס�޷���Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='02' and sf.studentNo='"+request.getParameter("updateid")+"'";
		            
		            List dormfeeList=checkinmanageservice.find(sqlstring);
		            
                    //�����鼮����Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='03' and sf.studentNo='"+request.getParameter("updateid")+"'";
		            
		            List bookfeeList=checkinmanageservice.find(sqlstring);
		          
		            if(tuitionList!=null&&tuitionList.size()>0)
		            	request.setAttribute("tuitionlist",tuitionList);
		            if(dormfeeList!=null&&dormfeeList.size()>0)
		            	request.setAttribute("dormfeelist",dormfeeList);
		            if(bookfeeList!=null&&bookfeeList.size()>0)
		            	request.setAttribute("bookfeelist",bookfeeList);
		            
		          if(stuinfoList!=null&&stuinfoList.size()!=0){
		            request.setAttribute("stuinfolist",stuinfoList);
		 	        System.out.println("find student info success");
		            return mapping.findForward("stufeeview");
		          }
		          else
			        return mapping.findForward("stufeeview");
	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }
	}
    
    //�����鿴�ɷ���Ϣ    
    public ActionForward stuview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
    	HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }

	        ActionMessages errors = new ActionMessages();
	        			
	          try {
		            if(checkinmanageservice==null)
		            	 System.out.println("service is null");		
		            
		            Account freshmen=(Account)session.getAttribute("accountPerson");
		            
		            String id=freshmen.getPerson().getPersonCode();	//��ȡ��¼������ѧ��                 
					 		 
		            String sqlstring=null;		            	            
		            //Ժϵ
		            List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
					if(collegeList!=null&&collegeList.size()>0)
						request.setAttribute("collegelist",collegeList);
	                //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=28 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList); 	            	            
		            
		            //����������Ϣ
		            sqlstring="select new Map(s.id as id,s.graduateNo as studentNo,s.graduateName as stuName,s.sex as gender," +
		            		  "s.speciality as majorin,s.curCollege as curCollege,s.requestAvailable as requestAvailable," +
		            		  "s.residentNeed as residentNeed,s.dormitoryId as dormitoryid) " +
		            		  "from YxGraduate s " +
		            		  "where s.graduateNo='"+id+"' and s.enrollYear='"+DateUtil.getNow("yyyy")+"'";
		            	            
		            List stuinfoList=checkinmanageservice.find(sqlstring);
		            
		            //
//		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,d.area as area ,d.location as location,d.dormitory as dorm,d.roomNumber as room) from YxGraduate s,Dormitorymodel d where s.dormitoryId=d.dormitoryId and s.gradutateNo='"+id+"' s.enrollYear='2007'";
//    	            
//		            List dorminfoList=checkinmanageservice.find(sqlstring);	
		            
		            
		            //����ס�޷���Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='02' and sf.studentNo='"+id+"'";
		            
		            List dormfeeList=checkinmanageservice.find(sqlstring);
		            
		            if(dormfeeList!=null&&dormfeeList.size()>0)
		            	request.setAttribute("dormfeelist",dormfeeList);

		          if(stuinfoList!=null&&stuinfoList.size()!=0){
		        	String requestAvailable = (String)((Map)stuinfoList.get(0)).get("requestAvailable");
		        	String residentNeed = (String)((Map)stuinfoList.get(0)).get("residentNeed");
		        	request.setAttribute("requestAvailable", requestAvailable);
		        	request.setAttribute("residentNeed", residentNeed);
		            request.setAttribute("stuinfolist",stuinfoList);
		 	        System.out.println("find student info success");
		            return mapping.findForward("feeinfoview");
		          }
		          else
			        return mapping.findForward("feeinfoview");

	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }
	}
    
    public ActionForward tuitionnotpaylist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		List s1=new ArrayList();
 		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
                //��ʼҳ
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				
				List collegeList=getCollegeList();
				 if(collegeList!=null&&collegeList.size()>0)
					 request.setAttribute("collegelist",collegeList);
				 
				 String[][] colandclsList=getColandCls();
				 if(colandclsList!=null&&colandclsList.length>0){
					 request.setAttribute("classlist",colandclsList);
					 //request.setAttribute("listlength",new Integer(colandclsList.length));
				 }
                //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
					
					Studentmodel stuinfo=new Studentmodel();				
					stuinfo.setStudentNo(request.getParameter("hstudentNo"));
					stuinfo.setStuName(request.getParameter("hstuName"));					
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
			
			 String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,c.classNo as classNo,col.collegeId as collegeId,col.collegeName as collegeName) from Studentmodel s,Classmodel c,Collegemodel col where s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
			 	
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";			 
			 
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
			 
			 if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
				 sqlstring=sqlstring+" and col.collegeId='"+request.getParameter("hcollegeId")+"'";
			 
			 sqlstring=sqlstring+" order by s.studentNo";
			 
			 List stuinfoList=checkinmanageservice.find(sqlstring);
			 
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 String stuNos="";
				 for(int i=0;i<stuinfoList.size();i++){
					 Map stum=(Map)stuinfoList.get(i);
					 String stuNo=(String)stum.get("studentNo");
					 stuNos=stuNos+"'"+stuNo+"'"+",";
				 }
				 if(stuNos.length()>0)
					 stuNos=stuNos.substring(0,stuNos.length()-1);
				 
               //�����ɷ���Ϣ���ѯ,ѧ���ѽ�������
			   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='01' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay) and ci.studentNo in ("+stuNos+")";
			 
		       List tuitionList=checkinmanageservice.find(sqlstring);
		       
               // �����ɷ���Ϣ���ѯ,ѧ��δ��������
			   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='01' and (ci.exactPay<ci.shouldPay) and ci.studentNo in ("+stuNos+")";
			 
		       List tuitionnotpayList=checkinmanageservice.find(sqlstring);
		       		      			 
               for(int i=0;i<stuinfoList.size();i++){
            	 boolean flag=false;
				 Map m=(Map)stuinfoList.get(i);
				 String sno=((String)m.get("studentNo")).trim();
			     
				 /*
			     if(tuitionList!=null&&tuitionList.size()>0){
				     int j=0;
				     for(j=0;j<tuitionList.size();j++){
					     Map uhm=(Map)tuitionList.get(j);
					     String stuno=((String)uhm.get("studentNo")).trim();					     
					     if(stuno.equals(sno)){					    	 
					    	 m.put("tuitionpayed","1");					    	 	
					    	 m.put("updateTime",uhm.get("updateTime"));
						     break;
					     }					     
				     }                     
			    }
			    */
			    if(tuitionnotpayList!=null&&tuitionnotpayList.size()>0){
				     int j=0;
				     for(j=0;j<tuitionnotpayList.size();j++){
					     Map uhm=(Map)tuitionnotpayList.get(j);
					     String stuno=((String)uhm.get("studentNo")).trim();					     
					     if(stuno.equals(sno)){					    	 
					    	 m.put("tuitionpayed","0");					    	 	
					    	 m.put("updateTime",uhm.get("updateTime"));
					    	 s1.add(m);
					    	 flag=true;
						     break;
					     }					     
				     }                     
			    }
			    if(!flag){//�ѽ�ѧ�ѱ���û�ҵ�
			    
			    	if(tuitionList!=null&&tuitionList.size()>0){
					     int j=0;
					     for(j=0;j<tuitionList.size();j++){
						     Map uhm=(Map)tuitionList.get(j);
						     String stuno=((String)uhm.get("studentNo")).trim();					     
						     if(stuno.equals(sno)){					    	 
						    	 m.put("tuitionpayed","1");					    	 	
						    	 m.put("updateTime",uhm.get("updateTime"));
						    	 flag=true;
							     break;
						     }					     
					     }                     
				    }			    	
			       
			    }
			    if(!flag){//δ��ѧ�ѱ���û�ҵ�
			    	m.put("tuitionpayed","0");
			        s1.add(m);
			    }
			  }
			 
			 }
			 if(s1!=null&&s1.size()!=0){
				 ChangeDepartmentValue(s1);
				 List resultList=new ArrayList();
                 //��ʼҳ����
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
					 request.setAttribute("collegeId",collegeId);
				     request.setAttribute("tuitionnotpaylist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				 }                 
				 
               if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 
					 ChangeMajorValue(s1);
					 ChangeGenderValue(s1);					 				 
					 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/������ѧ��Ϣһ��.xls");
						String	fileName="tuitionresult.xls";
						// Create the Sheet with the name of the Table
						HSSFWorkbook wb = new HSSFWorkbook();
						
		                //������ʾ�������Լ���ص���ʽ
				 		HSSFFont font = wb.createFont();
				 		    font.setFontHeightInPoints((short)8);
				 		    //font.setFontName("����");
				 		    font.setItalic(false);
				 		    font.setStrikeout(false);
				 		   
				 		//���ñ�������Ԫ�����ʽ
				 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
				 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				 		    cellHeadStyle.setBorderLeft((short)1);
				 		    cellHeadStyle.setBorderRight((short)1);
				 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				 		//���������е������Լ��Լ���صĶ��뷽ʽ
				 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
				 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellDataStyle.setFont(font);
						
						HSSFSheet sheet1 = wb.createSheet("Sheet1");
			 		    
						// Grab & populate the Column Names
						HSSFRow row = sheet1.createRow((short)0);
						
		               //Populate the first row of the spreadsheet with the column names
						List columnNames =new ArrayList();
																		
						columnNames.add(0,"ѧ��");
						columnNames.add(1,"����");
						columnNames.add(2,"�Ա�");
						columnNames.add(3,"¼ȡԺϵ");
						columnNames.add(4,"¼ȡרҵ");						
						columnNames.add(5,"�༶");
						columnNames.add(6,"��Ժ");
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = s1.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)s1.get(i);
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
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
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
				     return mapping.findForward("tuitionnotpaylist");
			 }
			 else
				 return mapping.findForward("tuitionnotpaylist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
    
    public ActionForward dormfeenotpaylist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		
		List dormdeptli=ygCheckinmanageService.find("select a.tabSsDept.name from TabSsManager a where a.stuNo='"+operator+"' and a.inOffice=1 ");
		if(dormdeptli!=null&&dormdeptli.size()>0){
			String dormdeptname=(String)dormdeptli.get(0);
			if(dormdeptname.equals("����"))
			    request.setAttribute("dormdeptname","����У��-"+dormdeptname);
			else if(dormdeptname.equals("��Է"))
				request.setAttribute("dormdeptname","����У��-"+dormdeptname);
		}
		ActionMessages errors = new ActionMessages();
		List s1=new ArrayList();
 		// ���ݿ���֤
		try {
			 if(ygCheckinmanageService==null)
				 System.out.println("service is null");
			 
                //��ʼҳ
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				
				List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
				 if(collegeList!=null&&collegeList.size()>0)
					 request.setAttribute("collegelist",collegeList); //Ժϵ�б�
				 
				 String[][] colandclsList=getColandCls();
				 if(colandclsList!=null&&colandclsList.length>0){
					 request.setAttribute("classlist",colandclsList);
					 //request.setAttribute("listlength",new Integer(colandclsList.length));
				 }
				 

               //רҵ
					List majorList=ygCheckinmanageService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=28 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
					
					YxGraduate stuinfo=new YxGraduate();				
					stuinfo.setGraduateNo(request.getParameter("hstudentNo"));
					stuinfo.setGraduateName(request.getParameter("hstuName"));
					stuinfo.setSex(request.getParameter("hgender"));
					stuinfo.setStudentType(request.getParameter("hstudentType"));
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
										
					String sqlstring="select new Map(s.id as id,s.graduateNo as graduateNo,s.graduateName as graduateName,s.sex as gender," +
							"s.curCollege as curCollege,s.speciality as speciality,s.studentType as studentType," +
							"s.updateDate as updateDate,s.IFPAYDORMFEE as dormfeepayed,s.distriction as distriction) " +
							"from YxGraduate s,Department d,TabSsManager a " +
							"where s.enrollYear='"+DateUtil.getNow("yyyy")+"'"+
							" and a.tabSsDept.id = s.distriction and s.curCollege=d.deptCode and s.dormitoryId is not null and s.dormitoryId<>'' and a.stuNo='"+operator+"' ";
				 	
					 if(request.getParameter("studentNo")!=null&&request.getParameter("studentNo").length()!=0)
						 sqlstring=sqlstring+" and s.graduateNo like '%"+request.getParameter("studentNo")+"%'";
								 
					 if(request.getParameter("stuName")!=null&&request.getParameter("stuName").length()!=0)
						 sqlstring=sqlstring+" and s.graduateName like '%"+request.getParameter("stuName")+"%'";
					 
					 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
						 sqlstring=sqlstring+" and s.sex='"+request.getParameter("hgender")+"'";
					 
					 if(request.getParameter("hstudentType")!=null&&request.getParameter("hstudentType").length()!=0)
						 sqlstring=sqlstring+" and s.studentType='"+request.getParameter("hstudentType")+"'";
					 
					 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
						 sqlstring=sqlstring+" and s.speciality='"+request.getParameter("hclassNo")+"'";
					 
					 if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
						 sqlstring=sqlstring+" and s.curCollege='"+request.getParameter("hcollegeId")+"'";
					 
					 sqlstring=sqlstring+" order by d.gsort,s.speciality,s.studentType,s.graduateNo";					 
					 List stuinfoList=ygCheckinmanageService.find(sqlstring);
				 
				 for(int i=0;i<stuinfoList.size();i++){
					 Map m = (Map)stuinfoList.get(i);
					 for(int j=0;j<collegeList.size();j++){
						 Department dp = (Department)collegeList.get(j);
						 if(((String)m.get("curCollege")).equals(dp.getDeptCode())){
							 m.put("curCollege", dp.getDeptName());
							 break;
						 }
					 }
				 }
				 for(int i=0;i<stuinfoList.size();i++){
					 Map m = (Map)stuinfoList.get(i);
					 for(int j=0;j<majorList.size();j++){
						 Map dp = (Map)majorList.get(j);
						 if(((String)m.get("speciality")).equals(dp.get("dictValue"))){
							 m.put("speciality", dp.get("dictCaption"));
							 break;
						 }
					 }
					 if(m.get("studentType")!=null){
						 String st=((String)m.get("studentType")).trim();
						 m.put("studentType",st);
					 }
				 }	 
				 if(stuinfoList!=null&&stuinfoList.size()!=0){
					 
					 String stuNos="";
					 for(int i=0;i<stuinfoList.size();i++){
						 Map stum=(Map)stuinfoList.get(i);
						 String stuNo=(String)stum.get("graduateNo");
						 stuNos=stuNos+"'"+stuNo+"'"+",";
					 }
					 if(stuNos.length()>0)
						 stuNos=stuNos.substring(0,stuNos.length()-1);
					 
	               //�����ɷ���Ϣ���ѯ,ס�޷��ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List tuitionList=ygCheckinmanageService.find(sqlstring);
			       
                   //�����ɷ���Ϣ���ѯ,ס�޷�δ��������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and (ci.exactPay<ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List tuitionnotpayList=ygCheckinmanageService.find(sqlstring);
				 
	               for(int i=0;i<stuinfoList.size();i++){
	            	 boolean flag=false;
					 Map m=(Map)stuinfoList.get(i);
					 String sno=((String)m.get("graduateNo")).trim();
				
					 if(tuitionnotpayList!=null&&tuitionnotpayList.size()>0){
					     int j=0;
					     for(j=0;j<tuitionnotpayList.size();j++){
						     Map uhm=(Map)tuitionnotpayList.get(j);
						     String stuno=((String)uhm.get("studentNo")).trim();
						     long sPay = ((Long)uhm.get("shouldPay")).longValue();
						     long ePay = ((Long)uhm.get("exactPay")).longValue();
						     if(stuno.equals(sno)){					    	 
						    	 m.put("dormfeepayed","0");
						    	 m.put("shouldPay", (new Long(sPay-ePay)).toString());
						    	 m.put("updateTime",uhm.get("updateTime"));
						    	 s1.add(m);
						    	 flag=true;
							     break;
						     }					     
					     }                     
				    }
				    if(!flag){
				    	//δ��ס�޷ѱ���û�ҵ�				    
				    	if(tuitionList!=null&&tuitionList.size()>0){
						     int j=0;
						     for(j=0;j<tuitionList.size();j++){
							     Map uhm=(Map)tuitionList.get(j);
							     String stuno=((String)uhm.get("studentNo")).trim();					     
							     if(stuno.equals(sno)){					    	 
							    	 m.put("dormfeepayed","1");								    	 
							    	 m.put("updateTime",uhm.get("updateTime"));
							    	 flag=true;
								     break;
							     }					     
						     }                     
					    }			    	
				       
				    }
				    if(!flag){
				    	//�ѽ�ס�޷ѱ���û�ҵ�
				    	m.put("dormfeepayed","0");
				    	m.put("shouldPay","");
				        s1.add(m);
				    }
				  }			 
				 }
			
			 if(s1!=null&&s1.size()!=0){
				 List resultList=new ArrayList();
                 //��ʼҳ����
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
					 request.setAttribute("collegeId",collegeId);
				     request.setAttribute("dormfeenotpaylist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				 }
				 
if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 
					 ChangeMajorValue(s1);
					 ChangeGenderValue(s1);					 
					 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/������ѧ��Ϣһ��.xls");
						String	fileName="dormfeeresult.xls";
						// Create the Sheet with the name of the Table
						HSSFWorkbook wb = new HSSFWorkbook();
						
		                //������ʾ�������Լ���ص���ʽ
				 		HSSFFont font = wb.createFont();
				 		    font.setFontHeightInPoints((short)8);
				 		    //font.setFontName("����");
				 		    font.setItalic(false);
				 		    font.setStrikeout(false);
				 		   
				 		//���ñ�������Ԫ�����ʽ
				 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
				 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				 		    cellHeadStyle.setBorderLeft((short)1);
				 		    cellHeadStyle.setBorderRight((short)1);
				 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				 		//���������е������Լ��Լ���صĶ��뷽ʽ
				 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
				 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellDataStyle.setFont(font);
						
						HSSFSheet sheet1 = wb.createSheet("Sheet1");
			 		    
						// Grab & populate the Column Names
						HSSFRow row = sheet1.createRow((short)0);
						
		               //Populate the first row of the spreadsheet with the column names
						List columnNames =new ArrayList();
																		
						columnNames.add(0,"ѧ��");
						columnNames.add(1,"����");						
						columnNames.add(2,"�Ա�");
						columnNames.add(3,"Ժϵ");
						columnNames.add(4,"רҵ");
						columnNames.add(5,"ѧ�����");
						columnNames.add(6,"Ӧ�ɽ��");
						columnNames.add(7,"��������");					
												
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = s1.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)s1.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("graduateNo"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("graduateName"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								if(((String)tableData.get("gender")).equals("1")){
									ctitle.setCellValue("��");
								}else{
									ctitle.setCellValue("Ů");
								}
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								
								ctitle.setCellValue((String)tableData.get("curCollege"));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("speciality"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentTypeName"));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("shouldPay"));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								if(tableData.get("updateTime")!=null&&!"".equals(((Date)tableData.get("updateTime")).toString())){
									ctitle.setCellValue(((Date)tableData.get("updateTime")).toString().substring(0,10));
								}else{
									ctitle.setCellValue("");
								}
								
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
				     return mapping.findForward("ygdormfeenotpaylist");
			 }
			 else
				 return mapping.findForward("ygdormfeenotpaylist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
    
    public ActionForward bookfeenotpaylist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		List s1=new ArrayList();
 		// ���ݿ���֤
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
                //��ʼҳ
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 			
				List collegeList=getCollegeList();
				 if(collegeList!=null&&collegeList.size()>0)
					 request.setAttribute("collegelist",collegeList);
				 
				 String[][] colandclsList=getColandCls();
				 if(colandclsList!=null&&colandclsList.length>0){
					 request.setAttribute("classlist",colandclsList);
					 //request.setAttribute("listlength",new Integer(colandclsList.length));
				 }
              //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
					
					Studentmodel stuinfo=new Studentmodel();				
					stuinfo.setStudentNo(request.getParameter("hstudentNo"));
					stuinfo.setStuName(request.getParameter("hstuName"));					
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
					
					
					String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,col.collegeId as collegeId,col.collegeName as collegeName) from Studentmodel s,Classmodel c,Collegemodel col where s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
				 	
					 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
						 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
								 
					 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
						 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";			 
					 
					 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
						 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
					 
					 if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
						 sqlstring=sqlstring+" and col.collegeId='"+request.getParameter("hcollegeId")+"'";
					 
					 sqlstring=sqlstring+" order by col.collegeId,c.classNo,s.studentNo";
					 
					 List stuinfoList=checkinmanageservice.find(sqlstring);
					 
				 if(stuinfoList!=null&&stuinfoList.size()!=0){
					 
	               //�����ɷ���Ϣ���ѯ,�鼮���ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='03' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay)";
				 
			       List tuitionList=checkinmanageservice.find(sqlstring); 
			       
                   //�����ɷ���Ϣ���ѯ,�鼮���ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='03' and (ci.exactPay<ci.shouldPay)";
				 
			       List tuitionnotpayList=checkinmanageservice.find(sqlstring);
				 
	               for(int i=0;i<stuinfoList.size();i++){
	            	 boolean flag=false;
					 Map m=(Map)stuinfoList.get(i);
					 String sno=((String)m.get("studentNo")).trim();
				
					 if(tuitionnotpayList!=null&&tuitionnotpayList.size()>0){
					     int j=0;
					     for(j=0;j<tuitionnotpayList.size();j++){
						     Map uhm=(Map)tuitionnotpayList.get(j);
						     String stuno=((String)uhm.get("studentNo")).trim();					     
						     if(stuno.equals(sno)){					    	 
						    	 m.put("bookfeepayed","0");					    	 	
						    	 m.put("updateTime",uhm.get("updateTime"));
						    	 s1.add(m);
						    	 flag=true;
							     break;
						     }					     
					     }                     
				    }
				    if(!flag){//�ѽ�ѧ�ѱ�û�ҵ�
				    
				    	if(tuitionList!=null&&tuitionList.size()>0){
						     int j=0;
						     for(j=0;j<tuitionList.size();j++){
							     Map uhm=(Map)tuitionList.get(j);
							     String stuno=((String)uhm.get("studentNo")).trim();					     
							     if(stuno.equals(sno)){					    	 
							    	 m.put("bookfeepayed","1");					    	 	
							    	 m.put("updateTime",uhm.get("updateTime"));
							    	 flag=true;
								     break;
							     }					     
						     }                     
					    }			    	
				       
				    }
				    if(!flag){//δ��ѧ�ѱ�û�ҵ�
				    	m.put("bookfeepayed","0");
				        s1.add(m);
				    }
				 			 
				    
				  }
				 
				 }
			
			 if(s1!=null&&s1.size()!=0){
				 List resultList=new ArrayList();
                 //��ʼҳ����
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
					 request.setAttribute("collegeId",collegeId);
				     request.setAttribute("bookfeenotpaylist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				 }
				 
if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 
					 ChangeMajorValue(s1);
					 ChangeGenderValue(s1);					 				 
					 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/������ѧ��Ϣһ��.xls");
						String	fileName="bookfeeresult.xls";
						// Create the Sheet with the name of the Table
						HSSFWorkbook wb = new HSSFWorkbook();
						
		                //������ʾ�������Լ���ص���ʽ
				 		HSSFFont font = wb.createFont();
				 		    font.setFontHeightInPoints((short)8);
				 		    //font.setFontName("����");
				 		    font.setItalic(false);
				 		    font.setStrikeout(false);
				 		   
				 		//���ñ�������Ԫ�����ʽ
				 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
				 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				 		    cellHeadStyle.setBorderLeft((short)1);
				 		    cellHeadStyle.setBorderRight((short)1);
				 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				 		//���������е������Լ��Լ���صĶ��뷽ʽ
				 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
				 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellDataStyle.setFont(font);
						
						HSSFSheet sheet1 = wb.createSheet("Sheet1");
			 		    
						// Grab & populate the Column Names
						HSSFRow row = sheet1.createRow((short)0);
						
		               //Populate the first row of the spreadsheet with the column names
						List columnNames =new ArrayList();
																		
						columnNames.add(0,"��Ժ");
						columnNames.add(1,"�༶");						
						columnNames.add(2,"ѧ��");
						columnNames.add(3,"����");
						columnNames.add(4,"�Ա�");						
						columnNames.add(5,"רҵ");						
												
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = s1.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)s1.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentNo"));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("stuName"));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("genderName"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("majorinName"));
							
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
				     return mapping.findForward("bookfeenotpaylist");
			 }
			 else
				 return mapping.findForward("bookfeenotpaylist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
    
//  ����ѧԺ����Ӧ��ѧ�ѡ�ס�޷ѡ��鼮��
    public ActionForward stufeelist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		List s1=new ArrayList();
		List sub1=new ArrayList();
 		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
                //��ʼҳ
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				
				List collegeList=getCollegeList();
				 if(collegeList!=null&&collegeList.size()>0)
					 request.setAttribute("collegelist",collegeList);
				 
				 String[][] colandclsList=getColandCls();
				 if(colandclsList!=null&&colandclsList.length>0){
					 request.setAttribute("classlist",colandclsList);
					 //request.setAttribute("listlength",new Integer(colandclsList.length));
				 }
                //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
					
					Studentmodel stuinfo=new Studentmodel();				
					stuinfo.setStudentNo(request.getParameter("hstudentNo"));
					stuinfo.setStuName(request.getParameter("hstuName"));					
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
			
			 //String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,c.yxCollege.collegeId as collegeId) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId��and s.nationality='CHN'��";
			 String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,c.yxCollege.collegeId as collegeId) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";	
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";			 
			 
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
			 
			 if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
				 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"'";
			 
			 sqlstring=sqlstring+" order by c.yxCollege.collegeId,c.classNo,s.studentNo";
			 
			 List stuinfoList=checkinmanageservice.find(sqlstring);
			 
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 
				 String stuNos="";
				 for(int i=0;i<stuinfoList.size();i++){
					 Map stum=(Map)stuinfoList.get(i);
					 String stuNo=(String)stum.get("studentNo");
					 stuNos=stuNos+"'"+stuNo+"'"+",";
				 }
				 if(stuNos.length()>0)
					 stuNos=stuNos.substring(0,stuNos.length()-1);
				 
               //�����ɷ���Ϣ���ѯ,ѧ��
			   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='01' and ci.studentNo in ("+stuNos+") order by ci.studentNo";
			 
		       List tuitionList=checkinmanageservice.find(sqlstring);
		       
               //�����ɷ���Ϣ���ѯ,ס�޷�
			   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and ci.studentNo in ("+stuNos+") order by ci.studentNo";
			 
		       List dormfeeList=checkinmanageservice.find(sqlstring);		                      
		       
               // �����ɷ���Ϣ���ѯ,�鼮���ѽ�������
			   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='03' and ci.studentNo in ("+stuNos+") order by ci.studentNo";
			 
		       List bookfeeList=checkinmanageservice.find(sqlstring);
		                      
			 
               for(int i=0;i<stuinfoList.size();i++){
            	 
				 Map m=(Map)stuinfoList.get(i);
				 String sno=((String)m.get("studentNo")).trim();
			
				 if(tuitionList!=null&&tuitionList.size()>0){
				     int j=0;
				     for(j=0;j<tuitionList.size();j++){
					     Map uhm=(Map)tuitionList.get(j);
					     String stuno=((String)uhm.get("studentNo")).trim();					     
					     if(stuno.equals(sno)){	
					    	 m.put("tuitionpayed",uhm.get("shouldPay"));
						     break;
					     }					     
				     }
				     if(j>tuitionList.size()||j==tuitionList.size()){
				    	 m.put("tuitionpayed","");
				     }
			     }
			     
			     
			     if(dormfeeList!=null&&dormfeeList.size()>0){
				     int j=0;
				     for(j=0;j<dormfeeList.size();j++){
					     Map uhm=(Map)dormfeeList.get(j);
					     String stuno=((String)uhm.get("studentNo")).trim();					     
					     if(stuno.equals(sno)){
					    	 m.put("dormfeepayed",uhm.get("shouldPay"));
						     break;
					     }					     
				     } 
				     if(j>dormfeeList.size()||j==dormfeeList.size()){
				    	 m.put("dormfeepayed","");
				     }
			     }
			     
			     
			     if(bookfeeList!=null&&bookfeeList.size()>0){
				     int j=0;
				     for(j=0;j<bookfeeList.size();j++){
					     Map uhm=(Map)bookfeeList.get(j);
					     String stuno=((String)uhm.get("studentNo")).trim();					     
					     if(stuno.equals(sno)){
					    	 m.put("bookfeepayed",uhm.get("shouldPay"));
						     break;
					     }					     
				     } 
				     if(j>bookfeeList.size()||j==bookfeeList.size()){
				    	 m.put("bookfeepayed","");
				     }
			     }
			     			    
			     String colno=((String)m.get("collegeId")).trim();
				 if(collegeList!=null&&collegeList.size()>0){
					 for(int j=0;j<collegeList.size();j++){
						 Map n=(Map)collegeList.get(j);
						 String cno2=((String)n.get("id")).trim();
						 if(colno.equals(cno2)){
							 m.put("collegeName",n.get("collegeName"));							     
						 }
					 }
				 }
			    
			    s1.add(m);		 
			    
			  }//for
			 
			 }
			 if(s1!=null&&s1.size()!=0){
				 
				 ChangeMajorValue(s1);
				 ChangeGenderValue(s1);				 
				 
				 List resultList=new ArrayList();
                 //��ʼҳ����
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
					 request.setAttribute("collegeId",collegeId);
				     request.setAttribute("stufeelist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				 }                 
				 
if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 	                   					 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/������ѧ��Ϣһ��.xls");
						String	fileName="stufee.xls";
						// Create the Sheet with the name of the Table
						HSSFWorkbook wb = new HSSFWorkbook();
						
		                //������ʾ�������Լ���ص���ʽ
				 		HSSFFont font = wb.createFont();
				 		    font.setFontHeightInPoints((short)8);
				 		    //font.setFontName("����");
				 		    font.setItalic(false);
				 		    font.setStrikeout(false);
				 		   
				 		//���ñ�������Ԫ�����ʽ
				 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
				 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				 		    cellHeadStyle.setBorderLeft((short)1);
				 		    cellHeadStyle.setBorderRight((short)1);
				 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				 		//���������е������Լ��Լ���صĶ��뷽ʽ
				 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
				 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellDataStyle.setFont(font);
						
						HSSFSheet sheet1 = wb.createSheet("Sheet1");
			 		    
						// Grab & populate the Column Names
						HSSFRow row = sheet1.createRow((short)0);
						
		               //Populate the first row of the spreadsheet with the column names
						List columnNames =new ArrayList();
						
						columnNames.add(0,"��Ժ");
						columnNames.add(1,"�༶");
						columnNames.add(2,"ѧ��");
						columnNames.add(3,"����");
						columnNames.add(4,"�Ա�");
						columnNames.add(5,"רҵ");						
						columnNames.add(6,"ѧ��");
						columnNames.add(7,"ס�޷�");
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = s1.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)s1.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("studentNo"));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("stuName"));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("genderName"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("majorinName"));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(tableData.get("tuitionpayed")+"");
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(tableData.get("dormfeepayed")+"");
								
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
				     return mapping.findForward("stufeelist");
			 }
			 else{
				 //request.setAttribute("msg","0");
				 return mapping.findForward("stufeelist");
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
    
    
    //����Ա�鿴ѧ�ѡ�ס�޷ѡ��鼮��δ��������
    public ActionForward classfeenotpaylist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		List s1=new ArrayList();
		List sub1=new ArrayList();
 		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
                //��ʼҳ
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}				
				
                //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
					
					Studentmodel stuinfo=new Studentmodel();				
					stuinfo.setStudentNo(request.getParameter("hstudentNo"));
					stuinfo.setStuName(request.getParameter("hstuName"));					
					
					List stuinfoList=new ArrayList();
					String sqlstring="";
					String classNo="";			 
					Account manager=(Account)session.getAttribute("accountPerson");	            
				    String managerNo=manager.getPerson().getPersonCode();	//��ȡ��¼�ߵ�ѧ����
				    List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"'");
				    
		if(managerclassList!=null&&managerclassList.size()>0){
			
			 classNo=(String)managerclassList.get(0);
			
			 sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.nationality='CHN' and c.classNo='"+classNo+"'";
			 	
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";	 
			 			 
			 sqlstring=sqlstring+" order by s.studentNo";
			 
			 stuinfoList=checkinmanageservice.find(sqlstring);
			 
		}	 
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 
				 String stuNos="";
				 for(int i=0;i<stuinfoList.size();i++){
					 Map stum=(Map)stuinfoList.get(i);
					 String stuNo=(String)stum.get("studentNo");
					 stuNos=stuNos+"'"+stuNo+"'"+",";
				 }
				 if(stuNos.length()>0)
					 stuNos=stuNos.substring(0,stuNos.length()-1);
				 
//				�����ɷ���Ϣ���ѯ,ѧ���ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='01' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List tuitionList=checkinmanageservice.find(sqlstring);
			       
	               //�����ɷ���Ϣ���ѯ,ѧ��δ��������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='01' and (ci.exactPay<ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List tuitionnotpayList=checkinmanageservice.find(sqlstring);
			       
	               //�����ɷ���Ϣ���ѯ,ס�޷��ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List dormfeeList=checkinmanageservice.find(sqlstring);
			       
	               //�����ɷ���Ϣ���ѯ,ס�޷�δ��������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and (ci.exactPay<ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List dormfeenotpayList=checkinmanageservice.find(sqlstring);
			       
	               // �����ɷ���Ϣ���ѯ,�鼮���ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='03' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List bookfeeList=checkinmanageservice.find(sqlstring);
			       
	               //�����ɷ���Ϣ���ѯ,�鼮��δ��������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay,ci.exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='03' and (ci.exactPay<ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List bookfeenotpayList=checkinmanageservice.find(sqlstring);
				 
	               for(int i=0;i<stuinfoList.size();i++){
	            	 boolean flag1=false;
					 boolean flag2=false;
					 boolean flag3=false;
					 Map m=(Map)stuinfoList.get(i);
					 String sno=((String)m.get("studentNo")).trim();
				
					 if(tuitionnotpayList!=null&&tuitionnotpayList.size()>0){
					     int j=0;
					     for(j=0;j<tuitionnotpayList.size();j++){
						     Map uhm=(Map)tuitionnotpayList.get(j);
						     String stuno=((String)uhm.get("studentNo")).trim();					     
						     if(stuno.equals(sno)){					    	 
						    	 m.put("tuitionpayed","0");					    	 	
						    	 m.put("tupdateTime",uhm.get("updateTime"));					    	 
						    	 flag1=true;
							     break;
						     }					     
					     }                     
				     }
				     if(!flag1){//�ѽ�ѧ�ѱ�û�ҵ�
				    
				    	if(tuitionList!=null&&tuitionList.size()>0){
						     int j=0;
						     for(j=0;j<tuitionList.size();j++){
							     Map uhm=(Map)tuitionList.get(j);
							     String stuno=((String)uhm.get("studentNo")).trim();					     
							     if(stuno.equals(sno)){					    	 
							    	 m.put("tuitionpayed","1");					    	 	
							    	 m.put("tupdateTime",uhm.get("updateTime"));
							    	 flag1=true;
								     break;
							     }					     
						     }                     
					    }			    	
				       
				     }
				     if(!flag1){//δ��ѧ�ѱ�û�ҵ�
				    	m.put("tuitionpayed","0");			        
				     }
				     
				     if(dormfeenotpayList!=null&&dormfeenotpayList.size()>0){
					     int j=0;
					     for(j=0;j<dormfeenotpayList.size();j++){
						     Map uhm=(Map)dormfeenotpayList.get(j);
						     String stuno=((String)uhm.get("studentNo")).trim();					     
						     if(stuno.equals(sno)){					    	 
						    	 m.put("dormfeepayed","0");					    	 	
						    	 m.put("dupdateTime",uhm.get("updateTime"));					    	 
						    	 flag2=true;
							     break;
						     }					     
					     }                     
				     }
				     if(!flag2){//�ѽ�ѧ�ѱ�û�ҵ�
				    
				    	if(dormfeeList!=null&&dormfeeList.size()>0){
						     int j=0;
						     for(j=0;j<dormfeeList.size();j++){
							     Map uhm=(Map)dormfeeList.get(j);
							     String stuno=((String)uhm.get("studentNo")).trim();					     
							     if(stuno.equals(sno)){					    	 
							    	 m.put("dormfeepayed","1");					    	 	
							    	 m.put("dupdateTime",uhm.get("updateTime"));
							    	 flag2=true;
								     break;
							     }					     
						     }                     
					    }			    	
				       
				     }
				     if(!flag2){//δ��ѧ�ѱ�û�ҵ�
				    	m.put("dormfeepayed","0");			        
				     } 
				     
				     if(bookfeenotpayList!=null&&bookfeenotpayList.size()>0){
					     int j=0;
					     for(j=0;j<bookfeenotpayList.size();j++){
						     Map uhm=(Map)bookfeenotpayList.get(j);
						     String stuno=((String)uhm.get("studentNo")).trim();					     
						     if(stuno.equals(sno)){					    	 
						    	 m.put("bookfeepayed","0");					    	 	
						    	 m.put("bupdateTime",uhm.get("updateTime"));					    	 
						    	 flag3=true;
							     break;
						     }					     
					     }                     
				     }
				     if(!flag3){//�ѽ�ѧ�ѱ�û�ҵ�
				    
				    	if(bookfeeList!=null&&bookfeeList.size()>0){
						     int j=0;
						     for(j=0;j<bookfeeList.size();j++){
							     Map uhm=(Map)bookfeeList.get(j);
							     String stuno=((String)uhm.get("studentNo")).trim();					     
							     if(stuno.equals(sno)){					    	 
							    	 m.put("bookfeepayed","1");					    	 	
							    	 m.put("bupdateTime",uhm.get("updateTime"));
							    	 flag3=true;
								     break;
							     }					     
						     }                     
					    }			    	
				       
				     }
				     if(!flag3){//δ��ѧ�ѱ�û�ҵ�
				    	m.put("bookfeepayed","0");			        
				     }
			    
			    if(((String)m.get("tuitionpayed")).equals("0")||((String)m.get("dormfeepayed")).equals("0")) 
			     s1.add(m);		 
			    
			  }//for
			 }	 
		
			 if(s1!=null&&s1.size()!=0){				
				 
				 List resultList=new ArrayList();
                 //��ʼҳ����
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);					 
				     request.setAttribute("feenotpaylist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				 }                 
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 
					   ChangeMajorValue(s1);
					   ChangeGenderValue(s1);
	                   ChangeTuitionValue(s1);
	                   ChangeDormfeeValue(s1);
	                   ChangeBookfeeValue(s1);					 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/������ѧ��Ϣһ��.xls");
						String	fileName="classfeeresult.xls";
						// Create the Sheet with the name of the Table
						HSSFWorkbook wb = new HSSFWorkbook();
						
		                //������ʾ�������Լ���ص���ʽ
				 		HSSFFont font = wb.createFont();
				 		    font.setFontHeightInPoints((short)8);
				 		    //font.setFontName("����");
				 		    font.setItalic(false);
				 		    font.setStrikeout(false);
				 		   
				 		//���ñ�������Ԫ�����ʽ
				 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
				 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				 		    cellHeadStyle.setBorderLeft((short)1);
				 		    cellHeadStyle.setBorderRight((short)1);
				 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				 		//���������е������Լ��Լ���صĶ��뷽ʽ
				 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
				 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				 		cellDataStyle.setFont(font);
						
						HSSFSheet sheet1 = wb.createSheet("Sheet1");
			 		    
						// Grab & populate the Column Names
						HSSFRow row = sheet1.createRow((short)0);
						
		               //Populate the first row of the spreadsheet with the column names
						List columnNames =new ArrayList();						
						
						columnNames.add(0,"�༶");
						columnNames.add(1,"ѧ��");
						columnNames.add(2,"����");
						columnNames.add(3,"�Ա�");
						columnNames.add(4,"רҵ");						
						columnNames.add(5,"ѧ��");
						columnNames.add(6,"ס��");						
						columnNames.add(7,"�鼮��");
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = s1.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)s1.get(i);
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
								ctitle.setCellValue((String)tableData.get("majorinName"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("tuitionpayedName"));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("dormfeepayedName"));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("bookfeepayedName"));
								
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
				     return mapping.findForward("classfeenotpaylist");
			 }
			 else{
				 //request.setAttribute("msg","0");
				 return mapping.findForward("classfeenotpaylist");
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
    

//  ȡ���й�������Ժϵ
	public List getCollegeList(){
		try {
			 if(ygCheckinmanageService==null)
				 System.out.println("service is null");
			 String sqlstring="select new Map(col.id.dictValue as yxCode,col.dictName as yxName) from Dictionary col where col.id.dictNo=99 order by col.id.dictValue";
			 List collegeList=ygCheckinmanageService.find(sqlstring);
			 
			 if(collegeList!=null&&collegeList.size()>0)
				 return collegeList;
			 else
				 return null;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
	
	}
	//ȡ��Ժ�Ͱ༶�б�
	public String[][] getColandCls(){
		
		   List rList=new ArrayList();			   
		   String sqlstring = "";	
		   String[][] result;
		   
		   try {
				 if(ygCheckinmanageService==null)
					 System.out.println("service is null");		     
		     		     
		     rList=yxGraduateService.getMajorListFromGraduateTable();
		     if(rList!=null&&rList.size()>0){
		    	 result=new String[rList.size()][3];
		         for(int i=0;i<rList.size();i++){
		             result[i][0] =(String)(((Map)rList.get(i)).get("majorCode"));
		             result[i][1] = (String)(((Map)rList.get(i)).get("majorName"));
		             result[i][2] = (String)(((Map)rList.get(i)).get("collegeCode"));

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
		String[][] ar={{"1","��"},{"2","Ů"}};
		String[][] st={{"D","��ʿ��"},{"M","˶ʿ��"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("gender")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("genderName",ar[k][1]);
				 }
			 }
			 
			 if(n.get("studentType")!=null){
				 String stype=((String)n.get("studentType")).trim();
				 for(int k=0;k<st.length;k++){				 
					 String stype1=st[k][0];
					 if(stype.equals(stype1)){
						 n.put("studentTypeName",st[k][1]);
					 }
				 }
			 }
			 else
				 n.put("studentTypeName","");
			 
		 }
		
	}
	
	public void ChangeDepartmentValue(List list){
		List departList=getdepartmentList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("department")!=null){
			     String mj=((String)n.get("department")).trim();
			     for(int k=0;k<departList.size();k++){
				     Map n1=(Map)departList.get(k);
				     String mj1=((String)n1.get("deptCode")).trim();
				     if(mj.equals(mj1)){
					     n.put("departmentName",((String)n1.get("deptName")).trim());
				     }
			     }
			 }
			 else
				 n.put("departmentName","");
				 
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
	
	public void ChangeTuitionValue(List list){
		String[][] ar={{"0","δ����"},{"1","�ѽ���"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);			 
			 String mj=((String)n.get("tuitionpayed")).trim();
			 for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("tuitionpayedName",ar[k][1]);
				   }
			 }
			 
		 }//for
		
	}
	
	public void ChangeDormfeeValue(List list){
		String[][] ar={{"0","δ����"},{"1","�ѽ���"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);			 
			 String mj=((String)n.get("dormfeepayed")).trim();
			 for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("dormfeepayedName",ar[k][1]);
				   }
			 }
			 
		 }//for
		
	}
	
	public void ChangeBookfeeValue(List list){
		String[][] ar={{"0","δ����"},{"1","�ѽ���"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);			 
			 String mj=((String)n.get("bookfeepayed")).trim();
			 for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("bookfeepayedName",ar[k][1]);
				   }
			 }
			 
		 }//for
		
	}
	
	public List getdepartmentList(){
		List departmentList=checkinmanageservice.find("select new Map(d.deptCode as deptCode,d.deptName as deptName) from Department d");
		return departmentList;
	}
	
	public List getmajorList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
		return majorList;
	}
	public void setYxGraduateService(YxGraduateService yxGraduateService) {
		this.yxGraduateService = yxGraduateService;
	}

}
