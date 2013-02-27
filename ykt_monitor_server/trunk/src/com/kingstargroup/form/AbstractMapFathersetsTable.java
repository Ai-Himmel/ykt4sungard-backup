package com.kingstargroup.form;

/**
 * AbstractMapFathersetsTable entity provides the base persistence definition of
 * the MapFathersetsTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapFathersetsTable implements
		java.io.Serializable {

	// Fields

	private long id;
	private String systemid;
	private String operationsystem;
	private String systemname;
	private long status;
	private String ip;
	private String hostname;
	private String area;
	private String macaddress;
	private double coordx;
	private double coordy;
	private String feature;

	// Constructors

	/** default constructor */
	public AbstractMapFathersetsTable() {
	}

	/** minimal constructor */
	public AbstractMapFathersetsTable(long id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapFathersetsTable(long id, String systemid,
			String operationsystem, String systemname, long status, String ip,
			String hostname, String area, String macaddress, double coordx,
			double coordy, String feature) {
		this.id = id;
		this.systemid = systemid;
		this.operationsystem = operationsystem;
		this.systemname = systemname;
		this.status = status;
		this.ip = ip;
		this.hostname = hostname;
		this.area = area;
		this.macaddress = macaddress;
		this.coordx = coordx;
		this.coordy = coordy;
		this.feature = feature;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getSystemid() {
		return this.systemid;
	}

	public void setSystemid(String systemid) {
		this.systemid = systemid;
	}

	public String getOperationsystem() {
		return this.operationsystem;
	}

	public void setOperationsystem(String operationsystem) {
		this.operationsystem = operationsystem;
	}

	public String getSystemname() {
		return this.systemname;
	}

	public void setSystemname(String systemname) {
		this.systemname = systemname;
	}

	public long getStatus() {
		return this.status;
	}

	public void setStatus(long status) {
		this.status = status;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public String getHostname() {
		return this.hostname;
	}

	public void setHostname(String hostname) {
		this.hostname = hostname;
	}

	public String getArea() {
		return this.area;
	}

	public void setArea(String area) {
		this.area = area;
	}

	public String getMacaddress() {
		return this.macaddress;
	}

	public void setMacaddress(String macaddress) {
		this.macaddress = macaddress;
	}

	public double getCoordx() {
		return this.coordx;
	}

	public void setCoordx(double coordx) {
		this.coordx = coordx;
	}

	public double getCoordy() {
		return this.coordy;
	}

	public void setCoordy(double coordy) {
		this.coordy = coordy;
	}

	public String getFeature() {
		return this.feature;
	}

	public void setFeature(String feature) {
		this.feature = feature;
	}

}