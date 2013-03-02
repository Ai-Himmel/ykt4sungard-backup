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

package com.liferay.portlet.journal.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="JournalArticleImageSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.journal.service.http.JournalArticleImageServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.http.JournalArticleImageServiceSoap
 *
 */
public class JournalArticleImageSoap implements Serializable {
	public static JournalArticleImageSoap toSoapModel(JournalArticleImage model) {
		JournalArticleImageSoap soapModel = new JournalArticleImageSoap();

		soapModel.setArticleImageId(model.getArticleImageId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setArticleId(model.getArticleId());
		soapModel.setVersion(model.getVersion());
		soapModel.setElName(model.getElName());
		soapModel.setLanguageId(model.getLanguageId());
		soapModel.setTempImage(model.getTempImage());

		return soapModel;
	}

	public static JournalArticleImageSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			JournalArticleImage model = (JournalArticleImage)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (JournalArticleImageSoap[])soapModels.toArray(new JournalArticleImageSoap[0]);
	}

	public JournalArticleImageSoap() {
	}

	public long getPrimaryKey() {
		return _articleImageId;
	}

	public void setPrimaryKey(long pk) {
		setArticleImageId(pk);
	}

	public long getArticleImageId() {
		return _articleImageId;
	}

	public void setArticleImageId(long articleImageId) {
		_articleImageId = articleImageId;
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		_groupId = groupId;
	}

	public String getArticleId() {
		return _articleId;
	}

	public void setArticleId(String articleId) {
		_articleId = articleId;
	}

	public double getVersion() {
		return _version;
	}

	public void setVersion(double version) {
		_version = version;
	}

	public String getElName() {
		return _elName;
	}

	public void setElName(String elName) {
		_elName = elName;
	}

	public String getLanguageId() {
		return _languageId;
	}

	public void setLanguageId(String languageId) {
		_languageId = languageId;
	}

	public boolean getTempImage() {
		return _tempImage;
	}

	public boolean isTempImage() {
		return _tempImage;
	}

	public void setTempImage(boolean tempImage) {
		_tempImage = tempImage;
	}

	private long _articleImageId;
	private long _groupId;
	private String _articleId;
	private double _version;
	private String _elName;
	private String _languageId;
	private boolean _tempImage;
}