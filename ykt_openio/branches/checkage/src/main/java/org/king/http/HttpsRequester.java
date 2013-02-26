package org.king.http;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class HttpsRequester {
    private static final Logger logger = Logger.getLogger(HttpRequester.class);

    private String spec;

    private String charsetName = "UTF-8";

    private String method = "POST";

    private int connectTimeout = 20000;

    private int readTimeout;

    private List<Parameter> parameters = new ArrayList<Parameter>();

    private String cookie;

    public HttpsRequester() {
    }

    public HttpsRequester(String spec) {
        this.spec = spec;
    }

    public HttpsURLConnection connect() throws IOException, KeyManagementException, NoSuchProviderException, NoSuchAlgorithmException {
        if (StringUtils.isBlank(spec)) {
            throw new RuntimeException("The request url could not be null.");
        }
        System.setProperty("java.protocol.handler.pkgs", "javax.net.ssl");
        HostnameVerifier hv = new HostnameVerifier() {
            public boolean verify(String urlHostName, SSLSession session) {
                return urlHostName.equals(session.getPeerHost());
            }
        };
        HttpsURLConnection.setDefaultHostnameVerifier(hv);
        TrustManager[] tm = {new TrustAnyTrustManager()};
        SSLContext sslContext = SSLContext.getInstance("SSL", "SunJSSE");
        sslContext.init(null, tm, new java.security.SecureRandom());
        //从上述SSLContext对象中得到SSLSocketFactory对象
        SSLSocketFactory ssf = sslContext.getSocketFactory();

        URL url = new URL(spec);
        HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();
        connection.setRequestMethod(this.method);
        connection.setDoOutput(true);
        connection.setDoInput(true);
        connection.setUseCaches(false);
        connection.setConnectTimeout(this.connectTimeout);
        connection.setSSLSocketFactory(ssf);
        return connection;
    }

    public HttpResponser send() throws Exception {
        HttpsURLConnection connection = connect();
        setCookie(connection);
        processParameters(connection);
        saveCookie(connection);
        HttpResponser response = processResponse(connection);

        return response;
    }

    private void saveCookie(HttpsURLConnection connection) {
        if (cookie == null || cookie.length() == 0) {
            String setCookie = connection.getHeaderField("Set-Cookie");
            cookie = setCookie.substring(0, setCookie.indexOf(";"));
        }
    }

    private void setCookie(HttpsURLConnection connection) {
        if (cookie == null || cookie.length() == 0) {
        } else {
            connection.setRequestProperty("Cookie", cookie);
        }
    }

    private void processParameters(HttpsURLConnection connection) throws IOException {
        if (HttpRequester.GET.equalsIgnoreCase(method)) {
            //all the parameters should be added to url
        } else {
            StringBuffer params = new StringBuffer();
            for (Parameter parameter : parameters) {
                params.append("&").append(parameter.getName()).append("=").append(parameter.getValue());
            }
            logger.debug(params);
            OutputStreamWriter outer = new OutputStreamWriter(connection.getOutputStream(), "UTF-8");
            outer.write(params.toString());
            outer.flush();
            outer.close();
        }
    }

    private HttpResponser processResponse(HttpsURLConnection connection) throws IOException {
        InputStream in = connection.getInputStream();
        if (StringUtils.isBlank(charsetName)) {
            charsetName = connection.getContentEncoding();
        }
        logger.debug("charsetName:" + charsetName);
        BufferedReader reader = new BufferedReader(new InputStreamReader(in, charsetName));
        StringBuffer content = new StringBuffer();
        String line;

        while ((line = reader.readLine()) != null) {
            content.append(line).append("\r\n");
        }
        reader.close();

        HttpResponser httpResponser = new HttpResponser();
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

    public void addParameter(Parameter parameter) {
        this.parameters.add(parameter);
    }

    public void cleanParameter() {
        this.parameters = new ArrayList<Parameter>();
    }

    private static class TrustAnyTrustManager implements X509TrustManager {

        public void checkClientTrusted(X509Certificate ax509certificate[], String s)
                throws CertificateException {
        }

        public void checkServerTrusted(X509Certificate ax509certificate[], String s)
                throws CertificateException {
        }

        public X509Certificate[] getAcceptedIssuers() {
            return new X509Certificate[0];
        }

        private TrustAnyTrustManager() {
        }

    }
}
