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

package com.liferay.portal.tools.servicebuilder;

import com.liferay.portal.freemarker.FreeMarkerUtil;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.StringUtil_IW;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelHintsUtil;
import com.liferay.portal.tools.SourceFormatter;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.TextFormatter;
import com.liferay.util.Time;
import com.liferay.util.log4j.Log4JUtil;
import com.liferay.util.xml.XMLFormatter;

import com.thoughtworks.qdox.JavaDocBuilder;
import com.thoughtworks.qdox.model.JavaClass;
import com.thoughtworks.qdox.model.JavaMethod;
import com.thoughtworks.qdox.model.JavaParameter;
import com.thoughtworks.qdox.model.Type;

import de.hunsicker.io.FileFormat;
import de.hunsicker.jalopy.Jalopy;
import de.hunsicker.jalopy.storage.Convention;
import de.hunsicker.jalopy.storage.ConventionKeys;
import de.hunsicker.jalopy.storage.Environment;

import freemarker.ext.beans.BeansWrapper;
import freemarker.template.TemplateHashModel;
import freemarker.template.TemplateModelException;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="ServiceBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Charles May
 * @author Alexander Chow
 * @author Harry Mark
 * @author Tariq Dweik
 *
 */
public class ServiceBuilder {

	public static void main(String[] args) {
		ClassLoader classLoader = ClassLoader.getSystemClassLoader();

		Log4JUtil.configureLog4J(
			classLoader.getResource("META-INF/portal-log4j.xml"));
		Log4JUtil.configureLog4J(
			classLoader.getResource("META-INF/portal-log4j-ext.xml"));

		ServiceBuilder serviceBuilder = null;

		if (args.length == 7) {
			String fileName = args[0];
			String hbmFileName = args[1];
			String modelHintsFileName = args[2];
			String springFileName = args[3];
			String springDataSourceFileName = "";
			String apiDir = args[5];
			String implDir = "src";
			String jsonFileName = args[6];
			String remotingFileName = "../tunnel-web/docroot/WEB-INF/remoting-servlet.xml";
			String sqlDir = "../sql";
			String sqlFileName = "portal-tables.sql";
			boolean autoNamespaceTables = false;
			String baseModelImplPackage = "com.liferay.portal.model.impl";
			String basePersistencePackage = "com.liferay.portal.service.persistence";
			String beanLocatorUtilPackage = "com.liferay.portal.kernel.bean";
			String principalBeanPackage = "com.liferay.portal.service.impl";
			String propsUtilPackage = "com.liferay.portal.util";
			String springHibernatePackage = "com.liferay.portal.spring.hibernate";
			String springUtilPackage = "com.liferay.portal.spring.util";
			String testDir = "";

			serviceBuilder = new ServiceBuilder(
				fileName, hbmFileName, modelHintsFileName, springFileName,
				springDataSourceFileName, apiDir, implDir, jsonFileName,
				remotingFileName, sqlDir, sqlFileName, autoNamespaceTables,
				baseModelImplPackage, basePersistencePackage,
				beanLocatorUtilPackage, principalBeanPackage, propsUtilPackage,
				springHibernatePackage, springUtilPackage, testDir);
		}
		else if (args.length == 0) {
			String fileName = System.getProperty("service.input.file");
			String hbmFileName = System.getProperty("service.hbm.file");
			String modelHintsFileName = System.getProperty("service.model.hints.file");
			String springFileName = System.getProperty("service.spring.file");
			String springDataSourceFileName = System.getProperty("service.spring.data.source.file");
			String apiDir = System.getProperty("service.api.dir");
			String implDir = System.getProperty("service.impl.dir");
			String jsonFileName = System.getProperty("service.json.file");
			String remotingFileName = System.getProperty("service.remoting.file");
			String sqlDir = System.getProperty("service.sql.dir");
			String sqlFileName = System.getProperty("service.sql.file");
			boolean autoNamespaceTables = GetterUtil.getBoolean(System.getProperty("service.auto.namespace.tables"));
			String baseModelImplPackage = System.getProperty("service.base.model.impl.package");
			String basePersistencePackage = System.getProperty("service.base.persistence.package");
			String beanLocatorUtilPackage = System.getProperty("service.bean.locator.util.package");
			String principalBeanPackage = System.getProperty("service.principal.bean.package");
			String propsUtilPackage = System.getProperty("service.props.util.package");
			String springHibernatePackage = System.getProperty("service.spring.hibernate.package");
			String springUtilPackage = System.getProperty("service.spring.util.package");
			String testDir = System.getProperty("service.test.dir");

			serviceBuilder = new ServiceBuilder(
				fileName, hbmFileName, modelHintsFileName, springFileName,
				springDataSourceFileName, apiDir, implDir, jsonFileName,
				remotingFileName, sqlDir, sqlFileName, autoNamespaceTables,
				baseModelImplPackage, basePersistencePackage,
				beanLocatorUtilPackage, principalBeanPackage, propsUtilPackage,
				springHibernatePackage, springUtilPackage, testDir);
		}

		if (serviceBuilder == null) {
			System.out.println(
				"Please set these required system properties. Sample values are:\n" +
				"\n" +
				"\t-Dservice.input.file=${service.file}\n" +
				"\t-Dservice.hbm.file=classes/META-INF/portal-hbm.xml\n" +
				"\t-Dservice.model.hints.file=classes/META-INF/portal-model-hints.xml\n" +
				"\t-Dservice.spring.file=classes/META-INF/portal-spring.xml\n" +
				"\t-Dservice.api.dir=${project.dir}/portal-service/src\n" +
				"\t-Dservice.impl.dir=src\n" +
				"\t-Dservice.json.file=${project.dir}/portal-web/docroot/html/js/liferay/service_unpacked.js\n" +
				"\t-Dservice.remoting.file=${project.dir}/tunnel-web/docroot/WEB-INF/remoting-servlet.xml\n" +
				"\t-Dservice.sql.dir=../sql\n" +
				"\t-Dservice.sql.file=portal-tables.sql\n" +
				"\t-Dservice.base.model.impl.package=com.liferay.portal.model.impl\n" +
				"\t-Dservice.base.persistence.package=com.liferay.portal.service.persistence\n" +
				"\t-Dservice.bean.locator.util.package=com.liferay.portal.kernel.bean\n" +
				"\t-Dservice.principal.bean.package=com.liferay.portal.service.impl\n" +
				"\t-Dservice.props.util.package=com.liferay.portal.util\n" +
				"\t-Dservice.spring.hibernate.package=com.liferay.portal.spring.hibernate\n" +
				"\t-Dservice.spring.util.package=com.liferay.portal.spring.util\n" +
				"\n" +
				"You can also customize the generated code by overriding the default templates with these optional properties:\n" +
				"\n" +
				"\t-Dservice.tpl.base_mode_impl.ftl=" + _TPL_ROOT + "base_mode_impl.ftl\n"+
				"\t-Dservice.tpl.base_persistence.ftl=" + _TPL_ROOT + "base_persistence.ftl\n"+
				"\t-Dservice.tpl.bean_locator_util.ftl=" + _TPL_ROOT + "bean_locator_util.ftl\n"+
				"\t-Dservice.tpl.copyright.txt=copyright.txt\n"+
				"\t-Dservice.tpl.dynamic_dialect.ftl=" + _TPL_ROOT + "dynamic_dialect.ftl\n"+
				"\t-Dservice.tpl.ejb_pk.ftl=" + _TPL_ROOT + "ejb_pk.ftl\n"+
				"\t-Dservice.tpl.exception.ftl=" + _TPL_ROOT + "exception.ftl\n"+
				"\t-Dservice.tpl.extended_model.ftl=" + _TPL_ROOT + "extended_model.ftl\n"+
				"\t-Dservice.tpl.extended_model_impl.ftl=" + _TPL_ROOT + "extended_model_impl.ftl\n"+
				"\t-Dservice.tpl.finder.ftl=" + _TPL_ROOT + "finder.ftl\n"+
				"\t-Dservice.tpl.finder_cache.ftl=" + _TPL_ROOT + "finder_cache.ftl\n"+
				"\t-Dservice.tpl.finder_util.ftl=" + _TPL_ROOT + "finder_util.ftl\n"+
				"\t-Dservice.tpl.hbm_xml.ftl=" + _TPL_ROOT + "hbm_xml.ftl\n"+
				"\t-Dservice.tpl.hibernate_configuration.ftl=" + _TPL_ROOT + "hibernate_configuration.ftl\n"+
				"\t-Dservice.tpl.hibernate_util.ftl=" + _TPL_ROOT + "hibernate_util.ftl\n"+
				"\t-Dservice.tpl.json_js.ftl=" + _TPL_ROOT + "json_js.ftl\n"+
				"\t-Dservice.tpl.json_js_method.ftl=" + _TPL_ROOT + "json_js_method.ftl\n"+
				"\t-Dservice.tpl.model.ftl=" + _TPL_ROOT + "model.ftl\n"+
				"\t-Dservice.tpl.model_hints_xml.ftl=" + _TPL_ROOT + "model_hints_xml.ftl\n"+
				"\t-Dservice.tpl.model_impl.ftl=" + _TPL_ROOT + "model_impl.ftl\n"+
				"\t-Dservice.tpl.model_soap.ftl=" + _TPL_ROOT + "model_soap.ftl\n"+
				"\t-Dservice.tpl.persistence.ftl=" + _TPL_ROOT + "persistence.ftl\n"+
				"\t-Dservice.tpl.persistence_impl.ftl=" + _TPL_ROOT + "persistence_impl.ftl\n"+
				"\t-Dservice.tpl.persistence_util.ftl=" + _TPL_ROOT + "persistence_util.ftl\n"+
				"\t-Dservice.tpl.principal_bean.ftl=" + _TPL_ROOT + "principal_bean.ftl\n"+
				"\t-Dservice.tpl.props.ftl=" + _TPL_ROOT + "props.ftl\n"+
				"\t-Dservice.tpl.props_util.ftl=" + _TPL_ROOT + "props_util.ftl\n"+
				"\t-Dservice.tpl.remoting_xml.ftl=" + _TPL_ROOT + "remoting_xml.ftl\n"+
				"\t-Dservice.tpl.service.ftl=" + _TPL_ROOT + "service.ftl\n"+
				"\t-Dservice.tpl.service_base_impl.ftl=" + _TPL_ROOT + "service_base_impl.ftl\n"+
				"\t-Dservice.tpl.service_factory.ftl=" + _TPL_ROOT + "service_factory.ftl\n"+
				"\t-Dservice.tpl.service_http.ftl=" + _TPL_ROOT + "service_http.ftl\n"+
				"\t-Dservice.tpl.service_impl.ftl=" + _TPL_ROOT + "service_impl.ftl\n"+
				"\t-Dservice.tpl.service_json.ftl=" + _TPL_ROOT + "service_json.ftl\n"+
				"\t-Dservice.tpl.service_json_serializer.ftl=" + _TPL_ROOT + "service_json_serializer.ftl\n"+
				"\t-Dservice.tpl.service_soap.ftl=" + _TPL_ROOT + "service_soap.ftl\n"+
				"\t-Dservice.tpl.service_util.ftl=" + _TPL_ROOT + "service_util.ftl\n"+
				"\t-Dservice.tpl.spring_data_source_xml.ftl=" + _TPL_ROOT + "spring_data_source_xml.ftl\n"+
				"\t-Dservice.tpl.spring_util.ftl=" + _TPL_ROOT + "spring_util.ftl\n"+
				"\t-Dservice.tpl.spring_xml.ftl=" + _TPL_ROOT + "spring_xml.ftl\n"+
				"\t-Dservice.tpl.spring_xml_session.ftl=" + _TPL_ROOT + "spring_xml_session.ftl");
		}
	}

	public static Set getBadCmpFields() {
		Set badCmpFields = new HashSet();

		badCmpFields.add("access");
		badCmpFields.add("active");
		badCmpFields.add("alias");
		badCmpFields.add("code");
		badCmpFields.add("data");
		badCmpFields.add("date");
		badCmpFields.add("end");
		badCmpFields.add("idd");
		badCmpFields.add("featured");
		badCmpFields.add("fields");
		badCmpFields.add("from");
		badCmpFields.add("hidden");
		badCmpFields.add("id");
		badCmpFields.add("index");
		badCmpFields.add("internal");
		badCmpFields.add("interval");
		badCmpFields.add("join");
		badCmpFields.add("key");
		badCmpFields.add("log");
		badCmpFields.add("number");
		badCmpFields.add("password");
		badCmpFields.add("path");
		badCmpFields.add("primary");
		badCmpFields.add("sale");
		badCmpFields.add("settings");
		badCmpFields.add("size");
		badCmpFields.add("start");
		badCmpFields.add("text");
		badCmpFields.add("to");
		badCmpFields.add("type");
		badCmpFields.add("uuid");
		badCmpFields.add("values");

		return badCmpFields;
	}

	public static Set getBadTableNames() {
		Set badTableNames = new HashSet();

		badTableNames.add("Account");
		badTableNames.add("Action");
		badTableNames.add("Cache");
		badTableNames.add("ClassName");
		badTableNames.add("Contact");
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
		writeFile(file, content, null);
	}

	public static void writeFile(File file, String content, Map jalopySettings)
		throws IOException {

		String packagePath = _getPackagePath(file);

		String className = file.getName();

		className = className.substring(0, className.length() - 5);

		content = SourceFormatter.stripImports(content, packagePath, className);

		File tempFile = new File("ServiceBuilder.temp");

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

		try {
			Jalopy.setConvention("../../misc/jalopy.xml");
		}
		catch (FileNotFoundException fnne) {
		}

		if (jalopySettings == null) {
			jalopySettings = new HashMap();
		}

		Environment env = Environment.getInstance();

		// Author

		String author = GetterUtil.getString(
			(String)jalopySettings.get("author"), "Brian Wing Shun Chan");

		env.set("author", author);

		// File name

		env.set("fileName", file.getName());

		Convention convention = Convention.getInstance();

		String classMask =
			"/**\n" +
			" * <a href=\"$fileName$.html\"><b><i>View Source</i></b></a>\n" +
			" *\n";

		String[] classCommentsArray = (String[])jalopySettings.get("classComments");

		if ((classCommentsArray != null) && (classCommentsArray.length > 0)) {
			for (int i = 0; i < classCommentsArray.length; i++) {
				String classComments = classCommentsArray[i];

				//classComments = "The quick brown fox jumped over the lazy dog. The quick brown fox jumped over the lazy dog. The quick brown fox jumped over the lazy dog. The quick brown fox jumped over the lazy dog.";
				classComments = StringUtil.wrap(classComments, 76, "\n * ");

				if (classComments.startsWith("\n")) {
					classComments = classComments.substring(
						1, classComments.length());
				}

				classMask += " * <p>\n" + classComments + "\n * </p>\n *\n";
			}
		}

		classMask +=
			" * @author $author$\n" +
			" *\n";

		String[] seeArray = (String[])jalopySettings.get("see");

		if ((classCommentsArray != null) && (classCommentsArray.length > 0)) {
			for (int i = 0; i < seeArray.length; i++) {
				String see = seeArray[i];

				classMask += " * @see " + see + "\n";
			}

			classMask += " *\n";
		}

		classMask += " */";

		convention.put(
			ConventionKeys.COMMENT_JAVADOC_TEMPLATE_CLASS,
			env.interpolate(classMask));

		convention.put(
			ConventionKeys.COMMENT_JAVADOC_TEMPLATE_INTERFACE,
			env.interpolate(classMask));

		if (jalopySettings.get("keepJavadoc") != null) {
			convention.put(
				ConventionKeys.COMMENT_JAVADOC_REMOVE,
				Boolean.FALSE.toString());
		}

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

			System.out.println("Writing " + file);

			// Workaround for bug with XJavaDoc

			file.setLastModified(
				System.currentTimeMillis() - (Time.SECOND * 5));
		}

		tempFile.deleteOnExit();
	}

	public ServiceBuilder(
		String fileName, String hbmFileName, String modelHintsFileName,
		String springFileName, String springDataSourceFileName, String apiDir,
		String implDir, String jsonFileName, String remotingFileName,
		String sqlDir, String sqlFileName, boolean autoNamespaceTables,
		String baseModelImplPackage, String basePersistencePackage,
		String beanLocatorUtilPackage, String principalBeanPackage,
		String propsUtilPackage, String springHibernatePackage,
		String springUtilPackage, String testDir) {

		new ServiceBuilder(
			fileName, hbmFileName, modelHintsFileName, springFileName,
			springDataSourceFileName, apiDir, implDir, jsonFileName,
			remotingFileName, sqlDir, sqlFileName, autoNamespaceTables,
			baseModelImplPackage, basePersistencePackage,
			beanLocatorUtilPackage, principalBeanPackage, propsUtilPackage,
			springHibernatePackage, springUtilPackage, testDir, true);
	}

	public ServiceBuilder(
		String fileName, String hbmFileName, String modelHintsFileName,
		String springFileName, String springDataSourceFileName, String apiDir,
		String implDir, String jsonFileName, String remotingFileName,
		String sqlDir, String sqlFileName, boolean autoNamespaceTables,
		String baseModelImplPackage, String basePersistencePackage,
		String beanLocatorUtilPackage, String principalBeanPackage,
		String propsUtilPackage, String springHibernatePackage,
		String springUtilPackage, String testDir, boolean build) {

		_tplBaseModeImpl = _getTplProperty("base_mode_impl", _tplBaseModeImpl);
		_tplBasePersistence = _getTplProperty(
			"base_persistence", _tplBasePersistence);
		_tplBeanLocatorUtil = _getTplProperty(
			"bean_locator_util", _tplBeanLocatorUtil);
		_tplDynamicDialect = _getTplProperty(
			"dynamic_dialect", _tplDynamicDialect);
		_tplEjbPk = _getTplProperty("ejb_pk", _tplEjbPk);
		_tplException = _getTplProperty("exception", _tplException);
		_tplExtendedModel = _getTplProperty(
			"extended_model", _tplExtendedModel);
		_tplExtendedModelImpl = _getTplProperty(
			"extended_model_impl", _tplExtendedModelImpl);
		_tplFinder = _getTplProperty("finder", _tplFinder);
		_tplFinderCache = _getTplProperty("finder_cache", _tplFinderCache);
		_tplFinderUtil = _getTplProperty("finder_util", _tplFinderUtil);
		_tplHbmXml = _getTplProperty("hbm_xml", _tplHbmXml);
		_tplHibernateConfiguration = _getTplProperty(
			"hibernate_configuration", _tplHibernateConfiguration);
		_tplHibernateUtil = _getTplProperty(
			"hibernate_util", _tplHibernateUtil);
		_tplJsonJs = _getTplProperty("json_js", _tplJsonJs);
		_tplJsonJsMethod = _getTplProperty("json_js_method", _tplJsonJsMethod);
		_tplModel = _getTplProperty("model", _tplModel);
		_tplModelHintsXml = _getTplProperty(
			"model_hints_xml", _tplModelHintsXml);
		_tplModelImpl = _getTplProperty("model_impl", _tplModelImpl);
		_tplModelSoap = _getTplProperty("model_soap", _tplModelSoap);
		_tplPersistence = _getTplProperty("persistence", _tplPersistence);
		_tplPersistenceImpl = _getTplProperty(
			"persistence_impl", _tplPersistenceImpl);
		_tplPersistenceUtil = _getTplProperty(
			"persistence_util", _tplPersistenceUtil);
		_tplPrincipalBean = _getTplProperty(
			"principal_bean", _tplPrincipalBean);
		_tplProps = _getTplProperty("props", _tplProps);
		_tplPropsUtil = _getTplProperty("props_util", _tplPropsUtil);
		_tplRemotingXml = _getTplProperty("remoting_xml", _tplRemotingXml);
		_tplService = _getTplProperty("service", _tplService);
		_tplServiceBaseImpl = _getTplProperty(
			"service_base_impl", _tplServiceBaseImpl);
		_tplServiceFactory = _getTplProperty(
			"service_factory", _tplServiceFactory);
		_tplServiceHttp = _getTplProperty("service_http", _tplServiceHttp);
		_tplServiceImpl = _getTplProperty("service_impl", _tplServiceImpl);
		_tplServiceJson = _getTplProperty("service_json", _tplServiceJson);
		_tplServiceJsonSerializer = _getTplProperty(
			"service_json_serializer", _tplServiceJsonSerializer);
		_tplServiceSoap = _getTplProperty("service_soap", _tplServiceSoap);
		_tplServiceUtil = _getTplProperty("service_util", _tplServiceUtil);
		_tplSpringDataSourceXml = _getTplProperty(
			"spring_data_source_xml", _tplSpringDataSourceXml);
		_tplSpringUtil = _getTplProperty("spring_util", _tplSpringUtil);
		_tplSpringXml = _getTplProperty("spring_xml", _tplSpringXml);

		try {
			_badTableNames = ServiceBuilder.getBadTableNames();
			_badCmpFields = ServiceBuilder.getBadCmpFields();

			_hbmFileName = hbmFileName;
			_modelHintsFileName = modelHintsFileName;
			_springFileName = springFileName;
			_springDataSourceFileName = springDataSourceFileName;
			_apiDir = apiDir;
			_implDir = implDir;
			_jsonFileName = jsonFileName;
			_remotingFileName = remotingFileName;
			_sqlDir = sqlDir;
			_sqlFileName = sqlFileName;
			_autoNamespaceTables = autoNamespaceTables;
			_baseModelImplPackage = baseModelImplPackage;
			_basePersistencePackage = basePersistencePackage;
			_beanLocatorUtilPackage = beanLocatorUtilPackage;
			_principalBeanPackage = principalBeanPackage;
			_propsUtilPackage = propsUtilPackage;
			_springHibernatePackage = springHibernatePackage;
			_springUtilPackage = springUtilPackage;
			_testDir = testDir;

			Document doc = PortalUtil.readDocumentFromFile(
				new File(fileName), true);

			Element root = doc.getRootElement();

			String packagePath = root.attributeValue("package-path");

			_outputPath =
				_implDir + "/" + StringUtil.replace(packagePath, ".", "/");

			_serviceOutputPath =
				_apiDir + "/" + StringUtil.replace(packagePath, ".", "/");

			if (Validator.isNotNull(_testDir)) {
				_testOutputPath =
					_testDir + "/" + StringUtil.replace(packagePath, ".", "/");
			}

			_packagePath = packagePath;

			Element portlet = root.element("portlet");
			Element namespace = root.element("namespace");

			if (portlet != null) {
				_portletName = portlet.attributeValue("name");

				_portletShortName = portlet.attributeValue("short-name");

				_portletPackageName =
					TextFormatter.format(_portletName, TextFormatter.B);

				_outputPath += "/" + _portletPackageName;

				_serviceOutputPath += "/" + _portletPackageName;

				_testOutputPath += "/" + _portletPackageName;

				_packagePath += "." + _portletPackageName;
			}
			else {
				_portletShortName = namespace.getText();
			}

			_portletShortName = _portletShortName.trim();

			if (!Validator.isChar(_portletShortName)) {
				throw new RuntimeException(
					"The namespace element must be a valid keyword");
			}

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

				if (_autoNamespaceTables) {
					table = _portletShortName + "_" + table;
				}

				boolean uuid = GetterUtil.getBoolean(
					entityEl.attributeValue("uuid"), false);
				boolean localService = GetterUtil.getBoolean(
					entityEl.attributeValue("local-service"), false);
				boolean remoteService = GetterUtil.getBoolean(
					entityEl.attributeValue("remote-service"), true);
				String persistenceClass = GetterUtil.getString(
					entityEl.attributeValue("persistence-class"),
					_packagePath + ".service.persistence." + ejbName +
						"PersistenceImpl");

				String finderClass = "";

				if (FileUtil.exists(
					_outputPath + "/service/persistence/" + ejbName +
						"FinderImpl.java")) {

					finderClass =
						_packagePath + ".service.persistence." + ejbName +
							"FinderImpl";
				}

				String dataSource = entityEl.attributeValue("data-source");
				String sessionFactory = entityEl.attributeValue(
					"session-factory");
				String txManager = entityEl.attributeValue(
					"tx-manager");

				Iterator itr2 = null;

				List pkList = new ArrayList();
				List regularColList = new ArrayList();
				List collectionList = new ArrayList();
				List columnList = new ArrayList();

				List columns = entityEl.elements("column");

				if (uuid) {
					Element column = DocumentHelper.createElement("column");

					column.addAttribute("name", "uuid");
					column.addAttribute("type", "String");

					columns.add(0, column);
				}

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
					boolean primary = GetterUtil.getBoolean(
						column.attributeValue("primary"), false);
					String collectionEntity = column.attributeValue("entity");
					String mappingKey = column.attributeValue("mapping-key");
					String mappingTable = column.attributeValue(
						"mapping-table");
					String idType = column.attributeValue("id-type");
					String idParam = column.attributeValue("id-param");
					boolean convertNull = GetterUtil.getBoolean(
						column.attributeValue("convert-null"), true);

					EntityColumn col = new EntityColumn(
						columnName, columnDBName, columnType, primary,
						collectionEntity, mappingKey, mappingTable, idType,
						idParam, convertNull);

					if (primary) {
						pkList.add(col);
					}

					if (columnType.equals("Collection")) {
						collectionList.add(col);
					}
					else {
						regularColList.add(col);
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

					Iterator itr3 = orderCols.iterator();

					while (itr3.hasNext()) {
						Element orderColEl = (Element)itr3.next();

						String orderColName =
							orderColEl.attributeValue("name");
						boolean orderColCaseSensitive = GetterUtil.getBoolean(
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

						col = (EntityColumn)col.clone();

						col.setCaseSensitive(orderColCaseSensitive);
						col.setOrderByAscending(orderColByAscending);

						orderColsList.add(col);
					}
				}

				List finderList = new ArrayList();

				List finders = entityEl.elements("finder");

				if (uuid) {
					Element finderEl = DocumentHelper.createElement("finder");

					finderEl.addAttribute("name", "Uuid");
					finderEl.addAttribute("return-type", "Collection");

					Element finderColEl = finderEl.addElement("finder-column");

					finderColEl.addAttribute("name", "uuid");

					finders.add(0, finderEl);

					if (columnList.contains(new EntityColumn("groupId"))) {
						finderEl = DocumentHelper.createElement("finder");

						finderEl.addAttribute("name", "UUID_G");
						finderEl.addAttribute("return-type", ejbName);

						finderColEl = finderEl.addElement("finder-column");

						finderColEl.addAttribute("name", "uuid");

						finderColEl = finderEl.addElement("finder-column");

						finderColEl.addAttribute("name", "groupId");

						finders.add(1, finderEl);
					}
				}

				itr2 = finders.iterator();

				while (itr2.hasNext()) {
					Element finderEl = (Element)itr2.next();

					String finderName = finderEl.attributeValue("name");
					String finderReturn =
						finderEl.attributeValue("return-type");
					String finderWhere =
						finderEl.attributeValue("where");
					boolean finderDBIndex = GetterUtil.getBoolean(
						finderEl.attributeValue("db-index"), true);

					List finderColsList = new ArrayList();

					List finderCols = finderEl.elements("finder-column");

					Iterator itr3 = finderCols.iterator();

					while (itr3.hasNext()) {
						Element finderColEl = (Element)itr3.next();

						String finderColName =
							finderColEl.attributeValue("name");

						String finderColDBName =
							finderColEl.attributeValue("db-name");

						if (Validator.isNull(finderColDBName)) {
							finderColDBName = finderColName;

							if (_badCmpFields.contains(finderColName)) {
								finderColDBName += "_";
							}
						}

						boolean finderColCaseSensitive = GetterUtil.getBoolean(
							finderColEl.attributeValue("case-sensitive"),
							true);

						String finderColComparator = GetterUtil.getString(
							finderColEl.attributeValue("comparator"), "=");

						EntityColumn col = Entity.getColumn(
							finderColName, columnList);

						col = (EntityColumn)col.clone();

						col.setDBName(finderColDBName);
						col.setCaseSensitive(finderColCaseSensitive);
						col.setComparator(finderColComparator);

						finderColsList.add(col);
					}

					finderList.add(
						new EntityFinder(
							finderName, finderReturn, finderColsList,
							finderWhere, finderDBIndex));
				}

				List referenceList = new ArrayList();

				if (build) {
					List references = entityEl.elements("reference");

					itr2 = references.iterator();

					while (itr2.hasNext()) {
						Element reference = (Element)itr2.next();

						String refPackage =
							reference.attributeValue("package-path");
						String refEntity = reference.attributeValue("entity");

						referenceList.add(
							getEntity(refPackage + "." + refEntity));
					}
				}

				List txRequiredList = new ArrayList();

				itr2 = entityEl.elements("tx-required").iterator();

				while (itr2.hasNext()) {
					Element txRequiredEl = (Element)itr2.next();

					String txRequired = txRequiredEl.getText();

					txRequiredList.add(txRequired);
				}

				_ejbList.add(
					new Entity(
						_packagePath, _portletName, _portletShortName, ejbName,
						table, uuid, localService, remoteService,
						persistenceClass, finderClass, dataSource,
						sessionFactory, txManager, pkList, regularColList,
						collectionList, columnList, order, finderList,
						referenceList, txRequiredList));
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

					System.out.println("Building " + entity.getName());

					if (true ||
						entity.getName().equals("EmailAddress") ||
						entity.getName().equals("User")) {

						if (entity.hasColumns()) {
							_createHBM(entity);
							_createHBMUtil(entity);

							_createPersistenceImpl(entity);
							_createPersistence(entity);
							_createPersistenceUtil(entity);

							if (Validator.isNotNull(_testDir)) {
								_createPersistenceTest(entity);
							}

							_createModelImpl(entity);
							_createExtendedModelImpl(entity);

							_createModel(entity);
							_createExtendedModel(entity);

							_createModelSoap(entity);

							_createPool(entity);

							if (entity.getPKList().size() > 1) {
								_createEJBPK(entity);
							}
						}

						_createFinder(entity);
						_createFinderUtil(entity);

						if (entity.hasLocalService()) {
							_createServiceBaseImpl(entity, _LOCAL);
							_createServiceImpl(entity, _LOCAL);
							_createService(entity, _LOCAL);
							_createServiceFactory(entity, _LOCAL);
							_createServiceUtil(entity, _LOCAL);
						}

						if (entity.hasRemoteService()) {
							_createServiceBaseImpl(entity, _REMOTE);
							_createServiceImpl(entity, _REMOTE);
							_createService(entity, _REMOTE);
							_createServiceFactory(entity, _REMOTE);
							_createServiceUtil(entity, _REMOTE);

							if (Validator.isNotNull(_jsonFileName)) {
								_createServiceHttp(entity);
								_createServiceJSON(entity);

								if (entity.hasColumns()) {
									_createServiceJSONSerializer(entity);
								}

								_createServiceSoap(entity);
							}
						}
					}
				}

				_createHBMXML();
				_createModelHintsXML();
				_createSpringXML();

				if (Validator.isNotNull(_jsonFileName)) {
					_createJSONJS();
				}

				if (Validator.isNotNull(_remotingFileName)) {
					_createRemotingXML();
				}

				_createSQLIndexes();
				_createSQLTables();
				_createSQLSequences();

				_createExceptions(exceptionList);

				_createBaseModelImpl();
				_createBasePersistence();
				_createBeanLocatorUtil();
				_createDynamicDialect();
				_createFinderCache();
				_createHibernateConfiguration();
				_createHibernateUtil();
				_createPrincipalBean();
				_createProps();
				_createPropsUtil();
				_createSpringDataSourceXML();
				_createSpringUtil();
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public String getClassName(Type type) {
		int dimensions = type.getDimensions();
		String name = type.getValue();

		if (dimensions > 0) {
			StringMaker sm = new StringMaker();

			for (int i = 0; i < dimensions; i++) {
				sm.append("[");
			}

			if (name.equals("boolean")) {
				return sm.toString() + "Z";
			}
			else if (name.equals("byte")) {
				return sm.toString() + "B";
			}
			else if (name.equals("char")) {
				return sm.toString() + "C";
			}
			else if (name.equals("double")) {
				return sm.toString() + "D";
			}
			else if (name.equals("float")) {
				return sm.toString() + "F";
			}
			else if (name.equals("int")) {
				return sm.toString() + "I";
			}
			else if (name.equals("long")) {
				return sm.toString() + "J";
			}
			else if (name.equals("short")) {
				return sm.toString() + "S";
			}
			else {
				return sm.toString() + "L" + name + ";";
			}
		}

		return name;
	}

	public String getCreateTableSQL(Entity entity){
		String createTableSQL = _getCreateTableSQL(entity);

		createTableSQL = StringUtil.replace(createTableSQL, "\n", "");
		createTableSQL = StringUtil.replace(createTableSQL, "\t", "");
		createTableSQL = createTableSQL.substring(
			0, createTableSQL.length() - 1);

		return createTableSQL;
	}

	public String getDimensions(String dims) {
		return getDimensions(Integer.parseInt(dims));
	}

	public String getDimensions(int dims) {
		String dimensions = "";

		for (int i = 0; i < dims; i++) {
			dimensions += "[]";
		}

		return dimensions;
	}

	public Entity getEntity(String name) throws IOException {
		int pos = name.lastIndexOf(".");

		if (pos == -1) {
			pos = _ejbList.indexOf(new Entity(name));

			return (Entity)_ejbList.get(pos);
		}
		else {
			String refPackage = name.substring(0, pos);
			String refPackageDir = StringUtil.replace(refPackage, ".", "/");
			String refEntity = name.substring(pos + 1, name.length());
			String refFileName =
				_implDir + "/" + refPackageDir + "/service.xml";

			File refFile = new File(refFileName);

			boolean useTempFile = false;

			if (!refFile.exists()) {
				refFileName = Time.getTimestamp();
				refFile = new File(refFileName);

				ClassLoader classLoader = getClass().getClassLoader();

				FileUtil.write(
					refFileName,
					StringUtil.read(
						classLoader, refPackageDir + "/service.xml"));

				useTempFile = true;
			}

			ServiceBuilder serviceBuilder = new ServiceBuilder(
				refFileName, _hbmFileName, _modelHintsFileName, _springFileName,
				_springDataSourceFileName, _apiDir, _implDir, _jsonFileName,
				_remotingFileName, _sqlDir, _sqlFileName, _autoNamespaceTables,
				_baseModelImplPackage, _basePersistencePackage,
				_beanLocatorUtilPackage, _principalBeanPackage,
				_propsUtilPackage, _springHibernatePackage, _springUtilPackage,
				_testDir, false);

			Entity entity = serviceBuilder.getEntity(refEntity);

			if (useTempFile) {
				refFile.deleteOnExit();
			}

			return entity;
		}
	}

	public String getGeneratorClass(String idType) {
		if (Validator.isNull(idType)) {
			idType = "assigned";
		}

		return idType;
	}

	public String getNoSuchEntityException(Entity entity) {
		String noSuchEntityException = entity.getName();

		if (Validator.isNull(entity.getPortletShortName()) ||
			noSuchEntityException.startsWith(entity.getPortletShortName())) {

			noSuchEntityException = noSuchEntityException.substring(
				entity.getPortletShortName().length());
		}

		noSuchEntityException = "NoSuch" + noSuchEntityException;

		return noSuchEntityException;
	}

	public String getPrimitiveObj(String type) {
		if (type.equals("boolean")) {
			return "Boolean";
		}
		else if (type.equals("double")) {
			return "Double";
		}
		else if (type.equals("float")) {
			return "Float";
		}
		else if (type.equals("int")) {
			return "Integer";
		}
		else if (type.equals("long")) {
			return "Long";
		}
		else if (type.equals("short")) {
			return "Short";
		}
		else {
			return type;
		}
	}

	public String getPrimitiveObjValue(String colType){
		if (colType.equals("Boolean")) {
			return ".booleanValue()";
		}
		else if (colType.equals("Double")) {
			return ".doubleValue()";
		}
		else if (colType.equals("Float")) {
			return ".floatValue()";
		}
		else if (colType.equals("Integer")) {
			return ".intValue()";
		}
		else if (colType.equals("Long")) {
			return ".longValue()";
		}
		else if (colType.equals("Short")) {
			return ".shortValue()";
		}

		return StringPool.BLANK;
	}

	public String getSqlType(String model, String field, String type) {
		if (type.equals("boolean") || type.equals("Boolean")) {
			return "BOOLEAN";
		}
		else if (type.equals("double") || type.equals("Double")) {
			return "DOUBLE";
		}
		else if (type.equals("float") || type.equals("Float")) {
			return "FLOAT";
		}
		else if (type.equals("int") || type.equals("Integer")) {
			return "INTEGER";
		}
		else if (type.equals("long") || type.equals("Long")) {
			return "BIGINT";
		}
		else if (type.equals("short") || type.equals("Short")) {
			return "INTEGER";
		}
		else if (type.equals("Date")) {
			return "TIMESTAMP";
		}
		else if (type.equals("String")) {
			Map hints = ModelHintsUtil.getHints(model, field);

			if (hints != null) {
				int maxLength = GetterUtil.getInteger(
					(String)hints.get("max-length"));

				if (maxLength == 2000000) {
					return "CLOB";
				}
			}

			return "VARCHAR";
		}
		else {
			return null;
		}
	}

	public boolean isCustomMethod(JavaMethod method) {
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
		else if (methodName.equals("getPermissionChecker")) {
			return false;
		}
		else if (methodName.equals("getUser") &&
				 method.getParameters().length == 0) {

			return false;
		}
		else if (methodName.equals("getUserId") &&
				 method.getParameters().length == 0) {

			return false;
		}
		else if ((methodName.endsWith("Service")) &&
				 (methodName.startsWith("get") ||
				  methodName.startsWith("set"))) {

			return false;
		}
		else {
			return true;
		}
	}

	public boolean isSoapMethod(JavaMethod method) {
		String returnValueName = method.getReturns().getValue();

		if (returnValueName.startsWith("java.io") ||
			returnValueName.equals("java.util.Map") ||
			returnValueName.equals("java.util.Properties") ||
			returnValueName.startsWith("javax")) {

			return false;
		}

		JavaParameter[] parameters = method.getParameters();

		for (int i = 0; i < parameters.length; i++) {
			JavaParameter javaParameter = parameters[i];

			String parameterTypeName =
				javaParameter.getType().getValue() +
					_getDimensions(javaParameter.getType());

			if ((parameterTypeName.indexOf(
					"com.liferay.portal.model.") != -1) ||
				(parameterTypeName.equals(
					"com.liferay.portal.theme.ThemeDisplay")) ||
				(parameterTypeName.equals(
					"com.liferay.portlet.PortletPreferencesImpl")) ||
				 parameterTypeName.startsWith("java.io") ||
				 //parameterTypeName.startsWith("java.util.List") ||
				 //parameterTypeName.startsWith("java.util.Locale") ||
				 parameterTypeName.startsWith("java.util.Map") ||
				 parameterTypeName.startsWith("java.util.Properties") ||
				 parameterTypeName.startsWith("javax")) {

				return false;
			}
		}

		return true;
	}

	private static String _getPackagePath(File file) throws IOException {
		String fileName = StringUtil.replace(file.toString(), "\\", "/");

		int x = fileName.indexOf("src/");

		if (x == -1) {
			x = fileName.indexOf("test/");
		}

		int y = fileName.lastIndexOf("/");

		fileName = fileName.substring(x + 4, y);

		return StringUtil.replace(fileName, "/", ".");
	}

	private void _createBaseModelImpl() throws Exception {
		if (_baseModelImplPackage.equals("com.liferay.portal.model.impl")) {
			return;
		}

		// Content

		String content = _processTemplate(_tplBaseModeImpl);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_baseModelImplPackage, ".", "/") +
					"/BaseModelImpl.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createBasePersistence() throws Exception {
		if (_basePersistencePackage.equals(
				"com.liferay.portal.service.persistence")) {

			return;
		}

		// Content

		String content = _processTemplate(_tplBasePersistence);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_basePersistencePackage, ".", "/") +
					"/BasePersistence.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createBeanLocatorUtil() throws Exception {
		if (_beanLocatorUtilPackage.equals("com.liferay.portal.kernel.bean")) {
			return;
		}

		// Content

		String content = _processTemplate(_tplBeanLocatorUtil);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_beanLocatorUtilPackage, ".", "/") +
					"/BeanLocatorUtil.java");

		writeFile(ejbFile, content);
	}

	private void _createDynamicDialect() throws Exception {
		if (_springHibernatePackage.equals(
				"com.liferay.portal.spring.hibernate")) {

			return;
		}

		// Content

		String content = _processTemplate(_tplDynamicDialect);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_springHibernatePackage, ".", "/") +
					"/DynamicDialect.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createEJBPK(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplEjbPk, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/persistence/" +
				entity.getPKClassName() + ".java");

		writeFile(ejbFile, content);
	}

	private void _createExceptions(List exceptions) throws Exception {
		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity) _ejbList.get(i);

			if (entity.hasColumns()) {
				exceptions.add(getNoSuchEntityException(entity));
			}
		}

		for (int i = 0; i < exceptions.size(); i++) {
			String exception = (String) exceptions.get(i);

			File exceptionFile = new File(
				_serviceOutputPath + "/" + exception + "Exception.java");

			if (!exceptionFile.exists()) {
				Map context = _getContext();

				context.put("exception", exception);

				String content = _processTemplate(_tplException, context);

				FileUtil.write(exceptionFile, content);
			}
		}
	}

	private void _createExtendedModel(Entity entity) throws Exception {
		JavaClass javaClass = _getJavaClass(
			_outputPath + "/model/impl/" + entity.getName() + "Impl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplExtendedModel, context);

		// Write file

		File modelFile = new File(
			_serviceOutputPath + "/model/" + entity.getName() + ".java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(modelFile, content, jalopySettings);
	}

	private void _createExtendedModelImpl(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplExtendedModelImpl, context);

		// Write file

		File modelFile = new File(
			_outputPath + "/model/impl/" + entity.getName() + "Impl.java");

		if (!modelFile.exists()) {
			writeFile(modelFile, content);
		}
	}

	private void _createFinder(Entity entity) throws Exception {
		if (!entity.hasFinderClass()) {
			return;
		}

		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/persistence/" + entity.getName() +
				"FinderImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplFinder, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/persistence/" + entity.getName() +
				"Finder.java");

		writeFile(ejbFile, content);
	}

	private void _createFinderCache() throws Exception {
		if (_springHibernatePackage.equals("com.liferay.portal.spring.hibernate")) {
			return;
		}

		// Content

		String content = _processTemplate(_tplFinderCache);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_springHibernatePackage, ".", "/") +
				"/FinderCache.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createFinderUtil(Entity entity) throws Exception {
		if (!entity.hasFinderClass()) {
			return;
		}

		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/persistence/" + entity.getName() +
				"FinderImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplFinderUtil, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/persistence/" + entity.getName() +
				"FinderUtil.java");

		writeFile(ejbFile, content);
	}

	private void _createHBM(Entity entity) throws IOException {
		File ejbFile = new File(
			_outputPath + "/service/persistence/" + entity.getName() +
				"HBM.java");

		if (ejbFile.exists()) {
			System.out.println("Removing deprecated " + ejbFile);

			ejbFile.delete();
		}
	}

	private void _createHBMUtil(Entity entity) throws IOException {
		File ejbFile = new File(
			_outputPath + "/service/persistence/" + entity.getName() +
				"HBMUtil.java");

		if (ejbFile.exists()) {
			System.out.println("Removing deprecated " + ejbFile);

			ejbFile.delete();
		}
	}

	private void _createHBMXML() throws Exception {
		Map context = _getContext();

		context.put("entities", _ejbList);

		// Content

		String content = _processTemplate(_tplHbmXml, context);

		File xmlFile = new File(_hbmFileName);

		if (!xmlFile.exists()) {
			String xml =
				"<?xml version=\"1.0\"?>\n" +
				"<!DOCTYPE hibernate-mapping PUBLIC \"-//Hibernate/Hibernate Mapping DTD 3.0//EN\" \"http://hibernate.sourceforge.net/hibernate-mapping-3.0.dtd\">\n" +
				"\n" +
				"<hibernate-mapping default-lazy=\"false\" auto-import=\"false\">\n" +
				"</hibernate-mapping>";

			FileUtil.write(xmlFile, xml);
		}

		String oldContent = FileUtil.read(xmlFile);
		String newContent = _fixHBMXML(oldContent);

		int firstClass = newContent.indexOf(
			"<class name=\"" + _packagePath + ".model.impl.");
		int lastClass = newContent.lastIndexOf(
			"<class name=\"" + _packagePath + ".model.impl.");

		if (firstClass == -1) {
			int x = newContent.indexOf("</hibernate-mapping>");

			newContent =
				newContent.substring(0, x) + content +
				newContent.substring(x, newContent.length());
		}
		else {
			firstClass = newContent.lastIndexOf("<class", firstClass) - 1;
			lastClass = newContent.indexOf("</class>", lastClass) + 9;

			newContent =
				newContent.substring(0, firstClass) + content +
					newContent.substring(lastClass, newContent.length());
		}

		newContent = _formatXML(newContent);

		if (!oldContent.equals(newContent)) {
			FileUtil.write(xmlFile, newContent);
		}
	}

	private void _createHibernateConfiguration() throws Exception {
		if (_springHibernatePackage.equals(
				"com.liferay.portal.spring.hibernate")) {

			return;
		}

		// Content

		String content = _processTemplate(_tplHibernateConfiguration);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_springHibernatePackage, ".", "/") +
					"/HibernateConfiguration.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createHibernateUtil() throws Exception {
		if (_springHibernatePackage.equals(
				"com.liferay.portal.spring.hibernate")) {

			return;
		}

		// Content

		String content = _processTemplate(_tplHibernateUtil);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_springHibernatePackage, ".", "/") +
				"/HibernateUtil.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createJSONJS() throws Exception {
		StringMaker content = new StringMaker();

		if (_ejbList.size() > 0) {
			content.append(_processTemplate(_tplJsonJs));
		}

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			if (entity.hasRemoteService()) {
				JavaClass javaClass = _getJavaClass(
					_outputPath + "/service/http/" + entity.getName() +
						"ServiceJSON.java");

				JavaMethod[] methods = javaClass.getMethods();

				Set jsonMethods = new LinkedHashSet();

				for (int j = 0; j < methods.length; j++) {
					JavaMethod javaMethod = methods[j];

					String methodName = javaMethod.getName();

					if (javaMethod.isPublic()) {
						jsonMethods.add(methodName);
					}
				}

				if (jsonMethods.size() > 0) {
					Map context = _getContext();

					context.put("entity", entity);
					context.put("methods", jsonMethods);

					content.append("\n\n");
					content.append(_processTemplate(_tplJsonJsMethod, context));
				}
			}
		}

		File jsonFile = new File(_jsonFileName);

		if (!jsonFile.exists()) {
			FileUtil.write(jsonFile, "");
		}

		String oldContent = FileUtil.read(jsonFile);
		String newContent = new String(oldContent);

		int oldBegin = oldContent.indexOf(
			"Liferay.Service." + _portletShortName);

		int oldEnd = oldContent.lastIndexOf(
			"Liferay.Service." + _portletShortName);

		oldEnd = oldContent.indexOf("};", oldEnd);

		int newBegin = newContent.indexOf(
			"Liferay.Service." + _portletShortName);

		int newEnd = newContent.lastIndexOf(
			"Liferay.Service." + _portletShortName);

		newEnd = newContent.indexOf("};", newEnd);

		if (newBegin == -1) {
			newContent = oldContent + "\n\n" + content.toString().trim();
		}
		else {
			newContent =
				newContent.substring(0, oldBegin) + content.toString().trim() +
					newContent.substring(oldEnd + 2, newContent.length());
		}

		if (!oldContent.equals(newContent)) {
			FileUtil.write(jsonFile, newContent);
		}
	}

	private void _createModel(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplModel, context);

		// Write file

		File modelFile = new File(
			_serviceOutputPath + "/model/" + entity.getName() + "Model.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(modelFile, content, jalopySettings);
	}

	private void _createModelHintsXML() throws Exception {
		Map context = _getContext();

		context.put("entities", _ejbList);

		// Content

		String content = _processTemplate(_tplModelHintsXml, context);

		File xmlFile = new File(_modelHintsFileName);

		if (!xmlFile.exists()) {
			String xml =
				"<?xml version=\"1.0\"?>\n" +
				"\n" +
				"<model-hints>\n" +
				"</model-hints>";

			FileUtil.write(xmlFile, xml);
		}

		String oldContent = FileUtil.read(xmlFile);
		String newContent = new String(oldContent);

		int firstModel = newContent.indexOf(
			"<model name=\"" + _packagePath + ".model.");
		int lastModel = newContent.lastIndexOf(
			"<model name=\"" + _packagePath + ".model.");

		if (firstModel == -1) {
			int x = newContent.indexOf("</model-hints>");

			newContent =
				newContent.substring(0, x) + content +
					newContent.substring(x, newContent.length());
		}
		else {
			firstModel = newContent.lastIndexOf("<model", firstModel) - 1;
			lastModel = newContent.indexOf("</model>", lastModel) + 9;

			newContent =
				newContent.substring(0, firstModel) + content +
				newContent.substring(lastModel, newContent.length());
		}

		newContent = _formatXML(newContent);

		if (!oldContent.equals(newContent)) {
			FileUtil.write(xmlFile, newContent);
		}
	}

	private void _createModelImpl(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplModelImpl, context);

		// Write file

		File modelFile = new File(
			_outputPath + "/model/impl/" + entity.getName() + "ModelImpl.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(modelFile, content, jalopySettings);
	}

	private void _createModelSoap(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplModelSoap, context);

		// Write file

		File modelFile = new File(
			_serviceOutputPath + "/model/" + entity.getName() + "Soap.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(modelFile, content, jalopySettings);
	}

	private void _createPersistence(Entity entity) throws Exception {
		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/persistence/" + entity.getName() +
				"PersistenceImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplPersistence, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/persistence/" + entity.getName() +
				"Persistence.java");

		writeFile(ejbFile, content);

		if (!_serviceOutputPath.equals(_outputPath)) {
			ejbFile = new File(
				_outputPath + "/service/persistence/" + entity.getName() +
					"Persistence.java");

			if (ejbFile.exists()) {
				System.out.println("Relocating " + ejbFile);

				ejbFile.delete();
			}
		}
	}

	private void _createPersistenceImpl(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplPersistenceImpl, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/persistence/" + entity.getName() +
				"PersistenceImpl.java");

		writeFile(ejbFile, content);
	}

	private void _createPersistenceTest(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplPersistenceTest, context);

		// Write file

		File ejbFile = new File(
			_testOutputPath + "/service/persistence/" + entity.getName() +
				"PersistenceTest.java");

		writeFile(ejbFile, content);
	}

	private void _createPersistenceUtil(Entity entity) throws Exception {
		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/persistence/" + entity.getName() +
				"PersistenceImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplPersistenceUtil, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/persistence/" + entity.getName() +
				"Util.java");

		writeFile(ejbFile, content);

		if (!_serviceOutputPath.equals(_outputPath)) {
			ejbFile = new File(
				_outputPath + "/service/persistence/" + entity.getName() +
					"Util.java");

			if (ejbFile.exists()) {
				System.out.println("Relocating " + ejbFile);

				ejbFile.delete();
			}
		}
	}

	private void _createPool(Entity entity) throws IOException {
		File ejbFile = new File(
			_outputPath + "/service/persistence/" + entity.getName() +
				"Pool.java");

		if (ejbFile.exists()) {
			System.out.println("Removing deprecated " + ejbFile);

			ejbFile.delete();
		}
	}

	private void _createPrincipalBean() throws Exception {
		if (_principalBeanPackage.equals("com.liferay.portal.service.impl")) {
			return;
		}

		// Content

		String content = _processTemplate(_tplPrincipalBean);

		// Write file

		File ejbFile = new File(
			_implDir + "/" +
				StringUtil.replace(_principalBeanPackage, ".", "/") +
					"/PrincipalBean.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createProps() throws Exception {
		if (_propsUtilPackage.equals("com.liferay.portal.util")) {
			return;
		}

		// Content

		File propsFile = new File(_implDir + "/portlet-service.properties");

		long buildNumber = 1;

		if (propsFile.exists()) {
			Properties props = PropertiesUtil.load(FileUtil.read(propsFile));

			buildNumber = GetterUtil.getLong(
				props.getProperty("build.number")) + 1;
		}

		Map context = _getContext();

		context.put("buildNumber", new Long(buildNumber));
		context.put("currentTimeMillis", new Long(System.currentTimeMillis()));

		String content = _processTemplate(_tplProps, context);

		// Write file

		FileUtil.write(propsFile, content, true);
	}

	private void _createPropsUtil() throws Exception {
		if (_propsUtilPackage.equals("com.liferay.portal.util")) {
			return;
		}

		// Content

		String content = _processTemplate(_tplPropsUtil);

		// Write file

		File ejbFile = new File(
			_implDir + "/" + StringUtil.replace(_propsUtilPackage, ".", "/") +
				"/PropsUtil.java");

		writeFile(ejbFile, content);
	}

	private void _createRemotingXML() throws Exception {
		StringMaker sm = new StringMaker();

		Document doc = PortalUtil.readDocumentFromFile(
			new File(_springFileName), true);

		Iterator itr = doc.getRootElement().elements("bean").iterator();

		while (itr.hasNext()) {
			Element beanEl = (Element)itr.next();

			String beanId = beanEl.attributeValue("id");

			if (beanId.endsWith("ServiceFactory") &&
				!beanId.endsWith("LocalServiceFactory")) {

				String serviceName = beanId.substring(0, beanId.length() - 7);

				String serviceMapping = serviceName;
				serviceMapping = StringUtil.replace(
					serviceMapping, ".service.", ".service.spring.");
				serviceMapping = StringUtil.replace(
					serviceMapping, ".", "_");

				Map context = _getContext();

				context.put("serviceName", serviceName);
				context.put("serviceMapping", serviceMapping);

				sm.append(_processTemplate(_tplRemotingXml, context));
			}
		}

		File outputFile = new File(_remotingFileName);

		if (!outputFile.exists()) {
			return;
		}

		String content = FileUtil.read(outputFile);
		String newContent = content;

		int x = content.indexOf("<bean ");
		int y = content.lastIndexOf("</bean>") + 8;

		if (x != -1) {
			newContent =
				content.substring(0, x - 1) + sm.toString() +
					content.substring(y, content.length());
		}
		else {
			x = content.indexOf("</beans>");

			newContent =
				content.substring(0, x) + sm.toString() +
					content.substring(x, content.length());
		}

		newContent = _formatXML(newContent);

		if (!content.equals(newContent)) {
			FileUtil.write(outputFile, newContent);

			System.out.println(outputFile.toString());
		}
	}

	private void _createService(Entity entity, int sessionType)
		throws Exception {

		String serviceComments = "This is a remote service. Methods of this service are expected to have security checks based on the propagated JAAS credentials because this service can be accessed remotely.";

		JavaClass javaClass = _getJavaClass(_outputPath + "/service/impl/" + entity.getName() + (sessionType != _REMOTE ? "Local" : "") + "ServiceImpl.java");

		JavaMethod[] methods = javaClass.getMethods();

		if (sessionType == _LOCAL) {
			if (javaClass.getSuperClass().getValue().endsWith(
					entity.getName() + "LocalServiceBaseImpl")) {

				JavaClass parentJavaClass = _getJavaClass(
					_outputPath + "/service/base/" + entity.getName() +
						"LocalServiceBaseImpl.java");

				JavaMethod[] parentMethods = parentJavaClass.getMethods();

				JavaMethod[] allMethods = new JavaMethod[parentMethods.length + methods.length];

				ArrayUtil.combine(parentMethods, methods, allMethods);

				methods = allMethods;
			}

			serviceComments = "This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.";
		}

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", methods);
		context.put("sessionTypeName",_getSessionTypeName(sessionType));
		context.put("serviceComments", serviceComments);

		// Content

		String content = _processTemplate(_tplService, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/" + entity.getName() +
				_getSessionTypeName(sessionType) + "Service.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createServiceBaseImpl(Entity entity, int sessionType)
		throws Exception {

		Map context = _getContext();

		context.put("entity", entity);
		context.put("sessionTypeName",_getSessionTypeName(sessionType));
		context.put(
			"referenceList", _mergeReferenceList(entity.getReferenceList()));

		// Content

		String content = _processTemplate(_tplServiceBaseImpl, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/base/" + entity.getName() +
				_getSessionTypeName(sessionType) + "ServiceBaseImpl.java");

		writeFile(ejbFile, content);
	}

	private void _createServiceFactory(Entity entity, int sessionType)
		throws Exception {

		Map context = _getContext();

		context.put("entity", entity);
		context.put("sessionTypeName", _getSessionTypeName(sessionType));

		// Content

		String content = _processTemplate(_tplServiceFactory, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/" + entity.getName() +
				_getSessionTypeName(sessionType) + "ServiceFactory.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createServiceHttp(Entity entity) throws Exception {
		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/impl/" + entity.getName() +
				"ServiceImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());
		context.put("hasHttpMethods", new Boolean(_hasHttpMethods(javaClass)));

		// Content

		String content = _processTemplate(_tplServiceHttp, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/http/" + entity.getName() +
				"ServiceHttp.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createServiceImpl(Entity entity, int sessionType)
		throws Exception {

		Map context = _getContext();

		context.put("entity", entity);
		context.put("sessionTypeName", _getSessionTypeName(sessionType));

		// Content

		String content = _processTemplate(_tplServiceImpl, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/impl/" + entity.getName() +
				_getSessionTypeName(sessionType) + "ServiceImpl.java");

		if (!ejbFile.exists()) {
			writeFile(ejbFile, content);
		}
	}

	private void _createServiceJSON(Entity entity) throws Exception {
		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/impl/" + entity.getName() +
				"ServiceImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplServiceJson, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/http/" + entity.getName() +
				"ServiceJSON.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createServiceJSONSerializer(Entity entity) throws Exception {
		Map context = _getContext();

		context.put("entity", entity);

		// Content

		String content = _processTemplate(_tplServiceJsonSerializer, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/http/" + entity.getName() +
				"JSONSerializer.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createServiceSoap(Entity entity) throws Exception {
		JavaClass javaClass = _getJavaClass(
			_outputPath + "/service/impl/" + entity.getName() +
				"ServiceImpl.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());

		// Content

		String content = _processTemplate(_tplServiceSoap, context);

		// Write file

		File ejbFile = new File(
			_outputPath + "/service/http/" + entity.getName() +
				"ServiceSoap.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createServiceUtil(Entity entity, int sessionType)
		throws Exception {

		JavaClass javaClass = _getJavaClass(
			_serviceOutputPath + "/service/" + entity.getName() +
				(sessionType != _REMOTE ? "Local" : "") + "Service.java");

		Map context = _getContext();

		context.put("entity", entity);
		context.put("methods", javaClass.getMethods());
		context.put("sessionTypeName", _getSessionTypeName(sessionType));

		// Content

		String content = _processTemplate(_tplServiceUtil, context);

		// Write file

		File ejbFile = new File(
			_serviceOutputPath + "/service/" + entity.getName() +
				_getSessionTypeName(sessionType) + "ServiceUtil.java");

		Map jalopySettings = new HashMap();

		jalopySettings.put("keepJavadoc", Boolean.TRUE);

		writeFile(ejbFile, content, jalopySettings);
	}

	private void _createSpringDataSourceXML() throws Exception {
		if (Validator.isNull(_springDataSourceFileName)) {
			return;
		}

		// Content

		String content = _processTemplate(_tplSpringDataSourceXml);

		// Write file

		File ejbFile = new File(_springDataSourceFileName);

		FileUtil.write(ejbFile, content, true);
	}

	private void _createSpringUtil() throws Exception {
		if (_springUtilPackage.equals("com.liferay.portal.spring.util")) {
			return;
		}

		// Content

		String content = _processTemplate(_tplSpringUtil);

		// Write file

		File ejbFile = new File(
			_implDir + "/" + StringUtil.replace(_springUtilPackage, ".", "/") +
				"/SpringUtil.java");

		FileUtil.write(ejbFile, content, true);
	}

	private void _createSpringXML() throws Exception {
		Map context = _getContext();

		context.put("entities", _ejbList);

		// Content

		String content = _processTemplate(_tplSpringXml, context);

		File xmlFile = new File(_springFileName);

		if (!xmlFile.exists()) {
			String xml =
				"<?xml version=\"1.0\"?>\n" +
				"<!DOCTYPE beans PUBLIC \"-//SPRING//DTD BEAN//EN\" \"http://www.springframework.org/dtd/spring-beans.dtd\">\n" +
				"\n" +
				"<beans>\n" +
				"</beans>";

			FileUtil.write(xmlFile, xml);
		}

		String oldContent = FileUtil.read(xmlFile);
		String newContent = _fixSpringXML(oldContent);

		int x = oldContent.indexOf("<beans>");
		int y = oldContent.lastIndexOf("</beans>");

		int firstSession = newContent.indexOf(
			"<bean id=\"" + _packagePath + ".service.", x);

		int lastSession = newContent.lastIndexOf(
			"<bean id=\"" + _packagePath + ".service.", y);

		if (firstSession == -1 || firstSession > y) {
			x = newContent.indexOf("</beans>");
			newContent =
				newContent.substring(0, x) + content +
				newContent.substring(x, newContent.length());
		}
		else {
			firstSession = newContent.lastIndexOf("<bean", firstSession) - 1;
			lastSession = newContent.indexOf("</bean>", lastSession) + 8;

			newContent =
				newContent.substring(0, firstSession) + content +
				newContent.substring(lastSession, newContent.length());
		}

		newContent = _formatXML(newContent);

		if (!oldContent.equals(newContent)) {
			FileUtil.write(xmlFile, newContent);
		}
	}

	private void _createSQLIndexes() throws IOException {
		if (!FileUtil.exists(_sqlDir)) {
			return;
		}

		// indexes.sql

		File sqlFile = new File(_sqlDir + "/indexes.sql");

		if (!sqlFile.exists()) {
			FileUtil.write(sqlFile, "");
		}

		Map indexSQLs = new TreeMap();

		BufferedReader br = new BufferedReader(new FileReader(sqlFile));

		while (true) {
			String indexSQL = br.readLine();

			if (indexSQL == null) {
				break;
			}

			if (Validator.isNotNull(indexSQL.trim())) {
				int pos = indexSQL.indexOf(" on ");

				String indexSpec = indexSQL.substring(pos + 4);

				indexSQLs.put(indexSpec, indexSQL);
			}
		}

		br.close();

		// indexes.properties

		File propsFile = new File(_sqlDir + "/indexes.properties");

		if (!propsFile.exists()) {
			FileUtil.write(propsFile, "");
		}

		Map indexProps = new TreeMap();

		br = new BufferedReader(new FileReader(propsFile));

		while (true) {
			String indexMapping = br.readLine();

			if (indexMapping == null) {
				break;
			}

			if (Validator.isNotNull(indexMapping.trim())) {
				String[] splitIndexMapping = indexMapping.split("\\=");

				indexProps.put(splitIndexMapping[1], splitIndexMapping[0]);
			}
		}

		br.close();

		// indexes.sql

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			List finderList = entity.getFinderList();

			for (int j = 0; j < finderList.size(); j++) {
				EntityFinder finder = (EntityFinder)finderList.get(j);

				if (finder.isDBIndex()) {
					StringMaker sm = new StringMaker();

					sm.append(entity.getTable() + " (");

					List finderColsList = finder.getColumns();

					for (int k = 0; k < finderColsList.size(); k++) {
						EntityColumn col = (EntityColumn)finderColsList.get(k);

						sm.append(col.getDBName());

						if ((k + 1) != finderColsList.size()) {
							sm.append(", ");
						}
					}

					sm.append(");");

					String indexSpec = sm.toString();

					String indexHash =
						Integer.toHexString(indexSpec.hashCode()).toUpperCase();

					String indexName = "IX_" + indexHash;

					sm = new StringMaker();

					sm.append("create index " + indexName + " on ");
					sm.append(indexSpec);

					indexSQLs.put(indexSpec, sm.toString());

					String finderName =
						entity.getTable() + StringPool.PERIOD +
							finder.getName();

					indexProps.put(finderName, indexName);
				}
			}
		}

		StringMaker sm = new StringMaker();

		Iterator itr = indexSQLs.values().iterator();

		String prevEntityName = null;

		while (itr.hasNext()) {
			String indexSQL = (String)itr.next();

			String entityName = indexSQL.split(" ")[4];

			if ((prevEntityName != null) &&
				(!prevEntityName.equals(entityName))) {

				sm.append("\n");
			}

			sm.append(indexSQL);

			if (itr.hasNext()) {
				sm.append("\n");
			}

			prevEntityName = entityName;
		}

		FileUtil.write(sqlFile, sm.toString(), true);

		// indexes.properties

		sm = new StringMaker();

		itr = indexProps.keySet().iterator();

		prevEntityName = null;

		while (itr.hasNext()) {
			String finderName = (String)itr.next();

			String indexName = (String)indexProps.get(finderName);

			String entityName = finderName.split("\\.")[0];

			if ((prevEntityName != null) &&
				(!prevEntityName.equals(entityName))) {

				sm.append("\n");
			}

			sm.append(indexName + StringPool.EQUAL + finderName);

			if (itr.hasNext()) {
				sm.append("\n");
			}

			prevEntityName = entityName;
		}

		FileUtil.write(propsFile, sm.toString(), true);
	}

	private void _createSQLSequences() throws IOException {
		if (!FileUtil.exists(_sqlDir)) {
			return;
		}

		File sqlFile = new File(_sqlDir + "/sequences.sql");

		if (!sqlFile.exists()) {
			FileUtil.write(sqlFile, "");
		}

		Set sequenceSQLs = new TreeSet();

		BufferedReader br = new BufferedReader(new FileReader(sqlFile));

		while (true) {
			String sequenceSQL = br.readLine();

			if (sequenceSQL == null) {
				break;
			}

			if (Validator.isNotNull(sequenceSQL)) {
				sequenceSQLs.add(sequenceSQL);
			}
		}

		br.close();

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			List columnList = entity.getColumnList();

			for (int j = 0; j < columnList.size(); j++) {
				EntityColumn column = (EntityColumn)columnList.get(j);

				if ("sequence".equals(column.getIdType())) {
					StringMaker sm = new StringMaker();

					String sequenceName = column.getIdParam();

					if (sequenceName.length() > 30) {
						sequenceName = sequenceName.substring(0, 30);
					}

					sm.append("create sequence " + sequenceName + ";");

					String sequenceSQL = sm.toString();

					if (!sequenceSQLs.contains(sequenceSQL)) {
						sequenceSQLs.add(sequenceSQL);
					}
				}
			}
		}

		StringMaker sm = new StringMaker();

		Iterator itr = sequenceSQLs.iterator();

		while (itr.hasNext()) {
			String sequenceSQL = (String)itr.next();

			sm.append(sequenceSQL);

			if (itr.hasNext()) {
				sm.append("\n");
			}
		}

		FileUtil.write(sqlFile, sm.toString(), true);
	}

	private void _createSQLTables() throws IOException {
		if (!FileUtil.exists(_sqlDir)) {
			return;
		}

		File sqlFile = new File(_sqlDir + "/" + _sqlFileName);

		if (!sqlFile.exists()) {
			FileUtil.write(sqlFile, StringPool.BLANK);
		}

		for (int i = 0; i < _ejbList.size(); i++) {
			Entity entity = (Entity)_ejbList.get(i);

			String createTableSQL = _getCreateTableSQL(entity);

			if (Validator.isNotNull(createTableSQL)) {
				_createSQLTables(sqlFile, createTableSQL, entity, true);

				File updateSQLFile = new File(
					_sqlDir + "/update-4.3.6-4.4.0.sql");

				if (updateSQLFile.exists()) {
					_createSQLTables(
						updateSQLFile, createTableSQL, entity, false);
				}
			}
		}
	}

	private void _createSQLTables(
			File sqlFile, String newCreateTableString, Entity entity,
			boolean addMissingTables)
		throws IOException {

		if (!sqlFile.exists()) {
			FileUtil.write(sqlFile, StringPool.BLANK);
		}

		String content = FileUtil.read(sqlFile);

		int x = content.indexOf(_CREATE_TABLE + entity.getTable() + " (");
		int y = content.indexOf(");", x);

		if (x != -1) {
			String oldCreateTableString = content.substring(x + 1, y);

			if (!oldCreateTableString.equals(newCreateTableString)) {
				content =
					content.substring(0, x) + newCreateTableString +
						content.substring(y + 2, content.length());

				FileUtil.write(sqlFile, content);
			}
		}
		else if (addMissingTables) {
			StringMaker sm = new StringMaker();

			BufferedReader br = new BufferedReader(new StringReader(content));

			String line = null;
			boolean appendNewTable = true;

			while ((line = br.readLine()) != null) {
				if (appendNewTable && line.startsWith(_CREATE_TABLE)) {
					x = _CREATE_TABLE.length();
					y = line.indexOf(" ", x);

					String tableName = line.substring(x, y);

					if (tableName.compareTo(entity.getTable()) > 0) {
						sm.append(newCreateTableString + "\n\n");

						appendNewTable = false;
					}
				}

				sm.append(line).append('\n');
			}

			if (appendNewTable) {
				sm.append("\n" + newCreateTableString);
			}

			br.close();

			FileUtil.write(sqlFile, sm.toString(), true);
		}
	}

	private String _fixHBMXML(String content) throws IOException {
		StringMaker sm = new StringMaker();

		BufferedReader br = new BufferedReader(new StringReader(content));

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.startsWith("\t<class name=\"")) {
				line = StringUtil.replace(
					line,
					new String[] {
						".service.persistence.", "HBM\" table=\""
					},
					new String[] {
						".model.", "\" table=\""
					});

				if (line.indexOf(".model.impl.") == -1) {
					line = StringUtil.replace(
						line,
						new String[] {
							".model.", "\" table=\""
						},
						new String[] {
							".model.impl.", "Impl\" table=\""
						});
				}
			}

			sm.append(line);
			sm.append('\n');
		}

		br.close();

		return sm.toString().trim();
	}

	private String _fixSpringXML(String content) throws IOException {
		return StringUtil.replace(content, ".service.spring.", ".service.");
	}

	private String _formatXML(String xml)
		throws DocumentException, IOException {

		String doctype = null;

		int x = xml.indexOf("<!DOCTYPE");

		if (x != -1) {
			int y = xml.indexOf(">", x) + 1;

			doctype = xml.substring(x, y);

			xml = xml.substring(0, x) + "\n" + xml.substring(y);
		}

		xml = StringUtil.replace(xml, '\r', "");
		xml = XMLFormatter.toString(xml);
		xml = StringUtil.replace(xml, "\"/>", "\" />");

		if (Validator.isNotNull(doctype)) {
			x = xml.indexOf("?>") + 2;

			xml = xml.substring(0, x) + "\n" + doctype + xml.substring(x);
		}

		return xml;
	}

	private Map _getContext() {
		Map context = new HashMap();

		context.put("hbmFileName", _hbmFileName);
		context.put("modelHintsFileName", _modelHintsFileName);
		context.put("springFileName", _springFileName);
		context.put("springDataSourceFileName", _springDataSourceFileName);
		context.put("apiDir", _apiDir);
		context.put("implDir", _implDir);
		context.put("jsonFileName", _jsonFileName);
		context.put("sqlDir", _sqlDir);
		context.put("sqlFileName", _sqlFileName);
		context.put("baseModelImplPackage", _baseModelImplPackage);
		context.put("basePersistencePackage", _basePersistencePackage);
		context.put("beanLocatorUtilPackage", _beanLocatorUtilPackage);
		context.put("principalBeanPackage", _principalBeanPackage);
		context.put("propsUtilPackage", _propsUtilPackage);
		context.put("springHibernatePackage", _springHibernatePackage);
		context.put("springUtilPackage", _springUtilPackage);
		context.put("portletName", _portletName);
		context.put("portletShortName", _portletShortName);
		context.put("portletPackageName", _portletPackageName);
		context.put("outputPath", _outputPath);
		context.put("serviceOutputPath", _serviceOutputPath);
		context.put("packagePath", _packagePath);
		context.put("serviceBuilder", this);

		context.put("stringUtil", StringUtil_IW.getInstance());

		try {
			BeansWrapper wrapper = BeansWrapper.getDefaultInstance();

			TemplateHashModel staticModels = wrapper.getStaticModels();

			context.put(
				"modelHintsUtil",
				staticModels.get("com.liferay.portal.model.ModelHintsUtil"));
			context.put(
				"validator",
				staticModels.get("com.liferay.portal.kernel.util.Validator"));
		}
		catch (TemplateModelException tme) {
		}

		return context;
	}

	private String _getCreateTableSQL(Entity entity) {
		List pkList = entity.getPKList();
		List regularColList = entity.getRegularColList();

		if (regularColList.size() == 0) {
			return null;
		}

		StringMaker sm = new StringMaker();

		sm.append(_CREATE_TABLE + entity.getTable() + " (\n");

		for (int i = 0; i < regularColList.size(); i++) {
			EntityColumn col = (EntityColumn)regularColList.get(i);

			String colName = col.getName();
			String colType = col.getType();
			String colIdType = col.getIdType();

			sm.append("\t" + col.getDBName());
			sm.append(" ");

			if (colType.equalsIgnoreCase("boolean")) {
				sm.append("BOOLEAN");
			}
			else if (colType.equalsIgnoreCase("double") ||
					 colType.equalsIgnoreCase("float")) {

				sm.append("DOUBLE");
			}
			else if (colType.equals("int") ||
					 colType.equals("Integer") ||
					 colType.equalsIgnoreCase("short")) {

				sm.append("INTEGER");
			}
			else if (colType.equalsIgnoreCase("long")) {
				sm.append("LONG");
			}
			else if (colType.equals("String")) {
				Map hints = ModelHintsUtil.getHints(
					_packagePath + ".model." + entity.getName(), colName);

				int maxLength = 75;

				if (hints != null) {
					maxLength = GetterUtil.getInteger(
						(String)hints.get("max-length"), maxLength);
				}

				if (maxLength < 4000) {
					sm.append("VARCHAR(" + maxLength + ")");
				}
				else if (maxLength == 4000) {
					sm.append("STRING");
				}
				else if (maxLength > 4000) {
					sm.append("TEXT");
				}
			}
			else if (colType.equals("Date")) {
				sm.append("DATE null");
			}
			else {
				sm.append("invalid");
			}

			if (col.isPrimary()) {
				sm.append(" not null");

				if (!entity.hasCompoundPK()) {
					sm.append(" primary key");
				}
			}
			else if (colType.equals("String")) {
				sm.append(" null");
			}

			if (Validator.isNotNull(colIdType) &&
				colIdType.equals("identity")) {

				sm.append(" IDENTITY");
			}

			if (((i + 1) != regularColList.size()) ||
				(entity.hasCompoundPK())) {

				sm.append(",");
			}

			sm.append("\n");
		}

		if (entity.hasCompoundPK()) {
			sm.append("\tprimary key (");

			for (int j = 0; j < pkList.size(); j++) {
				EntityColumn pk = (EntityColumn)pkList.get(j);

				sm.append(pk.getDBName());

				if ((j + 1) != pkList.size()) {
					sm.append(", ");
				}
			}

			sm.append(")\n");
		}

		sm.append(");");

		return sm.toString();
	}

	private String _getDimensions(Type type) {
		String dimensions = "";

		for (int i = 0; i < type.getDimensions(); i++) {
			dimensions += "[]";
		}

		return dimensions;
	}

	private JavaClass _getJavaClass(String fileName) throws IOException {
		int pos = fileName.indexOf(_implDir + "/") + _implDir.length();

		String srcFile = fileName.substring(pos + 1, fileName.length());
		String className = StringUtil.replace(
			srcFile.substring(0, srcFile.length() - 5), "/", ".");

		JavaDocBuilder builder = new JavaDocBuilder();

		File file = new File(fileName);

		if (!file.exists()) {
			return null;
		}

		builder.addSource(file);

		return builder.getClassByName(className);
	}

	private String _getSessionTypeName(int sessionType) {
		if (sessionType == _LOCAL) {
			return "Local";
		}
		else {
			return "";
		}
	}

	private String _getTplProperty(String key, String defaultValue) {
		return System.getProperty("service.tpl." + key, defaultValue);
	}

	private boolean _hasHttpMethods(JavaClass javaClass) {
		JavaMethod[] methods = javaClass.getMethods();

		for (int i = 0; i < methods.length; i++) {
			JavaMethod javaMethod = methods[i];

			if (!javaMethod.isConstructor() && javaMethod.isPublic() &&
				isCustomMethod(javaMethod)) {

				return true;
			}
		}

		return false;
	}

	private List _mergeReferenceList(List referenceList) {
		List list = new ArrayList(_ejbList.size() + referenceList.size());

		list.addAll(_ejbList);
		list.addAll(referenceList);

		return list;
	}

	private String _processTemplate(String name) throws Exception {
		return _processTemplate(name, _getContext());
	}

	private String _processTemplate(String name, Map context) throws Exception {
		return FreeMarkerUtil.process(name, context);
	}

	private static final int _REMOTE = 0;

	private static final int _LOCAL = 1;

	private static final String _CREATE_TABLE = "create table ";

	private static final String _TPL_ROOT = "com/liferay/portal/tools/servicebuilder/dependencies/";

	private String _tplBaseModeImpl = _TPL_ROOT + "base_mode_impl.ftl";
	private String _tplBasePersistence = _TPL_ROOT + "base_persistence.ftl";
	private String _tplBeanLocatorUtil = _TPL_ROOT + "bean_locator_util.ftl";
	private String _tplDynamicDialect = _TPL_ROOT + "dynamic_dialect.ftl";
	private String _tplEjbPk = _TPL_ROOT + "ejb_pk.ftl";
	private String _tplException = _TPL_ROOT + "exception.ftl";
	private String _tplExtendedModel = _TPL_ROOT + "extended_model.ftl";
	private String _tplExtendedModelImpl =
		_TPL_ROOT + "extended_model_impl.ftl";
	private String _tplFinder = _TPL_ROOT + "finder.ftl";
	private String _tplFinderCache = _TPL_ROOT + "finder_cache.ftl";
	private String _tplFinderUtil = _TPL_ROOT + "finder_util.ftl";
	private String _tplHbmXml = _TPL_ROOT + "hbm_xml.ftl";
	private String _tplHibernateConfiguration =
		_TPL_ROOT + "hibernate_configuration.ftl";
	private String _tplHibernateUtil = _TPL_ROOT + "hibernate_util.ftl";
	private String _tplJsonJs = _TPL_ROOT + "json_js.ftl";
	private String _tplJsonJsMethod = _TPL_ROOT + "json_js_method.ftl";
	private String _tplModel = _TPL_ROOT + "model.ftl";
	private String _tplModelHintsXml = _TPL_ROOT + "model_hints_xml.ftl";
	private String _tplModelImpl = _TPL_ROOT + "model_impl.ftl";
	private String _tplModelSoap = _TPL_ROOT + "model_soap.ftl";
	private String _tplPersistence = _TPL_ROOT + "persistence.ftl";
	private String _tplPersistenceImpl = _TPL_ROOT + "persistence_impl.ftl";
	private String _tplPersistenceTest = _TPL_ROOT + "persistence_test.ftl";
	private String _tplPersistenceUtil = _TPL_ROOT + "persistence_util.ftl";
	private String _tplPrincipalBean = _TPL_ROOT + "principal_bean.ftl";
	private String _tplProps = _TPL_ROOT + "props.ftl";
	private String _tplPropsUtil = _TPL_ROOT + "props_util.ftl";
	private String _tplRemotingXml = _TPL_ROOT + "remoting_xml.ftl";
	private String _tplService = _TPL_ROOT + "service.ftl";
	private String _tplServiceBaseImpl = _TPL_ROOT + "service_base_impl.ftl";
	private String _tplServiceFactory = _TPL_ROOT + "service_factory.ftl";
	private String _tplServiceHttp = _TPL_ROOT + "service_http.ftl";
	private String _tplServiceImpl = _TPL_ROOT + "service_impl.ftl";
	private String _tplServiceJson = _TPL_ROOT + "service_json.ftl";
	private String _tplServiceJsonSerializer =
		_TPL_ROOT + "service_json_serializer.ftl";
	private String _tplServiceSoap = _TPL_ROOT + "service_soap.ftl";
	private String _tplServiceUtil = _TPL_ROOT + "service_util.ftl";
	private String _tplSpringDataSourceXml =
		_TPL_ROOT + "spring_data_source_xml.ftl";
	private String _tplSpringUtil = _TPL_ROOT + "spring_util.ftl";
	private String _tplSpringXml = _TPL_ROOT + "spring_xml.ftl";
	private Set _badTableNames;
	private Set _badCmpFields;
	private String _hbmFileName;
	private String _modelHintsFileName;
	private String _springFileName;
	private String _springDataSourceFileName;
	private String _apiDir;
	private String _implDir;
	private String _jsonFileName;
	private String _remotingFileName;
	private String _sqlDir;
	private String _sqlFileName;
	private boolean _autoNamespaceTables;
	private String _baseModelImplPackage;
	private String _basePersistencePackage;
	private String _beanLocatorUtilPackage;
	private String _principalBeanPackage;
	private String _propsUtilPackage;
	private String _springHibernatePackage;
	private String _springUtilPackage;
	private String _testDir;
	private String _portletName = StringPool.BLANK;
	private String _portletShortName = StringPool.BLANK;
	private String _portletPackageName = StringPool.BLANK;
	private String _outputPath;
	private String _serviceOutputPath;
	private String _testOutputPath;
	private String _packagePath;
	private List _ejbList;

}