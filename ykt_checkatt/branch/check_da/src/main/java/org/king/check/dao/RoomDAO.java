package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TRoom;
import org.king.check.domain.TRoomdevice;
import org.king.check.domain.TTerm;
import org.king.framework.dao.DAO;

public interface RoomDAO extends DAO{
	
	public void  save(TRoom Troom);
	
	public void  update(TRoom Troom);
	
	public void  delete(TRoom Troom);
	
	public List find(String query);
	
	public TRoom get(Serializable id);
	
	public void delete(TRoomdevice roomdevice);
	
	public void save(TRoomdevice roomdevice);
	
}
