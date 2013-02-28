package org.king.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-11-13
 */
public class Order implements Serializable{
    private String oid;
    private Double amount;
    private String currency = "CNY";
    private String date;
    private String time;
    private String status;
    private String remark;

    private List<Item> items = new ArrayList<Item>();

    public Order() {
    }

    public Order(String oid) {
        this.oid = oid;
    }

    public Order(String oid, Double amount, String currency, String date, String time, String status, String remark) {
        this.oid = oid;
        this.amount = amount;
        this.currency = currency;
        this.date = date;
        this.time = time;
        this.status = status;
        this.remark = remark;
    }

    public String getOid() {
        return oid;
    }

    public void setOid(String oid) {
        this.oid = oid;
    }

    public Double getAmount() {
        return amount;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public String getCurrency() {
        return currency;
    }

    public void setCurrency(String currency) {
        this.currency = currency;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getRemark() {
        return remark;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public List<Item> getItems() {
        return items;
    }

    public void setItems(List<Item> items) {
        this.items = items;
    }

    public void addItem(Item book) {
        items.add(book);
    }
}
