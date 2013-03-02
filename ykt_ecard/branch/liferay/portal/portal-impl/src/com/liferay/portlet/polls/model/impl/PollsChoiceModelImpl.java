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

package com.liferay.portlet.polls.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.polls.model.PollsChoice;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="PollsChoiceModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>PollsChoice</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.polls.service.model.PollsChoice
 * @see com.liferay.portlet.polls.service.model.PollsChoiceModel
 * @see com.liferay.portlet.polls.service.model.impl.PollsChoiceImpl
 *
 */
public class PollsChoiceModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "PollsChoice";
	public static final Object[][] TABLE_COLUMNS = {
			{ "uuid_", new Integer(Types.VARCHAR) },
			

			{ "choiceId", new Integer(Types.BIGINT) },
			

			{ "questionId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table PollsChoice (uuid_ VARCHAR(75) null,choiceId LONG not null primary key,questionId LONG,name VARCHAR(75) null,description VARCHAR(1000) null)";
	public static final String TABLE_SQL_DROP = "drop table PollsChoice";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.polls.model.PollsChoice"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.polls.model.PollsChoice"));

	public PollsChoiceModelImpl() {
	}

	public long getPrimaryKey() {
		return _choiceId;
	}

	public void setPrimaryKey(long pk) {
		setChoiceId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_choiceId);
	}

	public String getUuid() {
		return GetterUtil.getString(_uuid);
	}

	public void setUuid(String uuid) {
		if ((uuid != null) && (uuid != _uuid)) {
			_uuid = uuid;
		}
	}

	public long getChoiceId() {
		return _choiceId;
	}

	public void setChoiceId(long choiceId) {
		if (choiceId != _choiceId) {
			_choiceId = choiceId;
		}
	}

	public long getQuestionId() {
		return _questionId;
	}

	public void setQuestionId(long questionId) {
		if (questionId != _questionId) {
			_questionId = questionId;
		}
	}

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
		}
	}

	public PollsChoice toEscapedModel() {
		if (isEscapedModel()) {
			return (PollsChoice)this;
		}
		else {
			PollsChoice model = new PollsChoiceImpl();

			model.setEscapedModel(true);

			model.setUuid(Html.escape(getUuid()));
			model.setChoiceId(getChoiceId());
			model.setQuestionId(getQuestionId());
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));

			model = (PollsChoice)Proxy.newProxyInstance(PollsChoice.class.getClassLoader(),
					new Class[] { PollsChoice.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PollsChoiceImpl clone = new PollsChoiceImpl();

		clone.setUuid(getUuid());
		clone.setChoiceId(getChoiceId());
		clone.setQuestionId(getQuestionId());
		clone.setName(getName());
		clone.setDescription(getDescription());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PollsChoiceImpl pollsChoice = (PollsChoiceImpl)obj;

		int value = 0;

		if (getQuestionId() < pollsChoice.getQuestionId()) {
			value = -1;
		}
		else if (getQuestionId() > pollsChoice.getQuestionId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		value = getName().compareTo(pollsChoice.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		PollsChoiceImpl pollsChoice = null;

		try {
			pollsChoice = (PollsChoiceImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = pollsChoice.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private String _uuid;
	private long _choiceId;
	private long _questionId;
	private String _name;
	private String _description;
}