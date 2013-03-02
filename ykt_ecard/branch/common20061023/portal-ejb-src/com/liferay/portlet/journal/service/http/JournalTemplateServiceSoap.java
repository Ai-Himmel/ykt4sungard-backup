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

package com.liferay.portlet.journal.service.http;

import com.liferay.portlet.journal.service.spring.JournalTemplateServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="JournalTemplateServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalTemplateServiceSoap {
	public static void deleteTemplate(java.lang.String templateId)
		throws RemoteException {
		try {
			JournalTemplateServiceUtil.deleteTemplate(templateId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalTemplateModel getTemplate(
		java.lang.String templateId) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalTemplate returnValue = JournalTemplateServiceUtil.getTemplate(templateId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalTemplateModel[] getTemplates(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalTemplateServiceUtil.getTemplates(portletId,
					groupId, companyId, begin, end);

			return (com.liferay.portlet.journal.model.JournalTemplate[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalTemplate[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalTemplateModel[] getTemplates(
		java.lang.String structureId) throws RemoteException {
		try {
			java.util.List returnValue = JournalTemplateServiceUtil.getTemplates(structureId);

			return (com.liferay.portlet.journal.model.JournalTemplate[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalTemplate[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalTemplateModel[] getTemplates(
		java.lang.String structureId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalTemplateServiceUtil.getTemplates(structureId,
					begin, end);

			return (com.liferay.portlet.journal.model.JournalTemplate[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalTemplate[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getTemplatesSize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws RemoteException {
		try {
			int returnValue = JournalTemplateServiceUtil.getTemplatesSize(portletId,
					groupId, companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getTemplatesSize(java.lang.String structureId)
		throws RemoteException {
		try {
			int returnValue = JournalTemplateServiceUtil.getTemplatesSize(structureId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}