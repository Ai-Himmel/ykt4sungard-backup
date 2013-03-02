package org.king.check.service;
import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Department;
import org.king.check.exception.DepartmentAlreadyExistException;
import org.king.framework.exception.BusinessException;

public interface DepartmentService {

	/**
	 * 得到所有部门
	 * @return
	 */
	public List findAll();

	/**
	 * 根据部门编号得到部门
	 * @param id
	 * @return
	 */
	public Department getDepartment(Serializable id);
	
	
	/**
	 * 保存部门
	 * @param department
	 * @throws BusinessException
	 * @throws DepartmentAlreadyExistException
	 */
     public void saveDepartment(Department department) throws BusinessException,DepartmentAlreadyExistException;
  
     /**
      * 创建部门
      * @param catalog
      * @param parentid
      * @throws BusinessException
      */
     public void createDepartment(Department department, Serializable parentid) throws BusinessException;
     
     

     /**
      * 修改部门
      * @param department
      * @throws BusinessException
      */
     public void updateDepartment(Department department) throws BusinessException;

     /**
      * 删除部门
      * @param department
      * @throws BusinessException
      */
     public void deleteDepartment(String id) throws BusinessException;
     
     
     public List getDepartmentTree(int hierarchy,Department department);
     
     
     public List getDepartmentsByParantId(String parantId);

     /**
      * 得到部门的xml树
      * @return
      */
     public String getDepartmentXmlTree() ;

}