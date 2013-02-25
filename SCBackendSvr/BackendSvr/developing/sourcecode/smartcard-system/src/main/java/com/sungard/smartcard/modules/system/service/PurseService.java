package com.sungard.smartcard.modules.system.service;

import java.util.List;


import com.sungard.smartcard.domain.Purse;
import com.sungard.smartcard.exception.FunctionException;


/**
 * [TODO 钱包信息维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */

public interface PurseService {
	public List<Purse> queryAll();
	public List<Purse> queryByParam(Purse purse);
	public int addPurse(Purse purse) throws FunctionException; 
	public int updatePurse(Purse purse) throws FunctionException;
	public int removePurse(Purse purse) throws FunctionException;
}
