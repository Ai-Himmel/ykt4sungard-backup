/**
 * 
 */
package org.king.business.web.action;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Blob;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.king.business.domain.TCifPhoto;
import org.king.business.service.StudentService;
import org.king.security.dao.AccountDAO;
import org.springframework.context.ApplicationContext;
import org.springframework.web.context.support.WebApplicationContextUtils;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * @author jeffxiao
 *
 */
public class EcardImageServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {
		        
		String path=req.getSession().getServletContext().getRealPath("/");
		
		try {
			String cutId = req.getParameter("cutId");
			res.setContentType("image/jpg");
			if (cutId==null||cutId.equals("")) {
				ServletOutputStream out = res.getOutputStream();
				FileInputStream fis=new FileInputStream(path+"pages/photo/temp.jpg");  
				byte buffer[] = new byte[512];
				while (fis.read(buffer, 0, 512) != -1) {						
					out.write(buffer);
				}	
				out.flush();
				return;
			}
			
			Blob stuPhoto = null;
			ApplicationContext ctx=WebApplicationContextUtils.getWebApplicationContext(this.getServletContext()); 
			StudentService studentService=   (StudentService)ctx.getBean("studentService");

			List list=studentService.getStuPhoto(cutId);
			if(list!=null&&list.size()>0){
				stuPhoto =(Blob)list.get(0);
			}	
			
			if (stuPhoto == null) {
				//Ã»ÓÐÍ·Ïñ
				ServletOutputStream out = res.getOutputStream();
				FileInputStream fis=new FileInputStream(path+"pages/photo/temp.jpg");  
				byte buffer[] = new byte[512];
				while (fis.read(buffer, 0, 512) != -1) {						
					out.write(buffer);
				}	
				out.flush();
				return;
			} else {
				ServletOutputStream out = res.getOutputStream();
				Blob temp = stuPhoto;
				if(temp==null){
					FileInputStream fis=new FileInputStream(path+"pages/photo/temp.jpg");  
					byte buffer[] = new byte[512];
					while (fis.read(buffer, 0, 512) != -1) {						
						out.write(buffer);
					}	
					out.flush();
					return;
				}
				InputStream is = temp.getBinaryStream();
				byte buffer[] = new byte[512];
				while (is.read(buffer, 0, 512) != -1) {						
					out.write(buffer);
				}		
				out.flush();
			}
							
	} catch(Exception pe) {			
			_log.error(pe);
			pe.printStackTrace();
			ServletOutputStream out = res.getOutputStream();
			FileInputStream fis=new FileInputStream(path+"pages/photo/temp.jpg");  
			byte buffer[] = new byte[512];
			while (fis.read(buffer, 0, 512) != -1) {						
				out.write(buffer);
			}	
			out.flush();
			return;
		}
	}
	
	private static final Log _log = LogFactory.getLog(EcardImageServlet.class);
}
