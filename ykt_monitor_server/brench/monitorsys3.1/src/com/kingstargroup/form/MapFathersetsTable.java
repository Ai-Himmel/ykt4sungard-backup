package com.kingstargroup.form;

/**
 * MapFathersetsTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapFathersetsTable extends AbstractMapFathersetsTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapFathersetsTable() {
	}

	/** minimal constructor */
	public MapFathersetsTable(long id) {
		super(id);
	}

	/** full constructor */
	public MapFathersetsTable(long id, String systemid, String operationsystem,
			String systemname, long status, String ip, String hostname,
			String area, String macaddress, long coordx, long coordy,
			String feature) {
		super(id, systemid, operationsystem, systemname, status, ip, hostname,
				area, macaddress, coordx, coordy, feature);
	}

}
