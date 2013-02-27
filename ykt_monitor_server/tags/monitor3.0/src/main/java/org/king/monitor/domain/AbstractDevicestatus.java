package org.king.monitor.domain;

import java.math.BigDecimal;

/**
 * AbstractDevicestatus entity provides the base persistence definition of the
 * Devicestatus entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractDevicestatus implements java.io.Serializable {

	// Fields

	private String id;
	private long deviceid;
	private String devicename;
	private String devphyid;
	private long fdevceid;
	private String devtypecode;
	private long sysid;
	private String areacode;
	private String cardverno;
	private long devusage;
	private String ip;
	private String errstarttime;
	private long errlasttime;
	private String errendtime;
	private String contactname;
	private long errreason;
	private long devstatus;
	private String lastupdate;

	// Constructors

	/** default constructor */
	public AbstractDevicestatus() {
	}

	/** full constructor */
	public AbstractDevicestatus(long deviceid, String devicename,
			String devphyid, long fdevceid, String devtypecode,
			long sysid, String areacode,String cardverno,long devusage, String ip, String errstarttime,
			long errlasttime, String errendtime, String contactname,
			long errreason, long devstatus,String lastupdate) {
		this.deviceid = deviceid;
		this.devicename = devicename;
		this.devphyid = devphyid;
		this.fdevceid = fdevceid;
		this.devtypecode = devtypecode;
		this.sysid = sysid;
		this.areacode=areacode;
		this.cardverno = cardverno;
		this.devusage= devusage;
		this.ip = ip;
		this.errstarttime = errstarttime;
		this.errlasttime = errlasttime;
		this.errendtime = errendtime;
		this.contactname = contactname;
		this.errreason = errreason;
		this.devstatus = devstatus;
		this.lastupdate = lastupdate;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}

	public String getDevicename() {
		return this.devicename;
	}

	public void setDevicename(String devicename) {
		this.devicename = devicename;
	}

	public String getDevphyid() {
		return this.devphyid;
	}

	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}

	public long getFdevceid() {
		return this.fdevceid;
	}

	public void setFdevceid(long fdevceid) {
		this.fdevceid = fdevceid;
	}


	public long getSysid() {
		return this.sysid;
	}

	public void setSysid(long sysid) {
		this.sysid = sysid;
	}

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public String getErrstarttime() {
		return this.errstarttime;
	}

	public void setErrstarttime(String errstarttime) {
		this.errstarttime = errstarttime;
	}

	public long getErrlasttime() {
		return this.errlasttime;
	}

	public void setErrlasttime(long errlasttime) {
		this.errlasttime = errlasttime;
	}

	public String getErrendtime() {
		return this.errendtime;
	}

	public void setErrendtime(String errendtime) {
		this.errendtime = errendtime;
	}

	public String getContactname() {
		return this.contactname;
	}

	public void setContactname(String contactname) {
		this.contactname = contactname;
	}

	public long getErrreason() {
		return this.errreason;
	}

	public void setErrreason(long errreason) {
		this.errreason = errreason;
	}

	public long getDevstatus() {
		return this.devstatus;
	}

	public void setDevstatus(long devstatus) {
		this.devstatus = devstatus;
	}

	public String getLastupdate() {
		return lastupdate;
	}

	public void setLastupdate(String lastupdate) {
		this.lastupdate = lastupdate;
	}

	public String getDevtypecode() {
		return devtypecode;
	}

	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}

	public String getAreacode() {
		return areacode;
	}

	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}

	public long getDevusage() {
		return devusage;
	}

	public void setDevusage(long devusage) {
		this.devusage = devusage;
	}
	
	

}