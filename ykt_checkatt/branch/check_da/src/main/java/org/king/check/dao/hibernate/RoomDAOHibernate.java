package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.check.dao.RoomDAO;
import org.king.check.domain.TRoom;
import org.king.check.domain.TRoomdevice;
import org.king.framework.dao.BaseDAO;

public class RoomDAOHibernate implements RoomDAO{
	
	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
    public void  save(TRoom Troom){
    	baseDAO.saveEntity(Troom);
    }
	
	public void  update(TRoom Troom){
		baseDAO.updateEntity(Troom);
	}
	
	public void  delete(TRoom Troom){
		baseDAO.removeEntity(Troom);
	}
	
	public void save(TRoomdevice Troomdevice){
		baseDAO.saveEntity(Troomdevice);
	}
	
	public void delete(TRoomdevice Troomdevice){
		baseDAO.removeEntity(Troomdevice);
	}

	public List find(String query) {	
		return baseDAO.findEntity(query);
	}

	public TRoom get(Serializable id) {
		return (TRoom)baseDAO.getEntity(TRoom.class, id);
	}

}
