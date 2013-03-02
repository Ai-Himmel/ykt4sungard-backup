/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.upload.web.action.UploadAction.java
 * 创建日期： 2006-5-25 10:18:30
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-5-25 10:18:30      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.upload.web.action;

import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;

import org.apache.log4j.Logger;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.upload.FormFile;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.web.action.BaseAction;
import org.king.upload.web.form.UpLoadForm;

/**
 * <p> UploadAction.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="UploadAction.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-5-25
 * 
 *
 */

public class UploadAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(UploadAction.class);
	private  DormitoryService dormitoryService;
	public void setDormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
	}
	
	public ActionForward upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
	    if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	           String encoding = request.getCharacterEncoding();

	       if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	        {
	            response.setContentType("text/html; charset=gb2312");
	        }
	        UpLoadForm theForm = (UpLoadForm ) form;
	        FormFile file = theForm.getTheFile();//取得上传的文件
	        String contentType = file.getContentType();

	        String size = (file.getFileSize() + " bytes");//文件大小
	        String fileName= file.getFileName();//文件名
	        try {
	          InputStream stream = file.getInputStream();//把文件读入
	          String filePath = request.getRealPath("/");//取当前系统路径
	          ByteArrayOutputStream baos = new ByteArrayOutputStream();
	          OutputStream bos = new FileOutputStream(filePath + "/page/upload/" +
	                                                  file.getFileName());
	              //建立一个上传文件的输出流，将上传文件存入web应用的根目录。
	          //System.out.println(filePath+"/"+file.getFileName());
	          int bytesRead = 0;
	          byte[] buffer = new byte[8192];
	          while ( (bytesRead = stream.read(buffer, 0, 8192)) != -1) {
	            bos.write(buffer, 0, bytesRead);//将文件写入服务器
	          }
	          bos.close();
	          stream.close();
	        }catch(Exception e){
	          System.err.print(e);
	        }
	        //request.setAttribute("dat",file.getFileName());
	         request.setAttribute("contentType", contentType);
	         request.setAttribute("size", size);
	         request.setAttribute("fileName", fileName);

	        return mapping.findForward("display");
	    }
	    return null;
	  } 
	
	public ActionForward load4upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		 return mapping.findForward("input");
	}
	
	
	public ActionForward importExcelFile(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionMessages messages = new ActionMessages();
		
	    if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	           String encoding = request.getCharacterEncoding();

	       if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	        {
	            response.setContentType("text/html; charset=gb2312");
	        }
	        UpLoadForm theForm = (UpLoadForm ) form;
	        FormFile file = theForm.getTheFile();//取得上传的文件
	        String contentType = file.getContentType();

	        String size = (file.getFileSize() + " bytes");//文件大小
	        String fileName= file.getFileName();//文件名
	        try {
	          InputStream is = file.getInputStream();//把文件读入
	          
	          //处理excel文件，导入到数据库中
	          Workbook rwb = Workbook.getWorkbook(is);
	          
	          //demo 处理新生交费格式.xls
	          Sheet rs = rwb.getSheet(0);
	          
	          Cell c00 = rs.getCell(0, 0);
	          String strc00 = c00.getContents();
	          Cell c01 = rs.getCell(0, 1);
	          
	          String strc01 = c01.getContents();
	          Cell c02 = rs.getCell(6, 1);
	          
	          String strc02 = c02.getContents();
	          Cell c03 = rs.getCell(6, 1);
	          String strc03 = c03.getContents();
	          
	         
	        }catch(Exception e){
	        	messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("导入文件出错!"));
	          
	        }


	    }
	    
	    if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
	    return mapping.findForward("input");
	
	}
	public ActionForward importDormitoryFile(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		ActionMessages messages = new ActionMessages();

		if (form instanceof UpLoadForm) {// 如果form是UpLoadsForm
			String encoding = request.getCharacterEncoding();

			if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
				response.setContentType("text/html; charset=gb2312");
			}
			UpLoadForm theForm = (UpLoadForm) form;
			FormFile file = theForm.getTheFile();// 取得上传的文件
			String contentType = file.getContentType();

			String size = (file.getFileSize() + " bytes");// 文件大小
			String fileName = file.getFileName();// 文件名
			try {
				InputStream is = file.getInputStream();// 把文件读入

				
				List dormList = reloadSpreadsheetModel(is);	 
				
				if(dormList!=null&&dormList.size()>0){
					dormitoryService.addConvertDorm(dormList);
				}

			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.importerr"));
				e.printStackTrace();

			}

		}

		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
		return mapping.findForward("init4Upload");
	}	
	
	
	public List reloadSpreadsheetModel(InputStream is) throws IOException {
		// Use POI to read the selected Excel Spreadsheet
		List result = new ArrayList();
		HSSFWorkbook wb = new HSSFWorkbook(is);
		// Extract the name of the first worksheet and use this for the tableName
		String tableName =  wb.getSheetName(0);
		// Select the first worksheet
		HSSFSheet sheet = wb.getSheet(tableName); 		    
		try {

			int rowCount = sheet.getPhysicalNumberOfRows();
			int colCount = sheet.getRow(0).getPhysicalNumberOfCells();
			if(colCount<6){
				return null;
			}
			for(int i = 1; i < rowCount; i++) {

				HSSFRow row = sheet.getRow(i); 

				ArrayList list = new ArrayList();
					list.add(row.getCell((short)0).getStringCellValue());					
					list.add(row.getCell((short)1).getStringCellValue());	
					list.add(String.valueOf(row.getCell((short)2).getNumericCellValue()));	
					list.add(row.getCell((short)3).getStringCellValue());											
					list.add(String.valueOf(row.getCell((short)4).getNumericCellValue())); 									
					list.add(String.valueOf(row.getCell((short)5).getNumericCellValue()));
				result.add(list);
			}

			return result;

		} catch (Exception e) {
			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return null;
		}
    }
}

