package com.sungard.smartcard.dao;

import java.util.List;
import java.util.Map;

import com.sungard.smartcard.exception.FunctionException;

/**
 * 
 * [TODO 操作实体数据库基础操作类]
 * 
 * @author bo.chen
 * @version v1.00
 * @since 1.00 2012-2-23
 */
public interface BaseDomainDao<T> {
	
	/**
	 * like
	 */
	public static final String LIKE = " like ";
	
	/**
	 * and
	 */
	public static final String AND = " and ";
	
	/**
	 * or
	 */
	public static final String OR = " or ";
	
	/**
	 * where
	 */
	public static final String WHERE = " where ";
	
	/**
	 * 一个空格" "
	 */
	public static final String SPACE = " ";

	public List<T> findDomains();

	public List<T> findDomains(Object[] fields);

	public List<T> findDomains(Map<Object, Object> wheres);

	public List<T> findDomains(Object[] fields, Map<Object, Object> wheres);

	public int updateDomain(Map<Object, Object> fields,
			Map<Object, Object> keys) throws FunctionException;

	public int updateDomain(Map<Object, Object> fields, Integer key)
			throws FunctionException;

	public int updateDomain(Map<Object, Object> fields, String key)
			throws FunctionException;

	public int removeDomain(Map<Object, Object> keys)
			throws FunctionException;

	public int removeDomain(Integer key) throws FunctionException;

	public int removeDomain(String key) throws FunctionException;

	public int addDomain(Map<Object, Object> fields) throws FunctionException;

	public T getDomain(Map<Object, Object> keys) throws FunctionException;

	public T getDomain(Integer key) throws FunctionException;

	public T getDomain(String key) throws FunctionException;

	public T getDomain(Object[] fields, Map<Object, Object> keys)
			throws FunctionException;

	public T getDomain(Object[] fields, Integer key) throws FunctionException;

	public T getDomain(Object[] fields, String key) throws FunctionException;

}
