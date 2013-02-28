package org.king.security.service;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.service.Service;

public interface TransService extends Service {

	public void getEayTransdtlList(DBPaginatedList page, Object[] conditions);

}
