package com.kingstargroup.form;

/**
 * MapSerialexceptTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapSerialexceptTableId extends AbstractMapSerialexceptTableId
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapSerialexceptTableId() {
	}

	/** full constructor */
	public MapSerialexceptTableId(String analysistime, String transdate,
			String devphyid, long devseqno) {
		super(analysistime, transdate, devphyid, devseqno);
	}

}
