import org.king.http.HttpResponser;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.SecureRandom;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;


/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class SSLSocketFactory {
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


    public SSLSocketFactory() {
        sslcontext = null;
    }

    private SSLContext createSSLContext() {
        SSLContext sslcontext = null;
        try {
            sslcontext = SSLContext.getInstance("SSL");
            sslcontext.init(null, new TrustManager[]{new TrustAnyTrustManager()
            }, new SecureRandom());
        }
        catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        catch (KeyManagementException e) {
            e.printStackTrace();
        }
        return sslcontext;
    }

    private SSLContext getSSLContext() {
        if (sslcontext == null)
            sslcontext = createSSLContext();
        return sslcontext;
    }

    private SSLContext sslcontext;

    public static void main(String[] args) throws IOException, KeyManagementException, NoSuchProviderException, NoSuchAlgorithmException {
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
        javax.net.ssl.SSLSocketFactory ssf = sslContext.getSocketFactory();
        URL url = new URL("https://10.49.255.74/info.html");
        //创建HttpsURLConnection对象，并设置其SSLSocketFactory对象
        HttpsURLConnection httpsConn = (HttpsURLConnection) url.openConnection();
        httpsConn.setSSLSocketFactory(ssf);
        processResponse(httpsConn);
    }

    private static HttpResponser processResponse(HttpsURLConnection connection) throws IOException {
        InputStream in = connection.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        StringBuffer temp = new StringBuffer();
        String line;

        while ((line = reader.readLine()) != null) {
            temp.append(line).append("\r\n");
        }
        reader.close();

        HttpResponser httpResponser = new HttpResponser();

        String content = new String(temp.toString().getBytes(), "UTF-8");
        httpResponser.setContent(content.toString());
        System.out.println(content);
        return httpResponser;
    }
}
