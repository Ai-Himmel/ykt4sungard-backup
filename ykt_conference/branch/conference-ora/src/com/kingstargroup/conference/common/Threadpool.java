package com.kingstargroup.conference.common;

import org.apache.log4j.Logger;

import java.util.HashMap;

import com.kingstargroup.conference.CardReadThread;

public class Threadpool {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(Threadpool.class);

	private static HashMap analyzesThreadMap = new HashMap();

	private static Threadpool intance = null;

	private static Object mutex = new Object();
	

	// Æô¶¯¶Á¿¨Ïß³Ì
	public void startThread() {
		if (logger.isInfoEnabled()) {
			logger.info("startThread() - start"); //$NON-NLS-1$
		}
		CardReadThread read = (CardReadThread) analyzesThreadMap
				.remove("com.kingstargroup.conference.CardReadThread");
		if (null != read) {
			read.terminate();
		}
		read = null;
		read = new CardReadThread();
		analyzesThreadMap.put("com.kingstargroup.conference.CardReadThread",
				read);
		read.start();

		if (logger.isDebugEnabled()) {
			logger.debug("startThread() - end"); //$NON-NLS-1$
		}
	}

	public void stopThread() {
		CardReadThread read = (CardReadThread) analyzesThreadMap
				.remove("com.kingstargroup.conference.CardReadThread");
		if (null != read) {
			read.terminate();
		}
		read = null;
	}

	public static Threadpool getIntance() {
		if (logger.isInfoEnabled()) {
			logger.info("getIntance() - start"); //$NON-NLS-1$
		}

		if (intance == null) {
			synchronized (mutex) {
				if (intance == null) {
					intance = new Threadpool();
				}
			}
		}

		if (logger.isDebugEnabled()) {
			logger.debug("getIntance() - end"); //$NON-NLS-1$
		}
		return intance;
	}

}
