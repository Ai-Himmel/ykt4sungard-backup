package org.king.topo.domain;



/**
 * MonitorTopoGroupStatistic entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoGroupStatistic extends AbstractMonitorTopoGroupStatistic implements java.io.Serializable {

    // Constructors

    /** default constructor */
    public MonitorTopoGroupStatistic() {
    }

	/** minimal constructor */
    public MonitorTopoGroupStatistic(Integer id) {
        super(id);        
    }
    
    /** full constructor */
    public MonitorTopoGroupStatistic(Integer id, String wordinfo, String hintinfo, Integer status, String lastupdate) {
        super(id, wordinfo, hintinfo, status, lastupdate);        
    }
   
}
