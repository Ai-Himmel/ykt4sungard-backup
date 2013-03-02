package org.king.check.dao;

import org.king.check.common.ec.DBPageLimit;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-26
 */
public interface CheckrecordDAO extends DAO {
    public void findDeviceCheckByPage(DBPageLimit page, MyQuery myQuery);

    public void findCheckDetailByPage(DBPageLimit page, MyQuery myQuery);

    public List findCheckDetail(String query);

}
