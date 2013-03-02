package com.kingstargroup.fdykt.news;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class ModifyNewsAction extends Action {
	private static final Logger logger = Logger.getLogger(ModifyNewsAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) {
		String forward = "success";
		
		//检验该用户是否具备修改news的权限，登录用户名，密码固定
		String admin = (String) request.getSession(true).getAttribute("admin");
		if(!"admin".equals(admin)){
			return mapping.findForward("newslogin");
		}
		
		BufferedReader reader = null;
		StringBuffer news = new StringBuffer();
		try{
			
			String contextPath = request.getSession().getServletContext().getRealPath("");
			
			String bakPath = contextPath+File.separator+"pages"+File.separator+"bak"+File.separator;
			
			//读取有效news
			File bakDir = new File(bakPath);
			if(!bakDir.exists()){
				bakDir.mkdir();
			}
			File[] files = bakDir.listFiles();
//			logger.info(files.length);
			File newsFile = null;
			List fileNames = new ArrayList();
			for(int i=0;i<files.length;i++){
				String fileName = files[i].getName();
				if(fileName.startsWith("news_") && fileName.endsWith(".txt")){
					newsFile = files[i];
					fileNames.add(fileName.substring(5,fileName.length()-4));
				} else if(fileName.startsWith("news_") && fileName.endsWith(".txt.bak")){
					fileNames.add(fileName.substring(5,fileName.length()-8));
				}
			}
			Collections.sort(fileNames);
			Collections.reverse(fileNames);
			if(newsFile!=null){
				reader = new BufferedReader(new InputStreamReader(new FileInputStream(newsFile), "UTF-8"));
				String line = null;
				while((line=reader.readLine())!=null){
					news.append(line).append("\r\n");
				}
			}
			request.setAttribute("news", news);
			request.setAttribute("fileNames", fileNames);
		} catch(Exception e){
			logger.error("读取新闻资讯失败："+e.getMessage());
			request.setAttribute("error", "读取新闻资讯失败："+e.getMessage());
			request.setAttribute("news", news);
		} finally{
			if(reader!=null){
				try {
					reader.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return mapping.findForward(forward);
	}
}
