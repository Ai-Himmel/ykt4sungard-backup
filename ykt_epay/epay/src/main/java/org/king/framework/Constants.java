package org.king.framework;

import org.king.framework.common.ConfigurableContants;

public class Constants extends ConfigurableContants
{
  public static final String MESSAGE_BUNDLE_KEY;
  public static final String ERROR_BUNDLE_KEY;
  public static final int DEFAULT_PAGE_SIZE;
  public static final String USER_IN_SESSION;

  static
  {
    init("oneks.properties");

    MESSAGE_BUNDLE_KEY = getProperty("constant.message_bundle_key", "messages");
    ERROR_BUNDLE_KEY = getProperty("constant.error_bundle_key", "errors");
    DEFAULT_PAGE_SIZE = Integer.parseInt(getProperty("constant.default_page_size", String.valueOf(25)));
    USER_IN_SESSION = getProperty("constant.user_in_session", "user");
  }
}