/**
 * 
 */
package com.kingstargroup.fdykt;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Blob;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dto.NewCardInfoDTO;


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
		String conferencepath = KSConfiguration.getInstance().getProperty("tempjpgpath","/opt/tomcat5/smartcardweb");
		String suffix = "/pages/changecard/temp.jpg";
		try {
			String custid = req.getParameter("custid");
			res.setContentType("image/jpg");
			if (custid!=null) {			
				DB2CustomerDAO customerDAO = new DB2CustomerDAO();
				NewCardInfoDTO newcardinfodto = customerDAO.getPhoto(custid);
				if(newcardinfodto!=null){
					Blob temp = newcardinfodto.getMinphoto();
					ServletOutputStream out = res.getOutputStream();
					InputStream fis = temp.getBinaryStream();
					byte buffer[] = new byte[256];
					while (fis.read(buffer, 0, 256) != -1) {						
						out.write(buffer);
					}	
					out.flush();
					return;
				}else{
					ServletOutputStream out = res.getOutputStream();
					FileInputStream fis=new FileInputStream(conferencepath+suffix); 
					byte buffer[] = new byte[256];
					while (fis.read(buffer, 0, 256) != -1) {						
						out.write(buffer);
					}	
					out.flush();
					return;
				}
				
			}
			
		} catch(Exception pe) {			
			_log.error(pe);
			pe.printStackTrace();
			ServletOutputStream out = res.getOutputStream();
			FileInputStream fis=new FileInputStream(conferencepath+suffix); 
			byte buffer[] = new byte[256];
			while (fis.read(buffer, 0, 256) != -1) {						
				out.write(buffer);
			}	
			out.flush();
			return;
		}
	}
	
	private static final Log _log = LogFactory.getLog(EcardImageServlet.class);
}
