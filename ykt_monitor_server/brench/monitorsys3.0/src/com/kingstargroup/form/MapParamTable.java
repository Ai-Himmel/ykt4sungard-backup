package com.kingstargroup.form;

/**
 * MapParamTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapParamTable extends AbstractMapParamTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapParamTable() {
	}

	/** full constructor */
	public MapParamTable(String parameter, double value, String name,
			String unit, long flag) {
		super(parameter, value, name, unit, flag);
	}

}
