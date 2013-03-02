package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.custype.CustomerTypePersistence;


public class CustomerTypeUtil {
	
	
	/**
	 * Description:返回客户类别名
	 * @param id
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static String getCustomerTypeName(Integer id) throws PortalException {
		return getPersistence().getCustomertype(id).getCusttypename();
	}
	
	
	public static CustomerTypePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CustomerTypePersistence persistence) {
		_persistence = persistence;
	}

	private static CustomerTypeUtil _getUtil() {
		if (_util == null) {
			_util = (CustomerTypeUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CustomerTypePersistence.class.getName();
	private static CustomerTypeUtil _util;
	private CustomerTypePersistence _persistence;

}
