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

package com.liferay.portlet.wiki.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.wiki.model.WikiPageResource;
import com.liferay.portlet.wiki.service.base.WikiPageResourceLocalServiceBaseImpl;

/**
 * <a href="WikiPageResourceLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageResourceLocalServiceImpl
	extends WikiPageResourceLocalServiceBaseImpl {

	public void deletePageResource(long nodeId, String title)
		throws PortalException, SystemException {

		wikiPageResourcePersistence.removeByN_T(nodeId, title);
	}

	public WikiPageResource getPageResource(long pageResourceId)
		throws PortalException, SystemException {

		return wikiPageResourcePersistence.findByPrimaryKey(pageResourceId);
	}

	public long getPageResourcePrimKey(long nodeId, String title)
		throws PortalException, SystemException {

		WikiPageResource pageResource = wikiPageResourcePersistence.fetchByN_T(
			nodeId, title);

		if (pageResource == null) {
			long pageResourcePrimKey = counterLocalService.increment();

			pageResource = wikiPageResourcePersistence.create(
				pageResourcePrimKey);

			pageResource.setNodeId(nodeId);
			pageResource.setTitle(title);

			wikiPageResourcePersistence.update(pageResource);
		}

		return pageResource.getResourcePrimKey();
	}

}