package org.king.yangong.dormitorymanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.framework.exception.BusinessException;
import org.king.yangong.dormitorymanage.domain.YxGraduate;


/**
	* File name: YxGraduateService.java<br>
	* Description: <br>
	* Modify History: <br>
	* ��������    ������     ����ʱ��       ��������<br>
	* ======================================<br>
	*  ����      ������    2007-6-8  <br>
	* @author   ������(jackey)
	* @version 
	* @since 1.0
	*/
public interface YxGraduateService {

	/**
		* Method name: getStudentTypeList<br>
		* Description: ѧ�������б�<br>
		* Return: @return<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getStudentTypeList();
	
	/**
		* Method name: getStyleList<br>
		* Description: ������ʽ�б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getStyleList();
	
	/**
		* Method name: getCollegeList<br>
		* Description: ¼ȡԺϵ�б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getCollegeList();
	
	/**
		* Method name: getCollegeListFromGraduateTable<br>
		* Description: ���о������л��ѧԺ��Ϣ�б�<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getCollegeListFromGraduateTable();
	
	
	/**
			* Method name: getCollegeListFromGraduateTableLimit<br>
			* Description: <br>
			* Return: List<br>
			* Args: @param stuemp_no
			* Args: @return
			* Modify History: <br>
			* ��������    ������     ����ʱ��       ��������<br>
			* ======================================<br>
			*  ����      ������    2007-7-2  <br>
			* @author   ������
			* @version 
			* @since 1.0
			*/
	public List getCollegeListFromGraduateTableLimit(String stuemp_no);
		
	/**
	* Method name: getMajorListFromGraduateTable<br>
	* Description: �б�<br>
	* Return: List<br>
	* Args: @return
	* Modify History: <br>
	* ��������    ������     ����ʱ��       ��������<br>
	* ======================================<br>
	*  ����      �޷�    2007-6-8  <br>
	* @author   �޷�
	* @version 
	* @since 1.0
	*/
	public List getMajorListFromGraduateTable();
	/**
		* Method name: getCollegeBindingList<br>
		* Description: ��Ҫ���ѧԺ��Ϣ�б�<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getCollegeBindingList(String stuemp_no);
	
	/**
		* Method name: getQuarterBindingList<br>
		* Description: ������Դ�б�<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getDormitoryList(String stuemp_no);
	
	/**
		* Method name: getBindedDormitoryList<br>
		* Description: �Ѱ󶨵�������Դ�б�<br>
		* Return: List<br>
		* Args: @param stuemp_no
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-11  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getBindedDormitoryList(String stuemp_no);
	/**
		* Method name: getSpecialityList<br>
		* Description: רҵ�б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	
	public List getSpecialityList();
	
	/**
		* Method name: getTypeList<br>
		* Description: �о��������б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getTypeList();
	

	/**
		* Method name: getGraduatesList<br>
		* Description: �о���������Ϣ�б�<br>
		* Return: List<br>
		* Args: @param graduate ��ѯ������YxGraduate����
		* Args: @param args args[0]:ѧ�Ź���ӵڼ�����ʼ args[1]:�б����ڵڼ�ҳ
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getGraduatesList(YxGraduate graduate,String[] args);
	
	public Integer getGraduatesListCount(YxGraduate graduate,String[] args);

	/**
		* Method name: getGraduateResidentsList<br>
		* Description: �о���ס����������ɸѡ�б�<br>
		* Return: List<br>
		* Args: @param graduate ��ѯ������YxGraduate����
		* Args: @param args args[0]:ѧ�Ź���ӵڼ�����ʼ args[1]:�б����ڵڼ�ҳ
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getGraduateResidentsList(YxGraduate graduate,String[] args);
	
	public Integer getGraduateResidentsListCount(YxGraduate graduate,String[] args);
	/**
		* Method name: updateGraduates<br>
		* Description: �����о���������Ϣ<br>
		* Return: boolean<br>
		* Args: @param graduateNo ���µ��о���ѧ���б�
		* Args: @param args args[0]:��ס������ args[1]:��ѧ��
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public boolean updateGraduates(String[] graduateNo,String[] args);
	
	/**
		* Method name: updateGraduateResidents<br>
		* Description: �����о���ס����Ϣ<br>
		* Return: boolean<br>
		* Args: @param graduateNo ���µ��о���ѧ���б�
		* Args: @param args args[0]:������ args[1]:�Ƿ��������
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public boolean updateGraduateResidents(String[] graduateNo,String[] args,HttpServletRequest request);
	
	/**
		* Method name: getTabssdeptList<br>
		* Description: ��ù�����<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-18  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getTabssdeptList(String stuemp_no);
	
	/**
		* Method name: getDistrictionList<br>
		* Description: ������������б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getDistrictionList();
	
	/**
		* Method name: getRequestavailableList<br>
		* Description: �Ƿ�������������ֵ��  1��  2��<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getRequestavailableList();
	
	/**
		* Method name: getSexList<br>
		* Description: ���ѧ���Ա��б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getSexList();
	
	/**
		* Method name: getSectionList<br>
		* Description: �������У���б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getSectionList();
	
	/**
		* Method name: getBuildingList<br>
		* Description: �������¥���б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getBuildingList();
	
	/**
		* Method name: getLayerList<br>
		* Description: ���������б�<br>
		* Return: List<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getLayerList();
	
	
	/**
		* Method name: getCellList<br>
		* Description: ��Ԫ���б�<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-8  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getCellList();
	
	public boolean updateDormitory(String[] temp, String[] untemp,String stuemp_no)
	throws DormitoryHasStuException,Exception;
	
	/**
		* Method name: saveDormDistribution<br>
		* Description: ѧ����������<br>
		* Return: void<br>
		* Args: @throws DormitoryNotEnoughException
		* Args: @throws StudentAlreadyInDormException
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-13  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public void saveDormDistribution(String stuemp_no) throws DormitoryNotEnoughException,
	StudentAlreadyInDormException,Exception;
	
	/**
		* Method name: getCollegeStudentCount<br>
		* Description: ѧԺ��Ҫ��סѧ����ͳ����Ϣ<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-13  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getCollegeStudentCount(String stuemp_no);
	
	/**
		* Method name: getCollegeDormitoryStatistic<br>
		* Description: ѧԺ����İ����ͳ����Ϣ<br>
		* Return: List<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-13  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getCollegeDormitoryStatistic(String stuemp_no);
	
	/**
		* Method name: getGraduateCount<br>
		* Description: ������������ͳ��<br>
		* Return: String<br>
		* Args: @return
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-6-14  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public String getGraduateCount(String stuemp_no);
	
	
	public List getGraduateResidentsExport(YxGraduate graduate, String[] args)
	throws BusinessException ;

	public List getGraduateListByDorm(String operator);

	public List getSxList(String stuemp_no);

	public List getCanreqList(String stuemp_no);
	public List getGzListByDorm(String operator);
}
