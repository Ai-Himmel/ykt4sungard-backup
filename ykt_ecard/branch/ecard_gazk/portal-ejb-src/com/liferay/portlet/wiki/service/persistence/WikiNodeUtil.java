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
 * <a href="WikiNodeUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiNodeUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.wiki.model.WikiNode"),
			"com.liferay.portlet.wiki.service.persistence.WikiNodePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.wiki.model.WikiNode"));

	public static com.liferay.portlet.wiki.model.WikiNode create(
		java.lang.String nodeId) {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(nodeId);
	}

	public static com.liferay.portlet.wiki.model.WikiNode remove(
		java.lang.String nodeId)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(nodeId));
		}

		com.liferay.portlet.wiki.model.WikiNode wikiNode = persistence.remove(nodeId);

		if (listener != null) {
			listener.onAfterRemove(wikiNode);
		}

		return wikiNode;
	}

	public static com.liferay.portlet.wiki.model.WikiNode update(
		com.liferay.portlet.wiki.model.WikiNode wikiNode)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = wikiNode.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(wikiNode);
			}
			else {
				listener.onBeforeUpdate(wikiNode);
			}
		}

		wikiNode = persistence.update(wikiNode);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(wikiNode);
			}
			else {
				listener.onAfterUpdate(wikiNode);
			}
		}

		return wikiNode;
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByPrimaryKey(
		java.lang.String nodeId)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(nodeId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode[] findByCompanyId_PrevAndNext(
		java.lang.String nodeId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(nodeId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode[] findByUserId_PrevAndNext(
		java.lang.String nodeId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(nodeId, userId, obc);
	}

	public static java.util.List findByC_S(java.lang.String companyId,
		boolean sharing) throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, sharing);
	}

	public static java.util.List findByC_S(java.lang.String companyId,
		boolean sharing, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, sharing, begin, end);
	}

	public static java.util.List findByC_S(java.lang.String companyId,
		boolean sharing, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, sharing, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByC_S_First(
		java.lang.String companyId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S_First(companyId, sharing, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByC_S_Last(
		java.lang.String companyId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S_Last(companyId, sharing, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode[] findByC_S_PrevAndNext(
		java.lang.String nodeId, java.lang.String companyId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S_PrevAndNext(nodeId, companyId, sharing, obc);
	}

	public static java.util.List findByU_S(java.lang.String userId,
		boolean sharing) throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, sharing);
	}

	public static java.util.List findByU_S(java.lang.String userId,
		boolean sharing, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, sharing, begin, end);
	}

	public static java.util.List findByU_S(java.lang.String userId,
		boolean sharing, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, sharing, begin, end, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByU_S_First(
		java.lang.String userId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_First(userId, sharing, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode findByU_S_Last(
		java.lang.String userId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_Last(userId, sharing, obc);
	}

	public static com.liferay.portlet.wiki.model.WikiNode[] findByU_S_PrevAndNext(
		java.lang.String nodeId, java.lang.String userId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.wiki.NoSuchNodeException, 
			com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_PrevAndNext(nodeId, userId, sharing, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByC_S(java.lang.String companyId, boolean sharing)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_S(companyId, sharing);
	}

	public static void removeByU_S(java.lang.String userId, boolean sharing)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_S(userId, sharing);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByC_S(java.lang.String companyId, boolean sharing)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_S(companyId, sharing);
	}

	public static int countByU_S(java.lang.String userId, boolean sharing)
		throws com.liferay.portal.SystemException {
		WikiNodePersistence persistence = (WikiNodePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_S(userId, sharing);
	}

	private static final Log _log = LogFactory.getLog(WikiNodeUtil.class);
}