package org.king.schedulemanage.service.impl;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.king.classmanage.dao.CollegemodelDAO;
import org.king.classmanage.dao.DictionaryDAO;
import org.king.classmanage.domain.Dictionary;
import org.king.framework.dao.MyQuery;
import org.king.schedulemanage.dao.ClassschedulemodelDAO;
import org.king.schedulemanage.dao.CollegeschedulemodelDAO;
import org.king.schedulemanage.domain.Classschedulemodel;
import org.king.schedulemanage.domain.Collegeschedulemodel;
import org.king.schedulemanage.service.*;
import org.king.utils.DateUtil;

public class ScheduleServiceImpl implements ScheduleService {
	private CollegeschedulemodelDAO collegeschedulemodelDAO;

	private ClassschedulemodelDAO classschedulemodelDAO;

	private CollegemodelDAO collegemodelDAO;

	private DictionaryDAO dictionaryDAO;

	public void setCollegeschedulemodelDAO(
			CollegeschedulemodelDAO collegeschedulemodelDAO) {
		this.collegeschedulemodelDAO = collegeschedulemodelDAO;
	}

	public void setClassschedulemodelDAO(
			ClassschedulemodelDAO classschedulemodelDAO) {
		this.classschedulemodelDAO = classschedulemodelDAO;
	}

	public void setCollegemodelDAO(CollegemodelDAO collegemodelDAO) {
		this.collegemodelDAO = collegemodelDAO;
	}

	public void setDictionaryDAO(DictionaryDAO dictionaryDAO) {
		this.dictionaryDAO = dictionaryDAO;
	}

	public void save(Collegeschedulemodel c) {
		collegeschedulemodelDAO.save(c);
	}

	public void update(Collegeschedulemodel c) {
		collegeschedulemodelDAO.update(c);
	}

	public void delete(Collegeschedulemodel c) {
		collegeschedulemodelDAO.delete(c);
	}

	public void saveClaSchedule(Classschedulemodel c) {
		classschedulemodelDAO.save(c);
	}

	public void updateClaSchedule(Classschedulemodel c) {
		classschedulemodelDAO.update(c);
	}

	public void deleteClaSchedule(Classschedulemodel c) {
		classschedulemodelDAO.delete(c);
	}

	public List getColleges() {
		List colleges = null;
		colleges = collegemodelDAO.getAll();
		return colleges;
	}
	
	/**
	 * 得到复旦学院的所有书院
	 * @return
	 */	
		public List getAllCollegeByfdxy() {
			
			String hql=" from org.king.classmanage.domain.Collegemodel a where a.yxSchool.schoolId='0001'";

			return collegemodelDAO.find(hql);
		}	

	public List getAllCollegeSchedule() {
		List collegeSchedules = null;
		collegeSchedules = collegeschedulemodelDAO.getAll();
		return collegeSchedules;
	}

	public List getCollegeScheduleDate() {
		List collegeScheduleDate = null;
		collegeScheduleDate = collegeschedulemodelDAO
				.find("select distinct c.fromdate from Collegeschedulemodel c order by c.fromdate asc");
		return collegeScheduleDate;
	}

	// public int getTimeSpanByDate(String date){
	// int timeSpan=60;
	// String fromtime,totime;
	// List scheduleTimes=collegeschedulemodelDAO.find("select new
	// Map(c.formtime as fromtime,c.totime as totime) from Collegeschedulemodel
	// c where c.fromdate = '"+date+"'");
	// for(int i=0;i<scheduleTimes.size();i++){
	// fromtime=((Map)scheduleTimes.get(i)).get("fromtime").toString();
	// totime=((Map)scheduleTimes.get(i)).get("totime").toString();
	// int
	// temp=Integer.valueOf(totime).intValue()-Integer.valueOf(fromtime).intValue();
	// }
	// return timeSpan;
	// }
	public Collegeschedulemodel getCollegeScheduleById(String scheduleId) {
		Collegeschedulemodel c = null;
		c = collegeschedulemodelDAO.get(scheduleId);
		return c;
	}

	public List getClassSDateByCollegeId(String collegeId) {
		List scheduledateList = null;
		scheduledateList = classschedulemodelDAO
				.find("select distinct c.fromdate from Classschedulemodel c ,Classmodel d where c.classId = d.classId and d.yxCollege.collegeId = '"
						+ collegeId + "' order by c.fromdate asc");
		return scheduledateList;
	}

	public List getCScheduleByCollegeId(String collegeId) {
		List classSchedules = null, newclassSchedule = null;
		Classschedulemodel c = new Classschedulemodel();
		MyQuery query = new MyQuery();
		
		query
				.setQueryString("select new Map(c as cSchedulemodel,d.classNo as classNo) from Classschedulemodel c,Classmodel d where c.classId=d.classId and d.yxCollege.collegeId ='"
						+ collegeId + "' order by c.fromdate asc");
		classSchedules = classschedulemodelDAO.find(query);
		query
				.setQueryString("from Classschedulemodel c where c.classId='all' and c.collegeId = '"
						+ collegeId + "')");
		newclassSchedule = classschedulemodelDAO.find(query);
		if (newclassSchedule.size() != 0) {
			for (int i = 0; i < newclassSchedule.size(); i++) {
				Map map = new HashMap();
				c = (Classschedulemodel) newclassSchedule.get(i);
				map.put("cSchedulemodel", c);
				map.put("classNo", "各班");
				classSchedules.add(map);
			}
		}
		return classSchedules;

	}

	public List getClassScheduleExcludeSplitsByCollegeIdAndDate(
			String collegeId,String classId, String dateId, String scheduleId) {
		String hql = "from Classschedulemodel c where c.fromdate='" + dateId
				+ "' and c.collegeId='" + collegeId
//				+ "' and c.collegeSchedule is null";
				+"' and (c.classId='"+classId+"' or c.classId='all') ";
		if (scheduleId != null)
			hql += " and c.scheduleId != '" + scheduleId + "'";
		return classschedulemodelDAO.find(hql);
	}

	public List getCScheduleByCollegeIdAndDate(String collegeId, String dateId) {
		List classSchedules = null, newclassSchedule = null;
		Classschedulemodel c = new Classschedulemodel();
		MyQuery query = new MyQuery();		
		query
				.setQueryString("select new Map(c as cSchedulemodel,d.classNo as classNo) from Classschedulemodel c,Classmodel d where c.classId=d.classId and c.fromdate='"
						+ dateId
						+ "' and d.yxCollege.collegeId ='"
						+ collegeId
						+ "' and c.collegeSchedule is not null order by c.fromdate asc");
		classSchedules = classschedulemodelDAO.find(query);
		query
				.setQueryString("from Classschedulemodel c where c.classId='all' and c.fromdate='"
						+ dateId + "' and c.collegeId = '" + collegeId + "')");
		newclassSchedule = classschedulemodelDAO.find(query);
		if (newclassSchedule.size() != 0) {
			for (int i = 0; i < newclassSchedule.size(); i++) {
				Map map = new HashMap();
				c = (Classschedulemodel) newclassSchedule.get(i);
				map.put("cSchedulemodel", c);
				map.put("classNo", "各班");
				classSchedules.add(map);
			}
		}
		return classSchedules;

	}

	public List getCScheduleByDate(String dateId) {
		List classSchedules = null;
		MyQuery query = new MyQuery();

		query
				.setQueryString("select new Map(c as cSchedulemodel,'') from Classschedulemodel c where c.fromdate='"
						+ dateId + "' and c.collegeSchedule is not null ");
		classSchedules = classschedulemodelDAO.find(query);

		return classSchedules;

	}

	public Classschedulemodel getClassScheduleById(String classScheduleId) {
		Classschedulemodel c = null;
		c = classschedulemodelDAO.get(classScheduleId);
		return c;
	}

	public List getCollegeScheduleByCollegeId(String collegeId) {
		List collegeSchedule;
		collegeSchedule = collegeschedulemodelDAO
				.find("from Collegeschedulemodel c where c.collegeId='"
						+ collegeId + "' or c.collegeId='ALL'");
		return collegeSchedule;
	}

	public List getCollegeScheduleByCollegeIdAndDate(String collegeId,
			String dateId) {
		List collegeSchedule;
		collegeSchedule = collegeschedulemodelDAO
				.find("from Collegeschedulemodel c where (c.fromdate = '"
						+ dateId + "' or c.todate = '" + dateId
						+ "') and (c.collegeId='" + collegeId
						+ "' or c.collegeId='ALL')");
		return collegeSchedule;
	}

	public int getCollegeScheduleCountByDate(String dateId) {
		return ((Integer) (collegeschedulemodelDAO
				.find("select count(*) from Collegeschedulemodel c where c.fromdate = '"
						+ dateId + "' or c.todate = '" + dateId + "'").get(0)))
				.intValue();
	}

	public List getCollegeScheduleyDate(String dateId) {
		return collegeschedulemodelDAO
				.find("from Collegeschedulemodel c where c.fromdate = '"
						+ dateId + "' or c.todate = '" + dateId + "'");
	}

	public List getClassScheduleByClassId(String classId, String collegeId) {
		
		Classschedulemodel c = new Classschedulemodel();
		List classSchedules = classschedulemodelDAO
				.find("select new Map(c as cSchedulemodel,d.classNo as classNo) from Classschedulemodel c,Classmodel d where c.classId=d.classId and c.classId = '"
						+ classId + "' order by c.fromdate asc");
		List newclassSchedule = classschedulemodelDAO
				.find("from Classschedulemodel c where c.classId='all' and c.collegeId = '"
						+ collegeId + "')");
		if (newclassSchedule.size() != 0) {
			for (int i = 0; i < newclassSchedule.size(); i++) {
				Map map = new HashMap();
				c = (Classschedulemodel) newclassSchedule.get(i);
				map.put("cSchedulemodel", c);
				map.put("classNo", "各班");
				classSchedules.add(map);
			}
		}
		return classSchedules;
	}

	public void saveDict(Dictionary dict) {
		dictionaryDAO.save(dict);
	}

	public void deleteDict(Dictionary dict) {
		dictionaryDAO.delete(dict);
	}

	public List getScheduleDates() {
		
		String bufdate = DateUtil.getNow("yyyy");
		
		bufdate = bufdate+"-01-01";
//	String bufdate ="2006-01-01";	
		
		return dictionaryDAO
				.find("from Dictionary a where a.id.dictNo= 13 " +
						"and a.dictCaption>='"+bufdate+"' order by a.dictCaption asc");
	}

	public List getClassSplitSchedulesInSameCollegeByCollegeschedule(
			Collegeschedulemodel collegeschedule, String collegeId,String excludeId) {
 
		String hql = "from Classschedulemodel c where c.collegeSchedule.scheduleId = '"
				+ collegeschedule.getScheduleId()
				+ "' ";
		if(!"ALL".equals(collegeId)){
			hql += " and c.collegeId = '"
				+ collegeId + "' ";
		}
		if (excludeId != null)
			hql += " and c.scheduleId != '" + excludeId + "'";

		return classschedulemodelDAO.find(hql);
	}

	public List getSplittedCScheduleByCollegeIdAndDate(String collegeId,
			String dateId) {

		String hql = "select new Map(c as cSchedulemodel,d.classNo as classNo) from Classschedulemodel c,Classmodel d where c.classId=d.classId and c.fromdate = '"
				+ dateId
				+ "' and c.collegeId = '"
				+ collegeId
				+ "' and c.collegeSchedule is not null";

		List classSchedules = classschedulemodelDAO.find(hql);
		List newclassSchedule = classschedulemodelDAO
				.find("from Classschedulemodel c where c.classId='all' and c.fromdate = '"
						+ dateId
						+ "' and c.collegeSchedule is not null and c.collegeId = '"
						+ collegeId + "')");

		for (int i = 0; i < newclassSchedule.size(); i++) {
			Classschedulemodel c = (Classschedulemodel) newclassSchedule.get(i);
			Map map = new HashMap();
			map.put("cSchedulemodel", c);
			map.put("classNo", "各班");
			classSchedules.add(map);
		}

		return classSchedules;
	}

	public List getSplittedCScheduleByCollegeId(String collegeId) {

		String hql = "select new Map(c as cSchedulemodel,d.classNo as classNo) from Classschedulemodel c,Classmodel d where c.classId=d.classId and  c.collegeId = '"
				+ collegeId + "' and c.collegeSchedule is not null";

		List classSchedules = classschedulemodelDAO.find(hql);
		List newclassSchedule = classschedulemodelDAO
				.find("from Classschedulemodel c where c.classId='all' and c.collegeSchedule is not null and c.collegeId = '"
						+ collegeId + "')");

		for (int i = 0; i < newclassSchedule.size(); i++) {
			Classschedulemodel c = (Classschedulemodel) newclassSchedule.get(i);
			Map map = new HashMap();
			map.put("cSchedulemodel", c);
			map.put("classNo", "各班");
			classSchedules.add(map);
		}

		return classSchedules;
	}

}
