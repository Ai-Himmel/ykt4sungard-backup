/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CollegeWithLeader.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-27     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

import org.king.classmanage.domain.Collegemodel;

public class CollegeWithLeader extends Collegemodel {
	public String managerId;
	public String managerName;

	/**
	 * @return Returns the managerName.
	 */
	public String getManagerName() {
		return managerName;
	}

	/**
	 * @param managerName The managerName to set.
	 */
	public void setManagerName(String managerName) {
		this.managerName = managerName;
	}

	/**
	 * @return Returns the managerId.
	 */
	public String getManagerId() {
		return managerId;
	}

	/**
	 * @param managerId The managerId to set.
	 */
	public void setManagerId(String managerId) {
		this.managerId = managerId;
	}

}
