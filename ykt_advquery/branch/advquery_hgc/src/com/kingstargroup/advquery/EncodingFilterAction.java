package com.kingstargroup.advquery;

import java.io.EOFException;

import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionServlet;

import com.kingstargroup.advquery.hibernate.dao.BasicDAO;

public class EncodingFilterAction  extends ActionServlet{
	
	public void process(HttpServletRequest request, HttpServletResponse response) throws EOFException ,ServletException {
		try{
		super.process(request,response);
		request.setCharacterEncoding("GBK");
		}catch(Exception e){
			_log.error(e);
		}
	}
	Log _log = LogFactory.getLog(EncodingFilterAction.class.getClass());

}
