/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeService.java
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
package org.king.classmanage.service;

import java.util.List;

import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Collegemodel;
import org.king.framework.service.Service;


public interface CollegeService extends Service {
	
	/** 
	* Description: 保存书院信息
	* @param collegemodel
	* Modify History: 2006-4-25   jackey    create
	*/
	public void saveCollege(Collegemodel collegemodel);	
	
	/** 
	* Description: 事务性保存书院及学工组组长信息
	* @param collegemodel
	* @param collegeleader
	* @param collegemanager 
	* Modify History: 2006-4-27   jackey    create
	*/
	public void saveCollegeAndLeader(Collegemodel collegemodel,String collegeleader,Collegemanager collegemanager);
	
	/** 
	* Description: 事务性更新书院及学工组组长信息
	* @param collegemodel
	* @param collegeleader
	* @param collegemanager 
	* Modify History: 2006-4-27   jackey    create
	*/
	public void updateCollegeAndLeader(Collegemodel collegemodel,String collegeleader,Collegemanager collegemanager);
	
	/** 
	* Description: 通过书院id查询学院信息
	* @param collegeId
	* @return Collegemodel
	* Modify History: 2006-4-25   jackey    create
	*/
	public Collegemodel getCollege(String collegeId);
	
	/**
	* Description: 通过书院编号查询学院信息
	*@param collegeNo
	*@return
	* @return Modify History: 2006-5-30 jackey create
	*/
	public List getCollegebyNo(String collegeNo);
	
	/**
	* Description: 通过书院名称查询学院信息
	*@param collegeName
	*@return
	* @return Modify History: 2006-6-5 jackey create
	*/
	public List getCollegebyName(String collegeName);
	
	/** 
	* Description: 查询所有书院信息
	* @return List
	* Modify History: 2006-4-25   jackey    create
	*/
	public List getAllCollege();
	
	/** 
	* Description: 查询复旦学院所有书院信息
	* @return List
	* Modify History: 2006-4-25   jackey    create
	*/	
	public List getAllCollegeByfdxy();
	/** 
	* Description: 删除书院信息
	* @param collegeId 
	* Modify History: 2006-4-25   jackey    create
	*/
	
	public void deleteCollege(String collegeId);
	
	/** 
	* Description: 给书院分配班级
	* @param collegeId
	* @param classId 
	* Modify History: 2006-4-25   jackey    create
	*/
	public void distributeClass(String collegeId,List classId);

}
