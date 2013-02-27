package org.king.host.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-28
 */
public class HostgroupsAlreadyExistException extends BaseException {
    /**
     *
     */
    public HostgroupsAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public HostgroupsAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public HostgroupsAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public HostgroupsAlreadyExistException(Throwable e) {
        super(e);
    }
}
