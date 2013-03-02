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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchPropertiesException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Properties;
import com.liferay.portal.service.persistence.PropertiesPK;
import com.liferay.portal.service.persistence.PropertiesUtil;
import com.liferay.portal.service.spring.PropertiesService;

/**
 * <a href="PropertiesServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.1 $
 *
 */
public class PropertiesServiceImpl extends PrincipalBean
	implements PropertiesService {

	// Business methods

	public java.util.Properties getPortalProperties(String companyId)
		throws SystemException {

		Properties properties = getProperties(companyId, Properties.PORTAL);

		return properties.getPropertiesObj();
	}

	public Properties getProperties(String companyId, String type)
		throws SystemException {

		PropertiesPK pk = new PropertiesPK(companyId, type);

		Properties properties = null;

		try {
			properties = PropertiesUtil.findByPrimaryKey(pk);
		}
		catch (NoSuchPropertiesException nspe) {
			properties = PropertiesUtil.create(pk);

			PropertiesUtil.update(properties);
		}

		return properties;
	}

	public void updatePortalProperties(
			String companyId, java.util.Properties propertiesObj)
		throws SystemException {

		updateProperties(companyId, Properties.PORTAL, propertiesObj);
	}

	public void updateProperties(
			String companyId, String type, java.util.Properties propertiesObj)
		throws SystemException {

		Properties properties = getProperties(companyId, type);

		properties.setPropertiesObj(propertiesObj);

		PropertiesUtil.update(properties);
	}

}