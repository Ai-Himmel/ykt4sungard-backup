/**
 * 
 */
package com.kingstargroup.conference.action;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Blob;
import java.util.HashMap;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.kingstargroup.CONSTANT;
import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.StringPool;
import com.kingstargroup.conference.common.WebKeys;
import com.kingstargroup.conference.hibernate.form.TCifPhoto;
import com.kingstargroup.conference.util.AnalyseUtil;

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
		String tempjpg = CONSTANT.TEMPJPG;
		try {
			String conId = req.getParameter("confid");
			String id = req.getParameter("id");
			String zerostuempNo = req.getParameter("stuempNo");
//			String attendeetime = req.getParameter("attendtime");			
			String username = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_NAME), StringPool.BLANK);
			res.setContentType("image/jpg");
			if (username.equals(StringPool.BLANK)) {
				ServletOutputStream out = res.getOutputStream();
				FileInputStream fis=new FileInputStream(tempjpg);  
				byte buffer[] = new byte[256];
				while (fis.read(buffer, 0, 256) != -1) {						
					out.write(buffer);
				}	
				out.flush();
				return;
			}
			if(conId!=null&&!"".equals(conId)){
					//第一次请求
					List attList = AnalyseUtil.getPicAttendeeList(conId, "", "0");
					if("0".equals(id)){
						if(attList!=null&&attList.size()>0){
							HashMap iter = (HashMap)attList.get(0);
							String custId = (String)iter.get("custId");
							String stuempNo = zerostuempNo;
							TCifPhoto photo = null;
							if(!"FUDAN".equals(CONSTANT.VERSION)){
								photo = AnalyseUtil.getCifPhoto(Integer.valueOf(custId));
							}else{
								photo = AnalyseUtil.getfudanCifPhoto(stuempNo);
							}
							if (photo == null) {
								//没有头像
								ServletOutputStream out = res.getOutputStream();
								FileInputStream fis=new FileInputStream(tempjpg);  
								byte buffer[] = new byte[256];
								while (fis.read(buffer, 0, 256) != -1) {						
									out.write(buffer);
								}	
								out.flush();
								return;
							} else {
								ServletOutputStream out = res.getOutputStream();
								Blob temp = photo.getMinphoto();
								if(temp==null){
									FileInputStream fis=new FileInputStream(tempjpg);  
									byte buffer[] = new byte[256];
									while (fis.read(buffer, 0, 256) != -1) {						
										out.write(buffer);
									}	
									out.flush();
									return;
								}
								InputStream is = temp.getBinaryStream();
								byte buffer[] = new byte[256];
								while (is.read(buffer, 0, 256) != -1) {						
									out.write(buffer);
								}		
								out.flush();
							}
							
						}else{
							ServletOutputStream out = res.getOutputStream();
							FileInputStream fis=new FileInputStream(tempjpg);  
							byte buffer[] = new byte[256];
							while (fis.read(buffer, 0, 256) != -1) {						
								out.write(buffer);
							}	
							out.flush();
							return;
						}
					}else{
						if(attList!=null&&attList.size()>0){
							int pos = Integer.parseInt(id);
							if(pos<attList.size()){
								HashMap iter = (HashMap)attList.get(pos);
								String custId = (String)iter.get("custId");
								String stuempNo = (String)iter.get("stuempNo");
								TCifPhoto photo = null;
								if(!"FUDAN".equals(CONSTANT.VERSION)){
									photo = AnalyseUtil.getCifPhoto(Integer.valueOf(custId));
								}else{
									photo = AnalyseUtil.getfudanCifPhoto(stuempNo);
								}
							
								if (photo == null) {
									//没有头像
									ServletOutputStream out = res.getOutputStream();
									FileInputStream fis=new FileInputStream(tempjpg);  
									byte buffer[] = new byte[256];
									while (fis.read(buffer, 0, 256) != -1) {						
										out.write(buffer);
									}	
									out.flush();
									return;
								} else {
									ServletOutputStream out = res.getOutputStream();
									Blob temp = photo.getMinphoto();
									if(temp==null){
										FileInputStream fis=new FileInputStream(tempjpg);  
										byte buffer[] = new byte[256];
										while (fis.read(buffer, 0, 256) != -1) {						
											out.write(buffer);
										}	
										out.flush();
										return;
									}
									InputStream is = temp.getBinaryStream();
									byte buffer[] = new byte[256];
									while (is.read(buffer, 0, 256) != -1) {						
										out.write(buffer);
									}		
									out.flush();
								}
								
							}else{
								ServletOutputStream out = res.getOutputStream();
								FileInputStream fis=new FileInputStream(tempjpg);  
								byte buffer[] = new byte[256];
								while (fis.read(buffer, 0, 256) != -1) {						
									out.write(buffer);
								}	
								out.flush();
								return;
							}
						}else{
							ServletOutputStream out = res.getOutputStream();
							FileInputStream fis=new FileInputStream(tempjpg);  
							byte buffer[] = new byte[256];
							while (fis.read(buffer, 0, 256) != -1) {						
								out.write(buffer);
							}	
							out.flush();
							return;
						}
					}
			}
			
		} catch(Exception pe) {			
			_log.error(pe);
			pe.printStackTrace();
			ServletOutputStream out = res.getOutputStream();
			FileInputStream fis=new FileInputStream(tempjpg);  
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
