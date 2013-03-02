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

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.king.check.dao.DepartmentDAO;
import org.king.check.domain.Department;
import org.king.check.exception.DepartmentAlreadyExistException;
import org.king.check.service.DepartmentService;
import org.king.framework.exception.BusinessException;
import org.king.security.util.ConvertXmlUtil;
/**
 * <p> DepartmentServiceImpl.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="DepartmentServiceImpl.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-16
 * 
 *
 */
public class DepartmentServiceImpl implements DepartmentService {

	private DepartmentDAO departmentDAO;
	
	
	public void setDepartmentDAO(DepartmentDAO departmentDAO) {
		this.departmentDAO = departmentDAO;
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
	public List getDepartmentsByParantId(String parantId) {
		// TODO Auto-generated method stub
		return null;
	}

	public List getDepartmentTree(int hierarchy, Department department) {
		List tempTree = new ArrayList();
		createTree(hierarchy, department, tempTree);

		return tempTree;

	}
	
	/**
	 * 创建树
	 * @param hierarchy
	 * @param department
	 * @param tempTree
	 */
	private void createTree(int hierarchy, Department department,List tempTree) {
		Department adepartment;
		Department[] it = null;

		if (department == null) {
			List deparments = departmentDAO.find("from Department department where department.parent is null");
            
			if(deparments!=null){
				it = new Department[deparments.size()];
				it = (Department[])deparments.toArray(it);
			}
			
			if (it == null) {
				return;
			}
		} else {
			it = new Department[department.getChildren().size()];
			System.arraycopy(department.getChildren().toArray(), 0, it, 0, department
					.getChildren().size());
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

			if (adepartment.getChildren().size() > 0) {
				catalogtitle += ("[" + adepartment.getName() + "]");
			} else {
				catalogtitle += adepartment.getName();
			}

			catalog2.put("deptId", adepartment.getId());
			catalog2.put("deptTitle", catalogtitle);
			tempTree.add(catalog2);

			if (adepartment.getChildren().size() > 0) {
				//call self
				createTree(hierarchy + 1, adepartment, tempTree);
			}
		}
	}

	public void createDepartment(Department department, Serializable parentid) throws BusinessException {
		if ((parentid != null) && !((String) parentid).trim().equals("")) {
			Department parent = departmentDAO.get(parentid);
			department.setParent(parent);
			parent.getChildren().add(department);
		}
        departmentDAO.save(department);

		
	}
	
	
	public String getDepartmentXmlTree() {
	
		List depts = departmentDAO.getAll();
		
		Map deptMap = new HashMap();
		List deptList = null;
		
		String rootId = "-1";
	
		//添加第一级子菜单
		deptList = departmentDAO.find("from Department department where department.parent is null");
		deptMap.put(rootId,deptList);
		
		//为每个菜单添加他的子菜单
		for(Iterator i=depts.iterator();i.hasNext();){
			Department dept = (Department)i.next();
			Set subDepts = dept.getChildren();
			List subDeptList = new ArrayList();
			for(Iterator j=subDepts.iterator();j.hasNext();){
				subDeptList.add((Department)j.next());
			}
			deptMap.put(dept.getId(),subDeptList);	
		}
		
		String xmlStr = ConvertXmlUtil.convertToTreeXml(deptMap);
		
		return xmlStr;
	}


}
