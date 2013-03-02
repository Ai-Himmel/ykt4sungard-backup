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

package com.liferay.portal.util;

import com.liferay.portal.kernel.util.KeyValuePair;

import java.io.InputStream;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.xml.sax.InputSource;

/**
 * <a href="EntityResolver.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EntityResolver implements org.xml.sax.EntityResolver {

	public InputSource resolveEntity(String publicId, String systemId) {
		ClassLoader classLoader = getClass().getClassLoader();

		if (_log.isInfoEnabled()) {
			_log.info("Resolving entity " + publicId + " " + systemId);
		}

		if (publicId != null) {
			for (int i = 0; i < _PUBLIC_IDS.length; i++) {
				KeyValuePair kvp = _PUBLIC_IDS[i];

				if (publicId.equals(kvp.getKey())) {
					InputStream is = classLoader.getResourceAsStream(
						_DEFINITIONS_PATH + kvp.getValue());

					if (_log.isInfoEnabled()) {
						_log.info("Entity found for public id " + systemId);
					}

					return new InputSource(is);
				}
			}
		}
		else if (systemId != null) {
			for (int i = 0; i < _SYSTEM_IDS.length; i++) {
				KeyValuePair kvp = _SYSTEM_IDS[i];

				if (systemId.equals(kvp.getKey())) {
					InputStream is = classLoader.getResourceAsStream(
						_DEFINITIONS_PATH + kvp.getValue());

					if (_log.isInfoEnabled()) {
						_log.info("Entity found for system id " + systemId);
					}

					return new InputSource(is);
				}
			}
		}

		if (_log.isInfoEnabled()) {
			_log.info("No entity found for " + publicId + " " + systemId);
		}

		return null;
	}

	private static String _DEFINITIONS_PATH = "com/liferay/portal/definitions/";

	private static KeyValuePair[] _PUBLIC_IDS = {
		new KeyValuePair(
			"datatypes",
			"datatypes.dtd"
		),

		new KeyValuePair(
			"-//Sun Microsystems, Inc.//DTD Facelet Taglib 1.0//EN",
			"facelet-taglib_1_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Display 2.0.0//EN",
			"liferay-display_2_0_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Display 3.5.0//EN",
			"liferay-display_3_5_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Display 4.0.0//EN",
			"liferay-display_4_0_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Layout Templates 3.6.0//EN",
			"liferay-layout-templates_3_6_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Layout Templates 4.0.0//EN",
			"liferay-layout-templates_4_0_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Layout Templates 4.3.0//EN",
			"liferay-layout-templates_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Look and Feel 3.5.0//EN",
			"liferay-look-and-feel_3_5_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Look and Feel 4.0.0//EN",
			"liferay-look-and-feel_4_0_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Look and Feel 4.3.0//EN",
			"liferay-look-and-feel_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Plugin Package 4.3.0//EN",
			"liferay-plugin-package_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Plugin Repository 4.3.0//EN",
			"liferay-plugin-repository_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 3.5.0//EN",
			"liferay-portlet-app_3_5_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.0.0//EN",
			"liferay-portlet-app_4_0_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.1.0//EN",
			"liferay-portlet-app_4_1_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.2.0//EN",
			"liferay-portlet-app_4_2_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.3.0//EN",
			"liferay-portlet-app_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.3.1//EN",
			"liferay-portlet-app_4_3_1.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.3.2//EN",
			"liferay-portlet-app_4_3_2.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.3.3//EN",
			"liferay-portlet-app_4_3_3.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.3.6//EN",
			"liferay-portlet-app_4_3_6.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Portlet Application 4.4.0//EN",
			"liferay-portlet-app_4_4_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 3.5.0//EN",
			"liferay-service-builder_3_5_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 3.6.1//EN",
			"liferay-service-builder_3_6_1.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 4.0.0//EN",
			"liferay-service-builder_4_0_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 4.2.0//EN",
			"liferay-service-builder_4_2_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 4.3.0//EN",
			"liferay-service-builder_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 4.3.3//EN",
			"liferay-service-builder_4_3_3.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Service Builder 4.4.0//EN",
			"liferay-service-builder_4_4_0.dtd"
		),

		new KeyValuePair(
			"-//Liferay//DTD Theme Loader 4.3.0//EN",
			"liferay-theme-loader_4_3_0.dtd"
		),

		new KeyValuePair(
			"-//MuleSource //DTD mule-configuration XML V1.0//EN",
			"mule-configuration.dtd"
		),

		new KeyValuePair(
			"-//SPRING//DTD BEAN//EN",
			"spring-beans.dtd"
		),

		new KeyValuePair(
			"-//Apache Software Foundation//DTD Struts Configuration 1.2//EN",
			"struts-config_1_2.dtd"
		),

		new KeyValuePair(
			"-//Apache Software Foundation//DTD Tiles Configuration 1.1//EN",
			"tiles-config_1_1.dtd"
		),

		new KeyValuePair(
			"-//Sun Microsystems, Inc.//DTD Web Application 2.3//EN",
			"web-app_2_3.dtd"
		),

		new KeyValuePair(
			"-//Sun Microsystems, Inc.//DTD JavaServer Faces Config 1.0//EN",
			"web-facesconfig_1_0.dtd"
		),

		new KeyValuePair(
			"-//Sun Microsystems, Inc.//DTD JavaServer Faces Config 1.1//EN",
			"web-facesconfig_1_1.dtd"
		),

		new KeyValuePair(
			"-//W3C//DTD XMLSCHEMA 200102//EN",
			"XMLSchema.dtd"
		)
	};

	private static KeyValuePair[] _SYSTEM_IDS = {
		new KeyValuePair(
			"http://java.sun.com/xml/ns/portlet/portlet-app_1_0.xsd",
			"portlet-app_1_0.xsd"
		),

		new KeyValuePair(
			"http://www.w3.org/2001/xml.xsd",
			"xml.xsd"
		)
	};

	private static Log _log = LogFactory.getLog(EntityResolver.class);

}