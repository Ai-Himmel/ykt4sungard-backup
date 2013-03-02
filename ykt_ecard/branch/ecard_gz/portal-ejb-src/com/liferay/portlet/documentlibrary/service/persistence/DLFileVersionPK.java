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

import com.liferay.util.StringPool;
import com.liferay.util.lang.FastStringBuffer;

import java.io.Serializable;

/**
 * <a href="DLFileVersionPK.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileVersionPK implements Comparable, Serializable {
	public String companyId;
	public String repositoryId;
	public String fileName;
	public double version;

	public DLFileVersionPK() {
	}

	public DLFileVersionPK(String companyId, String repositoryId,
		String fileName, double version) {
		this.companyId = companyId;
		this.repositoryId = repositoryId;
		this.fileName = fileName;
		this.version = version;
	}

	public String getCompanyId() {
		return companyId;
	}

	public void setCompanyId(String companyId) {
		this.companyId = companyId;
	}

	public String getRepositoryId() {
		return repositoryId;
	}

	public void setRepositoryId(String repositoryId) {
		this.repositoryId = repositoryId;
	}

	public String getFileName() {
		return fileName;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}

	public double getVersion() {
		return version;
	}

	public void setVersion(double version) {
		this.version = version;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileVersionPK pk = (DLFileVersionPK)obj;
		int value = 0;
		value = companyId.compareTo(pk.companyId);

		if (value != 0) {
			return value;
		}

		value = repositoryId.compareTo(pk.repositoryId);

		if (value != 0) {
			return value;
		}

		value = fileName.compareTo(pk.fileName);

		if (value != 0) {
			return value;
		}

		if (version < pk.version) {
			value = -1;
		}
		else if (version > pk.version) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		DLFileVersionPK pk = null;

		try {
			pk = (DLFileVersionPK)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		if ((companyId.equals(pk.companyId)) &&
				(repositoryId.equals(pk.repositoryId)) &&
				(fileName.equals(pk.fileName)) && (version == pk.version)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (companyId + repositoryId + fileName + version).hashCode();
	}

	public String toString() {
		FastStringBuffer sb = new FastStringBuffer();
		sb.append(StringPool.OPEN_CURLY_BRACE);
		sb.append("companyId");
		sb.append(StringPool.EQUAL);
		sb.append(companyId);
		sb.append(StringPool.COMMA);
		sb.append(StringPool.SPACE);
		sb.append("repositoryId");
		sb.append(StringPool.EQUAL);
		sb.append(repositoryId);
		sb.append(StringPool.COMMA);
		sb.append(StringPool.SPACE);
		sb.append("fileName");
		sb.append(StringPool.EQUAL);
		sb.append(fileName);
		sb.append(StringPool.COMMA);
		sb.append(StringPool.SPACE);
		sb.append("version");
		sb.append(StringPool.EQUAL);
		sb.append(version);
		sb.append(StringPool.CLOSE_CURLY_BRACE);

		return sb.toString();
	}
}