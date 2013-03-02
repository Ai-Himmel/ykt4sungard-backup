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

import com.liferay.portlet.journal.service.spring.JournalStructureServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="JournalStructureServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalStructureServiceSoap {
	public static com.liferay.portlet.journal.model.JournalStructureModel addStructure(
		java.lang.String structureId, boolean autoStructureId,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String name, java.lang.String description,
		java.lang.String xsd) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.addStructure(structureId,
					autoStructureId, portletId, groupId, name, description, xsd);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteStructure(java.lang.String structureId)
		throws RemoteException {
		try {
			JournalStructureServiceUtil.deleteStructure(structureId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalStructureModel getStructure(
		java.lang.String structureId) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.getStructure(structureId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalStructureModel[] getStructures(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalStructureServiceUtil.getStructures(portletId,
					groupId, companyId, begin, end);

			return (com.liferay.portlet.journal.model.JournalStructure[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalStructure[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getStructuresSize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws RemoteException {
		try {
			int returnValue = JournalStructureServiceUtil.getStructuresSize(portletId,
					groupId, companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalStructureModel updateStructure(
		java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsd)
		throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.updateStructure(structureId,
					name, description, xsd);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}