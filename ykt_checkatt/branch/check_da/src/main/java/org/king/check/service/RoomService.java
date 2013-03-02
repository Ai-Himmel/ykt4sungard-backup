package org.king.check.service;

import java.util.List;

import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.struts.action.DynaActionForm;
import org.king.check.domain.TRoom;
import org.king.check.domain.TRoomdevice;

public interface RoomService {
	
	public void  saveRoom(TRoom room)throws Exception;
	
	public void  updateRoom(TRoom room)throws Exception;
	
	public void  deleteRoom(TRoom room)throws Exception;
	
	public List  findRoom(TRoom room) throws Exception;
	
	public TRoom findOneRoom(String  areaName,String build ,String roomName)throws Exception;
	
	public String  saveRoomImp(HSSFSheet sheet)throws Exception;
	
	public TRoom  getRoom(String id)throws Exception;
	
	public void  saveRoomDevice(TRoomdevice  roomdevice)throws Exception;
	
	public void  deleteRoomDevice(TRoomdevice roomdevice)throws Exception;
	
	public List  findRoomDevice(TRoomdevice roomdevice)throws Exception;
	
	public String ifRoomCanImp(HSSFSheet  Sheet )throws Exception;
	
	/**
	 * Method name:getClassDevList
	 * Description:  ��ѯ�����豸�󶨹�ϵ
	 * Return: List
	 * @param shoolarea
	 * @param build
	 * @param roomName
	 * @return
	 * @throws Exception
	 */
	public List getClassDevList(String shoolarea,String build,String roomname)throws Exception;
	
	/**
	 * Method name:getAreaList
	 * Description: У���б�  
	 * @author jackey
	 * CreateDate 2010-4-16
	 * Return: List
	 * @return
	 * @throws Exception
	 */
	public List getAreaList()throws Exception;
	
	/**
	 * Method name:getBuildList
	 * Description: ¥���б�   
	 * @author jackey
	 * CreateDate 2010-4-16
	 * Return: List
	 * @param schoolarea
	 * @return
	 * @throws Exception
	 */
	public List getBuildList(String schoolarea)throws Exception;
	
	/**
	 * Method name:getRoomNameList
	 * Description: �����б�  
	 * @author jackey
	 * CreateDate 2010-4-16
	 * Return: List
	 * @param schoolarea
	 * @return
	 * @throws Exception
	 */
	public List getRoomNameList(String schoolarea)throws Exception;

    public List getRoomList(String build) throws Exception;
	
	/**
	 * Method name:getUnbindDevList
	 * Description: δ�󶨵��豸�б�  
	 * @author jackey
	 * CreateDate 2010-4-16
	 * Return: List
	 * @return
	 * @throws Exception
	 */
	public List getUnbindDevList()throws Exception;
	/**
	 * Method name:getBindDevList
	 * Description: �󶨵��豸�б�  
	 * @author jackey
	 * CreateDate 2010-4-16
	 * Return: List
	 * @return
	 * @throws Exception
	 */
	public List getBindDevList(String roomid) throws Exception;
	/**
	 * Method name:saveBindDevList
	 * Description:   ����󶨽�� 
	 * @author jackey
	 * CreateDate 2010-4-16
	 * Return: void
	 * @param roomid
	 * @param binddeviceArr
	 * @throws Exception
	 */
	public void saveBindDevList(String roomid,String[] binddeviceArr)throws Exception;
	
	/**
	 * Method name:getMyClassList
	 * Description:  ����Լ���Ȩ�޲�ѯ�İ༶�б�
	 * @author jackey
	 * CreateDate 2010-4-21
	 * Return: List
	 * @param accountId��¼�˺�
	 * @return
	 * @throws Exception
	 */
	public List getMyClassList(String accountId)throws Exception;
	
	/**
	 * Method name:getLectureList
	 * Description:  ����Լ���Ȩ�޲�ѯ�Ŀγ��б� 
	 * @author jackey
	 * CreateDate 2010-4-21
	 * Return: List
	 * @param accountId ��¼�˺�
	 * @return
	 * @throws Exception
	 */
	public List getLectureList(String accountId)throws Exception;
	
	
	public List getAreaListMap()throws Exception;
	
}
