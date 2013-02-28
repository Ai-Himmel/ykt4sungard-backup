package org.king.framework.exception;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class BaseException extends Exception {
    private Log log = LogFactory.getLog(getClass());
    private Throwable rootCause;

    public BaseException() {
    }

    public BaseException(String s) {
        this(s, null);
        rootCause = this;
    }

    public BaseException(String s, Throwable e) {
        super(s);

        if ((e instanceof BaseException))
            rootCause = ((BaseException) e).rootCause;
        else {
            rootCause = e;
        }

        log.info(s, e);
    }

    public BaseException(Throwable e) {
        this("", e);
    }

    public Throwable getRootCause() {
        return rootCause;
    }
}