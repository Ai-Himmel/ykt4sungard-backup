package org.king.check.service;

import org.apache.struts.action.DynaActionForm;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.Department;
import org.king.check.exception.DepartmentAlreadyExistException;
import org.king.framework.exception.BusinessException;
import org.king.security.domain.Account;

import java.io.Serializable;
import java.util.List;

public interface DepartmentService {

    public List findallGard();


    public List findAllsubDeptment();

    public List getAreaByGard();

    public List getClassByArea();

    public List getClassByArea(String accountId);

    /*
      * 查找部门
      *
      */

    public List findDept(String id);

    /**
     * 得到所有部门
     *
     * @return
     */
    public List findAll();

    /**
     * 根据部门编号得到部门
     *
     * @param id
     * @return
     */
    public Department getDepartment(Serializable id);


    /**
     * 保存部门
     *
     * @param department
     * @throws BusinessException
     * @throws DepartmentAlreadyExistException
     *
     */
    public void saveDepartment(Department department) throws BusinessException, DepartmentAlreadyExistException;

    /**
     * 创建部门
     *
     * @param parentid
     * @throws BusinessException
     */
    public void createDepartment(Department department, Serializable parentid) throws BusinessException;


    /**
     * 修改部门
     *
     * @param department
     * @throws BusinessException
     */
    public void updateDepartment(Department department) throws BusinessException;

    /**
     * 删除部门
     *
     * @param id
     * @throws BusinessException
     */
    public void deleteDepartment(String id) throws BusinessException;


    public List getDepartmentTree(int hierarchy, Department department);


    public List getDepartmentsByPlanId(String planId);

    /**
     * 得到部门的xml树
     *
     * @return
     */
    public String getDepartmentXmlTree(String accountId);

    public Department getDepartmentByName(String name);

    /**
     * find all the departments except the root department
     *
     * @return
     */
    public List findAllDepartments();

    public void findDepartmentsByPage(DynaActionForm dform, DBPageLimit page);

    public List getDeptTree();

    public List findDepartments(String createYear, String pid, String areaCode);

    public Long deleteDepartments(String[] deptIds);

    /**
     * 通过班级信息找到所有的校区
     *
     * @return .
     */
    public List findAreaFromDepartment(String pid);

    public List findAreaFromDepartment();

    /**
     * 找到院系
     *
     * @return .
     */
    public List findFaculty();

    /**
     * 根据校区代码和院系代码查找班级，不判断权限
     *
     * @param areaCode 校区代码
     * @param pid  院系代码的父节点
     * @return .
     */
    public List findDepartment(String areaCode, String pid);

    /**
     * 根据校区代码和院系代码查找班级，判断权限
     *
     * @param areaCode 校区代码
     * @param pid  院系代码的父节点
     * @param account  当前登录账户
     * @return .
     */
    public List findDepartment(String areaCode, String pid, Account account);

    /**
     * 根据校区代码，院系代码，班级代码查找课程，不判断权限
     *
     * @param areaCode 校区代码
     * @param pid  院系代码的父节点
     * @param deptId   班级代码
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId);

    public List findAllCourse();
    /**
     * 根据校区代码，院系代码，班级代码查找课程，判断权限
     *
     * @param areaCode 校区代码
     * @param pid  院系代码的父节点
     * @param deptId   班级代码
     * @param account  当前登录账户
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId, Account account);

    /**
     * 在用户登陆时，根据角色查找该用户有权限访问的班级，然后将账户班级关系更新
     *
     * @param account .
     */
    public void refreshOperLimt(final Account account);
}