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

package com.liferay.portlet.tags.service;


/**
 * <a href="TagsEntryServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.tags.service.TagsEntryService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.tags.service.TagsEntryServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsEntryService
 * @see com.liferay.portlet.tags.service.TagsEntryServiceFactory
 *
 */
public class TagsEntryServiceUtil {
	public static com.liferay.portlet.tags.model.TagsEntry addEntry(
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.addEntry(name);
	}

	public static com.liferay.portlet.tags.model.TagsEntry addEntry(
		java.lang.String name, java.lang.String[] properties)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.addEntry(name, properties);
	}

	public static void deleteEntry(long entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		tagsEntryService.deleteEntry(entryId);
	}

	public static java.util.List getEntries(java.lang.String className,
		long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.getEntries(className, classPK);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String[] properties)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.search(companyId, name, properties);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String[] properties, int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.search(companyId, name, properties, begin, end);
	}

	public static com.liferay.portal.kernel.json.JSONArrayWrapper searchAutocomplete(
		long companyId, java.lang.String name, java.lang.String[] properties,
		int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.searchAutocomplete(companyId, name, properties,
			begin, end);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String[] properties)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.searchCount(companyId, name, properties);
	}

	public static com.liferay.portlet.tags.model.TagsEntry updateEntry(
		long entryId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.updateEntry(entryId, name);
	}

	public static com.liferay.portlet.tags.model.TagsEntry updateEntry(
		long entryId, java.lang.String name, java.lang.String[] properties)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		TagsEntryService tagsEntryService = TagsEntryServiceFactory.getService();

		return tagsEntryService.updateEntry(entryId, name, properties);
	}
}