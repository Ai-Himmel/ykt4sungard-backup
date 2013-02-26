package org.king.http;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-27
 */
public class HttpRequester {
    private static final Logger logger = Logger.getLogger(HttpRequester.class);

    public final static String POST = "POST";

    public final static String GET = "GET";

    private String spec;

    private String charsetName = "UTF-8";

    private String method = "POST";

    private int connectTimeout = 10000;

    private int readTimeout;

    private List<Parameter> parameters = new ArrayList<Parameter>();

    public HttpRequester() {
    }

    public HttpRequester(String spec) {
        this.spec = spec;
    }

    public HttpResponser send() throws IOException {
        HttpURLConnection connection = connect();
        processParameters(connection);
        return processResponse(connection);
    }

    private HttpURLConnection connect() throws IOException, ProtocolException {
        if (StringUtils.isBlank(spec)) {
            throw new RuntimeException("The request url could not be null.");
        }
        URL url = new URL(getFullUrl());
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod(this.method);
        connection.setDoOutput(true);
        connection.setDoInput(true);
        connection.setUseCaches(false);
        connection.setConnectTimeout(this.connectTimeout);
        return connection;
    }

    public String getFullUrl() {
        if (StringUtils.isBlank(spec)) {
            return "";
        }
        StringBuffer fullUrl = new StringBuffer(spec);
        if (HttpRequester.GET.equalsIgnoreCase(method)) {
            //add parameter to url while it's a get request
            boolean isFirst = true;
            if (spec.indexOf("?") != -1) {
                isFirst = false;
            }
            for (Parameter parameter : parameters) {
                if (isFirst) {
                    fullUrl.append("?").append(parameter.getName()).append("=").append(parameter.getValue());
                    isFirst = false;
                } else {
                    fullUrl.append("&").append(parameter.getName()).append("=").append(parameter.getValue());
                }
            }
        } else {
            //do nothing while it's a post request
        }
        return fullUrl.toString();
    }

    private void processParameters(HttpURLConnection connection) throws IOException {
        if (HttpRequester.GET.equalsIgnoreCase(method)) {
            //all the parameters should be added to url
        } else {
            StringBuffer params = new StringBuffer();
            for (Parameter parameter : parameters) {
                params.append("&").append(parameter.getName()).append("=").append(parameter.getValue());
            }
            connection.getOutputStream().write(params.toString().getBytes());
            connection.getOutputStream().flush();
            connection.getOutputStream().close();
        }
    }

    private HttpResponser processResponse(HttpURLConnection connection) throws IOException {
        InputStream in = connection.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        StringBuffer temp = new StringBuffer();
        String line;
        if (StringUtils.isBlank(charsetName)) {
            charsetName = connection.getContentEncoding();
        }
        while ((line = reader.readLine()) != null) {
            temp.append(line).append("\r\n");
        }
        reader.close();

        HttpResponser httpResponser = new HttpResponser();
        logger.info("charsetName:" + charsetName);
        String content = new String(temp.toString().getBytes(), charsetName);
        httpResponser.setContent(content.toString());
        return httpResponser;
    }

    public void addParameter(String name, String value) {
        parameters.add(new Parameter(name, value));
    }

    public String getSpec() {
        return spec;
    }

    public void setSpec(String spec) {
        this.spec = spec;
    }

    public String getCharsetName() {
        return charsetName;
    }

    public void setCharsetName(String charsetName) {
        this.charsetName = charsetName;
    }

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }

    public int getConnectTimeout() {
        return connectTimeout;
    }

    public void setConnectTimeout(int connectTimeout) {
        this.connectTimeout = connectTimeout;
    }

    public int getReadTimeout() {
        return readTimeout;
    }

    public void setReadTimeout(int readTimeout) {
        this.readTimeout = readTimeout;
    }

    public List<Parameter> getParameters() {
        return parameters;
    }

    public void setParameters(List<Parameter> parameters) {
        this.parameters = parameters;
    }
}
