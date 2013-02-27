package org.king.termdev.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-2
 */

/**
 * MonitorDevtem entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevtem extends AbstractMonitorDevtem
        implements java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorDevtem() {
    }

    /**
     * full constructor
     */
    public MonitorDevtem(Integer deviceid, Integer templateid) {
        super(deviceid, templateid);
    }
}
