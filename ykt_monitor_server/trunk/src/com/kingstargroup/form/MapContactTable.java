package com.kingstargroup.form;

/**
 * MapContactTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapContactTable extends AbstractMapContactTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapContactTable() {
	}

	/** full constructor */
	public MapContactTable(String contactname, String contactgender,
			String contactcompany, String weekdays, String starttime,
			String endtime, String email, String cellphone) {
		super(contactname, contactgender, contactcompany, weekdays, starttime,
				endtime, email, cellphone);
	}

}
