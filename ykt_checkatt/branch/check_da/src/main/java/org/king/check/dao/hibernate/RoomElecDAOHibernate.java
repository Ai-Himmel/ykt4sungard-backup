package org.king.check.dao.hibernate;

import org.king.check.dao.RoomElecDAO;
import org.king.check.domain.TRoomElec;
import org.king.framework.dao.BaseDAO;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-11-2
 */
public class RoomElecDAOHibernate implements RoomElecDAO {
    private BaseDAO baseDAO;

    public BaseDAO getBaseDAO() {
        return baseDAO;
    }

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List findRoomElec(String query) {
        return baseDAO.findEntity(query);
    }

    public TRoomElec getRoomElec(Serializable id) {
        return (TRoomElec) baseDAO.getEntity(TRoomElec.class, id);
    }

    public void updateRoomElec(TRoomElec entity) {
        baseDAO.updateEntity(entity);
    }
}
