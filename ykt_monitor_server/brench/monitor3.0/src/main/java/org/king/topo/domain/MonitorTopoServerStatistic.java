package org.king.topo.domain;

import java.math.BigDecimal;
import java.sql.Clob;

/**
 * MonitorTopoServerStatistic entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoServerStatistic extends
		AbstractMonitorTopoServerStatistic implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoServerStatistic() {
	}

	/** full constructor */
	public MonitorTopoServerStatistic(String hintinfo, Integer status,
			String lastupdate) {
		super(hintinfo, status, lastupdate);
	}

}
