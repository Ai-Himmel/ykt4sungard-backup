package com.sungard.smartcard.modules.system.service;

import java.util.List;

import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.domain.Dictionary;
import com.sungard.smartcard.exception.FunctionException;


/**
 * [TODO 数据字典维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */

public interface DictionaryService {
	public List<Dictionary> queryAll();
	public List<Dictionary> queryByParam(Dictionary dictionary);
	public int addDictionary(Dictionary dictionary) throws FunctionException; 
	public int updateDictionary(Dictionary dictionary) throws FunctionException;
	public int removeDictionary(Dictionary dictionary) throws FunctionException;
}
