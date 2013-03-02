/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.service.impl.DepartmentServiceImpl.java
 * 创建日期： 2006-6-16 13:14:39
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-16 13:14:39      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 *
 */
package org.king.check.service.impl;

import org.apache.commons.beanutils.BeanComparator;
import org.apache.commons.collections.ComparatorUtils;
import org.apache.commons.collections.comparators.ComparableComparator;
import org.apache.commons.collections.comparators.ComparatorChain;
import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.DynaActionForm;
import org.king.check.Constants;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.common.query.QueryTranslate;
import org.king.check.dao.DepartmentDAO;
import org.king.check.dao.DepartmentTempDAO;
import org.king.check.domain.Department;
import org.king.check.domain.DepartmentTemp;
import org.king.check.domain.Toperlimit;
import org.king.check.domain.ToperlimitId;
import org.king.check.exception.DepartmentAlreadyExistException;
import org.king.check.service.DepartmentService;
import org.king.framework.exception.BusinessException;
import org.king.security.dao.AccountDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Role;
import org.king.security.util.ConvertXmlUtil;
import org.springframework.jdbc.core.JdbcTemplate;

import java.io.Serializable;
import java.util.*;

/**
 * <p> DepartmentServiceImpl.java </p>
 * <p> {功能说明} </p>
 * <p/>
 * <p><a href="DepartmentServiceImpl.java.html"><i>查看源代码</i></a></p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-16
 */


public class DepartmentServiceImpl implements DepartmentService {

    private static final Log logger = LogFactory.getLog(DepartmentServiceImpl.class);

    private DepartmentDAO departmentDAO;

    private JdbcTemplate jdbcTemplate;

    private DepartmentTempDAO departmentTempDAO;

    private AccountDAO accountDAO;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void setDepartmentTempDAO(DepartmentTempDAO departmentTempDAO) {
        this.departmentTempDAO = departmentTempDAO;
    }

    public void setDepartmentDAO(DepartmentDAO departmentDAO) {
        this.departmentDAO = departmentDAO;
    }

    public void setAccountDAO(AccountDAO accountDAO) {
        this.accountDAO = accountDAO;
    }

    public List findallGard() {
        List gard = new ArrayList();
        StringBuffer query = new StringBuffer("");
        //is there anyone can tell me why gjf use the conditon where d.id in ('1','2')
        query.append(" select distinct new Map(d.id as id , d.name as name ,d.parent.id as parentId  ) from  Department d where d.id in ('1','2')")
                .append(" order by d.name  desc ");

        gard = departmentDAO.find(query.toString());
        if (gard != null) {
            return gard;
        } else {
            return new ArrayList();
        }
    }

    public List findAllsubDeptment() {
        List result = new ArrayList();
        StringBuffer query = new StringBuffer(1024);
        query.append(" select t2.classno classno ,t4.short_name classname ,t3.dept_id gardno ,t3.short_name  gardname ")
                .append(" from ykt_ck.t_courseplan t1  ")
                .append(" left join ykt_ck.t_courseplanclass t2 on t1.id = t2.planid ")
                .append(" left join ykt_ck.department t3 on t3.dept_id = t1.gardno  ")
                .append(" left join ykt_ck.department t4 on t4.dept_id = t2.classno ")
                .append(" group by  t2.classno,t4.short_name,t3.dept_id,t3.short_name ");
        List subDeptList = jdbcTemplate.queryForList(query.toString());

        return subDeptList;
    }

    public List getAreaByGard() {

        StringBuffer query = new StringBuffer(1024);
        query.append(" select t1.gardno,t2.schoolarea,t3.areaname   ")
                .append(" from ykt_ck.t_courseplan t1 ,ykt_ck.t_room t2 ,ykt_cur.t_area t3 ")
                .append(" where t1.roomid = t2.roomid and t2.schoolarea = t3.areacode  ")
                .append(" group by t1.gardno,t2.schoolarea,t3.areaname ");
        List areaList = jdbcTemplate.queryForList(query.toString());
        return areaList;

    }

    public List getClassByArea() {
        StringBuffer query = new StringBuffer(1024);
        query.append(" select t2.schoolarea,t3.classno,t4.short_name classname  ")
                .append(" from ykt_ck.t_courseplan t1 ,ykt_ck.t_room t2 ,ykt_ck.t_courseplanclass t3,ykt_ck.department t4")
                .append(" where t1.roomid = t2.roomid and t1.id = t3.planid and t3.classno = t4.dept_id ")
                .append(" group by t2.schoolarea,t3.classno,t4.short_name order by t4.short_name desc");
        List classList = jdbcTemplate.queryForList(query.toString());
        return classList;
    }

    /**
     * 根据登陆账户部门权限查找班级
     *
     * @param accountId .
     * @return .
     */
    public List getClassByArea(String accountId) {
        StringBuffer query = new StringBuffer("select r.schoolarea, cpc.classno, d.short_name classname");
        query.append(" from ykt_ck.t_courseplan cp,ykt_ck.t_room r,ykt_ck.t_courseplanclass cpc,ykt_ck.department d,ykt_ck.t_oper_limit ol");
        query.append(" where cp.roomid = r.roomid and cp.id = cpc.planid and cpc.classno = d.dept_id and ol.dept_id = cpc.classno and ol.oper_id = '").append(accountId).append("'");
        query.append(" group by r.schoolarea, cpc.classno, d.short_name order by d.short_name desc");
        List classList = jdbcTemplate.queryForList(query.toString());
        return classList;
    }

    public Department getDepartmentByName(String name) {
        StringBuffer query = new StringBuffer(1024);
        query.append("  from Department d where d.name ='").append(name).append("'");
        List list = departmentDAO.find(query.toString());
        if (list != null && list.size() > 0) {
            return (Department) list.get(0);
        }
        return null;
    }

    public List findAllDepartments() {
        String hql = "from Department d where d.parent is not null order by d.name desc";
        return departmentDAO.find(hql);
    }


    public List findDept(String id) {
        StringBuffer query = new StringBuffer("from  Department d ");
        if (StringUtils.isNotEmpty(id)) {
            query.append(" where  d.id ='").append(id).append("'");
        }
        return departmentDAO.find(query.toString());

    }

    /* (non-Javadoc)
      * @see org.king.check.service.DepartmentService#findAll()
      */

    public List findAll() {
        return departmentDAO.getAll();
    }

    /* (non-Javadoc)
      * @see org.king.check.service.DepartmentService#getDepartment(java.io.Serializable)
      */

    public Department getDepartment(Serializable id) {
        return departmentDAO.get(id);
    }

    /* (non-Javadoc)
      * @see org.king.check.service.DepartmentService#saveDepartment(org.king.check.domain.Department)
      */

    public void saveDepartment(Department department) throws BusinessException,
            DepartmentAlreadyExistException {

        departmentDAO.save(department);

    }

    /* (non-Javadoc)
      * @see org.king.check.service.DepartmentService#updateDepartment(org.king.check.domain.Department)
      */

    public void updateDepartment(Department department)
            throws BusinessException {

        Department entity = getDepartment(department.getId());
        entity.setName(department.getName());
        departmentDAO.update(entity);

    }

    /* (non-Javadoc)
      * @see org.king.check.service.DepartmentService#deleteDepartment(java.lang.String)
      */

    public void deleteDepartment(String id) throws BusinessException {
        departmentDAO.delete(getDepartment(id));
    }

    /* (non-Javadoc)
      * @see org.king.check.service.DepartmentService#getDepartmentsByParantId(java.lang.String)
      */

    public List getDepartmentsByPlanId(String planId) {
        String hql = "select d from Department d,TCourseplan t,TCourseplanclass cpc where t.id=cpc.id.planid and t.id='" + planId + "' and d.id=cpc.id.classno";
        return departmentDAO.find(hql);
    }

    public List getDeptTree() {
        String sql = "select t.deptcode,t.deptname,t.deptlevel,t.fdeptcode from ykt_cur.t_dept t start with t.fdeptcode='1' connect by t.fdeptcode=prior deptcode order siblings by t.deptname";
        List result = jdbcTemplate.queryForList(sql);
        if (result != null && result.size() > 0) {
            for (int i = 0; i < result.size(); i++) {
                Map row = (Map) result.get(i);
                String title = "";
                int j = 0;
                int deptlevel = Integer.parseInt(row.get("deptlevel").toString());
                while (j < deptlevel) {
                    title += "\u2502";
                    j++;
                }
                if (i == (result.size() - 1)) {
                    title += "\u2514";
                } else {
                    title += "\u251c";
                }
                //判断是否有子节点
                if (i < result.size() - 1 && row.get("deptcode").equals(((Map) result.get(i)).get("fdeptcode"))) {
                    title += ("[" + row.get("deptname").toString() + "]");
                } else {
                    title += row.get("deptname").toString();
                }
                row.put("deptTitle", title);
            }
        }
        return result;
    }

    /**
     * 查找班级
     *
     * @param createYear 创建年份
     * @param pid        院系代码的父节点
     * @param areaCode   校区代码
     * @return .
     */
    public List findDepartments(String createYear, String pid, String areaCode) {
        if (StringUtils.isBlank(createYear)) {
            return new ArrayList();
        }
        StringBuffer query = new StringBuffer("select d.dept_id as deptId,d.short_name as deptName,d.faculty as faculty,a.areaname as areaName,d.create_year as createYear from ykt_ck.department d");
        query.append(" left join ykt_cur.t_area a on d.area_code=a.areacode left join ykt_ck.department_temp dt on d.dept_id=dt.dept_id inner join ykt_ck.t_faculty f on d.faculty = f.value");
        query.append(" where dt.dept_id is null");
        if (StringUtils.isNotBlank(pid)) {
            query.append(" and f.pid='").append(pid).append("'");
        }
        if (StringUtils.isNotBlank(createYear)) {
            query.append(" and d.create_year='").append(createYear).append("'");
        }
        if (StringUtils.isNotBlank(areaCode)) {
            query.append(" and d.area_code='").append(areaCode).append("'");
        }
        query.append(" order by d.area_code,d.faculty,d.short_name");
        return jdbcTemplate.queryForList(query.toString());
    }

    public List getDepartmentTree(int hierarchy, Department department) {
        List tempTree = new ArrayList();
        createTree(hierarchy, department, tempTree);

        return tempTree;

    }

    /**
     * 创建树
     *
     * @param hierarchy
     * @param department
     * @param tempTree
     */
    private void createTree(int hierarchy, Department department, List tempTree) {
        Department adepartment;
        Department[] it = null;

        if (department == null) {
            List deparments = departmentDAO.find("from Department department where department.parent is null");

            if (deparments != null) {
                it = new Department[deparments.size()];
                it = (Department[]) deparments.toArray(it);
            }

            if (it == null) {
                return;
            }
        } else {
            /*it = new Department[department.getChildren().size()];
            System.arraycopy(department.getChildren().toArray(), 0, it, 0, department
                    .getChildren().size());*/
        }

        for (int i = 0, n = it.length; i < n; i++) {
            adepartment = it[i];

            int k = 0;
            String catalogtitle = "";
            Map catalog2 = new HashMap();

            while (k < hierarchy) {
                //|
                catalogtitle += "\u2502";
                k++;
            }

            if (i == (n - 1)) {
                //|-
                catalogtitle += "\u2514";
            } else {
                //|_
                catalogtitle += "\u251c";
            }

            /*if (adepartment.getChildren().size() > 0) {
                catalogtitle += ("[" + adepartment.getName() + "]");
            } else {
                catalogtitle += adepartment.getName();
            }*/

            catalog2.put("deptId", adepartment.getId());
            catalog2.put("deptTitle", catalogtitle);
            tempTree.add(catalog2);

            /*if (adepartment.getChildren().size() > 0) {
                //call self
                createTree(hierarchy + 1, adepartment, tempTree);
            }*/
        }
    }

    public void createDepartment(Department department, Serializable parentid) throws BusinessException {
        if ((parentid != null) && !((String) parentid).trim().equals("")) {
            Department parent = departmentDAO.get(parentid);
//            department.setParent(parent);
//            parent.getChildren().add(department);
        }
        departmentDAO.save(department);


    }

    public String getDepartmentXmlTree(String accountId) {
        String sql;
        if (StringUtils.isNotBlank(accountId)) {
            sql = "select t.dept_id, t.short_name, t.dept_parentid, t1.oper_id from ykt_ck.department t left join (select o.* from ykt_ck.t_oper_limit o where o.oper_id = '"
                    + accountId
                    + "') t1 on t.dept_id = t1.dept_id start with t.dept_parentid is null connect by t.dept_parentid = prior t.dept_id order siblings by t.dept_name desc";
        } else {
            sql = "select t.dept_id,t.short_name,t.dept_parentid from ykt_ck.department t start with t.dept_parentid is null connect by t.dept_parentid=prior dept_id order siblings by t.short_name desc";
        }
        List result = jdbcTemplate.queryForList(sql);
        return ConvertXmlUtil.generateDepartmentTreeXml(result);
    }

    /**
     * find all the departments except the root department
     *
     * @return
     * @author Yiming.You
     */
    public void findDepartmentsByPage(DynaActionForm dform, DBPageLimit page) {
        String hql = "select d.id as id,d.name as name,d.areaCode as areaCode,a.areaName as areaName,d.createYear as createYear,d.faculty as faculty,f.pname as facultyName from Department d,TArea a,TFaculty f";
        hql += " where a.areaCode=d.areaCode and f.value=d.faculty";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNo() - 1) * page.getPageSize());
        queryTranslate.setPageSize(page.getPageSize());
        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            queryTranslate.addEqualCondition("d.areaCode", dform.get("schoolarea"));
        }
        if (StringUtils.isNotBlank((String) dform.get("pid"))) {
            queryTranslate.addEqualCondition("f.pid", dform.get("pid"));
        }
        if (StringUtils.isNotBlank((String) dform.get("departmentName"))) {
            queryTranslate.addLikeCondition("d.name", dform.get("departmentName"));
        }
        if (StringUtils.isNotBlank((String) dform.get("classno"))) {
            queryTranslate.addEqualCondition("d.id", dform.get("classno"));
        }
        if (StringUtils.isNotBlank((String) dform.get("createYear"))) {
            queryTranslate.addEqualCondition("d.createYear", dform.get("createYear"));
        }

        queryTranslate.setOrderby(" order by d.createYear desc,d.areaCode,d.faculty,d.name desc");
        page.setMap(true);
        departmentDAO.findDepartmentsByPage(page, queryTranslate);
    }

    /**
     * 将要删除的班级信息存储到临时表中
     *
     * @param deptIds .
     */
    public Long deleteDepartments(String[] deptIds) {
        if (deptIds == null || deptIds.length == 0) {
            return null;
        }
        Long deleteTime = Long.valueOf(System.currentTimeMillis());
        for (int i = 0; i < deptIds.length; i++) {
            if (StringUtils.isNotBlank(deptIds[i])) {
                DepartmentTemp departmentTemp = new DepartmentTemp();
                departmentTemp.setId(deptIds[i]);
                departmentTemp.setDeleteTime(deleteTime);
                departmentTempDAO.save(departmentTemp);
            }
        }
        return deleteTime;
    }

    /**
     * 通过班级信息找到所有的校区
     *
     * @return .
     */
    public List findAreaFromDepartment(String pid) {
        String query = "select distinct a.areacode as areaCode, a.areaname as areaName from ykt_ck.department d, ykt_cur.t_area a, ykt_ck.t_faculty f where d.area_code = a.areacode and f.value = d.faculty and f.pid = '" + pid + "'";
        return jdbcTemplate.queryForList(query);
    }

    public List findAreaFromDepartment() {
        String query = "select distinct a.areacode as areaCode, a.areaname as areaName from ykt_ck.department d, ykt_cur.t_area a where d.area_code = a.areacode";
        return jdbcTemplate.queryForList(query);
    }

    /**
     * 查找所有的院系
     *
     * @return .
     */
    public List findFaculty() {
        String query = "select f.id,f.name from ykt_ck.t_faculty f where f.pid='001'";
        return jdbcTemplate.queryForList(query);
    }

    /**
     * 根据校区代码和院系代码查找班级，不判断权限
     *
     * @param areaCode 校区代码
     * @param pid      院系代码父节点
     * @return .
     */
    public List findDepartment(String areaCode, String pid) {
        StringBuffer query = new StringBuffer("select d.dept_id as deptId,d.short_name as deptName from ykt_ck.department d,ykt_ck.t_faculty f where d.faculty=f.value and d.area_code is not null");
        if (StringUtils.isNotBlank(pid)) {
            query.append(" and f.pid='").append(pid).append("'");
        }
        if (StringUtils.isNotBlank(areaCode)) {
            query.append(" and d.area_code='").append(areaCode).append("'");
        }

        List departments = jdbcTemplate.queryForList(query.toString());
        //排序
        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("DEPTNAME", comparator));
        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(departments, multiSort);
        return departments;
    }

    /**
     * 根据校区代码和院系代码查找班级，判断权限
     *
     * @param areaCode 校区代码
     * @param pid      院系代码父节点
     * @param account  当前登录账户
     * @return .
     */
    public List findDepartment(String areaCode, String pid, Account account) {
        List departments = new ArrayList();
        Set roles = account.getRoles();
        Integer custid = account.getCustId();
        if (roles == null || roles.size() == 0) {
            return departments;
        }
        Map result = new HashMap();
        for (Iterator iterator = roles.iterator(); iterator.hasNext();) {
            Role role = (Role) iterator.next();
            combineDepartment(findDepartmentByRole(areaCode, pid, role, custid), result);
        }
        //将map转换成List<Map>
        Set set = result.entrySet();
        for (Iterator iterator = set.iterator(); iterator.hasNext();) {
            Map.Entry entry = (Map.Entry) iterator.next();
            Map row = new HashMap();
            row.put("DEPTID", entry.getKey());
            row.put("DEPTNAME", entry.getValue());
            departments.add(row);
        }

        //排序
        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("DEPTNAME", comparator));
        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(departments, multiSort);
        return departments;
    }

    /**
     * 将班级列表存入map中，以合并不同角色能查看的班级信息
     *
     * @param sub    .
     * @param result .
     */
    private void combineDepartment(List sub, Map result) {
        if (sub == null || sub.size() == 0) {
            return;
        }
        for (int i = 0; i < sub.size(); i++) {
            Map row = (Map) sub.get(i);
            String deptId = (String) row.get("DEPTID");
            String deptName = (String) row.get("DEPTNAME");
            if (!result.containsKey(deptId)) {
                result.put(deptId, deptName);
            }
        }
    }

    /**
     * 根据角色类型查找班级信息
     *
     * @param areaCode 校区代码
     * @param pid      院系代码父节点
     * @param role     角色
     * @param custid   客户ID
     * @return .
     */
    private List findDepartmentByRole(String areaCode, String pid, Role role, Integer custid) {
        StringBuffer query = new StringBuffer("select d.dept_id as deptId,d.short_name as deptName from ykt_ck.department d,ykt_ck.t_faculty f where d.faculty=f.value and d.area_code is not null");

        //当角色类型为 ROLE_TYPE_AREA_ADMIN 时，attribute里存放的是校区代码，当角色类型为 ROLE_TYPE_FACULTY_ADMIN，attribute里存放的是学院代码
        String attribute = role.getRemark();
        if (Constants.ROLE_TYPE_SYS_ADMIN.equals(role.getType())) {
            //获取系统管理员所有权限查看的班级，系统管理员可以查看所有的班级，所以此处不加限制条件

        } else if (Constants.ROLE_TYPE_AREA_ADMIN.equals(role.getType())) {
            //获取校区管理员有权限查看的班级
            query.append(" and d.area_code='").append(attribute).append("'");

        } else if (Constants.ROLE_TYPE_FACULTY_ADMIN.equals(role.getType())) {
            //获取院系管理员有权限查看的班级
            query.append(" and d.faculty='").append(attribute).append("'");

        } else if (Constants.ROLE_TYPE_ASSISTANT.equals(role.getType())) {
            //获取辅导员有权限查看的班级
            query = new StringBuffer("select distinct d.dept_id as deptId,d.short_name as deptName from ykt_ck.department d,ykt_ck.t_teacher_class tc,ykt_ck.t_faculty f where d.dept_id=tc.dept_id and f.value=d.faculty");
            query.append(" and tc.custid=").append(custid);

        } else if (Constants.ROLE_TYPE_TEACHER.equals(role.getType())) {
            //获取任课老师有权限查看的班级
            query = new StringBuffer("select distinct d.dept_id as deptId,d.short_name as deptName from ykt_ck.department d,ykt_ck.t_courseplan cp,ykt_ck.t_courseplanclass cpc,ykt_ck.t_faculty f where cp.id=cpc.planid and d.dept_id=cpc.classno and f.value=d.faculty");
            query.append(" and cp.custid=").append(custid);
        } else if (Constants.ROLE_TYPE_NORMAL.equals(role.getType())) {
            //todo 获取一般角色有权限查看的班级
            return new ArrayList();
        }
        if (StringUtils.isNotBlank(areaCode)) {
            query.append(" and d.area_code='").append(areaCode).append("'");
        }
        if (StringUtils.isNotBlank(pid)) {
            query.append(" and f.pid='").append(pid).append("'");
        }
        return jdbcTemplate.queryForList(query.toString());
    }

    /**
     * 根据校区代码，院系代码，班级代码查找课程，不判断权限
     *
     * @param areaCode 校区代码
     * @param pid      院系代码父节点
     * @param deptId   班级代码
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId) {
        if(StringUtils.isBlank(deptId)){
            return findAllCourse();
        }
        StringBuffer query = new StringBuffer("select distinct c.courseid, c.coursename");
        query.append(" from ykt_ck.department d,ykt_ck.t_courseplan cp,ykt_ck.t_courseplanclass cpc,ykt_ck.t_course c,ykt_ck.t_faculty f");
        query.append(" where cpc.planid = cp.id and cpc.classno = d.dept_id and c.courseid = cp.courseid and f.value=d.faculty");
        if (StringUtils.isNotBlank(areaCode)) {
            query.append(" and d.area_code='").append(areaCode).append("'");
        }
        if (StringUtils.isNotBlank(pid)) {
            query.append(" and f.pid='").append(pid).append("'");
        }
        if (StringUtils.isNotBlank(deptId)) {
            query.append(" and d.dept_id='").append(deptId).append("'");
        }
        List courses = jdbcTemplate.queryForList(query.toString());
        //排序
        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("COURSENAME", comparator));
        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(courses, multiSort);
        return courses;
    }

    public List findAllCourse() {
        StringBuffer query = new StringBuffer("select distinct c.courseid COURSEID,c.coursename COURSENAME from ykt_ck.t_course c order by c.coursename");
        List courses = jdbcTemplate.queryForList(query.toString());
        return courses;
    }

    /**
     * 根据校区代码，院系代码，班级代码查找课程，判断权限
     *
     * @param areaCode 校区代码
     * @param pid      院系代码父节点
     * @param deptId   班级代码
     * @param account  当前登录账户
     * @return .
     */
    public List findCourse(String areaCode, String pid, String deptId, Account account) {
        List courses = new ArrayList();
        if(StringUtils.isBlank(deptId)){
            courses = findAllCourse();
            return courses;
        }

        Set roles = account.getRoles();
        Integer custid = account.getCustId();
        if (roles == null || roles.size() == 0) {
            return courses;
        }
        Map result = new HashMap();
        for (Iterator iterator = roles.iterator(); iterator.hasNext();) {
            Role role = (Role) iterator.next();
            combineCourse(findCourseByRole(areaCode, pid, deptId, role, custid), result);
        }
        //将map转换成List<Map>
        Set set = result.entrySet();
        for (Iterator iterator = set.iterator(); iterator.hasNext();) {
            Map.Entry entry = (Map.Entry) iterator.next();
            Map row = new HashMap();
            row.put("COURSEID", entry.getKey());
            row.put("COURSENAME", entry.getValue());
            courses.add(row);
        }

        //排序
        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("COURSENAME", comparator));
        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(courses, multiSort);
        return courses;
    }

    /**
     * 将班级列表存入map中，以合并不同角色能查看的班级信息
     *
     * @param sub    .
     * @param result .
     */
    private void combineCourse(List sub, Map result) {
        if (sub == null || sub.size() == 0) {
            return;
        }
        for (int i = 0; i < sub.size(); i++) {
            Map row = (Map) sub.get(i);
            String courseId = (String) row.get("COURSEID");
            String courseName = (String) row.get("COURSENAME");
            if (!result.containsKey(courseId)) {
                result.put(courseId, courseName);
            }
        }
    }

    /**
     * 根据角色查找课程
     *
     * @param areaCode 校区代码
     * @param pid      院系代码
     * @param role     角色
     * @param custid   客户ID
     * @return .
     */
    private List findCourseByRole(String areaCode, String pid, String deptId, Role role, Integer custid) {
        StringBuffer query = new StringBuffer("select distinct c.courseid, c.coursename");
        query.append(" from ykt_ck.department d,ykt_ck.t_courseplan cp,ykt_ck.t_courseplanclass cpc,ykt_ck.t_course c,ykt_ck.t_faculty f");
        query.append(" where cpc.planid = cp.id and cpc.classno = d.dept_id and c.courseid = cp.courseid and f.value=d.faculty");

        //当角色类型为 ROLE_TYPE_AREA_ADMIN 时，attribute里存放的是校区代码，当角色类型为 ROLE_TYPE_FACULTY_ADMIN，attribute里存放的是学院代码
        String attribute = role.getRemark();
        if (Constants.ROLE_TYPE_SYS_ADMIN.equals(role.getType())) {
            //获取系统管理员所有权限查看的班级，系统管理员可以查看所有的班级，所以此处不加限制条件

        } else if (Constants.ROLE_TYPE_AREA_ADMIN.equals(role.getType())) {
            //获取校区管理员有权限查看的班级
            query.append(" and d.area_code='").append(attribute).append("'");

        } else if (Constants.ROLE_TYPE_FACULTY_ADMIN.equals(role.getType())) {
            //获取院系管理员有权限查看的班级
            query.append(" and d.faculty='").append(attribute).append("'");

        } else if (Constants.ROLE_TYPE_ASSISTANT.equals(role.getType())) {
            //获取辅导员有权限查看的班级
            query = new StringBuffer("select distinct c.courseid, c.coursename");
            query.append(" from ykt_ck.department d,ykt_ck.t_courseplan cp,ykt_ck.t_courseplanclass cpc,ykt_ck.t_course c,ykt_ck.t_teacher_class tc,ykt_ck.t_faculty f");
            query.append(" where cpc.planid = cp.id and cpc.classno = d.dept_id and c.courseid = cp.courseid and d.dept_id=tc.dept_id and f.value=d.faculty");
            query.append(" and tc.custid=").append(custid);

        } else if (Constants.ROLE_TYPE_TEACHER.equals(role.getType())) {
            //获取任课老师有权限查看的班级
            query.append(" and cp.custid=").append(custid);
        } else if (Constants.ROLE_TYPE_NORMAL.equals(role.getType())) {
            //todo 获取一般角色有权限查看的班级
            return new ArrayList();
        }
        if (StringUtils.isNotBlank(areaCode)) {
            query.append(" and d.area_code='").append(areaCode).append("'");
        }
        if (StringUtils.isNotBlank(pid)) {
            query.append(" and f.pid='").append(pid).append("'");
        }
        if (StringUtils.isNotBlank(deptId)) {
            query.append(" and d.dept_id='").append(deptId).append("'");
        }
        return jdbcTemplate.queryForList(query.toString());
    }

    /**
     * 在用户登陆时，根据角色查找该用户有权限访问的班级，然后将账户班级关系更新
     *
     * @param account .
     */
    public void refreshOperLimt(final Account account) {
        DepartmentServiceImpl.logger.debug("开始更新用户班级权限");
        //先取出数据库中已存在的账户班级关系
        List limitList = accountDAO.getAccountLimit(account.getCustId().toString());
        if (limitList == null) {
            limitList = new ArrayList();
        }
        //然后根据角色找到该角色有权限访问的所有班级
        Set<String> departments = new HashSet<String>();
        Set roles = account.getRoles();
        Integer custid = account.getCustId();
        //是否具有任课老师权限
        boolean isTeacher = false;
        for (Iterator iterator = roles.iterator(); iterator.hasNext();) {
            Role role = (Role) iterator.next();
            //任课老师权限单独处理
            if (Constants.ROLE_TYPE_TEACHER.equals(role.getType())) {
                //当角色是任课老师时，资源ID不在是班级，而是任课老师的CUSTID
                isTeacher = true;
            } else {
                List sub = findDepartmentByRole("", "", role, custid);
                for (int i = 0; i < sub.size(); i++) {
                    Map row = (Map) sub.get(i);
                    departments.add((String) row.get("DEPTID"));
                }
            }
        }

        //在删除已经不存在的账户班级关系
        Toperlimit teacherLimit = null;
        for (int i = 0; i < limitList.size(); i++) {
            Toperlimit toperlimit = (Toperlimit) limitList.get(i);
            if (Constants.ROLE_TYPE_TEACHER.equals(toperlimit.getType())) {
                //暂存任课老师权限
                teacherLimit = toperlimit;
            } else {
                if (departments.contains(toperlimit.getId().getResourceId())) {
                    departments.remove(toperlimit.getId().getResourceId());
                } else {
                    accountDAO.deleteAccountLimit(toperlimit);
                }
            }
        }
        //处理任课老师权限
        if (isTeacher && teacherLimit == null) {
            //新增任课老师权限
            Toperlimit operLimit = new Toperlimit();
            ToperlimitId operLimitId = new ToperlimitId();
            operLimitId.setResourceId(account.getCustId() + "");
            operLimitId.setOperId(custid + "");
            operLimit.setId(operLimitId);
            operLimit.setType(Constants.ROLE_TYPE_TEACHER);
            accountDAO.saveAccountLimit(operLimit);
        } else if (!isTeacher && teacherLimit != null) {
            //删除任课老师权限
            accountDAO.deleteAccountLimit(teacherLimit);
        }

        //增加新的账户班级关系
        for (String deptId : departments) {
            Toperlimit operLimit = new Toperlimit();
            ToperlimitId operLimitId = new ToperlimitId();
            operLimitId.setResourceId(deptId);
            operLimitId.setOperId(custid + "");
            operLimit.setId(operLimitId);
            accountDAO.saveAccountLimit(operLimit);
        }
        DepartmentServiceImpl.logger.debug("成功更新用户班级权限");
    }
}
