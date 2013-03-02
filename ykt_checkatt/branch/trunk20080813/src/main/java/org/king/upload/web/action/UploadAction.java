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

import org.apache.log4j.Logger;

import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.upload.FormFile;
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
/*	public ActionForward importDormitoryFile(ActionMapping mapping,
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

				// 处理excel文件，导入到数据库中
				Workbook rwb = Workbook.getWorkbook(is);

				// demo 处理新生交费格式.xls
				Sheet rs = rwb.getSheet(0);
				Dormitorymodel dorm = new Dormitorymodel();
				int j = 1;
				while (true) {
					String args[] = new String[6];
					for (int i = 0; i < 6; i++) {
						if (rs.getCell(i, j).getContents() != null
								&& rs.getCell(i, j).getContents() != "") {
							args[i] = rs.getCell(i, j).getContents();
						} else
							break;
					}
					if (args.length == 6 && j < 10000) {

						dormitoryService.addConvertDorm(args);
						j++;
					} else
						break;
				}

			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"导入文件出错!"));

			}

		}

		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
		return mapping.findForward("importDormitoryFile");
	}
*/
	
	
		
}

