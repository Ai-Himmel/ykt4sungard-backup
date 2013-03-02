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

package com.liferay.portlet.tags.service.base;

import com.liferay.portal.service.impl.PrincipalBean;

import com.liferay.portlet.tags.service.TagsAssetLocalService;
import com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsAssetService;
import com.liferay.portlet.tags.service.TagsAssetServiceFactory;
import com.liferay.portlet.tags.service.TagsEntryLocalService;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsEntryService;
import com.liferay.portlet.tags.service.TagsEntryServiceFactory;
import com.liferay.portlet.tags.service.TagsPropertyLocalService;
import com.liferay.portlet.tags.service.TagsPropertyLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsPropertyService;
import com.liferay.portlet.tags.service.TagsPropertyServiceFactory;
import com.liferay.portlet.tags.service.TagsSourceLocalService;
import com.liferay.portlet.tags.service.TagsSourceLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsSourceService;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinder;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsAssetPersistence;
import com.liferay.portlet.tags.service.persistence.TagsAssetUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinder;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryPersistence;
import com.liferay.portlet.tags.service.persistence.TagsEntryUtil;
import com.liferay.portlet.tags.service.persistence.TagsPropertyFinder;
import com.liferay.portlet.tags.service.persistence.TagsPropertyFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder;
import com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence;
import com.liferay.portlet.tags.service.persistence.TagsPropertyUtil;
import com.liferay.portlet.tags.service.persistence.TagsSourcePersistence;
import com.liferay.portlet.tags.service.persistence.TagsSourceUtil;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="TagsSourceServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class TagsSourceServiceBaseImpl extends PrincipalBean
	implements TagsSourceService, InitializingBean {
	public TagsAssetLocalService getTagsAssetLocalService() {
		return tagsAssetLocalService;
	}

	public void setTagsAssetLocalService(
		TagsAssetLocalService tagsAssetLocalService) {
		this.tagsAssetLocalService = tagsAssetLocalService;
	}

	public TagsAssetService getTagsAssetService() {
		return tagsAssetService;
	}

	public void setTagsAssetService(TagsAssetService tagsAssetService) {
		this.tagsAssetService = tagsAssetService;
	}

	public TagsAssetPersistence getTagsAssetPersistence() {
		return tagsAssetPersistence;
	}

	public void setTagsAssetPersistence(
		TagsAssetPersistence tagsAssetPersistence) {
		this.tagsAssetPersistence = tagsAssetPersistence;
	}

	public TagsAssetFinder getTagsAssetFinder() {
		return tagsAssetFinder;
	}

	public void setTagsAssetFinder(TagsAssetFinder tagsAssetFinder) {
		this.tagsAssetFinder = tagsAssetFinder;
	}

	public TagsEntryLocalService getTagsEntryLocalService() {
		return tagsEntryLocalService;
	}

	public void setTagsEntryLocalService(
		TagsEntryLocalService tagsEntryLocalService) {
		this.tagsEntryLocalService = tagsEntryLocalService;
	}

	public TagsEntryService getTagsEntryService() {
		return tagsEntryService;
	}

	public void setTagsEntryService(TagsEntryService tagsEntryService) {
		this.tagsEntryService = tagsEntryService;
	}

	public TagsEntryPersistence getTagsEntryPersistence() {
		return tagsEntryPersistence;
	}

	public void setTagsEntryPersistence(
		TagsEntryPersistence tagsEntryPersistence) {
		this.tagsEntryPersistence = tagsEntryPersistence;
	}

	public TagsEntryFinder getTagsEntryFinder() {
		return tagsEntryFinder;
	}

	public void setTagsEntryFinder(TagsEntryFinder tagsEntryFinder) {
		this.tagsEntryFinder = tagsEntryFinder;
	}

	public TagsPropertyLocalService getTagsPropertyLocalService() {
		return tagsPropertyLocalService;
	}

	public void setTagsPropertyLocalService(
		TagsPropertyLocalService tagsPropertyLocalService) {
		this.tagsPropertyLocalService = tagsPropertyLocalService;
	}

	public TagsPropertyService getTagsPropertyService() {
		return tagsPropertyService;
	}

	public void setTagsPropertyService(TagsPropertyService tagsPropertyService) {
		this.tagsPropertyService = tagsPropertyService;
	}

	public TagsPropertyPersistence getTagsPropertyPersistence() {
		return tagsPropertyPersistence;
	}

	public void setTagsPropertyPersistence(
		TagsPropertyPersistence tagsPropertyPersistence) {
		this.tagsPropertyPersistence = tagsPropertyPersistence;
	}

	public TagsPropertyFinder getTagsPropertyFinder() {
		return tagsPropertyFinder;
	}

	public void setTagsPropertyFinder(TagsPropertyFinder tagsPropertyFinder) {
		this.tagsPropertyFinder = tagsPropertyFinder;
	}

	public TagsPropertyKeyFinder getTagsPropertyKeyFinder() {
		return tagsPropertyKeyFinder;
	}

	public void setTagsPropertyKeyFinder(
		TagsPropertyKeyFinder tagsPropertyKeyFinder) {
		this.tagsPropertyKeyFinder = tagsPropertyKeyFinder;
	}

	public TagsSourceLocalService getTagsSourceLocalService() {
		return tagsSourceLocalService;
	}

	public void setTagsSourceLocalService(
		TagsSourceLocalService tagsSourceLocalService) {
		this.tagsSourceLocalService = tagsSourceLocalService;
	}

	public TagsSourcePersistence getTagsSourcePersistence() {
		return tagsSourcePersistence;
	}

	public void setTagsSourcePersistence(
		TagsSourcePersistence tagsSourcePersistence) {
		this.tagsSourcePersistence = tagsSourcePersistence;
	}

	public void afterPropertiesSet() {
		if (tagsAssetLocalService == null) {
			tagsAssetLocalService = TagsAssetLocalServiceFactory.getImpl();
		}

		if (tagsAssetService == null) {
			tagsAssetService = TagsAssetServiceFactory.getImpl();
		}

		if (tagsAssetPersistence == null) {
			tagsAssetPersistence = TagsAssetUtil.getPersistence();
		}

		if (tagsAssetFinder == null) {
			tagsAssetFinder = TagsAssetFinderUtil.getFinder();
		}

		if (tagsEntryLocalService == null) {
			tagsEntryLocalService = TagsEntryLocalServiceFactory.getImpl();
		}

		if (tagsEntryService == null) {
			tagsEntryService = TagsEntryServiceFactory.getImpl();
		}

		if (tagsEntryPersistence == null) {
			tagsEntryPersistence = TagsEntryUtil.getPersistence();
		}

		if (tagsEntryFinder == null) {
			tagsEntryFinder = TagsEntryFinderUtil.getFinder();
		}

		if (tagsPropertyLocalService == null) {
			tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getImpl();
		}

		if (tagsPropertyService == null) {
			tagsPropertyService = TagsPropertyServiceFactory.getImpl();
		}

		if (tagsPropertyPersistence == null) {
			tagsPropertyPersistence = TagsPropertyUtil.getPersistence();
		}

		if (tagsPropertyFinder == null) {
			tagsPropertyFinder = TagsPropertyFinderUtil.getFinder();
		}

		if (tagsPropertyKeyFinder == null) {
			tagsPropertyKeyFinder = TagsPropertyKeyFinderUtil.getFinder();
		}

		if (tagsSourceLocalService == null) {
			tagsSourceLocalService = TagsSourceLocalServiceFactory.getImpl();
		}

		if (tagsSourcePersistence == null) {
			tagsSourcePersistence = TagsSourceUtil.getPersistence();
		}
	}

	protected TagsAssetLocalService tagsAssetLocalService;
	protected TagsAssetService tagsAssetService;
	protected TagsAssetPersistence tagsAssetPersistence;
	protected TagsAssetFinder tagsAssetFinder;
	protected TagsEntryLocalService tagsEntryLocalService;
	protected TagsEntryService tagsEntryService;
	protected TagsEntryPersistence tagsEntryPersistence;
	protected TagsEntryFinder tagsEntryFinder;
	protected TagsPropertyLocalService tagsPropertyLocalService;
	protected TagsPropertyService tagsPropertyService;
	protected TagsPropertyPersistence tagsPropertyPersistence;
	protected TagsPropertyFinder tagsPropertyFinder;
	protected TagsPropertyKeyFinder tagsPropertyKeyFinder;
	protected TagsSourceLocalService tagsSourceLocalService;
	protected TagsSourcePersistence tagsSourcePersistence;
}