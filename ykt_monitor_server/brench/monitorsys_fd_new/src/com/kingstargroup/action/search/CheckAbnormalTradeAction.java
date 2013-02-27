package com.kingstargroup.action.search;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:CheckAbnormalTradeAction.java
 * Description: 查异常流水 
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-10-10   何林青    根据前台传过来的条件查异常流水功能
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class CheckAbnormalTradeAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckAbnormalTradeAction.class);

	public ActionForward abTradeList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}
			request.setCharacterEncoding("GBK");

			String deviceID = request.getParameter("DeviceID");
			String contactName = request.getParameter("ContactName");
			String startTime = request.getParameter("StartTime");
			String endTime = request.getParameter("EndTime");
			String abnormalType = request.getParameter("AbnormalType");
			String lastFlag = request.getParameter("lastanalysis");
			String startCount = request.getParameter("StartCount");

			StringBuffer sqlBuff = new StringBuffer();
			sqlBuff.append("from MapSerialexceptTable  serial where 1=1 ");
			if (!"".equals(deviceID)&&null!=deviceID) {
				sqlBuff.append("and serial.id.deviceId = :deviceID ");
			}		
			if (!"".equals(contactName)&&null!=contactName) {
				sqlBuff.append("and serial.contactname like :contactName ");
			}
			
			if (!"".equals(lastFlag) && null != lastFlag) {
				if ("1".equals(lastFlag)) {
					// ToDo:checked----to get the last version of result
					sqlBuff.append("and serial.id.analysisTime >= :startTime ");
					sqlBuff.append(" and serial.id.analysisTime <= :endTime ");
				} else {
					// ToDo:unchecked
					if (!"".equals(startTime)&&null!=startTime) {
						sqlBuff.append("and concat(serial.id.txDate,serial.id.txTime) >= :startTime ");
					}
					if (!"".equals(endTime)&&null!=endTime) {
						sqlBuff.append(" and concat(serial.id.txDate,serial.id.txTime) <= :endTime ");
					}
				}
			}		
			
			
			if (!"".equals(abnormalType)&&null!=abnormalType&&!"-".equals(abnormalType)) {
				if("2".equals(abnormalType)){
					sqlBuff.append(" and serial.abnormaltype > 200 and serial.abnormaltype < 210 ");
				}else if("5".equals(abnormalType)){
					sqlBuff.append(" and serial.abnormaltype > 50 and serial.abnormaltype < 60 ");
				}else{
					sqlBuff.append(" and serial.abnormaltype = :abnormalType ");
				}				
			}
			sqlBuff.append("order by serial.id.analysisTime desc,serial.id.txDate desc,serial.id.txTime desc,serial.id.deviceId desc");

			try {
//				MessageResources msgResources = (MessageResources) this
//						.getServlet().getServletContext().getAttribute(
//								Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				
				Query queryTime = session.createQuery("select a.value from MapParamTable a,MapSysDictionary b where a.parameter=b.dictCode and b.id.dictNo=:dictNo and b.id.dictValue=:dictValue");
				if (!"".equals(abnormalType)&&null!=abnormalType&&!"-".equals(abnormalType)) {
						queryTime.setInteger("dictNo",2);
						queryTime.setString("dictValue",abnormalType);			
				}else{
					queryTime.setInteger("dictNo",0);
					queryTime.setString("dictValue",abnormalType);	
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
				
				
				
				if (!"".equals(abnormalType)&&null!=abnormalType&&!"-".equals(abnormalType)) {
					if(!"2".equals(abnormalType)&&!"5".equals(abnormalType)){
						query.setInteger("abnormalType",Integer.parseInt(abnormalType));
					}				
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

			if (logger.isDebugEnabled()) {
				logger
						.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
			}	
		return null;
	}
	
	public ActionForward itemList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			xmlOut = XMLGenerateUtil.XMLGenerate("0000","0",null);
			xmlOut = XMLGenerateUtil.serialXMLGenerate(xmlOut,"",1);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} 

		if (logger.isDebugEnabled()) {
			logger
					.debug("deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
}
