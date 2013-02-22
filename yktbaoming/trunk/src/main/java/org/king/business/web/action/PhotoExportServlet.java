/**
 * 
 */
package org.king.business.web.action;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringBufferInputStream;
import java.io.StringReader;
import java.sql.Blob;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

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
import org.king.security.util.LdapFromSunDS;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;
import org.springframework.context.ApplicationContext;
import org.springframework.web.context.support.WebApplicationContextUtils;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * @author jeffxiao
 *
 */
public class PhotoExportServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {
				
		String[] fileName=null;
		
		try {
						
			LdapFromSunDS ldap = new LdapFromSunDS();
	 		ldap.init("");
	 	    
	 		String path=ldap.getPreference("constant.stuphoto.path");
			
			Blob stuPhoto = null;
			ApplicationContext ctx=WebApplicationContextUtils.getWebApplicationContext(this.getServletContext()); 
			StudentService studentService=   (StudentService)ctx.getBean("studentService");

			List list=studentService.find("select new Map(stubm.bmStudent.studentNo as studentNo,cif.id.photo as photo) from TCifPhoto cif,TCifCustomer cut,BmStuBm stubm where cif.id.cutId=cut.cutId and cut.stuempNo=stubm.bmStudent.studentNo and (stubm.bmTest.testDate is null or stubm.bmTest.testDate='' or stubm.bmTest.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"') and stubm.ifBm='"+Constants.yesCode+"' and stubm.bmTest.bmTestCat.ifFee='"+Constants.yesCode+"' and stubm.ifPay='"+Constants.yesCode+"'");
			List listnotfee=studentService.find("select new Map(stubm.bmStudent.studentNo as studentNo,cif.id.photo as photo) from TCifPhoto cif,TCifCustomer cut,BmStuBm stubm where cif.id.cutId=cut.cutId and cut.stuempNo=stubm.bmStudent.studentNo and (stubm.bmTest.testDate is null or stubm.bmTest.testDate='' or stubm.bmTest.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"') and stubm.ifBm='"+Constants.yesCode+"' and stubm.bmTest.bmTestCat.ifFee='"+Constants.noCode+"'");
			
			if(list==null)
				list=new ArrayList();
				
			if(listnotfee!=null&&listnotfee.size()>0){
				for(int i=0;i<listnotfee.size();i++){
					Map notfeem=(Map)listnotfee.get(i);
					list.add(notfeem);
				}
			}
			
			if(list!=null&&list.size()>0){	
				
//				res.setContentType("application/octet-stream"); 
//				res.setHeader("Content-Disposition","attachment;filename=stuphoto.zip");
				res.setContentType("application/x-msdownload");
				res.setHeader("Content-Disposition","attachment;filename=stuphoto.txt");
				
				fileName=new String[list.size()];
				for(int i=0;i<list.size();i++){	
					Map stuphoto=(Map)list.get(i);
					String studentNo=(String)stuphoto.get("studentNo");
				    stuPhoto =(Blob)stuphoto.get("photo");
				    BufferedOutputStream bufferout=null;
				    if (stuPhoto != null) {
				    	String fName=path+studentNo+".jpg";
				    	bufferout= new BufferedOutputStream(new FileOutputStream(fName)); 
                        Blob temp = stuPhoto;
						InputStream is = temp.getBinaryStream();
						byte buffer[] = new byte[512];
						while (is.read(buffer, 0, 512) != -1) {						
							bufferout.write(buffer);
						}		
						bufferout.flush();	
						bufferout.close();
						is.close();
						fileName[i]=fName;
					}
				}
				//压缩成zip
//				String zipfile="";
//				ServletOutputStream out=res.getOutputStream();
//				ZipOutputStream zipout=new ZipOutputStream(out);
//				byte zip[]=new byte[256];   
//				for(int i=0;i<fileName.length;i++){  
//				    if(zipfile.indexOf(fileName[i])==-1){//过滤重复照片
//			            zipfile=zipfile+fileName[i]+",";
//				    	InputStream in=new FileInputStream(fileName[i]);   
//			            ZipEntry e=new ZipEntry(fileName[i].replace(File.separatorChar,'/'));   
//			            zipout.putNextEntry(e);   
//			            int len=0;   
//			            while((len=in.read(zip))!=-1){
//			                zipout.write(zip,0,len);   
//			            }
//			            in.close();
//				    }
//				}
//				zipout.closeEntry();
//				zipout.close();	
//				out.close();
				
				//生成含有照片地址的txt
				if(path!=null){
					ServletOutputStream out=res.getOutputStream();
	                BufferedReader sr=new BufferedReader(new StringReader("照片已从数据库导出，保存在服务器路径："+path+"，本批照片导出日期为 "+DateUtil.getNow("yyyy-MM-dd")));   
					
				    String ostring=sr.readLine();
				    while (ostring!=null){
				    	out.write(ostring.getBytes());
				    	ostring=sr.readLine();
				    }
				}
				else{
					ServletOutputStream out=res.getOutputStream();
					BufferedReader sr=new BufferedReader(new StringReader("服务器上文件夹stuphoto不存在，无法保存照片。"));   
					
				    String ostring=sr.readLine();
				    while (ostring!=null){
				    	out.write(ostring.getBytes());
				    	ostring=sr.readLine();
				    }
				}
			    
			}
			else{
				res.setContentType("application/x-msdownload");
				res.setHeader("Content-Disposition","attachment;filename=stuphoto.txt");
				
				ServletOutputStream out=res.getOutputStream();
				BufferedReader sr=new BufferedReader(new StringReader("没有新照片。"));   
				
			    String ostring=sr.readLine();
			    while (ostring!=null){
			    	out.write(ostring.getBytes());
			    	ostring=sr.readLine();
			    }

			}
										
	} catch(Exception pe) {
			_log.error(pe);			
			pe.printStackTrace();	
			res.setContentType("application/x-msdownload");
			res.setHeader("Content-Disposition","attachment;filename=stuphoto.txt");
			
			ServletOutputStream out=res.getOutputStream();
			BufferedReader sr=new BufferedReader(new StringReader("照片生成过程中有错误。"));   
			
		    String ostring=sr.readLine();
		    while (ostring!=null){
		    	out.write(ostring.getBytes());
		    	ostring=sr.readLine();
		    }
			return;
		}
	}
	
	private static final Log _log = LogFactory.getLog(PhotoExportServlet.class);
}
