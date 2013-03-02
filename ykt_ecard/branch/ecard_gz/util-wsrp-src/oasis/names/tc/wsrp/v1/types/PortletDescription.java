/**
 * PortletDescription.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class PortletDescription  implements java.io.Serializable {
    private java.lang.String portletHandle;
    private oasis.names.tc.wsrp.v1.types.MarkupType[] markupTypes;
    private java.lang.String groupID;
    private oasis.names.tc.wsrp.v1.types.LocalizedString description;
    private oasis.names.tc.wsrp.v1.types.LocalizedString shortTitle;
    private oasis.names.tc.wsrp.v1.types.LocalizedString title;
    private oasis.names.tc.wsrp.v1.types.LocalizedString displayName;
    private oasis.names.tc.wsrp.v1.types.LocalizedString[] keywords;
    private java.lang.String[] userCategories;
    private java.lang.String[] userProfileItems;
    private java.lang.Boolean usesMethodGet;
    private java.lang.Boolean defaultMarkupSecure;
    private java.lang.Boolean onlySecure;
    private java.lang.Boolean userContextStoredInSession;
    private java.lang.Boolean templatesStoredInSession;
    private java.lang.Boolean hasUserSpecificState;
    private java.lang.Boolean doesUrlTemplateProcessing;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public PortletDescription() {
    }

    public PortletDescription(
           java.lang.Boolean defaultMarkupSecure,
           oasis.names.tc.wsrp.v1.types.LocalizedString description,
           oasis.names.tc.wsrp.v1.types.LocalizedString displayName,
           java.lang.Boolean doesUrlTemplateProcessing,
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           java.lang.String groupID,
           java.lang.Boolean hasUserSpecificState,
           oasis.names.tc.wsrp.v1.types.LocalizedString[] keywords,
           oasis.names.tc.wsrp.v1.types.MarkupType[] markupTypes,
           java.lang.Boolean onlySecure,
           java.lang.String portletHandle,
           oasis.names.tc.wsrp.v1.types.LocalizedString shortTitle,
           java.lang.Boolean templatesStoredInSession,
           oasis.names.tc.wsrp.v1.types.LocalizedString title,
           java.lang.String[] userCategories,
           java.lang.Boolean userContextStoredInSession,
           java.lang.String[] userProfileItems,
           java.lang.Boolean usesMethodGet) {
           this.portletHandle = portletHandle;
           this.markupTypes = markupTypes;
           this.groupID = groupID;
           this.description = description;
           this.shortTitle = shortTitle;
           this.title = title;
           this.displayName = displayName;
           this.keywords = keywords;
           this.userCategories = userCategories;
           this.userProfileItems = userProfileItems;
           this.usesMethodGet = usesMethodGet;
           this.defaultMarkupSecure = defaultMarkupSecure;
           this.onlySecure = onlySecure;
           this.userContextStoredInSession = userContextStoredInSession;
           this.templatesStoredInSession = templatesStoredInSession;
           this.hasUserSpecificState = hasUserSpecificState;
           this.doesUrlTemplateProcessing = doesUrlTemplateProcessing;
           this.extensions = extensions;
    }


    /**
     * Gets the portletHandle value for this PortletDescription.
     * 
     * @return portletHandle
     */
    public java.lang.String getPortletHandle() {
        return portletHandle;
    }


    /**
     * Sets the portletHandle value for this PortletDescription.
     * 
     * @param portletHandle
     */
    public void setPortletHandle(java.lang.String portletHandle) {
        this.portletHandle = portletHandle;
    }


    /**
     * Gets the markupTypes value for this PortletDescription.
     * 
     * @return markupTypes
     */
    public oasis.names.tc.wsrp.v1.types.MarkupType[] getMarkupTypes() {
        return markupTypes;
    }


    /**
     * Sets the markupTypes value for this PortletDescription.
     * 
     * @param markupTypes
     */
    public void setMarkupTypes(oasis.names.tc.wsrp.v1.types.MarkupType[] markupTypes) {
        this.markupTypes = markupTypes;
    }

    public oasis.names.tc.wsrp.v1.types.MarkupType getMarkupTypes(int i) {
        return this.markupTypes[i];
    }

    public void setMarkupTypes(int i, oasis.names.tc.wsrp.v1.types.MarkupType _value) {
        this.markupTypes[i] = _value;
    }


    /**
     * Gets the groupID value for this PortletDescription.
     * 
     * @return groupID
     */
    public java.lang.String getGroupID() {
        return groupID;
    }


    /**
     * Sets the groupID value for this PortletDescription.
     * 
     * @param groupID
     */
    public void setGroupID(java.lang.String groupID) {
        this.groupID = groupID;
    }


    /**
     * Gets the description value for this PortletDescription.
     * 
     * @return description
     */
    public oasis.names.tc.wsrp.v1.types.LocalizedString getDescription() {
        return description;
    }


    /**
     * Sets the description value for this PortletDescription.
     * 
     * @param description
     */
    public void setDescription(oasis.names.tc.wsrp.v1.types.LocalizedString description) {
        this.description = description;
    }


    /**
     * Gets the shortTitle value for this PortletDescription.
     * 
     * @return shortTitle
     */
    public oasis.names.tc.wsrp.v1.types.LocalizedString getShortTitle() {
        return shortTitle;
    }


    /**
     * Sets the shortTitle value for this PortletDescription.
     * 
     * @param shortTitle
     */
    public void setShortTitle(oasis.names.tc.wsrp.v1.types.LocalizedString shortTitle) {
        this.shortTitle = shortTitle;
    }


    /**
     * Gets the title value for this PortletDescription.
     * 
     * @return title
     */
    public oasis.names.tc.wsrp.v1.types.LocalizedString getTitle() {
        return title;
    }


    /**
     * Sets the title value for this PortletDescription.
     * 
     * @param title
     */
    public void setTitle(oasis.names.tc.wsrp.v1.types.LocalizedString title) {
        this.title = title;
    }


    /**
     * Gets the displayName value for this PortletDescription.
     * 
     * @return displayName
     */
    public oasis.names.tc.wsrp.v1.types.LocalizedString getDisplayName() {
        return displayName;
    }


    /**
     * Sets the displayName value for this PortletDescription.
     * 
     * @param displayName
     */
    public void setDisplayName(oasis.names.tc.wsrp.v1.types.LocalizedString displayName) {
        this.displayName = displayName;
    }


    /**
     * Gets the keywords value for this PortletDescription.
     * 
     * @return keywords
     */
    public oasis.names.tc.wsrp.v1.types.LocalizedString[] getKeywords() {
        return keywords;
    }


    /**
     * Sets the keywords value for this PortletDescription.
     * 
     * @param keywords
     */
    public void setKeywords(oasis.names.tc.wsrp.v1.types.LocalizedString[] keywords) {
        this.keywords = keywords;
    }

    public oasis.names.tc.wsrp.v1.types.LocalizedString getKeywords(int i) {
        return this.keywords[i];
    }

    public void setKeywords(int i, oasis.names.tc.wsrp.v1.types.LocalizedString _value) {
        this.keywords[i] = _value;
    }


    /**
     * Gets the userCategories value for this PortletDescription.
     * 
     * @return userCategories
     */
    public java.lang.String[] getUserCategories() {
        return userCategories;
    }


    /**
     * Sets the userCategories value for this PortletDescription.
     * 
     * @param userCategories
     */
    public void setUserCategories(java.lang.String[] userCategories) {
        this.userCategories = userCategories;
    }

    public java.lang.String getUserCategories(int i) {
        return this.userCategories[i];
    }

    public void setUserCategories(int i, java.lang.String _value) {
        this.userCategories[i] = _value;
    }


    /**
     * Gets the userProfileItems value for this PortletDescription.
     * 
     * @return userProfileItems
     */
    public java.lang.String[] getUserProfileItems() {
        return userProfileItems;
    }


    /**
     * Sets the userProfileItems value for this PortletDescription.
     * 
     * @param userProfileItems
     */
    public void setUserProfileItems(java.lang.String[] userProfileItems) {
        this.userProfileItems = userProfileItems;
    }

    public java.lang.String getUserProfileItems(int i) {
        return this.userProfileItems[i];
    }

    public void setUserProfileItems(int i, java.lang.String _value) {
        this.userProfileItems[i] = _value;
    }


    /**
     * Gets the usesMethodGet value for this PortletDescription.
     * 
     * @return usesMethodGet
     */
    public java.lang.Boolean getUsesMethodGet() {
        return usesMethodGet;
    }


    /**
     * Sets the usesMethodGet value for this PortletDescription.
     * 
     * @param usesMethodGet
     */
    public void setUsesMethodGet(java.lang.Boolean usesMethodGet) {
        this.usesMethodGet = usesMethodGet;
    }


    /**
     * Gets the defaultMarkupSecure value for this PortletDescription.
     * 
     * @return defaultMarkupSecure
     */
    public java.lang.Boolean getDefaultMarkupSecure() {
        return defaultMarkupSecure;
    }


    /**
     * Sets the defaultMarkupSecure value for this PortletDescription.
     * 
     * @param defaultMarkupSecure
     */
    public void setDefaultMarkupSecure(java.lang.Boolean defaultMarkupSecure) {
        this.defaultMarkupSecure = defaultMarkupSecure;
    }


    /**
     * Gets the onlySecure value for this PortletDescription.
     * 
     * @return onlySecure
     */
    public java.lang.Boolean getOnlySecure() {
        return onlySecure;
    }


    /**
     * Sets the onlySecure value for this PortletDescription.
     * 
     * @param onlySecure
     */
    public void setOnlySecure(java.lang.Boolean onlySecure) {
        this.onlySecure = onlySecure;
    }


    /**
     * Gets the userContextStoredInSession value for this PortletDescription.
     * 
     * @return userContextStoredInSession
     */
    public java.lang.Boolean getUserContextStoredInSession() {
        return userContextStoredInSession;
    }


    /**
     * Sets the userContextStoredInSession value for this PortletDescription.
     * 
     * @param userContextStoredInSession
     */
    public void setUserContextStoredInSession(java.lang.Boolean userContextStoredInSession) {
        this.userContextStoredInSession = userContextStoredInSession;
    }


    /**
     * Gets the templatesStoredInSession value for this PortletDescription.
     * 
     * @return templatesStoredInSession
     */
    public java.lang.Boolean getTemplatesStoredInSession() {
        return templatesStoredInSession;
    }


    /**
     * Sets the templatesStoredInSession value for this PortletDescription.
     * 
     * @param templatesStoredInSession
     */
    public void setTemplatesStoredInSession(java.lang.Boolean templatesStoredInSession) {
        this.templatesStoredInSession = templatesStoredInSession;
    }


    /**
     * Gets the hasUserSpecificState value for this PortletDescription.
     * 
     * @return hasUserSpecificState
     */
    public java.lang.Boolean getHasUserSpecificState() {
        return hasUserSpecificState;
    }


    /**
     * Sets the hasUserSpecificState value for this PortletDescription.
     * 
     * @param hasUserSpecificState
     */
    public void setHasUserSpecificState(java.lang.Boolean hasUserSpecificState) {
        this.hasUserSpecificState = hasUserSpecificState;
    }


    /**
     * Gets the doesUrlTemplateProcessing value for this PortletDescription.
     * 
     * @return doesUrlTemplateProcessing
     */
    public java.lang.Boolean getDoesUrlTemplateProcessing() {
        return doesUrlTemplateProcessing;
    }


    /**
     * Sets the doesUrlTemplateProcessing value for this PortletDescription.
     * 
     * @param doesUrlTemplateProcessing
     */
    public void setDoesUrlTemplateProcessing(java.lang.Boolean doesUrlTemplateProcessing) {
        this.doesUrlTemplateProcessing = doesUrlTemplateProcessing;
    }


    /**
     * Gets the extensions value for this PortletDescription.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this PortletDescription.
     * 
     * @param extensions
     */
    public void setExtensions(oasis.names.tc.wsrp.v1.types.Extension[] extensions) {
        this.extensions = extensions;
    }

    public oasis.names.tc.wsrp.v1.types.Extension getExtensions(int i) {
        return this.extensions[i];
    }

    public void setExtensions(int i, oasis.names.tc.wsrp.v1.types.Extension _value) {
        this.extensions[i] = _value;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof PortletDescription)) return false;
        PortletDescription other = (PortletDescription) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.portletHandle==null && other.getPortletHandle()==null) || 
             (this.portletHandle!=null &&
              this.portletHandle.equals(other.getPortletHandle()))) &&
            ((this.markupTypes==null && other.getMarkupTypes()==null) || 
             (this.markupTypes!=null &&
              java.util.Arrays.equals(this.markupTypes, other.getMarkupTypes()))) &&
            ((this.groupID==null && other.getGroupID()==null) || 
             (this.groupID!=null &&
              this.groupID.equals(other.getGroupID()))) &&
            ((this.description==null && other.getDescription()==null) || 
             (this.description!=null &&
              this.description.equals(other.getDescription()))) &&
            ((this.shortTitle==null && other.getShortTitle()==null) || 
             (this.shortTitle!=null &&
              this.shortTitle.equals(other.getShortTitle()))) &&
            ((this.title==null && other.getTitle()==null) || 
             (this.title!=null &&
              this.title.equals(other.getTitle()))) &&
            ((this.displayName==null && other.getDisplayName()==null) || 
             (this.displayName!=null &&
              this.displayName.equals(other.getDisplayName()))) &&
            ((this.keywords==null && other.getKeywords()==null) || 
             (this.keywords!=null &&
              java.util.Arrays.equals(this.keywords, other.getKeywords()))) &&
            ((this.userCategories==null && other.getUserCategories()==null) || 
             (this.userCategories!=null &&
              java.util.Arrays.equals(this.userCategories, other.getUserCategories()))) &&
            ((this.userProfileItems==null && other.getUserProfileItems()==null) || 
             (this.userProfileItems!=null &&
              java.util.Arrays.equals(this.userProfileItems, other.getUserProfileItems()))) &&
            ((this.usesMethodGet==null && other.getUsesMethodGet()==null) || 
             (this.usesMethodGet!=null &&
              this.usesMethodGet.equals(other.getUsesMethodGet()))) &&
            ((this.defaultMarkupSecure==null && other.getDefaultMarkupSecure()==null) || 
             (this.defaultMarkupSecure!=null &&
              this.defaultMarkupSecure.equals(other.getDefaultMarkupSecure()))) &&
            ((this.onlySecure==null && other.getOnlySecure()==null) || 
             (this.onlySecure!=null &&
              this.onlySecure.equals(other.getOnlySecure()))) &&
            ((this.userContextStoredInSession==null && other.getUserContextStoredInSession()==null) || 
             (this.userContextStoredInSession!=null &&
              this.userContextStoredInSession.equals(other.getUserContextStoredInSession()))) &&
            ((this.templatesStoredInSession==null && other.getTemplatesStoredInSession()==null) || 
             (this.templatesStoredInSession!=null &&
              this.templatesStoredInSession.equals(other.getTemplatesStoredInSession()))) &&
            ((this.hasUserSpecificState==null && other.getHasUserSpecificState()==null) || 
             (this.hasUserSpecificState!=null &&
              this.hasUserSpecificState.equals(other.getHasUserSpecificState()))) &&
            ((this.doesUrlTemplateProcessing==null && other.getDoesUrlTemplateProcessing()==null) || 
             (this.doesUrlTemplateProcessing!=null &&
              this.doesUrlTemplateProcessing.equals(other.getDoesUrlTemplateProcessing()))) &&
            ((this.extensions==null && other.getExtensions()==null) || 
             (this.extensions!=null &&
              java.util.Arrays.equals(this.extensions, other.getExtensions())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getPortletHandle() != null) {
            _hashCode += getPortletHandle().hashCode();
        }
        if (getMarkupTypes() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getMarkupTypes());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getMarkupTypes(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getGroupID() != null) {
            _hashCode += getGroupID().hashCode();
        }
        if (getDescription() != null) {
            _hashCode += getDescription().hashCode();
        }
        if (getShortTitle() != null) {
            _hashCode += getShortTitle().hashCode();
        }
        if (getTitle() != null) {
            _hashCode += getTitle().hashCode();
        }
        if (getDisplayName() != null) {
            _hashCode += getDisplayName().hashCode();
        }
        if (getKeywords() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getKeywords());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getKeywords(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getUserCategories() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getUserCategories());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getUserCategories(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getUserProfileItems() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getUserProfileItems());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getUserProfileItems(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getUsesMethodGet() != null) {
            _hashCode += getUsesMethodGet().hashCode();
        }
        if (getDefaultMarkupSecure() != null) {
            _hashCode += getDefaultMarkupSecure().hashCode();
        }
        if (getOnlySecure() != null) {
            _hashCode += getOnlySecure().hashCode();
        }
        if (getUserContextStoredInSession() != null) {
            _hashCode += getUserContextStoredInSession().hashCode();
        }
        if (getTemplatesStoredInSession() != null) {
            _hashCode += getTemplatesStoredInSession().hashCode();
        }
        if (getHasUserSpecificState() != null) {
            _hashCode += getHasUserSpecificState().hashCode();
        }
        if (getDoesUrlTemplateProcessing() != null) {
            _hashCode += getDoesUrlTemplateProcessing().hashCode();
        }
        if (getExtensions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getExtensions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getExtensions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(PortletDescription.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PortletDescription"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("portletHandle");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "portletHandle"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("markupTypes");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "markupTypes"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "MarkupType"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("groupID");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "groupID"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("description");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "description"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "LocalizedString"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("shortTitle");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "shortTitle"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "LocalizedString"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("title");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "title"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "LocalizedString"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("displayName");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "displayName"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "LocalizedString"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("keywords");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "keywords"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "LocalizedString"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userCategories");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userCategories"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userProfileItems");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userProfileItems"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("usesMethodGet");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "usesMethodGet"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("defaultMarkupSecure");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "defaultMarkupSecure"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("onlySecure");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "onlySecure"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userContextStoredInSession");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userContextStoredInSession"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("templatesStoredInSession");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "templatesStoredInSession"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("hasUserSpecificState");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "hasUserSpecificState"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("doesUrlTemplateProcessing");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "doesUrlTemplateProcessing"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("extensions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "extensions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Extension"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
