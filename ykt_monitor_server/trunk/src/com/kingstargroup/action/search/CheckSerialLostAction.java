/**
 * 
 */
package com.kingstargroup.action.search;

import org.apache.log4j.Logger;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
//import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: CheckSerialLostAction.java<br>
 * Description: <br>
 * Modify History（或Change Log）:  <br>
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述<br>
 * 创建  				 2005-11-4  何林青    <br>
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
public class CheckSerialLostAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckSerialLostAction.class);

	/**
	 * 
	 */
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			String deviceID = request.getParameter("DeviceID");
			String serialStatus = request.getParameter("SerialStatus");
			String contactName = request.getParameter("ContactName");
			String startTime = request.getParameter("StartTime");
			String endTime = request.getParameter("EndTime");
			String serialReason = request.getParameter("SerialReason");
			String lastFlag = request.getParameter("lastanalysis");
			String startCount = request.getParameter("StartCount");

			StringBuffer sqlBuff = new StringBuffer();
			sqlBuff.append("from MapSerialostTable  serial where 1=1 ");
			if (!"".equals(deviceID)&&null!=deviceID) {
				sqlBuff.append("and serial.id.deviceId = :deviceID ");
			}		
			if (!"".equals(serialStatus)&&null!=serialStatus&&!"-".equals(serialStatus)) {
				sqlBuff.append("and serial.serialStatus = :serialStatus ");
			}
			if (!"".equals(contactName)&&null!=contactName) {
				sqlBuff.append("and serial.contactname like :contactName ");
			}
			
			if (!"".equals(lastFlag) && null != lastFlag) {
				if ("1".equals(lastFlag)) {
					// ToDo:checked----to get the last version of result
					sqlBuff.append("and serial.id.analysistime >= :startTime ");
					sqlBuff.append("and serial.id.analysistime <= :endTime ");
				} else {
					// ToDo:unchecked
					if (!"".equals(startTime)&&null!=startTime) {
						sqlBuff.append("and concat(serial.txDate,serial.txTime) >= :startTime ");
					}
					if (!"".equals(endTime)&&null!=endTime) {
						sqlBuff.append("and concat(serial.txDate,serial.txTime) <= :endTime ");
					}
				}
			}
			
			
			if (!"".equals(serialReason)&&null!=serialReason&&!"-".equals(serialReason)) {
				sqlBuff.append(" and serial.serialReason = :serialReason ");
			}

			try {
//				MessageResources msgResources = (MessageResources) this
//						.getServlet().getServletContext().getAttribute(
//								Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				
				Query queryTime = session.createQuery("select a.value from MapParamTable a,MapSysDictionary b where a.parameter=b.dictCode and b.id.dictNo=:dictNo and b.id.dictValue=:dictValue");
				if (!"".equals(serialReason)&&null!=serialReason&&!"-".equals(serialReason)) {
					queryTime.setInteger("dictNo",2);
					queryTime.setString("dictValue",serialReason);	
				}else{
					queryTime.setInteger("dictNo",0);
					queryTime.setString("dictValue","0");	
				}
							
				List listTime = queryTime.list();
				String dateTime = DateUtil.getNow();
				int intevalTime = 0;
				if(listTime.size()>0){
					intevalTime = (int)(Float.parseFloat(listTime.get(0).toString())*60*60*-1);
				}else{
					intevalTime = -1*60*60;
				}	
				
				
				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());	
				
				if (!"".equals(deviceID)&&null!=deviceID) {
					query.setString("deviceID",deviceID);
				}		
				if (!"".equals(serialStatus)&&null!=serialStatus&&!"-".equals(serialStatus)) {
					query.setInteger("serialStatus",Integer.parseInt(serialStatus));
				}
				if (!"".equals(contactName)&&null!=contactName) {
					contactName = "%"+contactName+"%";
					query.setString("contactName",contactName);
				}
				if (!"".equals(lastFlag) && null != lastFlag) {
					if ("1".equals(lastFlag)) {
						// ToDo:checked----to get the last version of result
							query.setString("startTime",DateUtil.getNewTime(dateTime,intevalTime));	
							query.setString("endTime",dateTime);
					} else {
						// ToDo:unchecked
						if (!"".equals(startTime)&&null!=startTime) {
							query.setString("startTime",startTime);
						}
						if (!"".equals(endTime)&&null!=endTime) {
							query.setString("endTime",endTime);
						}
					}
				}				
				
				if (!"".equals(serialReason)&&null!=serialReason&&!"-".equals(serialReason)) {
					query.setInteger("serialReason",Integer.parseInt(serialReason));
				}
				
				
				if ("".equals(startCount) || null == startCount) {
					query.setFirstResult(0);
					query.setMaxResults(200);
				} else {
					query.setFirstResult(Integer.parseInt(startCount));
					query.setMaxResults(200);
				}

				List list = query.list();
				// user exist
				if (200 == list.size()) {
					xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(ErrorCode.SUCCESS, String
							.valueOf(list.size()), list, "1");
				} else {
					xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(ErrorCode.SUCCESS, String
							.valueOf(list.size()), list, "0");
				}

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
				
				e.printStackTrace();

			} finally {
				HibernateSessionFactory.closeSession();
			}			
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

}
