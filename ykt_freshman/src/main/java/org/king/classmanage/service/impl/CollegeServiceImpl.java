/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeServiceImpl.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-25     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service.impl;

import java.util.List;

import org.king.classmanage.dao.CollegemodelDAO;
import org.king.classmanage.dao.ManagermodelDAO;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.CollegemanagerId;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.service.CollegeService;
import org.king.framework.service.impl.BaseService;
import org.springframework.orm.ObjectRetrievalFailureException;

public class CollegeServiceImpl extends BaseService implements CollegeService {

	CollegemodelDAO collegemodelDAO;

	ManagermodelDAO managermodelDAO;

	/**
	 * @param collegemodelDAO
	 *            The collegemodelDAO to set.
	 */
	public void setCollegemodelDAO(CollegemodelDAO collegemodelDAO) {
		this.collegemodelDAO = collegemodelDAO;
	}

	/**
	 * @param managermodelDAO
	 *            The managermodelDAO to set.
	 */
	public void setManagermodelDAO(ManagermodelDAO managermodelDAO) {
		this.managermodelDAO = managermodelDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.CollegeService#saveCollege(org.king.classmanage.domain.Collegemodel)
	 */
	public void saveCollege(Collegemodel collegemodel) {
		collegemodelDAO.save(collegemodel);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.CollegeService#saveCollegeAndLeader(org.king.classmanage.domain.Collegemodel,
	 *      java.lang.String, org.king.classmanage.domain.Collegemanager)
	 */
	public void saveCollegeAndLeader(Collegemodel collegemodel,
			String collegeleader, Collegemanager collegemanager) {
		collegemodelDAO.save(collegemodel);
		CollegemanagerId managerId = new CollegemanagerId();
		managerId.setCollegeId(collegemodel.getCollegeId());
		managerId.setManagerId(collegeleader);
		collegemanager.setId(managerId);
		managermodelDAO.saveCollegeManager(collegemanager);

	}

	public void updateCollegeAndLeader(Collegemodel collegemodel,
			String collegeleader, Collegemanager collegemanager) {
		collegemodelDAO.update(collegemodel);
		managermodelDAO.deleteCollegeManager(collegemodel.getCollegeId());
		if (null != collegemanager) {
			managermodelDAO.saveCollegeManager(collegemanager);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.CollegeService#getCollege(java.lang.String)
	 */
	public Collegemodel getCollege(String collegeId) {
		
		try {
			return collegemodelDAO.get(collegeId);
		} catch (ObjectRetrievalFailureException e) {
			return null;
		}
	}
	
	
	/* (non-Javadoc)
	 * @see org.king.classmanage.service.CollegeService#getCollegebyNo(java.lang.String)
	 */
	public List getCollegebyNo(String collegeNo){
		return collegemodelDAO.find("from Collegemodel a where a.collegeNo='"+collegeNo+"'");		
	}
	
	
	public List getCollegebyName(String collegeName){
		return collegemodelDAO.find("from Collegemodel a where a.collegeName='"+collegeName+"'");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.CollegeService#getAllCollege()
	 */
	public List getAllCollege() {

		return collegemodelDAO.getAll();
	}
/**
 * 得到复旦学院的所有书院
 * @return
 */	
	public List getAllCollegeByfdxy() {
		
		String hql=" from org.king.classmanage.domain.Collegemodel a where a.yxSchool.schoolId='0001'";

		return collegemodelDAO.find(hql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.CollegeService#deleteCollege(java.lang.String)
	 */
	public void deleteCollege(String collegeId) {

		collegemodelDAO.delete(getCollege(collegeId));
		managermodelDAO.deleteCollegeManager(collegeId);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.CollegeService#distributeClass(java.lang.String,
	 *      java.util.List)
	 */
	public void distributeClass(String collegeId, List classId) {
		// TODO Auto-generated method stub

	}

}
