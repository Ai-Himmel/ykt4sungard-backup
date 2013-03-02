package org.king.schedulemanage.service;

import java.util.List;

import org.king.classmanage.domain.Dictionary;
import org.king.schedulemanage.domain.Classschedulemodel;
import org.king.schedulemanage.domain.Collegeschedulemodel;

public interface ScheduleService {
	/**
	 * 保存添加的书院日程安排
	 * 
	 * @param c
	 */
	public void save(Collegeschedulemodel c);

	/**
	 * 保存修改信息
	 * 
	 * @param c
	 */
	public void update(Collegeschedulemodel c);

	/**
	 * 删除书院日程记录
	 * 
	 * @param c
	 */
	public void delete(Collegeschedulemodel c);

	/**
	 * 保存添加的班级日程安排
	 * 
	 * @param c
	 */
	public void saveClaSchedule(Classschedulemodel c);

	/**
	 * 删除班级日程安排记录
	 * 
	 * @param c
	 */
	public void deleteClaSchedule(Classschedulemodel c);

	/**
	 * 保存班级日程修改
	 * 
	 * @param c
	 */
	public void updateClaSchedule(Classschedulemodel c);

	/**
	 * 获得所有的书院
	 * 
	 * @return
	 */
	public List getColleges();
	
	/**
	 * 得到复旦学院的所有书院
	 * @return
	 */	
	public List getAllCollegeByfdxy() ;
	/**
	 * 获得所有的书院日程安排
	 * 
	 * @return
	 */
	public List getAllCollegeSchedule();

	/**
	 * 获得书院日程安排日期
	 * 
	 * @return
	 */
	public List getCollegeScheduleDate();

	/**
	 * 获得迎新周日期，按日期先后排列
	 * 
	 * @return
	 */
	public List getScheduleDates();

	/**
	 * 根据id获得书院schedule
	 * 
	 * @param scheduleId
	 * @return
	 */
	public Collegeschedulemodel getCollegeScheduleById(String scheduleId);

	/**
	 * 根据id获得班级schedule
	 * 
	 * @param classScheduleId
	 * @return
	 */
	public Classschedulemodel getClassScheduleById(String classScheduleId);

	/**
	 * 根据书院获得班级日程安排日期
	 */
	public List getClassSDateByCollegeId(String collegeId);

	/**
	 * 根据书院id获得该书院所有班级日程安排
	 */
	public List getCScheduleByCollegeId(String collegeId);

	/*
	 * 根据书院id获取该书院日程安排
	 */
	public List getCollegeScheduleByCollegeId(String collegeId);

	/*
	 * 根据书院id获取该书院某日日程安排
	 */
	public List getCollegeScheduleByCollegeIdAndDate(String collegeId,
			String dateId);

	/*
	 * 获得某日期的日程安排数目
	 */
	public int getCollegeScheduleCountByDate(String dateId);

	/*
	 * 获得某日期的日程安排
	 */
	public List getCollegeScheduleyDate(String dateId);

	/**
	 * 根据班级id获取该班级日程安排
	 * 
	 * @param classId
	 * @return
	 */
	public List getClassScheduleByClassId(String classId, String collegeId);

	/**
	 * 保存数据字典
	 * 
	 * @param dict
	 */
	public void saveDict(Dictionary dict);

	/**
	 * 删除数据字典记录
	 * 
	 * @param dict
	 */
	public void deleteDict(Dictionary dict);

	public List getCScheduleByCollegeIdAndDate(String collegeId, String dateId);

	public List getCScheduleByDate(String dateId);

	/**
	 * 根据书院日程安排获取同属于这一日程内的所有班级日程安排
	 * 
	 * @param collegeschedule
	 * @return
	 */
	public List getClassSplitSchedulesInSameCollegeByCollegeschedule(
			Collegeschedulemodel collegeschedule,String collegeId, String excludeId);

	/**
	 * 根据书院id和日期id获取所有该日期内该书院内的班级日程安排，但不包括被分拆得到的班级日程安排，如果scheduleId非空，则也不包括id等于scheduleId的班级日程
	 * 
	 * @param collegeId
	 * @param classId
	 * @param dateId
	 * @param scheduleId
	 * @return
	 */
	/**
	* Description: 根据书院id、班级id和日期id获取所有该日期内该班级的所有相关班级日程安排，
	*@param collegeId
	*@param classId
	*@param dateId
	*@param scheduleId
	*@return
	* @return List
	* Modify History: 2006-8-23 jackey create
	*/
	public List getClassScheduleExcludeSplitsByCollegeIdAndDate(
			String collegeId,String classId, String dateId, String scheduleId);
	
	public List getSplittedCScheduleByCollegeIdAndDate(String collegeId, String dateId);
	
	public List getSplittedCScheduleByCollegeId(String collegeId);
}
