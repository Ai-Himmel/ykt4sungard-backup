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
 * <a href="PasswordPolicyRelPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface PasswordPolicyRelPersistence {
	public com.liferay.portal.model.PasswordPolicyRel create(
		long passwordPolicyRelId);

	public com.liferay.portal.model.PasswordPolicyRel remove(
		long passwordPolicyRelId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordPolicyRelException;

	public com.liferay.portal.model.PasswordPolicyRel remove(
		com.liferay.portal.model.PasswordPolicyRel passwordPolicyRel)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.PasswordPolicyRel update(
		com.liferay.portal.model.PasswordPolicyRel passwordPolicyRel)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.PasswordPolicyRel update(
		com.liferay.portal.model.PasswordPolicyRel passwordPolicyRel,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.PasswordPolicyRel updateImpl(
		com.liferay.portal.model.PasswordPolicyRel passwordPolicyRel,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.PasswordPolicyRel findByPrimaryKey(
		long passwordPolicyRelId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordPolicyRelException;

	public com.liferay.portal.model.PasswordPolicyRel fetchByPrimaryKey(
		long passwordPolicyRelId) throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.PasswordPolicyRel findByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordPolicyRelException;

	public com.liferay.portal.model.PasswordPolicyRel fetchByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.PasswordPolicyRel findByP_C_C(
		long passwordPolicyId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordPolicyRelException;

	public com.liferay.portal.model.PasswordPolicyRel fetchByP_C_C(
		long passwordPolicyId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException;

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

	public void removeByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordPolicyRelException;

	public void removeByP_C_C(long passwordPolicyId, long classNameId,
		long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordPolicyRelException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException;

	public int countByP_C_C(long passwordPolicyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}