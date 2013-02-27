package com.kingstargroup.form;

/**
 * MapfatherLine entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapFatherLine extends AbstractMapFatherLine implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapFatherLine() {
	}

	/** minimal constructor */
	public MapFatherLine(long id) {
		super(id);
	}

	/** full constructor */
	public MapFatherLine(long id, String spoint, String epoint, long splayer,
			long eplayer, long linetype, long linecolor, long linestyle,
			long linestatus) {
		super(id, spoint, epoint, splayer, eplayer, linetype, linecolor,
				linestyle, linestatus);
	}

}
