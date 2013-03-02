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

package com.liferay.portlet.biblejournal.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.biblejournal.model.BJEntry;
import com.liferay.portlet.biblejournal.model.BJVerse;
import com.liferay.portlet.biblejournal.service.spring.BJEntryServiceUtil;
import com.liferay.portlet.biblejournal.service.spring.BJTopicServiceUtil;

import java.util.Iterator;

import org.crosswire.bible.passage.NoSuchVerseException;
import org.crosswire.bible.passage.Passage;
import org.crosswire.bible.passage.PassageFactory;
import org.crosswire.bible.passage.Verse;

/**
 * <a href="BJUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class BJUtil {

	public static String[] BOOKS = new String[] {
		"Genesis",
		"Exodus",
		"Leviticus",
		"Numbers",
		"Deuteronomy",
		"Joshua",
		"Judges",
		"Ruth",
		"1 Samuel",
		"2 Samuel",
		"1 Kings",
		"2 Kings",
		"1 Chronicles",
		"2 Chronicles",
		"Ezra",
		"Nehemiah",
		"Esther",
		"Job",
		"Psalm",
		"Proverbs",
		"Ecclesiastes",
		"Song of Solomon",
		"Isaiah",
		"Jeremiah",
		"Lamentations",
		"Ezekiel",
		"Daniel",
		"Hosea",
		"Joel",
		"Amos",
		"Obadiah",
		"Jonah",
		"Micah",
		"Nahum",
		"Habakkuk",
		"Zephaniah",
		"Haggai",
		"Zechariah",
		"Malachi",
		"Matthew",
		"Mark",
		"Luke",
		"John",
		"Acts",
		"Romans",
		"1 Corinthians",
		"2 Corinthians",
		"Galatians",
		"Ephesians",
		"Philippians",
		"Colossians",
		"1 Thessalonians",
		"2 Thessalonians",
		"1 Timothy",
		"2 Timothy",
		"Titus",
		"Philemon",
		"Hebrews",
		"James",
		"1 Peter",
		"2 Peter",
		"1 John",
		"2 John",
		"3 John",
		"Jude",
		"Revelation"
	};

	public static Passage getVerses(String topicId)
		throws PortalException, SystemException {

		Passage passage = PassageFactory.createPassage();

		Iterator itr1 = BJTopicServiceUtil.getEntries(topicId).iterator();

		while (itr1.hasNext()) {
			BJEntry entry = (BJEntry)itr1.next();

			Iterator itr2 = BJEntryServiceUtil.getVerses(
				entry.getEntryId()).iterator();

			while (itr2.hasNext()) {
				BJVerse bjVerse = (BJVerse)itr2.next();

				try {
					Verse verse = new Verse(bjVerse.getName());

					passage.add(verse);
				}
				catch (NoSuchVerseException nsve) {
					nsve.printStackTrace();
				}
			}
		}

		return passage;
	}

}