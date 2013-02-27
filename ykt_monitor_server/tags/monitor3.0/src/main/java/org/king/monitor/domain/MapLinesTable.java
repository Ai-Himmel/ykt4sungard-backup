package org.king.monitor.domain;

/**
 * MapLinesTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapLinesTable extends AbstractMapLinesTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapLinesTable() {
	}

	/** minimal constructor */
	public MapLinesTable(long id) {
		super(id);
	}

	/** full constructor */
	public MapLinesTable(long id, String point1, String point2, long linetype,
			long linecolor, long linestyle, long linestatus) {
		super(id, point1, point2, linetype, linecolor, linestyle, linestatus);
	}

}
