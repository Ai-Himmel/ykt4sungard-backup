package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Dept;

/**
 * 部门业务处理接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
public interface DeptService {

	//查询返回list
	public List<Dept> allDepts(Dept dept);
		
	//根据code 删除
	public int deleDept(String deptcode);
	
	//修改保存部门
	public int updateDept(Dept dept);
	
	//新增保存
	public int addDept(Dept dept);
	
	//根据code判断是否存在记录
	public boolean isExitDept(String deptcode);
	
	//根据code 和name判断是否重复名称
	public boolean isExitDeptName(String deptcode,String deptname);
	
	//判断是否是根部门
	public boolean isFarDept(String deptcode);
	
	//判段是否存在下级部门记录
	public boolean isExistSonDept(String fdeptcode);

}
