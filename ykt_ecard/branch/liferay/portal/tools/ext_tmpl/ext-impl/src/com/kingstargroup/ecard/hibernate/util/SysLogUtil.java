package com.kingstargroup.ecard.hibernate.util;

import org.hibernate.HibernateException;

import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.hibernate.subsyslog.SysLogPersistence;
import com.kingstargroup.ecard.hibernate.subsyslog.TSubsysLog;
import com.liferay.portal.PortalException;

public class SysLogUtil {


		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: AccountUtil��¼��¼��־<br>
		 * Return: void<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-5-19  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
		public static void loginInfo(String stuempno)throws PortalException{
			try {
				String dateTime = SysDateUtil.getSysDate(0);
				String operateDate = dateTime.substring(0, 8);
				String operateTime = dateTime.substring(8);
				TSubsysLog log = new TSubsysLog();
				if("admin".equals(stuempno)){
					log.setCustId(Long.valueOf("0"));
					log.setLoginName("admin");
				}else{
					TCustomer cust = CustomerUtil.getCustomerByStuempno(stuempno);
					if(null==cust){
						log.setCustId(Long.valueOf("0"));
						log.setLoginName("");
					}else{
						log.setCustId(cust.getCustid());
						log.setLoginName(cust.getCustname());
					}	
				}					
				log.setLogDate(operateDate);
				log.setLogTime(operateTime);
				log.setSussysId(new Integer(2000));
				log.setComments(stuempno+"["+operateDate+operateTime+"]:�ɹ���¼�ۺϲ�ѯϵͳ");
				getPersistence().save(log);
			} catch (HibernateException dbse) {
				dbse.printStackTrace();
				throw dbse;
			}catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}
		
		
		
		public static SysLogPersistence getPersistence() {
			
			return _getUtil()._persistence;
		}

		public void setPersistence(SysLogPersistence persistence) {
			_persistence = persistence;
		}

		private static SysLogUtil _getUtil() {
			if (_util == null) {
				_util = (SysLogUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
			}

			return _util;
		}

		private static final String _UTIL = SysLogUtil.class.getName();
		private static SysLogUtil _util;
		private SysLogPersistence _persistence;



}
