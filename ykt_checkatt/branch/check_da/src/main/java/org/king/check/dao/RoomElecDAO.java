package org.king.check.dao;

import org.king.check.domain.TRoomElec;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-11-2
 */
public interface RoomElecDAO {
    public List findRoomElec(String  query);

	public TRoomElec getRoomElec(Serializable id);

    public void updateRoomElec(TRoomElec entity);
}
