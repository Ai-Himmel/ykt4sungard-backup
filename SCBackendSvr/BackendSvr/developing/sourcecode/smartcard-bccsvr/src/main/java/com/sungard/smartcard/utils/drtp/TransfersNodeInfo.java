/*
 * TransNodeInfo.java  v1.00  2011-12-30
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	TransNodeInfo.java  v1.00 2011-12-30
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.utils.drtp;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.sql.SQLXML;
import java.sql.Timestamp;

import org.apache.commons.lang.builder.ToStringBuilder;

/**
 * 待传输对象domain drtp参照.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-30
 * 
 */
public class TransfersNodeInfo {

    private String name;// 存放cpack字段名
    private Field field;// 字段
    private Method method;// 方法
    // private Class<?> class1;
    private String methodName;

    private String desc;

    public TransfersNodeInfo() {
    }

    /**
     * 构造方法.
     * 
     * @param name
     *            放期的drtp变量名
     * @param method
     *            对应domain方法
     * @param propType
     *            返回值类型
     */
    public TransfersNodeInfo(String name, Method method, Class<?> propType) {
        this.name = name;
        this.method = method;
        // this.class1 = propType;

        // SetIntFieldByName 1;
        // SetDoubleFieldByName 2;
        // SetStringFieldByName 3
        int m = 0;
        if (propType.equals(String.class)) {
            m = 3;
        } else if (propType.equals(Integer.TYPE) || propType.equals(Integer.class)) {
            m = 1;
        } else if (propType.equals(Long.TYPE) || propType.equals(Long.class)) {
            m = 1;
        } else if (propType.equals(Double.TYPE) || propType.equals(Double.class)) {
            m = 2;
        } else if (propType.equals(Float.TYPE) || propType.equals(Float.class)) {
            m = 2;
        } else if (propType.equals(Short.TYPE) || propType.equals(Short.class)) {
            m = 1;
        } else if (propType.equals(Timestamp.class)) {
            m = 1;
        } else if (propType.equals(SQLXML.class)) {
            m = 1;
        } else {
            m = 1;
        }

        switch (m) {
        case 3:
            this.methodName = "SetStringFieldByName";
            break;
        case 2:
            this.methodName = "SetDoubleFieldByName";
            break;
        case 1:
            this.methodName = "SetIntFieldByName";
            break;
        default:
            this.methodName = "SetStringFieldByName";
            break;
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Field getField() {
        return field;
    }

    public void setField(Field field) {
        this.field = field;
    }

    public Method getMethod() {
        return method;
    }

    public void setMethod(Method method) {
        this.method = method;
    }

    public String getDesc() {
        return desc;
    }

    public String getMethodName() {
        return methodName;
    }

    /**
     * bccsvr 操作方法名.
     * 
     * @return
     * @since v1.00
     */
    public void setMethodName(String methodName) {
        this.methodName = methodName;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    @Override
    public String toString() {
        // return HashCodeBuilder.reflectionHashCode(method)+" method "+
        // HashCodeBuilder.reflectionHashCode(setMethodName)+" setMethodName" +
        // "  name=" + name + " method=" + method.getName() + " setMethodName="
        // + setMethodName;
        return ToStringBuilder.reflectionToString(this);
    }
}
