package org.king.check.dao;

import org.king.check.domain.TSyncLog;
import org.king.framework.dao.MyQuery;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public interface SyncLogDAO {
    public void save(TSyncLog entiry);

    public void update(TSyncLog entiry);

    public TSyncLog get(Serializable id);

    public List find(String query);

    public List find(MyQuery myQuery);

    public void delete(TSyncLog entity);
}
