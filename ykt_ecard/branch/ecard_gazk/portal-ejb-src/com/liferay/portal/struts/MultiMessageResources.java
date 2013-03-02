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

package com.liferay.portal.struts;

import com.liferay.util.StringUtil;

import java.io.InputStream;

import java.net.URL;

import java.util.Enumeration;
import java.util.Map;
import java.util.Properties;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.util.MessageResourcesFactory;
import org.apache.struts.util.PropertyMessageResources;

/**
 * <a href="MultiMessageResources.java.html"><b><i>View Source </i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class MultiMessageResources extends PropertyMessageResources {

	public MultiMessageResources(MessageResourcesFactory factory,
								 String config) {

		super(factory, config);
	}

	public MultiMessageResources(MessageResourcesFactory factory,
								 String config, boolean returnNull) {

		super(factory, config, returnNull);
	}

	public Map getMessages() {
		return messages;
	}

	public void setServletContext(ServletContext servletContext) {
		_servletContext = servletContext;
	}

	protected void loadLocale(String localeKey) {
		synchronized (locales) {
			if (locales.get(localeKey) != null) {
				return;
			}

			locales.put(localeKey, localeKey);
		}

		String[] names = StringUtil.split(config.replace('.', '/'));

		for (int i = 0; i < names.length; i++) {
			String name = names[i];
			if (localeKey.length() > 0) {
				name += "_" + localeKey;
			}
			name += ".properties";

			_loadProps(name, localeKey, false);
		}

		for (int i = 0; i < names.length; i++) {
			String name = names[i];
			if (localeKey.length() > 0) {
				name += "_" + localeKey;
			}
			name += ".properties";

			_loadProps(name, localeKey, true);
		}
	}

	private void _loadProps(
		String name, String localeKey, boolean useServletContext) {

		Properties props = new Properties();

		try {
			URL url = null;

			if (useServletContext) {
				url = _servletContext.getResource("/WEB-INF/" + name);
			}
			else {
				ClassLoader classLoader = getClass().getClassLoader();

				url = classLoader.getResource(name);
			}

			if (url != null) {
				InputStream is = url.openStream();

				props.load(is);

				is.close();

				_log.info("Loading " + url);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		if (props.size() < 1) {
			return;
		}

		synchronized (messages) {
			Enumeration names = props.keys();

			while (names.hasMoreElements()) {
				String key = (String)names.nextElement();

				messages.put(messageKey(localeKey, key),
							 props.getProperty(key));
			}
		}
	}

	private static final Log _log =
		LogFactory.getLog(MultiMessageResources.class);

	private transient ServletContext _servletContext;

}