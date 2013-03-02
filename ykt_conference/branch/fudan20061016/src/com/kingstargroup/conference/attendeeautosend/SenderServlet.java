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
			System.out.println("ϵͳ�ļ�web.xml�����������ͳ����ʼ��ʧ�ܣ�");
			return;
		}

		if (time != null) {
			sender.setTime(Integer.parseInt(time));
		}
		t = new Thread(sender);
		t.start(); // �������������߳�
		System.out.println("ϵͳ�Ѿ����������Զ�����=========================");
	}

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
}
