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

package com.liferay.portlet.blogs.lar;

import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.BlogsEntryLocalServiceUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;

import com.thoughtworks.xstream.XStream;

import java.util.Calendar;
import java.util.Iterator;
import java.util.List;

import javax.portlet.PortletPreferences;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="BlogsPortletDataHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class BlogsPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Entries

			if (!context.addPrimaryKey(
					BlogsPortletDataHandlerImpl.class, "deleteData")) {

				BlogsEntryLocalServiceUtil.deleteEntries(context.getGroupId());
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public String exportData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = DocumentHelper.createDocument();

			Element root = doc.addElement("blogs-data");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Entries

			List entries = BlogsEntryUtil.findByGroupId(context.getGroupId());

			Iterator itr = entries.iterator();

			while (itr.hasNext()) {
				BlogsEntry entry = (BlogsEntry)itr.next();

				if (context.addPrimaryKey(
						BlogsEntry.class, entry.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					entry.setUserUuid(entry.getUserUuid());

					if (context.getBooleanParameter(_NAMESPACE, "comments")) {
						context.addComments(
							BlogsEntry.class, entry.getPrimaryKeyObj());
					}

					if (context.getBooleanParameter(_NAMESPACE, "ratings")) {
						context.addRatingsEntries(
							BlogsEntry.class, entry.getPrimaryKeyObj());
					}

					if (context.getBooleanParameter(_NAMESPACE, "tags")) {
						context.addTagsEntries(
							BlogsEntry.class, entry.getPrimaryKeyObj());
					}
				}
			}

			String xml = xStream.toXML(entries);

			Element el = root.addElement("blog-entries");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			return doc.asXML();
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public PortletDataHandlerControl[] getExportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {
			_entries, _comments, _ratings, _tags
		};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {
			_entries, _comments, _ratings, _tags
		};
	}

	public PortletPreferences importData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs, String data)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = PortalUtil.readDocumentFromXML(data);

			Element root = doc.getRootElement();

			// Entries

			Element el = root.element("blog-entries").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			List entries = (List)xStream.fromXML(tempDoc.asXML());

			Iterator itr = entries.iterator();

			while (itr.hasNext()) {
				BlogsEntry entry = (BlogsEntry)itr.next();

				importEntry(context, entry);
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected void importEntry(PortletDataContext context, BlogsEntry entry)
		throws Exception {

		long userId = context.getUserId(entry.getUserUuid());
		long plid = context.getPlid();

		Calendar displayDateCal = CalendarFactoryUtil.getCalendar();

		displayDateCal.setTime(entry.getDisplayDate());

		int displayDateMonth = displayDateCal.get(Calendar.MONTH);
		int displayDateDay = displayDateCal.get(Calendar.DATE);
		int displayDateYear = displayDateCal.get(Calendar.YEAR);
		int displayDateHour = displayDateCal.get(Calendar.HOUR);
		int displayDateMinute = displayDateCal.get(Calendar.MINUTE);

		String[] tagsEntries = null;

		if (context.getBooleanParameter(_NAMESPACE, "tags")) {
			tagsEntries = context.getTagsEntries(
				BlogsEntry.class, entry.getPrimaryKeyObj());
		}

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		ThemeDisplay themeDisplay = null;

		BlogsEntry existingEntry = null;

		if (context.getDataStrategy().equals(
				PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

			existingEntry = BlogsEntryUtil.fetchByUUID_G(
				entry.getUuid(), context.getGroupId());

			if (existingEntry == null) {
				existingEntry = BlogsEntryLocalServiceUtil.addEntry(
					entry.getUuid(), userId, plid, entry.getTitle(),
					entry.getContent(), displayDateMonth, displayDateDay,
					displayDateYear, displayDateHour, displayDateMinute,
					tagsEntries, addCommunityPermissions, addGuestPermissions,
					themeDisplay);
			}
			else {
				existingEntry = BlogsEntryLocalServiceUtil.updateEntry(
					userId, existingEntry.getEntryId(), entry.getTitle(),
					entry.getContent(), displayDateMonth, displayDateDay,
					displayDateYear, displayDateHour, displayDateMinute,
					tagsEntries, themeDisplay);
			}
		}
		else {
			existingEntry = BlogsEntryLocalServiceUtil.addEntry(
				userId, plid, entry.getTitle(), entry.getContent(),
				displayDateMonth, displayDateDay, displayDateYear,
				displayDateHour, displayDateMinute, tagsEntries,
				addCommunityPermissions, addGuestPermissions, themeDisplay);
		}

		if (context.getBooleanParameter(_NAMESPACE, "comments")) {
			context.importComments(
				BlogsEntry.class, entry.getPrimaryKeyObj(),
				existingEntry.getPrimaryKeyObj(), context.getGroupId());
		}

		if (context.getBooleanParameter(_NAMESPACE, "ratings")) {
			context.importRatingsEntries(
				BlogsEntry.class, entry.getPrimaryKeyObj(),
				existingEntry.getPrimaryKeyObj());
		}
	}

	private static final String _NAMESPACE = "blogs";

	private static final PortletDataHandlerBoolean _entries =
		new PortletDataHandlerBoolean(_NAMESPACE, "entries", true, true);

	private static final PortletDataHandlerBoolean _comments =
		new PortletDataHandlerBoolean(_NAMESPACE, "comments");

	private static final PortletDataHandlerBoolean _ratings =
		new PortletDataHandlerBoolean(_NAMESPACE, "ratings");

	private static final PortletDataHandlerBoolean _tags =
		new PortletDataHandlerBoolean(_NAMESPACE, "tags");

}