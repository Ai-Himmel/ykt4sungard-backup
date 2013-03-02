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
 * <a href="DLFileVersionFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class DLFileVersionFinder {

	/**
	 * Find all DLFileVersionPKs associated with the specified company id and
	 * file name.
	 *
	 * @return		a list of all DLFileVersionPKs associated with the specified
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
			query.append("SELECT fileName, version ");
			query.append("FROM DLFileVersion WHERE ");
			query.append("companyId = ? AND repositoryId = ? AND ");
			query.append("fileName LIKE ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, companyId);
			ps.setString(2, repositoryId);
			ps.setString(3, fileName);

			rs = ps.executeQuery();

			while (rs.next()) {
				DLFileVersionPK pk = new DLFileVersionPK(
					companyId, repositoryId, rs.getString(1), rs.getDouble(2));

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

}