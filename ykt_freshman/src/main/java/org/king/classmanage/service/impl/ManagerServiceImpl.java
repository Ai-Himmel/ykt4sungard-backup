/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagerServiceImpl.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-26     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service.impl;

import java.sql.Types;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.king.classmanage.dao.ManagermodelDAO;
import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Managermanagerrole;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmanager;
import org.king.classmanage.exception.ManagerInClassException;
import org.king.classmanage.exception.ManagerInCollegeException;
import org.king.classmanage.exception.ManagerInSchoolException;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.web.help.ManagerWithType;
import org.king.framework.dao.MyQuery;
import org.king.framework.service.impl.BaseService;
import org.king.security.dao.AccountDAO;
import org.king.utils.DateUtil;

public class ManagerServiceImpl extends BaseService implements ManagerService {

	private ManagermodelDAO managermodelDAO;

	private AccountDAO accountDAO;

	public static SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy");
	/**
	 * @param accountDAO
	 *            The accountDAO to set.
	 */
	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}

	/**
	 * @param managermodelDAO
	 *            The managermodelDAO to set.
	 */
	public void setManagermodelDAO(ManagermodelDAO managermodelDAO) {
		this.managermodelDAO = managermodelDAO;
	}

	public List findManagerInfo(String managerNo) {
		return managermodelDAO.find("from Person a where a.personCode='"
				+ managerNo + "'");

	}
	
	public void initForm(HttpServletRequest request) {
		
		List list = managermodelDAO.find("from org.king.classmanage.domain.Schoolmodel a where 1=1");
		request.setAttribute("schoolList", list);

	}	

	public List findManager(String[] args,String schoolId) {
		String managerNo = args[0];
		String managerName = args[1];
		String gender = args[2];
		String leader = args[3];
		String assistant = args[4];
		String tutor = args[5];
		String teacher = args[6];
		String page = args[7];
//		String school = args[8];
		String available = args[9];		
		List entitys = null;

		String hqlStr = "select new org.king.classmanage.web.help.ManagerWithType"
				+ "(a.managerId,a.managerNo,a.managerName,a.gender,a.managerOrg,a.managerType,a.available,a.contact,"
				+ "a.introduction,d.schoolName,b.id.roleId,c.roleName) "
				+ "from Managermodel a,Managermanagerrole b,Managerrole c,Schoolmodel d "
				+ "where a.managerId=b.id.managerId "
				+ "and b.id.roleId=c.roleId " +
						" and a.schoolId=d.schoolId and a.schoolId='"+schoolId+"' ";
		hqlStr += (StringUtils.isNotEmpty(managerNo) ? " and a.managerNo like ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(managerName) ? " and a.managerName like ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		
//		hqlStr += (StringUtils.isNotEmpty(school) ? " and a.schoolId = ?" : "");
		
		if (StringUtils.isNotEmpty(leader)) {
			hqlStr += (StringUtils.isNotEmpty(leader) ? " and (b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " or b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(tutor) ? " or b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
					: "");
			hqlStr += " )";
		} else {
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and (b.id.roleId = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(tutor) ? " or b.id.roleId = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
						: "");
				hqlStr += " )";
			} else {
				if (StringUtils.isNotEmpty(tutor)) {
					hqlStr += (StringUtils.isNotEmpty(tutor) ? " and (b.id.roleId = ?"
							: "");
					hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
							: "");
					hqlStr += " )";
				} else {
					hqlStr += (StringUtils.isNotEmpty(teacher) ? " and b.id.roleId = ?"
							: "");
				}
			}
		}
//					hqlStr +=" and a.available='1' ";
		
		hqlStr += (StringUtils.isNotEmpty(available) ? " and a.available = ?"
				: "");		
					
					
		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(managerNo)) {
			myQuery.addPara("%" + managerNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(managerName)) {
			myQuery.addPara("%" + managerName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}
		
//		if (StringUtils.isNotEmpty(school)) {
//			myQuery.addPara(school, Types.VARCHAR);
//		}

		if (StringUtils.isNotEmpty(leader)) {
			myQuery.addPara(leader, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor)) {
			myQuery.addPara(tutor, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(teacher)) {
			myQuery.addPara(teacher, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(available)) {
			myQuery.addPara(available, Types.VARCHAR);
		}

		if (StringUtils.isNumeric(page)) {
			myQuery.setPageStartNo(Integer.parseInt(page));
		} else {
			myQuery.setPageStartNo(0);
		}
		myQuery.setOrderby(" order by a.managerNo");
		myQuery.setQueryString(hqlStr);
		myQuery.setPageSize(100);
		myQuery.setOffset(true);
		entitys = managermodelDAO.find(myQuery);

		for (int i = 0; i < entitys.size(); i++) {

			ManagerWithType managerwithtype = (ManagerWithType) entitys.get(i);
			String genderCode = "";
			String genderStr = "";
			if (!"".equals(managerwithtype.getGender())) {// 性别
				if (genderCode.equals(managerwithtype.getGender())) {
					managerwithtype.setGender(genderStr);
				} else {
					genderCode = managerwithtype.getGender();
					List cap_list = managermodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ managerwithtype.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						managerwithtype.setGender(genderStr);
					}
				}
			}

			String orgCode = "";
			String orgStr = "";
			if (!"".equals(managerwithtype.getManagerOrg())) {// 单位
				if (orgCode.equals(managerwithtype.getManagerOrg())) {
					managerwithtype.setManagerOrg(orgStr);
				} else {
					orgCode = managerwithtype.getManagerOrg();
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managerwithtype.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						orgStr = Cap;
						managerwithtype.setManagerOrg(orgStr);
					}
				}

			}
		}
		return entitys;
	}

	public List findManagerExport(String[] args,String schoolId) {
		String managerNo = args[0];
		String managerName = args[1];
		String gender = args[2];
		String leader = args[3];
		String assistant = args[4];
		String tutor = args[5];
		String teacher = args[6];

//		String school = args[8];
		String available = args[9];	
		
		List entitys = null;

		String hqlStr = "select new org.king.classmanage.web.help.ManagerWithType"
				+ "(a.managerId,a.managerNo,a.managerName,a.gender,a.managerOrg,a.managerType,a.available,a.contact,"
				+ "a.introduction,d.schoolName,b.id.roleId,c.roleName) "
				+ "from Managermodel a,Managermanagerrole b,Managerrole c,Schoolmodel d "
				+ "where a.managerId=b.id.managerId "
				+ "and b.id.roleId=c.roleId " +
						"and d.schoolId=a.schoolId";
		
		hqlStr += " and a.schoolId='"+schoolId+"' ";
		
		hqlStr += (StringUtils.isNotEmpty(managerNo) ? " and a.managerNo like ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(managerName) ? " and a.managerName like ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		
//		hqlStr += (StringUtils.isNotEmpty(school) ? " and a.schoolId = ?" : "");
		
		if (StringUtils.isNotEmpty(leader)) {
			hqlStr += (StringUtils.isNotEmpty(leader) ? " and (b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " or b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(tutor) ? " or b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
					: "");
			hqlStr += " )";
		} else {
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and (b.id.roleId = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(tutor) ? " or b.id.roleId = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
						: "");
				hqlStr += " )";
			} else {
				if (StringUtils.isNotEmpty(tutor)) {
					hqlStr += (StringUtils.isNotEmpty(tutor) ? " and (b.id.roleId = ?"
							: "");
					hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
							: "");
					hqlStr += " )";
				} else {
					hqlStr += (StringUtils.isNotEmpty(teacher) ? " and b.id.roleId = ?"
							: "");
				}
			}
		}
		hqlStr += (StringUtils.isNotEmpty(available) ? " and a.available = ?"
				: "");	

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(managerNo)) {
			myQuery.addPara("%" + managerNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(managerName)) {
			myQuery.addPara("%" + managerName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}
		
//		if (StringUtils.isNotEmpty(school)) {
//			myQuery.addPara(school, Types.VARCHAR);
//		}

		if (StringUtils.isNotEmpty(leader)) {
			myQuery.addPara(leader, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor)) {
			myQuery.addPara(tutor, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(teacher)) {
			myQuery.addPara(teacher, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(available)) {
			myQuery.addPara(available, Types.VARCHAR);
		}

		myQuery.setPageStartNo(0);

		myQuery.setOrderby(" order by a.managerNo");
		myQuery.setQueryString(hqlStr);

		entitys = managermodelDAO.find(myQuery);
		for (int i = 0; i < entitys.size(); i++) {
			ManagerWithType managerwithtype = (ManagerWithType) entitys.get(i);
			String genderCode = "";
			String genderStr = "";
			if (!"".equals(managerwithtype.getGender())) {// 性别
				if (genderCode.equals(managerwithtype.getGender())) {
					managerwithtype.setGender(genderStr);
				} else {
					genderCode = managerwithtype.getGender();
					List cap_list = managermodelDAO
							.find("select a.dictCaption from Dictionary a where a.id.dictNo= 1 "
									+ "and a.id.dictValue='"
									+ managerwithtype.getGender() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						genderStr = Cap;
						managerwithtype.setGender(genderStr);
					}
				}
			}
			String orgCode = "";
			String orgStr = "";
			if (!"".equals(managerwithtype.getManagerOrg())) {// 单位
				if (orgCode.equals(managerwithtype.getManagerOrg())) {
					managerwithtype.setManagerOrg(orgStr);
				} else {
					orgCode = managerwithtype.getManagerOrg();
					List cap_list = managermodelDAO
							.find("select a.deptName from Department a "
									+ "where a.deptCode='"
									+ managerwithtype.getManagerOrg() + "'");

					if (cap_list.size() > 0) {
						String Cap = cap_list.get(0).toString();
						orgStr = Cap;
						managerwithtype.setManagerOrg(orgStr);
					}
				}

			}
		}
		return entitys;
	}

	public boolean inRole(String managerId, String role) {
		String hqlStr = "select count(a.managerId) "
				+ "from Managermodel a,Managermanagerrole b,Managerrole c "
				+ "where a.managerId=b.id.managerId "
				+ "and b.id.roleId=c.roleId and a.managerId = '" + managerId
				+ "' and c.roleId = '" + role + "'";
		List list = managermodelDAO.find(hqlStr);
		if (((Integer) list.get(0)).intValue() != 0)
			return true;

		return false;
	}

	public Integer findManagerCount(String[] args,String schoolId) {
		String managerNo = args[0];
		String managerName = args[1];
		String gender = args[2];
		String leader = args[3];
		String assistant = args[4];
		String tutor = args[5];
		String teacher = args[6];
		
//		String school = args[8];	
		String available = args[9];	
		
		Integer managerCount = new Integer("0");
		List entitys = null;

		String hqlStr = "select count(a.managerId) "
				+ "from Managermodel a,Managermanagerrole b,Managerrole c "
				+ "where a.managerId=b.id.managerId "
				+ "and b.id.roleId=c.roleId and a.schoolId='"+schoolId+"' ";
		hqlStr += (StringUtils.isNotEmpty(managerNo) ? " and a.managerNo like ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(managerName) ? " and a.managerName like ?"
				: "");

		hqlStr += (StringUtils.isNotEmpty(gender) ? " and a.gender = ?" : "");
		
//		hqlStr += (StringUtils.isNotEmpty(school) ? " and a.schoolId = ?" : "");		
		
		if (StringUtils.isNotEmpty(leader)) {
			hqlStr += (StringUtils.isNotEmpty(leader) ? " and (b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(assistant) ? " or b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(tutor) ? " or b.id.roleId = ?"
					: "");
			hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
					: "");
			hqlStr += " )";
		} else {
			if (StringUtils.isNotEmpty(assistant)) {
				hqlStr += (StringUtils.isNotEmpty(assistant) ? " and (b.id.roleId = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(tutor) ? " or b.id.roleId = ?"
						: "");
				hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
						: "");
				hqlStr += " )";
			} else {
				if (StringUtils.isNotEmpty(tutor)) {
					hqlStr += (StringUtils.isNotEmpty(tutor) ? " and (b.id.roleId = ?"
							: "");
					hqlStr += (StringUtils.isNotEmpty(teacher) ? " or b.id.roleId = ?"
							: "");
					hqlStr += " )";
				} else {
					hqlStr += (StringUtils.isNotEmpty(teacher) ? " and b.id.roleId = ?"
							: "");
				}
			}
		}
		hqlStr += (StringUtils.isNotEmpty(available) ? " and a.available = ?"
				: "");	

		MyQuery myQuery = new MyQuery();

		if (StringUtils.isNotEmpty(managerNo)) {
			myQuery.addPara("%" + managerNo + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(managerName)) {
			myQuery.addPara("%" + managerName + "%", Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(gender)) {
			myQuery.addPara(gender, Types.VARCHAR);
		}
		
//		if (StringUtils.isNotEmpty(school)) {
//			myQuery.addPara(school, Types.VARCHAR);
//		}		

		if (StringUtils.isNotEmpty(leader)) {
			myQuery.addPara(leader, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(assistant)) {
			myQuery.addPara(assistant, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(tutor)) {
			myQuery.addPara(tutor, Types.VARCHAR);
		}

		if (StringUtils.isNotEmpty(teacher)) {
			myQuery.addPara(teacher, Types.VARCHAR);
		}
		if (StringUtils.isNotEmpty(available)) {
			myQuery.addPara(available, Types.VARCHAR);
		}
		
		myQuery.setQueryString(hqlStr);

		entitys = managermodelDAO.find(myQuery);
		if (entitys != null) {
			managerCount = (Integer) entitys.get(0);
		}
		return managerCount;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#findManagerRole(java.lang.String)
	 */
	public List findManagerRole(String managerId) {
		return managermodelDAO
				.find("from Managermanagerrole a where a.id.managerId='"
						+ managerId + "'");

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#saveManager(org.king.classmanage.domain.Managermodel)
	 */
	public void saveManager(Managermodel managermodel) {
		managermodelDAO.save(managermodel);

	}
	public void updateManager(Managermodel managermodel) {
		managermodelDAO.update(managermodel);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#saveManagerandRole(org.king.classmanage.domain.Managermodel,
	 *      java.util.List)
	 */
	public void saveManagerandRole(Managermodel managermodel, List list) {
		
//		managermodel.setAvailable("1");//表示该管理人员在任
		managermodel.setSchoolId("0001");//表示该管理人员是复旦学院(id=0001)的管理人员
		managermodelDAO.save(managermodel);

		for (int i = 0; i < list.size(); i++) {
			Managermanagerrole managermanagerrole = (Managermanagerrole) list
					.get(i);
			managermanagerrole.getId()
					.setManagerId(managermodel.getManagerId());
			managermodelDAO.saveDuties(managermanagerrole);
		}
	}
/**
 * 护理学院添加管理员
 * @param managermodel
 * @param list
 */	
	public void saveManagerandRole_hlxy(Managermodel managermodel, List list) {
		
//		managermodel.setAvailable("1");//表示该管理人员在任
		managermodel.setSchoolId("0002");//表示该管理人员是复旦学院(id=0001)的管理人员
		managermodelDAO.save(managermodel);

		for (int i = 0; i < list.size(); i++) {
			Managermanagerrole managermanagerrole = (Managermanagerrole) list
					.get(i);
			managermanagerrole.getId()
					.setManagerId(managermodel.getManagerId());
			managermodelDAO.saveDuties(managermanagerrole);
		}
	}	
	/**
	 * 修改管理员在任情况
	 * @param deleteX
	 */
	public void modifyManager_Available(String[] deleteX) {
		
		if(deleteX.length>0){
			for(int i=0;i<deleteX.length;i++){
				Managermodel managermodel = findManager(deleteX[i]);
				if(managermodel!=null){
					managermodel.setAvailable("0");//修改为不在任
					managermodelDAO.update(managermodel);
				}
				
			}
			
		}
	}
	
	public Managermodel findManager(String manageId) {

		String hql="from org.king.classmanage.domain.Managermodel a where a.managerId='"+manageId+"'";
		List list =managermodelDAO.find(hql);
		if(list.size()>0){
			Managermodel managermodel =(Managermodel)list.get(0);
			return managermodel;
		}else{
			return null;
		}
	}
	
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#updateManagerandRole(org.king.classmanage.domain.Managermodel,
	 *      java.util.List)
	 */
	public void updateManagerandRole(Managermodel managermodel, List list,
			String roleStr) throws ManagerInClassException,
			ManagerInCollegeException, ManagerInSchoolException {
		List temp = managermodelDAO
				.find("select a.id.roleId from Managermanagerrole a where a.id.managerId='"
						+ managermodel.getManagerId() + "'");
		for (int i = 0; i < temp.size(); i++) {
			String temprole = temp.get(i).toString();
			if (roleStr.indexOf(temprole) == -1) {
				if ("01".equals(temprole)) {
					List checkCanDel = managermodelDAO
							.find("select distinct b.managerId from "
									+ "Managermodel b,Schoolmanager e "
									+ "where b.managerId=e.id.managerId "
									+ "and b.managerId='"
									+ managermodel.getManagerId() + "'");
					if (checkCanDel.size() > 0) {
						throw new ManagerInSchoolException(
								"Manager has in school");
					}
				} else if ("11".equals(temprole)) {
					List checkCanDel = managermodelDAO
							.find("select distinct b.managerId from "
									+ "Managermodel b,Collegemanager d "
									+ "where b.managerId=d.id.managerId "
									+ "and b.managerId='"
									+ managermodel.getManagerId() + "'");
					if (checkCanDel.size() > 0) {
						throw new ManagerInCollegeException(
								"Manager has in college");
					}
				} else if ("21".equals(temprole) || "22".equals(temprole)) {
					List checkCanDel = managermodelDAO
							.find("select distinct b.managerId from "
									+ "Managermodel b,Classmanager c "
									+ "where b.managerId=c.id.managerId "
									+ "and b.managerId='"
									+ managermodel.getManagerId() + "'");
					if (checkCanDel.size() > 0) {
						throw new ManagerInClassException(
								"Manager has in class");
					}
				}

			}
		}
		
//		managermodel.setAvailable("1");//表示该管理人员在任
		
		managermodelDAO.update(managermodel);
		List roleList = managermodelDAO
				.find("from Managermanagerrole managerrole where managerrole.id.managerId='"
						+ managermodel.getManagerId() + "'");
		for (int i = 0; i < roleList.size(); i++) {
			Managermanagerrole managermanagerrole = (Managermanagerrole) roleList
					.get(i);
			managermodelDAO.deleteManagermanagerRole(managermanagerrole);
		}
		for (int i = 0; i < list.size(); i++) {
			Managermanagerrole managermanagerrole = (Managermanagerrole) list
					.get(i);
			managermodelDAO.saveDuties(managermanagerrole);
		}

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getManager()
	 */
	public List getManager() {
		return managermodelDAO.getAll();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getCollegeManager()
	 */
	public List getCollegeManager() {
		return getCollegeManager(false);
	}

	public List getCollegeManager(boolean bool) {
		if (bool) {
			return managermodelDAO.findSpecial("college", "GET_ALL", true,"0001");
		} else {
			return managermodelDAO.findSpecial("college", "GET_ALL","0001");
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getCollegeManager(java.lang.String)
	 */
	public List getCollegeManager(String collegeId) {
		return managermodelDAO.findSpecial("college", collegeId,"0001");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getSchoolManager()
	 */
	public List getSchoolManager() {

		return getSchoolManager(false);
	}

	public List getSchoolManager(boolean bool) {
		if (bool) {
			return managermodelDAO.findSpecial("school", "GET_ALL", true,"");
		} else {
			return managermodelDAO.findSpecial("school", "GET_ALL","");
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getSchoolManager(java.lang.String)
	 */
	public List getSchoolManager(String schoolId) {

		return managermodelDAO.findSpecial("school", schoolId,"");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getClassAssitant()
	 */
	public List getClassAssitant() {
		return getClassAssitant(false);
	}

	public List getClassAssitant(boolean bool) {
		if (bool) {
			return managermodelDAO.findSpecial("class_ass", "GET_ALL", true,"0001");
		} else {
			return managermodelDAO.findSpecial("class_ass", "GET_ALL","0001");
		}
	}
	
	public List getClassAssitant_hlxy() {
		return getClassAssitant_hlxy(false);
	}

	public List getClassAssitant_hlxy(boolean bool) {
		if (bool) {
			return managermodelDAO.findSpecial("class_ass", "GET_ALL", true,"0002");
		} else {
			return managermodelDAO.findSpecial("class_ass", "GET_ALL","0002");
		}
	}
	
	public List getClassTutor_hlxy() {
		return getClassTutor_hlxy(false);
	}

	public List getClassTutor_hlxy(boolean bool) {
		if (bool) {
			return managermodelDAO.findSpecial("class_tu", "GET_ALL", true,"0002");
		} else {
			return managermodelDAO.findSpecial("class_tu", "GET_ALL","0002");
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getClassAssitant(java.lang.String)
	 */
	public List getClassAssitant(String classId) {
		return managermodelDAO.findSpecial("class_ass", classId,"0001");
	}
	
	public List getClassAssitant_hlxy(String classId) {
		return managermodelDAO.findSpecial("class_ass", classId,"0002");
	}

	public List getClassAssistantByManagerId(String managerId) {
		return managermodelDAO.find("select a from Classmanager a,Classmodel b where " +
				"a.id.classId=b.classId and b.curYear='"+DateUtil.getNow("yyyy")+"'  and a.id.managerId='"
				+ managerId + "'");

	}

	public List getCollegeAssistantByManagerId(String managerId) {
		return managermodelDAO.find("from Collegemanager where id.managerId='"
				+ managerId + "'");

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getClassTutor()
	 */
	public List getClassTutor() {
		return getClassTutor(false);
	}

	public List getClassTutor(boolean bool) {
		if (bool) {
			return managermodelDAO.findSpecial("class_tu", "GET_ALL", true,"0001");
		} else {
			return managermodelDAO.findSpecial("class_tu", "GET_ALL","0001");
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getClassTutor(java.lang.String)
	 */
	public List getClassTutor(String classId) {
		return managermodelDAO.findSpecial("class_tu", classId,"0001");
	}
	
	public List getClassSpeTutor(String classId) {
		return managermodelDAO.findSpecial("class_spetu", classId,"0001");
	}
	
	public List getClassTutor_hlxy(String classId) {
		return managermodelDAO.findSpecial("class_tu", classId,"0002");
	}
	
	public List getClassSpeTutor_hlxy(String classId) {
		return managermodelDAO.findSpecial("class_spetu", classId,"0002");
	}
	

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#getManager(java.lang.String)
	 */
	public Managermodel getManager(String manageId) {

		return managermodelDAO.get(manageId);
	}

	public List getManagerByNo(String managerNo) {
		return managermodelDAO.find("from Managermodel a where a.managerNo='"
				+ managerNo + "'");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#deleteManager(java.lang.String)
	 */
	public void deleteManager(String managerId) {
		managermodelDAO.delete(getManager(managerId));
	}

	public boolean deleteManagerandRole(String managerId)
			throws ManagerInClassException, ManagerInCollegeException,
			ManagerInSchoolException {
		List list_cl = managermodelDAO
				.find("from Classmanager a where a.id.managerId='" + managerId
						+ "'");
		if (list_cl.size() > 0) {
			throw new ManagerInClassException("Manager has in Class");
		}
		List list_co = managermodelDAO
				.find("from Collegemanager a where a.id.managerId='"
						+ managerId + "'");
		if (list_co.size() > 0) {
			throw new ManagerInCollegeException("Manager has in Class");
		}
		List list_s = managermodelDAO
				.find("from Schoolmanager a where a.id.managerId='" + managerId
						+ "'");
		if (list_s.size() > 0) {
			throw new ManagerInSchoolException("Manager has in Class");
		}
		try {
			Managermodel managermodel = getManager(managerId);
			String accId = getAccountidByNo(managermodel.getManagerNo());
			managermodelDAO.delete(managermodel);
			if (!"".equals(accId)) {
				accountDAO.delete(accountDAO.get(accId));
			}
			List list = managermodelDAO
					.find("from Managermanagerrole role where role.id.managerId='"
							+ managerId + "'");
			for (int i = 0; i < list.size(); i++) {
				Managermanagerrole managermanagerrole = (Managermanagerrole) list
						.get(i);
				managermodelDAO.deleteManagermanagerRole(managermanagerrole);
			}
			return true;
		} catch (Exception e) {
			return false;
		}

		// for (int i = 0; i < list_cl.size(); i++) {
		// Classmanager classmanager = (Classmanager) list_cl.get(i);
		// managermodelDAO.deleteClassmanager(classmanager);
		// }
		// for (int i = 0; i < list_co.size(); i++) {
		// Collegemanager collegemanager = (Collegemanager) list_co.get(i);
		// managermodelDAO.deleteCollegeManager(collegemanager);
		// }
		// for (int i = 0; i < list_s.size(); i++) {
		// Schoolmanager schoolmanager = (Schoolmanager) list_s.get(i);
		// managermodelDAO.deleteSchoolManager(schoolmanager);
		// }
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#saveCollegeManager(org.king.classmanage.domain.Collegemanager)
	 */
	public void saveCollegeManager(Collegemanager collegemanager) {
		// TODO Auto-generated method stub
		managermodelDAO.saveCollegeManager(collegemanager);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#deleteCollegeManager(java.lang.String,
	 *      java.lang.String)
	 */
	public void deleteCollegeManager(String collegeId) {
		// TODO Auto-generated method stub
		managermodelDAO.deleteCollegeManager(collegeId);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#saveSchoolManager(org.king.classmanage.domain.Schoolmanager)
	 */
	public void saveSchoolManager(Schoolmanager schoolmanager) {
		// TODO Auto-generated method stub
		managermodelDAO.saveSchoolManager(schoolmanager);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#deleteSchoolManager(org.king.classmanage.domain.Schoolmanager)
	 */
	public void deleteSchoolManager(String schoolId) {
		// TODO Auto-generated method stub
		managermodelDAO.deleteSchoolManager(schoolId);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#saveClassAssitant(org.king.classmanage.domain.Classmanager)
	 */
	public void saveClassAssitant(Classmanager classmanager) {
		// TODO Auto-generated method stub
		managermodelDAO.saveClassManager(classmanager);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#deleteClassAssitant(org.king.classmanage.domain.Classmanager)
	 */
	public void deleteClassAssitant(String classId) {
		// TODO Auto-generated method stub
		managermodelDAO.deleteClassAssitant(classId);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#saveClassTutor(org.king.classmanage.domain.Classmanager)
	 */
	public void saveClassTutor(Classmanager classmanager) {
		// TODO Auto-generated method stub
		managermodelDAO.saveClassManager(classmanager);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.classmanage.service.ManagerService#deleteClassTutor(org.king.classmanage.domain.Classmanager)
	 */
	public void deleteClassTutor(String classId) {
		// TODO Auto-generated method stub
		managermodelDAO.deleteClassTutor(classId);
	}

	public String findManagerclass(String managerId) {
		String classId = "";
		
		String datebuf = sdf1.format(new Date());//增加当前年份	
		
		List list = managermodelDAO
				.find("select new Map(b.classId as classId) from Classmanager a,Classmodel b where a.id.managerId='" + managerId
						+ "'and a.id.classId=b.classId and b.curYear='"+datebuf+"' ");
		if (list.size() > 0) {
			HashMap hashmap =  (HashMap)list.get(0);
			classId = (String)hashmap.get("classId");
		}
		return classId;
	}
	
	public List findManagerclass_hlxy(String managerId) {
//		String classId = "";
		
		String datebuf = sdf1.format(new Date());//增加当前年份	
		
		List list = managermodelDAO
				.find("select new Map(b.classId as classId) from Classmanager a,Classmodel b where a.id.managerId='" + managerId
						+ "'and a.id.classId=b.classId and b.curYear='"+datebuf+"' ");
//		if (list.size() > 0) {
//			HashMap hashmap =  (HashMap)list.get(0);
//			classId = (String)hashmap.get("classId");
//		}
		return list;
	}

	public String getRoleidByName(String roleName) {
		String roleId = "";
		List list = managermodelDAO
				.find("select a.id from Role a where a.name='" + roleName
						+ "'");
		if (list.size() > 0) {
			roleId = list.get(0).toString();
		}
		return roleId;
	}

	public String getAccountidByNo(String managerNo) {
		String managerId = "";
		List list = managermodelDAO
				.find("select a.id from Account a where a.name ='" + managerNo
						+ "'");
		if (list.size() > 0) {
			managerId = list.get(0).toString();
		}
		return managerId;
	}

}
