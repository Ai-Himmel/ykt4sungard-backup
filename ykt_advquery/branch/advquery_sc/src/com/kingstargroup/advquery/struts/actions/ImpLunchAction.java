package com.kingstargroup.advquery.struts.actions;

import java.io.InputStream;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.upload.FormFile;
import org.king.upload.web.form.UpLoadForm;

import com.kingstargroup.advquery.hibernate.util.LunchUtil;

public class ImpLunchAction extends Action {

    public ActionForward execute(
            ActionMapping mapping,
            ActionForm form, 
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {
    	HttpSession session = request.getSession(false);
		if (session == null) {
			session = request.getSession(true);
		}
   	    if (form instanceof UpLoadForm) {//���form��UpLoadsForm	           
	      String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//ȡ���ϴ����ļ�
	 	     if(file==null ){	 	    	
	 	    	request.setAttribute("errorcont",new String("��ѡ����EXCEL�ļ���"));
	 	    	return mapping.findForward("errortest");
	 	     }else{
	 	    	String fileName = file.getFileName();
	 	    	if(fileName.indexOf(".xls")==-1){
	 	    		request.setAttribute("errorcont",new String("��ѡ����EXCEL�ļ���"));
		 	    	return mapping.findForward("errortest");
	 	    	}
	 	    	/*if(fileName.indexOf(".xlsx")==-1){
	 	    		request.setAttribute("errorcont",new String("�汾�����ݣ���ת���Ͱ汾EXCEL��ʽ��"));
		 	    	return mapping.findForward("errortest");
	 	    	}*/
	 	     }	 	     
	 	     InputStream checkis = file.getInputStream();//���ļ�����,���ڼ���ʽ
	 	 	 String resultstring="";

	 	    try{
	 	    	
	 		HSSFWorkbook wb = new HSSFWorkbook(checkis);		
			String tableName =  wb.getSheetName(0);		
			HSSFSheet sheet = wb.getSheet(tableName); 	
			
   	         resultstring = LunchUtil.implunchfile(sheet);
   	         request.setAttribute("resultstring",resultstring); 
   	       
	    }catch(Exception e){
   		      e.printStackTrace();
   		      request.setAttribute("errorcont",new String("��������쳣������ʧ�ܣ�"));
   		      return mapping.findForward("errortest");
   	    }
	    finally{
	    	checkis.close();
	    }
	  }
	    return mapping.findForward("importsuccess");	
    }

}
