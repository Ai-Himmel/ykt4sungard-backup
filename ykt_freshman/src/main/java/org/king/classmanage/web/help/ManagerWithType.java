/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagerWithType.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-29     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

import org.king.classmanage.domain.Managermodel;

public class ManagerWithType extends Managermodel {
	
	public String roleId;
	public String roleName;
	public String getRoleId() {
		return roleId;
	}
	public void setRoleId(String roleId) {
		this.roleId = roleId;
	}
	public String getRoleName() {
		return roleName;
	}
	public void setRoleName(String roleName) {
		this.roleName = roleName;
	}

	public ManagerWithType() {
		super();
		// TODO Auto-generated constructor stub
	}
	public ManagerWithType(String managerNo) {
		super(managerNo);
		// TODO Auto-generated constructor stub
	}
	
	public ManagerWithType(String managerId,String managerNo, String managerName, String gender, String managerOrg, String managerType, String available,String contact, String introduction,String schoolId,String roleId,String roleName) {
		super(managerNo, managerName, gender, managerOrg, managerType, available, contact, introduction,schoolId);
		this.roleId = roleId;
		this.roleName = roleName;
		this.setManagerId(managerId);
	}
}
