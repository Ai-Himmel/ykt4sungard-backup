package com.sungard.smartcard.modules.system.dao;

import java.util.List;
import com.sungard.smartcard.domain.Dept;
/**
 * 部门数据库操作类接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
public interface DeptDao {
	
	/**
	 * 
	 * 根据code判断是否存在记录
	 **/
	public boolean isExitDept(String deptcode);
	/**
	 * 根据code 和name判断是否重复名称
	 * @param deptcode
	 * @param deptname
	 * @return
	 */
	public boolean isExitDeptName(String deptcode,String deptname);
	/**
	 * 新增保存
	 * @param dept
	 * @return
	 */
	public int addDept(Dept dept);
	/**
	 * 通过code获得dept
	 * @param deptcode
	 * @return
	 */
	public Dept getDept(String deptcode);
	
	/**
	 * 通过fdeptcode 获得最大deptcode
	 * @param fdeptcode
	 * @return
	 */
	public int getDeptcode(String  fdeptcode);
	
	/***
	 * 判断是否是根部门
	 * @param deptcode
	 * @return
	 */
	public boolean isFarDept(String deptcode);
	/**
	 * 判段是否存在下级部门记录
	 * @param fdeptcode
	 * @return
	 */
	public boolean isExistSonDept(String fdeptcode);
	
	/**
	 * 根据deptcode 删除
	 * @param deptcode
	 * @return
	 */
	public int deleDept(String deptcode);
	
	/**
	 * 修改保存部门
	 * @param dept
	 * @return
	 */
	public int updateDept(Dept dept);
	
	/***
	 * 查询
	 * @param dept
	 * @return
	 */
	public List<Dept> allDepts(Dept dept);
	
	public int update(String sql, Object[] args); 
	
}

