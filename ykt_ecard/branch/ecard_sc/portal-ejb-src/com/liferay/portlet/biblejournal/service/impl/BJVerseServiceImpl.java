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
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.biblejournal.NoSuchVerseException;
import com.liferay.portlet.biblejournal.model.BJEntry;
import com.liferay.portlet.biblejournal.model.BJTopic;
import com.liferay.portlet.biblejournal.model.BJVerse;
import com.liferay.portlet.biblejournal.service.persistence.BJEntryUtil;
import com.liferay.portlet.biblejournal.service.persistence.BJVerseUtil;
import com.liferay.portlet.biblejournal.service.spring.BJVerseService;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.crosswire.bible.passage.Passage;
import org.crosswire.bible.passage.PassageFactory;
import org.crosswire.bible.passage.Verse;

/**
 * <a href="BJVerseServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BJVerseServiceImpl
	extends PrincipalBean implements BJVerseService {

	// Business methods

	public List getEntries(int book, int chapter, int verse)
		throws PortalException, SystemException {

		try {
			User user = getUser();

			Verse verseObj = new Verse(book, chapter, verse);

			BJVerse bjVerse = _getBJVerse(
				user.getCompanyId(), getUserId(), verseObj.getName());

			return BJVerseUtil.getBJEntries(bjVerse.getVerseId());
		}
		catch (org.crosswire.bible.passage.NoSuchVerseException nsve) {
			throw new NoSuchVerseException();
		}
	}

	public List getTopics(int book, int chapter, int verse)
		throws PortalException, SystemException {

		try {
			List topics = new ArrayList();

			User user = getUser();

			Verse verseObj = new Verse(book, chapter, verse);

			String verseId = _getBJVerseId(
				user.getCompanyId(), getUserId(), verseObj.getName());

			Iterator itr1 = BJVerseUtil.getBJEntries(verseId).iterator();

			while (itr1.hasNext()) {
				BJEntry entry = (BJEntry)itr1.next();

				Iterator itr2 = BJEntryUtil.getBJTopics(
					entry.getEntryId()).iterator();

				while (itr2.hasNext()) {
					BJTopic topic = (BJTopic)itr2.next();

					topics.add(topic);
				}
			}

			return topics;
		}
		catch (org.crosswire.bible.passage.NoSuchVerseException nsve) {
			throw new NoSuchVerseException();
		}
	}

	public boolean hasEntries(int book, int chapter, int verse)
		throws PortalException, SystemException {

		if (getEntries(book, chapter, verse).size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public String[] parseVerseIds(String verses)
		throws PortalException, SystemException {

		try {
			List versesList = new ArrayList();

			Passage passage = PassageFactory.createPassage(verses);

			int countVerses = passage.countVerses();

			if (countVerses > 0) {
				User user = getUser();

				for (int i = 0; i < countVerses; i++) {
					Verse verse = passage.getVerseAt(i);

					String bjVerseId = _getBJVerseId(
						user.getCompanyId(), user.getUserId(), verse.getName());

					versesList.add(bjVerseId);
				}
			}

			return (String[])versesList.toArray(new String[0]);
		}
		catch (org.crosswire.bible.passage.NoSuchVerseException nsve) {
			throw new NoSuchVerseException();
		}
	}

	public BJVerse[] parseVerses(String verses)
		throws PortalException, SystemException {

		try {
			List versesList = new ArrayList();

			Passage passage = PassageFactory.createPassage(verses);

			int countVerses = passage.countVerses();

			if (countVerses > 0) {
				User user = getUser();

				for (int i = 0; i < countVerses; i++) {
					Verse verse = passage.getVerseAt(i);

					BJVerse bjVerse = _getBJVerse(
						user.getCompanyId(), user.getUserId(), verse.getName());

					versesList.add(bjVerse);
				}
			}

			return (BJVerse[])versesList.toArray(new BJVerse[0]);
		}
		catch (org.crosswire.bible.passage.NoSuchVerseException nsve) {
			throw new NoSuchVerseException();
		}
	}

	// Private methods

	public BJVerse _getBJVerse(String companyId, String userId, String name)
		throws SystemException {

		BJVerse verse = null;

		try {
			verse = BJVerseUtil.findByC_U_N(companyId, userId, name);
		}
		catch (com.liferay.portlet.biblejournal.NoSuchVerseException nsve) {
			String verseId = Long.toString(CounterServiceUtil.increment(
				BJVerse.class.getName()));

			verse = BJVerseUtil.create(verseId);

			verse.setCompanyId(companyId);
			verse.setUserId(userId);
			verse.setName(name);

			BJVerseUtil.update(verse);
		}

		return verse;
	}

	public String _getBJVerseId(String companyId, String userId, String name)
		throws SystemException {

		return _getBJVerse(companyId, userId, name).getVerseId();
	}

}