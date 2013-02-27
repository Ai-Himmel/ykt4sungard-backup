package com.kingstargroup;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.kingstargroup.action.bgAnalysis.BgMonitor;
import com.kingstargroup.commons.HibernateSessionFactory;

public class initServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public initServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occure
	 */
	public void init() throws ServletException {
		if(HibernateSessionFactory.initSessionFactory()==false){
			System.out.println("sessionFactory inital failure!");
			throw new ServletException();
		}else{
//			SystemStateAnalysisForUnix a = new SystemStateAnalysisForUnix();
//			a.start();
			BgMonitor.getIntance().newAnalyzeIntance();
//			String file = this.getInitParameter("database");
//			SqlStatementDictionary.getIntance().load(file);
//			 Put your initial code here

		}		
	}

}
