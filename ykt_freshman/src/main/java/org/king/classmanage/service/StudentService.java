/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentService.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-30     ������             
 * <p>
 *
 * @author      ������
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
	* Description:   ��ѯ�༶ѧ��
	*@param classId
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public List getStudentbyClass(String classId);
	
	public List getAbroadStudent();
	
	/**
	* Description: ��ѧ������������ѯ
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
	* Description: ���ҹ����ֵ�
	*@param dicId
	*@return
	* @return Modify History: 2006-5-9 jackey create
	*/
	public List getDiction(String dicId);
	
	/**
	* Description: ���Ҳ���
	*@return
	* @return Modify History: 2006-6-28 jackey create
	*/
	public List getDepartment();
	
	
	/**
	* Description: ����¥�и��ӹ�ϵ�Ĺ����ֵ�
	*@param parent
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public List getDictionarybyParent(String parent);
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ��ѧ��������Ϣ��ѯ��
	*@param args
	* @return Modify History: 2006-4-30 jackey create
	*/
	public List getStudent(String[] args,String schoolId);
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ��ѧ��������Ϣ��ѯ������
	*@param args
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List getStudentExport(String[] args,String schoolId);
	
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ��ѧ��������Ϣ��ѯ������Ա
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-22 jackey create
	*/
	public List getfdyStudent(String[] args,String classId);
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ��ѧ��������Ϣ��ѯ������Ա����
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List getfdyStudentExport(String[] args,String classId);
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ������ѧ��������Ϣ��ѯ��
	*@param args
	*@return
	* @return Modify History: 2006-5-29 jackey create
	*/
	public Integer getStudentCount(String[] args,String schoolId);
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ������ѧ��������Ϣ��ѯ������Ա
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-22 jackey create
	*/
	public Integer getfdyStudentCount(String[] args,String classId);
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ�������༶��
	*@param args
	*@return
	* @return Modify History: 2006-5-9 jackey create
	*/
	public List findStudent(String[] args);	
	
	/**
	* Description: ���Ӳ�ѯѧ����Ϣ�������༶������
	*@param args
	*@return
	* @return Modify History: 2006-7-3 jackey create
	*/
	public List findStudentExport(String[] args);	
	
	/**
	* Description:  ���Ӳ�ѯѧ����Ϣ�����������༶��
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public Integer findStudentCount(String[] args);
	
	/**
	* Description: ѧ������ķ�������Ϣ
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public Integer getStudentDistributionResult();
	
	/**
	* Description: ��ѧ����������
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public Integer getDormDistributionResult();
	

	/**
	* Description: ����ѧ���ķ�������Ϣ
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public void deleteStudentDormDistribution();
	
	/**
	* Description:  ������ѧ���ķְ���Ϣ
	* @return Modify History: 2006-6-28 jackey create
	*/
	public void deleteAbroadStuClassDistribution();
	
	/**
	* Description: ��������õ���רҵ��Ϣ
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getAllMajorinInfo();
	
	/**
	* Description: ��������õ���רҵ��Ϣ
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getCHNStudentCount();
	
	
	/**
	* Description: ��������õ������ѧ����Ϣ
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getAbroadStudentCount();
	
	
	/**
	* Description: ��Ժ�����Ľ��ͳ��
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getCollegeCHNStudentCount();
	
	/**
	* Description: ��Ժ�����Ľ��ͳ��
	*@return
	* @return Modify History: 2006-6-27 jackey create
	*/
	public List getCollegeAbroadStudentCount();
	
	
	/**
	* Description: ����Ժ���������
	*@return
	* @return Modify History: 2006-7-6 jackey create
	*/
	public List getCollegeDormitoryStatistic();
	
	/**
	* Description: ��Ժ�ϴη�������
	*@return
	* @return Modify History: 2006-6-30 jackey create
	*/
	public List getHisDistribution();
	
	/**
	* Description: ����Ժ������ͳ�Ʊ�
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
	 * ����ǰ׺�Ϳ�ʼ���Զ�����ѧ��
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
