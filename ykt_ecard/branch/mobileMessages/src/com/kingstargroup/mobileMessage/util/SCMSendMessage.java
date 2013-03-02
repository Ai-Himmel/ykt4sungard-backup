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
			log.info("---开始执行发送数据----");
			if (!SCMMessageUtil.BeginSendMessages()) {
				log.info("---发送数据失败----");
			} else {
				log.info("---执行发送成功--更新s_pro--");
			} 
			if(!SCMMessageUtil.insertRCMMessages()){
				log.info("---保存接收短信失败----");
			}else{
				log.info("---保存接收短信成功----");
			}
			if (!SCMMessageUtil.updateSuccessMessage()) {
				log.info("----获取信息发送返回信息失败----");
			} else {
				log.info("----获取信息发送返回信息成功--更新s_success---");
			}
		
			/*SisRunning = false;
		}*/
		}
	}

	private Logger log = Logger.getLogger(SCMSendMessage.class);
}
