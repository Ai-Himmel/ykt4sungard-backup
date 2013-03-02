package org.king.schedulemanage.service;

import java.util.List;

import org.king.classmanage.domain.Dictionary;
import org.king.schedulemanage.domain.Classschedulemodel;
import org.king.schedulemanage.domain.Collegeschedulemodel;

public interface ScheduleService {
	/**
	 * ������ӵ���Ժ�ճ̰���
	 * 
	 * @param c
	 */
	public void save(Collegeschedulemodel c);

	/**
	 * �����޸���Ϣ
	 * 
	 * @param c
	 */
	public void update(Collegeschedulemodel c);

	/**
	 * ɾ����Ժ�ճ̼�¼
	 * 
	 * @param c
	 */
	public void delete(Collegeschedulemodel c);

	/**
	 * ������ӵİ༶�ճ̰���
	 * 
	 * @param c
	 */
	public void saveClaSchedule(Classschedulemodel c);

	/**
	 * ɾ���༶�ճ̰��ż�¼
	 * 
	 * @param c
	 */
	public void deleteClaSchedule(Classschedulemodel c);

	/**
	 * ����༶�ճ��޸�
	 * 
	 * @param c
	 */
	public void updateClaSchedule(Classschedulemodel c);

	/**
	 * ������е���Ժ
	 * 
	 * @return
	 */
	public List getColleges();
	
	/**
	 * �õ�����ѧԺ��������Ժ
	 * @return
	 */	
	public List getAllCollegeByfdxy() ;
	/**
	 * ������е���Ժ�ճ̰���
	 * 
	 * @return
	 */
	public List getAllCollegeSchedule();

	/**
	 * �����Ժ�ճ̰�������
	 * 
	 * @return
	 */
	public List getCollegeScheduleDate();

	/**
	 * ���ӭ�������ڣ��������Ⱥ�����
	 * 
	 * @return
	 */
	public List getScheduleDates();

	/**
	 * ����id�����Ժschedule
	 * 
	 * @param scheduleId
	 * @return
	 */
	public Collegeschedulemodel getCollegeScheduleById(String scheduleId);

	/**
	 * ����id��ð༶schedule
	 * 
	 * @param classScheduleId
	 * @return
	 */
	public Classschedulemodel getClassScheduleById(String classScheduleId);

	/**
	 * ������Ժ��ð༶�ճ̰�������
	 */
	public List getClassSDateByCollegeId(String collegeId);

	/**
	 * ������Ժid��ø���Ժ���а༶�ճ̰���
	 */
	public List getCScheduleByCollegeId(String collegeId);

	/*
	 * ������Ժid��ȡ����Ժ�ճ̰���
	 */
	public List getCollegeScheduleByCollegeId(String collegeId);

	/*
	 * ������Ժid��ȡ����Ժĳ���ճ̰���
	 */
	public List getCollegeScheduleByCollegeIdAndDate(String collegeId,
			String dateId);

	/*
	 * ���ĳ���ڵ��ճ̰�����Ŀ
	 */
	public int getCollegeScheduleCountByDate(String dateId);

	/*
	 * ���ĳ���ڵ��ճ̰���
	 */
	public List getCollegeScheduleyDate(String dateId);

	/**
	 * ���ݰ༶id��ȡ�ð༶�ճ̰���
	 * 
	 * @param classId
	 * @return
	 */
	public List getClassScheduleByClassId(String classId, String collegeId);

	/**
	 * ���������ֵ�
	 * 
	 * @param dict
	 */
	public void saveDict(Dictionary dict);

	/**
	 * ɾ�������ֵ��¼
	 * 
	 * @param dict
	 */
	public void deleteDict(Dictionary dict);

	public List getCScheduleByCollegeIdAndDate(String collegeId, String dateId);

	public List getCScheduleByDate(String dateId);

	/**
	 * ������Ժ�ճ̰��Ż�ȡͬ������һ�ճ��ڵ����а༶�ճ̰���
	 * 
	 * @param collegeschedule
	 * @return
	 */
	public List getClassSplitSchedulesInSameCollegeByCollegeschedule(
			Collegeschedulemodel collegeschedule,String collegeId, String excludeId);

	/**
	 * ������Ժid������id��ȡ���и������ڸ���Ժ�ڵİ༶�ճ̰��ţ������������ֲ�õ��İ༶�ճ̰��ţ����scheduleId�ǿգ���Ҳ������id����scheduleId�İ༶�ճ�
	 * 
	 * @param collegeId
	 * @param classId
	 * @param dateId
	 * @param scheduleId
	 * @return
	 */
	/**
	* Description: ������Ժid���༶id������id��ȡ���и������ڸð༶��������ذ༶�ճ̰��ţ�
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
