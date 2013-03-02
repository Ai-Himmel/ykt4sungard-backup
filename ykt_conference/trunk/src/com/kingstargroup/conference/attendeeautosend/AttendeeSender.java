package com.kingstargroup.conference.attendeeautosend;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class AttendeeSender implements Runnable {
	private int time = 5 * 60 * 1000; // 扫描数据库时间间隔

	private boolean flag = true; // 停止线程标记

	public void setTime(int minute) {
		this.time = minute * 60 * 1000;
	}

	public void run() {
		// 保存前一次发送名单的时间
		long lastTime = new Date().getTime();
		// 服务器停止时退出线程
		while (flag) {
			long k = new Date().getTime() - lastTime;
			// 防止系统修改时间
			if (k < -1000) {
				lastTime = new Date().getTime();
				continue;
			}
			// 超过设定时间间隔开始发送名单
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
	 * 检索数据库，下发人员名单
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
					System.out.print("跳过，没有要下发的会议====\n");
					continue;
				}else{
					AttendeeUtil.addMesListByConfId(Integer.parseInt(conf.getConId().toString()));
				}
			}
			// Session session = Session.getInstance(getProperties(),new
			// Authentic());
			// while (flag) {// 服务器停止时退出线程
			// sendMail(session, toAddress, subject, content, file);// 发送名单
			// }
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
		}
	}

}
