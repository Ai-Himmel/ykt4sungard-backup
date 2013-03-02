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

package com.liferay.portlet.biblejournal.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.biblejournal.EntryContentException;
import com.liferay.portlet.biblejournal.EntryNameException;
import com.liferay.portlet.biblejournal.model.BJEntry;
import com.liferay.portlet.biblejournal.model.BJTopic;
import com.liferay.portlet.biblejournal.service.persistence.BJEntryUtil;
import com.liferay.portlet.biblejournal.service.spring.BJEntryService;
import com.liferay.portlet.biblejournal.service.spring.BJVerseServiceUtil;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;

/**
 * <a href="BJEntryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BJEntryServiceImpl
	extends PrincipalBean implements BJEntryService {

	// Business methods

	public BJEntry addEntry(
			String name, String content, String verses, String[] topicIds)
		throws PortalException, SystemException {

		_validate(name, content);

		String[] verseIds = BJVerseServiceUtil.parseVerseIds(verses);

		User user = getUser();

		String entryId = Long.toString(CounterServiceUtil.increment(
			BJEntry.class.getName()));

		BJEntry entry = BJEntryUtil.create(entryId);

		Date now = new Date();

		entry.setCompanyId(user.getCompanyId());
		entry.setUserId(user.getUserId());
		entry.setCreateDate(now);
		entry.setModifiedDate(now);
		entry.setName(name);
		entry.setContent(content);
		entry.setVersesInput(verses);

		BJEntryUtil.update(entry);

		BJEntryUtil.setBJTopics(entryId, topicIds);
		BJEntryUtil.setBJVerses(entryId, verseIds);

		return entry;
	}

	public void deleteEntry(String entryId)
		throws PortalException, SystemException {

		BJEntry entry = BJEntryUtil.findByPrimaryKey(entryId);

		deleteEntry(entry);
	}

	public void deleteEntry(BJEntry entry)
		throws PortalException, SystemException {

		if (!entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		BJEntryUtil.remove(entry.getEntryId());
	}

	public List getEntriesByCompany(String companyId) throws SystemException {
		return BJEntryUtil.findByCompanyId(companyId);
	}

	public List getEntriesByUser(String userId) throws SystemException {
		return BJEntryUtil.findByUserId(userId);
	}

	public BJEntry getEntry(String entryId)
		throws PortalException, SystemException {

		return BJEntryUtil.findByPrimaryKey(entryId);
	}

	public List getTopics(String entryId)
		throws PortalException, SystemException {

		return BJEntryUtil.getBJTopics(entryId);
	}

	public String[] getTopicIds(String entryId)
		throws PortalException, SystemException {

		List topics = BJEntryUtil.getBJTopics(entryId);

		String[] topicIds = new String[topics.size()];

		for (int i = 0; i < topics.size(); i++) {
			BJTopic topic = (BJTopic)topics.get(i);

			topicIds[i] = topic.getTopicId();
		}

		return topicIds;
	}

	public List getVerses(String entryId)
		throws PortalException, SystemException {

		return BJEntryUtil.getBJVerses(entryId);
	}

	public BJEntry updateEntry(
			String entryId, String name, String content, String verses,
			String[] topicIds)
		throws PortalException, SystemException {

		_validate(name, content);

		String[] verseIds = BJVerseServiceUtil.parseVerseIds(verses);

		BJEntry entry = BJEntryUtil.findByPrimaryKey(entryId);

		if (!entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		entry.setModifiedDate(new Date());
		entry.setName(name);
		entry.setContent(content);
		entry.setVersesInput(verses);

		BJEntryUtil.update(entry);

		BJEntryUtil.setBJTopics(entryId, topicIds);
		BJEntryUtil.setBJVerses(entryId, verseIds);

		return entry;
	}

	// Private methods

	private void _validate(String name, String content)
		throws PortalException {

		if (Validator.isNull(name)) {
			throw new EntryNameException();
		}
		else if (Validator.isNull(content)) {
			throw new EntryContentException();
		}
	}

}