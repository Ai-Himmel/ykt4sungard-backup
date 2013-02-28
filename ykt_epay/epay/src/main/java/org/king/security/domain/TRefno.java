package org.king.security.domain;

import java.math.BigDecimal;


/**
 * TRefno entity. @author MyEclipse Persistence Tools
 */

public class TRefno implements java.io.Serializable {


    // Fields    

     /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Long refno;
     private String mac;
     private Boolean status;
     private String accdate;
     private BigDecimal termid;
     private BigDecimal termseqno;
     private String lastsaved;
     private String reqrefno;


    // Constructors

    /** default constructor */
    public TRefno() {
    }

	/** minimal constructor */
    public TRefno(Long refno, String mac, Boolean status) {
        this.refno = refno;
        this.mac = mac;
        this.status = status;
    }
    
    /** full constructor */
    public TRefno(Long refno, String mac, Boolean status, String accdate, BigDecimal termid, BigDecimal termseqno, String lastsaved, String reqrefno) {
        this.refno = refno;
        this.mac = mac;
        this.status = status;
        this.accdate = accdate;
        this.termid = termid;
        this.termseqno = termseqno;
        this.lastsaved = lastsaved;
        this.reqrefno = reqrefno;
    }

   
    // Property accessors

    public Long getRefno() {
        return this.refno;
    }
    
    public void setRefno(Long refno) {
        this.refno = refno;
    }

    public String getMac() {
        return this.mac;
    }
    
    public void setMac(String mac) {
        this.mac = mac;
    }

    public Boolean getStatus() {
        return this.status;
    }
    
    public void setStatus(Boolean status) {
        this.status = status;
    }

    public String getAccdate() {
        return this.accdate;
    }
    
    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public BigDecimal getTermid() {
        return this.termid;
    }
    
    public void setTermid(BigDecimal termid) {
        this.termid = termid;
    }

    public BigDecimal getTermseqno() {
        return this.termseqno;
    }
    
    public void setTermseqno(BigDecimal termseqno) {
        this.termseqno = termseqno;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
    
    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getReqrefno() {
        return this.reqrefno;
    }
    
    public void setReqrefno(String reqrefno) {
        this.reqrefno = reqrefno;
    }
   








}