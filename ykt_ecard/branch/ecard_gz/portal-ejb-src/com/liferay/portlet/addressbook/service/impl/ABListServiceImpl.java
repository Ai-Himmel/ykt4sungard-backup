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

package com.liferay.portlet.addressbook.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.util.RecipientComparator;
import com.liferay.portlet.addressbook.ListNameException;
import com.liferay.portlet.addressbook.model.ABList;
import com.liferay.portlet.addressbook.service.persistence.ABListUtil;
import com.liferay.portlet.addressbook.service.spring.ABListLocalServiceUtil;
import com.liferay.portlet.addressbook.service.spring.ABListService;
import com.liferay.util.Validator;

import java.util.Collections;
import java.util.List;

/**
 * <a href="ABListServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class ABListServiceImpl extends PrincipalBean implements ABListService {

	// Business methods

	public ABList addList(String name)
		throws PortalException, SystemException {

		if (Validator.isNull(name)) {
			throw new ListNameException();
		}

		String listId = Long.toString(CounterServiceUtil.increment(
			ABList.class.getName()));

		ABList list = ABListUtil.create(listId);

		list.setUserId(getUserId());
		list.setName(name);

		ABListUtil.update(list);

		return list;
	}

	public void deleteList(String listId)
		throws PortalException, SystemException {

		ABList list = ABListUtil.findByPrimaryKey(listId);

		if (!list.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		ABListLocalServiceUtil.deleteList(listId);
	}

	public List getContacts(String listId)
		throws PortalException, SystemException {

		ABList list = ABListUtil.findByPrimaryKey(listId);

		if (!list.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		List contacts = ABListUtil.getABContacts(listId);

		Collections.sort(contacts, new RecipientComparator());

		return contacts;
	}

	public ABList getList(String listId)
		throws PortalException, SystemException {

		ABList list = ABListUtil.findByPrimaryKey(listId);

		if (!list.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		return list;
	}

	public List getLists() throws PortalException, SystemException {
		return ABListUtil.findByUserId(getUserId());
	}

	public int getListsSize() throws PortalException, SystemException {
		return ABListUtil.countByUserId(getUserId());
	}

	public void setContacts(String listId, List contacts)
		throws PortalException, SystemException {

		ABList list = ABListUtil.findByPrimaryKey(listId);

		if (!list.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		ABListUtil.setABContacts(listId, contacts);
	}

	public ABList updateList(String listId, String name)
		throws PortalException, SystemException {

		if (Validator.isNull(name)) {
			throw new ListNameException();
		}

		ABList list = ABListUtil.findByPrimaryKey(listId);

		if (!list.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		list.setName(name);

		ABListUtil.update(list);

		return list;
	}

}