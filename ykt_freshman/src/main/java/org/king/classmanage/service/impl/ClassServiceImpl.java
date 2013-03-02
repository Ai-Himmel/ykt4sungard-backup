/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassServiceImpl.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-29     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service.impl;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.sql.Types;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.king.classmanage.dao.ClassmodelDAO;
import org.king.classmanage.dao.CollegemodelDAO;
import org.king.classmanage.dao.ManagermodelDAO;
import org.king.classmanage.dao.StudentmodelDAO;
import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.ClassDorm;
import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.GzStuTemp;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.NHeaderSessionModel;
import org.king.classmanage.domain.NHeaderSessionModelId;
import org.king.classmanage.domain.NTableHeadModel;
import org.king.classmanage.domain.StudentListColumns;
import org.king.classmanage.domain.StudentfdyListColmns;
import org.king.classmanage.domain.SdListhlxy;
import org.king.classmanage.domain.SdfdyListhlxy;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.web.help.AbroadClasses;
import org.king.classmanage.web.help.ClassAlertHistory;
import org.king.classmanage.web.help.ClassStatistic;
import org.king.classmanage.web.help.ClassWithDormitory;
import org.king.classmanage.web.help.ClassWithManager;
import org.king.classmanage.web.help.NationDistributionInfo;
import org.king.dormitorymanage.dao.DormitorymodelDAO;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.framework.dao.MyQuery;
import org.king.framework.service.impl.BaseService;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.dao.YxGraduateDAO;

import com.ibm.icu.text.Collator;

public class ClassServiceImpl extends BaseService implements ClassService {

	private ClassmodelDAO classmodelDAO;

	private ManagermodelDAO managermodelDAO;

	private StudentmodelDAO studentmodelDAO;

	private CollegemodelDAO collegemodelDAO;	
	
	public static SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy");

	/**
	 * @return Returns the studentmodelDAO.
	 */
	public StudentmodelDAO getStudentmodelDAO() {
		return studentmodelDAO;
	}

	/**
	 * @param studentmodelDAO
	 *            The studentmodelDAO to set.
	 */
	public void setStudentmodelDAO(StudentmodelDAO studentmodelDAO) {
		this.studentmodelDAO = studentmodelDAO;
	}

	/**
	 * @param managermodelDAO
	 *            The managermodelDAO to set.
	 */
	public void setManagermodelDAO(ManagermodelDAO managermodelDAO) {
		this.managermodelDAO = managermodelDAO;
	}

	/**
	 * @param classmodelDAO
	 *            The classmodelDAO to set.
	 */
	public void setClassmodelDAO(ClassmodelDAO classmodelDAO) {
		this.classmodelDAO = classmodelDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#saveClassmodel(org.king.classmanage.domain.Classmodel)
	 */
	public void saveClassmodel(Classmodel classmodel) {
		classmodelDAO.save(classmodel);
	}
	
    private DormitorymodelDAO dormitorymodelDAO;
	
	private YxGraduateDAO yxGraduateDAO;
	
	public void setYxGraduateDAO(YxGraduateDAO yxGraduateDAO){
		this.yxGraduateDAO=yxGraduateDAO;
		
	}
	
	public void setDormitorymodelDAO(DormitorymodelDAO dormitorymodelDAO) {
		this.dormitorymodelDAO = dormitorymodelDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#saveClassandManager(org.king.classmanage.domain.Classmodel,
	 *      java.util.List)
	 */
	public void saveClassandManager_hlxy(Classmodel classmodel, List list) {
		
		classmodel.setYxCollege(collegemodelDAO.get("0002"));
		
		String datebuf = sdf1.format(new Date());//增加当前年份
		classmodel.setCurYear(datebuf);
		
		
		classmodelDAO.save(classmodel);
		for (int i = 0; i < list.size(); i++) {
			Classmanager classmanager = (Classmanager) list.get(i);
			classmanager.getId().setClassId(classmodel.getClassId());
			managermodelDAO.saveClassManager(classmanager);
		}
	}
	
	public void saveClassandManager(Classmodel classmodel, List list,
			String collegeId) {
		classmodel.setYxCollege(collegemodelDAO.get(collegeId));
		
		String datebuf = sdf1.format(new Date());//增加当前年份
		classmodel.setCurYear(datebuf);
		
		
		classmodelDAO.save(classmodel);
		for (int i = 0; i < list.size(); i++) {
			Classmanager classmanager = (Classmanager) list.get(i);
			classmanager.getId().setClassId(classmodel.getClassId());
			managermodelDAO.saveClassManager(classmanager);
		}
	}

	public void updateClassandManager_hlxy(Classmodel classmodel, List list) {
		// classmodel.setYxCollege(collegemodelDAO.get(collegeId));

		classmodel.setYxCollege(collegemodelDAO.get("0002"));//护理学院
		
		String datebuf = sdf1.format(new Date());//增加当前年份
		classmodel.setCurYear(datebuf);
		
		classmodelDAO.update(classmodel);
		managermodelDAO.deleteClassAssitant(classmodel.getClassId());
		managermodelDAO.deleteClassTutor(classmodel.getClassId());
		for (int i = 0; i < list.size(); i++) {
			Classmanager classmanager = (Classmanager) list.get(i);
			classmanager.getId().setClassId(classmodel.getClassId());
			managermodelDAO.saveClassManager(classmanager);
		}
	}
	
	public void updateClassandManager(Classmodel classmodel, List list,
			String collegeId) {
		// classmodel.setYxCollege(collegemodelDAO.get(collegeId));
		Collegemodel collegemodel = new Collegemodel();
		collegemodel.setCollegeId(collegeId);
		classmodel.setYxCollege(collegemodel);
		
		String datebuf = sdf1.format(new Date());//增加当前年份
		classmodel.setCurYear(datebuf);
		
		classmodelDAO.update(classmodel);
		managermodelDAO.deleteClassAssitant(classmodel.getClassId());
		managermodelDAO.deleteClassTutor(classmodel.getClassId());
		for (int i = 0; i < list.size(); i++) {
			Classmanager classmanager = (Classmanager) list.get(i);
			classmanager.getId().setClassId(classmodel.getClassId());
			managermodelDAO.saveClassManager(classmanager);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#getClassmodel(java.lang.String)
	 */
	public Classmodel getClassmodel(String classId) {
		String hql = " from Classmodel a where a.classId='"+classId+"'";
		List list = classmodelDAO.find(hql);
		if(list!=null&&list.size()>0){
			Classmodel classmodel = (Classmodel)list.get(0);
			return classmodel;
		}else{
			return null;
		}

//		return classmodelDAO.get(classId);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#getClassmodelbyNo(java.lang.String)
	 */
	public List getClassmodelbyNo(String classNo) {

		return classmodelDAO.find("from Classmodel where classNo='" + classNo
				+ "'");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#getClassmodelbyName(java.lang.String)
	 */
	public List getClassmodelbyName(String className) {
		return classmodelDAO.find("from Classmodel where className='"
				+ className + "'");
	}

	/*
	 * (non-Javadoc)
	 * 查找相应院系的班级
	 * @see org.king.classmanage.service.ClassService#getClassmodel()
	 */
	public List getClassmodelbyschoolId(String schoolId) {
		
		String datebuf = sdf1.format(new Date());//当前年份
		String hql = "from Classmodel a where a.curYear='"+datebuf;
		if (schoolId != null && !schoolId.equals("")){
		 hql+= " ' and a.yxCollege.yxSchool.schoolId='"+schoolId+"' order by a.classNo";
		}
		else {
			hql += "' order by a.classNo";
		}
		List list = classmodelDAO.find(hql);
		
		return list;
	}

	public List getClassmodel() {
		
		String datebuf = sdf1.format(new Date());//当前年份
		String hql = "from Classmodel a where a.curYear='"+datebuf+"' order by a.classNo";
		List list = classmodelDAO.find(hql);
	
//		return classmodelDAO.getAll();
		
		return list;
	}
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#delteClassmodel()
	 */
	public void deleteClassmodel(Classmodel classmodel) {
		classmodelDAO.delete(classmodel);
	}

	public void deleteClassandManager(Classmodel classmodel) {
		classmodelDAO.delete(classmodel);
		managermodelDAO.deleteClassAssitant(classmodel.getClassId());
		managermodelDAO.deleteClassTutor(classmodel.getClassId());
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#getClassbyCollegeId(java.lang.String)
	 */
	public List getClassbyCollegeId(String collegeId) {
		return classmodelDAO
				.find("from Classmodel classmodel where classmodel.yxCollege.collegeId='"
						+ collegeId + "' and classmodel.curYear='"+DateUtil.getNow("yyyy")+"' order by classmodel.classNo ");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#saveConnection(java.lang.String,
	 *      java.util.List)
	 */
	public void saveConnection(String classId, List dormitoryId) {
		// TODO Auto-generated method stub

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#alertClass(java.util.List,
	 *      java.lang.String)
	 */
	public void alertClass(List StudentId, String classId) {
		// TODO Auto-generated method stub

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#getAlertHistory()
	 */
	public List getAlertHistory(String[] args,String schoolId) {
		String studentNo = args[0];
		String stuName = args[1];
		String classes = args[2];
		String operatorTime1 = args[3];
		String operatorTime2 = args[4];
		String page = args[5];
		String orderby = args[6];
		String odr = args[7];

		List entitys = null;
		MyQuery myQuery = new MyQuery();
		
		if (schoolId != null && schoolId.equals("0001")) {//复旦学院
				String hqlStr = "select distinct new org.king.classmanage.web.help.ClassAlertHistory"
					+ "(a.studentId,b.studentNo,b.stuName,a.classIdO,'','',"
					+ "a.classIdN,'','',a.operatorId,a.operatorTime) "
					+ "from ClassAlertHis a,Studentmodel b "
					+ "where a.studentId=b.studentId and b.yxClass.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
	
			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and (a.classIdO = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " or a.classIdN = ?)" : "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime1) ? " and a.operatorTime >= ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime2) ? " and a.operatorTime <= ?"
					: "");
	
	
			if (StringUtils.isNotEmpty(studentNo)) {
				myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(stuName)) {
				myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(operatorTime1)) {
				myQuery.addPara(operatorTime1, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(operatorTime2)) {
				myQuery.addPara(operatorTime2, Types.VARCHAR);
			}
	
			// if (StringUtils.isNumeric(page)) {
			// myQuery.setPageStartNo(Integer.parseInt(page));
			// } else {
			// myQuery.setPageStartNo(0);
			// }
	
			if (orderby == null || orderby.length() == 0)
				myQuery.setOrderby(" order by a.operatorTime desc");
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("studentNo"))
				myQuery.setOrderby(" order by b.studentNo" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName"))
				myQuery.setOrderby(" order by b.stuName" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("operatetime"))
				myQuery.setOrderby(" order by a.operatorTime" + " " + odr);
	
			myQuery.setQueryString(hqlStr);
	
			// myQuery.setOffset(true);
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassAlertHistory classAlertHistory = (ClassAlertHistory) entitys
						.get(i);
				List list_ass_o = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassO() + "'");
				if (list_ass_o.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_o.get(0);
					classAlertHistory.setAssistantO(managermodel.getManagerName());
				}
				List list_cls_o = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassO()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_o.size() > 0) {
					Object[] classNo_O = (Object[]) list_cls_o.get(0);
					classAlertHistory.setClassO(classNo_O[0].toString());
					classAlertHistory.setCollegeO(classNo_O[1].toString());
				}
				List list_ass_n = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassN() + "'");
				if (list_ass_n.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_n.get(0);
					classAlertHistory.setAssistantN(managermodel.getManagerName());
				}
				List list_cls_n = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassN()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_n.size() > 0) {
					Object[] classNo_N = (Object[]) list_cls_n.get(0);
					classAlertHistory.setClassN(classNo_N[0].toString());
					classAlertHistory.setCollegeN(classNo_N[1].toString());
				}
	
			}
	
			// 其它字段排序
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName")) {
				// Comparator comp1 = new Comparator() {
				// public int compare(Object o1, Object o2) {
				// ClassAlertHistory m1 = (ClassAlertHistory) o1;
				// ClassAlertHistory m2 = (ClassAlertHistory) o2;
				// //
				// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
				// String collegeName1 = (String) m1.getStuName();
				// String collegeName2 = (String) m2.getStuName();
				//
				// java.text.RuleBasedCollator collator = (RuleBasedCollator)
				// java.text.Collator
				// .getInstance(java.util.Locale.CHINA);
				// java.text.CollationKey c1 = collator
				// .getCollationKey(collegeName1);
				// java.text.CollationKey c2 = collator
				// .getCollationKey(collegeName2);
				// return c1.compareTo(c2);
				//
				// }
				// };
				// Comparator comp2 = new Comparator() {
				// public int compare(Object o1, Object o2) {
				// ClassAlertHistory m1 = (ClassAlertHistory) o1;
				// ClassAlertHistory m2 = (ClassAlertHistory) o2;
				// //
				// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
				// String collegeName1 = (String) m1.getStuName();
				// String collegeName2 = (String) m2.getStuName();
				//
				// java.text.RuleBasedCollator collator = (RuleBasedCollator)
				// java.text.Collator
				// .getInstance(java.util.Locale.CHINA);
				// java.text.CollationKey c1 = collator
				// .getCollationKey(collegeName1);
				// java.text.CollationKey c2 = collator
				// .getCollationKey(collegeName2);
				// return c2.compareTo(c1);
				//
				// }
				// };
				// if (odr.equals("asc"))
				// Collections.sort(entitys, comp1);
				// else
				// Collections.sort(entitys, comp2);
				Collator col = Collator.getInstance(Locale.CHINA);
				for (int i = entitys.size() - 1; i >= 1; i--) {
					for (int j = 0; j < i; j++) {
						ClassAlertHistory m1 = (ClassAlertHistory) entitys.get(j);
						ClassAlertHistory m2 = (ClassAlertHistory) entitys
								.get(j + 1);
						if (odr.equals("asc")) {
							if (col.compare(m1.getStuName(), m2.getStuName()) == -1) {
								Object temp = entitys.get(j);
								entitys.set(j, entitys.get(j + 1));
								entitys.set(j + 1, temp);
	
							}
						} else {
							if (col.compare(m1.getStuName(), m2.getStuName()) == 1) {
								Object temp = entitys.get(j);
								entitys.set(j, entitys.get(j + 1));
								entitys.set(j + 1, temp);
	
							}
						}
	
					}
				}
	
			}
	
			if (orderby != null && orderby.length() > 0 && orderby.equals("classO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassO() != null)
							collegeName1 = (String) m1.getClassO();
						if (m2.getClassO() != null)
							collegeName2 = (String) m2.getClassO();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassO() != null)
							collegeName1 = (String) m1.getClassO();
						if (m2.getClassO() != null)
							collegeName2 = (String) m2.getClassO();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("assistantO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantO();
						String collegeName2 = (String) m2.getAssistantO();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantO();
						String collegeName2 = (String) m2.getAssistantO();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("collegeO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeO();
						String collegeName2 = (String) m2.getCollegeO();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeO();
						String collegeName2 = (String) m2.getCollegeO();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0 && orderby.equals("classN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassN() != null)
							collegeName1 = (String) m1.getClassN();
						if (m2.getClassN() != null)
							collegeName2 = (String) m2.getClassN();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassN() != null)
							collegeName1 = (String) m1.getClassN();
						if (m2.getClassN() != null)
							collegeName2 = (String) m2.getClassN();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("assistantN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantN();
						String collegeName2 = (String) m2.getAssistantN();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantN();
						String collegeName2 = (String) m2.getAssistantN();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("collegeN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeN();
						String collegeName2 = (String) m2.getCollegeN();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeN();
						String collegeName2 = (String) m2.getCollegeN();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("operator")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getOperator();
						String collegeName2 = (String) m2.getOperator();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getOperator();
						String collegeName2 = (String) m2.getOperator();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
		} else if (schoolId != null && schoolId.equals("0002")) {//护理学院
			
			String hqlStr = "select distinct new org.king.classmanage.web.help.ClassAlertHistory"
				+ "(a.studentId,b.enterenceNo,b.stuName,a.classIdO,'','',"
				+ "a.classIdN,'','',a.operatorId,a.operatorTime) "
				+ "from ClassAlertHis a,GzStuTemp b "
				+ "where a.studentId=b.enterenceNo  ";

			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.enterenceNo like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and (a.classIdO = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " or a.classIdN = ?)" : "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime1) ? " and a.operatorTime >= ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime2) ? " and a.operatorTime <= ?"
					: "");
	
	
			if (StringUtils.isNotEmpty(studentNo)) {
				myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(stuName)) {
				myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(operatorTime1)) {
				myQuery.addPara(operatorTime1, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(operatorTime2)) {
				myQuery.addPara(operatorTime2, Types.VARCHAR);
			}
	
			// if (StringUtils.isNumeric(page)) {
			// myQuery.setPageStartNo(Integer.parseInt(page));
			// } else {
			// myQuery.setPageStartNo(0);
			// }
	
			if (orderby == null || orderby.length() == 0)
				myQuery.setOrderby(" order by a.operatorTime desc");
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("studentNo"))
				myQuery.setOrderby(" order by b.enterenceNo" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName"))
				myQuery.setOrderby(" order by b.stuName" + " " + odr);
			else if (orderby != null && orderby.length() > 0
					&& orderby.equals("operatetime"))
				myQuery.setOrderby(" order by a.operatorTime" + " " + odr);
	
			myQuery.setQueryString(hqlStr);
	
			// myQuery.setOffset(true);
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassAlertHistory classAlertHistory = (ClassAlertHistory) entitys
						.get(i);
				List list_ass_o = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassO() + "'");
				if (list_ass_o.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_o.get(0);
					classAlertHistory.setAssistantO(managermodel.getManagerName());
				}
				List list_cls_o = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassO()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_o.size() > 0) {
					Object[] classNo_O = (Object[]) list_cls_o.get(0);
					classAlertHistory.setClassO(classNo_O[0].toString());
					classAlertHistory.setCollegeO(classNo_O[1].toString());
				}
				List list_ass_n = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassN() + "'");
				if (list_ass_n.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_n.get(0);
					classAlertHistory.setAssistantN(managermodel.getManagerName());
				}
				List list_cls_n = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassN()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_n.size() > 0) {
					Object[] classNo_N = (Object[]) list_cls_n.get(0);
					classAlertHistory.setClassN(classNo_N[0].toString());
					classAlertHistory.setCollegeN(classNo_N[1].toString());
				}
	
			}
	
			// 其它字段排序
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("stuName")) {
				// Comparator comp1 = new Comparator() {
				// public int compare(Object o1, Object o2) {
				// ClassAlertHistory m1 = (ClassAlertHistory) o1;
				// ClassAlertHistory m2 = (ClassAlertHistory) o2;
				// //
				// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
				// String collegeName1 = (String) m1.getStuName();
				// String collegeName2 = (String) m2.getStuName();
				//
				// java.text.RuleBasedCollator collator = (RuleBasedCollator)
				// java.text.Collator
				// .getInstance(java.util.Locale.CHINA);
				// java.text.CollationKey c1 = collator
				// .getCollationKey(collegeName1);
				// java.text.CollationKey c2 = collator
				// .getCollationKey(collegeName2);
				// return c1.compareTo(c2);
				//
				// }
				// };
				// Comparator comp2 = new Comparator() {
				// public int compare(Object o1, Object o2) {
				// ClassAlertHistory m1 = (ClassAlertHistory) o1;
				// ClassAlertHistory m2 = (ClassAlertHistory) o2;
				// //
				// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
				// String collegeName1 = (String) m1.getStuName();
				// String collegeName2 = (String) m2.getStuName();
				//
				// java.text.RuleBasedCollator collator = (RuleBasedCollator)
				// java.text.Collator
				// .getInstance(java.util.Locale.CHINA);
				// java.text.CollationKey c1 = collator
				// .getCollationKey(collegeName1);
				// java.text.CollationKey c2 = collator
				// .getCollationKey(collegeName2);
				// return c2.compareTo(c1);
				//
				// }
				// };
				// if (odr.equals("asc"))
				// Collections.sort(entitys, comp1);
				// else
				// Collections.sort(entitys, comp2);
				Collator col = Collator.getInstance(Locale.CHINA);
				for (int i = entitys.size() - 1; i >= 1; i--) {
					for (int j = 0; j < i; j++) {
						ClassAlertHistory m1 = (ClassAlertHistory) entitys.get(j);
						ClassAlertHistory m2 = (ClassAlertHistory) entitys
								.get(j + 1);
						if (odr.equals("asc")) {
							if (col.compare(m1.getStuName(), m2.getStuName()) == -1) {
								Object temp = entitys.get(j);
								entitys.set(j, entitys.get(j + 1));
								entitys.set(j + 1, temp);
	
							}
						} else {
							if (col.compare(m1.getStuName(), m2.getStuName()) == 1) {
								Object temp = entitys.get(j);
								entitys.set(j, entitys.get(j + 1));
								entitys.set(j + 1, temp);
	
							}
						}
	
					}
				}
	
			}
	
			if (orderby != null && orderby.length() > 0 && orderby.equals("classO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassO() != null)
							collegeName1 = (String) m1.getClassO();
						if (m2.getClassO() != null)
							collegeName2 = (String) m2.getClassO();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassO() != null)
							collegeName1 = (String) m1.getClassO();
						if (m2.getClassO() != null)
							collegeName2 = (String) m2.getClassO();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("assistantO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantO();
						String collegeName2 = (String) m2.getAssistantO();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantO();
						String collegeName2 = (String) m2.getAssistantO();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("collegeO")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeO();
						String collegeName2 = (String) m2.getCollegeO();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeO();
						String collegeName2 = (String) m2.getCollegeO();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0 && orderby.equals("classN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassN() != null)
							collegeName1 = (String) m1.getClassN();
						if (m2.getClassN() != null)
							collegeName2 = (String) m2.getClassN();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = "";
						String collegeName2 = "";
						if (m1.getClassN() != null)
							collegeName1 = (String) m1.getClassN();
						if (m2.getClassN() != null)
							collegeName2 = (String) m2.getClassN();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("assistantN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantN();
						String collegeName2 = (String) m2.getAssistantN();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getAssistantN();
						String collegeName2 = (String) m2.getAssistantN();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("collegeN")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeN();
						String collegeName2 = (String) m2.getCollegeN();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getCollegeN();
						String collegeName2 = (String) m2.getCollegeN();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
	
			if (orderby != null && orderby.length() > 0
					&& orderby.equals("operator")) {
				Comparator comp1 = new Comparator() { // 升序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getOperator();
						String collegeName2 = (String) m2.getOperator();
	
						return collegeName1.compareTo(collegeName2);
					}
				};
				Comparator comp2 = new Comparator() { // 降序比较器
					public int compare(Object o1, Object o2) {
						ClassAlertHistory m1 = (ClassAlertHistory) o1;
						ClassAlertHistory m2 = (ClassAlertHistory) o2;
						// System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName"));
						String collegeName1 = (String) m1.getOperator();
						String collegeName2 = (String) m2.getOperator();
	
						return collegeName2.compareTo(collegeName1);
					}
				};
				if (odr.equals("asc"))
					Collections.sort(entitys, comp1);
				else
					Collections.sort(entitys, comp2);
	
			}
		}


		return entitys;
	}

	public List getAlertHistoryExport(String[] args,String schoolId) {
		String studentNo = args[0];
		String stuName = args[1];
		String classes = args[2];
		String operatorTime1 = args[3];
		String operatorTime2 = args[4];

		List entitys = null;
		String hqlStr = "";
		if (schoolId != null && schoolId.equals("0001")) {//复旦学院
			hqlStr = "select distinct new org.king.classmanage.web.help.ClassAlertHistory"
				+ "(a.studentId,b.studentNo,b.stuName,a.classIdO,'','',"
				+ "a.classIdN,'','',a.operatorId,a.operatorTime) "
				+ "from ClassAlertHis a,Studentmodel b "
				+ "where a.studentId=b.studentId and b.yxClass.yxCollege.yxSchool.schoolId='"+schoolId+"' ";	

			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and (a.classIdO = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " or a.classIdN = ?)" : "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime1) ? " and a.operatorTime >= ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime2) ? " and a.operatorTime <= ?"
					: "");
			MyQuery myQuery = new MyQuery();
	
			if (StringUtils.isNotEmpty(studentNo)) {
				myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(stuName)) {
				myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(operatorTime1)) {
				myQuery.addPara(operatorTime1, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(operatorTime2)) {
				myQuery.addPara(operatorTime2, Types.VARCHAR);
			}
	
			myQuery.setPageStartNo(0);
			myQuery.setOrderby(" order by a.operatorTime desc");
			myQuery.setQueryString(hqlStr);
	
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassAlertHistory classAlertHistory = (ClassAlertHistory) entitys
						.get(i);
				List list_ass_o = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassO() + "'");
				if (list_ass_o.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_o.get(0);
					classAlertHistory.setAssistantO(managermodel.getManagerName());
				}
				List list_cls_o = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassO()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_o.size() > 0) {
					Object[] classNo_O = (Object[]) list_cls_o.get(0);
					classAlertHistory.setClassO(classNo_O[0].toString());
					classAlertHistory.setCollegeO(classNo_O[1].toString());
				}
				List list_ass_n = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassN() + "'");
				if (list_ass_n.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_n.get(0);
					classAlertHistory.setAssistantN(managermodel.getManagerName());
				}
				List list_cls_n = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassN()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_n.size() > 0) {
					Object[] classNo_N = (Object[]) list_cls_n.get(0);
					classAlertHistory.setClassN(classNo_N[0].toString());
					classAlertHistory.setCollegeN(classNo_N[1].toString());
				}
	
			}
		}else if(schoolId != null && schoolId.equals("0002")){//护理学院
			
			hqlStr = "select distinct new org.king.classmanage.web.help.ClassAlertHistory"
				+ "(a.studentId,b.enterenceNo,b.stuName,a.classIdO,'','',"
				+ "a.classIdN,'','',a.operatorId,a.operatorTime) "
				+ "from ClassAlertHis a,GzStuTemp b "
				+ "where a.studentId=b.enterenceNo  ";

			hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.enterenceNo like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " and (a.classIdO = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(classes) ? " or a.classIdN = ?)" : "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime1) ? " and a.operatorTime >= ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(operatorTime2) ? " and a.operatorTime <= ?"
					: "");
			MyQuery myQuery = new MyQuery();
	
			if (StringUtils.isNotEmpty(studentNo)) {
				myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(stuName)) {
				myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(classes)) {
				myQuery.addPara(classes, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(operatorTime1)) {
				myQuery.addPara(operatorTime1, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(operatorTime2)) {
				myQuery.addPara(operatorTime2, Types.VARCHAR);
			}
	
			myQuery.setPageStartNo(0);
			myQuery.setOrderby(" order by a.operatorTime desc");
			myQuery.setQueryString(hqlStr);
	
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassAlertHistory classAlertHistory = (ClassAlertHistory) entitys
						.get(i);
				List list_ass_o = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassO() + "'");
				if (list_ass_o.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_o.get(0);
					classAlertHistory.setAssistantO(managermodel.getManagerName());
				}
				List list_cls_o = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassO()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_o.size() > 0) {
					Object[] classNo_O = (Object[]) list_cls_o.get(0);
					classAlertHistory.setClassO(classNo_O[0].toString());
					classAlertHistory.setCollegeO(classNo_O[1].toString());
				}
				List list_ass_n = managermodelDAO
						.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
								+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
								+ "and b.id.classId='"
								+ classAlertHistory.getClassN() + "'");
				if (list_ass_n.size() > 0) {
					Managermodel managermodel = (Managermodel) list_ass_n.get(0);
					classAlertHistory.setAssistantN(managermodel.getManagerName());
				}
				List list_cls_n = classmodelDAO
						.find("select a.classNo,b.collegeName from Classmodel a,Collegemodel b where a.classId='"
								+ classAlertHistory.getClassN()
								+ "' and a.yxCollege.collegeId=b.collegeId");
				if (list_cls_n.size() > 0) {
					Object[] classNo_N = (Object[]) list_cls_n.get(0);
					classAlertHistory.setClassN(classNo_N[0].toString());
					classAlertHistory.setCollegeN(classNo_N[1].toString());
				}
	
			}
		}
		return entitys;
	}

	public Integer getAlertHistoryCount(String[] args) {

		String studentNo = args[0];
		String stuName = args[1];
		String classes = args[2];
		String operatorTime1 = args[3];
		String operatorTime2 = args[4];

		Integer alertHisCount = new Integer("0");
		List entitys = null;
		String hqlStr = "select count(distinct a.operatorTime) "
				+ "from ClassAlertHis a,Studentmodel b,Classmodel c,Collegemodel d,"
				+ "Classmodel h,Collegemodel i "
				+ "where a.studentId=b.studentId and a.classIdO=c.classId and a.classIdN=h.classId "
				+ "and (b.yxClass.classId=c.classId or b.yxClass.classId=h.classId) "
				+ "and c.yxCollege.collegeId=d.collegeId "
				+ "and h.yxCollege.collegeId=i.collegeId ";

		hqlStr += (StringUtils.isNotEmpty(studentNo) ? " and b.studentNo like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(stuName) ? " and b.stuName like ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classes) ? " and c.classId = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(operatorTime1) ? " and a.operatorTime >= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(operatorTime2) ? " and a.operatorTime <= ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classes) ? " and h.classId = ?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(studentNo)) {
			myQuery.addPara("%" + studentNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(stuName)) {
			myQuery.addPara("%" + stuName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classes)) {
			myQuery.addPara(classes, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(operatorTime1)) {
			myQuery.addPara(operatorTime1, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(operatorTime2)) {
			myQuery.addPara(operatorTime2, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classes)) {
			myQuery.addPara(classes, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr);

		entitys = classmodelDAO.find(myQuery);
		if (entitys != null) {
			alertHisCount = (Integer) entitys.get(0);
		}
		return alertHisCount;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#saveAlertHistory(java.lang.String,
	 *      java.lang.String, java.lang.String)
	 */
	public void saveAlertHistory(String studentId, String classId_o,
			String classId_n) {
		// TODO Auto-generated method stub

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#findClass(java.lang.String[])
	 */
	public List findClass(String[] args) {
		String classId = args[0];
		String college = args[1];
		String assistant = args[2];
		String tutor1 = args[3];
		String page = args[4];
		
		String datebuf = sdf1.format(new Date());//查询当前年份的班级
		String schoolId = "0001";

		List entitys = null;

		String hqlStr = "select new org.king.classmanage.web.help.ClassWithManager"
				+ "(a.classId,a.classNo,a.className,a.introduction,b.collegeName) "
				+ "from ";
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += "Classmanager f,";
		}
		if (StringUtils.isNotEmpty(tutor1)) {
			hqlStr += "Classmanager j,";
		}
		hqlStr += "Classmodel a,Collegemodel b where a.yxCollege.collegeId=b.collegeId ";

		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += " and a.classId=f.id.classId ";
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " and f.id.managerId =?"
					: "");
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}

		} else {
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}
		}
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolId) ? " and a.yxCollege.yxSchool.schoolId = ?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor1)) {
			myQuery.addPara(tutor1, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(college)) {
			myQuery.addPara(college, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}		
		if (StringUtils.isNotEmpty(schoolId)) {
			myQuery.addPara(schoolId, Types.VARCHAR);
		}	

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setPageSize(100);
		myQuery.setOrderby(" order by b.collegeNo,a.classNo ");
		myQuery.setQueryString(hqlStr);
		myQuery.setOffset(true);
		entitys = classmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			ClassWithManager classwithmanager = (ClassWithManager) entitys
					.get(i);
			List list_ass = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId() + "'");
			if (list_ass.size() > 0) {
				Managermodel managermodel = (Managermodel) list_ass.get(0);
				classwithmanager
						.setAssistantName(managermodel.getManagerName());
			}
			List list_tutor = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='22' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId()
							+ "' and b.tutorType is null");
			if (1 == list_tutor.size()) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());

			} else if (list_tutor.size() >= 2) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());
				Managermodel managermodel1 = (Managermodel) list_tutor.get(1);
				classwithmanager.setTutor2Name(managermodel1.getManagerName());
				if (!"".equals(managermodel1.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel1.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel1.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor2org(managermodel1.getManagerOrg());
			}
		}
		return entitys;
	}
	
	public List findClass_hlxy(String[] args) {
		String classId = args[0];
//		String college = args[1];
		String assistant = args[1];
		String tutor1 = args[2];
		String page = args[3];
		
		String datebuf = sdf1.format(new Date());//查询当前年份的班级
		String schoolId = "0002";

		List entitys = null;

		String hqlStr = "select new org.king.classmanage.web.help.ClassWithManager"
				+ "(a.classId,a.classNo,a.className,a.introduction,b.collegeName) "
				+ "from ";
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += "Classmanager f,";
		}
		if (StringUtils.isNotEmpty(tutor1)) {
			hqlStr += "Classmanager j,";
		}
		hqlStr += "Classmodel a,Collegemodel b where a.yxCollege.collegeId=b.collegeId ";

		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += " and a.classId=f.id.classId ";
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " and f.id.managerId =?"
					: "");
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}

		} else {
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}
		}
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?" : "");
		
		hqlStr += (StringUtils.isNotEmpty(schoolId) ? " and a.yxCollege.yxSchool.schoolId = ?" : "");

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor1)) {
			myQuery.addPara(tutor1, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}		
		if (StringUtils.isNotEmpty(schoolId)) {
			myQuery.addPara(schoolId, Types.VARCHAR);
		}	

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setPageSize(100);
		myQuery.setOrderby(" order by b.collegeNo,a.classNo ");
		myQuery.setQueryString(hqlStr);
		myQuery.setOffset(true);
		entitys = classmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			ClassWithManager classwithmanager = (ClassWithManager) entitys
					.get(i);
			List list_ass = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId() + "'");
			if (list_ass.size() > 0) {
				Managermodel managermodel = (Managermodel) list_ass.get(0);
				classwithmanager
						.setAssistantName(managermodel.getManagerName());
			}
			List list_tutor = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='22' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId()
							+ "' and b.tutorType is null");
			if (1 == list_tutor.size()) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());

			} else if (list_tutor.size() >= 2) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());
				Managermodel managermodel1 = (Managermodel) list_tutor.get(1);
				classwithmanager.setTutor2Name(managermodel1.getManagerName());
				if (!"".equals(managermodel1.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel1.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel1.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor2org(managermodel1.getManagerOrg());
			}
		}
		return entitys;
	}	

	public List findClassExport(String[] args) {
		String classId = args[0];
		String college = args[1];
		String assistant = args[2];
		String tutor1 = args[3];
		String page = args[4];

		List entitys = null;

		String hqlStr = "select new org.king.classmanage.web.help.ClassWithManager"
				+ "(a.classId,a.classNo,a.className,a.introduction,b.collegeName) "
				+ "from ";
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += "Classmanager f,";
		}
		if (StringUtils.isNotEmpty(tutor1)) {
			hqlStr += "Classmanager j,";
		}
		hqlStr += "Classmodel a,Collegemodel b where a.yxCollege.collegeId=b.collegeId ";

		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += " and a.classId=f.id.classId ";
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " and f.id.managerId =?"
					: "");
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}

		} else {
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}
		}
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
				: "");
		
		String datebuf = sdf1.format(new Date());//当前年份	
		
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
				: "");
		hqlStr +=  " and a.yxCollege.yxSchool.schoolId = '0001' ";
		
		MyQuery myQuery = new MyQuery();
		
		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor1)) {
			myQuery.addPara(tutor1, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(college)) {
			myQuery.addPara(college, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}

		
		myQuery.setOrderby(" order by b.collegeNo,a.classNo ");
		myQuery.setQueryString(hqlStr);
		;
		entitys = classmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			ClassWithManager classwithmanager = (ClassWithManager) entitys
					.get(i);
			List list_ass = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId() + "'");
			if (list_ass.size() > 0) {
				Managermodel managermodel = (Managermodel) list_ass.get(0);
				classwithmanager
						.setAssistantName(managermodel.getManagerName());
			}
			List list_tutor = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='22' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId()
							+ "' and b.tutorType is null");
			if (1 == list_tutor.size()) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());

			} else if (list_tutor.size() >= 2) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());
				Managermodel managermodel1 = (Managermodel) list_tutor.get(1);
				classwithmanager.setTutor2Name(managermodel1.getManagerName());
				if (!"".equals(managermodel1.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel1.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel1.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor2org(managermodel1.getManagerOrg());
			}
		}
		return entitys;
	}
	
	public List findClassExport_hlxy(String[] args) {
		String classId = args[0];
		String assistant = args[1];
		String tutor1 = args[2];
		String page = args[3];

		List entitys = null;

		String hqlStr = "select new org.king.classmanage.web.help.ClassWithManager"
				+ "(a.classId,a.classNo,a.className,a.introduction,b.collegeName) "
				+ "from ";
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += "Classmanager f,";
		}
		if (StringUtils.isNotEmpty(tutor1)) {
			hqlStr += "Classmanager j,";
		}
		hqlStr += "Classmodel a,Collegemodel b where a.yxCollege.collegeId=b.collegeId ";

		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += " and a.classId=f.id.classId ";
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " and f.id.managerId =?"
					: "");
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}

		} else {
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}
		}
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		
		String datebuf = sdf1.format(new Date());//当前年份	
		
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
				: "");
		hqlStr +=  " and a.yxCollege.yxSchool.schoolId = '0002' ";
		
		MyQuery myQuery = new MyQuery();
		
		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor1)) {
			myQuery.addPara(tutor1, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}

		
		myQuery.setOrderby(" order by b.collegeNo,a.classNo ");
		myQuery.setQueryString(hqlStr);
		;
		entitys = classmodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			ClassWithManager classwithmanager = (ClassWithManager) entitys
					.get(i);
			List list_ass = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId() + "'");
			if (list_ass.size() > 0) {
				Managermodel managermodel = (Managermodel) list_ass.get(0);
				classwithmanager
						.setAssistantName(managermodel.getManagerName());
			}
			List list_tutor = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='22' "
							+ "and b.id.classId='"
							+ classwithmanager.getClassId()
							+ "' and b.tutorType is null");
			if (1 == list_tutor.size()) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());

			} else if (list_tutor.size() >= 2) {
				Managermodel managermodel = (Managermodel) list_tutor.get(0);
				classwithmanager.setTutor1Name(managermodel.getManagerName());
				if (!"".equals(managermodel.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor1org(managermodel.getManagerOrg());
				Managermodel managermodel1 = (Managermodel) list_tutor.get(1);
				classwithmanager.setTutor2Name(managermodel1.getManagerName());
				if (!"".equals(managermodel1.getManagerOrg())) {// 单位
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managermodel1.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						managermodel1.setManagerOrg(Cap);
					}
				}
				classwithmanager.setTutor2org(managermodel1.getManagerOrg());
			}
		}
		return entitys;
	}

	public Integer getClassCount_hlxy(String[] args) {
		String classId = args[0];
		String assistant = args[1];
		String tutor1 = args[2];
		Integer classCount = new Integer("0");
		List entitys = null;

		String hqlStr = "select count(distinct a.classId) " + "from ";
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += "Classmanager f,";
		}
		if (StringUtils.isNotEmpty(tutor1)) {
			hqlStr += "Classmanager j,";
		}
		hqlStr += "Classmodel a,Collegemodel b where a.yxCollege.collegeId=b.collegeId ";

		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += " and a.classId=f.id.classId ";
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " and f.id.managerId =?"
					: "");
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}

		} else {
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}
		}

		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");

		hqlStr +=  " and a.yxCollege.yxSchool.schoolId = '0002' ";
		hqlStr +=  " and a.curYear = '"+DateUtil.getNow("yyyy")+"' ";
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor1)) {
			myQuery.addPara(tutor1, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr);

		entitys = classmodelDAO.find(myQuery);
		if (entitys != null) {
			classCount = (Integer) entitys.get(0);
		}
		return classCount;

	}
	
	public Integer getClassCount(String[] args) {
		String classId = args[0];
		String collegeId = args[1];
		String assistant = args[2];
		String tutor1 = args[3];
		Integer classCount = new Integer("0");
		List entitys = null;

		String hqlStr = "select count(distinct a.classId) " + "from ";
		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += "Classmanager f,";
		}
		if (StringUtils.isNotEmpty(tutor1)) {
			hqlStr += "Classmanager j,";
		}
		hqlStr += "Classmodel a,Collegemodel b where a.yxCollege.collegeId=b.collegeId ";

		if (StringUtils.isNotEmpty(assistant)) {
			hqlStr += " and a.classId=f.id.classId ";
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " and f.id.managerId =?"
					: "");
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}

		} else {
			if (StringUtils.isNotEmpty(tutor1)) {
				hqlStr += " and a.classId=j.id.classId ";
				hqlStr += (StringUtils.isNotEmpty(tutor1) ? " and j.id.managerId = ?"
						: "");
			}
		}

		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and b.collegeId = ?"
				: "");
		hqlStr +=  " and a.yxCollege.yxSchool.schoolId = '0001' ";
		hqlStr +=  " and a.curYear = '"+DateUtil.getNow("yyyy")+"' ";
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor1)) {
			myQuery.addPara(tutor1, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(collegeId)) {
			myQuery.addPara(collegeId, Types.VARCHAR);
		}

		myQuery.setQueryString(hqlStr);

		entitys = classmodelDAO.find(myQuery);
		if (entitys != null) {
			classCount = (Integer) entitys.get(0);
		}
		return classCount;

	}

	public List findClassSearch(String[] args,String schoolId) {
		
		String classId = args[0];
		String college = args[1];
		String assistant = args[2];
		String location = args[3];
		String dormitory = args[4];
		String roomnumber = args[5];
		String page = args[6];
		String area = args[7];
		String direction = args[8];		
		
		String datebuf = sdf1.format(new Date());
		
		List entitys = null;
		if (schoolId != null && schoolId.equals("0001")) {//复旦学院
			//-------------------------------------------------------------
			String hqlStr = "select  new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,f.accomodation,f.area,f.direction) "
				+ "from Classmodel a,Collegemodel b ";
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += ",Managermodel c,Managermanagerrole d,Classmanager e ";
			}
			hqlStr += ",Dormitorymodel f "
					+ "where a.yxCollege.collegeId=b.collegeId and a.classId=f.classId and a.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
			hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
					: "");
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.classId=e.id.classId and c.managerId=d.id.managerId and e.id.managerId=c.managerId and d.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.id.managerId = ?"
						: "");
			}
			hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
					: "");
			
			hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
					: "");
			
			hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
					: "");
			
			MyQuery myQuery = new MyQuery();
	
			if (StringUtils.isNotEmpty(classId)) {
				myQuery.addPara(classId, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(college)) {
				myQuery.addPara(college, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(assistant)) {
				myQuery.addPara(assistant, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(direction)) {
				myQuery.addPara(direction, Types.VARCHAR);
			}			
			
			if (StringUtils.isNotEmpty(datebuf)) {
				myQuery.addPara(datebuf, Types.VARCHAR);
			}
	
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
			myQuery
					.setOrderby(" order by b.collegeName,a.classNo,f.area,f.location,f.dormitory,f.roomNumber");
			myQuery.setQueryString(hqlStr);
			myQuery.setPageSize(100);
			myQuery.setOffset(true);
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
						.get(i);
	
				String clsssIdCode = "";
				String clsmanagerStr = "";
				if (!"".equals(classwithdormitory.getClassId())) {
					if (clsssIdCode.equals(classwithdormitory.getClassId())) {
						classwithdormitory.setAssistantName(clsmanagerStr);
					} else {
						clsssIdCode = classwithdormitory.getClassId();
						List list_ass = managermodelDAO
								.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
										+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
										+ "and b.id.classId='"
										+ classwithdormitory.getClassId() + "'");
						if (list_ass.size() > 0) {
							Managermodel managermodel = (Managermodel) list_ass
									.get(0);
							clsmanagerStr = managermodel.getManagerName();
							classwithdormitory.setAssistantName(clsmanagerStr);
						}
					}
				}
		//------------------------------------------------------------------		
				if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String areaCode = "";
					String areaStr = "";
					if (!"".equals(classwithdormitory.getArea())) {// 校区
						if (areaCode.equals(classwithdormitory.getArea())) {
							classwithdormitory.setArea(areaStr);
						} else {
							areaCode = classwithdormitory.getArea();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getArea() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								areaStr = Cap;
								classwithdormitory.setArea(areaStr);
							}
						}
		
					}
				}
				
				if(schoolId!=null&&schoolId.equals("0001")){//复旦学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}
				}else if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}				
				}
				
				
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
					if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
						classwithdormitory.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = classwithdormitory.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDormitory() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							classwithdormitory.setDormitory(dormitoryStr);
						}
					}
	
				}
				
				String directionCode = "";
				String directionStr = "";
				if (!"".equals(classwithdormitory.getDirection())) {// 朝向
					if (directionCode.equals(classwithdormitory.getDirection())) {
						classwithdormitory.setDirection(directionStr);
					} else {
						directionCode = classwithdormitory.getDirection();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDirection() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							directionStr = Cap;
							classwithdormitory.setDirection(directionStr);
						}
					}
	
				}
				
				String genderCode = "";
				String genderStr = "";
				if (!"".equals(classwithdormitory.getGender())) {// 性别
					if (genderCode.equals(classwithdormitory.getGender())) {
						classwithdormitory.setGender(genderStr);
					} else {
						genderCode = classwithdormitory.getGender();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getGender() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							genderStr = Cap;
							classwithdormitory.setGender(genderStr);
						}
					}
	
				}
	
			}
		} else if (schoolId != null && schoolId.equals("0002")) {//护理学院
			//--------------------------------------------------------------------
			String hqlStr = "select new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,g.distributeNum,f.area,f.direction) "
				+ "from ClassDorm g,Classmodel a,Collegemodel b ";
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += ",Managermodel c,Managermanagerrole d,Classmanager e ";
			}
			hqlStr += ",Dormitorymodel f "
					+ "where a.yxCollege.collegeId=b.collegeId " +
							"and g.classId=a.classId " +
							"and g.dormId=f.dormitoryId " +
							"and a.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
			hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
					: "");
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.classId=e.id.classId and c.managerId=d.id.managerId and e.id.managerId=c.managerId and d.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.id.managerId = ?"
						: "");
			}
			hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
					: "");			
			
			hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
					: "");
			
			MyQuery myQuery = new MyQuery();
	
			if (StringUtils.isNotEmpty(classId)) {
				myQuery.addPara(classId, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(college)) {
				myQuery.addPara(college, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(assistant)) {
				myQuery.addPara(assistant, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(direction)) {
				myQuery.addPara(direction, Types.VARCHAR);
			}			
			
			if (StringUtils.isNotEmpty(datebuf)) {
				myQuery.addPara(datebuf, Types.VARCHAR);
			}
	
			if (StringUtils.isNumeric(page)) {
				myQuery.setPageStartNo(Integer.parseInt(page));
			} else {
				myQuery.setPageStartNo(0);
			}
			myQuery
					.setOrderby(" order by b.collegeName,a.classNo,f.area,f.location,f.dormitory,f.roomNumber");
			myQuery.setQueryString(hqlStr);
			myQuery.setPageSize(100);
			myQuery.setOffset(true);
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
						.get(i);
	
				String clsssIdCode = "";
				String clsmanagerStr = "";
				if (!"".equals(classwithdormitory.getClassId())) {
					if (clsssIdCode.equals(classwithdormitory.getClassId())) {
						classwithdormitory.setAssistantName(clsmanagerStr);
					} else {
						clsssIdCode = classwithdormitory.getClassId();
						List list_ass = managermodelDAO
								.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
										+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
										+ "and b.id.classId='"
										+ classwithdormitory.getClassId() + "'");
						if (list_ass.size() > 0) {
							Managermodel managermodel = (Managermodel) list_ass
									.get(0);
							clsmanagerStr = managermodel.getManagerName();
							classwithdormitory.setAssistantName(clsmanagerStr);
						}
					}
				}
		//------------------------------------------------------------------		
				if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String areaCode = "";
					String areaStr = "";
					if (!"".equals(classwithdormitory.getArea())) {// 校区
						if (areaCode.equals(classwithdormitory.getArea())) {
							classwithdormitory.setArea(areaStr);
						} else {
							areaCode = classwithdormitory.getArea();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getArea() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								areaStr = Cap;
								classwithdormitory.setArea(areaStr);
							}
						}
		
					}
				}
				
				if(schoolId!=null&&schoolId.equals("0001")){//复旦学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}
				}else if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}				
				}
				
				
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
					if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
						classwithdormitory.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = classwithdormitory.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDormitory() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							classwithdormitory.setDormitory(dormitoryStr);
						}
					}
	
				}
				
				String directionCode = "";
				String directionStr = "";
				if (!"".equals(classwithdormitory.getDirection())) {// 朝向
					if (directionCode.equals(classwithdormitory.getDirection())) {
						classwithdormitory.setDirection(directionStr);
					} else {
						directionCode = classwithdormitory.getDirection();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDirection() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							directionStr = Cap;
							classwithdormitory.setDirection(directionStr);
						}
					}
	
				}
				
				String genderCode = "";
				String genderStr = "";
				if (!"".equals(classwithdormitory.getGender())) {// 性别
					if (genderCode.equals(classwithdormitory.getGender())) {
						classwithdormitory.setGender(genderStr);
					} else {
						genderCode = classwithdormitory.getGender();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getGender() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							genderStr = Cap;
							classwithdormitory.setGender(genderStr);
						}
					}
	
				}
	
			}
		}


		return entitys;
	}

	public List findClassSearchExport(String[] args,String schoolId) {
		String classId = args[0];
		String college = args[1];
		String assistant = args[2];
		String location = args[3];
		String dormitory = args[4];
		String roomnumber = args[5];
		
		String area = args[7];
		String direction = args[8];
		
		String datebuf = sdf1.format(new Date());//当前年份		
		
		List entitys = null;
		MyQuery myQuery = new MyQuery();
		
		if (schoolId != null && schoolId.equals("0001")) {//复旦学院
			String hqlStr = "select new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,f.accomodation,f.area,f.direction) "
				+ "from Classmodel a,Collegemodel b ";
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += ",Managermodel c,Managermanagerrole d,Classmanager e ";
			}
			hqlStr += ",Dormitorymodel f "
					+ "where a.yxCollege.collegeId=b.collegeId and a.classId=f.classId and a.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
			hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
					: "");
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.classId=e.id.classId and c.managerId=d.id.managerId and e.id.managerId=c.managerId and d.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.id.managerId = ?"
						: "");
			}
			hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
					: "");
			
			hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
					: "");
			
			hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
					: "");

	
			if (StringUtils.isNotEmpty(classId)) {
				myQuery.addPara(classId, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(college)) {
				myQuery.addPara(college, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(assistant)) {
				myQuery.addPara(assistant, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(direction)) {
				myQuery.addPara(direction, Types.VARCHAR);
			}			
			
			if (StringUtils.isNotEmpty(datebuf)) {
				myQuery.addPara(datebuf, Types.VARCHAR);
			}		
	
			myQuery.setPageStartNo(0);
			myQuery
					.setOrderby(" order by b.collegeName,a.classNo,f.area,f.location,f.dormitory,f.roomNumber");
			myQuery.setQueryString(hqlStr);
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
						.get(i);
	
				String clsssIdCode = "";
				String clsmanagerStr = "";
				if (!"".equals(classwithdormitory.getClassId())) {
					if (clsssIdCode.equals(classwithdormitory.getClassId())) {
						classwithdormitory.setAssistantName(clsmanagerStr);
					} else {
						clsssIdCode = classwithdormitory.getClassId();
						List list_ass = managermodelDAO
								.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
										+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
										+ "and b.id.classId='"
										+ classwithdormitory.getClassId() + "'");
						if (list_ass.size() > 0) {
							Managermodel managermodel = (Managermodel) list_ass
									.get(0);
							clsmanagerStr = managermodel.getManagerName();
							classwithdormitory.setAssistantName(clsmanagerStr);
						}
					}
				}
	
				//------------------------------------------------------------------		
				if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String areaCode = "";
					String areaStr = "";
					if (!"".equals(classwithdormitory.getArea())) {// 校区
						if (areaCode.equals(classwithdormitory.getArea())) {
							classwithdormitory.setArea(areaStr);
						} else {
							areaCode = classwithdormitory.getArea();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getArea() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								areaStr = Cap;
								classwithdormitory.setArea(areaStr);
							}
						}
		
					}
				}
				
				if(schoolId!=null&&schoolId.equals("0001")){//复旦学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}
				}else if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}				
				}
				
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
					if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
						classwithdormitory.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = classwithdormitory.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDormitory() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							classwithdormitory.setDormitory(dormitoryStr);
						}
					}
	
				}
				
				String directionCode = "";
				String directionStr = "";
				if (!"".equals(classwithdormitory.getDirection())) {// 朝向
					if (directionCode.equals(classwithdormitory.getDirection())) {
						classwithdormitory.setDirection(directionStr);
					} else {
						directionCode = classwithdormitory.getDirection();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDirection() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							directionStr = Cap;
							classwithdormitory.setDirection(directionStr);
						}
					}
	
				}
				
				String genderCode = "";
				String genderStr = "";
				if (!"".equals(classwithdormitory.getGender())) {// 性别
					if (genderCode.equals(classwithdormitory.getGender())) {
						classwithdormitory.setGender(genderStr);
					} else {
						genderCode = classwithdormitory.getGender();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getGender() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							genderStr = Cap;
							classwithdormitory.setGender(genderStr);
						}
					}
	
				}
	
			}

		} else if (schoolId != null && schoolId.equals("0002")) {//护理学院
			String hqlStr = "select new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,g.distributeNum,f.area,f.direction) "
				+ "from ClassDorm g,Classmodel a,Collegemodel b ";
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += ",Managermodel c,Managermanagerrole d,Classmanager e ";
			}
			hqlStr += ",Dormitorymodel f "
					+ "where a.yxCollege.collegeId=b.collegeId " +
							"and g.classId=a.classId " +
							"and g.dormId=f.dormitoryId " +
							"and a.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
			hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
					: "");
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.classId=e.id.classId and c.managerId=d.id.managerId and e.id.managerId=c.managerId and d.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.id.managerId = ?"
						: "");
			}
			hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
					: "");			
			
			hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
					: "");
			
//			MyQuery myQuery = new MyQuery();
	
			if (StringUtils.isNotEmpty(classId)) {
				myQuery.addPara(classId, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(college)) {
				myQuery.addPara(college, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(assistant)) {
				myQuery.addPara(assistant, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(direction)) {
				myQuery.addPara(direction, Types.VARCHAR);
			}			
			
			if (StringUtils.isNotEmpty(datebuf)) {
				myQuery.addPara(datebuf, Types.VARCHAR);
			}
	
			myQuery.setPageStartNo(0);
			myQuery
					.setOrderby(" order by b.collegeName,a.classNo,f.area,f.location,f.dormitory,f.roomNumber");
			myQuery.setQueryString(hqlStr);
			entitys = classmodelDAO.find(myQuery);
	
			for (int i = 0; i < entitys.size(); i++) {
				ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
						.get(i);
	
				String clsssIdCode = "";
				String clsmanagerStr = "";
				if (!"".equals(classwithdormitory.getClassId())) {
					if (clsssIdCode.equals(classwithdormitory.getClassId())) {
						classwithdormitory.setAssistantName(clsmanagerStr);
					} else {
						clsssIdCode = classwithdormitory.getClassId();
						List list_ass = managermodelDAO
								.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
										+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
										+ "and b.id.classId='"
										+ classwithdormitory.getClassId() + "'");
						if (list_ass.size() > 0) {
							Managermodel managermodel = (Managermodel) list_ass
									.get(0);
							clsmanagerStr = managermodel.getManagerName();
							classwithdormitory.setAssistantName(clsmanagerStr);
						}
					}
				}
	
				//------------------------------------------------------------------		
				if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String areaCode = "";
					String areaStr = "";
					if (!"".equals(classwithdormitory.getArea())) {// 校区
						if (areaCode.equals(classwithdormitory.getArea())) {
							classwithdormitory.setArea(areaStr);
						} else {
							areaCode = classwithdormitory.getArea();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getArea() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								areaStr = Cap;
								classwithdormitory.setArea(areaStr);
							}
						}
		
					}
				}
				
				if(schoolId!=null&&schoolId.equals("0001")){//复旦学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}
				}else if(schoolId!=null&&schoolId.equals("0002")){//护理学院
					String locationCode = "";
					String locationStr = "";
					if (!"".equals(classwithdormitory.getLocation())) {// 校区
						if (locationCode.equals(classwithdormitory.getLocation())) {
							classwithdormitory.setLocation(locationStr);
						} else {
							locationCode = classwithdormitory.getLocation();
							List cap_list = studentmodelDAO
									.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
											+ "and a.id.dictValue='"
											+ classwithdormitory.getLocation() + "'");
		
							if (cap_list.size() > 0) {
								String Cap = cap_list.get(0).toString();
								locationStr = Cap;
								classwithdormitory.setLocation(locationStr);
							}
						}
		
					}				
				}
				
				String dormitoryCode = "";
				String dormitoryStr = "";
				if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
					if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
						classwithdormitory.setDormitory(dormitoryStr);
					} else {
						dormitoryCode = classwithdormitory.getDormitory();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDormitory() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							dormitoryStr = Cap;
							classwithdormitory.setDormitory(dormitoryStr);
						}
					}
	
				}
				
				String directionCode = "";
				String directionStr = "";
				if (!"".equals(classwithdormitory.getDirection())) {// 朝向
					if (directionCode.equals(classwithdormitory.getDirection())) {
						classwithdormitory.setDirection(directionStr);
					} else {
						directionCode = classwithdormitory.getDirection();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getDirection() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							directionStr = Cap;
							classwithdormitory.setDirection(directionStr);
						}
					}
	
				}				
				
				String genderCode = "";
				String genderStr = "";
				if (!"".equals(classwithdormitory.getGender())) {// 性别
					if (genderCode.equals(classwithdormitory.getGender())) {
						classwithdormitory.setGender(genderStr);
					} else {
						genderCode = classwithdormitory.getGender();
						List cap_list = studentmodelDAO
								.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
										+ "and a.id.dictValue='"
										+ classwithdormitory.getGender() + "'");
	
						if (cap_list.size() > 0) {
							String Cap = cap_list.get(0).toString();
							genderStr = Cap;
							classwithdormitory.setGender(genderStr);
						}
					}
	
				}
	
			}
		}		
		

		return entitys;
	}

	public List findfdyClassSearch(String[] args, String classId) {
		String location = args[0];
		String dormitory = args[1];
		String roomnumber = args[2];
		String page = args[3];
		String direction = args[4];
		
		String datebuf = sdf1.format(new Date());//增加当前年份		
		
		List entitys = null;
		String hqlStr = "select distinct new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,f.accomodation,f.area,f.direction) "
				+ "from Classmodel a,Collegemodel b ";
		hqlStr += ",Dormitorymodel f "
				+ "where a.yxCollege.collegeId=b.collegeId and a.classId=f.classId and a.yxCollege.yxSchool.schoolId='0001' ";
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");

		hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
				: "");		

		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
				: "");
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(direction)) {
			myQuery.addPara(direction, Types.VARCHAR);
		}		
		
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery
				.setOrderby(" order by b.collegeName,a.classNo,f.location,f.dormitory,f.roomNumber");
		myQuery.setQueryString(hqlStr);
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		entitys = classmodelDAO.find(myQuery);

		for (int i = 0; i < entitys.size(); i++) {
			ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
					.get(i);

			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(classwithdormitory.getClassId())) {
				if (clsssIdCode.equals(classwithdormitory.getClassId())) {
					classwithdormitory.setAssistantName(clsmanagerStr);
				} else {
					clsssIdCode = classwithdormitory.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ classwithdormitory.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						classwithdormitory.setAssistantName(clsmanagerStr);
					}
				}
			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(classwithdormitory.getLocation())) {// 校区
				if (locationCode.equals(classwithdormitory.getLocation())) {
					classwithdormitory.setLocation(locationStr);
				} else {
					locationCode = classwithdormitory.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						classwithdormitory.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
				if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
					classwithdormitory.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = classwithdormitory.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						classwithdormitory.setDormitory(dormitoryStr);
					}
				}

			}
			
			String directionCode = "";
			String directionStr = "";
			if (!"".equals(classwithdormitory.getDirection())) {// 朝向
				if (directionCode.equals(classwithdormitory.getDirection())) {
					classwithdormitory.setDirection(directionStr);
				} else {
					directionCode = classwithdormitory.getDirection();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDirection() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						directionStr = Cap;
						classwithdormitory.setDirection(directionStr);
					}
				}

			}			
			
			String genderCode = "";
			String genderStr = "";
			if (!"".equals(classwithdormitory.getGender())) {// 性别
				if (genderCode.equals(classwithdormitory.getGender())) {
					classwithdormitory.setGender(genderStr);
				} else {
					genderCode = classwithdormitory.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						classwithdormitory.setGender(genderStr);
					}
				}

			}

		}

		return entitys;
	}
	
	public List findfdyClassSearch_hlxy(String[] args, List classlist) {
		String location = args[0];
		String dormitory = args[1];
		String roomnumber = args[2];
		String page = args[3];
		String area = args[4];
		String direction = args[5];	
		
		String classIds = args[6];		

		String datebuf = sdf1.format(new Date());//增加当前年份		
		
		List entitys = null;
		String hqlStr = "select distinct new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,g.distributeNum,f.area,f.direction) "
				+ "from Classmodel a,Collegemodel b ";
		hqlStr += ",Dormitorymodel f,ClassDorm g "
				+ "where a.yxCollege.collegeId=b.collegeId " +
						"and a.classId=g.classId " +
						"and f.dormitoryId=g.dormId " +
						"and a.yxCollege.yxSchool.schoolId='0002' ";
		
		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and a.classId = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?" : "");

		hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
				: "");		

		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
				: "");
		hqlStr += "and a.classId in(";
		if(classlist!=null&&classlist.size()>0){
			for(int i=0;i<classlist.size();i++){
				HashMap hashmap =  (HashMap)classlist.get(i);
				String classId = (String)hashmap.get("classId");
				hqlStr += "'"+classId + "',";
			}
			
		}
		hqlStr = hqlStr.substring(0,(hqlStr.length()-1));
		hqlStr += ") ";
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}		
		
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(direction)) {
			myQuery.addPara(direction, Types.VARCHAR);
		}		
		
		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery
				.setOrderby(" order by b.collegeName,a.classNo,f.area,f.location,f.dormitory,f.roomNumber");
		myQuery.setQueryString(hqlStr);
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		entitys = classmodelDAO.find(myQuery);

		for (int i = 0; i < entitys.size(); i++) {
			ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
					.get(i);

			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(classwithdormitory.getClassId())) {
				if (clsssIdCode.equals(classwithdormitory.getClassId())) {
					classwithdormitory.setAssistantName(clsmanagerStr);
				} else {
					clsssIdCode = classwithdormitory.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ classwithdormitory.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						classwithdormitory.setAssistantName(clsmanagerStr);
					}
				}
			}
			
			String areaCode = "";
			String areaStr = "";
			if (!"".equals(classwithdormitory.getArea())) {// 大校区
				if (areaCode.equals(classwithdormitory.getArea())) {
					classwithdormitory.setArea(areaStr);
				} else {
					areaCode = classwithdormitory.getArea();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getArea() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						areaStr = Cap;
						classwithdormitory.setArea(areaStr);
					}
				}

			}			

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(classwithdormitory.getLocation())) {// 校区
				if (locationCode.equals(classwithdormitory.getLocation())) {
					classwithdormitory.setLocation(locationStr);
				} else {
					locationCode = classwithdormitory.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						classwithdormitory.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
				if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
					classwithdormitory.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = classwithdormitory.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						classwithdormitory.setDormitory(dormitoryStr);
					}
				}

			}
			
			String directionCode = "";
			String directionStr = "";
			if (!"".equals(classwithdormitory.getDirection())) {// 朝向
				if (directionCode.equals(classwithdormitory.getDirection())) {
					classwithdormitory.setDirection(directionStr);
				} else {
					directionCode = classwithdormitory.getDirection();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDirection() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						directionStr = Cap;
						classwithdormitory.setDirection(directionStr);
					}
				}

			}			
			
			String genderCode = "";
			String genderStr = "";
			if (!"".equals(classwithdormitory.getGender())) {// 性别
				if (genderCode.equals(classwithdormitory.getGender())) {
					classwithdormitory.setGender(genderStr);
				} else {
					genderCode = classwithdormitory.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						classwithdormitory.setGender(genderStr);
					}
				}

			}

		}

		return entitys;
	}

	public List findfdyClassSearchExport(String[] args, String classId) {
		String location = args[0];
		String dormitory = args[1];
		String roomnumber = args[2];
		String direction = args[3];
		
		List entitys = null;
		String hqlStr = "select distinct new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'',f.location,f.dormitory,f.roomNumber,f.gender,f.telphone,f.accomodation,f.area,f.direction) "
				+ "from Classmodel a,Collegemodel b ";
		hqlStr += ",Dormitorymodel f "
				+ "where a.yxCollege.collegeId=b.collegeId " +
						"and a.classId=f.classId " +
						"and a.yxCollege.yxSchool.schoolId='0001' " +
						"and a.curYear='"+DateUtil.getNow("yyyy")+"' ";
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");

		hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
				: "");		
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(direction)) {
			myQuery.addPara(direction, Types.VARCHAR);
		}		

		myQuery.setPageStartNo(0);
		myQuery
				.setOrderby(" order by b.collegeName,a.classNo,f.location,f.dormitory,f.roomNumber");
		myQuery.setQueryString(hqlStr);
		entitys = classmodelDAO.find(myQuery);

		for (int i = 0; i < entitys.size(); i++) {
			ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
					.get(i);

			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(classwithdormitory.getClassId())) {
				if (clsssIdCode.equals(classwithdormitory.getClassId())) {
					classwithdormitory.setAssistantName(clsmanagerStr);
				} else {
					clsssIdCode = classwithdormitory.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ classwithdormitory.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						classwithdormitory.setAssistantName(clsmanagerStr);
					}
				}
			}

			String locationCode = "";
			String locationStr = "";
			if (!"".equals(classwithdormitory.getLocation())) {// 校区
				if (locationCode.equals(classwithdormitory.getLocation())) {
					classwithdormitory.setLocation(locationStr);
				} else {
					locationCode = classwithdormitory.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 6 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						classwithdormitory.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
				if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
					classwithdormitory.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = classwithdormitory.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 7 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						classwithdormitory.setDormitory(dormitoryStr);
					}
				}

			}
			
			String directionCode = "";
			String directionStr = "";
			if (!"".equals(classwithdormitory.getDirection())) {// 朝向
				if (directionCode.equals(classwithdormitory.getDirection())) {
					classwithdormitory.setDirection(directionStr);
				} else {
					directionCode = classwithdormitory.getDirection();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDirection() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						directionStr = Cap;
						classwithdormitory.setDirection(directionStr);
					}
				}

			}			
			
			String genderCode = "";
			String genderStr = "";
			if (!"".equals(classwithdormitory.getGender())) {// 性别
				if (genderCode.equals(classwithdormitory.getGender())) {
					classwithdormitory.setGender(genderStr);
				} else {
					genderCode = classwithdormitory.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						classwithdormitory.setGender(genderStr);
					}
				}

			}

		}

		return entitys;
	}
	
	public List findfdyClassSearchExport_hlxy(String[] args, List classlist) {
		String location = args[0];
		String dormitory = args[1];
		String roomnumber = args[2];
		String area = args[4];
		String direction = args[5];		
		
		String classIds = args[6];	
		
		List entitys = null;
		String hqlStr = "select distinct new org.king.classmanage.web.help.ClassWithDormitory"
				+ "(a.classId," +
						"a.classNo," +
						"a.className," +
						"b.collegeName," +
						"''," +
						"f.location," +
						"f.dormitory," +
						"f.roomNumber," +
						"f.gender," +
						"f.telphone," +
						"g.distributeNum," +
						"f.area," +
						"f.direction) "
				+ "from Classmodel a,Collegemodel b ";
		hqlStr += ",Dormitorymodel f,ClassDorm g "
				+ "where a.yxCollege.collegeId=b.collegeId " +
					"and a.classId=g.classId " +
					"and f.dormitoryId=g.dormId " +
					"and a.yxCollege.yxSchool.schoolId='0002' " +
					"and a.curYear='"+DateUtil.getNow("yyyy")+"' ";
		
		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and a.classId = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?" : "");

		hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
				: "");		
		
		hqlStr += "and a.classId in(";
		if(classlist!=null&&classlist.size()>0){
			for(int i=0;i<classlist.size();i++){
				HashMap hashmap =  (HashMap)classlist.get(i);
				String classId = (String)hashmap.get("classId");
				hqlStr += "'"+classId + "',";
			}
			
		}
		hqlStr = hqlStr.substring(0,(hqlStr.length()-1));
		hqlStr += ") ";
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(direction)) {
			myQuery.addPara(direction, Types.VARCHAR);
		}		

		myQuery.setPageStartNo(0);
		myQuery
				.setOrderby(" order by b.collegeName,a.classNo,f.area,f.location,f.dormitory,f.roomNumber");
		myQuery.setQueryString(hqlStr);
		entitys = classmodelDAO.find(myQuery);

		for (int i = 0; i < entitys.size(); i++) {
			ClassWithDormitory classwithdormitory = (ClassWithDormitory) entitys
					.get(i);

			String clsssIdCode = "";
			String clsmanagerStr = "";
			if (!"".equals(classwithdormitory.getClassId())) {
				if (clsssIdCode.equals(classwithdormitory.getClassId())) {
					classwithdormitory.setAssistantName(clsmanagerStr);
				} else {
					clsssIdCode = classwithdormitory.getClassId();
					List list_ass = managermodelDAO
							.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
									+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
									+ "and b.id.classId='"
									+ classwithdormitory.getClassId() + "'");
					if (list_ass.size() > 0) {
						Managermodel managermodel = (Managermodel) list_ass
								.get(0);
						clsmanagerStr = managermodel.getManagerName();
						classwithdormitory.setAssistantName(clsmanagerStr);
					}
				}
			}
			
			String areaCode = "";
			String areaStr = "";
			if (!"".equals(classwithdormitory.getArea())) {// 大校区
				if (areaCode.equals(classwithdormitory.getArea())) {
					classwithdormitory.setArea(areaStr);
				} else {
					areaCode = classwithdormitory.getArea();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 17 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getArea() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						areaStr = Cap;
						classwithdormitory.setArea(areaStr);
					}
				}

			}
			
			String locationCode = "";
			String locationStr = "";
			if (!"".equals(classwithdormitory.getLocation())) {// 校区
				if (locationCode.equals(classwithdormitory.getLocation())) {
					classwithdormitory.setLocation(locationStr);
				} else {
					locationCode = classwithdormitory.getLocation();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 20 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getLocation() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						locationStr = Cap;
						classwithdormitory.setLocation(locationStr);
					}
				}

			}
			String dormitoryCode = "";
			String dormitoryStr = "";
			if (!"".equals(classwithdormitory.getDormitory())) {// 楼号
				if (dormitoryCode.equals(classwithdormitory.getDormitory())) {
					classwithdormitory.setDormitory(dormitoryStr);
				} else {
					dormitoryCode = classwithdormitory.getDormitory();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 21 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDormitory() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						dormitoryStr = Cap;
						classwithdormitory.setDormitory(dormitoryStr);
					}
				}

			}
			
			String directionCode = "";
			String directionStr = "";
			if (!"".equals(classwithdormitory.getDirection())) {// 朝向
				if (directionCode.equals(classwithdormitory.getDirection())) {
					classwithdormitory.setDirection(directionStr);
				} else {
					directionCode = classwithdormitory.getDirection();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 24 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getDirection() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						directionStr = Cap;
						classwithdormitory.setDirection(directionStr);
					}
				}

			}			
			
			String genderCode = "";
			String genderStr = "";
			if (!"".equals(classwithdormitory.getGender())) {// 性别
				if (genderCode.equals(classwithdormitory.getGender())) {
					classwithdormitory.setGender(genderStr);
				} else {
					genderCode = classwithdormitory.getGender();
					List cap_list = studentmodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ classwithdormitory.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						classwithdormitory.setGender(genderStr);
					}
				}

			}

		}

		return entitys;
	}

	public Integer getClassSearchCount(String[] args,String schoolId) {
		String classId = args[0];
		String college = args[1];
		String assistant = args[2];
		String location = args[3];
		String dormitory = args[4];
		String roomnumber = args[5];
		String area = args[7];
		String direction = args[8];	
		
		Integer classCount = new Integer("0");
		List entitys = null;
		MyQuery myQuery = new MyQuery();		
		String datebuf = sdf1.format(new Date());//增加当前年份
		if (schoolId != null && schoolId.equals("0001")) {//复旦学院

				String hqlStr = "select count(*) "
					+ "from Classmodel a,Collegemodel b ";
				if (StringUtils.isNotEmpty(assistant)) {
					hqlStr += ",Managermodel c,Managermanagerrole d,Classmanager e ";
				}
				hqlStr += ",Dormitorymodel f "
						+ "where a.yxCollege.collegeId=b.collegeId and a.classId=f.classId and a.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
				hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
				hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
						: "");
				if (StringUtils.isNotEmpty(assistant)) {
					hqlStr += " and a.classId=e.id.classId and c.managerId=d.id.managerId and e.id.managerId=c.managerId and d.id.roleId='21' ";
					hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.id.managerId = ?"
							: "");
				}
				hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
						: "");
				
				hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
						: "");
				
				hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
						: "");
	
			if (StringUtils.isNotEmpty(classId)) {
				myQuery.addPara(classId, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(college)) {
				myQuery.addPara(college, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(assistant)) {
				myQuery.addPara(assistant, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(direction)) {
				myQuery.addPara(direction, Types.VARCHAR);
			}			
			
			if (StringUtils.isNotEmpty(datebuf)) {
				myQuery.addPara(datebuf, Types.VARCHAR);
			}
			
			myQuery.setQueryString(hqlStr);
		} else if (schoolId != null && schoolId.equals("0002")) {//护理学院
			String hqlStr = "select count(*) "
				+ "from ClassDorm g,Classmodel a,Collegemodel b ";
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += ",Managermodel c,Managermanagerrole d,Classmanager e ";
			}
			hqlStr += ",Dormitorymodel f "
					+ "where a.yxCollege.collegeId=b.collegeId " +
							"and g.classId=a.classId " +
							"and g.dormId=f.dormitoryId  " +
							"and a.yxCollege.yxSchool.schoolId='"+schoolId+"' ";
			hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
			hqlStr += (StringUtils.isNotEmpty(college) ? " and b.collegeId = ?"
					: "");
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += " and a.classId=e.id.classId and c.managerId=d.id.managerId and e.id.managerId=c.managerId and d.id.roleId='21' ";
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and e.id.managerId = ?"
						: "");
			}
			hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
					: "");			
			
			hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
					: "");
	
			if (StringUtils.isNotEmpty(classId)) {
				myQuery.addPara(classId, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(college)) {
				myQuery.addPara(college, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(assistant)) {
				myQuery.addPara(assistant, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(area)) {
				myQuery.addPara(area, Types.VARCHAR);
			}
			if (StringUtils.isNotEmpty(location)) {
				myQuery.addPara(location, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(dormitory)) {
				myQuery.addPara(dormitory, Types.VARCHAR);
			}
	
			if (StringUtils.isNotEmpty(roomnumber)) {
				myQuery.addPara(roomnumber, Types.VARCHAR);
			}
			
			if (StringUtils.isNotEmpty(direction)) {
				myQuery.addPara(direction, Types.VARCHAR);
			}			
			
			if (StringUtils.isNotEmpty(datebuf)) {
				myQuery.addPara(datebuf, Types.VARCHAR);
			}
			
			myQuery.setQueryString(hqlStr);
		}		


		entitys = classmodelDAO.find(myQuery);
		if (entitys != null) {
			classCount = (Integer) entitys.get(0);
		}
		return classCount;

	}

	public Integer getfdyClassSearchCount(String[] args, String classId) {
		String location = args[0];
		String dormitory = args[1];
		String roomnumber = args[2];
		Integer classCount = new Integer("0");
		List entitys = null;

		String datebuf = sdf1.format(new Date());//增加当前年份
		
		String hqlStr = "select count(*) "
				+ "from Classmodel a,Collegemodel b ";
		hqlStr += ",Dormitorymodel f "
				+ "where a.yxCollege.collegeId=b.collegeId and a.classId=f.classId and a.yxCollege.yxSchool.schoolId='0001' ";
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
				: "");
		
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
				: "");		
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}
		
		myQuery.setQueryString(hqlStr);

		entitys = classmodelDAO.find(myQuery);
		if (entitys != null) {
			classCount = (Integer) entitys.get(0);
		}
		return classCount;

	}
	
	public Integer getfdyClassSearchCount_hlxy(String[] args, List classlist) {
		String location = args[0];
		String dormitory = args[1];
		String roomnumber = args[2];
		String area = args[4];
		
		String direction = args[5];	
		
		String classIds = args[6];		
		
		Integer classCount = new Integer("0");
		List entitys = null;

		String datebuf = sdf1.format(new Date());//增加当前年份
		
		String hqlStr = "select count(*) "
				+ "from Classmodel a,Collegemodel b ";
		hqlStr += ",Dormitorymodel f,ClassDorm g "
				+ "where a.yxCollege.collegeId=b.collegeId " +
						"and a.classId=g.classId " +
						"and f.dormitoryId=g.dormId " +
						"and a.yxCollege.yxSchool.schoolId='0002' ";

		hqlStr += (StringUtils.isNotEmpty(classIds) ? " and a.classId = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(area) ? " and f.area = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(location) ? " and f.location = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(dormitory) ? " and f.dormitory = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(roomnumber) ? " and f.roomNumber = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(direction) ? " and f.direction = ?"
				: "");	
		
		hqlStr += (StringUtils.isNotEmpty(datebuf) ? " and a.curYear = ?"
				: "");	
		
		hqlStr += "and a.classId in(";
		if(classlist!=null&&classlist.size()>0){
			for(int i=0;i<classlist.size();i++){
				HashMap hashmap =  (HashMap)classlist.get(i);
				String classId = (String)hashmap.get("classId");
				hqlStr += "'"+classId + "',";
			}
			
		}
		hqlStr = hqlStr.substring(0,(hqlStr.length()-1));
		hqlStr += ") ";
		
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(classIds)) {
			myQuery.addPara(classIds, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(area)) {
			myQuery.addPara(area, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(location)) {
			myQuery.addPara(location, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(dormitory)) {
			myQuery.addPara(dormitory, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(roomnumber)) {
			myQuery.addPara(roomnumber, Types.VARCHAR);
		}
		
		if (StringUtils.isNotEmpty(direction)) {
			myQuery.addPara(direction, Types.VARCHAR);
		}	

		if (StringUtils.isNotEmpty(datebuf)) {
			myQuery.addPara(datebuf, Types.VARCHAR);
		}
		
		myQuery.setQueryString(hqlStr);

		entitys = classmodelDAO.find(myQuery);
		if (entitys != null) {
			classCount = (Integer) entitys.get(0);
		}
		return classCount;

	}

	public List classResultStatistic(String schoolId) {
		
		String datebuf = sdf1.format(new Date());//当前年份	
		
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "(b.collegeId,a.classNo,count(c.studentId),0,0) "
						+ "from Classmodel a ,Collegemodel b,Studentmodel c "
						+ "where a.yxCollege.collegeId=b.collegeId "
						+ "and c.yxClass.classId=a.classId  and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+datebuf+"' "
						+ "group by b.collegeId,a.classNo "
						+ "order by b.collegeId,a.classNo");
		List maleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,count(c.studentId),0) "
						+ "from Classmodel a ,Studentmodel c "
						+ "where c.yxClass.classId=a.classId and c.gender='1' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+datebuf+"' "
						+ "group by a.classNo " + "order by a.classNo");
		List femaleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,0,count(c.studentId)) "
						+ "from Classmodel a ,Studentmodel c "
						+ "where c.yxClass.classId=a.classId and c.gender='2' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+datebuf+"' "
						+ "group by a.classNo " + "order by a.classNo");

		int countMale = 0;
		int countFemale = 0;
		int countSum = 0;
		int allMale = 0;
		int allFemale = 0;
		int allSum = 0;
		String collegename = "";
		for (int i = 0; i < list.size(); i++) {
			ClassStatistic classstatistic = (ClassStatistic) list.get(i);
			for (int j = 0; j < maleList.size(); j++) {
				ClassStatistic male = (ClassStatistic) maleList.get(j);
				String classno = male.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuMale(male.getStuMale());
					maleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < femaleList.size(); k++) {
				ClassStatistic female = (ClassStatistic) femaleList.get(k);
				String classno = female.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuFemale(female.getStuFemale());
					femaleList.remove(k);
					break;
				}
			}
			if (collegename.equals(classstatistic.getCollegeName()) || i == 0) {
				countMale += classstatistic.getStuMale();
				countFemale += classstatistic.getStuFemale();
				countSum += classstatistic.getStuNumber();
				collegename = classstatistic.getCollegeName();
			}

			if (!collegename.equals(classstatistic.getCollegeName()) && i > 0) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				countMale = 0;
				countFemale = 0;
				countSum = 0;
				collegename = classstatistic.getCollegeName();
			}
			if (i == list.size() - 1) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i + 1, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				break;
			}
		}
		ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStuMale(allMale);
		addclass.setStuFemale(allFemale);
		addclass.setStuNumber(allSum);
		list.add(list.size(), addclass);

		return list;
	}

	public List classResultStatisticWithAbroad(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "(b.collegeId,a.classNo,count(c.studentId),0,0) "
						+ "from Classmodel a ,Collegemodel b,Studentmodel c "
						+ "where a.yxCollege.collegeId=b.collegeId "
						+ "and c.yxClass.classId=a.classId and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by b.collegeId,a.classNo "
						+ "order by b.collegeId,a.classNo");
		List maleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,count(c.studentId),0) "
						+ "from Classmodel a ,Studentmodel c "
						+ "where c.yxClass.classId=a.classId and c.nationality='CHN' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.classNo " + "order by a.classNo");
		List femaleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,0,count(c.studentId)) "
						+ "from Classmodel a ,Studentmodel c "
						+ "where c.yxClass.classId=a.classId and c.nationality<>'CHN' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.classNo " + "order by a.classNo");

		int countMale = 0;
		int countFemale = 0;
		int countSum = 0;
		int allMale = 0;
		int allFemale = 0;
		int allSum = 0;
		String collegename = "";
		for (int i = 0; i < list.size(); i++) {
			ClassStatistic classstatistic = (ClassStatistic) list.get(i);
			for (int j = 0; j < maleList.size(); j++) {
				ClassStatistic male = (ClassStatistic) maleList.get(j);
				String classno = male.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuMale(male.getStuMale());
					maleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < femaleList.size(); k++) {
				ClassStatistic female = (ClassStatistic) femaleList.get(k);
				String classno = female.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuFemale(female.getStuFemale());
					femaleList.remove(k);
					break;
				}
			}
			if (collegename.equals(classstatistic.getCollegeName()) || i == 0) {
				countMale += classstatistic.getStuMale();
				countFemale += classstatistic.getStuFemale();
				countSum += classstatistic.getStuNumber();
				collegename = classstatistic.getCollegeName();
			}

			if (!collegename.equals(classstatistic.getCollegeName()) && i > 0) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				countMale = 0;
				countFemale = 0;
				countSum = 0;
				collegename = classstatistic.getCollegeName();
			}
			if (i == list.size() - 1) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i + 1, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				break;
			}
		}
		ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStuMale(allMale);
		addclass.setStuFemale(allFemale);
		addclass.setStuNumber(allSum);
		list.add(list.size(), addclass);

		return list;
	}
	
	public List classCheckInResultStatistic(String schoolId) {
		
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "(b.collegeId,a.classNo,count(c.studentId),0,0) "
						+ "from Classmodel a ,Collegemodel b,Studentmodel c,Stucheckininfo d "
						+ "where a.yxCollege.collegeId=b.collegeId "
						+ "and c.yxClass.classId=a.classId "
						+ "and c.studentNo=d.studentNo and d.ifCheckedin='1' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by b.collegeId,a.classNo "
						+ "order by b.collegeId,a.classNo");
		List maleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,count(c.studentId),0) "
						+ "from Classmodel a ,Studentmodel c,Stucheckininfo d "
						+ "where c.yxClass.classId=a.classId and c.gender='1' "
						+ "and c.studentNo=d.studentNo and d.ifCheckedin='1'  and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.classNo " + "order by a.classNo");
		List femaleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,0,count(c.studentId)) "
						+ "from Classmodel a ,Studentmodel c,Stucheckininfo d "
						+ "where c.yxClass.classId=a.classId and c.gender='2' "
						+ "and c.studentNo=d.studentNo and d.ifCheckedin='1'  and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.classNo " + "order by a.classNo");

		int countMale = 0;
		int countFemale = 0;
		int countSum = 0;
		int allMale = 0;
		int allFemale = 0;
		int allSum = 0;
		String collegename = "";
		for (int i = 0; i < list.size(); i++) {
			ClassStatistic classstatistic = (ClassStatistic) list.get(i);
			for (int j = 0; j < maleList.size(); j++) {
				ClassStatistic male = (ClassStatistic) maleList.get(j);
				String classno = male.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuMale(male.getStuMale());
					maleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < femaleList.size(); k++) {
				ClassStatistic female = (ClassStatistic) femaleList.get(k);
				String classno = female.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuFemale(female.getStuFemale());
					femaleList.remove(k);
					break;
				}
			}
			if (collegename.equals(classstatistic.getCollegeName()) || i == 0) {
				countMale += classstatistic.getStuMale();
				countFemale += classstatistic.getStuFemale();
				countSum += classstatistic.getStuNumber();
				collegename = classstatistic.getCollegeName();
			}
			if (!collegename.equals(classstatistic.getCollegeName()) && i > 0) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				countMale = 0;
				countFemale = 0;
				countSum = 0;
				collegename = classstatistic.getCollegeName();
			}
			if (i == list.size() - 1) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i + 1, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				break;
			}
		}

		ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStuMale(allMale);
		addclass.setStuFemale(allFemale);
		addclass.setStuNumber(allSum);
		list.add(list.size(), addclass);
		return list;
	}
	
	public List classCheckInResultStatisticWithAbroad(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "(b.collegeId,a.classNo,count(c.studentId),0,0) "
						+ "from Classmodel a ,Collegemodel b,Studentmodel c,Stucheckininfo d "
						+ "where a.yxCollege.collegeId=b.collegeId "
						+ "and c.yxClass.classId=a.classId "
						+ "and c.studentNo=d.studentNo and d.ifCheckedin='1' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by b.collegeId,a.classNo "
						+ "order by b.collegeId,a.classNo");
		List maleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,count(c.studentId),0) "
						+ "from Classmodel a ,Studentmodel c,Stucheckininfo d "
						+ "where c.yxClass.classId=a.classId and c.nationality='CHN' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "and c.studentNo=d.studentNo and d.ifCheckedin='1' "
						+ "group by a.classNo " + "order by a.classNo");
		List femaleList = classmodelDAO
				.find("select new org.king.classmanage.web.help.ClassStatistic"
						+ "('',a.classNo,0,0,count(c.studentId)) "
						+ "from Classmodel a ,Studentmodel c,Stucheckininfo d "
						+ "where c.yxClass.classId=a.classId and c.nationality<>'CHN' and a.yxCollege.yxSchool='"+schoolId+"' and a.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "and c.studentNo=d.studentNo and d.ifCheckedin='1' "
						+ "group by a.classNo " + "order by a.classNo");

		int countMale = 0;
		int countFemale = 0;
		int countSum = 0;
		int allMale = 0;
		int allFemale = 0;
		int allSum = 0;
		String collegename = "";
		for (int i = 0; i < list.size(); i++) {
			ClassStatistic classstatistic = (ClassStatistic) list.get(i);
			for (int j = 0; j < maleList.size(); j++) {
				ClassStatistic male = (ClassStatistic) maleList.get(j);
				String classno = male.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuMale(male.getStuMale());
					maleList.remove(j);
					break;
				}
			}
			for (int k = 0; k < femaleList.size(); k++) {
				ClassStatistic female = (ClassStatistic) femaleList.get(k);
				String classno = female.getClassName();
				if (classno.equals(classstatistic.className)) {
					classstatistic.setStuFemale(female.getStuFemale());
					femaleList.remove(k);
					break;
				}
			}
			if (collegename.equals(classstatistic.getCollegeName()) || i == 0) {
				countMale += classstatistic.getStuMale();
				countFemale += classstatistic.getStuFemale();
				countSum += classstatistic.getStuNumber();
				collegename = classstatistic.getCollegeName();
			}
			if (!collegename.equals(classstatistic.getCollegeName()) && i > 0) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				countMale = 0;
				countFemale = 0;
				countSum = 0;
				collegename = classstatistic.getCollegeName();
			}
			if (i == list.size() - 1) {
				ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStuMale(countMale);
				addclass.setStuFemale(countFemale);
				addclass.setStuNumber(countSum);
				list.add(i + 1, addclass);
				allMale += countMale;
				allFemale += countFemale;
				allSum += countSum;
				break;
			}
		}

		ClassStatistic addclass = new ClassStatistic("", "", 0, 0, 0);
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStuMale(allMale);
		addclass.setStuFemale(allFemale);
		addclass.setStuNumber(allSum);
		list.add(list.size(), addclass);
		return list;
	}

	public List nationList() {
		List nationList = classmodelDAO
				.find("select distinct a.nation from Studentmodel a " +
						"where a.majorin<>'623' and a.yxClass is not null " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' and (a.nation<>'' or a.nation is not null)");
		String nationStr = "";
		for (int i = 0; i < nationList.size(); i++) {
			if (i < nationList.size() - 1) {
				nationStr += "'" + nationList.get(i).toString() + "',";
			} else {
				nationStr += "'" + nationList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(nationStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=2 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=2 and a.id.dictValue in ("
					+ nationStr
					+ ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}

	public List nationCheckInList() {
		List nationList = classmodelDAO
				.find("select distinct a.nation from Studentmodel a,Stucheckininfo b " +
						"where a.majorin<>'623' and a.yxClass is not null " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' "
						+ "and (a.nation<>'' or a.nation is not null) and a.studentNo=b.studentNo and b.ifCheckedin='1' ");
		String nationStr = "";
		for (int i = 0; i < nationList.size(); i++) {
			if (i < nationList.size() - 1) {
				nationStr += "'" + nationList.get(i).toString() + "',";
			} else {
				nationStr += "'" + nationList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(nationStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=2 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=2 and a.id.dictValue in ("
					+ nationStr
					+ ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}

	public List nationResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.nation) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.yxSchool='"+schoolId+"'  and b.curYear='"+DateUtil.getNow("yyyy")+"' " +
								"and b.yxCollege.collegeId=c.collegeId " +
								"and (a.nation<>'' or a.nation is not null) "
						+ "group by a.nation,c.collegeId,b.classNo "
						+ "order by a.nation,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}

		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;

	}

	public List nationCheckInResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.nation) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c,Stucheckininfo d "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId "
						+ "and (a.nation<>'' or a.nation is not null) "
						+ "and a.studentNo=d.studentNo and d.ifCheckedin='1' and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.nation,c.collegeId,b.classNo "
						+ "order by a.nation,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}

			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}

	public List abroadMajorinResultStatistic() {
		return classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.majorin) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId "
						+ "and a.nation<>'CHN'"
						+ "group by a.majorin,c.collegeId,b.classNo "
						+ "order by c.collegeId,b.classNo");
	}

	public List getCollegeClassList(String schoolId) {
		return classmodelDAO
				.find("select new map (c.collegeId as collegeId," +
						" c.collegeNo as collegeNo," +
						" c.collegeName as collegeName," +
						" b.classNo as classNo) " +
						" from Classmodel b,Collegemodel c " +
						" where b.yxCollege.collegeId=c.collegeId " +
						"  and b.curYear='"+DateUtil.getNow("yyyy")+"' and b.yxCollege.yxSchool.schoolId='"+schoolId+"' " +
						" order by c.collegeNo,b.classNo ");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#abroadMajorinList()
	 */
	public List abroadMajorinList() {
		List abroadmajorList = classmodelDAO
				.find("select distinct a.majorin from Studentmodel a where a.yxClass is not null and a.nation<>'CHN'");
		String majorinStr = "";
		for (int i = 0; i < abroadmajorList.size(); i++) {
			if (i < abroadmajorList.size() - 1) {
				majorinStr += "'" + abroadmajorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + abroadmajorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=11 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=11 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}
	
	public List tempexamTypeStatistic(String schoolId) {
		List list = classmodelDAO
		.find("select new org.king.classmanage.web.help.NationDistributionInfo"
				+ "('',b.classNo,"
				+ "count(a.enterenceNo),a.examType) "
				+ "from GzStuTemp a,Classmodel b where " +
						"a.classId=b.classId " +						
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"group by a.examType,b.classNo " +
								"order by a.examType,b.classNo ");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}
/**
 * 高考入学前科类统计
 * @param schoolId
 * @return
 */
	public List examTypeStatistic(String schoolId) {
		List list = classmodelDAO
		.find("select new org.king.classmanage.web.help.NationDistributionInfo"
				+ "('',b.classNo,"
				+ "count(a.enterenceNo),a.examType) "
				+ "from GzStuTemp a,Classmodel b where " +
						"a.classId=b.classId " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"group by a.examType,b.classNo " +
								"order by a.examType,b.classNo ");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}
/**
 * 入学后高考科类统计
 * @param schoolId
 * @return
 */	
	public List examTypeCheckedinStatistic(String schoolId) {
		List list = classmodelDAO
		.find("select new org.king.classmanage.web.help.NationDistributionInfo"
				+ "('',b.classNo,"
				+ "count(a.enterenceNo),a.examType) "
				+ "from GzStuTemp a,Classmodel b,Stucheckininfo c where " +
						"a.classId=b.classId " +
						"and a.enterenceNo=c.enrollNo " +
						"and c.ifCheckedin='1' " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"group by a.examType,b.classNo " +
								"order by a.examType,b.classNo ");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}
	
	public List tempgenderStatistic(String schoolId) {
		List list = classmodelDAO
		.find("select new org.king.classmanage.web.help.NationDistributionInfo"
				+ "('',b.classNo,"
				+ "count(a.enterenceNo),a.gender) "
				+ "from GzStuTemp a,Classmodel b where " +
						"a.classId=b.classId " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"group by a.gender,b.classNo " +
								"order by a.gender,b.classNo ");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}
	
	//高职性别统计
	public List genderResultStatistic(String schoolId) {
		List list = classmodelDAO
		.find("select new org.king.classmanage.web.help.NationDistributionInfo"
				+ "('',b.classNo,"
				+ "count(a.enterenceNo),a.gender) "
				+ "from GzStuTemp a,Classmodel b where " +
						"a.classId=b.classId " +						
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"group by a.gender,b.classNo " +
								"order by a.gender,b.classNo ");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}
	//报名后高职性别统计
	public List genderCheckInResultStatistic(String schoolId) {
		List list = classmodelDAO
		.find("select new org.king.classmanage.web.help.NationDistributionInfo"
				+ "('',b.classNo,"
				+ "count(a.enterenceNo),a.gender) "
				+ "from GzStuTemp a,Classmodel b,Stucheckininfo c where " +
						"a.classId=b.classId " +
						"and a.enterenceNo=c.enrollNo " +
						"and c.ifCheckedin='1' " +
						"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"group by a.gender,b.classNo " +
								"order by a.gender,b.classNo ");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}	
			
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#majorinResultStatistic()
	 */
	public List majorinResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.majorin) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId " +
								"and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.majorin,c.collegeId,b.classNo "
						+ "order by a.majorin,c.collegeId,b.classNo");

		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}

	public List majorinCheckInResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.majorin) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c,Stucheckininfo d "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId " +
								"and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "and a.studentNo=d.studentNo and d.ifCheckedin='1' "
						+ "group by a.majorin,c.collegeId,b.classNo "
						+ "order by a.majorin,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}
			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}

	public List examTypeList() {
		List majorList = classmodelDAO
				.find("select distinct a.examType from GzStuTemp a " +
						"where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ");
		String majorinStr = "";
		for (int i = 0; i < majorList.size(); i++) {
			if (i < majorList.size() - 1) {
				majorinStr += "'" + majorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + majorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=25 order by a.id.dictValue";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=25 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictValue";
		}
		return classmodelDAO.find(sql);
	}
	
	public List examTypeCheckInList() {
		List majorList = classmodelDAO
				.find("select distinct a.examType from GzStuTemp a,Stucheckininfo b " +
						"where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"and a.enterenceNo=b.enrollNo and b.ifCheckedin='1' ");
		String majorinStr = "";
		for (int i = 0; i < majorList.size(); i++) {
			if (i < majorList.size() - 1) {
				majorinStr += "'" + majorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + majorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=25 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=25 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}
	
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#majorinList()
	 */
	public List majorinList() {
		List majorList = classmodelDAO
				.find("select distinct a.majorin from Studentmodel a where " +
						"a.majorin<>'623' and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"and  a.yxClass is not null");
		String majorinStr = "";
		for (int i = 0; i < majorList.size(); i++) {
			if (i < majorList.size() - 1) {
				majorinStr += "'" + majorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + majorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=11 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=11 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}

	public List majorinCheckInList() {
		List majorList = classmodelDAO
				.find("select distinct a.majorin from Studentmodel a,Stucheckininfo b  "
						+ "where a.majorin<>'623' and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"and a.yxClass is not null and a.studentNo=b.studentNo and b.ifCheckedin='1' ");
		String majorinStr = "";
		for (int i = 0; i < majorList.size(); i++) {
			if (i < majorList.size() - 1) {
				majorinStr += "'" + majorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + majorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=11 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=11 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}
/*
 * （非 Javadoc）
 * @see org.king.classmanage.service.ClassService#genderList()
 */	
	public List genderList() {
		List majorList = classmodelDAO
				.find("select distinct a.gender from GzStuTemp a " +
						"where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' ");
		String majorinStr = "";
		for (int i = 0; i < majorList.size(); i++) {
			if (i < majorList.size() - 1) {
				majorinStr += "'" + majorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + majorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=1 order by a.id.dictValue";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=1 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictValue";
		}
		return classmodelDAO.find(sql);
	}

	public List genderCheckInList() {
		List majorList = classmodelDAO
				.find("select distinct a.gender from GzStuTemp a,Stucheckininfo b " +
						"where 1=1 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"and  a.enterenceNo=b.enrollNo and b.ifCheckedin='1'  ");
		String majorinStr = "";
		for (int i = 0; i < majorList.size(); i++) {
			if (i < majorList.size() - 1) {
				majorinStr += "'" + majorList.get(i).toString() + "',";
			} else {
				majorinStr += "'" + majorList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(majorinStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=1 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=1 and a.id.dictValue in ("
					+ majorinStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#nativeplaceResultStatistic()
	 */
	public List nativeplaceResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.fromProvince) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' " +
								"and b.yxCollege.collegeId=c.collegeId " +
								"and (a.fromProvince<>'' or a.fromProvince is not null) "
						+ "group by a.fromProvince,c.collegeId,b.classNo "
						+ "order by a.fromProvince,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}

	public List nativeplaceCheckInResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.fromProvince) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c,Stucheckininfo d  "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId "
						+ "and (a.fromProvince<>'' or a.fromProvince is not null) "
						+ "and a.studentNo=d.studentNo and d.ifCheckedin='1' and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.fromProvince,c.collegeId,b.classNo "
						+ "order by a.fromProvince,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}

		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#provinceList()
	 */
	public List provinceList() {

		String sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
				+ "where a.id.dictNo=10 order by a.id.dictNo";

		return classmodelDAO.find(sql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#nationalityList()
	 */
	public List nationalityList() {
		List nationalityList = classmodelDAO
				.find("select distinct a.nationality from Studentmodel a " +
						"where (a.nationality is not null and a.nationality<>'') and a.majorin<>'623' and a.yxClass is not null and a.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		String nationalityStr = "";
		for (int i = 0; i < nationalityList.size(); i++) {
			if (i < nationalityList.size() - 1) {
				nationalityStr += "'" + nationalityList.get(i).toString()
						+ "',";
			} else {
				nationalityStr += "'" + nationalityList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(nationalityStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=12 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=12 and a.id.dictValue in ("
					+ nationalityStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ClassService#nationalityResultStatistic()
	 */
	public List nationalityResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.nationality) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' " +
								"and b.yxCollege.collegeId=c.collegeId " +
								"and (a.nationality<>'' or a.nationality is not null) "
						+ "group by a.nationality,c.collegeId,b.classNo "
						+ "order by a.nationality,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}
		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;

	}

	public List nationalityCheckInList() {
		List nationalityList = classmodelDAO
				.find("select distinct a.nationality from Studentmodel a,Stucheckininfo b "
						+ "where (a.nationality is not null and a.nationality<>'') and a.majorin<>'623' and a.yxClass is not null " +
								"and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
								"and a.studentNo=b.studentNo and b.ifCheckedin='1' ");
		String nationalityStr = "";
		for (int i = 0; i < nationalityList.size(); i++) {
			if (i < nationalityList.size() - 1) {
				nationalityStr += "'" + nationalityList.get(i).toString()
						+ "',";
			} else {
				nationalityStr += "'" + nationalityList.get(i).toString() + "'";
			}
		}
		String sql = "";
		if ("".equals(nationalityStr)) {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=12 order by a.id.dictNo";
		} else {
			sql = "select new map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a "
					+ "where a.id.dictNo=12 and a.id.dictValue in ("
					+ nationalityStr + ") order by a.id.dictNo";
		}
		return classmodelDAO.find(sql);
	}

	public List nationalityCheckInResultStatistic(String schoolId) {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(c.collegeId,b.classNo,"
						+ "count(a.studentId),a.nationality) "
						+ "from Studentmodel a,Classmodel b,Collegemodel c,Stucheckininfo d "
						+ "where a.yxClass.classId=b.classId and b.yxCollege.collegeId=c.collegeId "
						+ "and (a.nationality<>'' or a.nationality is not null) "
						+ "and a.studentNo=d.studentNo and d.ifCheckedin='1' and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by a.nationality,c.collegeId,b.classNo "
						+ "order by a.nationality,c.collegeId,b.classNo");
		int smallCount = 0;
		int allCount = 0;
		String collegename = "";
		String majorin = "";
		for (int i = 0; i < list.size(); i++) {
			NationDistributionInfo distributioninfo = (NationDistributionInfo) list
					.get(i);
			if (majorin.equals(distributioninfo.getNation()) || i == 0) {
				if (collegename.equals(distributioninfo.getCollegeName())
						|| i == 0) {
					smallCount += distributioninfo.getStudentCount();
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}

				if (!collegename.equals(distributioninfo.getCollegeName())
						&& i > 0) {
					NationDistributionInfo addclass = new NationDistributionInfo(
							"", "", 0, "");
					addclass.setCollegeName(collegename);
					addclass.setClassName("smallCount");
					addclass.setStudentCount(smallCount);
					addclass.setNation(majorin);
					list.add(i, addclass);
					allCount += smallCount;
					smallCount = 0;
					collegename = distributioninfo.getCollegeName();
					majorin = distributioninfo.getNation();
				}
			}

			if (!majorin.equals(distributioninfo.getNation()) && i > 0) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				NationDistributionInfo addclass1 = new NationDistributionInfo(
						"", "", 0, "");
				addclass1.setCollegeName("allCount");
				addclass1.setClassName("--");
				addclass1.setStudentCount(allCount);
				addclass1.setNation(majorin);
				list.add(i + 1, addclass1);
				i++;
				allCount = 0;
				smallCount = 0;
				collegename = distributioninfo.getCollegeName();
				majorin = distributioninfo.getNation();
			}
			if (i == list.size() - 1) {
				NationDistributionInfo addclass = new NationDistributionInfo(
						"", "", 0, "");
				addclass.setCollegeName(collegename);
				addclass.setClassName("smallCount");
				addclass.setStudentCount(smallCount);
				addclass.setNation(majorin);
				list.add(i, addclass);
				allCount += smallCount;
				smallCount = 0;
				break;
			}

		}

		NationDistributionInfo addclass = new NationDistributionInfo("", "", 0,
				"");
		addclass.setCollegeName("allCount");
		addclass.setClassName("--");
		addclass.setStudentCount(allCount);
		addclass.setNation(majorin);
		list.add(list.size(), addclass);

		return list;
	}
	
	public List daleiResultStatisticDormDistr() {
		List daleiResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.collegeId,'',"
						+ "count(a.studentId),d.id.dictValue) "
						+ "from Studentmodel a,DistributionTemp b,Dictionary c,Dictionary d "
						+ "where a.studentId=b.studentId and a.majorin=c.id.dictValue and a.enrollYear='"+DateUtil.getNow("yyyy")+"' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 "
						+ "group by d.id.dictValue,b.collegeId");
		List totleResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "('daleiCount','',"
						+ "count(a.studentId),d.id.dictValue) "
						+ "from Studentmodel a,DistributionTemp b,Dictionary c,Dictionary d "
						+ "where a.studentId=b.studentId and a.majorin=c.id.dictValue "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and a.enrollYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue");
		daleiResult.addAll(totleResult);
		return daleiResult;
	}

	public List daleiResultStatistic(String schoolId) {
		List daleiResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.yxCollege.collegeId,'',"
						+ "count(a.studentId),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 "
						+ "group by d.id.dictValue,b.yxCollege.collegeId");
		List totleResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "('daleiCount','',"
						+ "count(a.studentId),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue");
		daleiResult.addAll(totleResult);
		return daleiResult;
	}

	public List daleiCheckInResultStatistic(String schoolId) {
		List daleiResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.yxCollege.collegeId,'',"
						+ "count(a.studentId),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d,Stucheckininfo e "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and a.studentNo=e.studentNo and e.ifCheckedin='1' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue,b.yxCollege.collegeId");
		List totleResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "('daleiCount','',"
						+ "count(a.studentId),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d,Stucheckininfo e "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and a.studentNo=e.studentNo and e.ifCheckedin='1' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='"+schoolId+"' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue");
		daleiResult.addAll(totleResult);
		return daleiResult;
	}

	public List zhuanyeResultStatistic() {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.yxCollege.collegeId,b.classNo,"
						+ "count(distinct c.id.dictValue),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='0001' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue, b.yxCollege.collegeId,b.classNo");

		List collegeResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.yxCollege.collegeId,'smallCount',"
						+ "count(distinct c.id.dictValue),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='0001' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue,b.yxCollege.collegeId");
		List totleResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "('allCount','--',"
						+ "count(distinct c.id.dictValue),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='0001' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue");
		list.addAll(collegeResult);
		list.addAll(totleResult);
		return list;
	}

	public List zhuanyeCheckInResultStatistic() {
		List list = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.yxCollege.collegeId,b.classNo,"
						+ "count(distinct c.id.dictValue),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d,Stucheckininfo e "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and a.studentNo=e.studentNo and e.ifCheckedin='1' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='0001' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue, b.yxCollege.collegeId,b.classNo");

		List collegeResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "(b.yxCollege.collegeId,'smallCount',"
						+ "count(distinct c.id.dictValue),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d,Stucheckininfo e "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and a.studentNo=e.studentNo and e.ifCheckedin='1' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='0001' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue,b.yxCollege.collegeId");
		List totleResult = classmodelDAO
				.find("select new org.king.classmanage.web.help.NationDistributionInfo"
						+ "('allCount','--',"
						+ "count(distinct c.id.dictValue),d.id.dictValue) "
						+ "from Studentmodel a,Classmodel b,Dictionary c,Dictionary d,Stucheckininfo e "
						+ "where a.yxClass.classId=b.classId and a.majorin=c.id.dictValue "
						+ "and a.studentNo=e.studentNo and e.ifCheckedin='1' "
						+ "and c.id.dictNo=11 and c.dictParent1=d.id.dictValue and d.id.dictNo=14 and b.yxCollege.yxSchool='0001' and b.yxCollege.yxSchool='0001' and b.curYear='"+DateUtil.getNow("yyyy")+"' "
						+ "group by d.id.dictValue");
		list.addAll(collegeResult);
		list.addAll(totleResult);
		return list;
	}

	public List findClassList() {
		List entitys = null;
		String hqlStr = "select distinct new org.king.classmanage.web.help.AbroadClasses"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'') "
				+ "from Classmodel a,Collegemodel b "
				+ "where a.yxCollege.collegeId=b.collegeId order by a.classNo ";

		entitys = classmodelDAO.find(hqlStr);

		for (int i = 0; i < entitys.size(); i++) {
			AbroadClasses abroadclasses = (AbroadClasses) entitys.get(i);

			List list_ass = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
							+ "and b.id.classId='"
							+ abroadclasses.getClassId()
							+ "'");
			if (list_ass.size() > 0) {
				Managermodel managermodel = (Managermodel) list_ass.get(0);
				abroadclasses.setManagerName(managermodel.getManagerName());
			}
		}

		return entitys;
	}

	public List findClassList(String[] args) {
		String collegeId = args[0];
		String classId = args[1];
		List entitys = null;

		String hqlStr = "select distinct new org.king.classmanage.web.help.AbroadClasses"
				+ "(a.classId,a.classNo,a.className,b.collegeName,'') "
				+ "from Classmodel a,Collegemodel b "
				+ "where a.yxCollege.collegeId=b.collegeId ";

		hqlStr += (StringUtils.isNotEmpty(collegeId) ? " and b.collegeId = ?"
				: "");
		hqlStr += (StringUtils.isNotEmpty(classId) ? " and a.classId = ?" : "");
		MyQuery myQuery = new MyQuery();
		if (StringUtils.isNotEmpty(collegeId)) {
			myQuery.addPara(collegeId, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(classId)) {
			myQuery.addPara(classId, Types.VARCHAR);
		}
		myQuery.setOrderby(" order by b.collegeName,a.classNo");
		myQuery.setQueryString(hqlStr);
		entitys = classmodelDAO.find(myQuery);

		for (int i = 0; i < entitys.size(); i++) {
			AbroadClasses abroadclasses = (AbroadClasses) entitys.get(i);

			List list_ass = managermodelDAO
					.find("select a from Managermodel a,Classmanager b,Managermanagerrole c "
							+ " where a.managerId=b.id.managerId and a.managerId=c.id.managerId and c.id.roleId='21' "
							+ "and b.id.classId='"
							+ abroadclasses.getClassId()
							+ "'");
			if (list_ass.size() > 0) {
				Managermodel managermodel = (Managermodel) list_ass.get(0);
				abroadclasses.setManagerName(managermodel.getManagerName());
			}
		}

		return entitys;
	}

	public Collegemodel getCollegeByClassId(String classId) {
		Collegemodel c = null;
		List s = classmodelDAO
				.find("from Collegemodel c where c.collegeId in (select d.yxCollege.collegeId from Classmodel d where d.classId = '"
						+ classId + "')");
		if (s != null) {
			c = (Collegemodel) s.get(0);
		}
		return c;
	}

	/**
	 * @param collegemodelDAO
	 *            The collegemodelDAO to set.
	 */
	public void setCollegemodelDAO(CollegemodelDAO collegemodelDAO) {
		this.collegemodelDAO = collegemodelDAO;
	}
	
	public void initForm(HttpServletRequest request){
		
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 所有楼列表
//		List buildingList = studentService.getDiction("7");
//		// List buildingList = dormitoryService.getDormmitoryList();
//		request.setAttribute("buildingList", buildingList);	
		
		String getrole = request.getParameter("getrole");
		String xhorgh = (String)request.getSession().getAttribute("userName");
		String hql = "";
		List list = new ArrayList();
		
		if(getrole!=null&&("2".equals(getrole)||"3".equals(getrole))){//护理学院,研工部---------大校区,小校区
			
			hql="select distinct new Map(" +
			"c.id.dictValue as dictValue," +
			"c.dictCaption as dictCaption," +
			"c.dictParent as dictParent,c.dictSort) " +
			"from Dormitorymodel a,TabSsManager b,Dictionary c " +
			"where a.curDormDept=b.tabSsDept.id and b.stuNo='"+xhorgh+"' "  +
			" and a.area=c.id.dictValue and c.id.dictNo=17 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("areaList", list);
			
			hql="select distinct new Map(" +
			"c.id.dictValue as dictValue," +
			"c.dictCaption as dictCaption,c.dictParent as dictParent,a.area as area,c.dictSort) " +
			"from Dormitorymodel a,TabSsManager b,Dictionary c " +
			"where a.curDormDept=b.tabSsDept.id and b.stuNo='"+xhorgh+"' "  +
			" and a.location=c.id.dictValue and c.id.dictNo=20 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList", list);
			
			//用于不需权限控制的情况		护理学院	
			hql = "select distinct new Map(" + "c.id.dictValue as dictValue,"
				+ "c.dictCaption as dictCaption,"
				+ "c.dictParent as dictParent,c.dictSort) "
				+ "from Dormitorymodel a,TabSsDept b,Dictionary c "
				+ "where a.curDormDept=b.id and b.id='8a708026130a0e4501130a0f9a930003' "
				+ " and a.area=c.id.dictValue and c.id.dictNo=17 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("areaList1", list);
			
			hql = "select distinct new Map("
				+ "c.id.dictValue as dictValue,"
				+ "c.dictCaption as dictCaption,c.dictParent as dictParent," +
						"a.area as area,c.dictSort) "
				+ "from Dormitorymodel a,TabSsDept b,Dictionary c "
				+ "where a.curDormDept=b.id and b.id='8a708026130a0e4501130a0f9a930003' "
				+ " and a.location=c.id.dictValue and c.id.dictNo=20 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList1", list);
		}else{
			 hql="select distinct new Map(" +
			"c.id.dictValue as dictValue," +
			"c.dictCaption as dictCaption," +
			"c.dictParent as dictParent,c.dictSort) " +
			"from Dormitorymodel a,TabSsManager b,Dictionary c " +
			"where a.curDormDept=b.tabSsDept.id and b.stuNo='"+xhorgh+"' and a.distributeNum>0 "  +
			" and a.location=c.id.dictValue and c.id.dictNo=6 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("locationList", list);
			//用于不需权限控制的情况			
			 hql="select distinct new Map(" +
				"c.id.dictValue as dictValue," +
				"c.dictCaption as dictCaption," +
				"c.dictParent as dictParent,c.dictSort) " +
				"from Dictionary c " +
				"where 1=1 "  +
				" and  c.id.dictNo=6 order by c.dictSort ";
				list = classmodelDAO.find(hql);
				request.setAttribute("locationList1", list);
			
		}
		if(getrole!=null&&("2".equals(getrole)||"3".equals(getrole))){//护理学院,研工部---------楼号
			hql="select distinct new Map(" +
			"c.id.dictValue as dictValue," +
			"c.dictCaption as dictCaption," +
			"c.dictParent as dictParent,a.location as location,a.area as area,c.dictSort) " +
			"from Dormitorymodel a,TabSsManager b,Dictionary c " +
			"where a.curDormDept=b.tabSsDept.id and b.stuNo='"+xhorgh+"' " +
			" and a.dormitory=c.id.dictValue and c.id.dictNo=21 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("buildingList", list);
			
			//用于不需权限控制的情况		护理学院		
			hql = "select distinct new Map(" + "c.id.dictValue as dictValue,"
				+ "c.dictCaption as dictCaption,"
				+ "c.dictParent as dictParent,a.location as location,a.area as area,c.dictSort) "
				+ "from Dormitorymodel a,TabSsDept b,Dictionary c "
				+ "where a.curDormDept=b.id and b.id='8a708026130a0e4501130a0f9a930003' "
				+ " and a.dormitory=c.id.dictValue and c.id.dictNo=21 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("buildingList1", list);
		}else{
			hql="select distinct new Map(" +
			"c.id.dictValue as dictValue," +
			"c.dictCaption as dictCaption," +
			"c.dictParent as dictParent,a.location as location,c.dictSort) " +
			"from Dormitorymodel a,TabSsManager b,Dictionary c " +
			"where a.curDormDept=b.tabSsDept.id and b.stuNo='"+xhorgh+"' and a.distributeNum>0 " +
			" and a.dormitory=c.id.dictValue and c.id.dictNo=7 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("buildingList", list);
			//用于不需权限控制的情况
			hql="select distinct new Map(" +
			"c.id.dictValue as dictValue," +
			"c.dictCaption as dictCaption," +
			"c.dictParent as dictParent,a.location as location,c.dictSort) " +
			"from Dormitorymodel a,Dictionary c " +
			"where 1=1 and a.distributeNum>0 " +
			" and a.dormitory=c.id.dictValue and c.id.dictNo=7 order by c.dictSort ";
			list = classmodelDAO.find(hql);
			request.setAttribute("buildingList1", list);
			
		}
		
		hql="select distinct new Map(" +
		"c.id.dictValue as dictValue," +
		"c.dictCaption as dictCaption," +
		"c.dictParent as dictParent) " +
		"from Dormitorymodel a,TabSsManager b,Dictionary c " +
		"where a.curDormDept=b.tabSsDept.id and b.stuNo='"+xhorgh+"' " +
		" and a.direction=c.id.dictValue and c.id.dictNo=24 ";
		list = classmodelDAO.find(hql);
		request.setAttribute("directionList", list);
		
		// 证件类型 
		List idTypeList = getDiction("29");
		request.setAttribute("idTypeList", idTypeList);
		// 培养层次 
		List cultureModeList = getDiction("26");
		request.setAttribute("cultureModeList", cultureModeList);
		// 学生性质
		List studentCharList = getDiction("27");
		request.setAttribute("studentCharList", studentCharList);
		

	}
	
	public void initClassForm(HttpServletRequest request,String classId){

		String hql = "select distinct manager from Managermodel manager,Managermanagerrole managerrole ";	
		hql += " where manager.managerId=managerrole.id.managerId and manager.managerId not in "
				+ "(select school.id.managerId from Classmanager school,Classmodel classmodel  " +
				"where school.id.classId=classmodel.classId and classmodel.curYear='"+DateUtil.getNow("yyyy")+"') "
				+ "and managerrole.id.roleId='21'  and manager.schoolId='0001' and manager.available='1' ";
		
		List list = classmodelDAO.find(hql);	
		
		hql = "select distinct manager from Managermodel manager,Managermanagerrole managerrole ";
		hql += ",Classmanager classes where manager.managerId=classes.id.managerId "
				+ "and classes.id.managerId=managerrole.id.managerId and managerrole.id.roleId='21' "
				+ "and manager.schoolId='0001' "									
				+ "and classes.id.classId='" + classId + "' and manager.available='1' ";
		
		List listmanager = classmodelDAO.find(hql);	
		if (list.size() > 0) {
			if (listmanager.size() > 0) {
				list.addAll(listmanager);
			}
			request.setAttribute("assistantList", list);
		}else{
			request.setAttribute("assistantList", listmanager);
		}

		
		hql = "select distinct manager from Managermodel manager,Managermanagerrole managerrole ";		
		hql+="  where manager.managerId=managerrole.id.managerId and manager.managerId not in "
			+ "(select school.id.managerId from Classmanager school,Classmodel classmodel " +
			"where school.id.classId=classmodel.classId and classmodel.curYear='"+DateUtil.getNow("yyyy")+"') "
			+ "and managerrole.id.roleId='22' and manager.schoolId='0001' and manager.available='1'  ";
		
		list = classmodelDAO.find(hql);	
		
		hql = "select distinct manager from Managermodel manager,Managermanagerrole managerrole ";
		hql += ",Classmanager classes where manager.managerId=classes.id.managerId "
				+ "and classes.id.managerId=managerrole.id.managerId and managerrole.id.roleId='22' "
				+ "and manager.schoolId='0001' "									
				+ "and classes.id.classId='" + classId + "' and manager.available='1' ";
		
		listmanager = classmodelDAO.find(hql);	
		if (list.size() > 0) {
			if (listmanager.size() > 0) {
				list.addAll(listmanager);
			}
			request.setAttribute("tutorList", list);
		}else{
			request.setAttribute("tutorList", listmanager);
		}
		
		
		
	}
	
	public List getDiction(String dicId) {
		return studentmodelDAO.find("from Dictionary a where a.id.dictNo="
				+ dicId + " order by a.id.dictValue");
	}
	
	public boolean updateGzClass(){
		
		boolean flag=false;
		
		//男生
		String sqlstring="select s from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' order by s.totalScore ";
		
		List maleList=classmodelDAO.find(sqlstring);
		
        //女生文科
		sqlstring="select s from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and s.examType='1' order by s.totalScore ";
		
		List femaleWenList=classmodelDAO.find(sqlstring);
		
        //女生理科
        sqlstring="select s from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and s.examType!='1' order by s.totalScore ";
		
		List femaleLiList=classmodelDAO.find(sqlstring);
		
		//当年护理学院的班级
		sqlstring=" select c.classId from Classmodel c where c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' order by c.classNo ";
		List classList=classmodelDAO.find(sqlstring);
		
		if(classList!=null&&classList.size()>0){
			//先分男生
			int malecount1=0;
			int malecount2=0;
			if(maleList!=null&&maleList.size()>0){				
				if(maleList.size()<7){//男生数不超过6个，分在一个班
					malecount1=maleList.size();
					String classId=(String)classList.get(0);//取第一个班级
					for(int i=0;i<maleList.size();i++){
						GzStuTemp gzStuTemp=(GzStuTemp)maleList.get(i);
						gzStuTemp.setClassId(classId);
						studentmodelDAO.updateGzStuTemp(gzStuTemp);
					}
					
				}
				else{//男生数超过6个，均分在二个班
					if(classList.size()>1){
						String classId1=(String)classList.get(0);//取第一个班级
						String classId2=(String)classList.get(1);//取第二个班级
						int maleSCount=maleList.size();
						String[][] maleclassSet=new String[maleSCount][2];
						for(int i=0;i<maleclassSet.length;i++){//s型班级数组
							if(i%2==0){//从左到右
								maleclassSet[i][0]=classId1;
								maleclassSet[i][1]=classId2;
							}
							else{//从右到左
								maleclassSet[i][0]=classId2;
								maleclassSet[i][1]=classId1;
							}				
						}
						int stucount=0;
						for(int i=0;i<maleclassSet.length;i++){
							for(int j=0;j<2;j++){
								if(stucount<maleList.size()){
								    GzStuTemp gzStuTemp=(GzStuTemp)maleList.get(stucount);
								    gzStuTemp.setClassId(maleclassSet[i][j]);
								    studentmodelDAO.updateGzStuTemp(gzStuTemp);
								    stucount++;
								    if(maleclassSet[i][j].equals(classId1))
								    	malecount1++;
								    else if(maleclassSet[i][j].equals(classId2))
								    	malecount2++;
								}
								else{
									break;
								}
							}
							if(stucount>maleList.size()-1)
								break;
						}
						
//						int mid=maleList.size()/2;
//						for(int i=0;i<mid;i++){
//							GzStuTemp gzStuTemp=(GzStuTemp)maleList.get(i);
//							gzStuTemp.setClassId(classId1);
//							studentmodelDAO.updateGzStuTemp(gzStuTemp);
//						}
//						for(int i=mid;i<maleList.size();i++){
//							GzStuTemp gzStuTemp=(GzStuTemp)maleList.get(i);
//							gzStuTemp.setClassId(classId2);
//							studentmodelDAO.updateGzStuTemp(gzStuTemp);
//						}
//						malecount1=mid;
//						malecount2=maleList.size()-mid;
					}
					else{//只有一个班
						String classId=(String)classList.get(0);//取第一个班级
						for(int i=0;i<maleList.size();i++){
							GzStuTemp gzStuTemp=(GzStuTemp)maleList.get(i);
							gzStuTemp.setClassId(classId);
							studentmodelDAO.updateGzStuTemp(gzStuTemp);
						}
					}
				}
			}
			//再分女生
			//女生文科
			int wenNum=femaleWenList.size();
			if(femaleWenList.size()>0){
				int WenSCount=wenNum+(malecount1+malecount2);//s型循环次数
				String[][] wenclassSet=new String[WenSCount][classList.size()];
				for(int i=0;i<wenclassSet.length;i++){//s型班级数组
					if(i%2==0){//从左到右
						for(int j=0;j<classList.size();j++){
							wenclassSet[i][j]=(String)classList.get(j);
						}
					}
					else{//从右到左
						for(int j=0;j<classList.size();j++){
							wenclassSet[i][j]=(String)classList.get(classList.size()-(j+1));
						}
					}				
				}
				//填充学生
				int stucount=0;
				for(int i=0;i<wenclassSet.length;i++){
					for(int j=0;j<classList.size();j++){
						if(malecount1>0&&i<(malecount1-1)&&wenclassSet[i][j].equals(classList.get(0))){
							continue;
						}
						else if(malecount2>0&&i<(malecount2-1)&&wenclassSet[i][j].equals(classList.get(1))){
							continue;
						}
						else{
							if(stucount<femaleWenList.size()){
							    GzStuTemp gzStuTemp=(GzStuTemp)femaleWenList.get(stucount);
							    gzStuTemp.setClassId(wenclassSet[i][j]);
							    studentmodelDAO.updateGzStuTemp(gzStuTemp);
							    stucount++;
							}
							else{
								break;
							}
						}
					}
					if(stucount>femaleWenList.size()-1)
						break;
				}
			
			}
            //女生理科
			int liNum=femaleLiList.size();
			if(femaleLiList.size()>0){
				int LiSCount=liNum+malecount1+malecount2;//s型循环次数
				String[][] liclassSet=new String[LiSCount][classList.size()];
				for(int i=0;i<liclassSet.length;i++){//s型班级数组
					if(i%2==0){//从左到右
						for(int j=0;j<classList.size();j++){
							liclassSet[i][j]=(String)classList.get(j);
						}
					}
					else{//从右到左
						for(int j=0;j<classList.size();j++){
							liclassSet[i][j]=(String)classList.get(classList.size()-(j+1));
						}
					}				
				}
				//填充学生
				int stucount=0;
				for(int i=0;i<liclassSet.length;i++){
					for(int j=0;j<classList.size();j++){
						if(stucount<femaleLiList.size()){
						    GzStuTemp gzStuTemp=(GzStuTemp)femaleLiList.get(stucount);
						    gzStuTemp.setClassId(liclassSet[i][j]);
						    studentmodelDAO.updateGzStuTemp(gzStuTemp);
						    stucount++;
						}
						else{
							break;
						}
					}
					if(stucount>femaleLiList.size()-1)
						break;
				}
			
			}
			
		}
		flag=true;
		
		return flag;
	}
	
    public boolean updateGzClassAlert(String[] ids,String toclassId,String operator){
		
		boolean flag=false;
		
		for(int i=0;i<ids.length;i++){
			List stuList=classmodelDAO.find(" select s from GzStuTemp s where s.id='"+ids[i]+"'");
			if(stuList!=null&&stuList.size()>0){
				GzStuTemp gzStuTemp=(GzStuTemp)stuList.get(0);
				String oclassId=gzStuTemp.getClassId();
				gzStuTemp.setClassId(toclassId);
				studentmodelDAO.updateGzStuTemp(gzStuTemp);
				
				ClassAlertHis classAlertHis=new ClassAlertHis();
				classAlertHis.setStudentId(gzStuTemp.getEnterenceNo());
				classAlertHis.setClassIdO(oclassId);
				classAlertHis.setClassIdN(toclassId);
				classAlertHis.setOperatorId(operator);
				classAlertHis.setOperatorTime(DateUtil.getNow());
				studentmodelDAO.saveAlertHis(classAlertHis);
			}
		}
		flag=true;
		return flag;
    }
	
	public List find(String query){
		List result=null;
		try{
			result=classmodelDAO.find(query);
			//System.out.println("find ok");
		}catch(Exception e){
			e.printStackTrace();
			//System.out.println("find error");
		}
		//if(result==null)
			//System.out.println("findresult is null");
		return result;
	}
	
	public boolean updateDormitory(String[] temp, String[] untemp,String curDept)
	throws DormitoryHasStuException {
List list = studentmodelDAO.find("select a.dormId from Studentmodel a "
		+ "where a.yxClass.yxCollege.yxSchool.schoolId='0002' and a.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' and a.dormId<>'' and a.dormId is not null");
String dromStr = "";
for (int i = 0; i < list.size(); i++) {
	dromStr += list.get(i).toString() + ",";
}
String dormitoryId = "";
String classId = "";
List location_list = studentmodelDAO
		.find("from Dictionary a where a.id.dictNo= 20 ");
List dormitory_list = studentmodelDAO
		.find("from Dictionary a where a.id.dictNo= 21 ");

String dormstring="";
if (null != untemp) {
	for (int i = 0; i < untemp.length; i++) {
		if (i % 6 == 0) {
			// dormitoryId
			dormitoryId = untemp[i];
			if ("".equals(dormitoryId)) {
				i = i + 5;
				continue;
			}
			if (dromStr.indexOf(dormitoryId) != -1) {
				// 宿舍有学生
//				Dormitorymodel dormm = dormitorymodelDAO
//						.get(dormitoryId);
//
//				if (!"".equals(dormm.getLocation())) {// 校区
//					String location = "";
//					String Cap = "";
//					for (int k = 0; k < location_list.size(); k++) {
//						Dictionary dictionary = (Dictionary) location_list
//								.get(k);
//						location = dictionary.getId().getDictValue();
//						if (location.equals(dormm.getLocation())) {
//							Cap = dictionary.getDictCaption();
//							break;
//						}
//					}
//					dormm.setLocation(Cap);
//
//				}
//
//				if (!"".equals(dormm.getDormitory())) {// 楼号
//					String dormitory = "";
//					String Cap = "";
//					for (int k = 0; k < dormitory_list.size(); k++) {
//						Dictionary dictionary = (Dictionary) dormitory_list
//								.get(k);
//						dormitory = dictionary.getId().getDictValue();
//						if (dormitory.equals(dormm.getDormitory())) {
//							Cap = dictionary.getDictCaption();
//							break;
//						}
//					}
//					dormm.setDormitory(Cap);
//				}
				throw new DormitoryHasStuException("");
			}
//			Dormitorymodel dormitorymodel = dormitorymodelDAO
//					.get(dormitoryId);
//			dormitorymodel.setClassId(null);
//			dormitorymodelDAO.update(dormitorymodel);
			
			
			List dormList=studentmodelDAO.find(" select a from Dormitorymodel a where a.dormitoryId='"+untemp[i]+"' ");
			if(dormList!=null&&dormList.size()>0){
				Dormitorymodel dormitorymodel=(Dormitorymodel)dormList.get(0);
				int unbindNum=(Integer.valueOf(untemp[i+4])).intValue();
				dormitorymodel.setEmptyNum(unbindNum);
				dormitorymodelDAO.update(dormitorymodel);
			}//更新部分绑定的宿舍
			
			dormstring=dormstring+untemp[i]+",";
		}
	}

}
List dorms = dormitorymodelDAO.find("select a from Dormitorymodel a where a.emptyNum>0 and a.curDormDept='"+curDept+"'");

if(dormstring.length()>0){
	if(dorms!=null&&dorms.size()>0){
	    for(int i=0;i<dorms.size();i++){
	    	Dormitorymodel dormitorymodel=(Dormitorymodel)dorms.get(i);
	    	if(dormstring.indexOf(dormitorymodel.getDormitoryId())==-1){
	    		dormitorymodel.setEmptyNum(0);	    		
	    		dormitorymodelDAO.update(dormitorymodel);
	    	}//更新已绑完的宿舍
	    }
	}
}
else{//宿舍被全部绑完了
	if(dorms!=null&&dorms.size()>0){
	    for(int i=0;i<dorms.size();i++){
	    	Dormitorymodel dormitorymodel=(Dormitorymodel)dorms.get(i);	    	
	    	dormitorymodel.setEmptyNum(0);
	    	dormitorymodelDAO.update(dormitorymodel);	    	
	    }
	}
}
	
String classdormstring="";
if (null != temp) {
	for (int i = 0; i < temp.length; i++) {
		if (i % 6 == 0) {
			// dormitoryId
			dormitoryId = temp[i];
			if ("".equals(dormitoryId)) {
				i = i + 5;
				continue;
			}
			
			classId = temp[i+5];
			
			List classdormList=dormitorymodelDAO.find(" select a from ClassDorm a where a.dormId='"+temp[i]+"' and a.classId='"+temp[i+5]+"' ");
			if(classdormList!=null&&classdormList.size()>0){
				ClassDorm classDorm=(ClassDorm)classdormList.get(0);				
				int bindNum=(Integer.valueOf(temp[i+4])).intValue();
				classDorm.setDistributeNum(new Integer(bindNum));
				classmodelDAO.updateClassDorm(classDorm);
								
				
			}
			else{
				ClassDorm classDorm=new ClassDorm();
				classDorm.setClassId(temp[i+5]);
				classDorm.setDormId(temp[i]);
				classDorm.setDistributeNum(Integer.valueOf(temp[i+4]));
				classDorm.setCurYear(DateUtil.getNow("yyyy"));
				classmodelDAO.saveClassDorm(classDorm);//添加该classdorm
			}
			classdormstring=classdormstring+temp[i]+temp[i+5]+",";
		}

	}
}

List classdorms = dormitorymodelDAO.find("select a from ClassDorm a,Dormitorymodel b where a.dormId=b.dormitoryId and b.curDormDept='"+curDept+"'");

if(classdormstring.length()>0){	
	if(classdorms!=null&&classdorms.size()>0){
	    for(int i=0;i<classdorms.size();i++){
	    	ClassDorm classDorm=(ClassDorm)classdorms.get(i);	    	
	    	if(classdormstring.indexOf(classDorm.getDormId()+classDorm.getClassId())==-1){	    		
	    		classmodelDAO.deleteClassDorm(classDorm);
	    	}//取消绑定
	    }
	}
}
else{//全部取消绑定
	if(classdorms!=null&&classdorms.size()>0){
	    for(int i=0;i<classdorms.size();i++){
	    	ClassDorm classDorm=(ClassDorm)classdorms.get(i);	    	
	    	classmodelDAO.deleteClassDorm(classDorm);	    	
	    }
	}
}
return true;

}
			
	public boolean updateMenuTime(MenuTime menuTime){
		classmodelDAO.updateMenuTime(menuTime);
		return true;
	}
	
	public Integer getClassDistributionResult() {
		Integer stuCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(a.id) from GzStuTemp a where a.enrollYear='"+DateUtil.getNow("yyyy")+"' and a.classId is not null and a.classId!=''");
		if (list.size() > 0) {
			stuCount = (Integer) list.get(0);
		}
		return stuCount;

	}

	public void deleteClassDistribution() {
		List list = studentmodelDAO.find(" select a from GzStuTemp a where a.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		for (int i = 0; i < list.size(); i++) {
			GzStuTemp gzStuTemp = (GzStuTemp) list.get(i);			
			gzStuTemp.setClassId(null);
			gzStuTemp.setStudentNo(null);
			studentmodelDAO.updateGzStuTemp(gzStuTemp);
		}
		
	}
	
	public Integer getDormDistributionResult() {
		Integer stuCount = new Integer("0");
		List list = studentmodelDAO
				.find("select count(a.id) from Studentmodel a where a.yxClass.yxCollege.yxSchool.schoolId='0002' and a.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' and a.dormId is not null and a.dormId!=''");
		if (list.size() > 0) {
			stuCount = (Integer) list.get(0);
		}
		return stuCount;

	}

	public void deleteDormDistribution() {
		List list = studentmodelDAO.find(" select a from Studentmodel a where a.yxClass.yxCollege.yxSchool.schoolId='0002' and a.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' ");
		for (int i = 0; i < list.size(); i++) {
			Studentmodel studentmodel = (Studentmodel) list.get(i);			
			studentmodel.setDormId(null);
			studentmodelDAO.update(studentmodel);
		}
		
	}
	
	public List getGzClassList(String schoolId) {
		return classmodelDAO.find("select new map (b.classId as classId,"
				+ " b.classNo as classNo,b.className as className) " + " from Classmodel b "
				+ " where  b.curYear='" + DateUtil.getNow("yyyy")
				+ "' and b.yxCollege.yxSchool.schoolId='" + schoolId + "' "
				+ " order by b.classNo ");
	}
	
	
	public StudentListColumns getUserSessionColumns(String accountId,String pageId){
			Class[]  parameterTypes  =  new  Class[1];//这里你要调用的方法只有一个参数  		 
			parameterTypes[0]  =  String.class;//这个参数的类型是String[]  
			
			List list = classmodelDAO.find("from NHeaderSessionModel n where n.id.accountId='"+accountId+"' and n.id.pageId='"+pageId+"' and n.showStatus='0'");
			StudentListColumns studentlc = new StudentListColumns("1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1");
			Field[] fields = studentlc.getClass().getDeclaredFields();
			for(int i=0; i<list.size();i++){
				NHeaderSessionModel hs =(NHeaderSessionModel)list.get(i);
				String culumnId = hs.getId().getCulumnId().toString();
				for(int j=0;j<fields.length;j++){
					if(culumnId.equals(fields[j].getName())){
						StringBuffer setterMethodName = new StringBuffer();
						char firstChar = Character.toUpperCase(culumnId.charAt(0));
						setterMethodName.append("set").append(firstChar)
								.append(culumnId.substring(1));
						try {
						Method m = studentlc.getClass().getMethod(setterMethodName.toString(),
								parameterTypes);	
						String[] arg = {"0"};
						m.invoke(studentlc,arg);
						} catch (IllegalArgumentException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (IllegalAccessException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (InvocationTargetException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}				
			}
			
			return studentlc;
	}
	public StudentfdyListColmns getUserSessionfdyColumns(String accountId,String pageId){
		Class[]  parameterTypes  =  new  Class[1];//这里你要调用的方法只有一个参数  		 
		parameterTypes[0]  =  String.class;//这个参数的类型是String[]  
		
		List list = classmodelDAO.find("from NHeaderSessionModel n where n.id.accountId='"+accountId+"' and n.id.pageId='"+pageId+"' and n.showStatus='0'");
		StudentfdyListColmns studentlc = new StudentfdyListColmns("1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1");
		Field[] fields = studentlc.getClass().getDeclaredFields();
		for(int i=0; i<list.size();i++){
			NHeaderSessionModel hs =(NHeaderSessionModel)list.get(i);
			String culumnId = hs.getId().getCulumnId().toString();
			for(int j=0;j<fields.length;j++){
				if(culumnId.equals(fields[j].getName())){
					StringBuffer setterMethodName = new StringBuffer();
					char firstChar = Character.toUpperCase(culumnId.charAt(0));
					setterMethodName.append("set").append(firstChar)
							.append(culumnId.substring(1));
					try {
					Method m = studentlc.getClass().getMethod(setterMethodName.toString(),
							parameterTypes);	
					String[] arg = {"0"};
					m.invoke(studentlc,arg);
					} catch (IllegalArgumentException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IllegalAccessException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (InvocationTargetException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}				
		}
		
		return studentlc;
}
	public SdListhlxy getUserSessionhlxyColumns(String accountId,String pageId){
		Class[]  parameterTypes  =  new  Class[1];//这里你要调用的方法只有一个参数  		 
		parameterTypes[0]  =  String.class;//这个参数的类型是String[]  
		
		List list = classmodelDAO.find("from NHeaderSessionModel n where n.id.accountId='"+accountId+"' and n.id.pageId='"+pageId+"' and n.showStatus='0'");
		SdListhlxy studentlc = new SdListhlxy("1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1");
		Field[] fields = studentlc.getClass().getDeclaredFields();
		for(int i=0; i<list.size();i++){
			NHeaderSessionModel hs =(NHeaderSessionModel)list.get(i);
			String culumnId = hs.getId().getCulumnId().toString();
			for(int j=0;j<fields.length;j++){
				if(culumnId.equals(fields[j].getName())){
					StringBuffer setterMethodName = new StringBuffer();
					char firstChar = Character.toUpperCase(culumnId.charAt(0));
					setterMethodName.append("set").append(firstChar)
							.append(culumnId.substring(1));
					try {
					Method m = studentlc.getClass().getMethod(setterMethodName.toString(),
							parameterTypes);	
					String[] arg = {"0"};
					m.invoke(studentlc,arg);
					} catch (IllegalArgumentException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IllegalAccessException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (InvocationTargetException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}				
		}
		
		return studentlc;
}
	public SdfdyListhlxy getUserSessionfdyhlxyColumns(String accountId,String pageId){
		Class[]  parameterTypes  =  new  Class[1];//这里你要调用的方法只有一个参数  		 
		parameterTypes[0]  =  String.class;//这个参数的类型是String[]  
		
		List list = classmodelDAO.find("from NHeaderSessionModel n where n.id.accountId='"+accountId+"' and n.id.pageId='"+pageId+"' and n.showStatus='0'");
		SdfdyListhlxy studentlc = new SdfdyListhlxy("1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1");
		Field[] fields = studentlc.getClass().getDeclaredFields();
		for(int i=0; i<list.size();i++){
			NHeaderSessionModel hs =(NHeaderSessionModel)list.get(i);
			String culumnId = hs.getId().getCulumnId().toString();
			for(int j=0;j<fields.length;j++){
				if(culumnId.equals(fields[j].getName())){
					StringBuffer setterMethodName = new StringBuffer();
					char firstChar = Character.toUpperCase(culumnId.charAt(0));
					setterMethodName.append("set").append(firstChar)
							.append(culumnId.substring(1));
					try {
					Method m = studentlc.getClass().getMethod(setterMethodName.toString(),
							parameterTypes);	
					String[] arg = {"0"};
					m.invoke(studentlc,arg);
					} catch (IllegalArgumentException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IllegalAccessException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (InvocationTargetException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}				
		}
		
		return studentlc;
}
	public List getNTableHeadList(String accountId,String pageId,String flag){
		List list = null;
		List headlist=null;
		List sessionlist=null;
		 headlist = classmodelDAO.find("from NTableHeadModel n where n.id.pageId='"+pageId+"' order by n.sort");
		 sessionlist = classmodelDAO.find("from NHeaderSessionModel ns where ns.id.pageId='"+pageId+"' and ns.id.accountId='"+accountId+"'");
		 if(sessionlist.size()==0){
			if("0".equals(flag)){
				list = sessionlist;
			}
			else{
				list = headlist;
			}
			
		}else{
			if("0".equals(flag)){
				for(int j=0;j<sessionlist.size();j++){
					NHeaderSessionModel hs = (NHeaderSessionModel)sessionlist.get(j);
					if("1".equals(hs.getShowStatus())){
						for(int i=0;i<headlist.size();i++){
							NTableHeadModel ntablehead = (NTableHeadModel)headlist.get(i);
							if(ntablehead.getId().getColumnId().equals(hs.getId().getCulumnId())){
								headlist.remove(i);
								break;
							}
						}
					}
				}			
								
			}else{
				for(int j=0;j<sessionlist.size();j++){
					NHeaderSessionModel hs = (NHeaderSessionModel)sessionlist.get(j);
					if("0".equals(hs.getShowStatus())){
						for(int i=0;i<headlist.size();i++){
							NTableHeadModel ntablehead = (NTableHeadModel)headlist.get(i);
							if(ntablehead.getId().getColumnId().equals(hs.getId().getCulumnId())){
								headlist.remove(i);
								break;
							}
						}
					}
				}
			}
			list = headlist;
		}
		
		return list;
	}
	
	
	public void saveUserSessionColumns(String accountId,String pageId,String tableheadleft,String tableheadright){
		List sessionlist=null;
		 sessionlist = classmodelDAO.find("from NHeaderSessionModel ns where ns.id.pageId='"+pageId+"' and ns.id.accountId='"+accountId+"'");
		int aa=sessionlist.size();
		 if(aa>0){
			for(int j=0;j<sessionlist.size();j++){
				NHeaderSessionModel hs = (NHeaderSessionModel)sessionlist.get(j);
				if(tableheadleft.indexOf(hs.getId().getCulumnId())!=-1){
					hs.setShowStatus("0");
				}else{
					hs.setShowStatus("1");
				}
				classmodelDAO.updateUserSession(hs);
				
			}
		}else{
			String tableheadleftArr[]= tableheadleft.split(",");
			if(tableheadleftArr!=null){
			for(int i=0;i<tableheadleftArr.length;i++){
				if(!"".equals(tableheadleftArr[i])){
					NHeaderSessionModel hs = new NHeaderSessionModel();
					NHeaderSessionModelId key = new NHeaderSessionModelId();
					key.setAccountId(accountId);
					key.setPageId(pageId);
					key.setCulumnId(tableheadleftArr[i]);
					hs.setId(key);
					hs.setShowStatus("0");
					classmodelDAO.saveUserSession(hs);
				}
			}
			
			}
			
			String tableheadrightArr[]= tableheadright.split(",");
			if(tableheadrightArr!=null){
			for(int i=0;i<tableheadrightArr.length;i++){
				if(!"".equals(tableheadrightArr[i])){
					NHeaderSessionModel hs = new NHeaderSessionModel();
					NHeaderSessionModelId key = new NHeaderSessionModelId();
					key.setAccountId(accountId);
					key.setPageId(pageId);
					key.setCulumnId(tableheadrightArr[i]);
					hs.setId(key);
					hs.setShowStatus("1");
					classmodelDAO.saveUserSession(hs);
				}
			}
			
			}
		}
	}
	
	
}



