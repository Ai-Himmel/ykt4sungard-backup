/**
 * 
 */
package org.king.check.util;

import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.configuration.reloading.FileChangedReloadingStrategy;


/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: GetPropertiesUtil.java<br>
 * Description: <br>
 * Modify History����Change Log��:  <br>
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���<br>
 * ����  				 2005-11-7  ������    <br>
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class GetPropertiesUtil {
	private static PropertiesConfiguration instance = null;
	private static FileChangedReloadingStrategy fcrs = null;
	private static Object mutex = new Object();

	/**
	 * 
	 */
	private GetPropertiesUtil() {
		super();
		// TODO Auto-generated constructor stub
	}
	public static PropertiesConfiguration getInstance(){
		synchronized (mutex) {
			if(null==instance){
				try {
					instance= new PropertiesConfiguration("SendMail.properties");
					fcrs = new FileChangedReloadingStrategy();
					instance.setReloadingStrategy(fcrs);
				} catch (ConfigurationException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		return instance;
	}
	
	public static boolean fileChanged(){
		synchronized (mutex) {
			if(null==instance){
				instance = getInstance();
			}
		}
		return fcrs.reloadingRequired();
	}
	
}
