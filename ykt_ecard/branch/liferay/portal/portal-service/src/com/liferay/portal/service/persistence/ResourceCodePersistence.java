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
 * <a href="ResourceCodePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface ResourceCodePersistence {
	public com.liferay.portal.model.ResourceCode create(long codeId);

	public com.liferay.portal.model.ResourceCode remove(long codeId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode remove(
		com.liferay.portal.model.ResourceCode resourceCode)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.ResourceCode update(
		com.liferay.portal.model.ResourceCode resourceCode)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.ResourceCode update(
		com.liferay.portal.model.ResourceCode resourceCode, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.ResourceCode updateImpl(
		com.liferay.portal.model.ResourceCode resourceCode, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.ResourceCode findByPrimaryKey(long codeId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode fetchByPrimaryKey(long codeId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.ResourceCode findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode[] findByCompanyId_PrevAndNext(
		long codeId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public java.util.List findByName(java.lang.String name)
		throws com.liferay.portal.SystemException;

	public java.util.List findByName(java.lang.String name, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByName(java.lang.String name, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.ResourceCode findByName_First(
		java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode findByName_Last(
		java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode[] findByName_PrevAndNext(
		long codeId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode findByC_N_S(long companyId,
		java.lang.String name, int scope)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public com.liferay.portal.model.ResourceCode fetchByC_N_S(long companyId,
		java.lang.String name, int scope)
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

	public void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public void removeByName(java.lang.String name)
		throws com.liferay.portal.SystemException;

	public void removeByC_N_S(long companyId, java.lang.String name, int scope)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceCodeException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public int countByName(java.lang.String name)
		throws com.liferay.portal.SystemException;

	public int countByC_N_S(long companyId, java.lang.String name, int scope)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}