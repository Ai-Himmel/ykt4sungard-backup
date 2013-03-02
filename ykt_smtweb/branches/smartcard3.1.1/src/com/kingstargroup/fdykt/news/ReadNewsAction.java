package com.kingstargroup.fdykt.news;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class ReadNewsAction extends Action {
	private static final Logger logger = Logger.getLogger(ReadNewsAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) {
		String fileName = request.getParameter("fileName");
		
		response.setCharacterEncoding("UTF-8");
        PrintWriter writer = null;
        BufferedReader reader = null;
        try {
        	writer = response.getWriter();
            if (StringUtils.isNotBlank(fileName)) {
            	String contextPath = request.getSession().getServletContext().getRealPath("");
    			String bakPath = contextPath+File.separator+"pages"+File.separator+"bak"+File.separator;
                
    			File newsFile = new File(bakPath+"news_"+fileName+".txt");
    			if(newsFile.exists()){
    			} else {
    				newsFile = new File(bakPath+"news_"+fileName+".txt.bak");
    			}
    			//读取文件
    			StringBuffer news = new StringBuffer();
    			if(newsFile.exists()){
    				reader = new BufferedReader(new InputStreamReader(new FileInputStream(newsFile), "UTF-8"));
    				String line = null;
    				while((line=reader.readLine())!=null){
    					news.append(line).append("\r\n");
    				}
    			}
                writer.write(news.toString());
                writer.flush();
            } else {
                writer.write("error:请选择日期！");
            }
        } catch (Exception e) {
        	logger.error(e.getMessage());
            writer.write("error:" + e.getMessage());
        } finally{
			if(reader!=null){
				try {
					reader.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
        return null;
	}
}
