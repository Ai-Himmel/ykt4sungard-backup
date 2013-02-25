package com.sungard.smartcard.modules.system.service;

import java.util.List;


import com.sungard.smartcard.domain.Waterrate;
import com.sungard.smartcard.exception.FunctionException;


/**
 * [TODO 数据字典维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */

public interface WaterrateService {
	public List<Waterrate> queryAll();
	public List<Waterrate> queryByParam(Waterrate waterrate);
	public int addWaterrate(Waterrate waterrate) throws FunctionException; 
	public int updateWaterrate(Waterrate waterrate) throws FunctionException;
	public int removeWaterrate(Waterrate waterrate) throws FunctionException;
}
