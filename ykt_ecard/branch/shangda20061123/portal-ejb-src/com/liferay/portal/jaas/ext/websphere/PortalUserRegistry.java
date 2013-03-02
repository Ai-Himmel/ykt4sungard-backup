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

package com.liferay.portal.jaas.ext.websphere;

import com.ibm.websphere.security.CertificateMapFailedException;
import com.ibm.websphere.security.CertificateMapNotSupportedException;
import com.ibm.websphere.security.CustomRegistryException;
import com.ibm.websphere.security.EntryNotFoundException;
import com.ibm.websphere.security.NotImplementedException;
import com.ibm.websphere.security.PasswordCheckFailedException;
import com.ibm.websphere.security.Result;
import com.ibm.websphere.security.UserRegistry;
import com.ibm.websphere.security.cred.WSCredential;

import com.liferay.portal.util.Constants;
import com.liferay.util.dao.DataAccess;

import java.rmi.RemoteException;

import java.security.cert.X509Certificate;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

/**
 * <a href="PortalUserRegistry.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class PortalUserRegistry implements UserRegistry {

	public void initialize(Properties props)
		throws CustomRegistryException, RemoteException {
	}

	public String checkPassword(String userId, String password)
		throws CustomRegistryException, PasswordCheckFailedException,
			   RemoteException {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);
			System.out.println("get connection");
			StringBuffer query = new StringBuffer();
			query.append("SELECT password_ ");
			query.append("FROM ykt_web.User_ WHERE ");
			query.append("userId = ?");
			System.out.println("sql prepared!");
			ps = con.prepareStatement(query.toString());

			ps.setString(1, userId);
			System.out.println("start execute query!");
			rs = ps.executeQuery();

			if (rs.next()) {
				if (!password.equals(rs.getString(1))) {
					throw new PasswordCheckFailedException(
						"Passwords do not match");
				}
			}
			else {
				throw new PasswordCheckFailedException(
					"User with the id " + userId + " does not exist");
			}
			System.out.println("end");
		}
		catch (Exception e) {
			throw new CustomRegistryException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return userId;
	}

	public String mapCertificate(X509Certificate[] certs)
		throws CertificateMapFailedException,
			   CertificateMapNotSupportedException, CustomRegistryException,
			   RemoteException {

		if ((certs == null) || (certs.length < 1)) {
			throw new CertificateMapFailedException();
		}

		String name = null;

		try {
			name = certs[0].getSubjectDN().getName();
		}
		catch(Exception e) {
			throw new CertificateMapNotSupportedException(e.getMessage());
		}

		if (!isValidUser(name)) {
			throw new CertificateMapFailedException(name);
		}

		return name;
	}

	public String getRealm() throws CustomRegistryException, RemoteException {
		return Constants.REALM_NAME;
	}

	public Result getUsers(String pattern, int limit)
		throws CustomRegistryException, RemoteException {

		return new Result();
	}

	public String getUserDisplayName(String userId)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return userId;
	}

	public String getUniqueUserId(String userId)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return userId;
	}

	public String getUserSecurityName(String userId)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return userId;
	}

	public boolean isValidUser(String userId)
		throws CustomRegistryException, RemoteException {

		return true;
	}

	public Result getGroups(String pattern, int limit)
		throws CustomRegistryException, RemoteException {

		return new Result();
	}

	public String getGroupDisplayName(String groupSecurityName)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return groupSecurityName;
	}

	public String getUniqueGroupId(String groupSecurityName)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return groupSecurityName;
	}

	public List getUniqueGroupIds(String userId)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return new ArrayList();
	}

	public String getGroupSecurityName(String uniqueGroupId)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return uniqueGroupId;
	}

	public boolean isValidGroup(String groupSecurityName)
		throws CustomRegistryException, RemoteException {

		return true;
	}

	public List getGroupsForUser(String userId)
		throws CustomRegistryException, EntryNotFoundException,
			   RemoteException {

		return new ArrayList();
	}

	public Result getUsersForGroup(String groupSecurityName, int limit)
		throws CustomRegistryException, EntryNotFoundException,
			   NotImplementedException, RemoteException {

		throw new NotImplementedException();
	}

	public WSCredential createCredential(String userId)
		throws CustomRegistryException, EntryNotFoundException,
			   NotImplementedException, RemoteException {

		throw new NotImplementedException();
	}

}