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

package com.liferay.portal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.service.MembershipRequestServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="MembershipRequestServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portal.service.MembershipRequestServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portal.model.MembershipRequestSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.MembershipRequest</code>,
 * that is translated to a <code>com.liferay.portal.model.MembershipRequestSoap</code>.
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
 * @see com.liferay.portal.service.MembershipRequestServiceUtil
 * @see com.liferay.portal.service.http.MembershipRequestServiceHttp
 * @see com.liferay.portal.service.model.MembershipRequestSoap
 *
 */
public class MembershipRequestServiceSoap {
	public static com.liferay.portal.model.MembershipRequestSoap addMembershipRequest(
		long groupId, java.lang.String comments) throws RemoteException {
		try {
			com.liferay.portal.model.MembershipRequest returnValue = MembershipRequestServiceUtil.addMembershipRequest(groupId,
					comments);

			return com.liferay.portal.model.MembershipRequestSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteMembershipRequests(long groupId, int statusId)
		throws RemoteException {
		try {
			MembershipRequestServiceUtil.deleteMembershipRequests(groupId,
				statusId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.MembershipRequestSoap getMembershipRequest(
		long membershipRequestId) throws RemoteException {
		try {
			com.liferay.portal.model.MembershipRequest returnValue = MembershipRequestServiceUtil.getMembershipRequest(membershipRequestId);

			return com.liferay.portal.model.MembershipRequestSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void updateStatus(long membershipRequestId,
		java.lang.String reviewComments, int statusId)
		throws RemoteException {
		try {
			MembershipRequestServiceUtil.updateStatus(membershipRequestId,
				reviewComments, statusId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(MembershipRequestServiceSoap.class);
}