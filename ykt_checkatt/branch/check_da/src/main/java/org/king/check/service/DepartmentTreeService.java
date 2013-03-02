package org.king.check.service;

import org.king.check.domain.Department;
import org.king.framework.exception.BusinessException;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-20
 */
public interface DepartmentTreeService {
    public void initDepartmentTree() throws BusinessException;

    public List<Department> searchAllDepartment(String prefix) throws BusinessException;

    public Department searchDepartment(String prefix) throws BusinessException;
}
