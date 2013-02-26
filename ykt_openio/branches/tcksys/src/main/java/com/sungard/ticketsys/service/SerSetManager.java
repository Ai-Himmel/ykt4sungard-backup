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
				throw new Exception("该车次已有票预留或售出。" );
			}
			serSetDao.removeBusserDay(newBusserDay);
		} catch (Exception e) {
			throw new Exception("删除车次["+newBusserDay.getSerdayId()+"]信息失败" + e.getMessage());
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
						//获取当前日期为星期几，是否在星期列表中
						Boolean isWeekDay = checkWeekDay(cstart,weekDays);
						if(isWeekDay){
							
							String departDate =  sdf.format(cstart.getTime());
							for (int i = 0; i < selbusSers.size(); i++) {
								BusSer myBusSer = (BusSer) selbusSers.get(i);
								//判断当前车次是否已经添加
								Boolean isAddSer = serSetDao.checkBusSer(departDate,myBusSer.getSerilNo());
								if(isAddSer){
									continue;
								}
								//新增车次
								//构造车次信息
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
									//构造座位号信息
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
			throw new Exception("添加车次失败"+e.getMessage());
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	// 判断当前日期是否在星期列表中
	private Boolean checkWeekDay(Calendar currtC, List<Integer> weekDays) {
		// 获取当前日期为星期几
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
	 * 查询出”可售票“的车次
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
	 *  查询出”可售票“的车次分页对象
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
	 * 不按状态的车次分页对象
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
