package org.king.monitor.domain;

/**
 * MapSetsTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapSetsTable extends AbstractMapSetsTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapSetsTable() {
	}

	/** minimal constructor */
	public MapSetsTable(long id) {
		super(id);
	}

	/** full constructor */
	public MapSetsTable(long id, long devid,String setsid, String setname,
			String fatherid, String settype, long setstatus, double xcoor,
			double ycoor, String feature) {
		super(id, devid,setsid, setname, fatherid, settype, setstatus, xcoor, ycoor,
				feature);
	}

}
