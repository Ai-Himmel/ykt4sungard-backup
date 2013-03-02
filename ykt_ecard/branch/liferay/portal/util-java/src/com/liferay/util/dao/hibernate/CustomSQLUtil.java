/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.util.dao.hibernate;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.CollectionFactory;
import com.liferay.util.dao.DataAccess;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

import java.sql.Connection;
import java.sql.DatabaseMetaData;

import java.util.Iterator;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="CustomSQLUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Bruno Farache
 *
 */
public abstract class CustomSQLUtil {

	public static final String DB2_FUNCTION_IS_NULL =
		"CAST(? AS VARCHAR(32672)) IS NULL";

	public static final String DB2_FUNCTION_IS_NOT_NULL =
		"CAST(? AS VARCHAR(32672)) IS NOT NULL";

	public static final String INFORMIX_FUNCTION_IS_NULL = "lportal.isnull(?)";

	public static final String INFORMIX_FUNCTION_IS_NOT_NULL =
		"NOT " + INFORMIX_FUNCTION_IS_NULL;

	public static final String MYSQL_FUNCTION_IS_NULL = "IFNULL(?, '1') = '1'";

	public static final String MYSQL_FUNCTION_IS_NOT_NULL =
		"IFNULL(?, '1') = '0'";

	public static final String SYBASE_FUNCTION_IS_NULL = "ISNULL(?, '1') = '1'";

	public static final String SYBASE_FUNCTION_IS_NOT_NULL =
		"ISNULL(?, '1') = '0'";

	public CustomSQLUtil(String functionIsNull, String functionIsNotNull) {
		this(null, functionIsNull, functionIsNotNull);
	}

	public CustomSQLUtil(Connection con, String functionIsNull,
						 String functionIsNotNull) {

		try {
			if (Validator.isNotNull(functionIsNull) &&
				Validator.isNotNull(functionIsNotNull)) {

				_functionIsNull = functionIsNull;
				_functionIsNotNull = functionIsNotNull;

				if (_log.isDebugEnabled()) {
					_log.info(
						"functionIsNull is manually set to " + functionIsNull);
					_log.info(
						"functionIsNotNull is manually set to " +
							functionIsNotNull);
				}
			}
			else if (con != null) {
				DatabaseMetaData metaData = con.getMetaData();

				String dbName = GetterUtil.getString(
					metaData.getDatabaseProductName());

				if (_log.isInfoEnabled()) {
					_log.info("Database name " + dbName);
				}

				if (dbName.startsWith("DB2")) {
					_vendorDB2 = true;
					_functionIsNull = DB2_FUNCTION_IS_NULL;
					_functionIsNotNull = DB2_FUNCTION_IS_NOT_NULL;

					if (_log.isInfoEnabled()) {
						_log.info("Detected DB2 with database name " + dbName);
					}
				}
				else if (dbName.startsWith("Informix")) {
					_vendorInformix = true;
					_functionIsNull = INFORMIX_FUNCTION_IS_NULL;
					_functionIsNotNull = INFORMIX_FUNCTION_IS_NOT_NULL;

					if (_log.isInfoEnabled()) {
						_log.info(
							"Detected Informix with database name " + dbName);
					}
				}
				else if (dbName.startsWith("MySQL")) {
					_vendorMySQL = true;
					//_functionIsNull = MYSQL_FUNCTION_IS_NULL;
					//_functionIsNotNull = MYSQL_FUNCTION_IS_NOT_NULL;

					if (_log.isInfoEnabled()) {
						_log.info(
							"Detected MySQL with database name " + dbName);
					}
				}
				else if (dbName.startsWith("Sybase") || dbName.equals("ASE")) {
					_vendorSybase = true;
					_functionIsNull = SYBASE_FUNCTION_IS_NULL;
					_functionIsNotNull = SYBASE_FUNCTION_IS_NOT_NULL;

					if (_log.isInfoEnabled()) {
						_log.info(
							"Detected Sybase with database name " + dbName);
					}
				}
				else if (dbName.startsWith("Oracle")) {
					_vendorOracle = true;

					if (_log.isInfoEnabled()) {
						_log.info(
							"Detected Oracle with database name " + dbName);
					}
				}
				else if (dbName.startsWith("PostgreSQL")) {
					_vendorPostgreSQL = true;

					if (_log.isInfoEnabled()) {
						_log.info(
							"Detected PostgreSQL with database name " + dbName);
					}
				}
				else {
					if (_log.isDebugEnabled()) {
						_log.debug(
							"Unable to detect database with name " + dbName);
					}
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
		finally {
			DataAccess.cleanUp(con);
		}

		_sqlPool = CollectionFactory.getHashMap();

		try {
			ClassLoader classLoader = getClass().getClassLoader();

			String[] configs = getConfigs();

			for (int i = 0; i < configs.length; i++) {
				read(classLoader, configs[i]);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public String get(String id) {
		return (String)_sqlPool.get(id);
	}

	/**
	 * Returns true if Hibernate is connecting to a DB2 database.
	 *
	 * @return		true if Hibernate is connecting to a DB2 database
	 */
	public boolean isVendorDB2() {
		return _vendorDB2;
	}

	/**
	 * Returns true if Hibernate is connecting to an Informix database.
	 *
	 * @return		true if Hibernate is connecting to an Informix database
	 */
	public boolean isVendorInformix() {
		return _vendorInformix;
	}

	/**
	 * Returns true if Hibernate is connecting to a MySQL database.
	 *
	 * @return		true if Hibernate is connecting to a MySQL database
	 */
	public boolean isVendorMySQL() {
		return _vendorMySQL;
	}

	/**
	 * Returns true if Hibernate is connecting to an Oracle database.
	 *
	 * Oracle has a nasty bug where it treats '' as a NULL value. See
	 * http://thedailywtf.com/forums/thread/26879.aspx for more information
	 * on this nasty bug.
	 *
	 * @return		true if Hibernate is connecting to an Oracle database
	 */
	public boolean isVendorOracle() {
		return _vendorOracle;
	}

	/**
	 * Returns true if Hibernate is connecting to a PostgreSQL database.
	 *
	 * @return		true if Hibernate is connecting to a PostgreSQL database
	 */
	public boolean isVendorPostgreSQL() {
		return _vendorPostgreSQL;
	}

	/**
	 * Returns true if Hibernate is connecting to a Sybase database.
	 *
	 * @return		true if Hibernate is connecting to a Sybase database
	 */
	public boolean isVendorSybase() {
		return _vendorSybase;
	}

	public String[] keywords(String keywords) {
		return keywords(keywords, true);
	}

	public String[] keywords(String keywords, boolean lowerCase) {
		if (lowerCase) {
			keywords = keywords.toLowerCase();
		}

		keywords = keywords.trim();

		String[] keywordsArray = StringUtil.split(keywords, StringPool.SPACE);

		for (int i = 0; i < keywordsArray.length; i++) {
			String keyword = keywordsArray[i];

			keywordsArray[i] =
				StringPool.PERCENT + keyword + StringPool.PERCENT;
		}

		return keywordsArray;
	}

	public String[] keywords(String[] keywordsArray) {
		return keywords(keywordsArray, true);
	}

	public String[] keywords(String[] keywordsArray, boolean lowerCase) {
		if ((keywordsArray == null) || (keywordsArray.length == 0)) {
			keywordsArray = new String[] {null};
		}

		if (lowerCase) {
			for (int i = 0; i < keywordsArray.length; i++) {
				keywordsArray[i] = StringUtil.lowerCase(keywordsArray[i]);
			}
		}

		return keywordsArray;
	}

	public String replaceAndOperator(String sql, boolean andOperator) {
		String andOrConnector = "OR";
		String andOrNullCheck = "AND ? IS NOT NULL";

		if (andOperator) {
			andOrConnector = "AND";
			andOrNullCheck = "OR ? IS NULL";
		}

		sql = StringUtil.replace(
			sql,
			new String[] {
				"[$AND_OR_CONNECTOR$]", "[$AND_OR_NULL_CHECK$]"
			},
			new String[] {
				andOrConnector, andOrNullCheck
			});

		if (_vendorPostgreSQL) {
			sql = StringUtil.replace(
				sql,
				new String[] {
					"Date >= ? AND ? IS NOT NULL",
					"Date <= ? AND ? IS NOT NULL",
					"Date >= ? OR ? IS NULL",
					"Date <= ? OR ? IS NULL"
				},
				new String[] {
					"Date >= ? AND CAST(? AS TIMESTAMP) IS NOT NULL",
					"Date <= ? AND CAST(? AS TIMESTAMP) IS NOT NULL",
					"Date >= ? OR CAST(? AS TIMESTAMP) IS NULL",
					"Date <= ? OR CAST(? AS TIMESTAMP) IS NULL"
				});
		}

		sql = replaceIsNull(sql);

		return sql;
	}

	public String replaceIsNull(String sql) {
		if (Validator.isNotNull(_functionIsNull)) {
			sql = StringUtil.replace(
				sql,
				new String[] {
					"? IS NULL", "? IS NOT NULL"
				},
				new String[] {
					_functionIsNull,
					_functionIsNotNull
				});
		}

		return sql;
	}

	public String replaceKeywords(
		String sql, String field, String operator, boolean last,
		String[] values) {

		if (values.length == 0) {
			return sql;
		}

		StringMaker oldSql = new StringMaker();

		oldSql.append("(");
		oldSql.append(field);
		oldSql.append(" ");
		oldSql.append(operator);
		oldSql.append(" ? [$AND_OR_NULL_CHECK$])");

		if (!last) {
			oldSql.append(" [$AND_OR_CONNECTOR$]");
		}

		StringMaker newSql = new StringMaker();

		newSql.append("(");

		for (int i = 0; i < values.length; i++) {
			if (i > 0) {
				newSql.append(" OR ");
			}

			newSql.append("(");
			newSql.append(field);
			newSql.append(" ");
			newSql.append(operator);
			newSql.append(" ? [$AND_OR_NULL_CHECK$])");
		}

		newSql.append(")");

		if (!last) {
			newSql.append(" [$AND_OR_CONNECTOR$]");
		}

		return StringUtil.replace(sql, oldSql.toString(), newSql.toString());
	}

	public String removeOrderBy(String sql) {
		int pos = sql.indexOf(" ORDER BY ");

		if (pos != -1) {
			sql = sql.substring(0, pos);
		}

		return sql;
	}

	public String replaceOrderBy(String sql, OrderByComparator obc) {
		if (obc == null) {
			return sql;
		}

		StringMaker sm = new StringMaker();

		sm.append(removeOrderBy(sql));
		sm.append(" ORDER BY ");
		sm.append(obc.getOrderBy());

		return sm.toString();
	}

	protected abstract String[] getConfigs();

	protected void read(ClassLoader classLoader, String source)
		throws Exception {

		String xml = null;

		try {
			xml = StringUtil.read(classLoader, source);
		}
		catch (Exception e) {
			_log.warn("Cannot load " + source);
		}

		if (xml == null) {
			return;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Loading " + source);
		}

		SAXReader reader = new SAXReader();

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		Iterator itr = root.elements("sql").iterator();

		while (itr.hasNext()) {
			Element sql = (Element)itr.next();

			String file = sql.attributeValue("file");

			if (Validator.isNotNull(file)) {
				read(classLoader, file);
			}
			else {
				String id = sql.attributeValue("id");
				String content = transform(sql.getText());

				content = replaceIsNull(content);

				_sqlPool.put(id, content);
			}
		}
	}

	protected String transform(String sql) {
		StringMaker sm = new StringMaker();

		try {
			BufferedReader br = new BufferedReader(new StringReader(sql));

			String line = null;

			while ((line = br.readLine()) != null) {
				sm.append(line.trim());
				sm.append(StringPool.SPACE);
			}

			br.close();
		}
		catch (IOException ioe) {
			return sql;
		}

		return sm.toString();
	}

	private static Log _log = LogFactory.getLog(CustomSQLUtil.class);

	private boolean _vendorDB2;
	private boolean _vendorInformix;
	private boolean _vendorMySQL;
	private boolean _vendorOracle;
	private boolean _vendorPostgreSQL;
	private boolean _vendorSybase;
	private String _functionIsNull;
	private String _functionIsNotNull;
	private Map _sqlPool;

}