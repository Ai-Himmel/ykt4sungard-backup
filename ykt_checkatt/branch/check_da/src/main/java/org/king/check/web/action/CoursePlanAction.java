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
	        	
   	 /*   if (form instanceof UpLoadForm) {//���form��UpLoadsForm
	 	           
	      String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//ȡ���ϴ����ļ�
	 	     if(file==null){	 	    	
	 	    	return mapping.findForward("importfail");
	 	     }
	 	     
	 	     String contentType = file.getContentType();
	      	 String size = (file.getFileSize() + " bytes");//�ļ���С
	      	 
	 	     String fileName= file.getFileName();//�ļ���
	 	     fileName=request.getParameter("filepath");
	 	     InputStream checkis = file.getInputStream();//���ļ�����,���ڼ���ʽ
	 	     InputStream is=file.getInputStream();//���ļ�����,���ڵ�������
	 	     	 	     
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
   			     rowCount--;//��ȥ������
   	             resultstring=resultstring+"����excel��¼����"+rowCount+"\n";
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
   	        		  String term = row.getCell((short)0).getStringCellValue().trim();//ѧ��
   	        		  String schoolarea = row.getCell((short)1).getStringCellValue().trim();//У��
   	        		  String build = row.getCell((short)2).getStringCellValue().trim();//¥��
   	        		  String room = row.getCell((short)3).getStringCellValue().trim();//����
   	        		  String course = row.getCell((short)4).getStringCellValue().trim();//�γ�
   	        	      String custId = row.getCell((short)5).getStringCellValue().trim();//��ʦѧ����
   	        	      String custname = row.getCell((short)6).getStringCellValue().trim();//��ʦ��
   	        	      String schoolclass = row.getCell((short)7).getStringCellValue().trim();//�༶��
   	        	      String week = row.getCell((short)8).getStringCellValue().trim();//�ܼ��Ͽ�
   	        	      String begWeek = row.getCell((short)9).getStringCellValue().trim();//��ʼ�ܴ�
   	        	      String endWeek = row.getCell((short)10).getStringCellValue().trim();//�����ܴ�
   	        		  String begtimes = row.getCell((short)11).getStringCellValue().trim();//��ʼ�δ�
   	        		  String endtimes = row.getCell((short)12).getStringCellValue().trim();//�����δ�
   	        		  
   	        		  
   	        		  
   	        		 
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
   	        	resultstring=resultstring+"����excel��ʽ��\n";
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

		// ������ʾ�������Լ���ص���ʽ
		HSSFFont font = wb.createFont();
		font.setFontHeightInPoints((short) 8);
		font.setItalic(false);
		font.setStrikeout(false);

		// ���ñ�������Ԫ�����ʽ
		HSSFCellStyle cellHeadStyle = wb.createCellStyle();
		cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellHeadStyle.setBorderBottom((short) 1);
		cellHeadStyle.setBorderLeft((short) 1);
		cellHeadStyle.setBorderRight((short) 1);
		cellHeadStyle.setBorderTop((short) 1);
		cellHeadStyle
				.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
		cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

		// ���������е������Լ��Լ���صĶ��뷽ʽ
		HSSFCellStyle cellDataStyle = wb.createCellStyle();
		cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellDataStyle.setFont(font);

		HSSFSheet sheet1 = wb.createSheet("Sheet1");

		// Grab & populate the Column Names
		HSSFRow row = sheet1.createRow((short) 0);

		// Populate the first row of the spreadsheet with the column names
		List columnNames = new ArrayList();
												

		columnNames.add(0, "ѧ��");
		columnNames.add(1, "У��	");
		columnNames.add(2, "��ѧ¥");
		columnNames.add(3, "����");
		columnNames.add(4, "�γ�	");
		columnNames.add(5, "��ʦѧ����");
		columnNames.add(6, "��ʦ����");
		columnNames.add(7, "�Ͽΰ༶");
		columnNames.add(8, "�ܼ�");
		columnNames.add(9, "��ʼ�ܴ�");
		columnNames.add(10, "�����ܴ�");
		columnNames.add(11, "��ʼ����");
		columnNames.add(12, "��������");		
		
		HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//�����ֶεı�������ʽ
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
			ctitle.setCellValue("09��");

			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("��˳");
			
			ctitle = row.createCell((short) 2);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("�´�¥");
			
			ctitle = row.createCell((short) 3);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("120");
			
			ctitle = row.createCell((short) 4);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("��ý�弼������");
			
			ctitle = row.createCell((short) 5);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("3209");
			
			ctitle = row.createCell((short) 6);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("֣�ζ�");
			
			ctitle = row.createCell((short) 7);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("09������ר,09������");
			
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
