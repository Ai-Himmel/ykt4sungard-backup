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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchListTypeException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.ClassName;
import com.liferay.portal.model.ListType;
import com.liferay.portal.service.base.ListTypeServiceBaseImpl;

import java.util.List;

/**
 * <a href="ListTypeServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ListTypeServiceImpl extends ListTypeServiceBaseImpl {

	public ListType getListType(int listTypeId)
		throws PortalException, SystemException {

		return listTypePersistence.findByPrimaryKey(listTypeId);
	}

	public List getListTypes(String type) throws SystemException {
		return listTypePersistence.findByType(type);
	}

	public void validate(int listTypeId, String type)
		throws PortalException, SystemException {

		ListType listType = listTypePersistence.findByPrimaryKey(listTypeId);

		if (!listType.getType().equals(type)) {
			NoSuchListTypeException nslte = new NoSuchListTypeException();

			nslte.setType(type);

			throw nslte;
		}
	}

	public void validate(int listTypeId, long classNameId, String type)
		throws PortalException, SystemException {

		ClassName className = classNameLocalService.getClassName(classNameId);

		validate(listTypeId, className.getValue() + type);
	}

}