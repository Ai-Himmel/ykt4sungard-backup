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
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-25     ������             
 * <p>
 *
 * @author      ������
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
		* Description: �Ա��б�<br>
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
		* Description: ��Ԫ�б�<br>
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
	/**
	* Method name: getMajorListFromGraduateTable<br>
	* Description: �б�<br>
	* Return: List<br>
	* Args: @return
	* Modify History: <br>
	* ��������    ������     ����ʱ��       ��������<br>
	* ======================================<br>
	*  ����      �޷�    2007-6-19  <br>
	* @author   �޷�
	* @version 
	* @since 1.0
	*/

	public List getMajorListFromGraduateTable();
	
	
	
}
