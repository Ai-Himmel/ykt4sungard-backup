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

package com.liferay.portal.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.NoteContentException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Note;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.NoteUtil;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.NoteLocalService;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;

/**
 * <a href="NoteLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class NoteLocalServiceImpl implements NoteLocalService {

	// Business methods

	public Note addNote(
			String userId, String className, String classPK, String content)
		throws PortalException, SystemException {

		_validate(content);

		User user = UserUtil.findByPrimaryKey(userId);

		String noteId = Long.toString(CounterServiceUtil.increment(
			Note.class.getName()));

		Note note = NoteUtil.create(noteId);

		Date now = new Date();

		note.setCompanyId(user.getCompanyId());
		note.setUserId(user.getUserId());
		note.setUserName(user.getFullName());
		note.setCreateDate(now);
		note.setModifiedDate(now);
		note.setClassName(className);
		note.setClassPK(classPK);
		note.setContent(content);

		NoteUtil.update(note);

		return note;
	}

	public void deleteNote(String noteId)
		throws PortalException, SystemException {

		NoteUtil.remove(noteId);
	}

	public void deleteNotes(String companyId, String className, String classPK)
		throws SystemException {

		NoteUtil.removeByC_C_C(companyId, className, classPK);
	}

	public Note getNote(String noteId) throws PortalException, SystemException {
		return NoteUtil.findByPrimaryKey(noteId);
	}

	public List getNotes(String companyId, String className, String classPK)
		throws PortalException, SystemException {

		return NoteUtil.findByC_C_C(companyId, className, classPK);
	}

	public Note updateNote(String noteId, String content)
		throws PortalException, SystemException {

		_validate(content);

		Note note = NoteUtil.findByPrimaryKey(noteId);

		note.setModifiedDate(new Date());
		note.setContent(content);

		NoteUtil.update(note);

		return note;
	}

	// Private methods

	private void _validate(String content) throws PortalException {
		if (Validator.isNull(content)) {
			throw new NoteContentException();
		}
	}

}