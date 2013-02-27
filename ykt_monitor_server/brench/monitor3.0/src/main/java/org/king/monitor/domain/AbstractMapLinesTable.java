package org.king.monitor.domain;

/**
 * AbstractMapLinesTable entity provides the base persistence definition of the
 * MapLinesTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapLinesTable implements java.io.Serializable {

	// Fields

	private long id;
	private String point1;
	private String point2;
	private long linetype;
	private long linecolor;
	private long linestyle;
	private long linestatus;

	// Constructors

	/** default constructor */
	public AbstractMapLinesTable() {
	}

	/** minimal constructor */
	public AbstractMapLinesTable(long id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapLinesTable(long id, String point1, String point2,
			long linetype, long linecolor, long linestyle, long linestatus) {
		this.id = id;
		this.point1 = point1;
		this.point2 = point2;
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

	public String getPoint1() {
		return this.point1;
	}

	public void setPoint1(String point1) {
		this.point1 = point1;
	}

	public String getPoint2() {
		return this.point2;
	}

	public void setPoint2(String point2) {
		this.point2 = point2;
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