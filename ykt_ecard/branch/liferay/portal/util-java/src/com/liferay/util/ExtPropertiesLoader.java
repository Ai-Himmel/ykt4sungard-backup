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

package com.liferay.util;

import com.germinus.easyconf.ComponentConfiguration;
import com.germinus.easyconf.ComponentProperties;
import com.germinus.easyconf.EasyConf;

import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.CompanyLocalServiceUtil;

import java.util.Enumeration;
import java.util.List;
import java.util.Map;
import java.util.Properties;

/**
 * <a href="ExtPropertiesLoader.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ExtPropertiesLoader {

	public static ExtPropertiesLoader getInstance(String name) {
		ExtPropertiesLoader props =
			(ExtPropertiesLoader)_propsPool.get(name);

		if (props == null) {
			props = new ExtPropertiesLoader(name);

			_propsPool.put(name, props);
		}

		return props;
	}

	public static ExtPropertiesLoader getInstance(String name, long companyId) {
		String key = name + _COMPANY_ID_SEPARATOR + companyId;

		ExtPropertiesLoader props =
			(ExtPropertiesLoader)_propsPool.get(key);

		if (props == null) {
			props = new ExtPropertiesLoader(name, companyId);

			_propsPool.put(key, props);
		}

		return props;
	}

	public boolean containsKey(String key) {
		return getComponentProperties().containsKey(key);
	}

	public String get(String key) {
		return getComponentProperties().getString(key);
	}

	public void set(String key, String value) {
		getComponentProperties().setProperty(key, value);
	}

	public String[] getArray(String key) {
		String[] array = getComponentProperties().getStringArray(key);

		if (array == null) {
			return new String[0];
		}
		else if (array.length > 0) {

			// Commons Configuration parses an empty property into a String
			// array with one String containing one space. It also leaves a
			// trailing array member if you set a property in more than one
			// line.

			if (Validator.isNull(array[array.length - 1])) {
				String[] subArray = new String[array.length - 1];

				System.arraycopy(array, 0, subArray, 0, subArray.length);

				array = subArray;
			}
		}

		return array;
	}

	public Properties getProperties() {

		// For some strange reason, componentProperties.getProperties() returns
		// values with spaces after commas. So a property setting of "xyz=1,2,3"
		// actually returns "xyz=1, 2, 3". This can break applications that
		// don't expect that extra space. However, getting the property value
		// directly through componentProperties returns the correct value. This
		// method fixes the weird behavior by returing properties with the
		// correct values.

		Properties props = new Properties();

		ComponentProperties componentProps = getComponentProperties();

		Enumeration enu = componentProps.getProperties().propertyNames();

		while (enu.hasMoreElements()) {
			String key = (String)enu.nextElement();

			props.setProperty(key, componentProps.getString(key));
		}

		return props;
	}

	public ComponentProperties getComponentProperties() {
		return _conf.getProperties();
	}

	private ExtPropertiesLoader(String name) {
		_conf = EasyConf.getConfiguration(name);

		_printSources(name);
	}

	private ExtPropertiesLoader(String name, long companyId) {
		String webId = null;

		if (companyId > 0) {
			try {
				Company company = CompanyLocalServiceUtil.getCompanyById(
					companyId);

				webId = company.getWebId();
			}
			catch (Exception e) {
			}
		}

		_conf = EasyConf.getConfiguration(webId, name);

		_printSources(name, companyId, webId);
	}

	private void _printSources(String name) {
		_printSources(name, 0, null);
	}

	private void _printSources(String name, long companyId, String webId) {
		List sources = getComponentProperties().getLoadedSources();

		for (int i = sources.size() - 1; i >= 0; i--) {
			String source = (String)sources.get(i);

			String info = "Loading " + source;

			if (companyId > 0) {
				info +=
					" for {companyId=" + companyId + ", webId=" + webId + "}";
			}

			System.out.println(info);
		}
	}

	private static Map _propsPool = CollectionFactory.getSyncHashMap();

	private static final String _COMPANY_ID_SEPARATOR = "_COMPANY_ID_";

	private ComponentConfiguration _conf;

}