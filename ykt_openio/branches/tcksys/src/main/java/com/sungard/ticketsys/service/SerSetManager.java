package com.sungard.ticketsys.service;

import hibernate.HibernateSessionFactory;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;

import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.dao.SerSetDao;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Seat;
import com.sungard.ticketsys.common.Page;

public class SerSetManager {
	private SerSetDao serSetDao = SerSetDao.getInstance();

	private static SerSetManager serSetManager;

	public static SerSetManager getInstance() {
		if (serSetManager == null) {
			serSetManager = new SerSetManager();
		}
		return serSetManager;
	}

	public BusserDay getBusserDay(String serdayId) {
		return serSetDao.getBusserDay(serdayId);
	}

	public void removeSerSet(BusserDay newBusserDay) throws Exception {
		try {
			if(newBusserDay.getTicketCount()>0||newBusserDay.getReserveCount()>0){
				throw new Exception("�ó�������ƱԤ�����۳���" );
			}
			serSetDao.removeBusserDay(newBusserDay);
		} catch (Exception e) {
			throw new Exception("ɾ������["+newBusserDay.getSerdayId()+"]��Ϣʧ��" + e.getMessage());
		}

	}

	public Page getSerSetByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String startTime, String endTime) {
		return serSetDao.getSerSetByConditions(pageNo, pageSize, searchSerSet,
				startTime, endTime, null);
	}

	@SuppressWarnings("unchecked")
	public List<BusserDay> getSerSetByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String startTime, String endTime,
			String orderBy) {
		Page page = serSetDao.getSerSetByConditions(pageNo, pageSize,
				searchSerSet, startTime, endTime, orderBy);
		if (page != null) {
			return (List<BusserDay>) page.getResult();
		} else {
			return null;
		}
	}

	public void setSerDay(Calendar cstart, Calendar cend,
			List<Integer> weekDays, List<BusSer> selbusSers) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		try {
			 SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
			if(weekDays!=null && weekDays.size()>0){
				
				 while(cstart.equals(cend)||cend.after(cstart)){
						//��ȡ��ǰ����Ϊ���ڼ����Ƿ��������б���
						Boolean isWeekDay = checkWeekDay(cstart,weekDays);
						if(isWeekDay){
							
							String departDate =  sdf.format(cstart.getTime());
							for (int i = 0; i < selbusSers.size(); i++) {
								BusSer myBusSer = (BusSer) selbusSers.get(i);
								//�жϵ�ǰ�����Ƿ��Ѿ����
								Boolean isAddSer = serSetDao.checkBusSer(departDate,myBusSer.getSerilNo());
								if(isAddSer){
									continue;
								}
								//��������
								//���쳵����Ϣ
								BusserDay busserDay = new BusserDay();
								busserDay.setSerdayId(myBusSer.getSerilNo()+departDate);
								busserDay.setBusSerNo(myBusSer.getSerilNo());
								busserDay.setDepartDate(departDate);
								busserDay.setTicketCount(0);
								busserDay.setReserveCount(0);
								busserDay.setRemainCount(myBusSer.getMaxCount());
								busserDay.setStatus(BusserDay.STATE_WAIT_SALE);
								int seatcount = myBusSer.getMaxCount();
								for(int j=1;j<=seatcount;j++){
									//������λ����Ϣ
									Seat seat = new Seat();
									seat.setSerdayId(myBusSer.getSerilNo()+departDate);
									seat.setSeatNo(j);
									seat.setStatus(Seat.STATE_WAIT_SALE);
									session.save(seat);
								}
								session.save(busserDay);
								
						      }
						}
						cstart.add(Calendar.DATE, 1);
					 }
				 tx.commit();
			}
		 
		} catch (Exception e) {
			tx.rollback();
			e.printStackTrace();
			throw new Exception("��ӳ���ʧ��"+e.getMessage());
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	// �жϵ�ǰ�����Ƿ��������б���
	private Boolean checkWeekDay(Calendar currtC, List<Integer> weekDays) {
		// ��ȡ��ǰ����Ϊ���ڼ�
		int currtW = currtC.get(Calendar.DAY_OF_WEEK) - 1;
		if (currtW < 0)
			currtW = 0;

		Boolean isWeekDay = false;
		for (int i = 0; i < weekDays.size(); i++) {
			int weekDay = weekDays.get(i);
			if (currtW == weekDay) {
				isWeekDay = true;
				break;
			}
		}
		return isWeekDay;
	}

	/**
	 * ��ѯ��������Ʊ���ĳ���
	 * @param pageNo
	 * @param pageSize
	 * @param searchSerSet
	 * @param departDate
	 * @param startAddr
	 * @param endAddr
	 * @param orderBy
	 * @return
	 */
	@SuppressWarnings("unchecked")
	public List<BusserDay> getSerSetByConditions(int pageNo,
			int pageSize, BusserDay searchSerSet, String departDate,
			String startAddr, String endAddr, String orderBy) {
		Page page = serSetDao.getSerSetByConditions(pageNo, pageSize,
				searchSerSet, departDate, startAddr,endAddr, orderBy,BusserDay.STATE_WAIT_SALE);
		if (page != null) {
			return (List<BusserDay>) page.getResult();
		} else {
			return null;
		}
	}
	
	/**
	 *  ��ѯ��������Ʊ���ĳ��η�ҳ����
	 * @param pageNo
	 * @param pageSize
	 * @param searchSerSet
	 * @param departDate
	 * @param startAddr
	 * @param endAddr
	 * @param orderBy
	 * @return
	 */
	public Page getPageByConditions(int pageNo,
			int pageSize, BusserDay searchSerSet, String departDate,
			String startAddr, String endAddr, String orderBy){
		return serSetDao.getSerSetByConditions(pageNo, pageSize,
				searchSerSet, departDate, startAddr,endAddr, orderBy,BusserDay.STATE_WAIT_SALE);
	}

	/**
	 * ����״̬�ĳ��η�ҳ����
	 * @param pageNo
	 * @param pageSize
	 * @param searchSerSet
	 * @param startDate
	 * @param endDate
	 * @param orderBy
	 * @return
	 */
	public Page getPageByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String startDate, String endDate,
			String orderBy) {
		return serSetDao.geBusserDayByConditions(pageNo, pageSize,
				searchSerSet, startDate, endDate,null, orderBy,null);
	}

	public boolean busserDayIsUsed(String serdayId) {
		// TODO Auto-generated method stub
		return false;
	}

}
