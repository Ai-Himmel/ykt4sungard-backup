/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassService.java
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
package org.king.classmanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.StudentListColumns;
import org.king.classmanage.domain.StudentfdyListColmns;
import org.king.classmanage.domain.SdListhlxy;
import org.king.classmanage.domain.SdfdyListhlxy;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.framework.service.Service;

public interface ClassService extends Service {
	/**
	* Description: 保存班级信息
	*@param classmodel
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveClassmodel(Classmodel classmodel);
	
	/**
	* Description: 同时保存班级和管理人员信息
	*@param classmodel
	*@param list
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveClassandManager(Classmodel classmodel,List list,String collegeId);
	
	
	/**
	* Description: 更新班级和管理人员信息
	*@param classmodel
	*@param list
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void updateClassandManager(Classmodel classmodel,List list,String collegeId);
	
	/**
	* Description: 通过班级号查询班级信息
	*@param classId
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public Classmodel getClassmodel(String classId);
	
	/**
	* Description:通过班级编号查询班级信息
	*@param classNo
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public List getClassmodelbyNo(String classNo);
	
	
	/**
	* Description: 通过班级名称查询班级信息
	*@param className
	*@return
	* @return Modify History: 2006-6-5 jackey create
	*/
	public List getClassmodelbyName(String className);
	
	/**
	* Description: 查询所有班级信息
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List getClassmodel();
/**
 * 查找相应院系的班级
 * @param schoolId
 * @return
 */	
	public List getClassmodelbyschoolId(String schoolId);
	/**
	* Description: 删除班级信息
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void deleteClassmodel(Classmodel classmodel);
	
	/**
	* Description: 同时删除班级和管理人员信息
	*@param classmodel
	* @return Modify History: 2006-4-30 jackey create
	*/
	public void deleteClassandManager(Classmodel classmodel);
	
	/**
	* Description: 通过学院id查询所有班级信息
	*@param collegeId
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List getClassbyCollegeId(String collegeId);
	
	/**
	* Description: 宿舍班级绑定处理
	*@param classId
	*@param dormitoryId
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveConnection(String classId,List dormitoryId);
	
	/**
	* Description: 班级调整
	*@param StudentId
	*@param classId
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void alertClass(List StudentId,String classId);
	
	/**
	* Description: 班级调整历史
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List getAlertHistory(String[] args,String schoolId);
	
	/**
	* Description: 班级调整历史导出
	*@param args
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List getAlertHistoryExport(String[] args,String schoolId);
	
	/**
	* Description: 班级调整历史记录数
	*@param args
	*@return
	* @return Modify History: 2006-6-9 jackey create
	*/
	public Integer getAlertHistoryCount(String[] args);
	
	/**
	* Description: 保存班级调整历史记录
	*@param studentId
	*@param classId_o
	*@param classId_n
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveAlertHistory(String studentId,String classId_o,String classId_n);
	
	/**
	* Description: 复杂条件查询班级（班级维护功能模块）
	*@param args
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List findClass(String[] args);
	
	public List findClassExport(String[] args);
	
	
	/**
	* Description: 复杂条件查询班级个数（班级维护功能模块）
	*@param args
	*@return
	* @return Modify History: 2006-5-25 jackey create
	*/
	public Integer getClassCount(String[] args);
	
	
	/**
	* Description: 复杂条件查询班级（班级查询功能模块）
	*@param args
	*@return
	* @return Modify History: 2006-4-30 jackey create
	*/
	public List findClassSearch(String[] args,String schoolId);
	
	public List findClassSearchExport(String[] args,String schoolId);
	
	/**
	* Description: 复杂条件查询班级（班级查询功能模块）辅导员
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List findfdyClassSearch(String[] args,String classId);
	
	/**
	* Description: 复杂条件查询班级导出（班级查询功能模块）辅导员
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List findfdyClassSearchExport(String[] args,String classId);
	
	
	/**
	* Description: 复杂条件查询班级个数（班级查询功能模块）
	*@param args
	*@return
	* @return Modify History: 2006-5-26 jackey create
	*/
	public Integer getClassSearchCount(String[] args,String schoolId);
	
	
	/**
	* Description: 复杂条件查询班级个数（班级查询功能模块）辅导员
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public Integer getfdyClassSearchCount(String[] args,String classId);
	
	/**
	* Description: 班级统计
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List classResultStatistic(String schoolId);
	
	
	/**
	* Description: 班级统计（留学生人数）
	*@return
	* @return List
	* Modify History: 2006-8-25 jackey create
	*/
	public List classResultStatisticWithAbroad(String schoolId);
	
	/**
	* Description: 报到后班级统计
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List classCheckInResultStatistic(String schoolId);
	
	/**
	* Description: 报到后班级统计（留学生人数）
	*@return
	* @return List
	* Modify History: 2006-8-25 jackey create
	*/
	public List classCheckInResultStatisticWithAbroad(String schoolId);
	/**
	* Description: 民族列表
	*@return
	* @return Modify History: 2006-5-15 jackey create
	*/
	public List nationList();
	
	/**
	* Description: 报到后民族列表
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationCheckInList();
	
	/**
	* Description: 民族统计
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List nationResultStatistic(String schoolId);
	
	/**
	* Description:  报到后民族统计
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationCheckInResultStatistic(String schoolId);
	
	/**
	* Description: 外国留学生专业统计（留学生分班结果统计）
	*@return
	* @return Modify History: 2006-6-13 jackey create
	*/
	public List abroadMajorinResultStatistic();
	
	/**
	* Description: 书院班级列表
	*@return
	* @return Modify History: 2006-6-12 jackey create
	*/
	public List getCollegeClassList(String schoolId);
	
	/**
	* Description: 专业统计
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List majorinResultStatistic(String schoolId);
	
	/**
	* Description:  报到后专业统计
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List majorinCheckInResultStatistic(String schoolId);
	/**
	* Description: 专业列表
	*@return
	* @return Modify History: 2006-5-16 jackey create
	*/
	public List majorinList();
	
	/**
	* Description:报到后专业列表
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List majorinCheckInList();
	
	/**
	* Description: 留学生的专业列表（留学生分班结果统计）
	*@return
	* @return Modify History: 2006-6-13 jackey create
	*/
	public List abroadMajorinList();
	
	/**
	* Description: 生源地统计
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List nativeplaceResultStatistic(String schoolId);
	
	/**
	* Description: 报到后生源地统计
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nativeplaceCheckInResultStatistic(String schoolId);
	
	/**
	* Description: 省份列表
	*@return
	* @return Modify History: 2006-5-16 jackey create
	*/
	public List provinceList();
	
	
	/**
	* Description: 国籍列表
	*@return
	* @return Modify History: 2006-6-20 jackey create
	*/
	public List nationalityList();
	
	/**
	* Description: 报到后国籍列表
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationalityCheckInList();
	
	/**
	* Description: 国籍统计
	*@return
	* @return Modify History: 2006-6-20 jackey create
	*/
	public List nationalityResultStatistic(String schoolId);
	
	/**
	* Description: 报到后国籍统计
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationalityCheckInResultStatistic(String schoolId);

	/**
	* Description: 大类统计
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List daleiResultStatistic(String schoolId);
	
	/**
	* Description: 报到后大类统计
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List daleiCheckInResultStatistic(String schoolId);
	
	/**
	* Description: 各书院专业个数统计
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List zhuanyeResultStatistic();
	
	/**
	* Description: 报到后各书院专业个数统计
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List zhuanyeCheckInResultStatistic();
	
	/**
	* Description: 可以分班的班级列表
	*@return
	* @return Modify History: 2006-5-17 jackey create
	*/
	public List findClassList();
	
	/**
	* Description: 复杂查询可以分班的班级列表
	*@param args
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public List findClassList(String[] args);
	/**
	 * 获得班级所在书院信息
	 * @param classId
	 * @return
	 */
	public Collegemodel getCollegeByClassId(String classId);
	
	/**
	 * 根据工号过滤出所管辖的宿舍范围等
	 * @param request
	 * @param xhorgh
	 */
	
	public void initForm(HttpServletRequest request);
	/**
	 * 护理学院
	 * @param args
	 * @param response
	 */
	public List findClassExport_hlxy(String[] args);
	
	public Integer getClassCount_hlxy(String[] args);
	
	public List findClass_hlxy(String[] args);
	
	public void saveClassandManager_hlxy(Classmodel classmodel, List list);
	
	public void updateClassandManager_hlxy(Classmodel classmodel, List list) ;
	
	public boolean updateGzClass();
	
	public boolean updateGzClassAlert(String[] ids,String toclassId,String operator);
	
	public List find(String query);
	
	public boolean updateDormitory(String[] temp, String[] untemp,String curDept)
	throws DormitoryHasStuException;
			
	public boolean updateMenuTime(MenuTime menuTime);
	
	public Integer getClassDistributionResult();
	
	public void deleteClassDistribution();
	
    public Integer getDormDistributionResult();
	
	public void deleteDormDistribution();
	
	public List examTypeList();
	
	public List examTypeCheckInList();
	
	public List tempexamTypeStatistic(String schoolId);
	
	public List examTypeStatistic(String schoolId);
	
	public List examTypeCheckedinStatistic(String schoolId);
	
	public List genderList();
	
	public List genderCheckInList();
	
	public List tempgenderStatistic(String schoolId);
	
	public List genderResultStatistic(String schoolId);
	
	public List genderCheckInResultStatistic(String schoolId);
	
	public List getGzClassList(String schoolId);
	
	public Integer getfdyClassSearchCount_hlxy(String[] args, List classlist) ;
	
	public List findfdyClassSearch_hlxy(String[] args, List classlist);
	
	public List findfdyClassSearchExport_hlxy(String[] args, List classlist);
	
	public List daleiResultStatisticDormDistr() ;
	
	public void initClassForm(HttpServletRequest request,String classId);
	
	
	/**
			* Method name: getUserSessionColumns<br>
			* Description: 得到页面对应的映射列信息<br>
			* Return: StudentListColumns<br>
			* Args: @param accountId
			* Args: @param pageId
			* Args: @return
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Nov 13, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	public StudentListColumns getUserSessionColumns(String accountId,String pageId);
	
	

	
	/**
			* Method name: getNTableHeadList<br>
			* Description: 获得表头列表<br>
			* Return: List<br>
			* Args: @param accountId
			* Args: @param pageId
			* Args: @param flag
			* Args: @return
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Nov 14, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	public List getNTableHeadList(String accountId,String pageId,String flag);
	
	public void saveUserSessionColumns(String accountId,String pageId,String tableheadleft,String tableheadright);
	public SdListhlxy getUserSessionhlxyColumns(String accountId,String pageId);
	public SdfdyListhlxy getUserSessionfdyhlxyColumns(String accountId,String pageId);
	public StudentfdyListColmns getUserSessionfdyColumns(String accountId,String pageId);
		
}
