package com.sungard.smartcard.modules.system.function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Branch;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.BranchService;
import com.sungard.smartcard.modules.system.service.SiteService;

@SmartCardFunction(infotype = 3, funcnum = 10001100, name = "网点管理")
public class BranchFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(BranchFunction.class);
	
	@Autowired
	private BranchService branchService;
	public void setBranchService(BranchService branchService) {
		this.branchService = branchService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Branch b = getParameter(Branch.class, session);
		logger.info("----------------添加网点---------------------");
		branchService.addNewBranch(b);
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		logger.info("----------------删除网点---------------------");
		Branch b = getParameter(Branch.class, session);
		branchService.delBranch(b);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		logger.info("----------------查询网点---------------------");
		Branch b = getParameter(Branch.class, session);
		outPack(branchService.queryBranch(b),Branch.class,session);
	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		logger.info("----------------更新网点---------------------");
		Branch b = getParameter(Branch.class, session);
		branchService.modifyBranch(b);
	}
	
}
