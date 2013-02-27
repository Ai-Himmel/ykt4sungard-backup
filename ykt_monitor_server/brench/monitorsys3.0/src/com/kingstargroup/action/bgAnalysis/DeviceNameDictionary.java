/**
 * 
 */
package com.kingstargroup.action.bgAnalysis;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.TDevice;
import com.kingstargroup.utils.DateUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DeviceNameDictionary.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-7-17     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class DeviceNameDictionary {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DeviceNameDictionary.class);


	private Map HashMap_deviceName = new HashMap();
	private Map HashMap_deviceType = new HashMap();
	String timeStamp ="";
	
	private static DeviceNameDictionary instance = null;
	private static Object mutex = new Object();
	
	/**
	 * 
	 */
	private DeviceNameDictionary() {
		initDictionary();
	}
	static public DeviceNameDictionary getInstance(){
		synchronized(mutex){
			if(null == instance){
				//
				instance = new DeviceNameDictionary();
			}
		}
		return instance;
	}
	
	/**
	 * @param deviceId
	 * @return �豸����
	 * 
	 */
	public String get(String deviceId){
		if(checkTimeStamp()){
			initDictionary();
		}
		String ret ="";
		if(HashMap_deviceName.get(deviceId)!=null){
			ret = (String)HashMap_deviceName.get(deviceId);
		}

		return ret;
	}
	
	/**
	 * @param deviceId
	 * @return �豸����
	 */
	public String getType(String deviceId){
		if(checkTimeStamp()){
			initDictionary();
		}
		String ret ="";
		if(HashMap_deviceType.get(deviceId)!=null){
			ret = (String)HashMap_deviceType.get(deviceId);
		}

		return ret;
	}
	
	private boolean checkTimeStamp(){

		if(DateUtil.checkIntervalTime(timeStamp,DateUtil.getNow(),24*3600)>0){
			return false;
		}else{
			return true;
		}
	}
	
	private void initDictionary(){
		if (logger.isInfoEnabled()) {
			logger.info("�豸�����ֵ��ʼ��");
		}

		try {
			timeStamp = DateUtil.getNow();
			HashMap_deviceName.clear();
			HashMap_deviceType.clear();
			Session session = HibernateSessionFactory.currentSession();//����ͬһ��session ����Ҫ������ر�
			List devList = null;
			Query dev_query = session.createSQLQuery("select {dev.*} from ykt_cur.t_device dev where dev.status=1").addEntity("dev",TDevice.class);
			devList = dev_query.list();
			Iterator dev_iter = devList.iterator();
			while(dev_iter.hasNext()){
				TDevice device = (TDevice)dev_iter.next();
				HashMap_deviceName.put(device.getDevphyid(),device.getDevicename());
				HashMap_deviceType.put(device.getDevphyid(), device.getDevtypecode());
			}

		} catch (HibernateException e) {
			logger.error("�豸�����ֵ��ʼ��ʧ��", e);

		} 

		if (logger.isInfoEnabled()) {
			logger.info("�豸�����ֵ��ʼ���ɹ���");
		}
	}
	

	
	
}
