package com.kingstargroup.ecard.portlet.msgboard.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.msgboard.MsgBoardPersistence;
import com.kingstargroup.ecard.hibernate.util.MsgBoardUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class MsgBoardServiceBase extends PrincipalBean
		implements InitializingBean, MsgBoardService {	
	
	public MsgBoardService getMsgBoardService() {
		return msgBoardService;
	}
	public void setMsgBoardService(MsgBoardService msgBoardService) {
		this.msgBoardService = msgBoardService;
	}
	public MsgBoardPersistence getMsgBoardPersistence() {
		return msgBoardPersistence;
	}
	public void setMsgBoardPersistence(MsgBoardPersistence msgBoardPersistence) {
		this.msgBoardPersistence = msgBoardPersistence;
	}
	public void afterPropertiesSet() throws Exception {

			if(msgBoardService == null){
				msgBoardService = MsgBoardServiceFactory.getImpl();
			}
			if(msgBoardPersistence == null){
				msgBoardPersistence = MsgBoardUtil.getPersistence();
			}

	}

	protected MsgBoardService msgBoardService;
	protected MsgBoardPersistence msgBoardPersistence;
	
	
}
