package org.king.check.web.action;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
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
import org.apache.struts.upload.FormFile;
import org.king.check.service.CourseplanService;
import org.king.framework.web.action.BaseAction;
import org.king.upload.web.form.UpLoadForm;

public class CoursePlanAction extends BaseAction {

	
	
	public ActionForward importExcel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception{
	   	
   		HttpSession session = request.getSession(false);

		/*if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";
				
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}*/
	        	
   	 /*   if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	 	           
	      String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//取得上传的文件
	 	     if(file==null){	 	    	
	 	    	return mapping.findForward("importfail");
	 	     }
	 	     
	 	     String contentType = file.getContentType();
	      	 String size = (file.getFileSize() + " bytes");//文件大小
	      	 
	 	     String fileName= file.getFileName();//文件名
	 	     fileName=request.getParameter("filepath");
	 	     InputStream checkis = file.getInputStream();//把文件读入,用于检查格式
	 	     InputStream is=file.getInputStream();//把文件读入,用于导入数据
	 	     	 	     
	 	     String resultstring="";
	 	     String testId=request.getParameter("testId");
	 	     String importMode=request.getParameter("importmode");
	 	    try{
	 	     resultstring=checkSbModel(checkis);
	 	     HSSFWorkbook wb =null;
	 	     HSSFSheet sheet=null;
	 	     int rowCount =0;
	 	     if(resultstring.equals("")){
	 	    	 wb=new HSSFWorkbook(is);
   	             String tableName =  wb.getSheetName(0);   			
   			     sheet = wb.getSheet(tableName);
   			     rowCount = sheet.getPhysicalNumberOfRows();
   			     rowCount--;//减去标题行
   	             resultstring=resultstring+"读入excel记录数："+rowCount+"\n";
	 	     }
	 	     else{
	 	    	request.setAttribute("importresult",resultstring); 
	 	    	return mapping.findForward("importfail");
	 	     }
	 	     
	 	     rowCount=sheet.getPhysicalNumberOfRows();
	 	 
   	         if(rowCount>0){
   	        	 if(importMode!=null&&importMode.equals("add")){
   	        	   for(int i=1;i<rowCount;i++){
   	        		  HSSFRow row = sheet.getRow(i);
   	        		  String term = row.getCell((short)0).getStringCellValue().trim();//学期
   	        		  String schoolarea = row.getCell((short)1).getStringCellValue().trim();//校区
   	        		  String build = row.getCell((short)2).getStringCellValue().trim();//楼宇
   	        		  String room = row.getCell((short)3).getStringCellValue().trim();//教室
   	        		  String course = row.getCell((short)4).getStringCellValue().trim();//课程
   	        	      String custId = row.getCell((short)5).getStringCellValue().trim();//教师学工号
   	        	      String custname = row.getCell((short)6).getStringCellValue().trim();//教师名
   	        	      String schoolclass = row.getCell((short)7).getStringCellValue().trim();//班级名
   	        	      String week = row.getCell((short)8).getStringCellValue().trim();//周几上课
   	        	      String begWeek = row.getCell((short)9).getStringCellValue().trim();//开始周次
   	        	      String endWeek = row.getCell((short)10).getStringCellValue().trim();//结束周次
   	        		  String begtimes = row.getCell((short)11).getStringCellValue().trim();//开始课次
   	        		  String endtimes = row.getCell((short)12).getStringCellValue().trim();//结束课次
   	        		  
   	        		  
   	        		  
   	        		 
   	        		 if(testId!=null&&testId.length()>0)
   	        	         resultstring=resultstring+RoomCourseTimeService.saveCoursePlanImport( schoolarea, build , room, course,
   	        	  			 custId, week, begtimes , endtimes);
   	        	 }
   	        	 else if(importMode!=null&&importMode.equals("update")){   	        		 
   	        		 resultstring=resultstring+studentService.updateStuBmbyImport(sheet,testId,userId);
   	        	 }
   	        	else if(importMode!=null&&importMode.equals("delete")){
  	        		 if(testId!=null&&testId.length()>0)
  	        	         resultstring=resultstring+studentService.deleteStuBmbyImport(sheet,testId,userId);
  	        	 }
   	         }
   	         else if(rowCount==0){
   	        	if(importMode!=null&&importMode.equals("delete")){
 	        		 if(testId!=null&&testId.length()>0)
 	        	         resultstring=resultstring+studentService.deleteStuBmbyImport(sheet,testId,userId);
 	        	 }
   	         }
   	         else{
   	        	resultstring=resultstring+"请检查excel格式！\n";
   	         }
   	         
   	         request.setAttribute("importresult",resultstring);   	         
   	      
	    }catch(Exception e){
   		      e.printStackTrace();
   		      return mapping.findForward("importfail");
   	    }
	    finally{
	    	checkis.close();
	    	is.close();
	    }
	 }*/
	    return mapping.findForward("importsuccess");
    }

	
	
	public ActionForward getModel(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
    	
    	String fileName = "coursePlanModel.xls";

		// Create the Sheet with the name of the Table
		HSSFWorkbook wb = new HSSFWorkbook();

		// 设置显示的字体以及相关的样式
		HSSFFont font = wb.createFont();
		font.setFontHeightInPoints((short) 8);
		font.setItalic(false);
		font.setStrikeout(false);

		// 设置标题栏单元格的样式
		HSSFCellStyle cellHeadStyle = wb.createCellStyle();
		cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellHeadStyle.setBorderBottom((short) 1);
		cellHeadStyle.setBorderLeft((short) 1);
		cellHeadStyle.setBorderRight((short) 1);
		cellHeadStyle.setBorderTop((short) 1);
		cellHeadStyle
				.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
		cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

		// 设置数据行的字体以及以及相关的对齐方式
		HSSFCellStyle cellDataStyle = wb.createCellStyle();
		cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellDataStyle.setFont(font);

		HSSFSheet sheet1 = wb.createSheet("Sheet1");

		// Grab & populate the Column Names
		HSSFRow row = sheet1.createRow((short) 0);

		// Populate the first row of the spreadsheet with the column names
		List columnNames = new ArrayList();
												

		columnNames.add(0, "学期");
		columnNames.add(1, "校区	");
		columnNames.add(2, "教学楼");
		columnNames.add(3, "教室");
		columnNames.add(4, "课程	");
		columnNames.add(5, "教师学工号");
		columnNames.add(6, "教师姓名");
		columnNames.add(7, "上课班级");
		columnNames.add(8, "周几");
		columnNames.add(9, "开始周次");
		columnNames.add(10, "结束周次");
		columnNames.add(11, "开始课数");
		columnNames.add(12, "结束课数");		
		
		HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//必填字段的标题栏格式
		keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		keycellHeadStyle.setBorderBottom((short) 1);
		keycellHeadStyle.setBorderLeft((short) 1);
		keycellHeadStyle.setBorderRight((short) 1);
		keycellHeadStyle.setBorderTop((short) 1);		
		keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);   
        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND); 
		
		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cname = row.createCell((short) i);	
			if(i==0||i==1)
				cname.setCellStyle(keycellHeadStyle);
			else
				cname.setCellStyle(cellHeadStyle);
			cname.setEncoding(HSSFCell.ENCODING_UTF_16);			
			cname.setCellValue((String) columnNames.get(i));
		}

		
			// create row in spreadsheet
			row = sheet1.createRow((short)1);

			// populate the spreadsheet with the cell
			HSSFCell ctitle = row.createCell((short) 0);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("09春");

			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("国顺");
			
			ctitle = row.createCell((short) 2);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("新大楼");
			
			ctitle = row.createCell((short) 3);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("120");
			
			ctitle = row.createCell((short) 4);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("多媒体技术基础");
			
			ctitle = row.createCell((short) 5);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("3209");
			
			ctitle = row.createCell((short) 6);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("郑任儿");
			
			ctitle = row.createCell((short) 7);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("09春工商专,09春货代");
			
			ctitle = row.createCell((short) 8);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("2");
						
			ctitle = row.createCell((short) 9);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("1");
			
			ctitle = row.createCell((short) 10);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("1");
			
			ctitle = row.createCell((short) 11);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("9");
		
		
			ctitle = row.createCell((short) 11);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("12");
        		
		response.setContentType("application/x-msdownload");
		response.setHeader("Content-Disposition", "attachment;"
				+ " filename="
				+ new String(fileName.getBytes(), "ISO-8859-1"));

		OutputStream os = response.getOutputStream();
		wb.write(os);
		/*-----------------------------------------------------------------------*/
		return null;
    }


}
