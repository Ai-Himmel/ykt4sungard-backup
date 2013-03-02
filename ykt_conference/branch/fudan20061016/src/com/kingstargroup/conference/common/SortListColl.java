package com.kingstargroup.conference.common;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Locale;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;

/**
 * 实现下拉列表框排序
 * 
 * @author Administrator
 * 
 */

public class SortListColl implements Comparator {

	public int compare(Object o1, Object o2) {
		if ((o1 instanceof HashMap) && (o2 instanceof HashMap)) {
			HashMap a = (HashMap) o1;
			HashMap b = (HashMap) o2;
			Collator col = Collator.getInstance(Locale.CHINA);
			String a1 = a.get("pym").toString();
			String b1 = b.get("pym").toString();
			CollationKey c1 = col.getCollationKey(a1);
			CollationKey c2 = col.getCollationKey(b1);
			if (null == a1 && null == b1) {
				return 0;
			} else if (null == a1) {
				return -1;
			} else if (null == b1) {
				return 1;
			} else {
				return c1.compareTo(c2);
			}
		} else {
			return 0;
		}

	}

}
