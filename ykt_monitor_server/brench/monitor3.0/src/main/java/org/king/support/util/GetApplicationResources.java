/**
 * 
 */
package org.king.support.util;

import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.configuration.reloading.FileChangedReloadingStrategy;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: GetApplicationResources.java<br>
 * Description: <br>
 * Modify History����Change Log��:  <br>
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���<br>
 * ����  				 2005-11-9  ������    <br>
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class GetApplicationResources {
	private static PropertiesConfiguration instance = null;
	private static Object mutex = new Object();

	/**
	 * 
	 */
	public static PropertiesConfiguration getInstance(){
		synchronized (mutex) {
			if(null==instance){
				try {
					instance= new PropertiesConfiguration("ApplicationResources.properties");
				} catch (ConfigurationException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		return instance;
	}

}
