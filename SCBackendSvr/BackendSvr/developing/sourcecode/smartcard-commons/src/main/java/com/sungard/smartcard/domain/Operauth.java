package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_OPERAUTH的实体类
 * 操作员授权表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Operauth implements Serializable {

    /**
     * 操作员
     */
    private String opercode;
    /**
     * 权限代码
     */
    private Integer authtype;
    /**
     * 授权人
     */
    private String authorizer;
    /**
     * 授权日期
     */
    private String authdate;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setAuthtype(Integer authtype) {
        this.authtype = authtype;
    }

    public Integer getAuthtype() {
        return this.authtype;
    }

    public void setAuthorizer(String authorizer) {
        this.authorizer = authorizer;
    }

    public String getAuthorizer() {
        return this.authorizer;
    }

    public void setAuthdate(String authdate) {
        this.authdate = authdate;
    }

    public String getAuthdate() {
        return this.authdate;
    }
}