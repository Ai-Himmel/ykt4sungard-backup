package org.king.framework.util;

import java.io.File;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class KingConfig
{
  private static Log log = LogFactory.getLog(KingConfig.class);
  private static final String DEFAULT_UPLOADFILE_PATH = "pages/upload/";
  private static final String DEFAULT_SECURITYCONFIG_PATH = "WEB-INF/security/acl-config.xml";
  private static final String DEFAULT_INDEX_PATH = "WEB-INF/index/";
  private static final String CLASS_REAL_PATH = getClassRealPath();
  private String uploadFilePath;
  private String securityConfigPath;
  private String indexPath;
  private String rootPath;

  public String getRootPath()
  {
    return rootPath;
  }

  public void setRootPath(String rootPath) {
    this.rootPath = rootPath;
  }

  private static String getClassRealPath()
  {
    URI uri = null;
    try
    {
      uri = new URI(KingConfig.class.getResource("/").toString());
    } catch (URISyntaxException e) {
      log.error(e);
    }

    File file = new File(uri);
    String result = file.toString();
    result = result + File.separator;

    result = result + ".." + File.separator + ".." + File.separator;

    return result;
  }

  public String getIndexPath() {
    if (indexPath == null) {
      return getDefaultRealPath("WEB-INF/index/");
    }

    return getRealPath(indexPath);
  }

  public String getSecurityConfigPath() {
    if (securityConfigPath == null) {
      securityConfigPath = getDefaultRealPath("WEB-INF/security/acl-config.xml");
    }

    return getRealPath(securityConfigPath);
  }

  public String getUploadFilePath(boolean isReal) {
    if (isReal) {
      if (uploadFilePath == null) {
        return getDefaultRealPath("pages/upload/");
      }

      return getRealPath(uploadFilePath);
    }
    if (uploadFilePath == null) {
      return "pages/upload/";
    }

    return uploadFilePath;
  }

  public void setIndexPath(String indexPath)
  {
    this.indexPath = indexPath;
  }

  public void setSecurityConfigPath(String securityConfigPath) {
    this.securityConfigPath = securityConfigPath;
  }

  public void setUploadFilePath(String uploadFilePath) {
    this.uploadFilePath = uploadFilePath;
  }

  private String getRealPath(String path) {
    return getRootPath() + path;
  }

  private String getDefaultRealPath(String path) {
    return CLASS_REAL_PATH + path;
  }
}