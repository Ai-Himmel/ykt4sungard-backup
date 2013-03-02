package org.king.yangong.dormitorymanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.classmanage.domain.ClassDorm;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.yangong.dormitorymanage.domain.YxGraduate;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DormitorymodelDAO.java
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
public interface YxGraduateDAO extends DAO {
	
	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public YxGraduate get(Serializable id);
	
	public List getAll();
	
	public void save(YxGraduate transientInstance);
	
    public void update(YxGraduate transientInstance);
    
    public void delete(YxGraduate persistentInstance);
    
    public void deleteClassDorm(ClassDorm classdorm);
    
    public void saveClassDorm(ClassDorm classdorm);
    
    public void updateClassDorm(ClassDorm classdorm);
	/**
	* Method name: getStudentTypeList<br>
	* Description: 学生类型列表<br>
	* Return: @return<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
    public List getStudentTypeList();
	/**
	* Method name: getStyleList<br>
	* Description: 培养方式列表<br>
	* Return: List<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
    public List getStyleList();
	/**
	* Method name: getCollegeList<br>
	* Description: 录取院系列表<br>
	* Return: List<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
    public List getCollegeList();
	/**
	* Method name: getCollegeListFromGraduateTable<br>
	* Description: 从研究生表中获得学院信息列表<br>
	* Return: List<br>
	* Args: @return
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
    public List getCollegeListFromGraduateTable();

    /**
	* Method name: getQuarterBindingList<br>
	* Description: 宿舍资源列表<br>
	* Return: List<br>
	* Args: @return
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/    
    public List getDormitoryList(String stuemp_no);
	/**
	* Method name: getSpecialityList<br>
	* Description: 专业列表<br>
	* Return: List<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
	public List getSpecialityList();
	/**
	* Method name: getTypeList<br>
	* Description: 研究生类型列表<br>
	* Return: List<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
	public List getTypeList();
	
	/**
		* Method name: getTabssdeptList<br>
		* Description: 获得管理部门<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-18  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getTabssdeptList(String stuemp_no);
	/**
	* Method name: getDistrictionList<br>
	* Description: 获得宿舍区域列表<br>
	* Return: List<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
	public List getDistrictionList();
	/**
	* Method name: getRequestavailableList<br>
	* Description: 是否可以申请宿舍字典表  1是  2否<br>
	* Return: List<br>
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      何林青    2007-6-8  <br>
	* @author   何林青
	* @version 
	* @since 1.0
	*/
	public List getRequestavailableList();
	
	/**
		* Method name: getSexList<br>
		* Description: 性别列表<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getSexList();
	
	/**
		* Method name: getSectionList<br>
		* Description: 获得宿舍校区列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getSectionList();
	
	/**
		* Method name: getBuildingList<br>
		* Description: 获得宿舍楼号列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getBuildingList();
	
	/**
		* Method name: getLayerList<br>
		* Description: 获得宿舍层列表<br>
		* Return: List<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getLayerList();
	
	/**
		* Method name: getCellList<br>
		* Description: 单元列表<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-6-8  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getCellList();
	/**
	* Method name: getMajorListFromGraduateTable<br>
	* Description: 列表<br>
	* Return: List<br>
	* Args: @return
	* Modify History: <br>
	* 操作类型    操作人     操作时间       操作内容<br>
	* ======================================<br>
	*  创建      罗帆    2007-6-19  <br>
	* @author   罗帆
	* @version 
	* @since 1.0
	*/

	public List getMajorListFromGraduateTable();
	
	
	
}
