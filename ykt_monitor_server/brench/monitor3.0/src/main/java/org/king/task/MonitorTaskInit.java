package org.king.task;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.quartz.SchedulerException;

/**
 * @author Linqing.He
 * 描述：监控任务初始化
 *
 */
public class MonitorTaskInit extends HttpServlet{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private static Log log = LogFactory.getLog(MonitorTaskInit.class);
	
	
	@Override
	public void init() throws ServletException {
		try {
			MonitorTaskDelegate task  = MonitorTaskDelegate.getinstance();
			task.LoadAllMonitorTask();
			MonitorTaskDelegate.sched.start();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("系统任务启动失败！");
		}
	}
	
	@Override
	public void destroy() {
		try {
			System.out.println("system go down we shut down the schedule!");
			MonitorTaskDelegate.sched.shutdown(false);
			System.out.println("schedule be setted down!");
		} catch (SchedulerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public final void service(final HttpServletRequest request,
			final HttpServletResponse response) throws ServletException,
			IOException {
		
		
	}
	

}
