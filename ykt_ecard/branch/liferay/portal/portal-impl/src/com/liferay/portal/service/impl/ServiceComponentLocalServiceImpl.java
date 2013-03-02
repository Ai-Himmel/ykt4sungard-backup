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

package com.liferay.portal.service.impl;

import com.liferay.portal.OldServiceComponentException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.ServiceComponent;
import com.liferay.portal.service.base.ServiceComponentLocalServiceBaseImpl;
import com.liferay.portal.tools.sql.DBUtil;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.util.Http;
import com.liferay.util.xml.XMLFormatter;

import java.io.IOException;
import java.io.StringReader;

import java.lang.reflect.Field;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentFactory;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ServiceComponentLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ServiceComponentLocalServiceImpl
	extends ServiceComponentLocalServiceBaseImpl {

	public ServiceComponent updateServiceComponent(
			ServletContext ctx, ClassLoader portletClassLoader,
			String buildNamespace, long buildNumber, long buildDate)
		throws PortalException, SystemException {

		ServiceComponent serviceComponent = null;
		ServiceComponent previousServiceComponent = null;

		List serviceComponents =
			serviceComponentPersistence.findByBuildNamespace(
				buildNamespace, 0, 1);

		if (serviceComponents.size() == 0) {
			long serviceComponentId = counterLocalService.increment();

			serviceComponent = serviceComponentPersistence.create(
				serviceComponentId);

			serviceComponent.setBuildNamespace(buildNamespace);
			serviceComponent.setBuildNumber(buildNumber);
			serviceComponent.setBuildDate(buildDate);
		}
		else {
			serviceComponent = (ServiceComponent)serviceComponents.get(0);

			if (serviceComponent.getBuildNumber() < buildNumber) {
				previousServiceComponent = serviceComponent;

				long serviceComponentId = counterLocalService.increment();

				serviceComponent = serviceComponentPersistence.create(
					serviceComponentId);

				serviceComponent.setBuildNamespace(buildNamespace);
				serviceComponent.setBuildNumber(buildNumber);
				serviceComponent.setBuildDate(buildDate);
			}
			else if (serviceComponent.getBuildNumber() > buildNumber) {
				throw new OldServiceComponentException(
					"Build namespace " + buildNamespace + " has build number " +
						serviceComponent.getBuildNumber() +
							" which is newer than " + buildNumber);
			}
			else {
				return serviceComponent;
			}
		}

		try {
			DocumentFactory docFactory = DocumentFactory.getInstance();

			Document doc = docFactory.createDocument("UTF-8");

			Element data = doc.addElement("data");

			String tablesSQL = Http.URLtoString(ctx.getResource(
				"/WEB-INF/sql/tables.sql"));

			data.addElement("tables-sql").addCDATA(tablesSQL);

			String sequencesSQL = Http.URLtoString(ctx.getResource(
				"/WEB-INF/sql/sequences.sql"));

			data.addElement("sequences-sql").addCDATA(sequencesSQL);

			String indexesSQL = Http.URLtoString(ctx.getResource(
				"/WEB-INF/sql/indexes.sql"));

			data.addElement("indexes-sql").addCDATA(indexesSQL);

			String dataXML = XMLFormatter.toString(doc);

			serviceComponent.setData(dataXML);

			serviceComponentPersistence.update(serviceComponent);

			upgradeDB(
				portletClassLoader, buildNamespace, buildNumber,
				previousServiceComponent, tablesSQL, sequencesSQL, indexesSQL);

			removeOldServiceComponents(buildNamespace);

			return serviceComponent;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	protected List getModels(ClassLoader portletClassLoader)
		throws DocumentException, IOException {

		List models = new ArrayList();

		String xml = StringUtil.read(
			portletClassLoader, "META-INF/portlet-model-hints.xml");

		SAXReader reader = new SAXReader();

		Document doc = reader.read(new StringReader(xml));

		Element root  = doc.getRootElement();

		Iterator itr = root.elements("model").iterator();

		while (itr.hasNext()) {
			Element modelEl = (Element)itr.next();

			String name = modelEl.attributeValue("name");

			models.add(name);
		}

		return models;
	}

	protected void upgradeDB(
			ClassLoader portletClassLoader, String buildNamespace,
			long buildNumber, ServiceComponent previousServiceComponent,
			String tablesSQL, String sequencesSQL, String indexesSQL)
		throws Exception {

		DBUtil dbUtil = DBUtil.getInstance();

		if (previousServiceComponent == null) {
			if (_log.isInfoEnabled()) {
				_log.info(
					"Running " + buildNamespace +
						" SQL scripts for the first time");
			}

			dbUtil.runSQLTemplateString(tablesSQL, true, true);
			dbUtil.runSQLTemplateString(sequencesSQL, true, true);
			dbUtil.runSQLTemplateString(indexesSQL, true, true);
		}
		else {
			if (_log.isInfoEnabled()) {
				_log.info(
					"Upgrading " + buildNamespace +
						" database to build number " + buildNumber);
			}

			if (!tablesSQL.equals(
					previousServiceComponent.getTablesSQL())) {

				if (_log.isInfoEnabled()) {
					_log.info("Upgrading database with tables.sql");
				}

				dbUtil.runSQLTemplateString(tablesSQL, true, false);

				upgradeModels(portletClassLoader);
			}

			if (!sequencesSQL.equals(
					previousServiceComponent.getSequencesSQL())) {

				if (_log.isInfoEnabled()) {
					_log.info("Upgrading database with sequences.sql");
				}

				dbUtil.runSQLTemplateString(sequencesSQL, true, false);
			}

			if (!indexesSQL.equals(
					previousServiceComponent.getIndexesSQL())) {

				if (_log.isInfoEnabled()) {
					_log.info("Upgrading database with indexes.sql");
				}

				dbUtil.runSQLTemplateString(indexesSQL, true, false);
			}
		}
	}

	protected void upgradeModels(ClassLoader portletClassLoader)
		throws Exception {

		List models = getModels(portletClassLoader);

		for (int i = 0; i < models.size(); i++) {
			String name = (String)models.get(i);

			int pos = name.lastIndexOf(".model.");

			name =
				name.substring(0, pos) + ".model.impl." +
					name.substring(pos + 7) + "ModelImpl";

			Class modelClass = Class.forName(name, true, portletClassLoader);

			Field tableNameField = modelClass.getField("TABLE_NAME");
			Field tableColumnsField = modelClass.getField("TABLE_COLUMNS");
			Field tableSQLCreateField = modelClass.getField("TABLE_SQL_CREATE");

			String tableName = (String)tableNameField.get(null);
			Object[][] tableColumns = (Object[][])tableColumnsField.get(null);
			String tableSQLCreate = (String)tableSQLCreateField.get(null);

			UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
				tableName, tableColumns);

			upgradeTable.setCreateSQL(tableSQLCreate);

			upgradeTable.updateTable();
		}
	}

	protected void removeOldServiceComponents(String buildNamespace)
		throws SystemException {

		int serviceComponentsCount =
			serviceComponentPersistence.countByBuildNamespace(buildNamespace);

		if (serviceComponentsCount < _MAX_SERVICE_COMPONENTS) {
			return;
		}

		List serviceComponents =
			serviceComponentPersistence.findByBuildNamespace(
				buildNamespace, _MAX_SERVICE_COMPONENTS,
				serviceComponentsCount);

		for (int i = 0; i < serviceComponents.size(); i++) {
			ServiceComponent serviceComponent =
				(ServiceComponent)serviceComponents.get(i);

			serviceComponentPersistence.remove(serviceComponent);
		}
	}

	private static final int _MAX_SERVICE_COMPONENTS = 10;

	private static Log _log =
		LogFactory.getLog(ServiceComponentLocalServiceImpl.class);

}