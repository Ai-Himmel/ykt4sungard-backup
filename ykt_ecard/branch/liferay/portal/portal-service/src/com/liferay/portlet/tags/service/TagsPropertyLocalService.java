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
 * <a href="TagsPropertyLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.tags.service.impl.TagsPropertyLocalServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsPropertyLocalServiceFactory
 * @see com.liferay.portlet.tags.service.TagsPropertyLocalServiceUtil
 *
 */
public interface TagsPropertyLocalService {
	public com.liferay.portlet.tags.model.TagsProperty addTagsProperty(
		com.liferay.portlet.tags.model.TagsProperty model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsProperty updateTagsProperty(
		com.liferay.portlet.tags.model.TagsProperty model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence();

	public void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder();

	public void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder);

	public com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence();

	public void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder();

	public void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder);

	public com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence getTagsPropertyPersistence();

	public void setTagsPropertyPersistence(
		com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence tagsPropertyPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsPropertyFinder getTagsPropertyFinder();

	public void setTagsPropertyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyFinder tagsPropertyFinder);

	public com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder getTagsPropertyKeyFinder();

	public void setTagsPropertyKeyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder tagsPropertyKeyFinder);

	public com.liferay.portlet.tags.service.persistence.TagsSourcePersistence getTagsSourcePersistence();

	public void setTagsSourcePersistence(
		com.liferay.portlet.tags.service.persistence.TagsSourcePersistence tagsSourcePersistence);

	public com.liferay.portal.service.persistence.UserPersistence getUserPersistence();

	public void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence);

	public com.liferay.portal.service.persistence.UserFinder getUserFinder();

	public void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder);

	public void afterPropertiesSet();

	public com.liferay.portlet.tags.model.TagsProperty addProperty(
		long userId, long entryId, java.lang.String key, java.lang.String value)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsProperty addProperty(
		long userId, java.lang.String entryName, java.lang.String key,
		java.lang.String value)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteProperties(long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteProperty(long propertyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteProperty(
		com.liferay.portlet.tags.model.TagsProperty property)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getProperties()
		throws com.liferay.portal.SystemException;

	public java.util.List getProperties(long entryId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsProperty getProperty(
		long propertyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsProperty getProperty(
		long entryId, java.lang.String key)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.lang.String[] getPropertyKeys(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List getPropertyValues(long companyId, java.lang.String key)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsProperty updateProperty(
		long propertyId, java.lang.String key, java.lang.String value)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}