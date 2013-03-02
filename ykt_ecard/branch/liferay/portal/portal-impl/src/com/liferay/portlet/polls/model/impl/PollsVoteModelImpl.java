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

import com.liferay.portlet.polls.model.PollsVote;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="PollsVoteModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>PollsVote</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.polls.service.model.PollsVote
 * @see com.liferay.portlet.polls.service.model.PollsVoteModel
 * @see com.liferay.portlet.polls.service.model.impl.PollsVoteImpl
 *
 */
public class PollsVoteModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "PollsVote";
	public static final Object[][] TABLE_COLUMNS = {
			{ "voteId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "questionId", new Integer(Types.BIGINT) },
			

			{ "choiceId", new Integer(Types.BIGINT) },
			

			{ "voteDate", new Integer(Types.TIMESTAMP) }
		};
	public static final String TABLE_SQL_CREATE = "create table PollsVote (voteId LONG not null primary key,userId LONG,questionId LONG,choiceId LONG,voteDate DATE null)";
	public static final String TABLE_SQL_DROP = "drop table PollsVote";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.polls.model.PollsVote"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.polls.model.PollsVote"));

	public PollsVoteModelImpl() {
	}

	public long getPrimaryKey() {
		return _voteId;
	}

	public void setPrimaryKey(long pk) {
		setVoteId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_voteId);
	}

	public long getVoteId() {
		return _voteId;
	}

	public void setVoteId(long voteId) {
		if (voteId != _voteId) {
			_voteId = voteId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
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

	public long getChoiceId() {
		return _choiceId;
	}

	public void setChoiceId(long choiceId) {
		if (choiceId != _choiceId) {
			_choiceId = choiceId;
		}
	}

	public Date getVoteDate() {
		return _voteDate;
	}

	public void setVoteDate(Date voteDate) {
		if (((voteDate == null) && (_voteDate != null)) ||
				((voteDate != null) && (_voteDate == null)) ||
				((voteDate != null) && (_voteDate != null) &&
				!voteDate.equals(_voteDate))) {
			_voteDate = voteDate;
		}
	}

	public PollsVote toEscapedModel() {
		if (isEscapedModel()) {
			return (PollsVote)this;
		}
		else {
			PollsVote model = new PollsVoteImpl();

			model.setEscapedModel(true);

			model.setVoteId(getVoteId());
			model.setUserId(getUserId());
			model.setQuestionId(getQuestionId());
			model.setChoiceId(getChoiceId());
			model.setVoteDate(getVoteDate());

			model = (PollsVote)Proxy.newProxyInstance(PollsVote.class.getClassLoader(),
					new Class[] { PollsVote.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PollsVoteImpl clone = new PollsVoteImpl();

		clone.setVoteId(getVoteId());
		clone.setUserId(getUserId());
		clone.setQuestionId(getQuestionId());
		clone.setChoiceId(getChoiceId());
		clone.setVoteDate(getVoteDate());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PollsVoteImpl pollsVote = (PollsVoteImpl)obj;

		long pk = pollsVote.getPrimaryKey();

		if (getPrimaryKey() < pk) {
			return -1;
		}
		else if (getPrimaryKey() > pk) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		PollsVoteImpl pollsVote = null;

		try {
			pollsVote = (PollsVoteImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = pollsVote.getPrimaryKey();

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

	private long _voteId;
	private long _userId;
	private long _questionId;
	private long _choiceId;
	private Date _voteDate;
}