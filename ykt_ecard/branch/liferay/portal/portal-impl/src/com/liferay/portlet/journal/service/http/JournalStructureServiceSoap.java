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

package com.liferay.portlet.journal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import com.liferay.portlet.journal.service.JournalStructureServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="JournalStructureServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.journal.service.JournalStructureServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.journal.model.JournalStructureSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.journal.model.JournalStructure</code>,
 * that is translated to a <code>com.liferay.portlet.journal.model.JournalStructureSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalStructureServiceUtil
 * @see com.liferay.portlet.journal.service.http.JournalStructureServiceHttp
 * @see com.liferay.portlet.journal.service.model.JournalStructureSoap
 *
 */
public class JournalStructureServiceSoap {
	public static com.liferay.portlet.journal.model.JournalStructureSoap addStructure(
		java.lang.String structureId, boolean autoStructureId, long plid,
		java.lang.String name, java.lang.String description,
		java.lang.String xsd, boolean addCommunityPermissions,
		boolean addGuestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.addStructure(structureId,
					autoStructureId, plid, name, description, xsd,
					addCommunityPermissions, addGuestPermissions);

			return com.liferay.portlet.journal.model.JournalStructureSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalStructureSoap addStructure(
		java.lang.String structureId, boolean autoStructureId, long plid,
		java.lang.String name, java.lang.String description,
		java.lang.String xsd, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.addStructure(structureId,
					autoStructureId, plid, name, description, xsd,
					communityPermissions, guestPermissions);

			return com.liferay.portlet.journal.model.JournalStructureSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteStructure(long groupId,
		java.lang.String structureId) throws RemoteException {
		try {
			JournalStructureServiceUtil.deleteStructure(groupId, structureId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalStructureSoap getStructure(
		long groupId, java.lang.String structureId) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.getStructure(groupId,
					structureId);

			return com.liferay.portlet.journal.model.JournalStructureSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalStructureSoap updateStructure(
		long groupId, java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsd)
		throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalStructure returnValue = JournalStructureServiceUtil.updateStructure(groupId,
					structureId, name, description, xsd);

			return com.liferay.portlet.journal.model.JournalStructureSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(JournalStructureServiceSoap.class);
}