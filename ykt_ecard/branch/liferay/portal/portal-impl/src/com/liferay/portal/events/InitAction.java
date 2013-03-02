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

package com.liferay.portal.events;

import com.liferay.portal.bean.BeanLocatorImpl;
import com.liferay.portal.jcr.jackrabbit.JCRFactoryImpl;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.kernel.events.SimpleAction;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaProps;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.PortalClassLoaderUtil;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.TimeZoneUtil;
import com.liferay.portal.log.CommonsLogFactoryImpl;
import com.liferay.portal.security.jaas.PortalConfiguration;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.velocity.LiferayResourceLoader;
import com.liferay.util.FileUtil;
import com.liferay.util.SystemProperties;
import com.liferay.util.Time;
import com.liferay.util.log4j.Log4JUtil;

import java.io.File;

import javax.security.auth.login.Configuration;

import org.apache.commons.collections.ExtendedProperties;
import org.apache.velocity.app.Velocity;
import org.apache.velocity.runtime.RuntimeConstants;

/**
 * <a href="InitAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InitAction extends SimpleAction {

	public void run(String[] ids) throws ActionException {

		// Set the default locale used by Liferay. This locale is no longer set
		// at the VM level. See LEP-2584.

		String userLanguage = SystemProperties.get("user.language");
		String userCountry = SystemProperties.get("user.country");
		String userVariant = SystemProperties.get("user.variant");

		LocaleUtil.setDefault(userLanguage, userCountry, userVariant);

		// Set the default time zone used by Liferay. This time zone is no
		// longer set at the VM level. See LEP-2584.

		String userTimeZone = SystemProperties.get("user.timezone");

		TimeZoneUtil.setDefault(userTimeZone);

		// Shared class loader

		try {
			PortalClassLoaderUtil.setClassLoader(
				Thread.currentThread().getContextClassLoader());
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Log4J

		if (GetterUtil.getBoolean(SystemProperties.get(
				"log4j.configure.on.startup"), true) &&
			!ServerDetector.isSun()) {

			ClassLoader classLoader = getClass().getClassLoader();

			Log4JUtil.configureLog4J(
				classLoader.getResource("META-INF/portal-log4j.xml"));
			Log4JUtil.configureLog4J(
				classLoader.getResource("META-INF/portal-log4j-ext.xml"));
		}

		// Shared log

		try {
			LogFactoryUtil.setLogFactory(new CommonsLogFactoryImpl());
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Bean locator

		BeanLocatorUtil.setBeanLocator(new BeanLocatorImpl());

		// Java properties

		JavaProps.isJDK5();

		// JAAS

		if ((GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.PORTAL_CONFIGURATION))) &&
			(ServerDetector.isJBoss() || ServerDetector.isPramati() ||
			 ServerDetector.isSun() || ServerDetector.isWebLogic())) {

			PortalConfiguration portalConfig = new PortalConfiguration(
				Configuration.getConfiguration());

			Configuration.setConfiguration(portalConfig);
		}

		// JCR

		try {
			File repositoryRoot = new File(JCRFactoryImpl.REPOSITORY_ROOT);

			if (!repositoryRoot.exists()) {
				repositoryRoot.mkdirs();

				File tempFile = new File(
					SystemProperties.get(SystemProperties.TMP_DIR) +
						File.separator + Time.getTimestamp());

				String repositoryXmlPath =
					"com/liferay/portal/jcr/jackrabbit/dependencies/" +
						"repository-ext.xml";

				ClassLoader classLoader = getClass().getClassLoader();

				if (classLoader.getResource(repositoryXmlPath) == null) {
					repositoryXmlPath =
						"com/liferay/portal/jcr/jackrabbit/dependencies/" +
							"repository.xml";
				}

				String content = StringUtil.read(
					classLoader, repositoryXmlPath);

				FileUtil.write(tempFile, content);

				FileUtil.copyFile(
					tempFile, new File(JCRFactoryImpl.CONFIG_FILE_PATH));

				tempFile.delete();
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Velocity

		LiferayResourceLoader.setListeners(PropsUtil.getArray(
			PropsUtil.VELOCITY_ENGINE_RESOURCE_LISTENERS));

		ExtendedProperties props = new ExtendedProperties();

		props.setProperty(RuntimeConstants.RESOURCE_LOADER, "servlet");

		props.setProperty(
			"servlet." + RuntimeConstants.RESOURCE_LOADER + ".class",
			LiferayResourceLoader.class.getName());

		props.setProperty(
			RuntimeConstants.RESOURCE_MANAGER_CLASS,
			PropsUtil.get(PropsUtil.VELOCITY_ENGINE_RESOURCE_MANAGER));

		props.setProperty(
			RuntimeConstants.RESOURCE_MANAGER_CACHE_CLASS,
			PropsUtil.get(PropsUtil.VELOCITY_ENGINE_RESOURCE_MANAGER_CACHE));

		props.setProperty(
			"velocimacro.library",
			PropsUtil.get(PropsUtil.VELOCITY_ENGINE_VELOCIMACRO_LIBRARY));

		props.setProperty(
			RuntimeConstants.RUNTIME_LOG_LOGSYSTEM_CLASS,
			PropsUtil.get(PropsUtil.VELOCITY_ENGINE_LOGGER));

		props.setProperty(
			"runtime.log.logsystem.log4j.category",
			PropsUtil.get(PropsUtil.VELOCITY_ENGINE_LOGGER_CATEGORY));

		Velocity.setExtendedProperties(props);

		try {
			Velocity.init();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}