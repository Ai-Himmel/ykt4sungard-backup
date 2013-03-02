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

package com.liferay.portal.model;

import com.liferay.portal.service.persistence.PropertiesPK;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;

import java.io.IOException;

/**
 * <a href="Properties.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class Properties extends PropertiesModel {

	public static final String PORTAL = "portal";

	public Properties() {
	}

	public Properties(PropertiesPK pk) {
		super(pk);
	}

	public Properties(String companyId, String type, String properties) {
		super(companyId, type, properties);

		setProperties(properties);
	}

	public void setProperties(String properties) {
		properties = GetterUtil.getString(properties);

		_propertiesObj = new java.util.Properties();

		try {
			com.liferay.util.PropertiesUtil.load(_propertiesObj, properties);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		super.setProperties(properties);
	}

	public java.util.Properties getPropertiesObj() {
		if (_propertiesObj == null) {
			setProperties(StringPool.BLANK);
		}

		return _propertiesObj;
	}

	public void setPropertiesObj(java.util.Properties propertiesObj) {
		_propertiesObj = propertiesObj;

		super.setProperties(
			com.liferay.util.PropertiesUtil.toString(propertiesObj));
	}

	private java.util.Properties _propertiesObj;

}