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

package com.liferay.portal.events;

import com.liferay.portal.jaas.PortalConfiguration;
import com.liferay.portal.struts.ActionException;
import com.liferay.portal.struts.SimpleAction;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.ServerDetector;
import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;
import com.liferay.util.velocity.ServletResourceLoader;

import java.net.URL;

import java.util.Enumeration;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Locale;
import java.util.Set;
import java.util.TimeZone;

import javax.security.auth.login.Configuration;

import org.apache.commons.collections.ExtendedProperties;
import org.apache.log4j.Level;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.apache.log4j.helpers.NullEnumeration;
import org.apache.log4j.xml.DOMConfigurator;
import org.apache.velocity.app.Velocity;
import org.apache.velocity.runtime.RuntimeConstants;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="InitAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.20 $
 *
 */
public class InitAction extends SimpleAction {

	public void run(String[] ids) throws ActionException {
		
		// Set default locale

		String userLanguage = SystemProperties.get("user.language");
		String userCountry = SystemProperties.get("user.country");
		String userVariant = SystemProperties.get("user.variant");

		if (Validator.isNull(userVariant)) {
			Locale.setDefault(new Locale(userLanguage, userCountry));
		}
		else {
			Locale.setDefault(
				new Locale(userLanguage, userCountry, userVariant));
		}
		// Set default time zone

		//TimeZone.setDefault(
			//TimeZone.getTimeZone(SystemProperties.get("user.timezone")));
			
		// Log4J

		if (GetterUtil.get(SystemProperties.get(
				"log4j.configure.on.startup"), true) &&
			!ServerDetector.isSun()) {

			ClassLoader classLoader = getClass().getClassLoader();

			URL portalLog4jUrl = classLoader.getResource(
				"META-INF/portal-log4j.xml");

			if (Logger.getRootLogger().getAllAppenders() instanceof
					NullEnumeration) {

				DOMConfigurator.configure(portalLog4jUrl);
			}
			else {
				Set currentLoggerNames = new HashSet();

				Enumeration enu = LogManager.getCurrentLoggers();

				while (enu.hasMoreElements()) {
					Logger logger = (Logger)enu.nextElement();

					currentLoggerNames.add(logger.getName());
				}

				try {
					SAXReader reader = new SAXReader();

					Document doc = reader.read(portalLog4jUrl);

					Element root = doc.getRootElement();

					Iterator itr = root.elements("category").iterator();

					while (itr.hasNext()) {
						Element category = (Element)itr.next();

						String name = category.attributeValue("name");
						String priority =
							category.element(
								"priority").attributeValue("value");

						Logger logger = Logger.getLogger(name);

						logger.setLevel(Level.toLevel(priority));
					}
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}
		}

		// JAAS

		if ((GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.PORTAL_CONFIGURATION))) &&
			(ServerDetector.isJBoss() || ServerDetector.isPramati() ||
			 ServerDetector.isSun() || ServerDetector.isWebLogic())) {

			PortalConfiguration portalConfig = new PortalConfiguration(
				Configuration.getConfiguration());

			Configuration.setConfiguration(portalConfig);
		}

		// Velocity

		ExtendedProperties props = new ExtendedProperties();

		props.setProperty(RuntimeConstants.RESOURCE_LOADER, "servlet");

		props.setProperty(
			"servlet." + RuntimeConstants.RESOURCE_LOADER + ".class",
			ServletResourceLoader.class.getName());

        props.setProperty(
			RuntimeConstants.RUNTIME_LOG_LOGSYSTEM_CLASS,
			"org.apache.velocity.runtime.log.SimpleLog4JLogSystem");

        props.setProperty(
			"runtime.log.logsystem.log4j.category", "org.apache.velocity");

		Velocity.setExtendedProperties(props);

		try {
			Velocity.init();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}