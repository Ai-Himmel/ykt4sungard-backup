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
import com.liferay.portal.kernel.json.JSONArrayWrapper;
import com.liferay.portlet.tags.model.TagsEntry;
import com.liferay.portlet.tags.service.base.TagsEntryServiceBaseImpl;

import java.util.List;

/**
 * <a href="TagsEntryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsEntryServiceImpl extends TagsEntryServiceBaseImpl {

	public TagsEntry addEntry(String name)
		throws PortalException, SystemException {

		return tagsEntryLocalService.addEntry(getUserId(), name);
	}

	public TagsEntry addEntry(String name, String[] properties)
		throws PortalException, SystemException {

		return tagsEntryLocalService.addEntry(getUserId(), name, properties);
	}

	public void deleteEntry(long entryId)
		throws PortalException, SystemException {

		tagsEntryLocalService.deleteEntry(entryId);
	}

	public List getEntries(String className, long classPK)
		throws PortalException, SystemException {

		return tagsEntryLocalService.getEntries(className, classPK);
	}

	public List search(long companyId, String name, String[] properties)
		throws SystemException {

		return tagsEntryLocalService.search(companyId, name, properties);
	}

	public List search(
		long companyId, String name, String[] properties, int begin, int end)
		throws SystemException {

		return tagsEntryLocalService.search(
			companyId, name, properties, begin, end);
	}

	public JSONArrayWrapper searchAutocomplete(
			long companyId, String name, String[] properties, int begin,
			int end)
		throws SystemException {

		return tagsEntryLocalService.searchAutocomplete(
			companyId, name, properties, begin, end);
	}

	public int searchCount(long companyId, String name, String[] properties)
		throws SystemException {

		return tagsEntryLocalService.searchCount(companyId, name, properties);
	}

	public TagsEntry updateEntry(long entryId, String name)
		throws PortalException, SystemException {

		return tagsEntryLocalService.updateEntry(entryId, name);
	}

	public TagsEntry updateEntry(long entryId, String name, String[] properties)
		throws PortalException, SystemException {

		return tagsEntryLocalService.updateEntry(
			getUserId(), entryId, name, properties);
	}

}