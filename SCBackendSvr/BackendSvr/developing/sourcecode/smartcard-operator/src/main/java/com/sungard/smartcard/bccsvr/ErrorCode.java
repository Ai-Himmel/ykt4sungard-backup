package com.sungard.smartcard.bccsvr;

/**
 * error code list
 *
 * @author Yiming.You
 * @version v1.00
 */
public interface ErrorCode {
    public int getCode();

    public String getMessage();

    //error code for system module
    enum System implements ErrorCode {
        OK(0, "OK"),
        SYSTEM_EXCEPTION(1000, "System Error:{}"),
        UNREALIZED_METHOD(1001, "Unrealized method");

        private final int code;
        private final String message;

        System(int code, String message) {
            this.code = code;
            this.message = message;
        }

        public int getCode() {
            return code;
        }

        public String getMessage() {
            return message;
        }
    }

    //error code for device module
    enum Device implements ErrorCode {
        DEVICE_NOT_EXIST(300001, "Device [{}] does not exist");

        private final int code;
        private final String message;

        Device(int code, String message) {
            this.code = code;
            this.message = message;
        }

        public int getCode() {
            return code;
        }

        public String getMessage() {
            return message;
        }
    }
}
