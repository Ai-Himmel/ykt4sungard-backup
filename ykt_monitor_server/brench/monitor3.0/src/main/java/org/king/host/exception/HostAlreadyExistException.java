package org.king.host.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public class HostAlreadyExistException extends BaseException {
    /**
     *
     */
    public HostAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public HostAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public HostAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public HostAlreadyExistException(Throwable e) {
        super(e);
    }
}
