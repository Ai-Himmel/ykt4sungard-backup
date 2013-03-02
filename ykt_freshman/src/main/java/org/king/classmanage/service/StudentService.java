/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentService.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-30     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.StuAdddelhis;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.exception.EnterenceNoNotExistException;
import org.king.classmanage.exception.FamilyAddressNotExistException;
import org.king.classmanage.exception.MakeStuNoFailException;
import org.king.classmanage.exception.StuNameNotExistException;
import org.king.classmanage.exception.TotalScoreNotExistException;
import org.king.dormitorymanage.exception.DormitoryNotExistException;
import org.king.dormitorymanage.exception.GenderNotExistException;
import org.king.dormitorymanage.exception.LocationNotExistException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.framework.dao.MyQuery;
import org.king.framework.service.Service;

public interface StudentService extends Service {
	
	public void saveStudent(Studentmodel studentmodel);
	
	public void updateStudent(Studentmodel studentmodel);
	
	public void updateStudentWithHis(Studentmodel studentmodel,ClassAlertHis classalerthis);

	public List getStudent();
	
	public void findDepartments(HttpServletRequest request);
	public List getStudentInfoByEnterenceNo(String enterenceNo);
	/**
	* Description:   查询班级学生
	*@param classId
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public List getStudentbyClass(String classId);
	
	public List getAbroadStudent();
	
	/**
	* Description: 留学生复杂条件查询
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public List getAbroadStudent(String[] args);
	
	public Studentmodel getStudent(String studentId);
	
	public void deleteStudent(String studentId);
	
	public List getStudentNoDorm();
	
	public void distributAbroadtoClass(String studentIds,String[] classIds);

	public void deleteAbroadDistribution();
	
	
	/**
	* Description: 查找国标字典
	*@param dicId
	*@return
	* @return Modify History: 2006-5-9 jackey create
	*/
	public List getDiction(String dicId);
	
	/**
	* Description: 查找部门
	*@return
	* @return Modify History: 2006-6-28 jackey create
	*/
	public List getDepartment();
	
	
	/**
	* Description: 宿舍楼有父子关系的国标字典
	*@param parent
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public List getDictionarybyParent(String parent);
	
	/**
	* Description: 复杂查询学生信息（学生基本信息查询）
	*@param args
	* @return Modify History: 2006-4-30 jackey create
	*/
	public List getStudent(String[] args,String schoolId);
	
	/**
	* Description: 复杂查询学生信息（学生基本信息查询）导出
	*@param args
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List getStudentExport(String[] args,String schoolId);
	
	
	/**
	* Description: 复杂查询学生信息（学生基本信息查询）辅导员
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-22 jackey create
	*/
	public List getfdyStudent(String[] args,String classId);
	
	/**
	* Description: 复杂查询学生信息（学生基本信息查询）辅导员导出
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List getfdyStudentExport(String[] args,String classId);
	
	/**
	* Description: 复杂查询学生信息人数（学生基本信息查询）
	*@param args
	*@return
	* @return Modify History: 2006-5-29 jackey create
	*/
	public Integer getStudentCount(String[] args,String schoolId);
	
	/**
	* Description: 复杂查询学生信息人数（学生基本信息查询）辅导员
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-22 jackey create
	*/
	public Integer getfdyStudentCount(String[] args,String classId);
	
	/**
	* Description: 复杂查询学生信息（调整班级）
	*@param args
	*@return
	* @return Modify History: 2006-5-9 jackey create
	*/
	public List findStudent(String[] args);	
	
	/**
	* Description: 复杂查询学生信息（调整班级）导出
	*@param args
	*@return
	* @return Modify History: 2006-7-3 jackey create
	*/
	public List findStudentExport(String[] args);	
	
	/**
	* Description:  复杂查询学生信息人数（调整班级）
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public Integer findStudentCount(String[] args);
	
	/**
	* Description: 学生宿舍的分配结果信息
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public Integer getStudentDistributionResult();
	
	/**
	* Description: 有学生的宿舍数
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public Integer getDormDistributionResult();
	

	/**
	* Description: 重置学生的分宿舍信息
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public void deleteStudentDormDistribution();
	
	/**
	* Description:  重置留学生的分班信息
	* @return Modify History: 2006-6-28 jackey create
	*/
	public void deleteAbroadStuClassDistribution();
	
	/**
	* Description: 宿舍分配用到的专业信息
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getAllMajorinInfo();
	
	/**
	* Description: 宿舍分配用到的专业信息
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getCHNStudentCount();
	
	
	/**
	* Description: 宿舍分配用到的外国学生信息
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getAbroadStudentCount();
	
	
	/**
	* Description: 书院分配后的结果统计
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getCollegeCHNStudentCount();
	
	/**
	* Description: 书院分配后的结果统计
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getCollegeAbroadStudentCount();
	
	
	/**
	* Description: 各书院的宿舍情况
	*@return
	* @return Modify History: 2006-7-6 jackey create
	*/
	public List getCollegeDormitoryStatistic();
	
	/**
	* Description: 书院上次分配的情况
	*@return
	* @return Modify History: 2006-6-30 jackey create
	*/
	public List getHisDistribution();
	
	/**
	* Description: 得书院的宿舍统计表
	*@return
	* @return Modify History: 2006-6-30 jackey create
	*/
	public List getCollegeDormitoryAll();
	
	public List find(String query);
	
	public List find(MyQuery query);
	
	public Studentmodel findbyStuId(String stuid);
	
	public void saveAddStu(StuAdddelhis stuAdddelhis);
	
	public void deleteStudent(Studentmodel studentmodel);
	
	public void addstu(List stuList);
	
	public void deleteStu(Studentmodel studentmodel);
	
	public void addConvertDorm(List stuList) throws EnterenceNoNotExistException,
	FamilyAddressNotExistException, StuNameNotExistException,
	TotalScoreNotExistException;
	
	/**
	 * 根据前缀和开始号自动生成学号
	 * @param request
	 */	
	public void AutoMakeByStartNo(HttpServletRequest request) throws MakeStuNoFailException;

	public Integer getStudentDistributionResult4yg(String perCode);

	public void deleteStudentDormDistribution4gy(String s);	
	
	public Integer getStudentDistributionResult(String schoolId);
	
	public void deleteStudentDormDistribution(String schoolId);
	
	public Integer getDormDistributionResult(String schoolId);
	
	public List getfdyStudent_hlxy(String[] args, List classlist) ;
	
	public Integer getfdyStudentCount_hlxy(String[] args, List classlist);
	
	public List getfdyStudentExport_hlxy(String[] args, List classlist);
	
	public List getStudentTempInfoByStudentNo(String studentNo);
	public List getStudentTempInfoByEnterenceNo(String enterenceNo);
	
	public void getStudent_hlxy(HttpServletRequest request);
	
	public List getStudentExport_hlxy(HttpServletRequest request);
	
	public List getmajorList();
	
	public List getfromProvinceList();
	
	public List getcountryList();
	
	public List getnationList();
	
	public void addConvertTempecard(List stuList) throws EnterenceNoNotExistException,
	FamilyAddressNotExistException, StuNameNotExistException,
	TotalScoreNotExistException ;
	
	public void findAssistantList(HttpServletRequest request);
}
