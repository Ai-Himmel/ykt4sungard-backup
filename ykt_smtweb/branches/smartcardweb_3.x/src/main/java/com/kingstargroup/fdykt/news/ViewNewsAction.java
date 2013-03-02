package com.kingstargroup.fdykt.news;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class ViewNewsAction extends Action {
	private static final Logger logger = Logger.getLogger(ViewNewsAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) {
		String forward = "success";
		
		BufferedReader reader = null;
		List news = new ArrayList();
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
			for(int i=0;i<files.length;i++){
				String fileName = files[i].getName();
				if(fileName.startsWith("news_") && fileName.endsWith(".txt")){
					newsFile = files[i];
				}
			}
			if(newsFile!=null){
				reader = new BufferedReader(new InputStreamReader(new FileInputStream(newsFile), "UTF-8"));
				String line = null;
				while((line=reader.readLine())!=null){
					news.add(line);
				}
			}
			request.setAttribute("news", news);
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
