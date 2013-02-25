package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGACCCHK的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cfgaccchk implements Serializable {

    /**
     * 对账类型
     */
    private Integer accchktype;
    /**
     * 对账类别名称
     */
    private String accchktypename;
    /**
     * 对账文件在前置机上的路径
     */
    private String accchkfilepath;
    /**
     * 对账程序的名称
     */
    private String accchkexcname;
    /**
     * 前置机节点
     */
    private Integer bccdrtpno;
    /**
     * 前置机功能号
     */
    private Integer bccfuncno;
    /**
     * 前置机超时时间（秒）
     */
    private Integer bcctimeout;
    /**
     * 是否删除前置上对账文件
     */
    private String delflag;

    public void setAccchktype(Integer accchktype) {
        this.accchktype = accchktype;
    }

    public Integer getAccchktype() {
        return this.accchktype;
    }

    public void setAccchktypename(String accchktypename) {
        this.accchktypename = accchktypename;
    }

    public String getAccchktypename() {
        return this.accchktypename;
    }

    public void setAccchkfilepath(String accchkfilepath) {
        this.accchkfilepath = accchkfilepath;
    }

    public String getAccchkfilepath() {
        return this.accchkfilepath;
    }

    public void setAccchkexcname(String accchkexcname) {
        this.accchkexcname = accchkexcname;
    }

    public String getAccchkexcname() {
        return this.accchkexcname;
    }

    public void setBccdrtpno(Integer bccdrtpno) {
        this.bccdrtpno = bccdrtpno;
    }

    public Integer getBccdrtpno() {
        return this.bccdrtpno;
    }

    public void setBccfuncno(Integer bccfuncno) {
        this.bccfuncno = bccfuncno;
    }

    public Integer getBccfuncno() {
        return this.bccfuncno;
    }

    public void setBcctimeout(Integer bcctimeout) {
        this.bcctimeout = bcctimeout;
    }

    public Integer getBcctimeout() {
        return this.bcctimeout;
    }

    public void setDelflag(String delflag) {
        this.delflag = delflag;
    }

    public String getDelflag() {
        return this.delflag;
    }
}