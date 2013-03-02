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

package com.liferay.portlet.network.service.persistence;

import com.kingstargroup.ecard.util.DBUtil;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.network.model.NetworkAddress;
import com.liferay.util.SystemProperties;
import com.liferay.util.dao.DataAccess;
import com.liferay.util.lang.FastStringBuffer;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="NetworkAddressFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class NetworkAddressFinder {

	/**
	 * Find all NetworkAddresses associated with the specified interval and
	 * activeness.
	 *
	 * @return		a list of all NetworkAddresses associated with the specified
	 *				interval and activeness
	 */
	public static List findByI_A(long interval, boolean active)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			/*
			 * Support DB2 Schema Name 
			 * Xiao Qi
			 * 2005-08-30
			 */
			query.append("SELECT addressId ");
			query.append("FROM ")
				.append(DBUtil.getSchemaName())
				.append("NetworkAddress WHERE ");
			query.append("interval_ = ? AND active_ = ?");

			ps = con.prepareStatement(query.toString());

			ps.setLong(1, interval);
			/*
			 * solve the boolean problem(db field format is char(1))
			 
			ps.setBoolean(2, active);
			*/
			ps.setString(2, DBUtil.bool2string(active));
			rs = ps.executeQuery();

			while (rs.next()) {
				NetworkAddress address =
					NetworkAddressUtil.findByPrimaryKey(rs.getString(1));

				list.add(address);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return list;
	}
}