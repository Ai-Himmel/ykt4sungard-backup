/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagermodelDAO.java
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
package org.king.classmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Managermanagerrole;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Schoolmanager;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface ManagermodelDAO extends DAO {

	/** 
	* Description: 条件查询
	* @param myQuery
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public List find(MyQuery myQuery);

	/** 
	* Description: HQL语句查询
	* @param query
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public List find(String query);

	/** 
	* Description: id查询
	* @param id
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public Managermodel get(Serializable id);

	/** 
	* Description: 全部查询
	* @return 
	* Modify History: 2006-4-26   jackey    create
	*/
	public List getAll();

	/** 
	* Description: 保存管理人员
	* @param transientInstance 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void save(Managermodel transientInstance);
	
	/**
	* Description: 保存管理人员角色信息
	*@param transientInstance
	* @return Modify History: 2006-4-28 jackey create
	*/
	public void saveDuties(Managermanagerrole transientInstance);

	/** 
	* Description: 更新记录
	* @param transientInstance 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void update(Managermodel transientInstance);

	/** 
	* Description: 删除管理人员记录
	* @param persistentInstance 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void delete(Managermodel persistentInstance);
	
	
	/**
	* Description:删除管理人员角色
	*@param persistentInstance
	* @return Modify History: 2006-4-28 jackey create
	*/
	public void deleteManagermanagerRole(Managermanagerrole persistentInstance);
	

	/** 
	* Description: 复杂查询
	* @param Obj  学院参数：school 书院参数：college 班级辅导员参数：class_ass 班级导师参数：class_tu 专业导师参数: class_spetu
	* @param id   id 如果为<br>  "GET_ALL"  </br>则表示查询所有  schoolId 表示所属院系
	* @return 
	* Modify History: 2006-4-27   jackey    create
	*/
	public List findSpecial(String Obj,String id,String schoolId);
	

	/** 
	* Description: 复杂查询
	* @param Obj  学院参数：school 书院参数：college 班级辅导员参数：class_ass 班级导师参数：class_tu 
	* @param id   id 如果为<br>  "GET_ALL"  </br>则表示查询所有  
	* @param check True 表示直接查询出没有分配的人员
	* @return Modify History: 2006-7-4 jackey create
	*/

	public List findSpecial(String Obj, String id, boolean check,String schoolId);
	
	
	/** 
	* Description: 保存书院管理员关系
	* @param collegemanager 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void saveCollegeManager(Collegemanager collegemanager);
	
	/** 
	* Description: 删除书院管理员关系
	* @param collegeId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteCollegeManager(String collegeId);
	
	
	/**
	* Description:  删除书院管理员
	*@param collegemanager
	* @return Modify History: 2006-5-29 jackey create
	*/
	public void deleteCollegeManager(Collegemanager collegemanager);
	
	/** 
	* Description: 保存学院管理员关系
	* @param schoolmanager 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void saveSchoolManager(Schoolmanager schoolmanager);
	
	/** 
	* Description: 删除学院管理员关系
	* @param schoolId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteSchoolManager(String schoolId);
	
	/**
	* Description: 删除学院管理员
	*@param schoolmanager
	* @return Modify History: 2006-5-29 jackey create
	*/
	public void deleteSchoolManager(Schoolmanager schoolmanager);
	
	/** 
	* Description: 保存班级管理员关系
	* @param classmanager 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void saveClassManager(Classmanager classmanager);
	
	/** 
	* Description: 删除班级辅导员关系
	* @param classId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteClassAssitant(String classId);
	
	/**
	* Description: 删除班级管理原
	*@param classmanager
	* @return Modify History: 2006-5-29 jackey create
	*/
	public void deleteClassmanager(Classmanager classmanager);
	
	
	/** 
	* Description: 保存班级导师关系
	* @param classId 
	* Modify History: 2006-4-26   jackey    create
	*/
	public void deleteClassTutor(String classId);
	

}
