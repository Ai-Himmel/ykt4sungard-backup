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
			System.out.println("ϵͳ�ļ�web.xml�����������ͳ����ʼ��ʧ�ܣ�");
			return;
		}

		if (time != null) {
			sender.setTime(Integer.parseInt(time));
		}
		t = new Thread(sender);
		t.start(); // �������������߳�
		System.out.println("ϵͳ�Ѿ����������Զ�����=========================");
		**/
	}
	/**
	public void destroy() {
		sender.stop(); //ֹͣ�ʼ������߳�
		try {
			t.join(1000);
			if (t.isAlive()) {
				System.out.println("���������߳�δֹͣ��");
			}
		} catch (Exception e) {
		}
	}
**/
	
}
