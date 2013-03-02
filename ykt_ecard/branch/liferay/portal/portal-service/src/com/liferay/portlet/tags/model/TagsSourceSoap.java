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

package com.liferay.portlet.tags.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="TagsSourceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.tags.service.http.TagsSourceServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.http.TagsSourceServiceSoap
 *
 */
public class TagsSourceSoap implements Serializable {
	public static TagsSourceSoap toSoapModel(TagsSource model) {
		TagsSourceSoap soapModel = new TagsSourceSoap();

		soapModel.setSourceId(model.getSourceId());
		soapModel.setParentSourceId(model.getParentSourceId());
		soapModel.setName(model.getName());
		soapModel.setAcronym(model.getAcronym());

		return soapModel;
	}

	public static TagsSourceSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			TagsSource model = (TagsSource)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (TagsSourceSoap[])soapModels.toArray(new TagsSourceSoap[0]);
	}

	public TagsSourceSoap() {
	}

	public long getPrimaryKey() {
		return _sourceId;
	}

	public void setPrimaryKey(long pk) {
		setSourceId(pk);
	}

	public long getSourceId() {
		return _sourceId;
	}

	public void setSourceId(long sourceId) {
		_sourceId = sourceId;
	}

	public long getParentSourceId() {
		return _parentSourceId;
	}

	public void setParentSourceId(long parentSourceId) {
		_parentSourceId = parentSourceId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getAcronym() {
		return _acronym;
	}

	public void setAcronym(String acronym) {
		_acronym = acronym;
	}

	private long _sourceId;
	private long _parentSourceId;
	private String _name;
	private String _acronym;
}