/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.upload.web.action.UploadAction.java
 * �������ڣ� 2006-5-25 10:18:30
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-5-25 10:18:30      ljf        �����ļ���ʵ�ֻ�������
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
 * <p> {����˵��} </p>
 *
 * <p><a href="UploadAction.java.html"><i>�鿴Դ����</i></a></p>  
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
	    if (form instanceof UpLoadForm) {//���form��UpLoadsForm
	           String encoding = request.getCharacterEncoding();

	       if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	        {
	            response.setContentType("text/html; charset=gb2312");
	        }
	        UpLoadForm theForm = (UpLoadForm ) form;
	        FormFile file = theForm.getTheFile();//ȡ���ϴ����ļ�
	        String contentType = file.getContentType();

	        String size = (file.getFileSize() + " bytes");//�ļ���С
	        String fileName= file.getFileName();//�ļ���
	        try {
	          InputStream stream = file.getInputStream();//���ļ�����
	          String filePath = request.getRealPath("/");//ȡ��ǰϵͳ·��
	          ByteArrayOutputStream baos = new ByteArrayOutputStream();
	          OutputStream bos = new FileOutputStream(filePath + "/page/upload/" +
	                                                  file.getFileName());
	              //����һ���ϴ��ļ�������������ϴ��ļ�����webӦ�õĸ�Ŀ¼��
	          //System.out.println(filePath+"/"+file.getFileName());
	          int bytesRead = 0;
	          byte[] buffer = new byte[8192];
	          while ( (bytesRead = stream.read(buffer, 0, 8192)) != -1) {
	            bos.write(buffer, 0, bytesRead);//���ļ�д�������
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
		
	    if (form instanceof UpLoadForm) {//���form��UpLoadsForm
	           String encoding = request.getCharacterEncoding();

	       if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	        {
	            response.setContentType("text/html; charset=gb2312");
	        }
	        UpLoadForm theForm = (UpLoadForm ) form;
	        FormFile file = theForm.getTheFile();//ȡ���ϴ����ļ�
	        String contentType = file.getContentType();

	        String size = (file.getFileSize() + " bytes");//�ļ���С
	        String fileName= file.getFileName();//�ļ���
	        try {
	          InputStream is = file.getInputStream();//���ļ�����
	          
	          //����excel�ļ������뵽���ݿ���
	          Workbook rwb = Workbook.getWorkbook(is);
	          
	          //demo �����������Ѹ�ʽ.xls
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
	        	messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("�����ļ�����!"));
	          
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

		if (form instanceof UpLoadForm) {// ���form��UpLoadsForm
			String encoding = request.getCharacterEncoding();

			if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
				response.setContentType("text/html; charset=gb2312");
			}
			UpLoadForm theForm = (UpLoadForm) form;
			FormFile file = theForm.getTheFile();// ȡ���ϴ����ļ�
			String contentType = file.getContentType();

			String size = (file.getFileSize() + " bytes");// �ļ���С
			String fileName = file.getFileName();// �ļ���
			try {
				InputStream is = file.getInputStream();// ���ļ�����

				// ����excel�ļ������뵽���ݿ���
				Workbook rwb = Workbook.getWorkbook(is);

				// demo �����������Ѹ�ʽ.xls
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
						"�����ļ�����!"));

			}

		}

		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
		return mapping.findForward("importDormitoryFile");
	}
*/
	
	
		
}

