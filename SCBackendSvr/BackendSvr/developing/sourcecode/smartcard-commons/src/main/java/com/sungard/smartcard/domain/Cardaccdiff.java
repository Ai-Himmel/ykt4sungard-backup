package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDACCDIFF的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardaccdiff implements Serializable {

    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 姓名
     */
    private String custname;
    /**
     * 校区
     */
    private String areacode;
    /**
     * 不平金额
     */
    private Double diffamt;
    /**
     * 不平天数
     */
    private Integer diffdaycnt;
    /**
     * 账户当前余额
     */
    private Double availbal;
    /**
     * 卡当前余额
     */
    private Double lastcardbal;
    /**
     * 账户卡交易次数
     */
    private Integer lastcardcnt;
    /**
     * 统计日期
     */
    private String statdate;
    /**
     * 统计时间
     */
    private String stattime;
    /**
     * 不平开始日期
     */
    private String startdate;
    /**
     * 统计截止日期
     */
    private String enddate;
    /**
     * 期间卡最大交易次数
     */
    private Integer maxcardcnt;
    /**
     * 期间卡最后余额
     */
    private Double cardaftbal;
    /**
     * 期间消费缺失金额
     */
    private Double paylossamt;
    /**
     * 期间充值缺失金额
     */
    private Double dpslossamt;
    /**
     * 期间缺失总金额
     */
    private Double totallossamt;
    /**
     * 期间缺失条数
     */
    private Integer totallosscnt;
    /**
     * 处理日期
     */
    private String dealdate;
    /**
     * 处理操作员
     */
    private String opercode;
    /**
     * 平账状态
     */
    private String status;
    /**
     * 备注
     */
    private String remark;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setCustname(String custname) {
        this.custname = custname;
    }

    public String getCustname() {
        return this.custname;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setDiffamt(Double diffamt) {
        this.diffamt = diffamt;
    }

    public Double getDiffamt() {
        return this.diffamt;
    }

    public void setDiffdaycnt(Integer diffdaycnt) {
        this.diffdaycnt = diffdaycnt;
    }

    public Integer getDiffdaycnt() {
        return this.diffdaycnt;
    }

    public void setAvailbal(Double availbal) {
        this.availbal = availbal;
    }

    public Double getAvailbal() {
        return this.availbal;
    }

    public void setLastcardbal(Double lastcardbal) {
        this.lastcardbal = lastcardbal;
    }

    public Double getLastcardbal() {
        return this.lastcardbal;
    }

    public void setLastcardcnt(Integer lastcardcnt) {
        this.lastcardcnt = lastcardcnt;
    }

    public Integer getLastcardcnt() {
        return this.lastcardcnt;
    }

    public void setStatdate(String statdate) {
        this.statdate = statdate;
    }

    public String getStatdate() {
        return this.statdate;
    }

    public void setStattime(String stattime) {
        this.stattime = stattime;
    }

    public String getStattime() {
        return this.stattime;
    }

    public void setStartdate(String startdate) {
        this.startdate = startdate;
    }

    public String getStartdate() {
        return this.startdate;
    }

    public void setEnddate(String enddate) {
        this.enddate = enddate;
    }

    public String getEnddate() {
        return this.enddate;
    }

    public void setMaxcardcnt(Integer maxcardcnt) {
        this.maxcardcnt = maxcardcnt;
    }

    public Integer getMaxcardcnt() {
        return this.maxcardcnt;
    }

    public void setCardaftbal(Double cardaftbal) {
        this.cardaftbal = cardaftbal;
    }

    public Double getCardaftbal() {
        return this.cardaftbal;
    }

    public void setPaylossamt(Double paylossamt) {
        this.paylossamt = paylossamt;
    }

    public Double getPaylossamt() {
        return this.paylossamt;
    }

    public void setDpslossamt(Double dpslossamt) {
        this.dpslossamt = dpslossamt;
    }

    public Double getDpslossamt() {
        return this.dpslossamt;
    }

    public void setTotallossamt(Double totallossamt) {
        this.totallossamt = totallossamt;
    }

    public Double getTotallossamt() {
        return this.totallossamt;
    }

    public void setTotallosscnt(Integer totallosscnt) {
        this.totallosscnt = totallosscnt;
    }

    public Integer getTotallosscnt() {
        return this.totallosscnt;
    }

    public void setDealdate(String dealdate) {
        this.dealdate = dealdate;
    }

    public String getDealdate() {
        return this.dealdate;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}