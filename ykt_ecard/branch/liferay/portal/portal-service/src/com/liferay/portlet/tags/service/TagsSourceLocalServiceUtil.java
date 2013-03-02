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
 * <a href="TagsSourceLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.tags.service.TagsSourceLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.tags.service.TagsSourceLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsSourceLocalService
 * @see com.liferay.portlet.tags.service.TagsSourceLocalServiceFactory
 *
 */
public class TagsSourceLocalServiceUtil {
	public static com.liferay.portlet.tags.model.TagsSource addTagsSource(
		com.liferay.portlet.tags.model.TagsSource model)
		throws com.liferay.portal.SystemException {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.addTagsSource(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.tags.model.TagsSource updateTagsSource(
		com.liferay.portlet.tags.model.TagsSource model)
		throws com.liferay.portal.SystemException {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.updateTagsSource(model);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence getTagsPropertyPersistence() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsPropertyPersistence();
	}

	public static void setTagsPropertyPersistence(
		com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence tagsPropertyPersistence) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsPropertyPersistence(tagsPropertyPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyFinder getTagsPropertyFinder() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsPropertyFinder();
	}

	public static void setTagsPropertyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyFinder tagsPropertyFinder) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsPropertyFinder(tagsPropertyFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder getTagsPropertyKeyFinder() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsPropertyKeyFinder();
	}

	public static void setTagsPropertyKeyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder tagsPropertyKeyFinder) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsPropertyKeyFinder(tagsPropertyKeyFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsSourcePersistence getTagsSourcePersistence() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		return tagsSourceLocalService.getTagsSourcePersistence();
	}

	public static void setTagsSourcePersistence(
		com.liferay.portlet.tags.service.persistence.TagsSourcePersistence tagsSourcePersistence) {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.setTagsSourcePersistence(tagsSourcePersistence);
	}

	public static void afterPropertiesSet() {
		TagsSourceLocalService tagsSourceLocalService = TagsSourceLocalServiceFactory.getService();

		tagsSourceLocalService.afterPropertiesSet();
	}
}