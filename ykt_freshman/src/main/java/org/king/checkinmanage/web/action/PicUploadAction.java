/**
 * 
 */
package org.king.checkinmanage.web.action;

import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.checkinmanage.web.form.UpLoadForm;
import org.apache.poi.hssf.usermodel.*;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.upload.FormFile;
import org.apache.struts.validator.DynaValidatorForm;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
/**
 * @author jackey
 *
 */
public class PicUploadAction extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward picUpload(ActionMapping mapping, ActionForm form,
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
	        
	        if(file==null){
	        	System.out.println("can not getFormFile.");
	        	return mapping.findForward("picUploadnoFile");
	        }
	        
	        String contentType = file.getContentType();

	        String size = (file.getFileSize() + " bytes");//文件大小
	        String fileName= file.getFileName();//文件名
	        Date date = new Date();
	        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddhhmmss");
	        String realName = sdf.format(date)+ fileName.substring(fileName.indexOf("."), fileName.length());

	       
	        try {
	          InputStream stream = file.getInputStream();//把文件读入
	          String filePath = request.getRealPath("/");//取当前系统路径
	          
	          String realPath = filePath + "/pages/upload";
	          File realFile = new File(realPath);
	          if (!realFile.exists())
	        	  realFile.mkdirs();
	          OutputStream bos = new FileOutputStream(realPath+"/"+realName);
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
	          e.printStackTrace();
	          System.out.println("pic upload fail.");
	          return mapping.findForward("picUploadfail");
	        }
	        //request.setAttribute("dat",file.getFileName());
	         request.setAttribute("contentType", contentType);
	         request.setAttribute("size", size);
	         request.setAttribute("fileName", "pages/upload/"+realName);
	         request.setAttribute("b", request.getParameter("b"));
	         request.setAttribute("c", request.getParameter("c"));
	         request.setAttribute("d", request.getParameter("d"));
	         request.setAttribute("e", request.getParameter("e"));
	         request.setAttribute("f", request.getParameter("f"));
	         request.setAttribute("g", request.getParameter("g"));
	         request.setAttribute("h", request.getParameter("h"));
	         request.setAttribute("i", request.getParameter("i"));
	         
	         request.setAttribute("msg", "success");
             
	        return mapping.findForward("picUploadsuccess");
	    }
	    return null;
	  }
        
}
