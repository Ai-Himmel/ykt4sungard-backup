/**
 * 
 */
package com.kingstargroup.action.bgAnalysis;

import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: testmailandsms.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2006-1-10 何林青 <br>
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class testmailandsms extends Thread implements AnalyzeThreadInterface {

	public void initParam() {
		// TODO Auto-generated method stub

	}

	public void anaylize() {
		// TODO Auto-generated method stub

	}

	public void terminate() {
		// TODO Auto-generated method stub

	}

	public boolean isTerminate() {
		// TODO Auto-generated method stub
		return false;
	}

	public void sendMail() {
		// TODO Auto-generated method stub
			String tmpStr = "";
			String[] tempList = null;
					CommonSendMailUtil.sendMail(GetApplicationResources
							.getInstance().getString(
									"com.kingstar.MonitorSys.SUBJECT_SERIAL"),
							"jackey", "linqing.he@kingstargroup.com", StringUtil
									.wholeMailGenerate("jackey","2006/01/10 00:00:00",
											1, tmpStr,
											"SUPRESS_EXCEPTION"));

	}

	public void sendSMG() {

			String SmgMessage = StringUtil.wholeSMGGenerate("jackey", "2006/01/10 00:00:00", 1, "SUPRESS_EXCEPTION");
			CommonSendSMGUtil.sendSMG("13564319628", SmgMessage);
	}

	public void run() {
		// TODO Auto-generated method stub
		super.run();
		while(true){
			sendMail();
			sendSMG();
			try {
				sleep(120000);

			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
