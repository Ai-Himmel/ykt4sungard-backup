package org.king.check.service.impl;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.struts.action.DynaActionForm;
import org.king.check.dao.RoomDAO;
import org.king.check.domain.ClassDevAllInfo;
import org.king.check.domain.TArea;
import org.king.check.domain.TCheckstrategy;
import org.king.check.domain.TRoom;
import org.king.check.domain.TRoomdevice;
import org.king.check.domain.TRoomdeviceId;
import org.king.check.domain.TodayStuCheckSearch;
import org.king.check.domain.TodayStuCheckSearchDetail;
import org.king.check.service.AreaService;
import org.king.check.service.RoomService;
import org.king.utils.DateUtil;
import org.springframework.jdbc.core.JdbcTemplate;

public class RoomServiceImpl implements RoomService {

	private RoomDAO roomDAO;

	private AreaService areaService;
	
	private JdbcTemplate jdbcTemplate;

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public void setAreaService(AreaService areaService) {
		this.areaService = areaService;
	}

	public void setRoomDAO(RoomDAO roomDAO) {
		this.roomDAO = roomDAO;
	}

	public void saveRoom(TRoom Troom) throws Exception {
		roomDAO.save(Troom);
	}

	public TRoom getRoom(String id) throws Exception {
		return roomDAO.get(id);
	}
	


	// 查找某些个教室
	public List findRoom(TRoom room) throws Exception {
		StringBuffer query = new StringBuffer(
				" from TRoom  r where 1=1 ");
		if (StringUtils.isNotEmpty(room.getSchoolArea().getAreaCode())) {
			query = query.append(" and r.schoolArea ='").append(
					room.getSchoolArea()).append("'");
		}
		if (StringUtils.isNotEmpty(room.getBuild())) {
			query = query.append(" and r.build like '%")
					.append(room.getBuild()).append("%'");
		}
		if (StringUtils.isNotEmpty(room.getRoomName())) {
			query = query.append(" and r.roomName like '%").append(
					room.getRoomName()).append("%'");
		}

		return roomDAO.find(query.toString());
	}

	public TRoom findOneRoom(String areaName, String build, String roomName)
			throws Exception {
		StringBuffer query = new StringBuffer(
				" from TRoom  r where 1=1 ");
		if (StringUtils.isNotEmpty(areaName)) {
			query = query.append(" and r.schoolArea.areaName ='").append(
					areaName).append("'");
		}
		if (StringUtils.isNotEmpty(build)) {
			query = query.append(" and r.build = '").append(build).append("'");
		}
		if (StringUtils.isNotEmpty(roomName)) {
			query = query.append(" and r.roomName = '").append(roomName)
					.append("'");
		}
		List list = roomDAO.find(query.toString());
		if (list != null && !list.isEmpty()) {
			TRoom oneroom = (TRoom) list.get(0);
			return oneroom;
		}
		return null;
	}

	public void updateRoom(TRoom Troom) throws Exception {
		roomDAO.update(Troom);
	}

	public void deleteRoom(TRoom Troom) throws Exception {
		Troom.setStatus(0);
		roomDAO.update(Troom);
	}

	
	public void deleteRoomDevice(TRoomdevice roomdevice) throws Exception {
		roomDAO.delete(roomdevice);

	}

	public void saveRoomDevice(TRoomdevice roomdevice) throws Exception {
		roomDAO.save(roomdevice);

	}

	public List findRoomDevice(TRoomdevice roomdevice) throws Exception {

		StringBuffer query = new StringBuffer(" from TRoomdevice rd where 1=1 ");
		if (StringUtils.isNotEmpty(roomdevice.getId().getRoomId())) {
			query.append(" and  rd.id.roomId ='").append(
					roomdevice.getId().getRoomId()).append("'");
		}
		if (roomdevice.getId().getDeviceId() != null
				&& !"".equals(roomdevice.getId().getDeviceId().toString())) {
			query.append(" and rd.id.deviceId =").append(
					roomdevice.getId().getDeviceId());
		}
		List result = roomDAO.find(query.toString());

		return result;
	}

	public List getClassDevList(String schoolarea, String build, String roomname)
			throws Exception {
		// TODO Auto-generated method stub
		StringBuffer sql = new StringBuffer();
		sql
				.append("select new org.king.check.domain.ClassDevAllInfo(a.roomId,a.schoolArea.areaCode,a.schoolArea.areaName,a.build,a.roomName,'') from TRoom a where 1=1 ");
		if (null != schoolarea && !"".equals(schoolarea)) {
			sql.append("and a.schoolArea.areaCode='").append(schoolarea)
					.append("' ");
		}
		if (null != build && !"".equals(build)) {
			sql.append("and a.build='").append(build).append("' ");
		}
		if (null != roomname && !"".equals(roomname)) {
			sql.append("and a.roomName='").append(roomname).append("' ");
		}
		List entitys = roomDAO.find(sql.toString());

		for (int i = 0; i < entitys.size(); i++) {
			ClassDevAllInfo classDevAllInfo = (ClassDevAllInfo) entitys.get(i);
			if (!"".equals(classDevAllInfo.getRoomid())
					&& classDevAllInfo.getRoomid() != null) {
				List list_devs = roomDAO
						.find("select b.devicename from TRoomdevice a,TDevice b "
								+ "where a.id.roomId='"
								+ classDevAllInfo.getRoomid()
								+ "' and a.id.deviceId=b.deviceid");
				String devicename = "";
				if (list_devs.size() > 0) {
					for (int j = 0; j < list_devs.size(); j++) {
						
						  devicename += list_devs.get(j).toString() + ";";
						
					}
				}
				if (devicename.lastIndexOf(",") != -1) {
					devicename = devicename.substring(0, devicename
							.lastIndexOf(","));
				}
				classDevAllInfo.setDevname(devicename);

			}
		}
		return entitys;
	}

	public List getAreaList() throws Exception {
		List list = roomDAO.find("from TArea a where a.areaLevel=2");
		return list;
	}

	public List getBuildList(String schoolarea) throws Exception {
		List list = null;
		if (!"".equals(schoolarea)) {
			list = roomDAO
					.find("select distinct new map(a.build as build) from TRoom a where a.schoolArea.areaCode='"
							+ schoolarea + "'");
		} else {
			list = roomDAO
					.find("select distinct new map(a.build as build) from TRoom a");
		}
		return list;

	}

	public List getRoomNameList(String build) throws Exception {
		List list = null;
		if (!"".equals(build)) {
			list = roomDAO
					.find("select distinct new map(a.roomName as roomname) from TRoom a where a.build='"
							+ build + "'");
		} else {
			list = roomDAO
					.find("select distinct new map(a.roomName as roomname) from TRoom a ");
		}
		return list;
	}

    public List getRoomList(String build) throws Exception {
		List list = null;
		if (!"".equals(build)) {
			list = roomDAO.find("select distinct new map(a.roomId as roomId,a.roomName as roomname) from TRoom a where a.build='" + build + "'");
		} else {
			list = roomDAO.find("select distinct new map(a.roomName as roomname) from TRoom a ");
		}
		return list;
	}

	public List getBindDevList(String roomid) throws Exception {
		// TODO Auto-generated method stub
		List list = new ArrayList();
		if (!"".equals(roomid)) {
			list = roomDAO
					.find("select a from TDevice a,TRoomdevice b where b.id.roomId='"
							+ roomid + "' and a.deviceid=b.id.deviceId");
		}
		return list;
	}

	public List getUnbindDevList() throws Exception {
		List list = roomDAO
				.find("from TDevice a where a.deviceid not in (select distinct b.id.deviceId from TRoomdevice b) ");// and
		// a.devtypecode='9000'");
		return list;
	}

	public void saveBindDevList(String roomid, String[] binddeviceArr)
			throws Exception {
		// TODO Auto-generated method stub
		if (!"".equals(roomid)) {
			TRoomdevice roomdevice = new TRoomdevice();
			TRoomdeviceId id = new TRoomdeviceId();
			id.setRoomId(roomid);
			roomdevice.setId(id);
			List roomdeviceList = findRoomDevice(roomdevice);
			for (int i = 0; i < roomdeviceList.size(); i++) {
				TRoomdevice rd = (TRoomdevice) roomdeviceList.get(i);
				deleteRoomDevice(rd);
			}
			for (int j = 0; j < binddeviceArr.length; j++) {
				String binddevice = binddeviceArr[j];
				if (!"".equals(binddevice)) {
					TRoomdevice tmprd = new TRoomdevice();
					TRoomdeviceId rdid = new TRoomdeviceId();
					rdid.setRoomId(roomid);
					rdid.setDeviceId(Integer.valueOf(binddevice));
					tmprd.setId(rdid);
					saveRoomDevice(tmprd);
				}
			}

		}
	}

	public List getLectureList(String accountId) throws Exception {
		List list = new ArrayList();
		if (!"".equals(accountId)) {
			list = roomDAO
					.find(" select distinct tc.course from TCourseplan tc,TCourseplanclass tcp,Toperlimit tol,Department d" +
							" where tc.id=tcp.id.planid   and tcp.id.classno=tol.id.deptId " +
							" and tol.id.deptId=d.id and tol.id.operId='"
							+ accountId
							+ "' and tc.useDate='" 
							+ DateUtil.getNow("yyyyMMdd")
							+ "' order by tc.course.coursename");
		}
		return list;
	}

	public List getMyClassList(String accountId) throws Exception {
		List list = new ArrayList();
		if (!"".equals(accountId)) {
			list = roomDAO
					.find("select distinct d from Toperlimit tol,Department d where tol.id.deptId=d.id and tol.id.operId='"
							+ accountId + "' order by d.id");
		}
		return list;
	}
	
	

	

	public List getAreaListMap() throws Exception {
		List list = roomDAO
				.find("select new Map(a.areaCode as areaCode ,a.areaName as areaName  ) from TArea a where a.areaLevel=2");
		return list;
	}

	public String ifRoomCanImp(HSSFSheet sheet) throws Exception {
		String result="";
		try{
			int rowCount=sheet.getPhysicalNumberOfRows();
			if(rowCount>0){	        	  	        	
				for(int i=1;i<rowCount;i++){
					HSSFRow row = sheet.getRow(i);   
					try{   
						String schoolArea ="";//校区
						String build = "";//楼宇
						String roomName ="";//教室        
						schoolArea = row.getCell((short)0).getStringCellValue().trim();//校区
						build = row.getCell((short)1).getStringCellValue().trim();//楼宇
						roomName = row.getCell((short)2).getStringCellValue().trim();//教室
						TArea area = areaService.findAreaByName(schoolArea);
						if(area==null){
							result = result+"第"+i+"行校区名称错误，请核对校区名称。<br>";
							break;
						}
					}catch(NumberFormatException  ne){
						result = result+"第"+i+"行数字数据非文本类型，修改文本类型后再导入。<br> ";   
					}catch(NullPointerException n){
						result = result+"第"+i+"行有空数据，请填充后再导入。<br>";
					}
				}
			}else{
				result = "没有找到有效的记录。<br>";	
			}
		}catch(Exception e){
			result = result+"Excel文件检查异常，无法导入。<br>";  
		}
		if(!"".equals(result)){
			result = result+"导入失败。";
		}
		return result;
	}
	
	public String saveRoomImp(HSSFSheet sheet) throws Exception {
		String result="";
		try{
			int rowCount=sheet.getPhysicalNumberOfRows();
			if(rowCount>0){	       
				int savenum=0;
				for(int i=1;i<rowCount;i++){
					HSSFRow row = sheet.getRow(i);   
					try{   
						String schoolArea ="";//校区
						String build = "";//楼宇
						String roomName ="";//教室        
						schoolArea = row.getCell((short)0).getStringCellValue().trim();//校区
						build = row.getCell((short)1).getStringCellValue().trim();//楼宇
						roomName = row.getCell((short)2).getStringCellValue().trim();//教室
						if(findOneRoom(schoolArea,build,roomName)!=null){
							result = result+" 第"+i+"行教室已存在，未导入。<br>";
							continue;
						}else{
							TArea area = areaService.findAreaByName(schoolArea);
							TRoom room = new TRoom();
							room.setSchoolArea(area);
							room.setBuild(build);
							room.setRoomName(roomName);
							//room.setStatus(status);
							roomDAO.save(room);
						}
						savenum++;
					}catch(Exception e){
						result=result+" 第"+i+"行，数据导入失败。<br>" ;
					}
				}
				result =result+" 成功导入"+savenum+"行。<br>";
			}else{
				result =result+ " 没有找到有效的记录。<br>";	
			}
		}catch(Exception e){
			result = result+"导入出现异常中断。<br>";  
		}
	  return result;	
	}

}
