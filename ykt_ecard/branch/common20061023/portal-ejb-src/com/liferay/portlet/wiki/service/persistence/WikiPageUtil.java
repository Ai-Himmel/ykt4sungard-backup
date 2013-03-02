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

package com.liferay.portlet.wiki.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="WikiPageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiPageUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.wiki.model.WikiPage"),
			"com.liferay.portlet.wiki.service.persistence.WikiPagePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.wiki.model.WikiPage"));

	public static com.liferay.portlet.wiki.model.WikiPage create(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK) {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(wikiPagePK);
	}

	public static com.liferay.portlet.wiki.model.WikiPage remove(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(wikiPagePK));
		}

		com.liferay.portlet.wiki.model.WikiPage wikiPage = persistence.remove(wikiPagePK);

		if (listener != null) {
			listener.onAfterRemove(wikiPage);
		}

		return wikiPage;
	}

	public static com.liferay.portlet.wiki.model.WikiPage update(
		com.liferay.portlet.wiki.model.WikiPage wikiPage)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = wikiPage.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(wikiPage);
			}
			else {
				listener.onBeforeUpdate(wikiPage);
			}
		}

		wikiPage = persistence.update(wikiPage);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(wikiPage);
			}
			else {
				listener.onAfterUpdate(wikiPage);
			}
		}

		return wikiPage;
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByPrimaryKey(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(wikiPagePK);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage[] findByCompanyId_PrevAndNext(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(wikiPagePK, companyId,
			obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage[] findByUserId_PrevAndNext(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(wikiPagePK, userId, obc);
	}

	public static java.util.List findByNodeId(java.lang.String nodeId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByNodeId(nodeId);
	}

	public static java.util.List findByNodeId(java.lang.String nodeId,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByNodeId(nodeId, begin, end);
	}

	public static java.util.List findByNodeId(java.lang.String nodeId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByNodeId(nodeId, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByNodeId_First(
		java.lang.String nodeId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByNodeId_First(nodeId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByNodeId_Last(
		java.lang.String nodeId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByNodeId_Last(nodeId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage[] findByNodeId_PrevAndNext(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK,
		java.lang.String nodeId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByNodeId_PrevAndNext(wikiPagePK, nodeId, obc);
	}

	public static java.util.List findByN_T(java.lang.String nodeId,
		java.lang.String title) throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T(nodeId, title);
	}

	public static java.util.List findByN_T(java.lang.String nodeId,
		java.lang.String title, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T(nodeId, title, begin, end);
	}

	public static java.util.List findByN_T(java.lang.String nodeId,
		java.lang.String title, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T(nodeId, title, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByN_T_First(
		java.lang.String nodeId, java.lang.String title,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_First(nodeId, title, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByN_T_Last(
		java.lang.String nodeId, java.lang.String title,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_Last(nodeId, title, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage[] findByN_T_PrevAndNext(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK,
		java.lang.String nodeId, java.lang.String title,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_PrevAndNext(wikiPagePK, nodeId, title, obc);
	}

	public static java.util.List findByN_T_H(java.lang.String nodeId,
		java.lang.String title, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_H(nodeId, title, head);
	}

	public static java.util.List findByN_T_H(java.lang.String nodeId,
		java.lang.String title, boolean head, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_H(nodeId, title, head, begin, end);
	}

	public static java.util.List findByN_T_H(java.lang.String nodeId,
		java.lang.String title, boolean head, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_H(nodeId, title, head, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByN_T_H_First(
		java.lang.String nodeId, java.lang.String title, boolean head,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_H_First(nodeId, title, head, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByN_T_H_Last(
		java.lang.String nodeId, java.lang.String title, boolean head,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_H_Last(nodeId, title, head, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage[] findByN_T_H_PrevAndNext(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK,
		java.lang.String nodeId, java.lang.String title, boolean head,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_T_H_PrevAndNext(wikiPagePK, nodeId, title,
			head, obc);
	}

	public static java.util.List findByN_H(java.lang.String nodeId, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_H(nodeId, head);
	}

	public static java.util.List findByN_H(java.lang.String nodeId,
		boolean head, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_H(nodeId, head, begin, end);
	}

	public static java.util.List findByN_H(java.lang.String nodeId,
		boolean head, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_H(nodeId, head, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByN_H_First(
		java.lang.String nodeId, boolean head,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_H_First(nodeId, head, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByN_H_Last(
		java.lang.String nodeId, boolean head,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_H_Last(nodeId, head, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiPage[] findByN_H_PrevAndNext(
		com.liferay.portlet.wiki.service.persistence.WikiPagePK wikiPagePK,
		java.lang.String nodeId, boolean head,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchPageException, 
			com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByN_H_PrevAndNext(wikiPagePK, nodeId, head, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByNodeId(java.lang.String nodeId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByNodeId(nodeId);
	}

	public static void removeByN_T(java.lang.String nodeId,
		java.lang.String title) throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByN_T(nodeId, title);
	}

	public static void removeByN_T_H(java.lang.String nodeId,
		java.lang.String title, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByN_T_H(nodeId, title, head);
	}

	public static void removeByN_H(java.lang.String nodeId, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByN_H(nodeId, head);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByNodeId(java.lang.String nodeId)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByNodeId(nodeId);
	}

	public static int countByN_T(java.lang.String nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByN_T(nodeId, title);
	}

	public static int countByN_T_H(java.lang.String nodeId,
		java.lang.String title, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByN_T_H(nodeId, title, head);
	}

	public static int countByN_H(java.lang.String nodeId, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPagePersistence persistence = (WikiPagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByN_H(nodeId, head);
	}

	private static final Log _log = LogFactory.getLog(WikiPageUtil.class);
}