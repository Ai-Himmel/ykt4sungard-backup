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
 * <a href="TagsPropertyLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.tags.service.TagsPropertyLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.tags.service.TagsPropertyLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsPropertyLocalService
 * @see com.liferay.portlet.tags.service.TagsPropertyLocalServiceFactory
 *
 */
public class TagsPropertyLocalServiceUtil {
	public static com.liferay.portlet.tags.model.TagsProperty addTagsProperty(
		com.liferay.portlet.tags.model.TagsProperty model)
		throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.addTagsProperty(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.tags.model.TagsProperty updateTagsProperty(
		com.liferay.portlet.tags.model.TagsProperty model)
		throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.updateTagsProperty(model);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence getTagsPropertyPersistence() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsPropertyPersistence();
	}

	public static void setTagsPropertyPersistence(
		com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence tagsPropertyPersistence) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsPropertyPersistence(tagsPropertyPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyFinder getTagsPropertyFinder() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsPropertyFinder();
	}

	public static void setTagsPropertyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyFinder tagsPropertyFinder) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsPropertyFinder(tagsPropertyFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder getTagsPropertyKeyFinder() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsPropertyKeyFinder();
	}

	public static void setTagsPropertyKeyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder tagsPropertyKeyFinder) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsPropertyKeyFinder(tagsPropertyKeyFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsSourcePersistence getTagsSourcePersistence() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getTagsSourcePersistence();
	}

	public static void setTagsSourcePersistence(
		com.liferay.portlet.tags.service.persistence.TagsSourcePersistence tagsSourcePersistence) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setTagsSourcePersistence(tagsSourcePersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.tags.model.TagsProperty addProperty(
		long userId, long entryId, java.lang.String key, java.lang.String value)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.addProperty(userId, entryId, key, value);
	}

	public static com.liferay.portlet.tags.model.TagsProperty addProperty(
		long userId, java.lang.String entryName, java.lang.String key,
		java.lang.String value)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.addProperty(userId, entryName, key,
			value);
	}

	public static void deleteProperties(long entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.deleteProperties(entryId);
	}

	public static void deleteProperty(long propertyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.deleteProperty(propertyId);
	}

	public static void deleteProperty(
		com.liferay.portlet.tags.model.TagsProperty property)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		tagsPropertyLocalService.deleteProperty(property);
	}

	public static java.util.List getProperties()
		throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getProperties();
	}

	public static java.util.List getProperties(long entryId)
		throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getProperties(entryId);
	}

	public static com.liferay.portlet.tags.model.TagsProperty getProperty(
		long propertyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getProperty(propertyId);
	}

	public static com.liferay.portlet.tags.model.TagsProperty getProperty(
		long entryId, java.lang.String key)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getProperty(entryId, key);
	}

	public static java.lang.String[] getPropertyKeys(long companyId)
		throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getPropertyKeys(companyId);
	}

	public static java.util.List getPropertyValues(long companyId,
		java.lang.String key) throws com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.getPropertyValues(companyId, key);
	}

	public static com.liferay.portlet.tags.model.TagsProperty updateProperty(
		long propertyId, java.lang.String key, java.lang.String value)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsPropertyLocalService tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getService();

		return tagsPropertyLocalService.updateProperty(propertyId, key, value);
	}
}