package com.kingstargroup.mobileMessage.util;



import org.apache.log4j.Logger;

import com.kingstargroup.mobileMessage.util.SCMMessageUtil;

public class SCMSendMessage extends Thread {

	//private static boolean SisRunning = false; // send flag
	private long seconds = KSConfiguration.getInstance().getPropertyAsInt("sendSeconds",10);
	
	public void run() {
		while(true){
		try{
		Thread.sleep(seconds*1000);
		}catch(InterruptedException e)
		{
		}
		/*if (!SisRunning) {// seng and receive all are not true
			SisRunning = true;*/
			//log.error("-------------"+Thread.currentThread().getName());
			log.info("---��ʼִ�з�������----");
			if (!SCMMessageUtil.BeginSendMessages()) {
				log.info("---��������ʧ��----");
			} else {
				log.info("---ִ�з��ͳɹ�--����s_pro--");
			} 
			if(!SCMMessageUtil.insertRCMMessages()){
				log.info("---������ն���ʧ��----");
			}else{
				log.info("---������ն��ųɹ�----");
			}
			if (!SCMMessageUtil.updateSuccessMessage()) {
				log.info("----��ȡ��Ϣ���ͷ�����Ϣʧ��----");
			} else {
				log.info("----��ȡ��Ϣ���ͷ�����Ϣ�ɹ�--����s_success---");
			}
		
			/*SisRunning = false;
		}*/
		}
	}

	private Logger log = Logger.getLogger(SCMSendMessage.class);
}
