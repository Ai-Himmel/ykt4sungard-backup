package org.king.bean;

import org.king.common.Constant;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class SendBean implements Serializable {
    private String action = Constant.CHECK_ACTION;

    private String time;

    private String code;

    private String requestTime;

    private List<Transdtl> data = new ArrayList<Transdtl>();

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getRequestTime() {
        return requestTime;
    }

    public void setRequestTime(String requestTime) {
        this.requestTime = requestTime;
    }

    public List<Transdtl> getData() {
        return data;
    }

    public void setData(List<Transdtl> data) {
        this.data = data;
    }
}
