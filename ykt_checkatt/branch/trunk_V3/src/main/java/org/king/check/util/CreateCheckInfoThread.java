package org.king.check.util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.service.CheckInfoService;
import org.king.framework.service.ServiceLocator;

public class CreateCheckInfoThread {
	private static final Log log = LogFactory.getLog(CreateCheckInfoThread.class);

	private static CheckInfoService checkInfoService;

	/**
	 * ����ǰһ��Ŀ�����Ϣ�Լ�����
	 */
	public static void startCreateCheckInfo(){
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		System.out.println("CheckInfo-��ʼ���ɿ��ڱ����������ڣ� "+yesterday);
		checkInfoService = (CheckInfoService) ServiceLocator.getInstance().getService("checkInfoService");
		try{
			checkInfoService.createCheckInfo(yesterday,yesterday);
			System.out.println("CheckInfo-���ɿ��ڱ���ɹ�");
		}catch(Exception e){
			System.out.println("CheckInfo-���ɿ��ڱ���ʧ�ܣ�"+e.getMessage());
			e.printStackTrace();
		}
	}
	
	/**
	 * @deprecated
	 * @return
	 */
	public synchronized static void openThread() {
	}
	
	/**
	 * @deprecated
	 * @return
	 */
	public synchronized static void stopThread() {
	}
	
	/**
	 * @deprecated
	 * @return
	 */
	public synchronized static boolean isOpen(){
		return false;
	}
}
