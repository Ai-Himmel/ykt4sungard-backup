package org.king.check.domain;

public class ClassDevAllInfo {
	
	private String roomid;
	private String areacode;
	private String areaname;
	private String build;
	private String roomname;
//	private Integer status;
	private String devname;
	
	public ClassDevAllInfo(String roomid, String areacode, String areaname,
			String build, String roomname, String devname) {
		this.roomid = roomid;
		this.areacode = areacode;
		this.areaname = areaname;
		this.build = build;
		this.roomname = roomname;
		this.devname = devname;
	}
	public String getRoomid() {
		return roomid;
	}
	public void setRoomid(String roomid) {
		this.roomid = roomid;
	}
	public String getAreacode() {
		return areacode;
	}
	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}
	public String getAreaname() {
		return areaname;
	}
	public void setAreaname(String areaname) {
		this.areaname = areaname;
	}
	public String getBuild() {
		return build;
	}
	public void setBuild(String build) {
		this.build = build;
	}
	public String getRoomname() {
		return roomname;
	}
	public void setRoomname(String roomname) {
		this.roomname = roomname;
	}
	public String getDevname() {
		return devname;
	}
	public void setDevname(String devname) {
		this.devname = devname;
	}
	
	
	
}
