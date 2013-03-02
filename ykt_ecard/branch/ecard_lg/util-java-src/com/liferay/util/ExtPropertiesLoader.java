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

package com.liferay.util;

import com.germinus.easyconf.ComponentConfiguration;
import com.germinus.easyconf.ComponentProperties;
import com.germinus.easyconf.EasyConf;

import java.util.List;
import java.util.Properties;

/**
 * <a href="ExtPropertiesLoader.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class ExtPropertiesLoader {

	public void init(String name) {
		_conf = EasyConf.getConfiguration(name);

		_printSources(name);
	}

	public void init(String name, String companyId) {
		_conf = EasyConf.getConfiguration(companyId, name);

		_printSources(name, companyId);
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

		if ((array == null) ||
			((array.length == 1) && Validator.isNull(array[0]))) {

			// Commons Configuration parses an empty property into a String
			// array with one String containing one space

			array = new String[0];
		}

		return array;
	}

	public Properties getProperties() {
		return getComponentProperties().getProperties();
	}

	public ComponentProperties getComponentProperties() {
		return _conf.getProperties();
	}

	private void _printSources(String name) {
		_printSources(name, null);
	}

	private void _printSources(String name, String companyId) {
		List sources = getComponentProperties().getLoadedSources();

		for (int i = sources.size() - 1; i >= 0; i--) {
			String source = (String)sources.get(i);

			String info = "Loading " + source;

			if (companyId != null) {
				info += " for " + companyId;
			}

			System.out.println(info);
		}
	}

	private ComponentConfiguration _conf;

}