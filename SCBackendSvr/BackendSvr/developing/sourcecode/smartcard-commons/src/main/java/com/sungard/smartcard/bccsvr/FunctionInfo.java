/*
 * FunctionInfo.java  v1.00  2012-2-17
 * Peoject	smartcard-commons
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	FunctionInfo.java  v1.00 2012-2-17
 * Project	: 	smartcard-commons
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

/**
 * 启动的功能号.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-17
 * 
 */
public class FunctionInfo {

    private int funcnum;
    private String funcname;
    private String desc;
    private Class<?> classz;

    public FunctionInfo(int funcnum, String funcname, String desc, Class<?> classz) {
        this.funcnum = funcnum;
        this.funcname = funcname;
        this.desc = desc;
        this.classz = classz;
    }

    public int getFuncnum() {
        return funcnum;
    }

    public void setFuncnum(int funcnum) {
        this.funcnum = funcnum;
    }

    public String getFuncname() {
        return funcname;
    }

    public void setFuncname(String funcname) {
        this.funcname = funcname;
    }

    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public Class<?> getClassz() {
        return classz;
    }

    public void setClassz(Class<?> classz) {
        this.classz = classz;
    }

}
