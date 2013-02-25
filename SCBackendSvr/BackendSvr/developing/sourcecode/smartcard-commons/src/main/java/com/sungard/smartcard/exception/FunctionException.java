package com.sungard.smartcard.exception;

/**
 * 该异常被捕获后，可根据messageCode和args进行format，得到错误提示信息，主要用于返回给客户端
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
public class FunctionException extends Exception {
    private int code;
    private Object[] args;

    public FunctionException(int code) {
        this.code = code;
    }

    public FunctionException(int code, Object... args) {
        this.code = code;
        this.args = args;
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public Object[] getArgs() {
        return args;
    }

    public void setArgs(Object[] args) {
        this.args = args;
    }
}
