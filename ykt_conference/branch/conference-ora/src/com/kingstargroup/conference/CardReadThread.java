package com.kingstargroup.conference;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.conference.action.cardread.ReadCardUtil;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.SignDAO;
import com.kingstargroup.conference.hibernate.HibernateSessionFactory;
import com.kingstargroup.conference.hibernate.form.TConference;

public class CardReadThread extends Thread {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(CardReadThread.class);

	private boolean requestStop = false;
	

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		while (!requestStop) {
			anaylize();
		}
		System.out.println("$$$$$$$$$$$$$$$$��������ֹͣ����$$$$$$$$$$$$$$$$$$$$$");
		logger.info("$$$$$$$$$$$$$$$$��������ֹͣ����$$$$$$$$$$$$$$$$$$$$$"); //$NON-NLS-1$
	}

	public void anaylize() {
		Transaction tx = null;
		try {
			if (logger.isInfoEnabled()) {
				logger.info("**************�ڿ����ѷ����̳߳�ʼ��**************"); //$NON-NLS-1$
			}
			
			String CardNo = ReadCardUtil.ReadCardNO();
			if (null != CardNo) {
			//	System.out.println(CardNo);
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				ConferenceDAO confdao = ConferenceDAO.getInstance();
				SignDAO signdao = SignDAO.getInstance();
				TConference conf = confdao.getConIdByTime("");
				if (null==conf) {
					// û������ʱ��
					System.out.println("=====No such meeting===");
					ReadCardUtil.BeepOnce();
					ReadCardUtil.BeepTwice();
				} else {
					if (signdao.getCustbyidandPhyNo(conf.getConId().intValue(), CardNo)) {
						signdao.updatecheckFlag(conf.getConId().intValue(), CardNo);
						ReadCardUtil.BeepOnce();
					}else{
						//��¼��Ϣ
						System.out.println("=====No one in this meeting===");
						signdao.recordHis(conf.getConId(),CardNo);
						ReadCardUtil.BeepOnce();
					}
				}
				tx.commit();
				sleep(500);
			}else{
				sleep(1000);
			}
			

		} catch (HibernateException e) {
			logger.error("���������̳߳��������쳣��", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			ReadCardUtil.BeepTwice();
		} catch (Exception e) {
			logger.error("���������̳߳��������쳣��", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			ReadCardUtil.BeepTwice();
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("���������߳�״̬�����󣬴�ʱ�߳�״̬����߳�!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("���������߳�״̬�����󣬴�ʱ�߳�״̬�������߳�!"); //$NON-NLS-1$
			this.destroy();

		}
	}

	public boolean isTerminate() {
		// TODO Auto-generated method stub
		return this.isAlive();
	}

}
