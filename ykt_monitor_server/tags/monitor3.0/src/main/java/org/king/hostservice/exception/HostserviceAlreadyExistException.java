package org.king.hostservice.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public class HostserviceAlreadyExistException extends BaseException {
    /**
     *
     */
    public HostserviceAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public HostserviceAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public HostserviceAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public HostserviceAlreadyExistException(Throwable e) {
        super(e);
    }
}
