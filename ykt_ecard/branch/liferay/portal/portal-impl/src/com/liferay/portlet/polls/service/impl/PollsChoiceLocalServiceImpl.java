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

package com.liferay.portlet.polls.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.polls.QuestionChoiceException;
import com.liferay.portlet.polls.model.PollsChoice;
import com.liferay.portlet.polls.service.base.PollsChoiceLocalServiceBaseImpl;

import java.util.List;

/**
 * <a href="PollsChoiceLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsChoiceLocalServiceImpl
	extends PollsChoiceLocalServiceBaseImpl {

	public PollsChoice addChoice(
			long questionId, String name, String description)
		throws PortalException, SystemException {

		return addChoice(null, questionId, name, description);
	}

	public PollsChoice addChoice(
			String uuid, long questionId, String name, String description)
		throws PortalException, SystemException {

		validate(name, description);

		pollsQuestionPersistence.findByPrimaryKey(questionId);

		long choiceId = counterLocalService.increment();

		PollsChoice choice = pollsChoicePersistence.create(choiceId);

		choice.setUuid(uuid);
		choice.setQuestionId(questionId);
		choice.setName(name);
		choice.setDescription(description);

		pollsChoicePersistence.update(choice);

		return choice;
	}

	public PollsChoice getChoice(long choiceId)
		throws PortalException, SystemException {

		return pollsChoicePersistence.findByPrimaryKey(choiceId);
	}

	public List getChoices(long questionId) throws SystemException {
		return pollsChoicePersistence.findByQuestionId(questionId);
	}

	public int getChoicesCount(long questionId) throws SystemException {
		return pollsChoicePersistence.countByQuestionId(questionId);
	}

	public PollsChoice updateChoice(
			long choiceId, long questionId, String name, String description)
		throws PortalException, SystemException {

		validate(name, description);

		pollsQuestionPersistence.findByPrimaryKey(questionId);

		PollsChoice choice = pollsChoicePersistence.findByPrimaryKey(choiceId);

		choice.setQuestionId(questionId);
		choice.setName(name);
		choice.setDescription(description);

		pollsChoicePersistence.update(choice);

		return choice;
	}

	protected void validate(String name, String description)
		throws PortalException {

		if (Validator.isNull(name) || Validator.isNull(description)) {
			throw new QuestionChoiceException();
		}
	}

}