package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Branch;
import com.sungard.smartcard.domain.Site;

public interface BranchDao {
	/*
	 * 添加网点数据
	 */
	public void addBranch(Branch b);
	
	/*
	 * 删除网点数据
	 */
	public void delBranch(Branch b);
	
	/*
	 * 更新网点数据
	 */
	public void updateBranch(Branch b);
	
	/*
	 * 查找网点数据
	 */
	public List<Branch> queryBranch(Branch b);
	
	/*
	 * 根据参数获取网点数
	 */
	public int getBranchNumByParam(String branchname,Integer branchno);
}
