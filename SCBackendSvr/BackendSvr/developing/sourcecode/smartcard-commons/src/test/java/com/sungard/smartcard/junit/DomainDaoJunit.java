package com.sungard.smartcard.junit;

import java.util.LinkedHashMap;
import java.util.Map;

import com.sungard.smartcard.junit.domain.DictionaryDomain;
import org.junit.BeforeClass;
import org.junit.Test;

import com.sungard.smartcard.exception.FunctionException;


public class DomainDaoJunit {
	
	private static DictionaryDomain dictionaryDomain;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
//		Map<Object,Object> map = new LinkedHashMap<Object, Object>();
//		map.put("key1", "value1");
//		map.put("key2", "value2");
//		map.put("key3", "value3");
//		map.put("key4", "value4");
//		
//		List<String> list = new ArrayList<String>();
//		list.add("1");
//		list.add("2");
//		list.add("3");
//		list.add("4");
		

		dictionaryDomain = new DictionaryDomain();
		dictionaryDomain.setTableName("t_dictionary");
		dictionaryDomain.setParamas(new String[]{"dicttype", "dicttypename", "dictval", "dictcaption"});
	}
	
	/*public List<T> findDomains(Map<Object,Object> wheres);
	public List<T> findDomains(Object[] params,Map<Object,Object> wheres);
	public int updateDomain(Map<Object,Object> params,Map<Object,Object> wheres) throws FunctionException;
	public int removeDomain(Map<Object,Object> wheres) throws FunctionException;
	public int addDomain(Map<Object,Object> params) throws FunctionException;
	public T getDomain(Map<Object,Object> wheres) throws FunctionException;
	public T getDomain(Object[] params,Map<Object,Object> wheres) throws FunctionException;*/
	
	@Test
	public void findDomainsTest(){
		dictionaryDomain.findDomains();
	}
	
	/**
	 * public List<T> findDomains(Map<Object,Object> wheres);
	 */
	@Test
	public void findDomainsTest2(){
		Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
		wheres.put("dicttype", 1);
		wheres.put("dictval", "1");
		dictionaryDomain.findDomains(wheres);
		
	}
	/**
	 * List<T> findDomains(Object[] params,Map<Object,Object> wheres);
	 * 
	 */
	@Test
	public void findDomainsTest3(){
		Object[] params = new Object[]{"dicttype", "dicttypename"};
		
		Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
		wheres.put("dicttype like ?", "%s%");
		wheres.put("dictval", "1");
		dictionaryDomain.findDomains(params,wheres);
		
	}
	/**
	 * public List<T> findDomains(Object[] params);
	 */
	@Test
	public void findDomainsTest4(){
		Object[] params = new Object[]{"dicttype", "dicttypename"};
		
		dictionaryDomain.findDomains(params);
		
	}

	/**
	 * public int updateDomain(Map<Object,Object> params,Map<Object,Object> wheres) throws FunctionException;
	 */
	@Test
	public void updateDomainTest(){
		try {
			Map<Object, Object> params = new LinkedHashMap<Object, Object>();
			params.put("dicttypename", "系统状态2");
			params.put("dictcaption", "流水入帐状态2");
			
			Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
			wheres.put("dicttype", 1);
			wheres.put("dictval", "2");
			dictionaryDomain.updateDomain(params, wheres);
		} catch (FunctionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	/**
	 * public int removeDomain(Map<Object,Object> wheres) throws FunctionException;
	 */
	@Test
	public void removeDomain(){
		try {
			Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
			wheres.put("dicttype", 1);
			wheres.put("dictval", "2");
			dictionaryDomain.removeDomain(wheres);
		} catch (FunctionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * public int addDomain(Map<Object,Object> params) throws FunctionException;
	 */
	@Test
	public void addDomain(){
		try {
			Map<Object, Object> params = new LinkedHashMap<Object, Object>();
			params.put("dicttype", 1);
			params.put("dicttypename", "系统状态2");
			params.put("dictval", "6");
			params.put("dictcaption", "流水入帐状态2");
			dictionaryDomain.addDomain(params);
		} catch (FunctionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	@Test
	public void getDomain(){
		try {
			Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
			wheres.put("dicttype like ?", 1);
			wheres.put("dictval", "6");
			dictionaryDomain.getDomain(wheres);
		} catch (FunctionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
