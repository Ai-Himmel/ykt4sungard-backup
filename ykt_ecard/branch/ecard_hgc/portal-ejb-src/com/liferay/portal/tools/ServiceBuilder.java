/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.tools;

import com.liferay.portal.util.EntityResolver;
import com.liferay.portal.util.PortletKeys;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringUtil;
import com.liferay.util.TextFormatter;
import com.liferay.util.Time;
import com.liferay.util.Validator;
import com.liferay.util.lang.ClassUtil;
import com.liferay.util.lang.FastStringBuffer;
import de.hunsicker.io.FileFormat;
import de.hunsicker.jalopy.Jalopy;
import de.hunsicker.jalopy.storage.Convention;
import de.hunsicker.jalopy.storage.ConventionKeys;
import de.hunsicker.jalopy.storage.Environment;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.lang.reflect.Field;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import xjavadoc.Type;
import xjavadoc.XClass;
import xjavadoc.XJavaDoc;
import xjavadoc.XMethod;
import xjavadoc.XParameter;

import xjavadoc.filesystem.FileSourceSet;

/**
 * <a href="ServiceBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ServiceBuilder {

	public static void main(String[] args) {
		if (args.length == 5) {
			new ServiceBuilder(args[0], args[1], args[2], args[3], args[4]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public static Set getBadCmpFields() {
		Set badCmpFields = new HashSet();

		badCmpFields.add("access");
		badCmpFields.add("active");
		badCmpFields.add("alias");
		badCmpFields.add("date");
		badCmpFields.add("end");
		badCmpFields.add("featured");
		badCmpFields.add("fields");
		badCmpFields.add("from");
		badCmpFields.add("index");
		badCmpFields.add("internal");
		badCmpFields.add("interval");
		badCmpFields.add("join");
		badCmpFields.add("key");
		badCmpFields.add("log");
		badCmpFields.add("password");
		badCmpFields.add("primary");
		badCmpFields.add("sale");
		badCmpFields.add("settings");
		badCmpFields.add("size");
		badCmpFields.add("start");
		badCmpFields.add("text");
		badCmpFields.add("to");
		badCmpFields.add("type");
		badCmpFields.add("values");

		return badCmpFields;
	}

	public static Set getBadTableNames() {
		Set badTableNames = new HashSet();

		badTableNames = new HashSet();
		badTableNames.add("Action");
		badTableNames.add("Cache");
		badTableNames.add("Group");
		badTableNames.add("Organization");
		badTableNames.add("Permission");
		badTableNames.add("Release");
		badTableNames.add("Resource");
		badTableNames.add("Role");
		badTableNames.add("User");

		return badTableNames;
	}

	public static void writeFile(File file, String content) throws IOException {
		writeFile(file, content, "Brian Wing Shun Chan");
	}

	public static void writeFile(File file, String content, String author)
		throws IOException {

		File tempFile = new File("ServiceBuilder.temp");
		FileUtil.write(tempFile, content);

		// Strip unused imports

		String[] checkImports = new String[] {
			"com.liferay.portal.PortalException",
			"com.liferay.portal.auth.HttpPrincipal",
			"com.liferay.portal.service.impl.PrincipalSessionBean",
			"com.liferay.portal.servlet.TunnelUtil",
			"com.liferay.portal.util.PropsUtil",
			"com.liferay.util.GetterUtil",
			"com.liferay.util.StringPool",
			"com.liferay.util.StringUtil",
			"com.liferay.util.ObjectValuePair",
			"com.liferay.util.dao.hibernate.OrderByComparator",
			"com.liferay.util.dao.hibernate.Query",
			"com.liferay.util.dao.hibernate.ScrollableResults",
			"com.liferay.util.lang.BooleanWrapper",
			"com.liferay.util.lang.DoubleWrapper",
			"com.liferay.util.lang.FastStringBuffer;",
			"com.liferay.util.lang.FloatWrapper",
			"com.liferay.util.lang.IntegerWrapper",
			"com.liferay.util.lang.LongWrapper",
			"com.liferay.util.lang.MethodWrapper",
			"com.liferay.util.lang.NullWrapper",
			"com.liferay.util.lang.ShortWrapper",
			"java.rmi.RemoteException",
			"java.util.Collection",
			"java.util.Collections",
			"java.util.Date",
			"java.util.HashSet",
			"java.util.Properties",
			"java.util.Set",
			"org.hibernate.Hibernate",
			"org.hibernate.ObjectNotFoundException",
			"org.hibernate.Query",
			"org.hibernate.ScrollableResults"
		};

		Set classes = ClassUtil.getClasses(tempFile);

		for (int i = 0; i < checkImports.length; i++) {
			String importClass = checkImports[i].substring(
				checkImports[i].lastIndexOf(".") + 1, checkImports[i].length());

			if (!classes.contains(importClass)) {
				content = StringUtil.replace(
					content, "import " + checkImports[i] + ";", "");
			}
		}

		FileUtil.write(tempFile, content);

		// Beautify

		StringBuffer sb = new StringBuffer();

		Jalopy jalopy = new Jalopy();
		jalopy.setFileFormat(FileFormat.UNIX);
		jalopy.setInput(tempFile);
		jalopy.setOutput(sb);

		try {
			Jalopy.setConvention("../tools/jalopy.xml");
		}
		catch (FileNotFoundException fnne) {
		}

		Environment env = Environment.getInstance();
		env.set("author", author);
		env.set("fileName", file.getName());

		Convention convention = Convention.getInstance();

		convention.put(
			ConventionKeys.COMMENT_JAVADOC_TEMPLATE_CLASS,
			env.interpolate(convention.get(
				ConventionKeys.COMMENT_JAVADOC_TEMPLATE_CLASS, "")));

		convention.put(
			ConventionKeys.COMMENT_JAVADOC_TEMPLATE_INTERFACE,
			env.interpolate(convention.get(
				ConventionKeys.COMMENT_JAVADOC_TEMPLATE_INTERFACE, "")));

		jalopy.format();

		String newContent = sb.toString();

		/*
		// Remove blank lines after try {

		newContent = StringUtil.replace(newContent, "try {\n\n", "try {\n");

		// Remove blank lines after ) {

		newContent = StringUtil.replace(newContent, ") {\n\n", ") {\n");

		// Remove blank lines empty braces { }

		newContent = StringUtil.replace(newContent, "\n\n\t}", "\n\t}");

		// Add space to last }

		newContent = newContent.substring(0, newContent.length() - 2) + "\n\n}";
		*/

		// Write file if and only if the file has changed

		String oldContent = null;

		if (file.exists()) {

			// Read file

			oldContent = FileUtil.read(file);

			// Keep old version number

			int x = oldContent.indexOf("@version $Revision:");

			if (x != -1) {
				int y = oldContent.indexOf("$", x);
				y = oldContent.indexOf("$", y + 1);

				String oldVersion = oldContent.substring(x, y + 1);

				newContent = StringUtil.replace(
					newContent, "@version $Rev: $", oldVersion);
			}
		}
		else {
			newContent = StringUtil.replace(
				newContent, "@version $Rev: $", "@version $Revision: 1.183 $");
		}

		if (oldContent == null || !oldContent.equals(newContent)) {
			FileUtil.write(file, newContent);

			System.out.println(file);

			// Workaround for bug with XJavaDoc

			file.setLastModified(
				System.currentTimeMillis() - (Time.SECOND * 5));
		}

		tempFile.deleteOnExit();
	}

	public ServiceBuilder(String fileName, String hbmFileName,
						  String springEntFileName, String springProFileName,
						  String sprintUtilClassName) {

		new ServiceBuilder(
			fileName, hbmFileName, springEntFileName, springProFileName,
			sprintUtilClassName, true);
	}

	public ServiceBuilder(String fileName, String hbmFileName,
						  String springEntFileName, String springProFileName,
						  String sprintUtilClassName, boolean build) {

		try {
			_badTableNames = ServiceBuilder.getBadTableNames();
			_badCmpFields = ServiceBuilder.getBadCmpFields();

			_hbmFileName = hbmFileName;
			_springEntFileName = springEntFileName;
			_springProFileName = springProFileName;
			_springUtilClassName = sprintUtilClassName;

			SAXReader reader = new SAXReader(true);
			reader.setEntityResolver(new EntityResolver());

			Document doc = reader.read(new File(fileName));

			Element root = doc.getRootElement();

			_portalRoot = root.attributeValue("root-dir");

			String packageDir = root.attributeValue("package-dir");

			_portletName = root.element("portlet").attributeValue("name");

			_portletShortName =
				root.element("portlet").attributeValue("short-name");

			_portletClassName =
				TextFormatter.format(_portletName, TextFormatter.D);

			_portletPackageName =
				TextFormatter.format(_portletName, TextFormatter.B);

			_outputPath =
				"src/" + StringUtil.replace(packageDir, ".", "/") + "/" +
					_portletPackageName;

			_packagePath = packageDir + "." + _portletPackageName;

			_ejbList = new ArrayList();

			List entities = root.elements("entity");

			Iterator itr1 = entities.iterator();

			while (itr1.hasNext()) {
				Element entityEl = (Element)itr1.next();

				String ejbName = entityEl.attributeValue("name");

				String table = entityEl.attributeValue("table");
				if (Validator.isNull(table)) {
					table = ejbName;

					if (_badTableNames.contains(ejbName)) {
						table += "_";
					}
				}

				boolean localService = GetterUtil.get(
					entityEl.attributeValue("local-service"), false);
				String persistenceClass = GetterUtil.get(
					entityEl.attributeValue("persistence-class"),
					_packagePath + ".service.persistence."+ ejbName +
						"Persistence");

				Iterator itr2 = null;

				List pkList = new ArrayList();
				List collectionList = new ArrayList();
				List columnList = new ArrayList();

				List columns = entityEl.elements("column");

				itr2 = columns.iterator();

				while (itr2.hasNext()) {
					Element column = (Element)itr2.next();

					String columnName = column.attributeValue("name");

					String columnDBName = column.attributeValue("db-name");
					if (Validator.isNull(columnDBName)) {
						columnDBName = columnName;

						if (_badCmpFields.contains(columnName)) {
							columnDBName += "_";
						}
					}

					String columnType = column.attributeValue("type");
					boolean primary = GetterUtil.get(
						column.attributeValue("primary"), false);
					String collectionEntity = column.attributeValue("entity");
					String mappingKey = column.attributeValue("mapping-key");
					String mappingTable = column.attributeValue("mapping-table");

					EntityColumn col = new EntityColumn(
						columnName, columnDBName, columnType, primary,
						collectionEntity, mappingKey, mappingTable);

					if (primary) {
						pkList.add(col);
					}

					if (columnType.equals("Collection")) {
						collectionList.add(col);
					}

					columnList.add(col);
				}

				EntityOrder order = null;

				Element orderEl = entityEl.element("order");

				if (orderEl != null) {
					boolean asc = true;
					if ((orderEl.attribute("by") != null) &&
						(orderEl.attributeValue("by").equals("desc"))) {

						asc = false;
					}

					List orderColsList = new ArrayList();

					order = new EntityOrder(asc, orderColsList);

					List orderCols = orderEl.elements("order-column");

					Iterator k = orderCols.iterator();

					while (k.hasNext()) {
						Element orderColEl = (Element)k.next();

						String orderColName =
							orderColEl.attributeValue("name");
						boolean orderColCaseSensitive = GetterUtil.get(
							orderColEl.attributeValue("case-sensitive"),
							true);

						boolean orderColByAscending = asc;
						String orderColBy = GetterUtil.getString(
							orderColEl.attributeValue("order-by"));
						if (orderColBy.equals("asc")) {
							orderColByAscending = true;
						}
						else if (orderColBy.equals("desc")) {
							orderColByAscending = false;
						}

						EntityColumn col = Entity.getColumn(
							orderColName, columnList);

						col.setCaseSensitive(orderColCaseSensitive);
						col.setOrderByAscending(orderColByAscending);

						orderColsList.add(col);
					}
				}

				List finderList = new ArrayList();

				List finders = entityEl.elements("finder");

				itr2 = finders.iterator();

				while (itr2.hasNext()) {
					Element finder = (Element)itr2.next();

					String finderName = finder.attributeValue("name");
					String finderReturn =
						finder.attributeValue("return-type");
					String finderWhere =
						finder.attributeValue("where");
					boolean finderDBIndex = GetterUtil.get(
						finder.attributeValue("db-index"), true);

					List finderColsList = new ArrayList();

					List finderCols = finder.elements("finder-column");

					Iterator k = finderCols.iterator();

					while (k.hasNext()) {
						Element finderEl = (Element)k.next();

						String finderColName =
							finderEl.attributeValue("name");

						String finderColDBName =
							finderEl.attributeValue("db-name");
						if (Validator.isNull(finderColDBName)) {
							finderColDBName = finderColName;

							if (_badCmpFields.contains(finderColName)) {
								finderColDBName += "_";
							}
						}

						String finderColType = "String";
						boolean finderColCheckArray = GetterUtil.get(
							finderEl.attributeValue("check-array"), false);

						if (finderColCheckArray) {
							EntityColumn finderCol = new EntityColumn(
								finderColName, finderColDBName, finderColType,
								false, null, null, null, false, false,
								finderColCheckArray);

							finderColsList.add(finderCol);
						}
						else {
							finderColsList.add(finderColName);
						}
					}

					finderList.add(new EntityFinder(
						finderName, finderReturn, finderColsList, finderWhere,
						finderDBIndex));
				}

				List referenceList = new ArrayList();

				if (build) {
					List references = entityEl.elements("reference");

					itr2 = references.iterator();

					while (itr2.hasNext()) {
						Element reference = (Element)itr2.next();

						String refPackageDir =
							reference.attributeValue("package-path");
						String refEntity = reference.attributeValue("entity");

						ServiceBuilder serviceBuilder = new ServiceBuilder(
							"src/" + StringUtil.replace(
								refPackageDir, ".", "/") + "/service.xml",
							_hbmFileName, _springEntFileName,
							_springProFileName, _springUtilClassName, false);

						referenceList.add(serviceBuilder.getEntity(refEntity));
					}
				}

				_ejbList.add(
					new Entity(
						_packagePath, _portletName, _portletShortName, ejbName,
						table, localService, persistenceClass, pkList,
						collectionList, columnList, order, finderList,
						referenceList));
			}

			List exceptionList = new ArrayList();

			if (root.element("exceptions") != null) {
				List exceptions =
					root.element("exceptions").elements("exception");

				itr1 = exceptions.iterator();

				while (itr1.hasNext()) {
					Element exception = (Element)itr1.next();

					exceptionList.add(exception.getText());
				}
			}

			if (build) {
				for (int x = 0; x < _ejbList.size(); x++) {
					Entity entity = (Entity)_ejbList.get(x);

					if (entity.hasColumns()) {
						_createHBM(entity);
						_createHBMUtil(entity);

						_createPersistence(entity);
						_createPersistenceUtil(entity);

						_createModel(entity);
						_createExtendedModel(entity);

						_createPool(entity);

						if (entity.getPKList().size() > 1) {
							_createEJBPK(entity);
						}
					}

					if (entity.hasLocalService()) {
						_createServiceImpl(entity, _BASIC_LOCAL);
						_createService(entity, _BASIC_LOCAL);
						_createServiceEJB(entity, _BASIC_LOCAL);
						_createServiceEJBImpl(entity, _BASIC_LOCAL);
						_createServiceHome(entity, _BASIC_LOCAL);
						_createServiceFactory(entity, _BASIC_LOCAL);
						_createServiceUtil(entity, _BASIC_LOCAL);

						_createService(entity, _BASIC_REMOTE);
						_createServiceEJB(entity, _BASIC_REMOTE);
						_createServiceRemoteEJBImpl(entity);
						_createServiceHome(entity, _BASIC_REMOTE);
						_createServiceFactory(entity, _BASIC_REMOTE);
						_createServiceUtil(entity, _BASIC_REMOTE);
					}

					_createServiceImpl(entity, _PRINCIPAL_REMOTE);
					_createService(entity, _PRINCIPAL_REMOTE);
					_createServiceEJB(entity, _PRINCIPAL_REMOTE);
					_createServiceEJBImpl(entity, _PRINCIPAL_REMOTE);
					_createServiceHome(entity, _PRINCIPAL_REMOTE);
					_createServiceFactory(entity, _PRINCIPAL_REMOTE);
					_createServiceUtil(entity, _PRINCIPAL_REMOTE);

					_createServiceHttp(entity);
					_createServiceSoap(entity);
				}

				_createEJBXML();
				_createHBMXML();
				_createSpringXML(true);
				_createSpringXML(false);

				_createSQLIndexes();
				_createSQLTables();

				_createExceptions(exceptionList);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public Entity getEntity(String name) {
		int pos = name.lastIndexOf(".");

		if (pos == -1) {
			pos = _ejbList.indexOf(new Entity(name));

			return (Entity)_ejbList.get(pos);
		}
		else {
			String refPackageDir = name.substring(0, pos);
			String refEJB = name.substring(pos + 1, name.length());

			ServiceBuilder serviceBuilder = new ServiceBuilder(
				"src/" + StringUtil.replace(
					refPackageDir, ".", "/") + "/service.xml",
				_hbmFileName, _springEntFileName, _springProFileName,
				_springUtilClassName, false);

			return serviceBuilder.getEntity(refEJB);
		}
	}

	private void _createEJBPK(Entity entity) throws IOException {
		List pkList = entity.getPKList();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.persistence;");

		// Imports

		sb.append("import com.liferay.util.StringPool;");
		sb.append("import com.liferay.util.lang.FastStringBuffer;");
		sb.append("import java.io.Serializable;");
		sb.append("import java.util.Date;");

		// Class declaration

		sb.append("public class " + entity.getPKClassName() + " implements Comparable, Serializable {");

		// Fields

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append("public " + col.getType() + " " + col.getName() + ";");
		}

		// Default constructor

		sb.append("public " + entity.getPKClassName() + "() {}");

		// Primary key constructor

		sb.append("public " + entity.getPKClassName() + "(");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append(col.getType() + " " + col.getName());

			if ((i + 1) != pkList.size()) {
				sb.append(", ");
			}
		}

		sb.append(") {");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append("this." + col.getName() + " = " + col.getName() + ";");
		}

		sb.append("}");

		// Getter and setter methods

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			if (!col.isCollection()) {
				sb.append("public " + col.getType() + " get" + col.getMethodName() + "() {");
				sb.append("return " + col.getName() + ";");
				sb.append("}");

				sb.append("public void set" + col.getMethodName() + "(" + col.getType() + " " + col.getName() + ") {");
				sb.append("this." + col.getName() + " = " + col.getName() + ";");
				sb.append("}");
			}
		}

		// Compare to method

		sb.append("public int compareTo(Object obj) {");
		sb.append("if (obj == null) {");
		sb.append("return -1;");
		sb.append("}");
		sb.append(entity.getPKClassName() + " pk = (" + entity.getPKClassName() + ")obj;");
		sb.append("int value = 0;");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			if (!col.isPrimitiveType()) {
				sb.append("value = " + col.getName() + ".compareTo(pk." + col.getName() + ");");
			}
			else {
				sb.append("if (" + col.getName() + " < pk." + col.getName() + ") {");
				sb.append("value = -1;");
				sb.append("}");
				sb.append("else if (" + col.getName() + " > pk." + col.getName() + ") {");
				sb.append("value = 1;");
				sb.append("}");
				sb.append("else {");
				sb.append("value = 0;");
				sb.append("}");
			}

			sb.append("if (value != 0) {");
			sb.append("return value;");
			sb.append("}");
		}

		sb.append("return 0;");
		sb.append("}");

		// Equals method

		sb.append("public boolean equals(Object obj) {");
		sb.append("if (obj == null) {");
		sb.append("return false;");
		sb.append("}");
		sb.append(entity.getPKClassName() + " pk = null;");
		sb.append("try {");
		sb.append("pk = (" + entity.getPKClassName() + ")obj;");
		sb.append("}");
		sb.append("catch (ClassCastException cce) {");
		sb.append("return false;");
		sb.append("}");
		sb.append("if (");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			if (!col.isPrimitiveType()) {
				sb.append("(" + col.getName() + ".equals(pk." + col.getName() + "))");
			}
			else {
				sb.append("(" + col.getName() + " == pk." + col.getName() + ")");
			}

			if ((i + 1) != pkList.size()) {
				sb.append(" && ");
			}
		}

		sb.append(") {");
		sb.append("return true;");
		sb.append("} else {");
		sb.append("return false;");
		sb.append("}");
		sb.append("}");

		// Hash code method

		sb.append("public int hashCode() {");
		sb.append("return (");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append(col.getName());

			if ((i + 1) != pkList.size()) {
				sb.append(" + ");
			}
		}

		sb.append(").hashCode();");
		sb.append("}");

		// To string method

		sb.append("public String toString() {");
		sb.append("FastStringBuffer sb = new FastStringBuffer();");
		sb.append("sb.append(StringPool.OPEN_CURLY_BRACE);");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append("sb.append(\"" + col.getName() + "\");");
			sb.append("sb.append(StringPool.EQUAL);");
			sb.append("sb.append(" + col.getName() + ");");

			if ((i + 1) != pkList.size()) {
				sb.append("sb.append(StringPool.COMMA);");
				sb.append("sb.append(StringPool.SPACE);");
			}
		}

		sb.append("sb.append(StringPool.CLOSE_CURLY_BRACE);");
		sb.append("return sb.toString();");
		sb.append("}");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/persistence/" + entity.getPKClassName() + ".java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createEJBXML() throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			List referenceList = entity.getReferenceList();

			if (entity.hasLocalService()) {
				_createEJBXMLSession(entity, referenceList, sb, _BASIC_LOCAL);
				_createEJBXMLSession(entity, referenceList, sb, _BASIC_REMOTE);
			}

			_createEJBXMLSession(entity, referenceList, sb, _PRINCIPAL_REMOTE);
		}

		File xmlFile = new File("classes/META-INF/ejb-jar.xml");

		if (!xmlFile.exists()) {
			String content =
				"<?xml version=\"1.0\"?>\n" +
				"<!DOCTYPE ejb-jar PUBLIC \"-//Sun Microsystems, Inc.//DTD Enterprise JavaBeans 2.0//EN\" \"http://java.sun.com/dtd/ejb-jar_2_0.dtd\">\n" +
				"\n" +
				"<ejb-jar>\n" +
				"\t<enterprise-beans>\n" +
				"\t</enterprise-beans>\n" +
				"</ejb-jar>";

			FileUtil.write(xmlFile, content);
		}

		String oldContent = FileUtil.read(xmlFile);
		String newContent = new String(oldContent);

		int x = oldContent.indexOf("<session>");
		int y = oldContent.lastIndexOf("</session>");

		if (x == -1) {
			x = newContent.indexOf("<enterprise-beans/>");
			if (x != -1) {
				newContent = StringUtil.replace(
					newContent, "<enterprise-beans/>", "<enterprise-beans />");
			}

			x = newContent.indexOf("<enterprise-beans />");
			if (x != -1) {
				newContent = StringUtil.replace(
					newContent, "<enterprise-beans />",
					"<enterprise-beans>\n\t</enterprise-beans>");
			}

			x = newContent.indexOf("</enterprise-beans>") - 1;
			newContent =
				newContent.substring(0, x) + sb.toString() +
				newContent.substring(x, newContent.length());
		}
		else {
			int firstSession = newContent.indexOf(
				"<ejb-name>" + StringUtil.replace(
					_packagePath + ".service.ejb.", ".", "_"),
				x);
			int lastSession = newContent.lastIndexOf(
				"<ejb-name>" + StringUtil.replace(
					_packagePath + ".service.ejb.", ".", "_"),
				y);

			if (firstSession == -1 || firstSession > y) {
				x = newContent.indexOf("</enterprise-beans>") - 1;
				newContent =
					newContent.substring(0, x) + sb.toString() +
					newContent.substring(x, newContent.length());
			}
			else {
				firstSession = newContent.lastIndexOf(
					"<session>", firstSession) - 2;
				lastSession = newContent.indexOf(
					"</session>", lastSession) + 11;

				newContent =
					newContent.substring(0, firstSession) + sb.toString() +
					newContent.substring(lastSession, newContent.length());
			}
		}

		if (!oldContent.equals(newContent)) {
			FileUtil.write(xmlFile, newContent);
		}
	}

	private void _createEJBXMLSession(Entity entity, List referenceList, FastStringBuffer sb, int sessionType) {
		sb.append("\t\t<session>\n");
		sb.append("\t\t\t<display-name>" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB</display-name>\n");
		sb.append("\t\t\t<ejb-name>" + StringUtil.replace(_packagePath + ".service.ejb.", ".", "_") + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB</ejb-name>\n");
		sb.append("\t\t\t<" + (sessionType == _BASIC_LOCAL ? "local-" : "") + "home>" + _packagePath + ".service.ejb." + entity.getName() + _getSessionTypeName(sessionType) + "ServiceHome</" + (sessionType == _BASIC_LOCAL ? "local-" : "") + "home>\n");
		sb.append("\t\t\t<" + (sessionType == _BASIC_LOCAL ? "local" : "remote") + ">" + _packagePath + ".service.ejb." + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB</" + (sessionType == _BASIC_LOCAL ? "local" : "remote") + ">\n");
		sb.append("\t\t\t<ejb-class>" + _packagePath + ".service.ejb." + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJBImpl</ejb-class>\n");
		sb.append("\t\t\t<session-type>Stateless</session-type>\n");
		sb.append("\t\t\t<transaction-type>Container</transaction-type>\n");

		for (int j = 0; j < referenceList.size(); j++) {
			Entity entityRef = (Entity)referenceList.get(j);

			if (entityRef.hasLocalService()) {
				sb.append("\t\t\t<ejb-local-ref>\n");
				sb.append("\t\t\t\t<ejb-ref-name>ejb/liferay/" + entityRef.getName() + "LocalServiceHome</ejb-ref-name>\n");
				sb.append("\t\t\t\t<ejb-ref-type>Session</ejb-ref-type>\n");
				sb.append("\t\t\t\t<local-home>" + entityRef.getPackagePath() + ".service.ejb." + entityRef.getName() + "LocalServiceHome</local-home>\n");
				sb.append("\t\t\t\t<local>" + entityRef.getPackagePath() + ".service.ejb." + entityRef.getName() + "LocalServiceEJB</local>\n");
				sb.append("\t\t\t\t<ejb-link>" + StringUtil.replace(entityRef.getPackagePath() + ".service.ejb.", ".", "_") + entityRef.getName() + "LocalServiceEJB</ejb-link>\n");
				sb.append("\t\t\t</ejb-local-ref>\n");
			}
		}

		for (int j = 0; j < _ejbList.size(); j++) {
			Entity entityRef = (Entity)_ejbList.get(j);

			if (!((sessionType == _BASIC_LOCAL) && entity.equals(entityRef)) && entityRef.hasLocalService()) {
				sb.append("\t\t\t<ejb-local-ref>\n");
				sb.append("\t\t\t\t<ejb-ref-name>ejb/liferay/" + entityRef.getName() + "LocalServiceHome</ejb-ref-name>\n");
				sb.append("\t\t\t\t<ejb-ref-type>Session</ejb-ref-type>\n");
				sb.append("\t\t\t\t<local-home>" + _packagePath + ".service.ejb." + entityRef.getName() + "LocalServiceHome</local-home>\n");
				sb.append("\t\t\t\t<local>" + _packagePath + ".service.ejb." + entityRef.getName() + "LocalServiceEJB</local>\n");
				sb.append("\t\t\t\t<ejb-link>" + StringUtil.replace(_packagePath + ".service.ejb.", ".", "_") + entityRef.getName() + "LocalServiceEJB</ejb-link>\n");
				sb.append("\t\t\t</ejb-local-ref>\n");
			}
		}

		sb.append("\t\t</session>\n");
	}

	private void _createExceptions(List exceptions) throws IOException {
		String copyright = null;
		try {
			copyright = FileUtil.read("../copyright.txt");
		}
		catch (FileNotFoundException fnfe) {
		}

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			if (entity.hasColumns()) {
				exceptions.add(_getNoSuchEntityException(entity));
			}
		}

		for (int i = 0; i < exceptions.size(); i++) {
			String exception = (String)exceptions.get(i);

			FastStringBuffer sb = new FastStringBuffer();

			if (Validator.isNotNull(copyright)) {
				sb.append(copyright + "\n");
				sb.append("\n");
			}

			sb.append("package " + _packagePath + ";\n");
			sb.append("\n");
			sb.append("import com.liferay.portal.PortalException;\n");
			sb.append("\n");

			if (Validator.isNotNull(copyright)) {
				sb.append("/**\n");
				sb.append(" * <a href=\"" + exception + "Exception.java.html\"><b><i>View Source</i></b></a>\n");
				sb.append(" *\n");
				sb.append(" * @author  Brian Wing Shun Chan\n");
				sb.append(" * @version $Revision: 1.183 $\n");
				sb.append(" *\n");
				sb.append(" */\n");
			}

			sb.append("public class " + exception + "Exception extends PortalException {\n");
			sb.append("\n");
			sb.append("\tpublic " + exception + "Exception() {\n");
			sb.append("\t\tsuper();\n");
			sb.append("\t}\n");
			sb.append("\n");
			sb.append("\tpublic " + exception + "Exception(String msg) {\n");
			sb.append("\t\tsuper(msg);\n");
			sb.append("\t}\n");
			sb.append("\n");
			sb.append("\tpublic " + exception + "Exception(String msg, Throwable cause) {\n");
			sb.append("\t\tsuper(msg, cause);\n");
			sb.append("\t}\n");
			sb.append("\n");
			sb.append("\tpublic " + exception + "Exception(Throwable cause) {\n");
			sb.append("\t\tsuper(cause);\n");
			sb.append("\t}\n");
			sb.append("\n");
			sb.append("}");

			File exceptionFile = new File(_outputPath + "/" + exception + "Exception.java");

			if (!exceptionFile.exists()) {
				FileUtil.write(exceptionFile, sb.toString());
			}
		}
	}

	private void _createExtendedModel(Entity entity) throws IOException {
		List pkList = entity.getPKList();
		List columnList = entity.getColumnList();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".model;");

		// Imports

		if (entity.hasCompoundPK()) {
			sb.append("import " + _packagePath + ".service.persistence." + entity.getName() + "PK;");
		}

		sb.append("import java.util.Date;");

		// Class declaration

		sb.append("public class " + entity.getName() + " extends " + entity.getName() + "Model {");

		// Empty constructor

		sb.append("public " + entity.getName() + "() {");
		sb.append("}");

		// Primary key constructor

		sb.append("public " + entity.getName() + "(");

		if (entity.hasCompoundPK()) {
			sb.append(entity.getPKClassName() + " pk");
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append(col.getType() + " " + col.getName());
		}

		sb.append(") {");
		sb.append("super(");

		if (entity.hasCompoundPK()) {
			sb.append("pk");
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append(col.getName());
		}

		sb.append(");");
		sb.append("}");

		// Complete constructor

		sb.append("public " + entity.getName() + "(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append(col.getType() + " " + col.getName() + ", ");
			}
		}

		if (columnList.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(") {");
		sb.append("super(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append(col.getName() + ", ");
			}
		}

		if (columnList.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(");");
		sb.append("}");

		// Class close brace

		sb.append("}");

		// Write file

		File modelFile = new File(_outputPath + "/model/" + entity.getName() + ".java");

		if (!modelFile.exists()) {
			writeFile(modelFile, sb.toString());
		}
	}

	private void _createHBM(Entity entity) throws IOException {
		List pkList = entity.getPKList();
		List columnList = entity.getColumnList();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.persistence;");

		// Imports

		sb.append("import java.util.Date;");
		sb.append("import java.util.Set;");

		// Class declaration

		sb.append("public class " + entity.getName() + "HBM {");

		// Empty constructor

		sb.append("protected " + entity.getName() + "HBM() {");
		sb.append("}");

		// Primary key constructor

		sb.append("protected " + entity.getName() + "HBM(");

		if (entity.hasCompoundPK()) {
			sb.append(entity.getPKClassName() + " pk");
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append(col.getType() + " " + col.getName());
		}

		sb.append(") {");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append("_" + col.getName() + " = " + (entity.hasCompoundPK() ? "pk." : "") + col.getName() + ";");
		}

		sb.append("}");

		// Complete constructor

		sb.append("protected " + entity.getName() + "HBM(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() == null) {
				sb.append(col.getType() + (col.getEJBName() != null ? "HBM" : "") + " " + col.getName() + ", ");
			}
		}

		if (columnList.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(") {");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() == null) {
				sb.append("_" + col.getName() + " = " + col.getName() + ";");
			}
		}

		sb.append("}");

		// Primary key accessor

		sb.append("public " + entity.getPKClassName() + " getPrimaryKey() {");

		if (entity.hasCompoundPK()) {
			sb.append("return new " + entity.getPKClassName() + "(");

			for (int i = 0; i < pkList.size(); i++) {
				EntityColumn col = (EntityColumn)pkList.get(i);

				sb.append("_" + col.getName());

				if ((i + 1) != (pkList.size())) {
					sb.append(", ");
				}
			}

			sb.append(");");
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append("return _" + col.getName() + ";");
		}

		sb.append("}");

		sb.append("protected void setPrimaryKey(" + entity.getPKClassName() + " pk) {");

		if (entity.hasCompoundPK()) {
			for (int i = 0; i < pkList.size(); i++) {
				EntityColumn col = (EntityColumn)pkList.get(i);

				sb.append("_" + col.getName() + " = pk." + col.getName() + ";");
			}
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append("_" + col.getName() + " = pk;");
		}

		sb.append("}");

		// Getter and setter methods

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append("protected " + col.getType() + (col.getEJBName() != null ? "HBM" : "") + " get" + col.getMethodName() + "() {");
				sb.append("return _" + col.getName() + ";");
				sb.append("}");

				sb.append("protected void set" + col.getMethodName() + "(" + col.getType() + (col.getEJBName() != null ? "HBM" : "") + " " + col.getName() + ") {");
				sb.append("_" + col.getName() + " = " + col.getName() + ";");
				sb.append("}");
			}
			else {
				sb.append("protected Set get" + col.getMethodName() + "() {");
				sb.append("return _" + col.getName() + ";");
				sb.append("}");

				sb.append("protected void set" + col.getMethodName() + "(Set " + col.getName() + ") {");
				sb.append("_" + col.getName() + " = " + col.getName() + ";");
				sb.append("}");
			}
		}

		// Fields

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append("private " + col.getType() + (col.getEJBName() != null ? "HBM" : "") + " _" + col.getName() + ";");
			}
			else {
				sb.append("private Set _" + col.getName() + ";");
			}
		}

		// Class close brace

		sb.append("}");

		// Write file

		File modelFile = new File(_outputPath + "/service/persistence/" + entity.getName() + "HBM.java");

		writeFile(modelFile, sb.toString());
	}

	private void _createHBMUtil(Entity entity) throws IOException {
		List pkList = entity.getPKList();
		List columnList = entity.getColumnList();
		List finderList = entity.getFinderList();

		String pkClassName = entity.getPKClassName();
		String pkVarName = entity.getPKVarName();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.persistence;");

		// Class declaration

		sb.append("public class " + entity.getName() + "HBMUtil {");

		// Model methods

		sb.append("public static " + _packagePath + ".model." + entity.getName() + " model(" + entity.getName() + "HBM " + entity.getVarName() + "HBM) {");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() != null) {
				Entity tempEntity = getEntity(col.getEJBName());

				sb.append(_packagePath + ".model." + col.getEJBName() + " " + col.getName() + " = null;");

				sb.append("try {");
				sb.append(col.getName() + " = " + tempEntity.getName() + "Util.findByPrimaryKey((" + tempEntity.getPKClassName() + ")" + entity.getVarName() + "HBM.get" + col.getMethodName() + "().getPrimaryKey());");
				sb.append("}");
				sb.append("catch (Exception e) {");
				sb.append("e.printStackTrace();");
				sb.append("}");
			}
		}

		sb.append(_packagePath + ".model." + entity.getName() + " " + entity.getVarName() + " = " + entity.getName() + "Pool.get(" + entity.getVarName() + "HBM.getPrimaryKey());");
		sb.append("if (" + entity.getVarName() + " == null) {");
		sb.append(entity.getVarName() + " = new " + _packagePath + ".model." + entity.getName() + "(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() == null) {
				sb.append(entity.getVarName() + "HBM.get" + col.getMethodName() + "(), ");
			}
			else if (!col.isCollection() && col.getEJBName() != null) {
				sb.append(col.getName() + ", ");
			}
		}

		if (columnList.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(");");
		sb.append(entity.getName() + "Pool.put(" + entity.getVarName() + ".getPrimaryKey(), " + entity.getVarName() + ");");
		sb.append("}");
		sb.append("return " + entity.getVarName() + ";");
		sb.append("}");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/persistence/" + entity.getName() + "HBMUtil.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createHBMXML() throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			List pkList = entity.getPKList();
			List columnList = entity.getColumnList();
			List finderList = entity.getFinderList();

			if (entity.hasColumns()) {
				sb.append("\t<class name=\"" + _packagePath + ".service.persistence." + entity.getName() + "HBM\" table=\"" + entity.getTable() + "\">\n");
				sb.append("\t\t<cache usage=\"read-write\" />\n");

				if (entity.hasCompoundPK()) {
					sb.append("\t\t<composite-id name=\"primaryKey\" class=\"" + _packagePath + ".service.persistence." + entity.getName() + "PK\">\n");

					for (int j = 0; j < pkList.size(); j++) {
						EntityColumn col = (EntityColumn)pkList.get(j);

						sb.append("\t\t\t<key-property name=\"" + col.getName() + "\" ");

						if (!col.getName().equals(col.getDBName())) {
							sb.append("column=\"" + col.getDBName() + "\" />\n");
						}
						else {
							sb.append("/>\n");
						}
					}

					sb.append("\t\t</composite-id>\n");
				}
				else {
					EntityColumn col = (EntityColumn)pkList.get(0);

					sb.append("\t\t<id name=\"" + col.getName() + "\" type=\"java.lang." + col.getType() + "\">\n");
					sb.append("\t\t\t<generator class=\"assigned\" />\n");
					sb.append("\t\t</id>\n");
				}

				for (int j = 0; j < columnList.size(); j++) {
					EntityColumn col = (EntityColumn)columnList.get(j);

					if (!col.isPrimary() && !col.isCollection() && col.getEJBName() == null) {
						sb.append("\t\t<property name=\"" + col.getName() + "\" ");

						if (!col.getName().equals(col.getDBName())) {
							sb.append("column=\"" + col.getDBName() + "\" ");
						}

						if (col.isPrimitiveType()) {
							sb.append("type=\"com.liferay.util.dao.hibernate.");

							if (col.getType().equals("boolean")) {
								sb.append("Boolean");
							}
							else if (col.getType().equals("double")) {
								sb.append("Double");
							}
							else if (col.getType().equals("float")) {
								sb.append("Float");
							}
							else if (col.getType().equals("int")) {
								sb.append("Integer");
							}
							else if (col.getType().equals("long")) {
								sb.append("Long");
							}
							else if (col.getType().equals("short")) {
								sb.append("Short");
							}

							sb.append("Type\" ");
						}

						sb.append("/>\n");
					}
					else if (!col.isPrimary() && col.isCollection() && col.getEJBName() != null) {
						Entity tempEntity = getEntity(col.getEJBName());

						EntityColumn pk1 = (EntityColumn)pkList.get(0);
						EntityColumn pk2 = (EntityColumn)tempEntity.getPKList().get(0);

						if (col.isMappingOneToMany()) {
							sb.append("\t\t<set name=\"" + col.getName() + "\" lazy=\"true\">\n");
							sb.append("\t\t\t<key column=\"" + col.getMappingKey() + "\" />\n");
							sb.append("\t\t\t<one-to-many class=\"" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM\" />\n");
							sb.append("\t\t</set>\n");
						}
						else if (col.isMappingManyToMany()) {
							sb.append("\t\t<set name=\"" + col.getName() + "\" table=\"" + col.getMappingTable() + "\" lazy=\"true\">\n");
							sb.append("\t\t\t<key column=\"" + pk1.getName() + "\" />\n");
							sb.append("\t\t\t<many-to-many class=\"" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM\" column=\"" + pk2.getName() + "\" />\n");
							sb.append("\t\t</set>\n");
						}
					}
				}

				sb.append("\t</class>\n");
			}
		}

		File xmlFile = new File(_hbmFileName);

		if (!xmlFile.exists()) {
			String content =
				"<?xml version=\"1.0\"?>\n" +
				"<!DOCTYPE hibernate-mapping PUBLIC \"-//Hibernate/Hibernate Mapping DTD 3.0//EN\" \"http://hibernate.sourceforge.net/hibernate-mapping-3.0.dtd\">\n" +
				"\n" +
				"<hibernate-mapping default-lazy=\"false\">\n" +
				"</hibernate-mapping>";

			FileUtil.write(xmlFile, content);
		}

		String oldContent = FileUtil.read(xmlFile);
		String newContent = new String(oldContent);

		int firstClass = newContent.indexOf(
			"<class name=\"" + _packagePath + ".service.persistence.");
		int lastClass = newContent.lastIndexOf(
			"<class name=\"" + _packagePath + ".service.persistence.");

		if (firstClass == -1) {
			int x = newContent.indexOf("</hibernate-mapping>");
			newContent =
				newContent.substring(0, x) + sb.toString() +
				newContent.substring(x, newContent.length());
		}
		else {
			firstClass = newContent.lastIndexOf(
				"<class", firstClass) - 1;
			lastClass = newContent.indexOf(
				"</class>", lastClass) + 9;

			newContent =
				newContent.substring(0, firstClass) + sb.toString() +
				newContent.substring(lastClass, newContent.length());
		}

		if (!oldContent.equals(newContent)) {
			FileUtil.write(xmlFile, newContent);
		}
	}

	private void _createModel(Entity entity) throws IOException {
		List pkList = entity.getPKList();
		List columnList = entity.getColumnList();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".model;");

		// Imports

		if (entity.hasCompoundPK()) {
			sb.append("import " + _packagePath + ".service.persistence." + entity.getName() + "PK;");
		}

		sb.append("import com.liferay.portal.model.BaseModel;");
		sb.append("import com.liferay.portal.util.PropsUtil;");
		sb.append("import com.liferay.util.GetterUtil;");
		sb.append("import com.liferay.util.Xss;");
		sb.append("import java.util.Date;");

		// Class declaration

		sb.append("public class " + entity.getName() + "Model extends BaseModel {");

		// Fields

		sb.append("public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(\"value.object.cacheable." + _packagePath + ".model." + entity.getName() + "\"), VALUE_OBJECT_CACHEABLE);");

		sb.append("public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(\"value.object.max.size." + _packagePath + ".model." + entity.getName() + "\"), VALUE_OBJECT_MAX_SIZE);");

		sb.append("public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(\"xss.allow." + _packagePath + ".model." + entity.getName() + "\"), XSS_ALLOW);");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (col.getType().equals("String")) {
				sb.append("public static boolean XSS_ALLOW_" + col.getName().toUpperCase() + " = GetterUtil.get(PropsUtil.get(\"xss.allow." + _packagePath + ".model." + entity.getName() + "." + col.getName() + "\"), XSS_ALLOW_BY_MODEL);");
			}
		}

		sb.append("public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(\"lock.expiration.time." + _packagePath + ".model." + entity.getName() + "Model\"));");

		// Empty constructor

		sb.append("public " + entity.getName() + "Model() {");
		sb.append("}");

		// Primary key constructor

		sb.append("public " + entity.getName() + "Model(");

		if (entity.hasCompoundPK()) {
			sb.append(entity.getPKClassName() + " pk");
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append(col.getType() + " " + col.getName());
		}

		sb.append(") {");

		for (int i = 0; i < pkList.size(); i++) {
			EntityColumn col = (EntityColumn)pkList.get(i);

			sb.append("_" + col.getName() + " = " + (entity.hasCompoundPK() ? "pk." : "") + col.getName() + ";");
		}

		sb.append("setNew(true);");
		sb.append("}");

		// Complete constructor

		sb.append("public " + entity.getName() + "Model(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append(col.getType() + " " + col.getName() + ", ");
			}
		}

		if (columnList.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(") {");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append("_" + col.getName() + " = " + col.getName() + ";");
			}
		}

		sb.append("}");

		// Primary key accessor

		sb.append("public " + entity.getPKClassName() + " getPrimaryKey() {");

		if (entity.hasCompoundPK()) {
			sb.append("return new " + entity.getPKClassName() + "(");

			for (int i = 0; i < pkList.size(); i++) {
				EntityColumn col = (EntityColumn)pkList.get(i);

				sb.append("_" + col.getName());

				if ((i + 1) != (pkList.size())) {
					sb.append(", ");
				}
			}

			sb.append(");");
		}
		else {
			EntityColumn col = (EntityColumn)pkList.get(0);

			sb.append("return _" + col.getName() + ";");
		}

		sb.append("}");

		// Getter and setter methods

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append("public " + col.getType() + " get" + col.getMethodName() + "() {");
				sb.append("return _" + col.getName() + ";");
				sb.append("}");

				if (col.getType().equals("boolean")) {
					sb.append("public " + col.getType() + " is" + col.getMethodName() + "() {");
					sb.append("return _" + col.getName() + ";");
					sb.append("}");
				}

				sb.append("public void set" + col.getMethodName() + "(" + col.getType() + " " + col.getName() + ") {");
				sb.append("if (");

				if (!col.isPrimitiveType()) {
					sb.append("(" + col.getName() + " == null && _" + col.getName() + " != null) ||");
					sb.append("(" + col.getName() + " != null && _" + col.getName() + " == null) ||");
					sb.append("(" + col.getName() + " != null && _" + col.getName() + " != null && !" + col.getName() + ".equals(_" + col.getName() + "))");
				}
				else {
					sb.append(col.getName() + " != _" + col.getName());
				}

				sb.append(") {");

				if (col.getType().equals("String")) {
					sb.append("if (!XSS_ALLOW_" + col.getName().toUpperCase() + ") {");
					sb.append(col.getName() + " = Xss.strip(" + col.getName() + ");");
					sb.append("}");
				}

				sb.append("_" + col.getName() + " = " + col.getName() + ";");

				sb.append("setModified(true);");
				sb.append("}");
				sb.append("}");
			}
		}

		// Protect model

		sb.append("public BaseModel getProtected() {");
		sb.append("return null;");
		sb.append("}");

		sb.append("public void protect() {");
		sb.append("}");

		// Clone method

		sb.append("public Object clone() {");
		sb.append("return new " + entity.getName() + "(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() == null) {
				sb.append("get" + col.getMethodName() + "(), ");
			}
			else if (!col.isCollection() && col.getEJBName() != null) {
				sb.append("(" + col.getEJBName() + ")get" + col.getMethodName() + "().clone(), ");
			}
		}

		if (columnList.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(");");
		sb.append("}");

		// Compare to method

		sb.append("public int compareTo(Object obj) {");
		sb.append("if (obj == null) {");
		sb.append("return -1;");
		sb.append("}");
		sb.append(entity.getName() + " " + entity.getVarName() + " = (" + entity.getName() + ")obj;");

		if (entity.isOrdered()) {
			EntityOrder order = entity.getOrder();

			List orderList = order.getColumns();

			sb.append("int value = 0;");

			for (int i = 0; i < orderList.size(); i++) {
				EntityColumn col = (EntityColumn)orderList.get(i);

				if (!col.isPrimitiveType()) {
					if (col.isCaseSensitive()) {
						sb.append("value = get" + col.getMethodName() + "().compareTo(" + entity.getVarName() + ".get" + col.getMethodName() + "());");
					}
					else {
						sb.append("value = get" + col.getMethodName() + "().toLowerCase().compareTo(" + entity.getVarName() + ".get" + col.getMethodName() + "().toLowerCase());");
					}
				}
				else {
					sb.append("if (get" + col.getMethodName() + "() < " + entity.getVarName() + ".get" + col.getMethodName() + "()) {");
					sb.append("value = -1;");
					sb.append("}");
					sb.append("else if (get" + col.getMethodName() + "() > " + entity.getVarName() + ".get" + col.getMethodName() + "()) {");
					sb.append("value = 1;");
					sb.append("}");
					sb.append("else {");
					sb.append("value = 0;");
					sb.append("}");
				}

				if (!col.isOrderByAscending()) {
					sb.append("value = value * -1;");
				}

				sb.append("if (value != 0) {");
				sb.append("return value;");
				sb.append("}");
			}

			sb.append("return 0;");
		}
		else {
			sb.append(entity.getPKClassName() + " pk = " + entity.getVarName() + ".getPrimaryKey();");
			sb.append("return getPrimaryKey().compareTo(pk);");
		}

		sb.append("}");

		// Equals method

		sb.append("public boolean equals(Object obj) {");
		sb.append("if (obj == null) {");
		sb.append("return false;");
		sb.append("}");
		sb.append(entity.getName() + " " + entity.getVarName() + " = null;");
		sb.append("try {");
		sb.append(entity.getVarName() + " = (" + entity.getName() + ")obj;");
		sb.append("}");
		sb.append("catch (ClassCastException cce) {");
		sb.append("return false;");
		sb.append("}");
		sb.append(entity.getPKClassName() + " pk = " + entity.getVarName() + ".getPrimaryKey();");
		sb.append("if (getPrimaryKey().equals(pk)) {");
		sb.append("return true;");
		sb.append("}");
		sb.append("else {");
		sb.append("return false;");
		sb.append("}");
		sb.append("}");

		// Hash code method

		sb.append("public int hashCode() {");
		sb.append("return getPrimaryKey().hashCode();");
		sb.append("}");

		// Fields

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection()) {
				sb.append("private " + col.getType() + " _" + col.getName() + ";");
			}
		}

		// Class close brace

		sb.append("}");

		// Write file

		File modelFile = new File(_outputPath + "/model/" + entity.getName() + "Model.java");

		writeFile(modelFile, sb.toString());
	}

	private void _createPersistence(Entity entity) throws IOException {
		List pkList = entity.getPKList();
		List columnList = entity.getColumnList();
		List finderList = entity.getFinderList();

		String pkClassName = entity.getPKClassName();
		String pkVarName = entity.getPKVarName();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.persistence;");

		// Imports

		sb.append("import com.liferay.portal.PortalException;");
		sb.append("import com.liferay.portal.SystemException;");
		sb.append("import com.liferay.portal.util.HibernateUtil;");
		sb.append("import com.liferay.portal.service.persistence.BasePersistence;");
		sb.append("import com.liferay.util.StringPool;");
		sb.append("import com.liferay.util.StringUtil;");
		sb.append("import com.liferay.util.dao.hibernate.OrderByComparator;");
		sb.append("import com.liferay.util.lang.FastStringBuffer;");
		sb.append("import java.util.ArrayList;");
		sb.append("import java.util.Collection;");
		sb.append("import java.util.Collections;");
		sb.append("import java.util.Date;");
		sb.append("import java.util.HashSet;");
		sb.append("import java.util.Iterator;");
		sb.append("import java.util.List;");
		sb.append("import java.util.Set;");
		sb.append("import org.apache.commons.logging.Log;");
		sb.append("import org.apache.commons.logging.LogFactory;");
		sb.append("import org.hibernate.Hibernate;");
		sb.append("import org.hibernate.HibernateException;");
		sb.append("import org.hibernate.ObjectNotFoundException;");
		sb.append("import org.hibernate.Query;");
		sb.append("import org.hibernate.ScrollableResults;");
		sb.append("import org.hibernate.Session;");
		sb.append("import " + _packagePath + "." + _getNoSuchEntityException(entity) + "Exception;");

		// Class declaration

		sb.append("public class " + entity.getName() + "Persistence extends BasePersistence {");

		// Create method

		sb.append("public " + _packagePath + ".model." + entity.getName() + " create(" + entity.getPKClassName() + " " + pkVarName + ") {");
		sb.append("return new " + _packagePath + ".model." + entity.getName() + "(" + pkVarName + ");");
		sb.append("}");

		// Remove method

		sb.append("public " + _packagePath + ".model." + entity.getName() + " remove(" + pkClassName + " " + pkVarName + ") throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
		sb.append("Session session = null;");
		sb.append("try {");
		sb.append("session = openSession();");
		sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, " + pkVarName + ");");
		sb.append("if (" + entity.getVarName() + "HBM == null) {");
		sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + " + pkVarName + ".toString());");
		sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(" + pkVarName + ".toString());");
		sb.append("}");
		sb.append(_packagePath + ".model." + entity.getName() + " " + entity.getVarName() + " = " + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM);");
		sb.append("session.delete(" + entity.getVarName() + "HBM);");
		sb.append("session.flush();");
		sb.append(entity.getName() + "Pool.remove(" + pkVarName + ");");
		sb.append("return " + entity.getVarName() + ";");
		sb.append("}");
		sb.append("catch (HibernateException he) {");
		sb.append("throw new SystemException(he);");
		sb.append("}");
		sb.append("finally {");
		sb.append("HibernateUtil.closeSession(session);");
		sb.append("}");
		sb.append("}");

		// Update method

		sb.append("public " + _packagePath + ".model." + entity.getName() + " update(" + _packagePath + ".model." + entity.getName() + " " + entity.getVarName() + ") throws SystemException {");
		sb.append("Session session = null;");
		sb.append("try {");
		sb.append("if (" + entity.getVarName() + ".isNew() || " + entity.getVarName() + ".isModified()) {");
		sb.append("session = openSession();");
		sb.append("if (" + entity.getVarName() + ".isNew()) {");
		sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = new " + entity.getName() + "HBM(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() == null) {
				sb.append(entity.getVarName() + ".get" + col.getMethodName() + "(), ");
			}
		}

		if (sb.toString().endsWith(", ")) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(");");
		sb.append("session.save(" + entity.getVarName() + "HBM);");
		sb.append("session.flush();");
		sb.append("}");
		sb.append("else {");
		sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, " + entity.getVarName() + ".getPrimaryKey());");
		sb.append("if (" + entity.getVarName() + "HBM != null) {");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isPrimary() && !col.isCollection() && col.getEJBName() == null) {
				sb.append(entity.getVarName() + "HBM.set" + col.getMethodName() + "(" + entity.getVarName() + ".get" + col.getMethodName() + "());");
			}
		}

		sb.append("session.flush();");
		sb.append("}");
		sb.append("else {");
		sb.append(entity.getVarName() + "HBM = new " + entity.getName() + "HBM(");

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() == null) {
				sb.append(entity.getVarName() + ".get" + col.getMethodName() + "(), ");
			}
		}

		if (sb.toString().endsWith(", ")) {
			sb.delete(sb.length() - 2, sb.length());
		}

		sb.append(");");
		sb.append("session.save(" + entity.getVarName() + "HBM);");
		sb.append("session.flush();");
		sb.append("}");
		sb.append("}");

		/*
		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (!col.isCollection() && col.getEJBName() != null) {
				sb.append("try {");
				sb.append(entity.getVarName() + "EJB.set" + col.getMethodName() + "(" + col.getEJBName() + "HomeUtil.get" + col.getEJBName() + "Home().findByPrimaryKey(" + entity.getVarName() + ".get" + col.getMethodName() + "().getPrimaryKey()));");
				sb.append("}");
				sb.append("catch (FinderException fe) {");
				sb.append("fe.printStackTrace();");
				sb.append("}");
				sb.append("catch (NamingException ne) {");
				sb.append("ne.printStackTrace();");
				sb.append("}");
			}
		}
		*/

		sb.append(entity.getVarName() + ".setNew(false);");
		sb.append(entity.getVarName() + ".setModified(false);");
		sb.append(entity.getVarName() + ".protect();");
		sb.append(entity.getName() + "Pool.put(" + entity.getVarName() + ".getPrimaryKey(), " + entity.getVarName() + ");");
		sb.append("}");
		sb.append("return " + entity.getVarName() + ";");
		sb.append("}");
		sb.append("catch (HibernateException he) {");
		sb.append("throw new SystemException(he);");
		sb.append("}");
		sb.append("finally {");
		sb.append("HibernateUtil.closeSession(session);");
		sb.append("}");
		sb.append("}");

		// Relationship methods

		for (int i = 0; i < columnList.size(); i++) {
			EntityColumn col = (EntityColumn)columnList.get(i);

			if (col.isCollection() && col.isMappingManyToMany()) {
				Entity tempEntity = getEntity(col.getEJBName());
				EntityOrder tempOrder = tempEntity.getOrder();
				EntityColumn tempCol = tempEntity.getColumnByMappingTable(col.getMappingTable());

				// getUsers(String pk)

				sb.append("public List get" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("FastStringBuffer query = new FastStringBuffer();");
				sb.append("query.append(\"SELECT " + tempEntity.getVarName() + "HBM FROM \");");
				sb.append("query.append(" + entity.getPackagePath() + ".service.persistence." + entity.getName() + "HBM.class.getName());");
				sb.append("query.append(\" " + entity.getVarName() + "HBM \");");
				sb.append("query.append(\"JOIN " + entity.getVarName() + "HBM." + col.getName() + " AS " + tempEntity.getVarName() + "HBM \");");
				sb.append("query.append(\"WHERE " + entity.getVarName() + "HBM." + pkVarName + " = ? \");");

				if (tempOrder != null) {
					List tempOrderList = tempOrder.getColumns();

					sb.append("query.append(\"ORDER BY \");");

					for (int j = 0; j < tempOrderList.size(); j++) {
						EntityColumn tempOrderCol = null;

						if (tempOrderList.get(j) instanceof EntityColumn) {
							tempOrderCol = (EntityColumn)tempOrderList.get(j);
						}
						else {
							tempOrderCol = tempEntity.getColumn((String)tempOrderList.get(j));
						}

						sb.append("query.append(\"" + tempEntity.getVarName() + "HBM." + tempOrderCol.getDBName() + " " + (tempOrderCol.isOrderByAscending() ? "ASC" : "DESC") + "\")");

						if ((j + 1) != tempOrderList.size()) {
							sb.append(".append(\", \");");
						}
						else {
							sb.append(";");
						}
					}
				}

				sb.append("Query q = session.createQuery(query.toString());");
				sb.append("q.set" + pkClassName + "(0, pk);");

				sb.append("Iterator itr = q.list().iterator();");
				sb.append("List list = new ArrayList();");

				sb.append("while (itr.hasNext()) {");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)itr.next();");
				sb.append("list.add(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBMUtil.model(" + tempEntity.getVarName() + "HBM));");
				sb.append("}");

				sb.append("return list;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// getUsers(String pk, int begin, int end)

				sb.append("public List get" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, int begin, int end) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
				sb.append("return get" + tempEntity.getNames() + "(pk, begin, end, null);");
				sb.append("}");

				// getUsers(String pk, int begin, int end, OrderByComparator obc)

				sb.append("public List get" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, int begin, int end, OrderByComparator obc) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("FastStringBuffer query = new FastStringBuffer();");
				sb.append("query.append(\"SELECT " + tempEntity.getVarName() + "HBM FROM \");");
				sb.append("query.append(" + entity.getPackagePath() + ".service.persistence." + entity.getName() + "HBM.class.getName());");
				sb.append("query.append(\" " + entity.getVarName() + "HBM \");");
				sb.append("query.append(\"JOIN " + entity.getVarName() + "HBM." + col.getName() + " AS " + tempEntity.getVarName() + "HBM \");");
				sb.append("query.append(\"WHERE " + entity.getVarName() + "HBM." + pkVarName + " = ? \");");

				sb.append("if (obc != null) {");
				sb.append("query.append(\"ORDER BY \" + obc.getOrderBy());");
				sb.append("}");

				if (tempOrder != null) {
					List tempOrderList = tempOrder.getColumns();

					sb.append("else {");
					sb.append("query.append(\"ORDER BY \");");

					for (int j = 0; j < tempOrderList.size(); j++) {
						EntityColumn tempOrderCol = null;

						if (tempOrderList.get(j) instanceof EntityColumn) {
							tempOrderCol = (EntityColumn)tempOrderList.get(j);
						}
						else {
							tempOrderCol = tempEntity.getColumn((String)tempOrderList.get(j));
						}

						sb.append("query.append(\"" + tempEntity.getVarName() + "HBM." + tempOrderCol.getDBName() + " " + (tempOrderCol.isOrderByAscending() ? "ASC" : "DESC") + "\")");

						if ((j + 1) != tempOrderList.size()) {
							sb.append(".append(\", \");");
						}
						else {
							sb.append(";");
						}
					}

					sb.append("}");
				}

				sb.append("Query q = session.createQuery(query.toString());");
				sb.append("q.set" + pkClassName + "(0, pk);");

				sb.append("List list = new ArrayList();");

				sb.append("if (getDialect().supportsLimit()) {");

				sb.append("q.setMaxResults(end - begin);");
				sb.append("q.setFirstResult(begin);");
				sb.append("Iterator itr = q.list().iterator();");
				sb.append("while (itr.hasNext()) {");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)itr.next();");
				sb.append("list.add(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBMUtil.model(" + tempEntity.getVarName() + "HBM));");
				sb.append("}");

				sb.append("}");
				sb.append("else {");

				sb.append("ScrollableResults sr = q.scroll();");
				sb.append("if (sr.first() && sr.scroll(begin)) {");
				sb.append("for (int i = begin; i < end; i++) {");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)sr.get(0);");
				sb.append("list.add(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBMUtil.model(" + tempEntity.getVarName() + "HBM));");
				sb.append("if (!sr.next()) {");
				sb.append("break;");
				sb.append("}");
				sb.append("}");
				sb.append("}");

				sb.append("}");

				sb.append("return list;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// getUsersSize(String pk)

				sb.append("public int get" + tempEntity.getNames() + "Size(" + entity.getPKClassName() + " pk) throws SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append("FastStringBuffer query = new FastStringBuffer();");
				sb.append("query.append(\"SELECT COUNT(*) FROM \");");
				sb.append("query.append(" + entity.getPackagePath() + ".service.persistence." + entity.getName() + "HBM.class.getName());");
				sb.append("query.append(\" " + entity.getVarName() + "HBM \");");
				sb.append("query.append(\"JOIN " + entity.getVarName() + "HBM." + col.getName() + " AS " + tempEntity.getVarName() + "HBM \");");
				sb.append("query.append(\"WHERE " + entity.getVarName() + "HBM." + pkVarName + " = ? \");");

				sb.append("Query q = session.createQuery(query.toString());");
				sb.append("q.set" + pkClassName + "(0, pk);");

				sb.append("Iterator itr = q.iterate();");
				sb.append("if (itr.hasNext()) {");
				sb.append("Integer count = (Integer)itr.next();");
				sb.append("if (count != null) {");
				sb.append("return count.intValue();");
				sb.append("}");
				sb.append("}");
				sb.append("return 0;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// setUsers(String pk, String[] pks)

				sb.append("public void set" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPKClassName() + "[] pks) throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("Set " + col.getName() + "Set = new HashSet();");
				sb.append("for (int i = 0; pks != null && i < pks.length; i++) {");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, pks[i]);");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + pks[i].toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(pks[i].toString());");
				sb.append("}");
				sb.append(col.getName() + "Set.add(" + tempEntity.getVarName() + "HBM);");
				sb.append("}");
				sb.append(entity.getVarName() + "HBM.set" + col.getMethodName() + "(" + col.getName() + "Set);");
				sb.append("session.flush();");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// setUsers(String pk, List pks)

				sb.append("public void set" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, List " + col.getName() + ") throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("Set " + col.getName() + "Set = new HashSet();");
				sb.append("Iterator itr = " + col.getName() + ".iterator();");
				sb.append("while (itr.hasNext()) {");
				sb.append(tempEntity.getPackagePath() + ".model." + tempEntity.getName() + " " + tempEntity.getVarName() + " = (" + tempEntity.getPackagePath() + ".model." + tempEntity.getName() + ")itr.next();");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + ".getPrimaryKey());");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("}");
				sb.append(col.getName() + "Set.add(" + tempEntity.getVarName() + "HBM);");
				sb.append("}");
				sb.append(entity.getVarName() + "HBM.set" + col.getMethodName() + "(" + col.getName() + "Set);");
				sb.append("session.flush();");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// addUser(String pk, String userPK)

				sb.append("public boolean add" + tempEntity.getName() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPKClassName() + " " + tempEntity.getVarName() + "PK) throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + "PK);");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + "PK.toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + "PK.toString());");
				sb.append("}");
				sb.append("boolean value = " + entity.getVarName() + "HBM.get" + col.getMethodName() + "().add(" + tempEntity.getVarName() + "HBM);");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// addUser(String pk, User user)

				sb.append("public boolean add" + tempEntity.getName() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPackagePath() + ".model." + tempEntity.getName() + " " + tempEntity.getVarName() + ") throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + ".getPrimaryKey());");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("}");
				sb.append("boolean value = " + entity.getVarName() + "HBM.get" + col.getMethodName() + "().add(" + tempEntity.getVarName() + "HBM);");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// addUsers(String pk, String[] userPKs)

				sb.append("public boolean add" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPKClassName() + "[] " + tempEntity.getVarName() + "PKs) throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("boolean value = false;");
				sb.append("for (int i = 0; i < " + tempEntity.getVarName() + "PKs.length; i++) {");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + "PKs[i]);");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + "PKs[i].toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + "PKs[i].toString());");
				sb.append("}");
				sb.append("if (" + entity.getVarName() + "HBM.get" + col.getMethodName() + "().add(" + tempEntity.getVarName() + "HBM)) {");
				sb.append("value = true;");
				sb.append("}");
				sb.append("}");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// addUsers(String pk, List userPKs)

				sb.append("public boolean add" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, List " + tempEntity.getVarNames() + ") throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("boolean value = false;");
				sb.append("for (int i = 0; i < " + tempEntity.getVarNames() + ".size(); i++) {");
				sb.append(tempEntity.getPackagePath() + ".model." + tempEntity.getName() + " " + tempEntity.getVarName() + " = (" + tempEntity.getPackagePath() + ".model." + tempEntity.getName() + ")" + tempEntity.getVarNames() + ".get(i);");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + ".getPrimaryKey());");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("}");
				sb.append("if (" + entity.getVarName() + "HBM.get" + col.getMethodName() + "().add(" + tempEntity.getVarName() + "HBM)) {");
				sb.append("value = true;");
				sb.append("}");
				sb.append("}");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// clearUsers(String pk)

				sb.append("public void clear" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(entity.getVarName() + "HBM.get" + col.getMethodName() + "().clear();");
				sb.append("session.flush();");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// containsUser(String pk, String userPK)

				sb.append("public boolean contains" + tempEntity.getName() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPKClassName() + " " + tempEntity.getVarName() + "PK) throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + "PK);");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + "PK.toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + "PK.toString());");
				sb.append("}");
				sb.append("Collection c = " + entity.getVarName() + "HBM.get" + col.getMethodName() + "();");
				sb.append("return c.contains(" + tempEntity.getVarName() + "HBM);");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// containsUser(String pk, User user)

				sb.append("public boolean contains" + tempEntity.getName() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPackagePath() + ".model." + tempEntity.getName() + " " + tempEntity.getVarName() + ") throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + ".getPrimaryKey());");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("}");
				sb.append("Collection c = " + entity.getVarName() + "HBM.get" + col.getMethodName() + "();");
				sb.append("return c.contains(" + tempEntity.getVarName() + "HBM);");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// removeUser(String pk, String userPK)

				sb.append("public boolean remove" + tempEntity.getName() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPKClassName() + " " + tempEntity.getVarName() + "PK) throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + "PK);");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + "PK.toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + "PK.toString());");
				sb.append("}");
				sb.append("boolean value = " + entity.getVarName() + "HBM.get" + col.getMethodName() + "().remove(" + tempEntity.getVarName() + "HBM);");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// removeUser(String pk, User user)

				sb.append("public boolean remove" + tempEntity.getName() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPackagePath() + ".model." + tempEntity.getName() + " " + tempEntity.getVarName() + ") throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + ".getPrimaryKey());");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("}");
				sb.append("boolean value = " + entity.getVarName() + "HBM.get" + col.getMethodName() + "().remove(" + tempEntity.getVarName() + "HBM);");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// removeUsers(String pk, String[] userPKs)

				sb.append("public boolean remove" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, " + tempEntity.getPKClassName() + "[] " + tempEntity.getVarName() + "PKs) throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("boolean value = false;");
				sb.append("for (int i = 0; i < " + tempEntity.getVarName() + "PKs.length; i++) {");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = null;");
				sb.append(tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + "PKs[i]);");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + "PKs[i].toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + "PKs[i].toString());");
				sb.append("}");
				sb.append("if (" + entity.getVarName() + "HBM.get" + col.getMethodName() + "().remove(" + tempEntity.getVarName() + "HBM)) {");
				sb.append("value = true;");
				sb.append("}");
				sb.append("}");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				// removeUsers(String pk, List users)

				sb.append("public boolean remove" + tempEntity.getNames() + "(" + entity.getPKClassName() + " pk, List " + tempEntity.getVarNames() + ") throws " + _getNoSuchEntityException(entity) + "Exception, " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception, SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, pk);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + pk.toString());");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(pk.toString());");
				sb.append("}");
				sb.append("boolean value = false;");
				sb.append("for (int i = 0; i < " + tempEntity.getVarNames() + ".size(); i++) {");
				sb.append(tempEntity.getPackagePath() + ".model." + tempEntity.getName() + " " + tempEntity.getVarName() + " = (" + tempEntity.getPackagePath() + ".model." + tempEntity.getName() + ")" + tempEntity.getVarNames() + ".get(i);");
				sb.append(tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM " + tempEntity.getVarName() + "HBM = (" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM)session.get(" + tempEntity.getPackagePath() + ".service.persistence." + tempEntity.getName() + "HBM.class, " + tempEntity.getVarName() + ".getPrimaryKey());");
				sb.append("if (" + tempEntity.getVarName() + "HBM == null) {");
				sb.append("_log.warn(\"No " + tempEntity.getName() + " exists with the primary key of \" + " + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("throw new " + tempEntity.getPackagePath() + "." + _getNoSuchEntityException(tempEntity) + "Exception(" + tempEntity.getVarName() + ".getPrimaryKey().toString());");
				sb.append("}");
				sb.append("if (" + entity.getVarName() + "HBM.get" + col.getMethodName() + "().remove(" + tempEntity.getVarName() + "HBM)) {");
				sb.append("value = true;");
				sb.append("}");
				sb.append("}");
				sb.append("session.flush();");
				sb.append("return value;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");
			}
		}

		// Finder methods

		sb.append("public " + _packagePath + ".model." + entity.getName() + " findByPrimaryKey(" + pkClassName + " " + pkVarName + ") throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
		sb.append(_packagePath + ".model." + entity.getName() + " " + entity.getVarName() + " = " + entity.getName() + "Pool.get(" + pkVarName + ");");
		sb.append("Session session = null;");
		sb.append("try {");
		sb.append("if (" + entity.getVarName() + " == null) {");
		sb.append("session = openSession();");
		sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)session.get(" + entity.getName() + "HBM.class, " + pkVarName + ");");
		sb.append("if (" + entity.getVarName() + "HBM == null) {");
		sb.append("_log.warn(\"No " + entity.getName() + " exists with the primary key of \" + " + pkVarName + ".toString());");
		sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception(" + pkVarName + ".toString());");
		sb.append("}");
		sb.append(entity.getVarName() + " = " + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM);");
		sb.append("}");
		sb.append("return " + entity.getVarName() + ";");
		sb.append("}");
		sb.append("catch (HibernateException he) {");
		sb.append("throw new SystemException(he);");
		sb.append("}");
		sb.append("finally {");
		sb.append("HibernateUtil.closeSession(session);");
		sb.append("}");
		sb.append("}");

		for (int i = 0; i < finderList.size(); i++) {
			EntityFinder finder = (EntityFinder)finderList.get(i);

			List finderColsList = finder.getColumns();

			// Regular finder

			sb.append("public " + (finder.isCollection() ? "List" : _packagePath + ".model." + entity.getName()) + " findBy" + finder.getName() + "(");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append(col.getType() + "[] " + col.getName() + "Array");
				}
				else {
					sb.append(col.getType() + " " + col.getName());
				}

				if ((j + 1) != finderColsList.size()) {
					sb.append(", ");
				}
			}

			if (finder.isCollection()) {
				sb.append(") throws SystemException {");
			}
			else {
				sb.append(") throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
			}

			sb.append("Session session = null;");
			sb.append("try {");
			sb.append("session = openSession();");
			sb.append("FastStringBuffer query = new FastStringBuffer();");
			sb.append("query.append(\"FROM " + entity.getTable() + " IN CLASS " + _packagePath + ".service.persistence." + entity.getName() + "HBM WHERE \");");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append("query.append(\"(\");");

					sb.append("if (" + col.getName() + "Array.length > 0) {");

					sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
					sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
					sb.append("query.append(\" OR \");");
					sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
					sb.append("if ((i + 1) != " + col.getName() + "Array.length) {");
					sb.append("query.append(\" OR \");");
					sb.append("}");
					sb.append("}");

					sb.append("}");
					sb.append("else {");
					sb.append("query.append(\"" + col.getDBName() + " = \");");
					sb.append("query.append(\"" + col.getDBName() + "\");");
					sb.append("}");

					sb.append("query.append(\")\");");
				}
				else {
					sb.append("query.append(\"" + col.getDBName() + " = ?\");");
				}

				if ((j + 1) != finderColsList.size()) {
					sb.append("query.append(\" AND \");");
				}
				else if (Validator.isNull(finder.getWhere())) {
					sb.append("query.append(\" \");");
				}
				else {
					sb.append("query.append(\" AND " + finder.getWhere() + " \");");
				}
			}

			EntityOrder order = entity.getOrder();

			if (order != null) {
				List orderList = order.getColumns();

				sb.append("query.append(\"ORDER BY \");");

				for (int j = 0; j < orderList.size(); j++) {
					EntityColumn col = null;

					if (orderList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)orderList.get(j);
					}
					else {
						col = entity.getColumn((String)orderList.get(j));
					}

					sb.append("query.append(\"" + col.getDBName() + " " + (col.isOrderByAscending() ? "ASC" : "DESC") + "\")");

					if ((j + 1) != orderList.size()) {
						sb.append(".append(\", \");");
					}
					else {
						sb.append(";");
					}
				}
			}

			sb.append("Query q = session.createQuery(query.toString());");

			sb.append("int queryPos = 0;");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
					sb.append("q.setString(queryPos++, " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
					sb.append("q.setString(queryPos++, StringPool.PERCENT + StringPool.COMMA + " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
					sb.append("}");
				}
				else {
					String type = col.getType();

					if (col.isPrimitiveType()) {
						if (col.getType().equals("boolean")) {
							type = "Boolean";
						}
						else if (col.getType().equals("double")) {
							type = "Double";
						}
						else if (col.getType().equals("float")) {
							type = "Float";
						}
						else if (col.getType().equals("int")) {
							type = "Integer";
						}
						else if (col.getType().equals("long")) {
							type = "Long";
						}
						else if (col.getType().equals("short")) {
							type = "Short";
						}
					}

					sb.append("q.set" + type + "(queryPos++, " + col.getName());

					if (col.getType().equals("Boolean")) {
						sb.append(".booleanValue()");
					}
					else if (col.getType().equals("Integer")) {
						sb.append(".intValue()");
					}

					sb.append(");");
				}
			}

			sb.append("Iterator itr = q.list().iterator();");

			if (finder.isCollection()) {
				sb.append("List list = new ArrayList();");

				sb.append("while (itr.hasNext()) {");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)itr.next();");
				sb.append("list.add(" + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM));");
				sb.append("}");

				sb.append("return list;");
			}
			else {
				sb.append("if (!itr.hasNext()) {");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception();");
				sb.append("}");

				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)itr.next();");
				sb.append("return " + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM);");
			}

			sb.append("}");
			sb.append("catch (HibernateException he) {");
			sb.append("throw new SystemException(he);");
			sb.append("}");
			sb.append("finally {");
			sb.append("HibernateUtil.closeSession(session);");
			sb.append("}");
			sb.append("}");

			// Scrollable finder

			if (finder.isCollection()) {
				sb.append("public List findBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append(col.getType() + "[] " + col.getName() + "Array, ");
					}
					else {
						sb.append(col.getType() + " " + col.getName() + ", ");
					}
				}

				sb.append("int begin, int end) throws SystemException {");
				sb.append("return findBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("" + col.getName() + "Array, ");
					}
					else {
						sb.append("" + col.getName() + ", ");
					}
				}

				sb.append("begin, end, null);");
				sb.append("}");

				sb.append("public List findBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append(col.getType() + "[] " + col.getName() + "Array, ");
					}
					else {
						sb.append(col.getType() + " " + col.getName() + ", ");
					}
				}

				sb.append("int begin, int end, OrderByComparator obc) throws SystemException {");
				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append("FastStringBuffer query = new FastStringBuffer();");
				sb.append("query.append(\"FROM " + entity.getTable() + " IN CLASS " + _packagePath + ".service.persistence." + entity.getName() + "HBM WHERE \");");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("query.append(\"(\");");

						sb.append("if (" + col.getName() + "Array.length > 0) {");

						sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
						sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
						sb.append("query.append(\" OR \");");
						sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
						sb.append("if ((i + 1) != " + col.getName() + "Array.length) {");
						sb.append("query.append(\" OR \");");
						sb.append("}");
						sb.append("}");

						sb.append("}");
						sb.append("else {");
						sb.append("query.append(\"" + col.getDBName() + " = \");");
						sb.append("query.append(\"" + col.getDBName() + "\");");
						sb.append("}");

						sb.append("query.append(\")\");");
					}
					else {
						sb.append("query.append(\"" + col.getDBName() + " = ?\");");
					}

					if ((j + 1) != finderColsList.size()) {
						sb.append("query.append(\" AND \");");
					}
					else if (Validator.isNull(finder.getWhere())) {
						sb.append("query.append(\" \");");
					}
					else {
						sb.append("query.append(\" AND " + finder.getWhere() + " \");");
					}
				}

				sb.append("if (obc != null) {");
				sb.append("query.append(\"ORDER BY \" + obc.getOrderBy());");
				sb.append("}");

				if (order != null) {
					List orderList = order.getColumns();

					sb.append("else {");
					sb.append("query.append(\"ORDER BY \");");

					for (int j = 0; j < orderList.size(); j++) {
						EntityColumn col = null;

						if (orderList.get(j) instanceof EntityColumn) {
							col = (EntityColumn)orderList.get(j);
						}
						else {
							col = entity.getColumn((String)orderList.get(j));
						}

						sb.append("query.append(\"" + col.getDBName() + " " + (col.isOrderByAscending() ? "ASC" : "DESC") + "\")");

						if ((j + 1) != orderList.size()) {
							sb.append(".append(\", \");");
						}
						else {
							sb.append(";");
						}
					}

					sb.append("}");
				}

				sb.append("Query q = session.createQuery(query.toString());");

				sb.append("int queryPos = 0;");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
						sb.append("q.setString(queryPos++, " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
						sb.append("q.setString(queryPos++, StringPool.PERCENT + StringPool.COMMA + " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
						sb.append("}");
					}
					else {
						String type = col.getType();

						if (col.isPrimitiveType()) {
							if (col.getType().equals("boolean")) {
								type = "Boolean";
							}
							else if (col.getType().equals("double")) {
								type = "Double";
							}
							else if (col.getType().equals("float")) {
								type = "Float";
							}
							else if (col.getType().equals("int")) {
								type = "Integer";
							}
							else if (col.getType().equals("long")) {
								type = "Long";
							}
							else if (col.getType().equals("short")) {
								type = "Short";
							}
						}

						sb.append("q.set" + type + "(queryPos++, " + col.getName());

						if (col.getType().equals("Boolean")) {
							sb.append(".booleanValue()");
						}
						else if (col.getType().equals("Integer")) {
							sb.append(".intValue()");
						}

						sb.append(");");
					}
				}

				sb.append("List list = new ArrayList();");

				sb.append("if (getDialect().supportsLimit()) {");

				sb.append("q.setMaxResults(end - begin);");
				sb.append("q.setFirstResult(begin);");
				sb.append("Iterator itr = q.list().iterator();");
				sb.append("while (itr.hasNext()) {");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)itr.next();");
				sb.append("list.add(" + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM));");
				sb.append("}");

				sb.append("}");
				sb.append("else {");

				sb.append("ScrollableResults sr = q.scroll();");
				sb.append("if (sr.first() && sr.scroll(begin)) {");
				sb.append("for (int i = begin; i < end; i++) {");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)sr.get(0);");
				sb.append("list.add(" + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM));");
				sb.append("if (!sr.next()) {");
				sb.append("break;");
				sb.append("}");
				sb.append("}");
				sb.append("}");

				sb.append("}");

				sb.append("return list;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");

				sb.append("public " + _packagePath + ".model." + entity.getName() + " findBy" + finder.getName() + "_First(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append(col.getType() + "[] " + col.getName() + "Array, ");
					}
					else {
						sb.append(col.getType() + " " + col.getName() + ", ");
					}
				}

				sb.append("OrderByComparator obc) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");

				sb.append("List list = findBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("" + col.getName() + "Array, ");
					}
					else {
						sb.append("" + col.getName() + ", ");
					}
				}

				sb.append("0, 1, obc);");

				sb.append("if (list.size() == 0) {");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception();");
				sb.append("}");
				sb.append("else {");
				sb.append("return (" + _packagePath + ".model." + entity.getName() + ")list.get(0);");
				sb.append("}");
				sb.append("}");

				sb.append("public " + _packagePath + ".model." + entity.getName() + " findBy" + finder.getName() + "_Last(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append(col.getType() + "[] " + col.getName() + "Array, ");
					}
					else {
						sb.append(col.getType() + " " + col.getName() + ", ");
					}
				}

				sb.append("OrderByComparator obc) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");

				sb.append("int count = countBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("" + col.getName() + "Array");
					}
					else {
						sb.append("" + col.getName());
					}

					if ((j + 1) != finderColsList.size()) {
						sb.append(", ");
					}
				}

				sb.append(");");

				sb.append("List list = findBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("" + col.getName() + "Array, ");
					}
					else {
						sb.append("" + col.getName() + ", ");
					}
				}

				sb.append("count - 1, count, obc);");

				sb.append("if (list.size() == 0) {");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception();");
				sb.append("}");
				sb.append("else {");
				sb.append("return (" + _packagePath + ".model." + entity.getName() + ")list.get(0);");
				sb.append("}");
				sb.append("}");

				sb.append("public " + _packagePath + ".model." + entity.getName() + "[] findBy" + finder.getName() + "_PrevAndNext(" + pkClassName + " " + pkVarName + ", ");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append(col.getType() + "[] " + col.getName() + "Array, ");
					}
					else {
						sb.append(col.getType() + " " + col.getName() + ", ");
					}
				}

				sb.append("OrderByComparator obc) throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
				sb.append(_packagePath + ".model." + entity.getName() + " " + entity.getVarName() + " = findByPrimaryKey(" + pkVarName + ");");

				sb.append("int count = countBy" + finder.getName() + "(");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("" + col.getName() + "Array");
					}
					else {
						sb.append("" + col.getName());
					}

					if ((j + 1) != finderColsList.size()) {
						sb.append(", ");
					}
				}

				sb.append(");");

				sb.append("Session session = null;");
				sb.append("try {");
				sb.append("session = openSession();");
				sb.append("FastStringBuffer query = new FastStringBuffer();");
				sb.append("query.append(\"FROM " + entity.getTable() + " IN CLASS " + _packagePath + ".service.persistence." + entity.getName() + "HBM WHERE \");");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("query.append(\"(\");");

						sb.append("if (" + col.getName() + "Array.length > 0) {");

						sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
						sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
						sb.append("query.append(\" OR \");");
						sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
						sb.append("if ((i + 1) != " + col.getName() + "Array.length) {");
						sb.append("query.append(\" OR \");");
						sb.append("}");
						sb.append("}");

						sb.append("}");
						sb.append("else {");
						sb.append("query.append(\"" + col.getDBName() + " = \");");
						sb.append("query.append(\"" + col.getDBName() + "\");");
						sb.append("}");

						sb.append("query.append(\")\");");
					}
					else {
						sb.append("query.append(\"" + col.getDBName() + " = ?\");");
					}

					if ((j + 1) != finderColsList.size()) {
						sb.append("query.append(\" AND \");");
					}
					else if (Validator.isNull(finder.getWhere())) {
						sb.append("query.append(\" \");");
					}
					else {
						sb.append("query.append(\" AND " + finder.getWhere() + " \");");
					}
				}

				sb.append("if (obc != null) {");
				sb.append("query.append(\"ORDER BY \" + obc.getOrderBy());");
				sb.append("}");

				if (order != null) {
					List orderList = order.getColumns();

					sb.append("else {");
					sb.append("query.append(\"ORDER BY \");");

					for (int j = 0; j < orderList.size(); j++) {
						EntityColumn col = null;

						if (orderList.get(j) instanceof EntityColumn) {
							col = (EntityColumn)orderList.get(j);
						}
						else {
							col = entity.getColumn((String)orderList.get(j));
						}

						sb.append("query.append(\"" + col.getDBName() + " " + (col.isOrderByAscending() ? "ASC" : "DESC") + "\")");

						if ((j + 1) != orderList.size()) {
							sb.append(".append(\", \");");
						}
						else {
							sb.append(";");
						}
					}

					sb.append("}");
				}

				sb.append("Query q = session.createQuery(query.toString());");

				sb.append("int queryPos = 0;");

				for (int j = 0; j < finderColsList.size(); j++) {
					EntityColumn col = null;

					if (finderColsList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)finderColsList.get(j);
					}
					else {
						String finderColName = (String)finderColsList.get(j);

						col = entity.getColumn(finderColName);
					}

					if (col.isCheckArray()) {
						sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
						sb.append("q.setString(queryPos++, " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
						sb.append("q.setString(queryPos++, StringPool.PERCENT + StringPool.COMMA + " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
						sb.append("}");
					}
					else {
						String type = col.getType();

						if (col.isPrimitiveType()) {
							if (col.getType().equals("boolean")) {
								type = "Boolean";
							}
							else if (col.getType().equals("double")) {
								type = "Double";
							}
							else if (col.getType().equals("float")) {
								type = "Float";
							}
							else if (col.getType().equals("int")) {
								type = "Integer";
							}
							else if (col.getType().equals("long")) {
								type = "Long";
							}
							else if (col.getType().equals("short")) {
								type = "Short";
							}
						}

						sb.append("q.set" + type + "(queryPos++, " + col.getName());

						if (col.getType().equals("Boolean")) {
							sb.append(".booleanValue()");
						}
						else if (col.getType().equals("Integer")) {
							sb.append(".intValue()");
						}

						sb.append(");");
					}
				}

				sb.append(_packagePath + ".model." + entity.getName() + "[] array = new " + _packagePath + ".model." + entity.getName() + "[3];");

				sb.append("ScrollableResults sr = q.scroll();");
				sb.append("if (sr.first()) {");
				sb.append("while (true) {");
				sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)sr.get(0);");
				sb.append("if (" + entity.getVarName() + "HBM == null) {");
				sb.append("break;");
				sb.append("}");
				sb.append(_packagePath + ".model." + entity.getName() + " cur" + entity.getName() + " = " + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM);");
				sb.append("int value = obc.compare(" + entity.getVarName() + ", cur" + entity.getName() + ");");
				sb.append("if (value == 0) {");
				sb.append("if (!" + entity.getVarName() + ".equals(cur" + entity.getName() + ")) {");
				sb.append("break;");
				sb.append("}");
				sb.append("array[1] = cur" + entity.getName() + ";");
				sb.append("if (sr.previous()) {");
				sb.append("array[0] = " + entity.getName() + "HBMUtil.model((" + entity.getName() + "HBM)sr.get(0));");
				sb.append("}");
				sb.append("sr.next();");
				sb.append("if (sr.next()) {");
				sb.append("array[2] = " + entity.getName() + "HBMUtil.model((" + entity.getName() + "HBM)sr.get(0));");
				sb.append("}");
				sb.append("break;");
				sb.append("}");
				sb.append("if (count == 1) {");
				sb.append("break;");
				sb.append("}");
				sb.append("count = (int)Math.ceil(count / 2.0);");
				sb.append("if (value < 0) {");
				sb.append("if (!sr.scroll(count * -1)) {");
				sb.append("break;");
				sb.append("}");
				sb.append("}");
				sb.append("else {");
				sb.append("if (!sr.scroll(count)) {");
				sb.append("break;");
				sb.append("}");
				sb.append("}");
				sb.append("}");
				sb.append("}");

				sb.append("return array;");
				sb.append("}");
				sb.append("catch (HibernateException he) {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
				sb.append("finally {");
				sb.append("HibernateUtil.closeSession(session);");
				sb.append("}");
				sb.append("}");
			}
		}

		sb.append("public List findAll() throws SystemException {");
		sb.append("Session session = null;");
		sb.append("try {");
		sb.append("session = openSession();");
		sb.append("FastStringBuffer query = new FastStringBuffer();");
		sb.append("query.append(\"FROM " + entity.getTable() + " IN CLASS " + _packagePath + ".service.persistence." + entity.getName() + "HBM \");");

		EntityOrder order = entity.getOrder();

		if (order != null) {
			List orderList = order.getColumns();

			sb.append("query.append(\"ORDER BY \");");

			for (int j = 0; j < orderList.size(); j++) {
				EntityColumn col = null;

				if (orderList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)orderList.get(j);
				}
				else {
					col = entity.getColumn((String)orderList.get(j));
				}

				sb.append("query.append(\"" + col.getDBName() + " " + (col.isOrderByAscending() ? "ASC" : "DESC") + "\")");

				if ((j + 1) != orderList.size()) {
					sb.append(".append(\", \");");
				}
				else {
					sb.append(";");
				}
			}
		}

		sb.append("Query q = session.createQuery(query.toString());");

		sb.append("Iterator itr = q.iterate();");
		sb.append("List list = new ArrayList();");

		sb.append("while (itr.hasNext()) {");
		sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)itr.next();");
		sb.append("list.add(" + entity.getName() + "HBMUtil.model(" + entity.getVarName() + "HBM));");
		sb.append("}");

		sb.append("return list;");
		sb.append("}");
		sb.append("catch (HibernateException he) {");
		sb.append("throw new SystemException(he);");
		sb.append("}");
		sb.append("finally {");
		sb.append("HibernateUtil.closeSession(session);");
		sb.append("}");
		sb.append("}");

		// Remove by methods

		for (int i = 0; i < finderList.size(); i++) {
			EntityFinder finder = (EntityFinder)finderList.get(i);

			List finderColsList = finder.getColumns();

			sb.append("public void removeBy" + finder.getName() + "(");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append(col.getType() + "[] " + col.getName() + "Array");
				}
				else {
					sb.append(col.getType() + " " + col.getName());
				}

				if ((j + 1) != finderColsList.size()) {
					sb.append(", ");
				}
			}

			if (finder.isCollection()) {
				sb.append(") throws SystemException {");
			}
			else {
				sb.append(") throws " + _getNoSuchEntityException(entity) + "Exception, SystemException {");
			}

			sb.append("Session session = null;");
			sb.append("try {");
			sb.append("session = openSession();");
			sb.append("FastStringBuffer query = new FastStringBuffer();");
			sb.append("query.append(\"FROM " + entity.getTable() + " IN CLASS " + _packagePath + ".service.persistence." + entity.getName() + "HBM WHERE \");");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append("query.append(\"(\");");

					sb.append("if (" + col.getName() + "Array.length > 0) {");

					sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
					sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
					sb.append("query.append(\" OR \");");
					sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
					sb.append("if ((i + 1) != " + col.getName() + "Array.length) {");
					sb.append("query.append(\" OR \");");
					sb.append("}");
					sb.append("}");

					sb.append("}");
					sb.append("else {");
					sb.append("query.append(\"" + col.getDBName() + " = \");");
					sb.append("query.append(\"" + col.getDBName() + "\");");
					sb.append("}");

					sb.append("query.append(\")\");");
				}
				else {
					sb.append("query.append(\"" + col.getDBName() + " = ?\");");
				}

				if ((j + 1) != finderColsList.size()) {
					sb.append("query.append(\" AND \");");
				}
				else if (Validator.isNull(finder.getWhere())) {
					sb.append("query.append(\" \");");
				}
				else {
					sb.append("query.append(\" AND " + finder.getWhere() + " \");");
				}
			}

			if (order != null) {
				List orderList = order.getColumns();

				sb.append("query.append(\"ORDER BY \");");

				for (int j = 0; j < orderList.size(); j++) {
					EntityColumn col = null;

					if (orderList.get(j) instanceof EntityColumn) {
						col = (EntityColumn)orderList.get(j);
					}
					else {
						col = entity.getColumn((String)orderList.get(j));
					}

					sb.append("query.append(\"" + col.getDBName() + " " + (col.isOrderByAscending() ? "ASC" : "DESC") + "\")");

					if ((j + 1) != orderList.size()) {
						sb.append(".append(\", \");");
					}
					else {
						sb.append(";");
					}
				}
			}

			sb.append("Query q = session.createQuery(query.toString());");

			sb.append("int queryPos = 0;");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
					sb.append("q.setString(queryPos++, " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
					sb.append("q.setString(queryPos++, StringPool.PERCENT + StringPool.COMMA + " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
					sb.append("}");
				}
				else {
					String type = col.getType();

					if (col.isPrimitiveType()) {
						if (col.getType().equals("boolean")) {
							type = "Boolean";
						}
						else if (col.getType().equals("double")) {
							type = "Double";
						}
						else if (col.getType().equals("float")) {
							type = "Float";
						}
						else if (col.getType().equals("int")) {
							type = "Integer";
						}
						else if (col.getType().equals("long")) {
							type = "Long";
						}
						else if (col.getType().equals("short")) {
							type = "Short";
						}
					}

					sb.append("q.set" + type + "(queryPos++, " + col.getName());

					if (col.getType().equals("Boolean")) {
						sb.append(".booleanValue()");
					}
					else if (col.getType().equals("Integer")) {
						sb.append(".intValue()");
					}

					sb.append(");");
				}
			}

			sb.append("Iterator itr = q.list().iterator();");
			sb.append("while (itr.hasNext()) {");
			sb.append(entity.getName() + "HBM " + entity.getVarName() + "HBM = (" + entity.getName() + "HBM)itr.next();");
			sb.append(entity.getName() + "Pool.remove((" + pkClassName + ")" + entity.getVarName() + "HBM.getPrimaryKey());");
			sb.append("session.delete(" + entity.getVarName() + "HBM);");
			sb.append("}");

			sb.append("session.flush();");
			sb.append("}");
			sb.append("catch (HibernateException he) {");

			if (finder.isCollection()) {
				sb.append("throw new SystemException(he);");
			}
			else {
				sb.append("if (he instanceof ObjectNotFoundException) {");
				sb.append("throw new " + _getNoSuchEntityException(entity) + "Exception();");
				sb.append("}");
				sb.append("else {");
				sb.append("throw new SystemException(he);");
				sb.append("}");
			}

			sb.append("}");
			sb.append("finally {");
			sb.append("HibernateUtil.closeSession(session);");
			sb.append("}");
			sb.append("}");
		}

		// Count by methods

		for (int i = 0; i < finderList.size(); i++) {
			EntityFinder finder = (EntityFinder)finderList.get(i);

			List finderColsList = finder.getColumns();

			sb.append("public int countBy" + finder.getName() + "(");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append(col.getType() + "[] " + col.getName() + "Array");
				}
				else {
					sb.append(col.getType() + " " + col.getName());
				}

				if ((j + 1) != finderColsList.size()) {
					sb.append(", ");
				}
			}

			sb.append(") throws SystemException {");
			sb.append("Session session = null;");
			sb.append("try {");
			sb.append("session = openSession();");
			sb.append("FastStringBuffer query = new FastStringBuffer();");
			sb.append("query.append(\"SELECT COUNT(*) \");");
			sb.append("query.append(\"FROM " + entity.getTable() + " IN CLASS " + _packagePath + ".service.persistence." + entity.getName() + "HBM WHERE \");");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append("query.append(\"(\");");

					sb.append("if (" + col.getName() + "Array.length > 0) {");

					sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
					sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
					sb.append("query.append(\" OR \");");
					sb.append("query.append(\"" + col.getDBName() + " LIKE ?\");");
					sb.append("if ((i + 1) != " + col.getName() + "Array.length) {");
					sb.append("query.append(\" OR \");");
					sb.append("}");
					sb.append("}");

					sb.append("}");
					sb.append("else {");
					sb.append("query.append(\"" + col.getDBName() + " = \");");
					sb.append("query.append(\"" + col.getDBName() + "\");");
					sb.append("}");

					sb.append("query.append(\")\");");
				}
				else {
					sb.append("query.append(\"" + col.getDBName() + " = ?\");");
				}

				if ((j + 1) != finderColsList.size()) {
					sb.append("query.append(\" AND \");");
				}
				else if (Validator.isNull(finder.getWhere())) {
					sb.append("query.append(\" \");");
				}
				else {
					sb.append("query.append(\" AND " + finder.getWhere() + " \");");
				}
			}

			sb.append("Query q = session.createQuery(query.toString());");

			sb.append("int queryPos = 0;");

			for (int j = 0; j < finderColsList.size(); j++) {
				EntityColumn col = null;

				if (finderColsList.get(j) instanceof EntityColumn) {
					col = (EntityColumn)finderColsList.get(j);
				}
				else {
					String finderColName = (String)finderColsList.get(j);

					col = entity.getColumn(finderColName);
				}

				if (col.isCheckArray()) {
					sb.append("for (int i = 0; i < " + col.getName() + "Array.length; i++) {");
					sb.append("q.setString(queryPos++, " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
					sb.append("q.setString(queryPos++, StringPool.PERCENT + StringPool.COMMA + " + col.getName() + "Array[i] + StringPool.COMMA + StringPool.PERCENT);");
					sb.append("}");
				}
				else {
					String type = col.getType();

					if (col.isPrimitiveType()) {
						if (col.getType().equals("boolean")) {
							type = "Boolean";
						}
						else if (col.getType().equals("double")) {
							type = "Double";
						}
						else if (col.getType().equals("float")) {
							type = "Float";
						}
						else if (col.getType().equals("int")) {
							type = "Integer";
						}
						else if (col.getType().equals("long")) {
							type = "Long";
						}
						else if (col.getType().equals("short")) {
							type = "Short";
						}
					}

					sb.append("q.set" + type + "(queryPos++, " + col.getName());

					if (col.getType().equals("Boolean")) {
						sb.append(".booleanValue()");
					}
					else if (col.getType().equals("Integer")) {
						sb.append(".intValue()");
					}

					sb.append(");");
				}
			}

			sb.append("Iterator itr = q.list().iterator();");
			sb.append("if (itr.hasNext()) {");
			sb.append("Integer count = (Integer)itr.next();");
			sb.append("if (count != null) {");
			sb.append("return count.intValue();");
			sb.append("}");
			sb.append("}");
			sb.append("return 0;");
			sb.append("}");
			sb.append("catch (HibernateException he) {");
			sb.append("throw new SystemException(he);");
			sb.append("}");
			sb.append("finally {");
			sb.append("HibernateUtil.closeSession(session);");
			sb.append("}");
			sb.append("}");
		}

		// Fields

		sb.append("private static final Log _log = LogFactory.getLog(" + entity.getName() + "Persistence.class);");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/persistence/" + entity.getName() + "Persistence.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createPersistenceUtil(Entity entity) throws IOException {
		XClass xClass = _getXClass(_outputPath + "/service/persistence/" + entity.getName() + "Persistence.java");

		List methods = xClass.getMethods();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.persistence;");

		// Imports

		sb.append("import com.liferay.portal.model.ModelListener;");
		sb.append("import com.liferay.portal.util.PropsUtil;");
		sb.append("import com.liferay.util.GetterUtil;");
		sb.append("import com.liferay.util.InstancePool;");
		sb.append("import com.liferay.util.Validator;");
		sb.append("import org.apache.commons.logging.Log;");
		sb.append("import org.apache.commons.logging.LogFactory;");

		// Class declaration

		sb.append("public class " + entity.getName() + "Util {");

		// Fields

		sb.append("public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(\"value.object.persistence." + _packagePath + ".model." + entity.getName() + "\"), \"" + entity.getPersistenceClass() + "\");");
		sb.append("public static String LISTENER = GetterUtil.getString(PropsUtil.get(\"value.object.listener." + _packagePath + ".model." + entity.getName() + "\"));");

		// Methods

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			String methodName = xMethod.getName();

			sb.append("public static " + xMethod.getReturnType().getType().getQualifiedName() + xMethod.getReturnType().getDimensionAsString() + " " + methodName + "(");

			List parameters = xMethod.getParameters();

			String p0Name = "";
			if (parameters.size() > 0) {
				p0Name = ((XParameter)parameters.get(0)).getName();
			}

			for (int j = 0; j < parameters.size(); j++) {
				XParameter xParameter = (XParameter)parameters.get(j);

				sb.append(xParameter.getType().getQualifiedName() + xParameter.getDimensionAsString() + " " + xParameter.getName());

				if ((j + 1) != parameters.size()) {
					sb.append(", ");
				}
			}

			sb.append(")");

			List thrownExceptions = xMethod.getThrownExceptions();

			if (thrownExceptions.size() > 0) {
				sb.append(" throws ");

				Iterator itr = thrownExceptions.iterator();

				while (itr.hasNext()) {
					XClass thrownException = (XClass)itr.next();

					sb.append(thrownException.getQualifiedName());

					if (itr.hasNext()) {
						sb.append(", ");
					}
				}
			}

			sb.append(" {");

			sb.append(entity.getName() + "Persistence persistence = (" + entity.getName() + "Persistence)InstancePool.get(PERSISTENCE);");

			if (methodName.equals("remove") || methodName.equals("update")) {
				sb.append("ModelListener listener = null;");

				sb.append("if (Validator.isNotNull(LISTENER)) {");

				sb.append("try {");
				sb.append("listener = (ModelListener)Class.forName(LISTENER).newInstance();");
				sb.append("}");
				sb.append("catch (Exception e) {");
				sb.append("_log.error(e.getMessage());");
				sb.append("}");

				sb.append("}");

				if (methodName.equals("update")) {
					sb.append("boolean isNew = " + p0Name + ".isNew();");
				}

				sb.append("if (listener != null) {");

				if (methodName.equals("remove")) {
					sb.append("listener.onBeforeRemove(findByPrimaryKey(" + p0Name + "));");
				}
				else {
					sb.append("if (isNew) {");
					sb.append("listener.onBeforeCreate(" + p0Name + ");");
					sb.append("}");
					sb.append("else {");
					sb.append("listener.onBeforeUpdate(" + p0Name + ");");
					sb.append("}");
				}

				sb.append("}");

				if (methodName.equals("remove")) {
					sb.append(_packagePath + ".model." + entity.getName() + " " + entity.getVarName() + " = ");
				}
				else {
					sb.append(entity.getVarName() + " = ");
				}
			}
			else {
				if (!xMethod.getReturnType().getType().getQualifiedName().equals("void")) {
					sb.append("return ");
				}
			}

			sb.append("persistence." + methodName + "(");

			for (int j = 0; j < parameters.size(); j++) {
				XParameter xParameter = (XParameter)parameters.get(j);

				sb.append(xParameter.getName());

				if ((j + 1) != parameters.size()) {
					sb.append(", ");
				}
			}

			sb.append(");");

			if (methodName.equals("remove") || methodName.equals("update")) {
				sb.append("if (listener != null) {");

				if (methodName.equals("remove")) {
					sb.append("listener.onAfterRemove(" + entity.getVarName() + ");");
				}
				else {
					sb.append("if (isNew) {");
					sb.append("listener.onAfterCreate(" + entity.getVarName() + ");");
					sb.append("}");
					sb.append("else {");
					sb.append("listener.onAfterUpdate(" + entity.getVarName() + ");");
					sb.append("}");
				}

				sb.append("}");

				sb.append("return " + entity.getVarName() + ";");
			}

			sb.append("}");
		}

		// Fields

		sb.append("private static final Log _log = LogFactory.getLog(" + entity.getName() + "Util.class);");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/persistence/" + entity.getName() + "Util.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createPool(Entity entity) throws IOException {
		List pkList = entity.getPKList();
		List columnList = entity.getColumnList();

		String pkClassName = entity.getPKClassName();
		String pkVarName = entity.getPKVarName();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.persistence;");

		// Imports

		sb.append("import " + _packagePath + ".model." + entity.getName() + ";");

		if (!_packagePath.equals("com.liferay.portal")) {
			sb.append("import com.liferay.portal.service.persistence.GlobalPool;");
		}

		sb.append("import com.liferay.portal.util.PropsUtil;");
		sb.append("import com.liferay.util.GetterUtil;");
		sb.append("import com.liferay.util.SystemProperties;");
		sb.append("import com.liferay.util.Validator;");
		sb.append("import com.opensymphony.oscache.base.NeedsRefreshException;");
		sb.append("import com.opensymphony.oscache.general.GeneralCacheAdministrator;");

		// Class declaration

		sb.append("public class " + entity.getName() + "Pool {");

		// Protected methods

		sb.append("public static void clear() {");
		sb.append("_instance._clear();");
		sb.append("}");

		sb.append("public static " + entity.getName() + " get(" + pkClassName + " " + pkVarName + ") {");
		sb.append("return _instance._get(" + pkVarName + ");");
		sb.append("}");

		sb.append("public static " + entity.getName() + " put(" + pkClassName + " " + pkVarName + ", " + entity.getName() + " obj) {");
		sb.append("return _instance._put(" + pkVarName + ", obj);");
		sb.append("}");

		sb.append("public static " + entity.getName() + " remove(" + pkClassName + " " + pkVarName + ") {");
		sb.append("return _instance._remove(" + pkVarName + ");");
		sb.append("}");

		// Private constructor

		sb.append("private " + entity.getName() + "Pool() {");
		sb.append("_cacheable = " + entity.getName() + ".CACHEABLE;");
		sb.append("int maxSize = " + entity.getName() + ".MAX_SIZE;");
		sb.append("_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());");
		sb.append("_cache.getCache().setCapacity(maxSize);");
		sb.append("GlobalPool.registerPool(" + entity.getName() + "Pool.class.getName()" + ");");
		sb.append("}");

		// Private methods

		sb.append("private void _clear() {");
		sb.append("_cache.flushAll();");
		sb.append("}");

		sb.append("private " + entity.getName() + " _get(" + pkClassName + " " + pkVarName + ") {");
		sb.append("if (!_cacheable) {");
		sb.append("return null;");
		sb.append("}");
		sb.append("else if (" + pkVarName + " == null) {");
		sb.append("return null;");
		sb.append("}");
		sb.append("else {");
		sb.append(entity.getName() + " obj = null;");
		sb.append("String key = " + pkVarName + ".toString();");
		sb.append("if (Validator.isNull(key)) {");
		sb.append("return null;");
		sb.append("}");
		sb.append("try {");
		sb.append("obj = (" + entity.getName() + ")_cache.getFromCache(key);");
		sb.append("}");
		sb.append("catch (NeedsRefreshException nfe) {");
		sb.append("}");
		sb.append("finally {");
		sb.append("if (obj == null) {");
		sb.append("_cache.cancelUpdate(key);");
		sb.append("}");
		sb.append("}");
		sb.append("return obj;");
		sb.append("}");
		sb.append("}");

		sb.append("private " + entity.getName() + " _put(" + pkClassName + " " + pkVarName + ", " + entity.getName() + " obj) {");
		sb.append("if (!_cacheable) {");
		sb.append("return obj;");
		sb.append("}");
		sb.append("else if (" + pkVarName + " == null) {");
		sb.append("return obj;");
		sb.append("}");
		sb.append("else {");
		sb.append("String key = " + pkVarName + ".toString();");
		sb.append("if (Validator.isNotNull(key)) {");
		sb.append("_cache.flushEntry(key);");
		sb.append("_cache.putInCache(key, obj);");
		sb.append("}");
		sb.append("return obj;");
		sb.append("}");
		sb.append("}");

		sb.append("private " + entity.getName() + " _remove(" + pkClassName + " " + pkVarName + ") {");
		sb.append("if (!_cacheable) {");
		sb.append("return null;");
		sb.append("}");
		sb.append("else if (" + pkVarName + " == null) {");
		sb.append("return null;");
		sb.append("}");
		sb.append("else {");
		sb.append(entity.getName() + " obj = null;");
		sb.append("String key = " + pkVarName + ".toString();");
		sb.append("if (Validator.isNull(key)) {");
		sb.append("return null;");
		sb.append("}");
		sb.append("try {");
		sb.append("obj = (" + entity.getName() + ")_cache.getFromCache(key);");
		sb.append("_cache.flushEntry(key);");
		sb.append("}");
		sb.append("catch (NeedsRefreshException nfe) {");
		sb.append("}");
		sb.append("finally {");
		sb.append("if (obj == null) {");
		sb.append("_cache.cancelUpdate(key);");
		sb.append("}");
		sb.append("}");
		sb.append("return obj;");
		sb.append("}");
		sb.append("}");

		// Fields

		sb.append("private static " + entity.getName() + "Pool _instance = new " + entity.getName() + "Pool();");

		sb.append("private GeneralCacheAdministrator _cache;");
		sb.append("private boolean _cacheable;");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/persistence/" + entity.getName() + "Pool.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createService(Entity entity, int sessionType) throws IOException {
		XClass xClass = _getXClass(_outputPath + "/service/impl/" + entity.getName() + (sessionType != _PRINCIPAL_REMOTE ? "Local" : "") + "ServiceImpl.java");

		List methods = xClass.getMethods();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.spring;");

		// Interface declaration

		sb.append("public interface " + entity.getName() + _getSessionTypeName(sessionType) + "Service {");

		// Methods

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			String methodName = xMethod.getName();

			if (_isCustomMethod(xMethod) && xMethod.isPublic()) {
				sb.append("public " + xMethod.getReturnType().getType().getQualifiedName() + xMethod.getReturnType().getDimensionAsString() + " " + methodName + "(");

				List parameters = xMethod.getParameters();

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					sb.append(xParameter.getType().getQualifiedName() + xParameter.getDimensionAsString() + " " + xParameter.getName());

					if ((j + 1) != parameters.size()) {
						sb.append(", ");
					}
				}

				sb.append(")");

				List thrownExceptions = xMethod.getThrownExceptions();

				Set newExceptions = new LinkedHashSet();

				for (int j = 0; j < thrownExceptions.size(); j++) {
					XClass thrownException = (XClass)thrownExceptions.get(j);

					newExceptions.add(thrownException.getQualifiedName());
				}

				if (sessionType != _BASIC_LOCAL) {
					newExceptions.add("java.rmi.RemoteException");
				}

				if (newExceptions.size() > 0) {
					sb.append(" throws ");

					Iterator itr = newExceptions.iterator();

					while (itr.hasNext()) {
						sb.append(itr.next());

						if (itr.hasNext()) {
							sb.append(", ");
						}
					}
				}

				sb.append(";");
			}
		}

		// Interface close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/spring/" + entity.getName() + _getSessionTypeName(sessionType) + "Service.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceEJB(Entity entity, int sessionType) throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.ejb;");

		// Imports

		sb.append("import " + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "Service;");

		if (sessionType == _BASIC_LOCAL) {
			sb.append("import javax.ejb.EJBLocalObject;");
		}
		else {
			sb.append("import javax.ejb.EJBObject;");
		}

		// Interface declaration

		sb.append("public interface " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB extends EJB" + (sessionType == _BASIC_LOCAL ? "Local" : "") + "Object, " + entity.getName() + _getSessionTypeName(sessionType) + "Service {");

		// Interface close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/ejb/" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceEJBImpl(Entity entity, int sessionType) throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.ejb;");

		// Imports

		sb.append("import " + _packagePath + ".service.impl." + entity.getName() + _getSessionTypeName(sessionType) + "ServiceImpl;");
		sb.append("import javax.ejb.CreateException;");
		sb.append("import javax.ejb.SessionContext;");
		sb.append("import javax.ejb.SessionBean;");

		if (sessionType == _PRINCIPAL_REMOTE) {
			sb.append("import com.liferay.portal.auth.PrincipalException;");
			sb.append("import com.liferay.portal.service.impl.PrincipalSessionBean;");
		}

		// Class declaration

		sb.append("public class " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJBImpl extends " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceImpl implements SessionBean {");

		if (sessionType == _PRINCIPAL_REMOTE) {
			sb.append("public String getUserId() throws PrincipalException {");
			sb.append("return PrincipalSessionBean.getUserId(_sc);");
			sb.append("}");
		}

		// Methods

		sb.append("public void ejbCreate() throws CreateException {");
		sb.append("}");

		sb.append("public void ejbRemove() {");
		sb.append("}");

		sb.append("public void ejbActivate() {");
		sb.append("}");

		sb.append("public void ejbPassivate() {");
		sb.append("}");

		sb.append("public SessionContext getSessionContext() {");
		sb.append("return _sc;");
		sb.append("}");

		sb.append("public void setSessionContext(SessionContext sc) {");
		sb.append("_sc = sc;");
		sb.append("}");

		// Fields

		sb.append("private SessionContext _sc;");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/ejb/" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJBImpl.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceFactory(Entity entity, int sessionType) throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.spring;");

		// Imports

		sb.append("import " + _springUtilClassName + ";");
		sb.append("import org.springframework.context.ApplicationContext;");

		// Class declaration

		sb.append("public class " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory {");

		// Fields

		sb.append("private static final String NAME = " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory.class.getName();");

		// Methods

		sb.append("public static " + entity.getName() + _getSessionTypeName(sessionType) + "Service getService() {");
		sb.append("ApplicationContext ctx = SpringUtil.getContext();");
		sb.append(entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory factory = (" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory)ctx.getBean(NAME);");
		sb.append("return factory._service;");
		sb.append("}");

		sb.append("public void setService(" + entity.getName() + _getSessionTypeName(sessionType) + "Service service) {");
		sb.append("_service = service;");
		sb.append("}");

		// Fields

		sb.append("private " + entity.getName() + _getSessionTypeName(sessionType) + "Service _service;");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/spring/" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceHome(Entity entity, int sessionType) throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.ejb;");

		// Imports

		sb.append("import javax.ejb.CreateException;");

		if (sessionType == _BASIC_LOCAL) {
			sb.append("import javax.ejb.EJBLocalHome;");
		}
		else {
			sb.append("import java.rmi.RemoteException;");
			sb.append("import javax.ejb.EJBHome;");
		}

		// Interface declaration

		sb.append("public interface " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceHome extends EJB" + (sessionType == _BASIC_LOCAL ? "Local" : "") + "Home {");

		// Create method

		sb.append("public " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB create() throws CreateException");

		if (sessionType != _BASIC_LOCAL) {
			sb.append(", RemoteException");
		}

		sb.append(";");

		// Interface close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/ejb/" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceHome.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceHttp(Entity entity) throws IOException {
		XClass xClass = _getXClass(_outputPath + "/service/impl/" + entity.getName() + "ServiceImpl.java");

		List methods = xClass.getMethods();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.http;");

		// Imports

		if (_hasHttpMethods(xClass)) {
			sb.append("import " + _packagePath + ".service.spring." + entity.getName() + "ServiceUtil;");
		}

		sb.append("import com.liferay.portal.auth.HttpPrincipal;");
		sb.append("import com.liferay.portal.servlet.TunnelUtil;");
		sb.append("import com.liferay.util.ObjectValuePair;");
		sb.append("import com.liferay.util.lang.BooleanWrapper;");
		sb.append("import com.liferay.util.lang.DoubleWrapper;");
		sb.append("import com.liferay.util.lang.FloatWrapper;");
		sb.append("import com.liferay.util.lang.IntegerWrapper;");
		sb.append("import com.liferay.util.lang.LongWrapper;");
		sb.append("import com.liferay.util.lang.MethodWrapper;");
		sb.append("import com.liferay.util.lang.NullWrapper;");
		sb.append("import com.liferay.util.lang.ShortWrapper;");
		sb.append("import org.apache.commons.logging.Log;");
		sb.append("import org.apache.commons.logging.LogFactory;");

		// Class declaration

		sb.append("public class " + entity.getName() + "ServiceHttp {");

		// Methods

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			String methodName = xMethod.getName();

			if (_isCustomMethod(xMethod) && xMethod.isPublic()) {
				XClass returnType = xMethod.getReturnType().getType();
				String returnTypeName = returnType.getQualifiedName() + xMethod.getReturnType().getDimensionAsString();

				sb.append("public static " + returnTypeName + " " + methodName + "(HttpPrincipal httpPrincipal");

				List parameters = xMethod.getParameters();

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					if (j == 0) {
						sb.append(", ");
					}

					sb.append(xParameter.getType().getQualifiedName() + xParameter.getDimensionAsString() + " " + xParameter.getName());

					if ((j + 1) != parameters.size()) {
						sb.append(", ");
					}
				}

				sb.append(")");

				List thrownExceptions = xMethod.getThrownExceptions();

				Set newExceptions = new LinkedHashSet();

				for (int j = 0; j < thrownExceptions.size(); j++) {
					XClass thrownException = (XClass)thrownExceptions.get(j);

					newExceptions.add(thrownException.getQualifiedName());
				}

				sb.append(" throws ");

				if (newExceptions.contains("com.liferay.portal.PortalException")) {
					sb.append("com.liferay.portal.PortalException, ");
				}

				sb.append("com.liferay.portal.SystemException {");
				sb.append("try {");

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					String parameterTypeName =
						xParameter.getType().getQualifiedName() +
							xParameter.getDimensionAsString();

					sb.append("Object paramObj" + j + " = ");

					if (parameterTypeName.equals("boolean")) {
						sb.append("new BooleanWrapper(" + xParameter.getName() + ");");
					}
					else if (parameterTypeName.equals("double")) {
						sb.append("new DoubleWrapper(" + xParameter.getName() + ");");
					}
					else if (parameterTypeName.equals("float")) {
						sb.append("new FloatWrapper(" + xParameter.getName() + ");");
					}
					else if (parameterTypeName.equals("int")) {
						sb.append("new IntegerWrapper(" + xParameter.getName() + ");");
					}
					else if (parameterTypeName.equals("long")) {
						sb.append("new LongWrapper(" + xParameter.getName() + ");");
					}
					else if (parameterTypeName.equals("short")) {
						sb.append("new ShortWrapper(" + xParameter.getName() + ");");
					}
					else {
						sb.append(xParameter.getName() + ";");

						sb.append("if (" + xParameter.getName() + " == null) {");
						sb.append("paramObj" + j + " = new NullWrapper(\"" + _getClassName(xParameter) + "\");");
						sb.append("}");
					}
				}

				sb.append("MethodWrapper methodWrapper = new MethodWrapper(");
				sb.append(entity.getName() + "ServiceUtil.class.getName(),");
				sb.append("\"" + methodName + "\",");

				if (parameters.size() == 0) {
					sb.append("new Object[0]);");
				}
				else {
					sb.append("new Object[] {");

					for (int j = 0; j < parameters.size(); j++) {
						sb.append("paramObj" + j);

						if ((j + 1) != parameters.size()) {
							sb.append(", ");
						}
					}

					sb.append("});");
				}

				sb.append("Object returnObj = null;");

				sb.append("try {");
				sb.append("returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);");
				sb.append("}");
				sb.append("catch (Exception e) {");

				Iterator itr = newExceptions.iterator();

				while (itr.hasNext()) {
					String exceptionType = (String)itr.next();

					sb.append("if (e instanceof " + exceptionType + ") {");
					sb.append("throw (" + exceptionType + ")e;");
					sb.append("}");
				}

				sb.append("throw e;");
				sb.append("}");

				if (!returnTypeName.equals("void")) {
					if (returnTypeName.equals("boolean")) {
						sb.append("return ((Boolean)returnObj).booleanValue();");
					}
					else if (returnTypeName.equals("double")) {
						sb.append("return ((Double)returnObj).doubleValue();");
					}
					else if (returnTypeName.equals("float")) {
						sb.append("return ((Float)returnObj).floatValue();");
					}
					else if (returnTypeName.equals("int")) {
						sb.append("return ((Integer)returnObj).intValue();");
					}
					else if (returnTypeName.equals("long")) {
						sb.append("return ((Long)returnObj).longValue();");
					}
					else if (returnTypeName.equals("short")) {
						sb.append("return ((Short)returnObj).shortValue();");
					}
					else {
						sb.append("return (" + returnTypeName + ")returnObj;");
					}
				}

				sb.append("}");

				if (newExceptions.contains("com.liferay.portal.PortalException")) {
					sb.append("catch (com.liferay.portal.PortalException pe) {");
					sb.append("throw pe;");
					sb.append("}");
				}

				if (newExceptions.contains("com.liferay.portal.SystemException")) {
					sb.append("catch (com.liferay.portal.SystemException se) {");
					sb.append("throw se;");
					sb.append("}");
				}

				sb.append("catch (Exception e) {");
				sb.append("_log.error(e.getMessage());");
				sb.append("throw new com.liferay.portal.SystemException();");
				sb.append("}");
				sb.append("}");
			}
		}

		// Fields

		sb.append("private static final Log _log = LogFactory.getLog(" + entity.getName() + "ServiceHttp.class);");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/http/" + entity.getName() + "ServiceHttp.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceImpl(Entity entity, int sessionType) throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.impl;");

		// Imports

		if (sessionType == _PRINCIPAL_REMOTE) {
			sb.append("import com.liferay.portal.service.impl.PrincipalBean;");
		}

		sb.append("import " + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "Service;");

		// Class declaration

		sb.append("public class " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceImpl " + (sessionType == _PRINCIPAL_REMOTE ? "extends PrincipalBean " : "") + "implements " + entity.getName() + _getSessionTypeName(sessionType) + "Service {");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/impl/" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceImpl.java");

		if (!ejbFile.exists()) {
			writeFile(ejbFile, sb.toString());
		}
	}

	private void _createServiceRemoteEJBImpl(Entity entity) throws IOException {
		XClass xClass = _getXClass(_outputPath + "/service/impl/" + entity.getName() + "LocalServiceImpl.java");

		List methods = xClass.getMethods();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.ejb;");

		// Imports

		sb.append("import com.liferay.portal.service.impl.PrincipalSessionBean;");

		// Class declaration

		sb.append("public class " + entity.getName() + "RemoteServiceEJBImpl extends " + entity.getName() + "LocalServiceEJBImpl {");

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/ejb/" + entity.getName() + "RemoteServiceEJBImpl.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceSoap(Entity entity) throws IOException {
		XClass xClass = _getXClass(_outputPath + "/service/impl/" + entity.getName() + "ServiceImpl.java");

		List methods = xClass.getMethods();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.http;");

		// Imports

		if (_hasSoapMethods(xClass)) {
			sb.append("import " + _packagePath + ".service.spring." + entity.getName() + "ServiceUtil;");
		}

		sb.append("import java.rmi.RemoteException;");

		// Class declaration

		sb.append("public class " + entity.getName() + "ServiceSoap {");

		// Methods

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			String methodName = xMethod.getName();

			if (_isCustomMethod(xMethod) && xMethod.isPublic() &&
				_isSoapMethod(xMethod)) {

				String returnValueName =
					xMethod.getReturnType().getType().getQualifiedName();
				String returnValueDimension =
					xMethod.getReturnType().getDimensionAsString();

				String extendedModelName =
					_packagePath + ".model." + entity.getName();
				String modelName = extendedModelName + "Model";

				sb.append("public static ");

				if (returnValueName.equals(extendedModelName)) {
					if (entity.hasColumns()) {
						sb.append(modelName + returnValueDimension);
					}
					else {
						sb.append(extendedModelName + returnValueDimension);
					}
				}
				else if (returnValueName.equals("java.util.List")) {
					if (entity.hasColumns()) {
						sb.append(modelName + "[]");
					}
					else {
						sb.append("java.util.List");
					}
				}
				else {
					sb.append(returnValueName + returnValueDimension);
				}

				sb.append(" " + methodName + "(");

				List parameters = xMethod.getParameters();

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					sb.append(xParameter.getType().getQualifiedName() + xParameter.getDimensionAsString() + " " + xParameter.getName());

					if ((j + 1) != parameters.size()) {
						sb.append(", ");
					}
				}

				sb.append(") throws RemoteException {");
				sb.append("try {");

				if (!returnValueName.equals("void")) {
					sb.append(returnValueName + returnValueDimension + " returnValue = ");
				}

				sb.append(entity.getName() + "ServiceUtil." + methodName + "(");

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					sb.append(xParameter.getName());

					if ((j + 1) != parameters.size()) {
						sb.append(", ");
					}
				}

				sb.append(");");

				if (!returnValueName.equals("void")) {
					sb.append("return ");

					if (entity.hasColumns() &&
						returnValueName.equals("java.util.List")) {

						sb.append("(" + extendedModelName + "[])returnValue.toArray(new " + extendedModelName + "[0])");
					}
					else {
						sb.append("returnValue");
					}

					sb.append(";");
				}

				sb.append("}");

				sb.append("catch (Exception e) {");
				sb.append("throw new RemoteException(e.getMessage());");
				sb.append("}");
				sb.append("}");
			}
		}

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/http/" + entity.getName() + "ServiceSoap.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createServiceUtil(Entity entity, int sessionType) throws IOException {
		XClass xClass = _getXClass(_outputPath + "/service/impl/" + entity.getName() + (sessionType != _PRINCIPAL_REMOTE ? "Local" : "") + "ServiceImpl.java");

		List methods = xClass.getMethods();

		FastStringBuffer sb = new FastStringBuffer();

		// Package

		sb.append("package " + _packagePath + ".service.spring;");

		// Class declaration

		sb.append("public class " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceUtil {");

		// Portlet id field

		String portletKey = TextFormatter.format(_portletName, TextFormatter.A);

		try {
			PortletKeys portletKeys = new PortletKeys();

			Field field = portletKeys.getClass().getField(portletKey);

			sb.append("public static final String PORTLET_ID = \"" + field.get(portletKeys) + "\";");
		}
		catch (Exception e) {
		}

		// Methods

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			String methodName = xMethod.getName();

			if (_isCustomMethod(xMethod) && xMethod.isPublic()) {
				sb.append("public static " + xMethod.getReturnType().getType().getQualifiedName() + xMethod.getReturnType().getDimensionAsString() + " " + methodName + "(");

				List parameters = xMethod.getParameters();

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					sb.append(xParameter.getType().getQualifiedName() + xParameter.getDimensionAsString() + " " + xParameter.getName());

					if ((j + 1) != parameters.size()) {
						sb.append(", ");
					}
				}

				sb.append(")");

				List thrownExceptions = xMethod.getThrownExceptions();

				Set newExceptions = new LinkedHashSet();

				for (int j = 0; j < thrownExceptions.size(); j++) {
					XClass thrownException = (XClass)thrownExceptions.get(j);

					newExceptions.add(thrownException.getQualifiedName());
				}

				sb.append(" throws ");

				if (newExceptions.contains("com.liferay.portal.PortalException")) {
					sb.append("com.liferay.portal.PortalException, ");
				}

				sb.append("com.liferay.portal.SystemException {");
				sb.append("try {");
				sb.append(entity.getName() + _getSessionTypeName(sessionType) + "Service " + entity.getVarName() + _getSessionTypeName(sessionType) + "Service = " + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory.getService();");

				if (!xMethod.getReturnType().getType().getQualifiedName().equals("void")) {
					sb.append("return ");
				}

				sb.append(entity.getVarName() + _getSessionTypeName(sessionType) + "Service." + methodName + "(");

				for (int j = 0; j < parameters.size(); j++) {
					XParameter xParameter = (XParameter)parameters.get(j);

					sb.append(xParameter.getName());

					if ((j + 1) != parameters.size()) {
						sb.append(", ");
					}
				}

				sb.append(");");
				sb.append("}");

				if (newExceptions.contains("com.liferay.portal.PortalException")) {
					sb.append("catch (com.liferay.portal.PortalException pe) {");
					sb.append("throw pe;");
					sb.append("}");
				}

				if (newExceptions.contains("com.liferay.portal.SystemException")) {
					sb.append("catch (com.liferay.portal.SystemException se) {");
					sb.append("throw se;");
					sb.append("}");
				}

				sb.append("catch (Exception e) {");
				sb.append("throw new com.liferay.portal.SystemException(e);");
				sb.append("}");
				sb.append("}");
			}
		}

		// Class close brace

		sb.append("}");

		// Write file

		File ejbFile = new File(_outputPath + "/service/spring/" + entity.getName() + _getSessionTypeName(sessionType) + "ServiceUtil.java");

		writeFile(ejbFile, sb.toString());
	}

	private void _createSpringXML(boolean enterprise) throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			if (entity.hasLocalService()) {
				_createSpringXMLSession(entity, sb, _BASIC_LOCAL, enterprise);
				_createSpringXMLSession(entity, sb, _BASIC_REMOTE, enterprise);
			}

			_createSpringXMLSession(entity, sb, _PRINCIPAL_REMOTE, enterprise);
		}

		File xmlFile = null;
		if (enterprise) {
			xmlFile = new File(_springEntFileName);
		}
		else {
			xmlFile = new File(_springProFileName);
		}

		if (!xmlFile.exists()) {
			String content =
				"<?xml version=\"1.0\"?>\n" +
				"<!DOCTYPE beans PUBLIC \"-//SPRING//DTD BEAN//EN\" \"http://www.springframework.org/dtd/spring-beans.dtd\">\n" +
				"\n" +
				"<beans>\n" +
				"</beans>";

			FileUtil.write(xmlFile, content);
		}

		String oldContent = FileUtil.read(xmlFile);
		String newContent = new String(oldContent);

		int x = oldContent.indexOf("<beans>");
		int y = oldContent.lastIndexOf("</beans>");

		int firstSession = newContent.indexOf(
			"<bean id=\"" +  _packagePath + ".service.spring.", x);
		int lastSession = newContent.lastIndexOf(
			"<bean id=\"" +  _packagePath + ".service.spring.", y);

		if (firstSession == -1 || firstSession > y) {
			x = newContent.indexOf("</beans>");
			newContent =
				newContent.substring(0, x) + sb.toString() +
				newContent.substring(x, newContent.length());
		}
		else {
			firstSession = newContent.lastIndexOf("<bean", firstSession) - 1;
			lastSession = newContent.indexOf("</bean>", lastSession) + 8;

			newContent =
				newContent.substring(0, firstSession) + sb.toString() +
				newContent.substring(lastSession, newContent.length());
		}

		if (!oldContent.equals(newContent)) {
			FileUtil.write(xmlFile, newContent);
		}
	}

	private void _createSpringXMLSession(Entity entity, FastStringBuffer sb, int sessionType, boolean enterprise) {
		if (enterprise) {
			sb.append("\t<bean id=\"" + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "Service.enterprise\" class=\"" + (sessionType == _BASIC_LOCAL ? "com.liferay.portal.spring.LocalSessionFactoryBean" : "com.liferay.portal.spring.RemoteSessionFactoryBean") + "\" lazy-init=\"true\">\n");

			sb.append("\t\t<property name=\"businessInterface\">\n");
			sb.append("\t\t\t<value>" + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "Service</value>\n");
			sb.append("\t\t</property>\n");

			sb.append("\t\t<property name=\"jndiName\">\n");

			if (sessionType == _BASIC_LOCAL) {
				sb.append("\t\t\t<value>ejb/liferay/" + entity.getName() + "LocalServiceHome</value>\n");
			}
			else {
				sb.append("\t\t\t<value>" + StringUtil.replace(_packagePath + ".service.ejb.", ".", "_") + entity.getName() + _getSessionTypeName(sessionType) + "ServiceEJB</value>\n");
			}

			sb.append("\t\t</property>\n");

			sb.append("\t</bean>\n");
		}
		else {
			sb.append("\t<bean id=\"" + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "Service.professional\" class=\"" + _packagePath + ".service.impl." + entity.getName() + (sessionType == _BASIC_REMOTE ? "Local" : _getSessionTypeName(sessionType)) + "ServiceImpl\" lazy-init=\"true\" />\n");
		}

		sb.append("\t<bean id=\"" + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory\" class=\"" + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "ServiceFactory\" lazy-init=\"true\">\n");
		sb.append("\t\t<property name=\"service\">\n");
		sb.append("\t\t\t<ref bean=\"" + _packagePath + ".service.spring." + entity.getName() + _getSessionTypeName(sessionType) + "Service." + (enterprise ? "enterprise" : "professional") + "\" />\n");
		sb.append("\t\t</property>\n");
		sb.append("\t</bean>\n");
	}

	private void _createSQLIndexes() throws IOException {
		String sqlPath = _portalRoot + "/sql";

		File sqlFile = new File(sqlPath + "/indexes.sql");

		String content = FileUtil.read(sqlFile);

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			List finderList = entity.getFinderList();

			for (int j = 0; j < finderList.size(); j++) {
				EntityFinder finder = (EntityFinder)finderList.get(j);

				if (finder.isDBIndex()) {
					FastStringBuffer sb = new FastStringBuffer();

					String indexName =
						entity.getName() + "_ix_" + finder.getName();

					if (indexName.length() > 30) {
						indexName = indexName.substring(0, 30);
					}

					sb.append("create index " + indexName + " on " + entity.getName());

					if (_badTableNames.contains(entity.getName())) {
						sb.append("_");
					}

					sb.append(" (");

					List finderColsList = finder.getColumns();

					for (int k = 0; k < finderColsList.size(); k++) {
						EntityColumn col = null;

						if (finderColsList.get(k) instanceof EntityColumn) {
							col = (EntityColumn)finderColsList.get(k);
						}
						else {
							String finderColName = (String)finderColsList.get(k);

							col = entity.getColumn(finderColName);
						}

						sb.append(col.getDBName());

						if ((k + 1) != finderColsList.size()) {
							sb.append(", ");
						}
					}

					sb.append(");");

					if (content.indexOf(sb.toString()) == -1) {
						content += "\n" + sb.toString();

						FileUtil.write(sqlFile, content);
					}
				}
			}
		}
	}

	private void _createSQLTables() throws IOException {
		String sqlPath = _portalRoot + "/sql";

		File sqlFile = new File(sqlPath + "/portal-tables.sql");

		String content = FileUtil.read(sqlFile);

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			List pkList = entity.getPKList();
			List columnList = entity.getColumnList();

			String createString = "create table " + entity.getTable() + " (";
			
			if ((content.indexOf(createString) == -1) &&
				(columnList.size() > 0)) {

				FastStringBuffer sb = new FastStringBuffer();

				sb.append("\n\n" + createString + "\n");

				for (int j = 0; j < columnList.size(); j++) {
					EntityColumn col = (EntityColumn)columnList.get(j);

					sb.append("\t" + col.getName());
					
					if (_badCmpFields.contains(col.getName())) {
						sb.append("_");
					}
					
					sb.append(" ");

					if (col.getType().equals("Date")) {
						sb.append("DATE");
					}
					else if (col.getType().equals("String")) {
						sb.append("VARCHAR(100)");
					}
					else if (col.getType().equals("boolean")) {
						sb.append("BOOLEAN");
					}
					else if (col.getType().equals("double")) {
						sb.append("DOUBLE");
					}
					else {
						sb.append("int");
					}

					if (col.isPrimary()) {
						sb.append(" not null");

						if (!entity.hasCompoundPK()) { 
							sb.append(" primary key");
						}
					}

					if (((j + 1) != columnList.size()) ||
						(entity.hasCompoundPK())) {

						sb.append(",");
					}

					sb.append("\n");
				}
				
				if (entity.hasCompoundPK()) {
					sb.append("\tprimary key (");

					for (int k = 0; k < pkList.size(); k++) {
						EntityColumn pk = (EntityColumn)pkList.get(k);

						sb.append(pk.getName());

						if ((k + 1) != pkList.size()) {
							sb.append(", ");
						}
					}

					sb.append(")\n");
				}

				sb.append(");");

				content += sb.toString();

				FileUtil.write(sqlFile, content);
			}
		}
	}

	private String _getClassName(Type type) {
		int dimension = type.getDimension();
		String name = type.getType().getQualifiedName();

		if (dimension > 0) {
			FastStringBuffer sb = new FastStringBuffer();

			for (int i = 0; i < dimension; i++) {
				sb.append("[");
			}

			if (name.equals("boolean")) {
				return sb.toString() + "Z";
			}
			else if (name.equals("byte")) {
				return sb.toString() + "B";
			}
			else if (name.equals("char")) {
				return sb.toString() + "C";
			}
			else if (name.equals("double")) {
				return sb.toString() + "D";
			}
			else if (name.equals("float")) {
				return sb.toString() + "F";
			}
			else if (name.equals("int")) {
				return sb.toString() + "I";
			}
			else if (name.equals("long")) {
				return sb.toString() + "J";
			}
			else if (name.equals("short")) {
				return sb.toString() + "S";
			}
			else {
				return sb.toString() + "L" + name + ";";
			}
		}

		return name;
	}

	private String _getNoSuchEntityException(Entity entity) {
		String noSuchEntityException = entity.getName();
		if (Validator.isNull(entity.getPortletShortName()) || noSuchEntityException.startsWith(entity.getPortletShortName())) {
			noSuchEntityException = noSuchEntityException.substring(entity.getPortletShortName().length(), noSuchEntityException.length());
		}
		noSuchEntityException = "NoSuch" + noSuchEntityException;

		return noSuchEntityException;
	}

	private String _getSessionTypeName(int sessionType) {
		String sessionTypeName = "";
		if (sessionType == _BASIC_LOCAL) {
			sessionTypeName = "Local";
		}
		else if (sessionType == _BASIC_REMOTE) {
			sessionTypeName = "Remote";
		}

		return sessionTypeName;
	}

	private XClass _getXClass(String fileName) {
		XClass xClass = (XClass)SimpleCachePool.get(fileName);

		if (xClass == null) {
			int pos = fileName.indexOf("/");

			String srcDir = fileName.substring(0, pos);
			String srcFile = fileName.substring(pos + 1, fileName.length());
			String className = StringUtil.replace(
				srcFile.substring(0, srcFile.length() - 5), "/", ".");

			XJavaDoc xJavaDoc = new XJavaDoc();

			xJavaDoc.addSourceSet(
				new FileSourceSet(new File(srcDir), new String[] {srcFile}));

			xClass = xJavaDoc.getXClass(className);

			SimpleCachePool.put(fileName, xClass);
		}

		return xClass;
	}

	private boolean _hasHttpMethods(XClass xClass) {
		List methods = xClass.getMethods();

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			if (_isCustomMethod(xMethod) && xMethod.isPublic()) {
				return true;
			}
		}

		return false;
	}

	private boolean _hasSoapMethods(XClass xClass) {
		List methods = xClass.getMethods();

		for (int i = 0; i < methods.size(); i++) {
			XMethod xMethod = (XMethod)methods.get(i);

			if (_isCustomMethod(xMethod) && xMethod.isPublic() &&
				_isSoapMethod(xMethod)) {

				return true;
			}
		}

		return false;
	}

	private boolean _isCustomMethod(XMethod method) {
		String methodName = method.getName();

		if (methodName.equals("hasAdministrator") ||
			methodName.equals("ejbCreate") ||
			methodName.equals("ejbRemove") ||
			methodName.equals("ejbActivate") ||
			methodName.equals("ejbPassivate") ||
			methodName.equals("getSessionContext") ||
			methodName.equals("setSessionContext") ||
			methodName.equals("hashCode") ||
			methodName.equals("getClass") ||
			methodName.equals("wait") ||
			methodName.equals("equals") ||
			methodName.equals("toString") ||
			methodName.equals("notify") ||
			methodName.equals("notifyAll")) {

			return false;
		}
		else if (methodName.equals("getUser") &&
				 method.getParameters().size() == 0) {

			return false;
		}
		else if (methodName.equals("getUserId") &&
				 method.getParameters().size() == 0) {

			return false;
		}
		else {
			return true;
		}
	}

	private boolean _isSoapMethod(XMethod method) {
		String returnValueName =
			method.getReturnType().getType().getQualifiedName();

		if (returnValueName.startsWith("java.io") ||
			returnValueName.equals("java.util.Properties") ||
			returnValueName.startsWith("javax")) {

			return false;
		}

		List parameters = method.getParameters();

		for (int i = 0; i < parameters.size(); i++) {
			XParameter xParameter = (XParameter)parameters.get(i);

			String parameterTypeName =
				xParameter.getType().getQualifiedName() +
					xParameter.getDimensionAsString();

			if ((parameterTypeName.indexOf(
					"com.liferay.portal.model.") != -1) ||
				(parameterTypeName.equals(
					"com.liferay.portlet.PortletPreferencesImpl")) ||
				 parameterTypeName.startsWith("java.io") ||
				 //parameterTypeName.startsWith("java.util.List") ||
				 parameterTypeName.startsWith("java.util.Locale") ||
				 parameterTypeName.startsWith("java.util.Properties") ||
				 parameterTypeName.startsWith("javax")) {

				return false;
			}
		}

		return true;
	}

	private int _PRINCIPAL_REMOTE = 0;
	private int _BASIC_LOCAL = 1;
	private int _BASIC_REMOTE = 2;

	private Set _badTableNames;
	private Set _badCmpFields;
	private String _hbmFileName;
	private String _springEntFileName;
	private String _springProFileName;
	private String _springUtilClassName;
	private String _portalRoot;
	private String _portletName;
	private String _portletShortName;
	private String _portletClassName;
	private String _portletPackageName;
	private String _outputPath;
	private String _packagePath;
	private List _ejbList;

}