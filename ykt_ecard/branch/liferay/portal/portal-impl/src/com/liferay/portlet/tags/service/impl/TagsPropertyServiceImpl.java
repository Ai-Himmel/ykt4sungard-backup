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

package com.liferay.portlet.tags.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.tags.model.TagsProperty;
import com.liferay.portlet.tags.service.base.TagsPropertyServiceBaseImpl;

import java.util.List;

/**
 * <a href="TagsPropertyServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsPropertyServiceImpl extends TagsPropertyServiceBaseImpl {

	public TagsProperty addProperty(long entryId, String key, String value)
		throws PortalException, SystemException {

		return tagsPropertyLocalService.addProperty(
			getUserId(), entryId, key, value);
	}

	public TagsProperty addProperty(String entryName, String key, String value)
		throws PortalException, SystemException {

		return tagsPropertyLocalService.addProperty(
			getUserId(), entryName, key, value);
	}

	public void deleteProperty(long propertyId)
		throws PortalException, SystemException {

		tagsPropertyLocalService.deleteProperty(propertyId);
	}

	public List getProperties(long entryId) throws SystemException {
		return tagsPropertyLocalService.getProperties(entryId);
	}

	public List getPropertyValues(long companyId, String key)
		throws SystemException {

		return tagsPropertyLocalService.getPropertyValues(companyId, key);
	}

	public TagsProperty updateProperty(
			long propertyId, String key, String value)
		throws PortalException, SystemException {

		return tagsPropertyLocalService.updateProperty(propertyId, key, value);
	}

}