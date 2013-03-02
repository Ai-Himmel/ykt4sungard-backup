package com.kingstargroup.fdykt.util;

import java.io.CharArrayReader;
import java.io.IOException;
import java.io.Reader;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.log4j.Logger;
import org.w3c.dom.Document;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

public class Transformer {
	private static final Logger logger = Logger.getLogger(Transformer.class);

	/**
	 * transform query result into map,key is the alias of the field in query
	 * string
	 * 
	 * @param rs
	 *            .
	 * @return .
	 * @throws SQLException .
	 */
	public List<Map> transformToMap(ResultSet rs) throws SQLException {
		List<Map> result = new ArrayList<Map>();
		if (rs != null) {
			ResultSetMetaData metaData = rs.getMetaData();
			int columnCount = metaData.getColumnCount();
			while (rs.next()) {
				Map row = new HashMap();
				for (int i = 1; i <= columnCount; i++) {
					String value = rs.getObject(i) == null ? "" : rs.getObject(i).toString();
					row.put(metaData.getColumnName(i), value);
				}
				result.add(row);
			}
		}
		return result;
	}

	/**
	 * transform query result into pojo,make sure there are set methods for the
	 * alias of the field in query string
	 * 
	 * @param rs
	 *            .
	 * @param entityClass
	 *            .
	 * @param <T>
	 *            .
	 * @return .
	 * @throws InvocationTargetException .
	 * @throws NoSuchMethodException .
	 * @throws InstantiationException .
	 * @throws IllegalAccessException .
	 * @throws SQLException .
	 */
	public <T> List<T> transformToBean(ResultSet rs, final Class<T> entityClass) throws InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException, SQLException {
		Map<String, Method> methods = getMethods(entityClass);
		List<T> result = new ArrayList<T>();
		if (rs != null) {
			ResultSetMetaData metaData = rs.getMetaData();
			int columnCount = metaData.getColumnCount();
			while (rs.next()) {
				T bean = getInstance(entityClass);
				for (int i = 1; i <= columnCount; i++) {
					String columnName = metaData.getColumnName(i);
					String value = rs.getObject(i) == null ? "" : rs.getObject(i).toString();
					Method setMethod = methods.get("SET" + columnName.toUpperCase());
					if (setMethod != null) {
						Object[] args = new Object[] { value };
						setMethod.invoke(bean, args);
					} else {
						logger.warn("can't find method:" + "SET" + columnName.toUpperCase());
					}
				}
				result.add(bean);
			}
		}
		return result;
	}

	/**
	 * get mapped methods,chang method name into upper case
	 * 
	 * @param entityClass
	 *            .
	 * @return .
	 */
	public Map<String, Method> getMethods(Class entityClass) {
		Map<String, Method> methods = new HashMap<String, Method>();
		Method[] array = entityClass.getMethods();
		for (int i = 0; i < array.length; i++) {
			Method method = array[i];
			String methodName = method.getName().toUpperCase();
			methods.put(methodName, method);
		}
		return methods;
	}

	/**
	 * use constructor without args to get instance
	 * 
	 * @param entityClass
	 *            .
	 * @param <T>
	 *            .
	 * @return
	 * @throws NoSuchMethodException .
	 * @throws InvocationTargetException .
	 * @throws IllegalAccessException .
	 * @throws InstantiationException .
	 */
	public <T> T getInstance(final Class<T> entityClass) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException, InstantiationException {
		Class[] argsClass = new Class[0];
		Object[] args = new Object[0];
		Constructor<T> constructor = entityClass.getConstructor(argsClass);
		return constructor.newInstance(args);
	}

	public Document parse(String content) throws IOException, SAXException, ParserConfigurationException {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		factory.setIgnoringElementContentWhitespace(true);
		DocumentBuilder builder = factory.newDocumentBuilder();
		Reader reader = new CharArrayReader(content.toCharArray());
		Document document = builder.parse(new InputSource(reader));
		return document;
	}
}
