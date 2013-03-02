/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassService.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-29     ������             
 * <p>
 *
 * @author      ������
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
	* Description: ����༶��Ϣ
	*@param classmodel
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveClassmodel(Classmodel classmodel);
	
	/**
	* Description: ͬʱ����༶�͹�����Ա��Ϣ
	*@param classmodel
	*@param list
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveClassandManager(Classmodel classmodel,List list,String collegeId);
	
	
	/**
	* Description: ���°༶�͹�����Ա��Ϣ
	*@param classmodel
	*@param list
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void updateClassandManager(Classmodel classmodel,List list,String collegeId);
	
	/**
	* Description: ͨ���༶�Ų�ѯ�༶��Ϣ
	*@param classId
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public Classmodel getClassmodel(String classId);
	
	/**
	* Description:ͨ���༶��Ų�ѯ�༶��Ϣ
	*@param classNo
	*@return
	* @return Modify History: 2006-5-27 jackey create
	*/
	public List getClassmodelbyNo(String classNo);
	
	
	/**
	* Description: ͨ���༶���Ʋ�ѯ�༶��Ϣ
	*@param className
	*@return
	* @return Modify History: 2006-6-5 jackey create
	*/
	public List getClassmodelbyName(String className);
	
	/**
	* Description: ��ѯ���а༶��Ϣ
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List getClassmodel();
/**
 * ������ӦԺϵ�İ༶
 * @param schoolId
 * @return
 */	
	public List getClassmodelbyschoolId(String schoolId);
	/**
	* Description: ɾ���༶��Ϣ
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void deleteClassmodel(Classmodel classmodel);
	
	/**
	* Description: ͬʱɾ���༶�͹�����Ա��Ϣ
	*@param classmodel
	* @return Modify History: 2006-4-30 jackey create
	*/
	public void deleteClassandManager(Classmodel classmodel);
	
	/**
	* Description: ͨ��ѧԺid��ѯ���а༶��Ϣ
	*@param collegeId
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List getClassbyCollegeId(String collegeId);
	
	/**
	* Description: ����༶�󶨴���
	*@param classId
	*@param dormitoryId
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveConnection(String classId,List dormitoryId);
	
	/**
	* Description: �༶����
	*@param StudentId
	*@param classId
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void alertClass(List StudentId,String classId);
	
	/**
	* Description: �༶������ʷ
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List getAlertHistory(String[] args,String schoolId);
	
	/**
	* Description: �༶������ʷ����
	*@param args
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List getAlertHistoryExport(String[] args,String schoolId);
	
	/**
	* Description: �༶������ʷ��¼��
	*@param args
	*@return
	* @return Modify History: 2006-6-9 jackey create
	*/
	public Integer getAlertHistoryCount(String[] args);
	
	/**
	* Description: ����༶������ʷ��¼
	*@param studentId
	*@param classId_o
	*@param classId_n
	* @return Modify History: 2006-4-29 jackey create
	*/
	public void saveAlertHistory(String studentId,String classId_o,String classId_n);
	
	/**
	* Description: ����������ѯ�༶���༶ά������ģ�飩
	*@param args
	*@return
	* @return Modify History: 2006-4-29 jackey create
	*/
	public List findClass(String[] args);
	
	public List findClassExport(String[] args);
	
	
	/**
	* Description: ����������ѯ�༶�������༶ά������ģ�飩
	*@param args
	*@return
	* @return Modify History: 2006-5-25 jackey create
	*/
	public Integer getClassCount(String[] args);
	
	
	/**
	* Description: ����������ѯ�༶���༶��ѯ����ģ�飩
	*@param args
	*@return
	* @return Modify History: 2006-4-30 jackey create
	*/
	public List findClassSearch(String[] args,String schoolId);
	
	public List findClassSearchExport(String[] args,String schoolId);
	
	/**
	* Description: ����������ѯ�༶���༶��ѯ����ģ�飩����Ա
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List findfdyClassSearch(String[] args,String classId);
	
	/**
	* Description: ����������ѯ�༶�������༶��ѯ����ģ�飩����Ա
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-26 jackey create
	*/
	public List findfdyClassSearchExport(String[] args,String classId);
	
	
	/**
	* Description: ����������ѯ�༶�������༶��ѯ����ģ�飩
	*@param args
	*@return
	* @return Modify History: 2006-5-26 jackey create
	*/
	public Integer getClassSearchCount(String[] args,String schoolId);
	
	
	/**
	* Description: ����������ѯ�༶�������༶��ѯ����ģ�飩����Ա
	*@param args
	*@param classId
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public Integer getfdyClassSearchCount(String[] args,String classId);
	
	/**
	* Description: �༶ͳ��
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List classResultStatistic(String schoolId);
	
	
	/**
	* Description: �༶ͳ�ƣ���ѧ��������
	*@return
	* @return List
	* Modify History: 2006-8-25 jackey create
	*/
	public List classResultStatisticWithAbroad(String schoolId);
	
	/**
	* Description: ������༶ͳ��
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List classCheckInResultStatistic(String schoolId);
	
	/**
	* Description: ������༶ͳ�ƣ���ѧ��������
	*@return
	* @return List
	* Modify History: 2006-8-25 jackey create
	*/
	public List classCheckInResultStatisticWithAbroad(String schoolId);
	/**
	* Description: �����б�
	*@return
	* @return Modify History: 2006-5-15 jackey create
	*/
	public List nationList();
	
	/**
	* Description: �����������б�
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationCheckInList();
	
	/**
	* Description: ����ͳ��
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List nationResultStatistic(String schoolId);
	
	/**
	* Description:  ����������ͳ��
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationCheckInResultStatistic(String schoolId);
	
	/**
	* Description: �����ѧ��רҵͳ�ƣ���ѧ���ְ���ͳ�ƣ�
	*@return
	* @return Modify History: 2006-6-13 jackey create
	*/
	public List abroadMajorinResultStatistic();
	
	/**
	* Description: ��Ժ�༶�б�
	*@return
	* @return Modify History: 2006-6-12 jackey create
	*/
	public List getCollegeClassList(String schoolId);
	
	/**
	* Description: רҵͳ��
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List majorinResultStatistic(String schoolId);
	
	/**
	* Description:  ������רҵͳ��
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List majorinCheckInResultStatistic(String schoolId);
	/**
	* Description: רҵ�б�
	*@return
	* @return Modify History: 2006-5-16 jackey create
	*/
	public List majorinList();
	
	/**
	* Description:������רҵ�б�
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List majorinCheckInList();
	
	/**
	* Description: ��ѧ����רҵ�б���ѧ���ְ���ͳ�ƣ�
	*@return
	* @return Modify History: 2006-6-13 jackey create
	*/
	public List abroadMajorinList();
	
	/**
	* Description: ��Դ��ͳ��
	*@return
	* @return Modify History: 2006-5-12 jackey create
	*/
	public List nativeplaceResultStatistic(String schoolId);
	
	/**
	* Description: ��������Դ��ͳ��
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nativeplaceCheckInResultStatistic(String schoolId);
	
	/**
	* Description: ʡ���б�
	*@return
	* @return Modify History: 2006-5-16 jackey create
	*/
	public List provinceList();
	
	
	/**
	* Description: �����б�
	*@return
	* @return Modify History: 2006-6-20 jackey create
	*/
	public List nationalityList();
	
	/**
	* Description: ����������б�
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationalityCheckInList();
	
	/**
	* Description: ����ͳ��
	*@return
	* @return Modify History: 2006-6-20 jackey create
	*/
	public List nationalityResultStatistic(String schoolId);
	
	/**
	* Description: ���������ͳ��
	*@return
	* @return Modify History: 2006-6-21 jackey create
	*/
	public List nationalityCheckInResultStatistic(String schoolId);

	/**
	* Description: ����ͳ��
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List daleiResultStatistic(String schoolId);
	
	/**
	* Description: ���������ͳ��
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List daleiCheckInResultStatistic(String schoolId);
	
	/**
	* Description: ����Ժרҵ����ͳ��
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List zhuanyeResultStatistic();
	
	/**
	* Description: ���������Ժרҵ����ͳ��
	*@return
	* @return List
	* Modify History: 2006-8-21 jackey create
	*/
	public List zhuanyeCheckInResultStatistic();
	
	/**
	* Description: ���Էְ�İ༶�б�
	*@return
	* @return Modify History: 2006-5-17 jackey create
	*/
	public List findClassList();
	
	/**
	* Description: ���Ӳ�ѯ���Էְ�İ༶�б�
	*@param args
	*@return
	* @return Modify History: 2006-6-15 jackey create
	*/
	public List findClassList(String[] args);
	/**
	 * ��ð༶������Ժ��Ϣ
	 * @param classId
	 * @return
	 */
	public Collegemodel getCollegeByClassId(String classId);
	
	/**
	 * ���ݹ��Ź��˳�����Ͻ�����᷶Χ��
	 * @param request
	 * @param xhorgh
	 */
	
	public void initForm(HttpServletRequest request);
	/**
	 * ����ѧԺ
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
			* Description: �õ�ҳ���Ӧ��ӳ������Ϣ<br>
			* Return: StudentListColumns<br>
			* Args: @param accountId
			* Args: @param pageId
			* Args: @return
			* Modify History: <br>
			* ��������    ������     ����ʱ��       ��������<br>
			* ======================================<br>
			*  ����      ������    Nov 13, 2007  <br>
			* @author   ������
			* @version 
			* @since 1.0
			*/
	public StudentListColumns getUserSessionColumns(String accountId,String pageId);
	
	

	
	/**
			* Method name: getNTableHeadList<br>
			* Description: ��ñ�ͷ�б�<br>
			* Return: List<br>
			* Args: @param accountId
			* Args: @param pageId
			* Args: @param flag
			* Args: @return
			* Modify History: <br>
			* ��������    ������     ����ʱ��       ��������<br>
			* ======================================<br>
			*  ����      ������    Nov 14, 2007  <br>
			* @author   ������
			* @version 
			* @since 1.0
			*/
	public List getNTableHeadList(String accountId,String pageId,String flag);
	
	public void saveUserSessionColumns(String accountId,String pageId,String tableheadleft,String tableheadright);
	public SdListhlxy getUserSessionhlxyColumns(String accountId,String pageId);
	public SdfdyListhlxy getUserSessionfdyhlxyColumns(String accountId,String pageId);
	public StudentfdyListColmns getUserSessionfdyColumns(String accountId,String pageId);
		
}
