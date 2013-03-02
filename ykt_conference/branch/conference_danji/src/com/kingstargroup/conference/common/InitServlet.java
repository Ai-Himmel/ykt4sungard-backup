/**
 * 
 */
package com.kingstargroup.conference.common;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import com.kingstargroup.conference.attendeeautosend.AttendeeSender;
import com.kingstargroup.conference.util.FuncListUtil;
import com.kingstargroup.conference.util.OperatorUtil;

/**
 * @author hjw
 *
 */
public class InitServlet extends HttpServlet {
	//private AttendeeSender sender;
	//private Thread t;

	/**
	 * 
	 */
	private static final long serialVersionUID = 233660845301654380L;

	/* (non-Javadoc)
	 * @see javax.servlet.GenericServlet#init(javax.servlet.ServletConfig)
	 */
	public void init(ServletConfig sc) throws ServletException {
		super.init(sc);
		System.out.println("====== Starting initialize hibernate session factory ======");
		com.kingstargroup.conference.hibernate.HibernateSessionFactory.init();
		System.out.println("====== Initialize hibernate session factory successfully ======");
		System.out.println("====== Starting construct module JS tree ======");
		getServletContext().setAttribute(WebKeys.MODULE_JS_TREE, FuncListUtil.createJSTree());
		System.out.println("====== Construct module JS tree successfully ======");
		getServletContext().setAttribute(WebKeys.DEPT_JS_TREE,OperatorUtil.createDeptJSList("NA"));
		System.out.println("====== Construct dept JS tree successfully ======");
		/** 
		sender = new AttendeeSender();
		String time = getInitParameter("time");
		if (time == null) {
			System.out.println("系统文件web.xml错误：名单发送程序初始化失败！");
			return;
		}

		if (time != null) {
			sender.setTime(Integer.parseInt(time));
		}
		t = new Thread(sender);
		t.start(); // 启动名单发送线程
		System.out.println("系统已经启动名单自动发送=========================");
		**/
	}
	/**
	public void destroy() {
		sender.stop(); //停止邮件发送线程
		try {
			t.join(1000);
			if (t.isAlive()) {
				System.out.println("名单发送线程未停止。");
			}
		} catch (Exception e) {
		}
	}
**/
	
}
