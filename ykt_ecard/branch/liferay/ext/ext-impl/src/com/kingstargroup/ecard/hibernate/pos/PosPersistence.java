package com.kingstargroup.ecard.hibernate.pos;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Query;
import org.hibernate.Session;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.liferay.portal.service.persistence.BasePersistence;

public class PosPersistence extends BasePersistence {
	private static final Log _log = LogFactory.getLog(PosPersistence.class);
	
	/**
	 * 得到部门信息
	 */
	public List getDepartments() {
		Session session = openSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("from TDept");
		try {
			Query sqlquery = session.createQuery(sqlStr.toString());
			List list = sqlquery.list();
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					TDept m1 = (TDept) o1;
					TDept m2 = (TDept) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String deptName1 = (String) m1.getDeptname();
					String deptName2 = (String) m2.getDeptname();
					CollationKey c1 = col.getCollationKey(deptName1);
					CollationKey c2 = col.getCollationKey(deptName2);
					return c1.compareTo(c2);
				}
			};
			Collections.sort(list, comp1);
			return list;
		} catch (Exception e) {
			e.printStackTrace();
			_log.error(e);
			return null;
		}
	}

}
