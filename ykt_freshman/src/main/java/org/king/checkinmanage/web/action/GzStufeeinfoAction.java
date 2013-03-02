/**
 * 
 */
package org.king.checkinmanage.web.action;

import java.io.OutputStream;
import java.util.ArrayList;
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
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;

/**
 * @author jackey
 *
 */
public class GzStufeeinfoAction extends BaseAction{
	
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
                  
	                //רҵ
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList); 
					 		 
		            String sqlstring=null;		            	            
		            
		            //����������Ϣ
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince) from Studentmodel s where s.studentNo='"+id+"'";
		            	            
		            List stuinfoList=checkinmanageservice.find(sqlstring);
		            
		            //���ڰ༶
		            sqlstring="select new Map(s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.studentNo='"+id+"'";
    	            
		            List classinfoList=checkinmanageservice.find(sqlstring);
		            
		            //����ѧ����Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='01' and sf.studentNo='"+id+"'";
		            
		            List tuitionList=checkinmanageservice.find(sqlstring);
		            
		            //����ס�޷���Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='02' and sf.studentNo='"+id+"'";
		            
		            List dormfeeList=checkinmanageservice.find(sqlstring);
		            
                    //�����鼮����Ϣ
		            sqlstring="select new Map(sf.id as id,sf.studentNo as studentNo,sf.feeItem as feeItem,sf.shouldPay as shouldPay,sf.exactPay as exactPay) from StuFeeInfo sf where sf.feeItem='03' and sf.studentNo='"+id+"'";
		            
		            List bookfeeList=checkinmanageservice.find(sqlstring);
		          
		            if(tuitionList!=null&&tuitionList.size()>0)
		            	request.setAttribute("tuitionlist",tuitionList);
		            if(dormfeeList!=null&&dormfeeList.size()>0)
		            	request.setAttribute("dormfeelist",dormfeeList);
		            if(bookfeeList!=null&&bookfeeList.size()>0)
		            	request.setAttribute("bookfeelist",bookfeeList);
		            if(classinfoList!=null&&classinfoList.size()>0)
		            	request.setAttribute("classinfolist",classinfoList);
		          if(stuinfoList!=null&&stuinfoList.size()!=0){
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
			 
			 List classList=getClassList();
			 if(classList!=null&&classList.size()>0)
				 request.setAttribute("classlist",classList);
			 
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
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
			
			 String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,c.classNo as classNo,col.collegeId as collegeId,col.collegeName as collegeName) from Studentmodel s,Classmodel c,Collegemodel col where s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
			 	
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
						columnNames.add(3,"�༶");
						
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
								ctitle.setCellValue((String)tableData.get("classNo"));
																
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

		ActionMessages errors = new ActionMessages();
		List s1=new ArrayList();
 		// ���ݿ���֤
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 List classList=getClassList();
			 if(classList!=null&&classList.size()>0)
				 request.setAttribute("classlist",classList);
			 
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
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
					
					
					String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,col.collegeId as collegeId,col.collegeName as collegeName) from Studentmodel s,Classmodel c,Collegemodel col where s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.dormId is not null and s.dormId<>'' and s.nationality='CHN'";
				 	
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
					 
					 String stuNos="";
					 for(int i=0;i<stuinfoList.size();i++){
						 Map stum=(Map)stuinfoList.get(i);
						 String stuNo=(String)stum.get("studentNo");
						 stuNos=stuNos+"'"+stuNo+"'"+",";
					 }
					 if(stuNos.length()>0)
						 stuNos=stuNos.substring(0,stuNos.length()-1);
					 
	               //�����ɷ���Ϣ���ѯ,ס�޷��ѽ�������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
			       List tuitionList=checkinmanageservice.find(sqlstring);
			       
                   //�����ɷ���Ϣ���ѯ,ס�޷�δ��������
				   sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.shouldPay as shouldPay,ci.exactPay as exactPay,ci.updateTime as updateTime) from StuFeeInfo ci where ci.feeItem='02' and (ci.exactPay<ci.shouldPay) and ci.studentNo in ("+stuNos+")";
				 
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
						    	 m.put("dormfeepayed","0");					    	 	
						    	 m.put("updateTime",uhm.get("updateTime"));
						    	 s1.add(m);
						    	 flag=true;
							     break;
						     }					     
					     }                     
				    }
				    if(!flag){//�ѽ�ס�޷ѱ���û�ҵ�
				    
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
				    if(!flag){//δ��ס�޷ѱ���û�ҵ�
				    	m.put("dormfeepayed","0");
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
						
						columnNames.add(0,"�༶");						
						columnNames.add(1,"ѧ��");
						columnNames.add(2,"����");
						columnNames.add(3,"�Ա�");						
												
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
				     return mapping.findForward("dormfeenotpaylist");
			 }
			 else
				 return mapping.findForward("dormfeenotpaylist");
			 
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
			 
			 List classList=getClassList();
			 if(classList!=null&&classList.size()>0)
				 request.setAttribute("classlist",classList);
			 
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
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
			
			 //String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,c.yxCollege.collegeId as collegeId) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId��and s.nationality='CHN'��";
			 String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,c.yxCollege.collegeId as collegeId) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";	
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
			     			    
			    
				m.put("collegeName","����ѧԺ");							     
				
			    
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
												
						columnNames.add(0,"�༶");
						columnNames.add(1,"ѧ��");
						columnNames.add(2,"����");
						columnNames.add(3,"�Ա�");						
						columnNames.add(4,"ѧ��");
						columnNames.add(5,"ס�޷�");
						
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
								ctitle.setCellValue(tableData.get("tuitionpayed")+"");
								
								ctitle=row.createCell((short)5);
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
    
    //����ѧԺѧ�ѡ�ס�޷ѡ��鼮��δ��������
    public ActionForward feenotpaylist(ActionMapping mapping, ActionForm form,
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
			 
			 List classList=getClassList();
			 if(classList!=null&&classList.size()>0)
				 request.setAttribute("classlist",classList);
			 
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
					
					String classNo=request.getParameter("hclassNo");
					String collegeId=request.getParameter("hcollegeId");
			
			 String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.dormId as dormId,c.classNo as classNo,c.yxCollege.collegeId as collegeId) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
			 	
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
				 
               //�����ɷ���Ϣ���ѯ,ѧ���ѽ�������
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
					    	if(m.get("dormId")!=null&&!((String)m.get("dormId")).equals(""))
					    	    m.put("dormfeepayed","0");	
					    	else
					    		m.put("dormfeepayed","2");	
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
			     if(!flag2){//δ���ѽɱ�û�ҵ�
			    	 if(m.get("dormId")!=null&&!((String)m.get("dormId")).equals(""))
			    	     m.put("dormfeepayed","0");
			    	 else
			    		 m.put("dormfeepayed","2");
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
			    
			     
				m.put("collegeName","����ѧԺ");							     
				
			    
			    if(((String)m.get("tuitionpayed")).equals("0")||((String)m.get("dormfeepayed")).equals("0")) 
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
				     request.setAttribute("feenotpaylist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				 }                 
				 
if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 
	                   ChangeTuitionValue(s1);
	                   ChangeDormfeeValue(s1);
	                   ChangeBookfeeValue(s1);					 
					 /*-----------------------------------------------------------------------*/
		                // Create the Excel File
				 		//FileOutputStream fileOut = new FileOutputStream("c:/������ѧ��Ϣһ��.xls");
						String	fileName="feeresult.xls";
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
						columnNames.add(4,"ѧ��");
						columnNames.add(5,"ס�޷�");	
						
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
								ctitle.setCellValue((String)tableData.get("tuitionpayedName"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("dormfeepayedName"));
																
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
				     return mapping.findForward("feenotpaylist");
			 }
			 else{
				 //request.setAttribute("msg","0");
				 return mapping.findForward("feenotpaylist");
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
				    
				    sqlstring="select new Map(c.classId as classId,c.classNo as classNo) from Classmodel c,Managermodel m,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"' order by c.classNo ";
		 	         
			        List managerclassList=checkinmanageservice.find(sqlstring);
				    
		if(managerclassList!=null&&managerclassList.size()>0){
			
			request.setAttribute("classlist",managerclassList);
       	 
       	   if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0&&!request.getParameter("hclassNo").equals("null"))
       	     classNo=request.getParameter("hclassNo");
       	   else{
       		 Map cm=(Map)managerclassList.get(0);
       		 classNo=(String)cm.get("classNo");
       	   }
			
			 sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.dormId as dormId,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.nationality='CHN' and c.classNo='"+classNo+"'";
			 	
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
						    	 if(m.get("dormId")!=null&&!((String)m.get("dormId")).equals(""))
						    	     m.put("dormfeepayed","0");	
						    	 else
						    		 m.put("dormfeepayed","2");	
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
				    	 if(m.get("dormId")!=null&&!((String)m.get("dormId")).equals(""))
				    	     m.put("dormfeepayed","0");	
				    	 else
				    		 m.put("dormfeepayed","2");	
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
					 request.setAttribute("classNo",classNo);
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
						columnNames.add(4,"ѧ��");
						columnNames.add(5,"ס�޷�");	
						
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
								ctitle.setCellValue((String)tableData.get("tuitionpayedName"));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("dormfeepayedName"));
																
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
    

	//ȡ����ѧԺ��������Ժ
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
	//ȡ��Ժ�Ͱ༶�б�
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
		String[][] ar={{"1","��"},{"2","Ů"}};
		
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
		String[][] ar={{"0","δ����"},{"1","�ѽ���"},{"2","�������"}};
		
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

//	ȡ����ѧԺ�����а༶
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
