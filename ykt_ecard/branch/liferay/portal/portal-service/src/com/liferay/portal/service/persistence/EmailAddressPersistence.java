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

package com.liferay.portal.service.persistence;

/**
 * <a href="EmailAddressPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface EmailAddressPersistence {
	public com.liferay.portal.model.EmailAddress create(long emailAddressId);

	public com.liferay.portal.model.EmailAddress remove(long emailAddressId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress remove(
		com.liferay.portal.model.EmailAddress emailAddress)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress update(
		com.liferay.portal.model.EmailAddress emailAddress)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress update(
		com.liferay.portal.model.EmailAddress emailAddress, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress updateImpl(
		com.liferay.portal.model.EmailAddress emailAddress, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress findByPrimaryKey(
		long emailAddressId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress fetchByPrimaryKey(
		long emailAddressId) throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress[] findByCompanyId_PrevAndNext(
		long emailAddressId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress[] findByUserId_PrevAndNext(
		long emailAddressId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public java.util.List findByC_C(long companyId, long classNameId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByC_C(long companyId, long classNameId,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findByC_C(long companyId, long classNameId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress findByC_C_First(
		long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress findByC_C_Last(
		long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress[] findByC_C_PrevAndNext(
		long emailAddressId, long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public java.util.List findByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException;

	public java.util.List findByC_C_C(long companyId, long classNameId,
		long classPK, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByC_C_C(long companyId, long classNameId,
		long classPK, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress findByC_C_C_First(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress findByC_C_C_Last(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress[] findByC_C_C_PrevAndNext(
		long emailAddressId, long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public java.util.List findByC_C_C_P(long companyId, long classNameId,
		long classPK, boolean primary)
		throws com.liferay.portal.SystemException;

	public java.util.List findByC_C_C_P(long companyId, long classNameId,
		long classPK, boolean primary, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByC_C_C_P(long companyId, long classNameId,
		long classPK, boolean primary, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.EmailAddress findByC_C_C_P_First(
		long companyId, long classNameId, long classPK, boolean primary,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress findByC_C_C_P_Last(
		long companyId, long classNameId, long classPK, boolean primary,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public com.liferay.portal.model.EmailAddress[] findByC_C_C_P_PrevAndNext(
		long emailAddressId, long companyId, long classNameId, long classPK,
		boolean primary, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchEmailAddressException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public void removeByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public void removeByC_C(long companyId, long classNameId)
		throws com.liferay.portal.SystemException;

	public void removeByC_C_C(long companyId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException;

	public void removeByC_C_C_P(long companyId, long classNameId, long classPK,
		boolean primary) throws com.liferay.portal.SystemException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public int countByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public int countByC_C(long companyId, long classNameId)
		throws com.liferay.portal.SystemException;

	public int countByC_C_C(long companyId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException;

	public int countByC_C_C_P(long companyId, long classNameId, long classPK,
		boolean primary) throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}