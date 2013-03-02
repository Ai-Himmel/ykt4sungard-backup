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

package com.liferay.portlet.journal.model.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Image;
import com.liferay.portal.service.ImageLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.util.LocaleTransformerListener;
import com.liferay.util.LocalizationUtil;

/**
 * <a href="JournalArticleImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleImpl
	extends JournalArticleModelImpl implements JournalArticle {

	public static final double DEFAULT_VERSION = 1.0;

	public static final String[] TYPES =
		PropsUtil.getArray(PropsUtil.JOURNAL_ARTICLE_TYPES);

	public static final String PORTLET = "portlet";

	public static final String STAND_ALONE = "stand-alone";

	public JournalArticleImpl() {
	}

	public String getUserUuid() throws SystemException {
		return PortalUtil.getUserValue(getUserId(), "uuid", _userUuid);
	}

	public void setUserUuid(String userUuid) {
		_userUuid = userUuid;
	}

	public String[] getAvailableLocales() {
		return LocalizationUtil.getAvailableLocales(getContent());
	}

	public String getContentByLocale(String languageId){
		LocaleTransformerListener listener = new LocaleTransformerListener();

		listener.setTemplateDriven(isTemplateDriven());
		listener.setLanguageId(languageId);

		return listener.onXml(getContent());
	}

	public String getDefaultLocale() {
		String xml = getContent();

		if (xml == null) {
			return StringPool.BLANK;
		}

		if (isTemplateDriven()) {
			String defaultLanguageId = LocaleUtil.toLanguageId(
				LocaleUtil.getDefault());

			return defaultLanguageId;
		}
		else {
			return LocalizationUtil.getDefaultLocale(xml);
		}
	}

	public boolean isTemplateDriven() {
		if (Validator.isNull(getStructureId())) {
			return false;
		}
		else {
			return true;
		}
	}

	public String getApprovedByUserUuid() throws SystemException {
		return PortalUtil.getUserValue(
			getApprovedByUserId(), "uuid", _approvedByUserUuid);
	}

	public void setApprovedByUserUuid(String approvedByUserUuid) {
		_approvedByUserUuid = approvedByUserUuid;
	}

	public String getSmallImageType() throws PortalException, SystemException {
		if (_smallImageType == null && isSmallImage()) {
			Image smallImage =  ImageLocalServiceUtil.getImage(
				getSmallImageId());

			_smallImageType = smallImage.getType();
		}

		return _smallImageType;
	}

	public void setSmallImageType(String smallImageType) {
		_smallImageType = smallImageType;
	}

	private String _userUuid;
	private String _approvedByUserUuid;
	private String _smallImageType;

}