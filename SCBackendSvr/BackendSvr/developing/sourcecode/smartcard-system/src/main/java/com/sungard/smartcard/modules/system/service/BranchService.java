package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Branch;
import com.sungard.smartcard.exception.FunctionException;

/**
 * 网点维护业务
 * @author HongYi.Wang
 */
public interface BranchService {
	/*
	 * 新增网点
	 * @param Branch
	 */
	public void addNewBranch(Branch b) throws FunctionException;
	
	/*
	 * 修改网点
	 * @param Branch
	 */
	public void modifyBranch(Branch b) throws FunctionException;
	
	/*
	 * 删除站点
	 * @param Branch
	 */
	public void delBranch(Branch b) throws FunctionException;
	
	/*
	 * 查询网点
	 */
	public List<Branch> queryBranch(Branch b) throws FunctionException;
	
}
