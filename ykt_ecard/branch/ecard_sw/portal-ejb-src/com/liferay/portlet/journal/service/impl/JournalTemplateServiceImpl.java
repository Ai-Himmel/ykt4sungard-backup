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

package com.liferay.portlet.journal.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.journal.DuplicateTemplateIdException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.RequiredTemplateException;
import com.liferay.portlet.journal.TemplateDescriptionException;
import com.liferay.portlet.journal.TemplateIdException;
import com.liferay.portlet.journal.TemplateNameException;
import com.liferay.portlet.journal.TemplateSmallImageNameException;
import com.liferay.portlet.journal.TemplateSmallImageSizeException;
import com.liferay.portlet.journal.TemplateXslException;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplateUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalTemplateService;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.io.File;
import java.io.IOException;

import java.util.Date;
import java.util.List;

import org.dom4j.DocumentException;

/**
 * <a href="JournalTemplateServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class JournalTemplateServiceImpl
	extends PrincipalBean implements JournalTemplateService {

	// Business methods

	public JournalTemplate addTemplate(
			String templateId, boolean autoTemplateId, String portletId,
			String groupId, String structureId, String name, String description,
			String xsl, boolean formatXsl, boolean smallImage,
			String smallImageURL, File smallFile)
		throws PortalException, SystemException {

		templateId = templateId.trim().toUpperCase();

		try {
			if (formatXsl) {
				xsl = JournalUtil.formatXML(xsl);
			}
		}
		catch (DocumentException de) {
			throw new TemplateXslException();
		}
		catch (IOException ioe) {
			throw new TemplateXslException();
		}

		byte[] smallBytes = null;
		try {
			smallBytes = FileUtil.getBytes(smallFile);
		}
		catch (IOException ioe) {
		}

		_validate(
			templateId, autoTemplateId, name, description, xsl, smallImage,
			smallImageURL, smallFile, smallBytes);

		User user = getUser();

		if (autoTemplateId) {
			templateId = Long.toString(CounterServiceUtil.increment(
				JournalTemplate.class.getName()));
		}

		JournalTemplate template = JournalTemplateUtil.create(templateId);

		Date now = new Date();

		template.setPortletId(portletId);
		template.setGroupId(groupId);
		template.setCompanyId(user.getCompanyId());
		template.setUserId(user.getUserId());
		template.setUserName(user.getFullName());
		template.setCreateDate(now);
		template.setModifiedDate(now);
		template.setStructureId(structureId);
		template.setName(name);
		template.setDescription(description);
		template.setXsl(xsl);
		template.setSmallImage(smallImage);
		template.setSmallImageURL(smallImageURL);

		JournalTemplateUtil.update(template);

		// Save images

		_saveImages(
			smallImage, template.getSmallImageId(), smallFile, smallBytes);

		return template;
	}

	public void deleteTemplate(String templateId)
		throws PortalException, SystemException {

		templateId = templateId.trim().toUpperCase();

		if (!JournalArticleServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		if (JournalArticleUtil.countByTemplateId(templateId) > 0) {
			throw new RequiredTemplateException();
		}

		// Find template

		JournalTemplate template =
			JournalTemplateUtil.findByPrimaryKey(templateId);

		// Delete template

		JournalTemplateUtil.remove(templateId);

		// Delete all images associated with this template

		ImageLocalUtil.remove(template.getSmallImageId());
	}

	public JournalTemplate getTemplate(String templateId)
		throws PortalException, SystemException {

		templateId = templateId.trim().toUpperCase();

		return JournalTemplateUtil.findByPrimaryKey(templateId);
	}

	public List getTemplates(
			String portletId, String groupId, String companyId, int begin,
			int end)
		throws SystemException {

		return JournalTemplateUtil.findByP_G_C(
			portletId, groupId, companyId, begin, end);
	}

	public List getTemplates(String structureId)
		throws SystemException {

		return JournalTemplateUtil.findByStructureId(structureId);
	}

	public List getTemplates(String structureId, int begin, int end)
		throws SystemException {

		return JournalTemplateUtil.findByStructureId(structureId, begin, end);
	}

	public int getTemplatesSize(
			String portletId, String groupId, String companyId)
		throws SystemException {

		return JournalTemplateUtil.countByP_G_C(portletId, groupId, companyId);
	}

	public int getTemplatesSize(String structureId) throws SystemException {
		return JournalTemplateUtil.countByStructureId(structureId);
	}

	public JournalTemplate updateTemplate(
			String templateId, String name, String description, String xsl,
			boolean formatXsl, boolean smallImage, String smallImageURL,
			File smallFile)
		throws PortalException, SystemException {

		templateId = templateId.trim().toUpperCase();

		try {
			if (formatXsl) {
				xsl = JournalUtil.formatXML(xsl);
			}
		}
		catch (DocumentException de) {
			throw new TemplateXslException();
		}
		catch (IOException ioe) {
			throw new TemplateXslException();
		}

		byte[] smallBytes = null;
		try {
			smallBytes = FileUtil.getBytes(smallFile);
		}
		catch (IOException ioe) {
		}

		_validate(
			name, description, xsl, smallImage, smallImageURL, smallFile,
			smallBytes);

		User user = getUser();

		JournalTemplate template =
			JournalTemplateUtil.findByPrimaryKey(templateId);

		template.setModifiedDate(new Date());
		template.setName(name);
		template.setDescription(description);
		template.setXsl(xsl);
		template.setSmallImage(smallImage);
		template.setSmallImageURL(smallImageURL);

		JournalTemplateUtil.update(template);

		// Save images

		_saveImages(
			smallImage, template.getSmallImageId(), smallFile, smallBytes);

		return template;
	}

	// Private methods

	private void _saveImages(
		boolean smallImage, String smallImageKey, File smallFile,
		byte[] smallBytes) {

		// Save small image

		if (smallImage) {
			if (smallFile != null && smallBytes != null) {
				ImageLocalUtil.put(smallImageKey, smallBytes);
			}
		}
		else {
			ImageLocalUtil.remove(smallImageKey);
		}
	}

	private void _validate(
			String templateId, boolean autoTemplateId, String name,
			String description, String xsl, boolean smallImage,
			String smallImageURL, File smallFile, byte[] smallBytes)
		throws PortalException, SystemException {

		if (!autoTemplateId) {
			if ((Validator.isNull(templateId)) ||
				(Validator.isNumber(templateId)) ||
				(templateId.indexOf(StringPool.SPACE) != -1)) {

				throw new TemplateIdException();
			}

			try {
				JournalTemplateUtil.findByPrimaryKey(templateId);

				throw new DuplicateTemplateIdException();
			}
			catch (NoSuchTemplateException nste) {
			}
		}

		_validate(name, description, xsl, smallImage, smallImageURL, smallFile,
				  smallBytes);
	}

	private void _validate(
			String name, String description, String xsl, boolean smallImage,
			String smallImageURL, File smallFile, byte[] smallBytes)
		throws PortalException {

		if (Validator.isNull(name)) {
			throw new TemplateNameException();
		}
		else if (Validator.isNull(description)) {
			throw new TemplateDescriptionException();
		}
		else if (Validator.isNull(xsl)) {
			throw new TemplateXslException();
		}

		String[] imageExtensions =
			PropsUtil.getArray(PropsUtil.JOURNAL_IMAGE_EXTENSIONS);

		// Small image

		if (smallImage && Validator.isNull(smallImageURL) &&
			smallFile != null && smallBytes != null) {

			String smallImageName = smallFile.getName();

			if (smallImageName != null) {
				boolean validSmallImageExtension = false;

				for (int i = 0; i < imageExtensions.length; i++) {
					if (StringPool.STAR.equals(imageExtensions[i]) ||
						StringUtil.endsWith(
							smallImageName, imageExtensions[i])) {

						validSmallImageExtension = true;

						break;
					}
				}

				if (!validSmallImageExtension) {
					throw new TemplateSmallImageNameException(smallImageName);
				}
			}

			long smallImageMaxSize = GetterUtil.getLong(
				PropsUtil.get(PropsUtil.JOURNAL_IMAGE_SMALL_MAX_SIZE));

			if ((smallImageMaxSize > 0) &&
				((smallBytes == null) ||
					(smallBytes.length > smallImageMaxSize))) {

				throw new TemplateSmallImageSizeException();
			}
		}
	}

}