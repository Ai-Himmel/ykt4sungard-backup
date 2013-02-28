package org.king.framework.util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.jdbc.support.lob.LobCreator;
import org.springframework.jdbc.support.lob.LobHandler;

import java.io.InputStream;
import java.io.Reader;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MyLobHandler
        implements LobHandler {
    private final Log log = LogFactory.getLog(getClass());
    private LobHandler defaultLobHandler;
    private LobHandler oracleLobHandler;
    private LobHandler myLobHandler;
    private boolean isOracle;
    private String dataBaseType;

    private boolean isOracle() {
        return getDataBaseType().indexOf("Oracle") != -1;
    }

    private LobHandler getOracleLobHandler() {
        return oracleLobHandler;
    }

    public void setOracleLobHandler(LobHandler oracleLobHandler) {
        this.oracleLobHandler = oracleLobHandler;
    }

    public byte[] getBlobAsBytes(ResultSet arg0, String arg1)
            throws SQLException {
        return getMyLobHandler().getBlobAsBytes(arg0, arg1);
    }

    public byte[] getBlobAsBytes(ResultSet arg0, int arg1)
            throws SQLException {
        return getMyLobHandler().getBlobAsBytes(arg0, arg1);
    }

    public InputStream getBlobAsBinaryStream(ResultSet arg0, String arg1)
            throws SQLException {
        return getMyLobHandler().getBlobAsBinaryStream(arg0, arg1);
    }

    public InputStream getBlobAsBinaryStream(ResultSet arg0, int arg1)
            throws SQLException {
        return getMyLobHandler().getBlobAsBinaryStream(arg0, arg1);
    }

    public String getClobAsString(ResultSet arg0, String arg1)
            throws SQLException {
        return getMyLobHandler().getClobAsString(arg0, arg1);
    }

    public String getClobAsString(ResultSet arg0, int arg1)
            throws SQLException {
        return getMyLobHandler().getClobAsString(arg0, arg1);
    }

    public InputStream getClobAsAsciiStream(ResultSet arg0, String arg1)
            throws SQLException {
        return getMyLobHandler().getClobAsAsciiStream(arg0, arg1);
    }

    public InputStream getClobAsAsciiStream(ResultSet arg0, int arg1)
            throws SQLException {
        return getMyLobHandler().getClobAsAsciiStream(arg0, arg1);
    }

    public Reader getClobAsCharacterStream(ResultSet arg0, String arg1)
            throws SQLException {
        return getMyLobHandler().getClobAsCharacterStream(arg0, arg1);
    }

    public Reader getClobAsCharacterStream(ResultSet arg0, int arg1)
            throws SQLException {
        return getMyLobHandler().getClobAsCharacterStream(arg0, arg1);
    }

    public LobCreator getLobCreator() {
        return getMyLobHandler().getLobCreator();
    }

    private LobHandler getMyLobHandler() {
        if (isOracle())
            myLobHandler = getOracleLobHandler();
        else {
            myLobHandler = getDefaultLobHandler();
        }

        return myLobHandler;
    }

    private void setMyLobHandler(LobHandler myLobHandler) {
        this.myLobHandler = myLobHandler;
    }

    private LobHandler getDefaultLobHandler() {
        return defaultLobHandler;
    }

    public void setDefaultLobHandler(LobHandler defaultLobHandler) {
        this.defaultLobHandler = defaultLobHandler;
    }

    private String getDataBaseType() {
        return dataBaseType;
    }

    public void setDataBaseType(String dataBaseType) {
        this.dataBaseType = dataBaseType;
    }
}