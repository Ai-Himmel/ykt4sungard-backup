package com.sungard.smartcard.dao.impl;

import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import org.apache.commons.lang.ArrayUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.CollectionUtils;

import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.dao.BaseDomainDao;
import com.sungard.smartcard.exception.FunctionException;

public class BaseDomainDaoImpl<T> implements BaseDomainDao<T> {
	
	private String tableName;
	private String[] fields;
	private Object key;
	private String paramaString;
	
	/* 实体类 */
	protected Class<T> entityClass ;
	
	private static String DOMAIN_QUERY_ALL = "select %s from %s where 1=1 %s";
	private static String DOMAIN_UPDATE_BY_DOMAIN = "update %s set %s where 1=1 %s";
	private static String DOMAIN_DELETE_BY_DOMAIN = "delete %s where 1=1 %s";
	private static String DOMAIN_ADD = "INSERT INTO %s(%s) values(%s)";
	private static String DOMAIN_QUERY_ONE = "select %s where %s";
	
	 @Autowired
	 protected JdbcTemplate jdbcTemplate;

	 public BaseDomainDaoImpl() {
		super();
		Type genType = getClass().getGenericSuperclass();   
		Type[] fields = ((ParameterizedType) genType).getActualTypeArguments();   
		entityClass =  (Class)fields[0]; 
	}

	public void setTableName(String tableName) {
		this.tableName = tableName;
	}


	public void setKey(Object key) {
		this.key = key;
	}

	public void setParamas(String[] fields) {
		this.fields = fields;
		this.paramaString = formatArrays(fields);
	}




	@Override
	public List<T> findDomains() {
		return this.findDomains(null,null);
	}
	
	@Override
	public List<T> findDomains(Object[] fields) {
		return this.findDomains(fields,null);
	}
	
	@Override
	public List<T> findDomains(Map<Object, Object> wheres) {
		return this.findDomains(null,wheres);
	}

	@Override
	public List<T> findDomains(Object[] fields, Map<Object, Object> wheres) {
		StringBuilder paramString2 = new StringBuilder();
		if(!ArrayUtils.isEmpty(fields)){
			paramString2.append(" ").append(formatArrays(fields)).append(" ");
		}
		List<Object> values = new ArrayList<Object>();
		StringBuilder whereString = new StringBuilder();
		if(!CollectionUtils.isEmpty(wheres)){
			Set<Map.Entry<Object, Object>> paramSet = wheres.entrySet();
			for(Entry<Object, Object> entry : paramSet){
				if(!entry.getKey().toString().contains(OR)){
					whereString.append(AND);
				}
				whereString.append(entry.getKey());
				if(entry.getKey().toString().contains(LIKE)){
					whereString.append(SPACE);
				}else{
					whereString.append(" = ? ");
				}
				values.add(entry.getValue());
			}
		}
		return jdbcTemplate.query(String.format(DOMAIN_QUERY_ALL, paramString2.toString().isEmpty()?paramaString:paramString2,tableName,whereString.toString()), values.toArray(),new BeanPropertyRowMapper(entityClass));
//		System.out.println(DOMAIN_QUERY_ALL);
//		
//		System.out.println(paramString2.toString().isEmpty()?paramaString:paramString2);
//		System.out.println(tableName);
//		System.out.println(whereString.toString());
//		
//		System.out.println(String.format(DOMAIN_QUERY_ALL, paramString2.toString().isEmpty()?paramaString:paramString2,tableName,whereString.toString()));
//		System.out.println(Arrays.toString(values.toArray()));
//		System.out.println(entityClass);
//		return null;
	}

	@Override
	public int updateDomain(Map<Object,Object> fields, Map<Object, Object> keys) throws FunctionException {
		return this.updateDomainByWhere(fields, keys);
	}
	
	
	
	@Override
	public int updateDomain(Map<Object, Object> fields, Integer key)
			throws FunctionException {
		return this.updateDomainByWhere(fields, key);
	}

	@Override
	public int updateDomain(Map<Object, Object> fields, String key)
			throws FunctionException {
		return this.updateDomainByWhere(fields, key);
	}


	private int updateDomainByWhere(Map<Object, Object> fields, Object keys)
			throws FunctionException {
		if(CollectionUtils.isEmpty(fields)||keys==null){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
		}
		List<Object> values = new ArrayList<Object>();
		String split = "";
		StringBuilder paramString2 = new StringBuilder();
		Set<Map.Entry<Object, Object>> paramSet = fields.entrySet();
		for(Entry<Object, Object> entry : paramSet){
			paramString2.append(SPACE).append(split).append(entry.getKey()).append(" = ").append(" ? ").append(SPACE);
			split = ",";
			values.add(entry.getValue());
		}
		StringBuilder whereString = new StringBuilder();
		if(keys instanceof Map){
			if(CollectionUtils.isEmpty((Map<Object, Object>) keys)){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
			}
			keys = (Map<Object, Object>)keys;
			split = "";
			Set<Map.Entry<Object, Object>> whereSet = ((Map<Object, Object>) keys).entrySet();
			for(Entry<Object, Object> entry : whereSet){
//				whereString.append(" and ").append(entry.getKey()).append(" = ? ");
//				values.add(entry.getValue());
				if(!entry.getKey().toString().contains(OR)){
					whereString.append(AND);
				}
				whereString.append(entry.getKey());
				if(entry.getKey().toString().contains(LIKE)){
					whereString.append(SPACE);
				}else{
					whereString.append(" = ? ");
				}
				values.add(entry.getValue());
			}
		}else if(keys instanceof Integer || keys instanceof String){
			if(this.key==null){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码(数据库主键)");
			}
			whereString.append(AND).append(this.key);
			if(keys.toString().contains(LIKE)){
				whereString.append(SPACE);
			}else{
				whereString.append(" = ? ");
			}
			
			values.add(keys);
			
		}else{
			throw new FunctionException(RetCode.SYSTEM_PARAM_ERROR, "调用方法参数类型");
		}
		
//		System.out.println(String.format(DOMAIN_UPDATE_BY_DOMAIN,tableName,paramString2,whereString));
//		System.out.println(values.toString());
//		return 0;
		return jdbcTemplate.update(String.format(DOMAIN_UPDATE_BY_DOMAIN,tableName,paramString2,whereString),values.toArray());
	}

	@Override
	public int removeDomain(Map<Object, Object> keys) throws FunctionException {
		return removeDomainByKey(keys);
	}
	
	@Override
	public int removeDomain(Integer key) throws FunctionException {
		return removeDomainByKey(key);
	}

	@Override
	public int removeDomain(String key) throws FunctionException {
		return removeDomainByKey(key);
	}
	
	private int removeDomainByKey(Object keys)  throws FunctionException {
		
		if(keys==null){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
		}
		List<Object> values = new ArrayList<Object>();
		StringBuilder whereString = new StringBuilder();
		if(keys instanceof Map){
			if(CollectionUtils.isEmpty((Map<Object, Object>) keys)){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
			}
			keys  = (Map<Object,Object>)keys;
			Set<Map.Entry<Object, Object>> paramSet = ((Map<Object, Object>) keys).entrySet();
			for(Entry<Object, Object> entry : paramSet){
//				whereString.append(" and ").append(entry.getKey()).append(" = ? ");
//				values.add(entry.getValue());
				if(!entry.getKey().toString().contains(OR)){
					whereString.append(AND);
				}
				whereString.append(entry.getKey());
				if(entry.getKey().toString().contains(LIKE)){
					whereString.append(SPACE);
				}else{
					whereString.append(" = ? ");
				}
				values.add(entry.getValue());
			}
		}else if(keys instanceof Integer || keys instanceof String){
			if(this.key==null){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码(数据库主键)");
			}
			whereString.append(AND).append(this.key);
			if(keys.toString().contains(LIKE)){
				whereString.append(SPACE);
			}else{
				whereString.append(" = ? ");
			}
			
			values.add(keys);
			
		}else{
			throw new FunctionException(RetCode.SYSTEM_PARAM_ERROR, "调用方法参数类型");
		}
		
//		System.out.println(String.format(DOMAIN_DELETE_BY_DOMAIN, tableName,whereString));
//		System.out.println(values);
//		return 0;
		return jdbcTemplate.update(String.format(DOMAIN_DELETE_BY_DOMAIN, tableName,whereString),values.toArray());
	}


	@Override
	public int addDomain(Map<Object,Object> fields) throws FunctionException {
		if(CollectionUtils.isEmpty(fields)){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
		}
		List<Object> valuelist = new ArrayList<Object>();
		List<String> pams = new ArrayList<String>();
		StringBuilder paramString2 = new StringBuilder();
		Set<Map.Entry<Object, Object>> paramSet = fields.entrySet();
		paramString2.append(" ").append(formatCollection(fields.keySet())).append(" ");
		for(Entry<Object, Object> entry : paramSet){
			pams.add("?");
			valuelist.add(entry.getValue());
		}
//		System.out.println(String.format(DOMAIN_ADD,tableName, paramString2.toString(),formatCollection(pams)));
//		System.out.println(valuelist);
//		return 0;
		return jdbcTemplate.update(String.format(DOMAIN_ADD,tableName, paramString2.toString(),formatCollection(pams)),valuelist.toArray());
	}
	@Override
	public T getDomain(Map<Object, Object> keys) throws FunctionException {
		return this.getDomainById(null,keys);
	}
	
	
	@Override
	public T getDomain(Integer key) throws FunctionException {
		return this.getDomainById(null,key);
	}

	@Override
	public T getDomain(String key) throws FunctionException {
		return this.getDomainById(null,key);
	}
	
	private T getDomainById(Object[] fields,Object key) throws FunctionException {
		Map<Object, Object> keys = new LinkedHashMap<Object, Object>();
		if(key==null){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
		}
		List<T> list ;
		if(key instanceof Map){
			if(CollectionUtils.isEmpty((Map<Object, Object>) key)){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码");
			}
			list = this.findDomains(fields,keys);
		}else if(key instanceof Integer || key instanceof String){
			if(this.key==null){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "主键代码(数据库主键)");
			}
			keys.put(this.key, key);
			list = this.findDomains(keys);
			
		}else{
			throw new FunctionException(RetCode.SYSTEM_PARAM_ERROR, "调用方法参数类型");
		}
		if(CollectionUtils.isEmpty(list)){
			return null;
		}else if(list.size()>1){
			throw new FunctionException(RetCode.SYSTEM_PARAM_ERROR, "调用方法参数类型");
		}else{
			return list.get(0);
		}
	}


	@Override
	public T getDomain(Object[] fields, Integer key) throws FunctionException {
		return this.getDomainById(fields,key);
	}

	@Override
	public T getDomain(Object[] fields, String key) throws FunctionException {
		return this.getDomainById(fields,key);
	}


	@Override
	public T getDomain(Object[] fields, Map<Object, Object> keys) throws FunctionException {
		return this.getDomainById(fields,keys);
	}

	
	private String formatArrays(Object[] objects){
		if(ArrayUtils.isEmpty(objects)){
			return "";
		}else{
			return Arrays.toString(objects).replaceAll("\\[|\\]", "");
		}
	}								
	private String formatCollection(Collection collection){
		if(CollectionUtils.isEmpty(collection)){
			return "";
		}else{
			return collection.toString().replaceAll("\\[|\\]", "");
		}
	}
}
