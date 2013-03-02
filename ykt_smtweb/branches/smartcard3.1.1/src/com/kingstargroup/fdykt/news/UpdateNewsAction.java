package com.kingstargroup.fdykt.news;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.kingstargroup.fdykt.util.DateUtil;

public class UpdateNewsAction extends Action {
	private static final Logger logger = Logger.getLogger(UpdateNewsAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) {
		String forward = "success";
		
		OutputStreamWriter writer = null;
		String news = "";
		try{
			request.setCharacterEncoding("GBK");
			news = request.getParameter("news");
			
			String contextPath = request.getSession().getServletContext().getRealPath("");
			
			String bakPath = contextPath+File.separator+"pages"+File.separator+"bak"+File.separator;
			
			File bakDir = new File(bakPath);
			if(!bakDir.exists()){
				bakDir.mkdir();
			}
			//备份之前正在用的news
			File[] files = bakDir.listFiles();
//			logger.info(files.length);
			for(int i=0;i<files.length;i++){
				String fileName = files[i].getName();
				if(fileName.startsWith("news_") && fileName.endsWith(".txt")){
					files[i].renameTo(new File(files[i].getAbsolutePath()+".bak"));
					logger.info("rename file:"+files[i].getAbsolutePath());
				}
			}
			
			//保存当前输入news
			String currentTime = DateUtil.getNow();
			File bakFile = new File(bakPath+"news_"+currentTime+".txt");
			logger.info(bakPath+"news_"+currentTime+".txt");
			bakFile.createNewFile();
			writer = new OutputStreamWriter(new FileOutputStream(bakFile), "UTF-8"); 
			writer.write(news);
		} catch(Exception e){
			logger.error("保存新闻资讯失败："+e.getMessage());
			request.setAttribute("error", "保存新闻资讯失败："+e.getMessage());
			request.setAttribute("news", news);
			forward = "failure";
		} finally{
			if(writer!=null){
				try {
					writer.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return mapping.findForward(forward);
	}
}
