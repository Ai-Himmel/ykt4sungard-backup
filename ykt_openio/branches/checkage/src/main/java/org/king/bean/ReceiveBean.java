package org.king.bean;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class ReceiveBean implements Serializable {
    private String action;

    private String status;

    private String msg;

    private List<ReceiveItem> data = new ArrayList<ReceiveItem>();

    private String time;

    private String code;

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public List<ReceiveItem> getData() {
        return data;
    }

    public void setData(List<ReceiveItem> data) {
        this.data = data;
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

    public void addItem(ReceiveItem item) {
        if (this.data == null) {
            data = new ArrayList<ReceiveItem>();
        }
        this.data.add(item);
    }
}
