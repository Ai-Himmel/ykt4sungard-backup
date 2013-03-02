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
      * ���Ҳ���
      *
      */

    public List findDept(String id);

    /**
     * �õ����в���
     *
     * @return
     */
    public List findAll();

    /**
     * ���ݲ��ű�ŵõ�����
     *
     * @param id
     * @return
     */
    public Department getDepartment(Serializable id);


    /**
     * ���沿��
     *
     * @param department
     * @throws BusinessException
     * @throws DepartmentAlreadyExistException
     *
     */
    public void saveDepartment(Department department) throws BusinessException, DepartmentAlreadyExistException;

    /**
     * ��������
     *
     * @param parentid
     * @throws BusinessException
     */
    public void createDepartment(Department department, Serializable parentid) throws BusinessException;


    /**
     * �޸Ĳ���
     *
     * @param department
     * @throws BusinessException
     */
    public void updateDepartment(Department department) throws BusinessException;

    /**
     * ɾ������
     *
     * @param id
     * @throws BusinessException
     */
    public void deleteDepartment(String id) throws BusinessException;


    public List getDepartmentTree(int hierarchy, Department department);


    public List getDepartmentsByPlanId(String planId);

    /**
     * �õ����ŵ�xml��
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
     * ͨ���༶��Ϣ�ҵ����е�У��
     *
     * @return .
     */
    public List findAreaFromDepartment(String pid);

    public List findAreaFromDepartment();

    /**
     * �ҵ�Ժϵ
     *
     * @return .
     */
    public List findFaculty();

    /**
     * ����У�������Ժϵ������Ұ༶�����ж�Ȩ��
     *
     * @param areaCode У������
     * @param pid  Ժϵ����ĸ��ڵ�
     * @return .
     */
    public List findDepartment(String areaCode, String pid);

    /**
     * ����У�������Ժϵ������Ұ༶���ж�Ȩ��
     *
     * @param areaCode У������
     * @param pid  Ժϵ����ĸ��ڵ�
     * @param account  ��ǰ��¼�˻�
     * @return .
     */
    public List findDepartment(String areaCode, String pid, Account account);

    /**
     * ����У�����룬Ժϵ���룬�༶������ҿγ̣����ж�Ȩ��
     *
     * @param areaCode У������
     * @param pid  Ժϵ����ĸ��ڵ�
     * @param deptId   �༶����
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId);

    public List findAllCourse();
    /**
     * ����У�����룬Ժϵ���룬�༶������ҿγ̣��ж�Ȩ��
     *
     * @param areaCode У������
     * @param pid  Ժϵ����ĸ��ڵ�
     * @param deptId   �༶����
     * @param account  ��ǰ��¼�˻�
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId, Account account);

    /**
     * ���û���½ʱ�����ݽ�ɫ���Ҹ��û���Ȩ�޷��ʵİ༶��Ȼ���˻��༶��ϵ����
     *
     * @param account .
     */
    public void refreshOperLimt(final Account account);
}