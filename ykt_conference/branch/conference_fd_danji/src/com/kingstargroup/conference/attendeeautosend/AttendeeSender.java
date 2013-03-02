package com.kingstargroup.conference.attendeeautosend;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class AttendeeSender implements Runnable {
	private int time = 5 * 60 * 1000; // ɨ�����ݿ�ʱ����

	private boolean flag = true; // ֹͣ�̱߳��

	public void setTime(int minute) {
		this.time = minute * 60 * 1000;
	}

	public void run() {
		// ����ǰһ�η���������ʱ��
		long lastTime = new Date().getTime();
		// ������ֹͣʱ�˳��߳�
		while (flag) {
			long k = new Date().getTime() - lastTime;
			// ��ֹϵͳ�޸�ʱ��
			if (k < -1000) {
				lastTime = new Date().getTime();
				continue;
			}
			// �����趨ʱ������ʼ��������
			if (k > time) {
				sendData();
				lastTime = new Date().getTime();
			}
			try {
				Thread.sleep(100);
			} catch (Exception e) {
			}
		}
	}

	public void stop() {
		flag = false;
	}

	/**
	 * �������ݿ⣬�·���Ա����
	 */
	private void sendData() {
		String signTime = DateUtilExtend.getNowTime2();
		try {
			List confList = ConferenceUtil.getAllotAttendeeConfByDate();
			Iterator iter = confList.iterator();
			while (iter.hasNext() && flag) {
				TConference conf = (TConference) iter.next();
				if ((DateUtilExtend.timeDiff2(signTime,conf.getConSigntime())>3)
						||(DateUtilExtend.timeDiff2(conf.getConSigntime(),signTime)>3)){
					System.out.print("������û��Ҫ�·��Ļ���====\n");
					continue;
				}else{
					AttendeeUtil.addMesListByConfId(Integer.parseInt(conf.getConId().toString()));
				}
			}
			// Session session = Session.getInstance(getProperties(),new
			// Authentic());
			// while (flag) {// ������ֹͣʱ�˳��߳�
			// sendMail(session, toAddress, subject, content, file);// ��������
			// }
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
		}
	}

}
