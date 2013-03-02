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

package com.liferay.portlet.documentlibrary.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.util.Constants;
import com.liferay.util.dao.DataAccess;
import com.liferay.util.lang.FastStringBuffer;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="DLFileRankFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class DLFileRankFinder {

	/**
	 * Count all DLFileRanks associated with the specified group id and user id.
	 *
	 * @return		the count of all DLFileRanks associated with the specified
	 *				group id and user id
	 */
	public static int countByG_U(String groupId, String userId)
		throws SystemException {

		int count = 0;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append("FROM ");
			query.append("DLFileRank, DLRepository ");
			query.append("WHERE ");
			query.append("DLFileRank.repositoryId = DLRepository.repositoryId AND ");
			query.append("DLRepository.groupId = ? AND DLFileRank.userId = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, groupId);
			ps.setString(2, userId);

			rs = ps.executeQuery();

			while (rs.next()) {
				count += rs.getInt(1);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return count;
	}

	/**
	 * Find all DLFileRankPKs associated with the specified company id and
	 * file name.
	 *
	 * @return		a list of all DLFileRankPKs associated with the specified
	 *				company id and file name
	 */
	public static List findByFileName(
			String companyId, String repositoryId, String fileName)
		throws SystemException {

		if (!fileName.endsWith("%")) {
			fileName += "%";
		}

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT userId, fileName ");
			query.append("FROM DLFileRank WHERE ");
			query.append("companyId = ? AND repositoryId = ? AND ");
			query.append("fileName LIKE ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, companyId);
			ps.setString(2, repositoryId);
			ps.setString(3, fileName);

			rs = ps.executeQuery();

			while (rs.next()) {
				DLFileRankPK pk = new DLFileRankPK(
					companyId, rs.getString(1), repositoryId, rs.getString(2));

				list.add(pk);
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

	/**
	 * Find all DLFileRanks associated with the specified group id and user id.
	 *
	 * @return		a list of all DLFileRanks associated with the group id and
	 *				user id
	 */
	public static List findByG_U(String groupId, String userId)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT ");
			query.append("DLFileRank.companyId, DLFileRank.repositoryId, ");
			query.append("DLFileRank.fileName ");
			query.append("FROM ");
			query.append("DLFileRank, DLRepository ");
			query.append("WHERE ");
			query.append("DLFileRank.repositoryId = DLRepository.repositoryId AND ");
			query.append("DLRepository.groupId = ? AND DLFileRank.userId = ? ");
			query.append("ORDER BY DLFileRank.createDate DESC");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, groupId);
			ps.setString(2, userId);

			rs = ps.executeQuery();

			while (rs.next()) {
				DLFileRankPK pk = new DLFileRankPK(
					rs.getString(1), userId, rs.getString(2), rs.getString(3));

				list.add(DLFileRankUtil.findByPrimaryKey(pk));
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