package org.king.check.service;
import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Department;
import org.king.check.exception.DepartmentAlreadyExistException;
import org.king.framework.exception.BusinessException;

public interface DepartmentService {

	/**
	 * �õ����в���
	 * @return
	 */
	public List findAll();

	/**
	 * ���ݲ��ű�ŵõ�����
	 * @param id
	 * @return
	 */
	public Department getDepartment(Serializable id);
	
	
	/**
	 * ���沿��
	 * @param department
	 * @throws BusinessException
	 * @throws DepartmentAlreadyExistException
	 */
     public void saveDepartment(Department department) throws BusinessException,DepartmentAlreadyExistException;
  
     /**
      * ��������
      * @param catalog
      * @param parentid
      * @throws BusinessException
      */
     public void createDepartment(Department department, Serializable parentid) throws BusinessException;
     
     

     /**
      * �޸Ĳ���
      * @param department
      * @throws BusinessException
      */
     public void updateDepartment(Department department) throws BusinessException;

     /**
      * ɾ������
      * @param department
      * @throws BusinessException
      */
     public void deleteDepartment(String id) throws BusinessException;
     
     
     public List getDepartmentTree(int hierarchy,Department department);
     
     
     public List getDepartmentsByParantId(String parantId);

     /**
      * �õ����ŵ�xml��
      * @return
      */
     public String getDepartmentXmlTree() ;

}