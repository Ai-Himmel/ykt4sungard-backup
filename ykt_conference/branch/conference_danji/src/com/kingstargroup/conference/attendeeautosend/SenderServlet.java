package com.kingstargroup.conference.attendeeautosend;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

public class SenderServlet extends HttpServlet {
	private AttendeeSender sender;
	private Thread t;

	public void init() throws ServletException {
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
	}

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
}
