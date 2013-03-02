package org.king.check.service.impl;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.common.tst.DepartmentSearchEngine;
import org.king.check.dao.DepartmentDAO;
import org.king.check.domain.Department;
import org.king.check.service.DepartmentTreeService;
import org.king.framework.exception.BusinessException;

import java.util.List;

/**
 * 构造班级树形结构，并支持拼音查找操作
 * User: Yiming.You
 * Date: 2010-9-20
 */
public class DepartmentTreeServiceImpl implements DepartmentTreeService {
    private static Log log = LogFactory.getLog(DepartmentTreeServiceImpl.class);

    private DepartmentSearchEngine searchEngine;

    private DepartmentDAO departmentDAO;

    public void setDepartmentDAO(DepartmentDAO departmentDAO) {
        this.departmentDAO = departmentDAO;
    }

    /**
     * you can call this method just when the department has been changed
     */
    public void initDepartmentTree() throws BusinessException {
        log.info("init department tree");
        List sources = departmentDAO.find("select d from Department d,TDept dept where dept.deptcode=d.faculty");
        searchEngine = new DepartmentSearchEngine(sources);
    }

    private DepartmentSearchEngine getSearchEngine() throws BusinessException {
        if (searchEngine == null) {
            synchronized (searchEngine) {
                if (searchEngine == null) {
                    initDepartmentTree();
                }
            }
        }
        return searchEngine;
    }

    public List<Department> searchAllDepartment(String prefix) throws BusinessException {
        return getSearchEngine().searchAll(prefix);
    }

    public Department searchDepartment(String prefix) throws BusinessException {
        return getSearchEngine().search(prefix);
    }
}
