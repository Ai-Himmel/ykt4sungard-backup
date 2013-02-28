package org.king.security.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.DAO;

public interface VTransdtlDAO extends DAO {

	public void findByPage(DBPaginatedList page, QueryTranslate queryTranslate);

}
