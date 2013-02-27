package com.kingstargroup.form;

/**
 * AbstractMapfatherLine entity provides the base persistence definition of the
 * MapfatherLine entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapFatherLine implements java.io.Serializable {

	// Fields

	private long id;
	private String spoint;
	private String epoint;
	private long splayer;
	private long eplayer;
	private long linetype;
	private long linecolor;
	private long linestyle;
	private long linestatus;

	// Constructors

	/** default constructor */
	public AbstractMapFatherLine() {
	}

	/** minimal constructor */
	public AbstractMapFatherLine(long id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapFatherLine(long id, String spoint, String epoint,
			long splayer, long eplayer, long linetype, long linecolor,
			long linestyle, long linestatus) {
		this.id = id;
		this.spoint = spoint;
		this.epoint = epoint;
		this.splayer = splayer;
		this.eplayer = eplayer;
		this.linetype = linetype;
		this.linecolor = linecolor;
		this.linestyle = linestyle;
		this.linestatus = linestatus;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getSpoint() {
		return this.spoint;
	}

	public void setSpoint(String spoint) {
		this.spoint = spoint;
	}

	public String getEpoint() {
		return this.epoint;
	}

	public void setEpoint(String epoint) {
		this.epoint = epoint;
	}

	public long getSplayer() {
		return this.splayer;
	}

	public void setSplayer(long splayer) {
		this.splayer = splayer;
	}

	public long getEplayer() {
		return this.eplayer;
	}

	public void setEplayer(long eplayer) {
		this.eplayer = eplayer;
	}

	public long getLinetype() {
		return this.linetype;
	}

	public void setLinetype(long linetype) {
		this.linetype = linetype;
	}

	public long getLinecolor() {
		return this.linecolor;
	}

	public void setLinecolor(long linecolor) {
		this.linecolor = linecolor;
	}

	public long getLinestyle() {
		return this.linestyle;
	}

	public void setLinestyle(long linestyle) {
		this.linestyle = linestyle;
	}

	public long getLinestatus() {
		return this.linestatus;
	}

	public void setLinestatus(long linestatus) {
		this.linestatus = linestatus;
	}

}