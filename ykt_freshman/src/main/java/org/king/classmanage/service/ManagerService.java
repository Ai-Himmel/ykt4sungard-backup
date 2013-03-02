/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagerService.java
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
package org.king.classmanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmanager;
import org.king.classmanage.exception.ManagerInClassException;
import org.king.classmanage.exception.ManagerInCollegeException;
import org.king.classmanage.exception.ManagerInSchoolException;
import org.king.framework.service.Service;

public interface ManagerService extends Service {

	/**
	 * Description: 管理人员的基本信息
	 * 
	 * @param managerNo
	 * @return
	 * @return Modify History: 2006-5-29 jackey create
	 */
	public List findManagerInfo(String managerNo);
	
/**
 * 管理人员编辑页面需要的参数
 * @param request
 */	
	public void initForm(HttpServletRequest request);

	/**
	 * Description: 多条件查询管理人员
	 * 
	 * @param args
	 * @return Modify History: 2006-4-28 jackey create
	 */
	
	public Managermodel findManager(String manageId);
	
	public List findManager(String[] args,String schoolId);
	
	public List findManagerExport(String[] args,String schoolId);

	/**
	 * Description: 多条件查询管理人员人数
	 * 
	 * @param args
	 * @return
	 * @return Modify History: 2006-5-29 jackey create
	 */
	public Integer findManagerCount(String[] args,String schoolId);

	/**
	 * Description: 查询管理人员的角色
	 * 
	 * @param managerId
	 * @return
	 * @return Modify History: 2006-4-29 jackey create
	 */
	public List findManagerRole(String managerId);

	/**
	 * Description: 保存管理员
	 * 
	 * @param managermodel
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveManager(Managermodel managermodel);
	public void updateManager(Managermodel managermodel);
	
	/**
	 * 护理学院添加辅导员
	 * @param managermodel
	 * @param list
	 */
	public void saveManagerandRole_hlxy(Managermodel managermodel, List list) ;

	/**
	 * Description: 同时保存管理人员和角色信息
	 * 
	 * @param managermodel
	 * @param list
	 * @return Modify History: 2006-4-28 jackey create
	 */
	public void saveManagerandRole(Managermodel managermodel, List list);

	/**
	 * Description: 同时更新管理人员和角色信息
	 * 
	 * @param managermodel
	 * @param list
	 * @return Modify History: 2006-4-28 jackey create
	 */
	public void updateManagerandRole(Managermodel managermodel, List list,
			String roleStr)throws ManagerInClassException, ManagerInCollegeException,
			ManagerInSchoolException;

	/**
	 * Description: 查询所有管理员
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getManager();

	/**
	 * Description: 查询书院学工组组长
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getCollegeManager();
	
	public List getCollegeManager(boolean bool);

	/**
	 * Description: 通过书院查学工组组长
	 * 
	 * @param collegeId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getCollegeManager(String collegeId);

	/**
	 * Description: 保存书院管理员关系
	 * 
	 * @param collegemanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveCollegeManager(Collegemanager collegemanager);

	/**
	 * Description: 删除书院管理员关系
	 * 
	 * @param collegemanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteCollegeManager(String collegeId);

	/**
	 * Description: 查询学院管理员
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getSchoolManager();
	
	public List getSchoolManager(boolean bool);

	/**
	 * Description: 通过学院查管理员
	 * 
	 * @param schoolId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getSchoolManager(String schoolId);

	/**
	 * Description: 保存学院管理员关系
	 * 
	 * @param schoolmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveSchoolManager(Schoolmanager schoolmanager);

	/**
	 * Description: 删除学院管理员关系
	 * 
	 * @param schoolmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteSchoolManager(String schoolId);

	/**
	 * Description: 查询所有班级辅导员
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getClassAssitant();
	
	public List getClassAssitant(boolean bool);

	/**
	 * Description: 查询辅导员是否已在班级
	 * 
	 * @param managerId
	 * @return
	 * @return Modify History: 2006-5-27 jackey create
	 */
	public List getClassAssistantByManagerId(String managerId);

	/**
	 * Description: 查询管理员是否已在书院
	 * 
	 * @param managerId
	 * @return
	 */
	public List getCollegeAssistantByManagerId(String managerId);

	/**
	 * Description: 通过班号查辅导员
	 * 
	 * @param classId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getClassAssitant(String classId);

	/**
	 * Description: 保存班级辅导员关系
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveClassAssitant(Classmanager classmanager);

	/**
	 * Description: 删除班级辅导员关系
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteClassAssitant(String classId);

	/**
	 * Description: 查询班级导师
	 * 
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public List getClassTutor();
	
	public List getClassTutor(boolean bool);

	/**
	 * Description: 通过班号查导师
	 * 
	 * @param classId
	 * @return Modify History: 2006-4-27 jackey create
	 */
	public List getClassTutor(String classId);
	
	/**
	* Description: 通过班号查专业导师
	*@param classId
	*@return
	* @return Modify History: 2006-7-6 jackey create
	*/
	public List getClassSpeTutor(String classId);
	

	/**
	 * Description: 保存班级导师关系
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void saveClassTutor(Classmanager classmanager);

	/**
	 * Description: 删除班级导师关系
	 * 
	 * @param classmanager
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteClassTutor(String classId);

	/**
	 * Description: id查询管理员
	 * 
	 * @param manageId
	 * @return Modify History: 2006-4-26 jackey create
	 */
	public Managermodel getManager(String manageId);

	/**
	 * Description: 学工号查询管理员
	 * 
	 * @param managerNo
	 * @return
	 * @return Modify History: 2006-5-29 jackey create
	 */
	public List getManagerByNo(String managerNo);

	/**
	 * Description: 删除管理员
	 * 
	 * @param managerId
	 *            Modify History: 2006-4-26 jackey create
	 */
	public void deleteManager(String managerId);
	
	/**
	 * 修改管理员在任情况
	 * @param deleteX
	 */
	public void modifyManager_Available(String[] deleteX);

	/**
	 * Description: 同时删除管理员和角色信息
	 * 
	 * @param managerId
	 * @return Modify History: 2006-4-28 jackey create
	 */
	public boolean deleteManagerandRole(String managerId) throws ManagerInClassException,ManagerInCollegeException,ManagerInSchoolException;

	public boolean inRole(String managerId, String role);
	
	/**
	* Description: TODO
	*@param managerNo
	*@return班级id
	* @return Modify History: 2006-6-21 jackey create
	*/
	public String findManagerclass(String managerId);
	
	
	/**
	* Description: 通过角色名角色表中查找id
	*@param roleName
	*@return
	* @return Modify History: 2006-6-28 jackey create
	*/
	public String getRoleidByName(String roleName);
	
	/**
	* Description: 通过学工号查找accountid
	*@param roleName
	*@return
	* @return Modify History: 2006-6-28 jackey create
	*/
	public String getAccountidByNo(String managerNo);
	
/**
 * 护理学院用于查找班级辅导员等等
 * @return
 */	
	public List getClassAssitant_hlxy();
	
	public List getClassAssitant_hlxy(boolean bool);
	
	public List getClassTutor_hlxy();
	
	public List getClassTutor_hlxy(boolean bool);
	
	public List getClassAssitant_hlxy(String classId);
	
	public List getClassTutor_hlxy(String classId) ;
	
	public List getClassSpeTutor_hlxy(String classId) ;
	
	public List findManagerclass_hlxy(String managerId);
	
	

	
}
