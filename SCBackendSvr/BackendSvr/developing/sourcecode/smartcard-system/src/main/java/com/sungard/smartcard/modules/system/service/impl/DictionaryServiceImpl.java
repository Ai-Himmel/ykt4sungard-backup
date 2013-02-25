package com.sungard.smartcard.modules.system.service.impl;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.CollectionUtils;

import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Dictionary;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.DictionaryDao;
import com.sungard.smartcard.modules.system.service.DictionaryService;

/**
 * [TODO 数据字典维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
@Service
@Transactional
public class DictionaryServiceImpl implements DictionaryService {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory
	.getLogger(DictionaryServiceImpl.class);
	
	@Autowired
	@Qualifier("dictionaryDaoImpl")
	private DictionaryDao dictionaryDao;
	

	public void setDictionaryDao(DictionaryDao dictionaryDao) {
		this.dictionaryDao = dictionaryDao;
	}

	@Override
	public List<Dictionary> queryAll() {
//		return dictionaryDao.findDictionarys();
		return dictionaryDao.findDomains();
	}
	
	private boolean checkPramary(Dictionary dictionary) throws FunctionException{
		if (dictionary == null || dictionary.getDicttype()==null || dictionary.getDicttype() == 0) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "字典类型");
		}
		if (StringUtils.isBlank(dictionary.getDictval())) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "字字典值");
		}
		return true;
	}
	
	private int successRows(int rows) throws FunctionException{
		if(rows==0){
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "数据字典表");
		}
		return rows;
	}

	@Override
	public List<Dictionary> queryByParam(Dictionary dictionary) {
//		StringBuffer sql = new StringBuffer(
//				"select dicttype, dicttypename, dictval, dictcaption from t_dictionary where 1=1");
//		List<Object> param = new ArrayList<Object>();
//		if (dictionary.getDicttype()>0) {
//			sql.append(" and dicttype = ?");
//			param.add(dictionary.getDicttype());
//		}
//		if (StringUtils.isNotBlank(dictionary.getDicttypename())) {
//			sql.append(" and dicttypename like ?");
//			param.add("%" + dictionary.getDicttypename() + "%");
//		}
//		if (StringUtils.isNotBlank(dictionary.getDictval())) {
//			sql.append(" and dictval = ?");
//			param.add(dictionary.getDictval());
//		}
//		return dictionaryDao.findDictionarys(sql.toString(), param.size()>0?param.toArray():null);
		Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
		if(dictionary!=null){
			if (dictionary.getDicttype()>0) {
				wheres.put("dicttype", dictionary.getDicttype());
			}
			if (StringUtils.isNotBlank(dictionary.getDicttypename())) {
				wheres.put("dicttypename like ?", "%" + dictionary.getDicttypename() + "%");
			}
			if (StringUtils.isNotBlank(dictionary.getDictval())) {
				wheres.put("dictval", dictionary.getDictval());
			}
		}
		return dictionaryDao.findDomains(wheres);
		
	}

	@Override
	public int addDictionary(Dictionary dictionary) throws FunctionException {
//		if(checkPramary(dictionary)&&dictionaryDao.getDictionary(dictionary)!=null){
//			throw new FunctionException(RetCode.IS_EXISTS, "数据字典");
//		}
//		return dictionaryDao.addDictionary(dictionary);
		if(checkPramary(dictionary)){
			Dictionary dictionaryPamaras = new Dictionary();
			dictionaryPamaras.setDicttype(dictionary.getDicttype());
			
			if(CollectionUtils.isEmpty(this.queryByParam(dictionaryPamaras))){
				throw new FunctionException(RetCode.IS_EXISTS, "字典类型");
			}
				
			Map<Object, Object> domain = new LinkedHashMap<Object, Object>();
			domain.put("dicttype", dictionary.getDicttype());
			domain.put("dicttypename", dictionary.getDicttypename());
			domain.put("dictval", dictionary.getDictval());
			domain.put("dictcaption", dictionary.getDictcaption());
			return dictionaryDao.addDomain(domain);
		}else{
			return -1;
		}
	}

	@Override
	public int updateDictionary(Dictionary dictionary) throws FunctionException {
		if(checkPramary(dictionary)){
//			Dictionary dbDictionary = dictionaryDao.getDictionary(dictionary);
//			dbDictionary.setDicttypename(dictionary.getDicttypename());
//			dbDictionary.setDictcaption(dictionary.getDictcaption());
			
//			return dictionaryDao.updateDictionary(dbDictionary);
			
			Map<Object, Object> domain = new LinkedHashMap<Object, Object>();
			domain.put("dicttypename", dictionary.getDicttypename());
			domain.put("dictcaption", dictionary.getDictcaption());
			
			Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
			wheres.put("dicttype", dictionary.getDicttype());
			wheres.put("dictval", dictionary.getDictval());
			return successRows(dictionaryDao.updateDomain(domain, wheres));
		}else{
			return -1;
		}
	}

	@Override
	public int removeDictionary(Dictionary dictionary) throws FunctionException {
		if(checkPramary(dictionary)){
			//return dictionaryDao.removeDictionary(dictionary);
			Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
			wheres.put("dicttype", dictionary.getDicttype());
			wheres.put("dictval", dictionary.getDictval());
			return successRows(dictionaryDao.removeDomain(wheres));
		}else{
			return -1;
		}
	}

	
	
}
