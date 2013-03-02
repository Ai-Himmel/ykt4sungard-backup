/************************************iso8583.c******************************/

#include <stdlib.h>
#include <string.h>
#include "stdfunc.h"
#include "iso8583.h"

/*
 * 组包解包是否压缩数据，通常在POS中需压缩
 */
static int s_iCompress = 1;

static ISO_DEF s_isodef[] = {

#if ISO8583_VERSION==93

    /*000*/ {TYP_BCD, 0, 4, "Message Type Indicator"},
    /*001*/ {TYP_BIT, 0, 16, "Bitmap"},
    /*002*/ {TYP_BCD, 2, 19, "Primary Account number"},
    /*003*/ {TYP_BCD, 0, 6, "Processing Code"},
    /*004*/ {TYP_BCD, 0, 12, "Amount, Transaction"},
    /*005*/ {TYP_BCD, 0, 12, "Amount, Reconciliation"},
    /*006*/ {TYP_BCD, 0, 12, "Amount, Cardholder billing"},
    /*007*/ {TYP_BCD, 0, 10, "Date and time, transmission"},
    /*008*/ {TYP_BCD, 0, 8, "Amount, Cardholder billing fee"},
    /*009*/ {TYP_BCD, 0, 8, "Conversion rate, Reconciliation"},
    /*010*/ {TYP_BCD, 0, 8, "Conversion rate, Cardholder billing"},
    /*011*/ {TYP_BCD, 0, 6, "Systems trace audit number"},
    /*012*/ {TYP_BCD, 0, 12, "Date and time, Local transaction"},
    /*013*/ {TYP_BCD, 0, 4, "Date, Effective"},
    /*014*/ {TYP_BCD, 0, 4, "Date, Expiration"},
    /*015*/ {TYP_BCD, 0, 6, "Date, Settlement"},
    /*016*/ {TYP_BCD, 0, 4, "Date, Conversion"},
    /*017*/ {TYP_BCD, 0, 4, "Date, Capture"},
    /*018*/ {TYP_BCD, 0, 4, "Merchant type"},
    /*019*/ {TYP_BCD, 0, 3, "Country code, Acquiring institution"},
    /*020*/ {TYP_BCD, 0, 3, "Country code, Primary account number"},
    /*021*/ {TYP_BCD, 0, 3, "Country code, Forwarding institution"},
    /*022*/ {TYP_ASC, 0, 12, "Point of service data code"},
    /*023*/ {TYP_BCD, 0, 3, "Card sequence number"},
    /*024*/ {TYP_BCD, 0, 3, "Function code"},
    /*025*/ {TYP_BCD, 0, 4, "Message reason code"},
    /*026*/ {TYP_BCD, 0, 4, "Card acceptor business code"},
    /*027*/ {TYP_BCD, 0, 1, "Approval code length"},
    /*028*/ {TYP_BCD, 0, 6, "Date, Reconciliation"},
    /*029*/ {TYP_BCD, 0, 3, "Reconciliation indicator"},
    /*030*/ {TYP_BCD, 0, 24, "Amounts, original"},
    /*031*/ {TYP_ASC, 2, 99, "Acquirer reference data"},
    /*032*/ {TYP_BCD, 2, 11, "Acquirer institution identification code"},
    /*033*/ {TYP_BCD, 2, 11, "Forwarding institution identification code"},
    /*034*/ {TYP_ASC, 2, 28, "Primary account number, extended"},
    /*035*/ {TYP_BCD, 2, 37, "Track 2 data"},
    /*036*/ {TYP_BCD, 3, 104, "Track 3 data"},
    /*037*/ {TYP_ASC, 0, 12, "Retrieval reference number"},
    /*038*/ {TYP_ASC, 0, 6, "Approval code"},
    /*039*/ {TYP_BCD, 0, 3, "Action code"},
    /*040*/ {TYP_BCD, 0, 3, "Service code"},
    /*041*/ {TYP_ASC, 0, 8, "Card acceptor terminal identification"},
    /*042*/ {TYP_ASC, 0, 15, "Card acceptor identification code"},
    /*043*/ {TYP_ASC, 2, 99, "Card acceptor name/location"},
    /*044*/ {TYP_ASC, 2, 99, "Additional response data"},
    /*045*/ {TYP_ASC, 2, 76, "Track 1 data"},
    /*046*/ {TYP_ASC, 3, 204, "Amounts, Fees"},
    /*047*/ {TYP_ASC, 3, 999, "Additional data - national"},
    /*048*/ {TYP_ASC, 3, 999, "Additional data - private"},
    /*049*/ {TYP_ASC, 0, 3, "Currency code, Transaction"},
    /*050*/ {TYP_ASC, 0, 3, "Currency code, Reconciliation"},
    /*051*/ {TYP_ASC, 0, 3, "Currency code, Cardholder billing"},
    /*052*/ {TYP_BIN, 0, 8, "Personal identification number, PIN) data"},
    /*053*/ {TYP_BIN, 2, 48, "Security related control information"},
    /*054*/ {TYP_ASC, 3, 120, "Amounts, additional"},
    /*055*/ {TYP_BIN, 3, 255, "IC card system related data"},
    /*056*/ {TYP_BIN, 3, 255, "Original data elements"},
    /*057*/ {TYP_BCD, 0, 3, "Authorization life cycle code"},
    /*058*/ {TYP_BCD, 2, 11, "Authorizing agent institution Id Code"},
    /*059*/ {TYP_ASC, 3, 999, "Transport data"},
    /*060*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*061*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*062*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*063*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*064*/ {TYP_BIN, 0, 8, "Message authentication code field"}

#if ISO_FLDS==128 
 ,
 /*065*/ {TYP_BIN, 0, 8, "Reserved for ISO use"},
    /*066*/ {TYP_ASC, 3, 204, "Amounts, original fees"},
    /*067*/ {TYP_BCD, 0, 2, "Extended payment data"},
    /*068*/ {TYP_BCD, 0, 3, "Country code, receiving institution"},
    /*069*/ {TYP_BCD, 0, 3, "Country code, settlement institution"},
    /*070*/ {TYP_BCD, 0, 3, "Country code, authorizing agent Inst."},
    /*071*/ {TYP_BCD, 0, 8, "Message number"},
    /*072*/ {TYP_ASC, 3, 999, "Data record"},
    /*073*/ {TYP_BCD, 0, 6, "Date, action"},
    /*074*/ {TYP_BCD, 0, 10, "Credits, number"},
    /*075*/ {TYP_BCD, 0, 10, "Credits, reversal number"},
    /*076*/ {TYP_BCD, 0, 10, "Debits, number"},
    /*077*/ {TYP_BCD, 0, 10, "Debits, reversal number"},
    /*078*/ {TYP_BCD, 0, 10, "Transfer, number"},
    /*079*/ {TYP_BCD, 0, 10, "Transfer, reversal number"},
    /*080*/ {TYP_BCD, 0, 10, "Inquiries, number"},
    /*081*/ {TYP_BCD, 0, 10, "Authorizations, number"},
    /*082*/ {TYP_BCD, 0, 10, "Inquiries, reversal number"},
    /*083*/ {TYP_BCD, 0, 10, "Payments, number"},
    /*084*/ {TYP_BCD, 0, 10, "Payments, reversal number"},
    /*085*/ {TYP_BCD, 0, 10, "Fee collections, number"},
    /*086*/ {TYP_BCD, 0, 16, "Credits, amount"},
    /*087*/ {TYP_BCD, 0, 16, "Credits, reversal amount"},
    /*088*/ {TYP_BCD, 0, 16, "Debits, amount"},
    /*089*/ {TYP_BCD, 0, 16, "Debits, reversal amount"},
    /*090*/ {TYP_BCD, 0, 10, "Authorizations, reversal number"},
    /*091*/ {TYP_BCD, 0, 3, "Country code, transaction Dest. Inst."},
    /*092*/ {TYP_BCD, 0, 3, "Country code, transaction Orig. Inst."},
    /*093*/ {TYP_BCD, 2, 11, "Transaction Dest. Inst. Id code"},
    /*094*/ {TYP_BCD, 2, 11, "Transaction Orig. Inst. Id code"},
    /*095*/ {TYP_ASC, 2, 99, "Card issuer reference data"},
    /*096*/ {TYP_BIN, 3, 999, "Key management data"},
    /*097*/ {TYP_BCD, 0, 1+16, "Amount, Net reconciliation"}, /* was ISO_AMOUNT */
    /*098*/ {TYP_ASC, 0, 25, "Payee"},
    /*099*/ {TYP_ASC, 2, 11, "Settlement institution Id code"},
    /*100*/ {TYP_BCD, 2, 11, "Receiving institution Id code"},
    /*101*/ {TYP_ASC, 2, 17, "File name"},
    /*102*/ {TYP_ASC, 2, 28, "Account identification 1"},
    /*103*/ {TYP_ASC, 2, 28, "Account identification 2"},
    /*104*/ {TYP_ASC, 3, 100, "Transaction description"},
    /*105*/ {TYP_BCD, 0, 16, "Credits, Chargeback amount"},
    /*106*/ {TYP_BCD, 0, 16, "Debits, Chargeback amount"},
    /*107*/ {TYP_BCD, 0, 10, "Credits, Chargeback number"},
    /*108*/ {TYP_BCD, 0, 10, "Debits, Chargeback number"},
    /*109*/ {TYP_ASC, 2, 84, "Credits, Fee amounts"},
    /*110*/ {TYP_ASC, 2, 84, "Debits, Fee amounts"},
    /*111*/ {TYP_ASC, 3, 999, "Reserved for ISO use"},
    /*112*/ {TYP_ASC, 3, 999, "Reserved for ISO use"},
    /*113*/ {TYP_ASC, 3, 999, "Reserved for ISO use"},
    /*114*/ {TYP_ASC, 3, 999, "Reserved for ISO use"},
    /*115*/ {TYP_ASC, 3, 999, "Reserved for ISO use"},
    /*116*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*117*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*118*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*119*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*120*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*121*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*122*/ {TYP_ASC, 3, 999, "Reserved for national use"},
    /*123*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*124*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*125*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*126*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*127*/ {TYP_ASC, 3, 999, "Reserved for private use"},
    /*128*/ {TYP_BIN, 0, 8, "Message authentication code field"}
#endif /*ISO_FLDS==128*/

#else /*ISO8583_VERSION*/

    /*000*/ {TYP_BCD, 0, 4}, // "Message Type Indicator"
    /*001*/ {TYP_BIT, 0, 16}, // "Bitmap"
    /*002*/ {TYP_BCD, 2, 30}, // "Primary Account number"
    /*003*/ {TYP_BCD, 0, 6}, // "Processing Code"
    /*004*/ {TYP_BCD, 0, 12}, // "Amount, Transaction"
    /*005*/ {TYP_BCD, 0, 12}, // "Amount, Reconciliation"
    /*006*/ {TYP_BCD, 0, 12}, // "Amount, Cardholder billing"
    /*007*/ {TYP_BCD, 0, 10}, // "Date and time, transmission"
    /*008*/ {TYP_BCD, 0, 8}, // "Amount, Cardholder billing fee"
    /*009*/ {TYP_BCD, 0, 8}, // "Conversion rate, Reconciliation"
    /*010*/ {TYP_BCD, 0, 8}, // "Conversion rate, Cardholder billing"
    /*011*/ {TYP_BCD, 0, 20}, // "Systems trace audit number"
    /*012*/ {TYP_BCD, 0, 6}, // "Date and time, Local transaction"
    /*013*/ {TYP_BCD, 0, 8}, // "Date, Effective"
    /*014*/ {TYP_BCD, 0, 4}, // "Date, Expiration"
    /*015*/ {TYP_BCD, 0, 4}, // "Date, Settlement"
    /*016*/ {TYP_BCD, 0, 4}, // "Date, Conversion"
    /*017*/ {TYP_BCD, 0, 4}, // "Date, Capture"
    /*018*/ {TYP_BCD, 0, 4}, // "Merchant type"
    /*019*/ {TYP_BCD, 0, 3}, // "Country code, Acquiring institution"
    /*020*/ {TYP_BCD, 0, 3}, // "Country code, Primary account number"
    /*021*/ {TYP_BCD, 0, 3}, // "Country code, Forwarding institution"
    /*022*/ {TYP_ASC, 0, 12}, // "Point of service data code"
    /*023*/ {TYP_BCD, 0, 3}, // "Card sequence number"
    /*024*/ {TYP_BCD, 0, 3}, // "Function code"
    /*025*/ {TYP_BCD, 0, 4}, // "Message reason code"
    /*026*/ {TYP_BCD, 0, 4}, // "Card acceptor business code"
    /*027*/ {TYP_BCD, 0, 1}, // "Approval code length"
    /*028*/ {TYP_BCD, 0, 6}, // "Date, Reconciliation"
    /*029*/ {TYP_BCD, 0, 3}, // "Reconciliation indicator"
    /*030*/ {TYP_BCD, 0, 24}, // "Amounts, original"
    /*031*/ {TYP_ASC, 2, 99}, // "Acquirer reference data"
    /*032*/ {TYP_BCD, 2, 6}, // "Acquirer institution identification code"
    /*033*/ {TYP_BCD, 2, 11}, // "Forwarding institution identification code"
    /*034*/ {TYP_ASC, 2, 28}, // "Primary account number, extended"
	
   /*035*/ {TYP_BCD, 2, 37}, // "Track 2 data"  changed by hhd at 20100814 ASC->BCD
    /*036*/ {TYP_BCD, 3, 104}, // "Track 3 data"  changed by hhd at 20100814 ASC->BCD
    /*037*/ {TYP_ASC, 0, 20}, // "Retrieval reference number"
    /*038*/ {TYP_ASC, 0, 6}, // "Approval code"
    /*039*/ {TYP_ASC, 0, 2}, // "Action code"
    /*040*/ {TYP_BCD, 0, 3}, // "Service code"
    /*041*/ {TYP_ASC, 0, 8}, // "Card acceptor terminal identification"
    /*042*/ {TYP_ASC, 0, 15}, // "Card acceptor identification code"
    /*043*/ {TYP_ASC, 2, 99}, // "Card acceptor name/location"
    /*044*/ {TYP_ASC, 2, 99}, // "Additional response data"
    /*045*/ {TYP_ASC, 2, 76}, // "Track 1 data"
    /*046*/ {TYP_ASC, 3, 204}, // "Amounts, Fees"
    /*047*/ {TYP_ASC, 3, 999}, // "Additional data - national"
    /*048*/ {TYP_ASC, 0, 62}, // "Additional data - private"
    /*049*/ {TYP_ASC, 0, 3}, // "Currency code, Transaction"
    /*050*/ {TYP_ASC, 0, 3}, // "Currency code, Reconciliation"
    /*051*/ {TYP_ASC, 0, 3}, // "Currency code, Cardholder billing"
    /*052*/ {TYP_BIN, 0, 8}, // "Personal identification number, PIN) data"
    /*053*/ {TYP_BIN, 2, 48}, // "Security related control information"
    /*054*/ {TYP_ASC, 3, 120}, // "Amounts, additional"
    /*055*/ {TYP_BIN, 3, 255}, // "IC card system related data"
    /*056*/ {TYP_BIN, 3, 255}, // "Original data elements"
    /*057*/ {TYP_BCD, 0, 3}, // "Authorization life cycle code"
    /*058*/ {TYP_BCD, 2, 11}, // "Authorizing agent institution Id Code"
    /*059*/ {TYP_ASC, 3, 999}, // "Transport data"
    /*060*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*061*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*062*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*063*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*064*/ {TYP_BIN, 0, 8}  // "Message authentication code field"

#if ISO_FLDS==128
 ,
 /*065*/ {TYP_BIN, 0, 8}, // "Reserved for ISO use"
    /*066*/ {TYP_ASC, 3, 204}, // "Amounts, original fees"
    /*067*/ {TYP_BCD, 0, 2}, // "Extended payment data"
    /*068*/ {TYP_BCD, 0, 3}, // "Country code, receiving institution"
    /*069*/ {TYP_BCD, 0, 3}, // "Country code, settlement institution"
    /*070*/ {TYP_BCD, 0, 3}, // "Country code, authorizing agent Inst."
    /*071*/ {TYP_BCD, 0, 8}, // "Message number"
    /*072*/ {TYP_ASC, 3, 999}, // "Data record"
    /*073*/ {TYP_BCD, 0, 6}, // "Date, action"
    /*074*/ {TYP_BCD, 0, 10}, // "Credits, number"
    /*075*/ {TYP_BCD, 0, 10}, // "Credits, reversal number"
    /*076*/ {TYP_BCD, 0, 10}, // "Debits, number"
    /*077*/ {TYP_BCD, 0, 10}, // "Debits, reversal number"
    /*078*/ {TYP_BCD, 0, 10}, // "Transfer, number"
    /*079*/ {TYP_BCD, 0, 10}, // "Transfer, reversal number"
    /*080*/ {TYP_BCD, 0, 10}, // "Inquiries, number"
    /*081*/ {TYP_BCD, 0, 10}, // "Authorizations, number"
    /*082*/ {TYP_BCD, 0, 10}, // "Inquiries, reversal number"
    /*083*/ {TYP_BCD, 0, 10}, // "Payments, number"
    /*084*/ {TYP_BCD, 0, 10}, // "Payments, reversal number"
    /*085*/ {TYP_BCD, 0, 10}, // "Fee collections, number"
    /*086*/ {TYP_BCD, 0, 16}, // "Credits, amount"
    /*087*/ {TYP_BCD, 0, 16}, // "Credits, reversal amount"
    /*088*/ {TYP_BCD, 0, 16}, // "Debits, amount"
    /*089*/ {TYP_BCD, 0, 16}, // "Debits, reversal amount"
    /*090*/ {TYP_BCD, 0, 10}, // "Authorizations, reversal number"
    /*091*/ {TYP_BCD, 0, 3}, // "Country code, transaction Dest. Inst."
    /*092*/ {TYP_BCD, 0, 3}, // "Country code, transaction Orig. Inst."
    /*093*/ {TYP_BCD, 2, 11}, // "Transaction Dest. Inst. Id code"
    /*094*/ {TYP_BCD, 2, 11}, // "Transaction Orig. Inst. Id code"
    /*095*/ {TYP_ASC, 2, 99}, // "Card issuer reference data"
    /*096*/ {TYP_BIN, 3, 999}, // "Key management data"
    /*097*/ {TYP_BCD, 0, 1+16}, // "Amount, Net reconciliation"/* was ISO_AMOUNT */
    /*098*/ {TYP_ASC, 0, 25}, // "Payee"
    /*099*/ {TYP_ASC, 2, 11}, // "Settlement institution Id code"
    /*100*/ {TYP_ASC, 0, 6}, // "Receiving institution Id code"
    /*101*/ {TYP_ASC, 2, 17}, // "File name"
    /*102*/ {TYP_ASC, 2, 28}, // "Account identification 1"
    /*103*/ {TYP_ASC, 2, 28}, // "Account identification 2"
    /*104*/ {TYP_ASC, 3, 9}, // "Transaction description"
    /*105*/ {TYP_BCD, 0, 16}, // "Credits, Chargeback amount"
    /*106*/ {TYP_BCD, 0, 16}, // "Debits, Chargeback amount"
    /*107*/ {TYP_BCD, 0, 10}, // "Credits, Chargeback number"
    /*108*/ {TYP_BCD, 0, 10}, // "Debits, Chargeback number"
    /*109*/ {TYP_ASC, 2, 84}, // "Credits, Fee amounts"
    /*110*/ {TYP_ASC, 2, 84}, // "Debits, Fee amounts"
    /*111*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
    /*112*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
    /*113*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
    /*114*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
    /*115*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
    /*116*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*117*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*118*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*119*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*120*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*121*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*122*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*123*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*124*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*125*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*126*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*127*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*128*/ {TYP_BIN, 0, 8}  // "Message authentication code field"

#endif /*ISO_FLDS==128*/

#endif /*ISO8583_VERSION*/
};


void iso8583_compress(int c)
{
 s_iCompress = c;
}

/* Initialize an ISO message struct - i.e. set all entries to NULL */
void iso8583_init(ISO_MSG *m)
{
 int i;

 for (i=0; i<=ISO_FLDS; i++) {
  m->fld[i].buf = NULL;
  m->fld[i].len = 0;
 }
}

int iso8583_set(ISO_MSG *m, int idx, const unsigned char *data, int len)
{
 if (m->fld[idx].buf != NULL) {
  free(m->fld[idx].buf);
  m->fld[idx].buf = NULL;
  m->fld[idx].len = 0;
 }

 if (len > s_isodef[idx].len)
  return 0;
 
 m->fld[idx].len = len;
 m->fld[idx].buf = (unsigned char*)malloc(m->fld[idx].len * sizeof(char));
 if (m->fld[idx].buf == NULL)
  return 0;

 memcpy(m->fld[idx].buf, data, m->fld[idx].len);

 return len;
}

int iso8583_get(const ISO_MSG *m, int idx, unsigned char *data, int len)
{
 if (m == NULL || data == NULL || m->fld[idx].buf == NULL)
  return 0;
 
 if (m->fld[idx].len > len)
  return 0;
  
 memcpy(data, m->fld[idx].buf, m->fld[idx].len);
 
 return m->fld[idx].len;
}


/*
 * Using the definition d, pack the content of the ISO message m into 
 * buf. NOTE: buf must be large enough to contain the packed message.
 * Returns the length of the data written to buf.
 */
int iso8583_pack(const ISO_MSG *m, char *buf)
{
 char *start = buf;
 int flds, i;
 char fmt[8], tmp[8]={0};

 /* Field 0 is mandatory and fixed length. */
 if (m->fld[0].len != s_isodef[0].len || s_isodef[0].fmt != FMT_FIXED) {
  MY_TRACE("flds = %d", 0);
  return -1;
 }

 if (s_iCompress) 
 {
  buf += ASC2BCD((unsigned char*)buf, (const char*)m->fld[0].buf, s_isodef[0].len, s_isodef[0].fmt);
 }
 else
 {
  memcpy(buf, m->fld[0].buf, s_isodef[0].len);
  buf += s_isodef[0].len;  
 }

 /*
  * The bitmap contains either 64 or 128 fields - flds is the 
  * number of allowed fields, i.e. either 64 or 128.
  */
 if (m->fld[1].buf == NULL || s_isodef[1].len != 16) {
  MY_TRACE("flds = %d", 1);
  return -1;
 }
 
#if ISO_FLDS==128
 if ((m->fld[1].len == s_isodef[1].len) && (m->fld[1].buf[0] & 0x80))
 {
  memcpy(buf, m->fld[1].buf, s_isodef[0].len);
  buf += s_isodef[1].len;
  flds = 128;
 }
 else
 {
  if ((m->fld[1].len == 8) && !(m->fld[1].buf[0] & 0x80))
  {
   memcpy(buf, m->fld[1].buf, 8);
   buf += 8;
   flds = 64;
  }
  else
  {
   MY_TRACE("flds = %d", 1);
   return -1;
  }
 }
#else /*ISO_FLDS==128*/
 if ((m->fld[1].len != 8) || (m->fld[1].buf[0] & 0x80)) {
  MY_TRACE("flds = %d", 1);
  return -1;
 }
 
 memcpy(buf, m->fld[1].buf, m->fld[1].len);
 buf += m->fld[1].len;
 flds = 64;
#endif /*ISO_FLDS==128*/

 for (i = 2; i <= flds; i++) 
 {
  if (MY_BITGET(m->fld[1].buf, i)) 
  { /* i'th bit != 0 */
   if (m->fld[i].buf == NULL || m->fld[i].len <= 0 || m->fld[i].len > s_isodef[i].len)
   {
    MY_TRACE("flds = %d", i);
    return -1;
   }

   if (s_isodef[i].fmt) 
   { /* Variable length */
    if (s_iCompress)
    {
     sprintf(fmt, "%%0%dd", s_isodef[i].fmt);
     sprintf(tmp, fmt, m->fld[i].len);
     buf += ASC2BCD((unsigned char*)buf, tmp, s_isodef[i].fmt, 0);
    }
    else
    {
     sprintf(fmt, "%%0%dd", s_isodef[i].fmt);
     sprintf(buf, fmt, m->fld[i].len);
     buf += s_isodef[i].fmt;
    }   
   }

   switch (s_isodef[i].typ) {
   case TYP_BCD: /* Fallthrough */
    if (s_iCompress)
    {
     buf += ASC2BCD((unsigned char*)buf,(const char*) m->fld[i].buf, m->fld[i].len, s_isodef[i].fmt); 
     break;
    }
   case TYP_ASC:
   case TYP_BIN:
    memcpy(buf, m->fld[i].buf, m->fld[i].len);
    buf += m->fld[i].len;
    break;
   default:
    MY_TRACE("flds = %d", i);
    return -1;
    break;
   }
     }
 }

 return (buf-start);
}


/*
 * Using the definition d, unpack the content of buf into the ISO 
 * message struct m.
 * Returns 0. FIXME: Should be something different.
 */
int iso8583_unpack(ISO_MSG *m, const char *buf)
{
 const char *start = buf;
 int flds, i;
    char fmt[8];

 memset(fmt, 0, sizeof(fmt));

 /* Field 0 is mandatory and fixed length. */
 if (m->fld[0].buf != NULL || s_isodef[0].fmt != FMT_FIXED) {
  MY_TRACE("flds = %d", 0);
  return -1;
 }

 m->fld[0].len = s_isodef[0].len;
 m->fld[0].buf = (unsigned char *) malloc((m->fld[0].len) * sizeof(char));
 if(s_iCompress)
 {
  buf += BCD2ASC((char*)m->fld[0].buf,(const unsigned char*) buf, m->fld[0].len, s_isodef[0].fmt);
 }
 else
 {
  memcpy(m->fld[0].buf, buf, m->fld[0].len);
  buf += m->fld[0].len;
 }


 /*
  * First bit in the bitmap (field 1) defines if the message is 
  * extended or not.
  * 0: not exteded - i.e. only (some of) the fields 0 to 64 are 
  *    used
  * 1: extended - i.e. (some of) the fields 0 to 128 are used
  * I.e. if one or more of the fields 65 to 128 is used, the 
  * bit is 1.
  */
#if ISO_FLDS==128
 if(buf[0] & 0x80) {
  flds = 128;
 } else {
  flds = 64;
 }
#else /*ISO_FLDS==128*/
 if(buf[0] & 0x80) {
  MY_TRACE("flds = %d", 1);
  return -1;
 }
 flds = 64;
#endif /*ISO_FLDS==128*/

 m->fld[1].len = flds/8;
 m->fld[1].buf = (unsigned char *) calloc((m->fld[1].len), sizeof(char));
 memcpy(m->fld[1].buf, buf, m->fld[1].len);
 buf += m->fld[1].len;

 for (i = 2; i <= flds; i++) 
 {
  if (MY_BITGET(m->fld[1].buf, i)) 
  { /* i'th bit != 0 */
   if ( s_isodef[i].fmt)
   { /* Variable length */
    if(s_iCompress) 
    {
     buf += BCD2INT(&(m->fld[i].len),(const unsigned char*) buf, s_isodef[i].fmt, 0);
    }
    else
    {
     sprintf(fmt, "%%0%dd", s_isodef[i].fmt);
     sscanf(buf, fmt, &(m->fld[i].len));
     buf += s_isodef[i].fmt;     
    }    

    if (m->fld[i].len > s_isodef[i].len) {
     MY_TRACE("flds = %d", i);
     return -1;
    }
   }
   else
   {
    m->fld[i].len = s_isodef[i].len;
   }

   m->fld[i].buf = (unsigned char *) malloc((m->fld[i].len) * sizeof(char));
   
   switch (s_isodef[i].typ) {
   case TYP_BCD: /* Fallthrough */
    if(s_iCompress)
    {
     buf += BCD2ASC((char*)m->fld[i].buf,(const unsigned char*) buf, m->fld[i].len, s_isodef[i].fmt); 
     break;
    }
   case TYP_ASC:
   case TYP_BIN:
    memcpy(m->fld[i].buf, buf, m->fld[i].len);
    buf += m->fld[i].len;
    break;
   default:
    MY_TRACE("flds = %d", i);
    return -1;
    break;
   }
  }
 }

 return (buf-start);
}


/* Dump the content of the ISO message m into a file */
void iso8583_dump(FILE *fp, ISO_MSG *m)
{
 int i, j;

 for (i=0; i<=ISO_FLDS; i++) 
 {
  if (m->fld[i].buf != NULL) 
  {
   fprintf(fp, "\nfield #%02d %03d:", i, m->fld[i].len);
   for (j=0; j<m->fld[i].len; j++) {
    fprintf(fp, " %02X", m->fld[i].buf[j]);
   }
  }
 }
}


/* Free memory used by the ISO message struct m. */
void iso8583_free(ISO_MSG *m)
{
 int i;

 for (i=0; i<=ISO_FLDS; i++) {
  if (m->fld[i].buf != NULL) {
   free(m->fld[i].buf);
   m->fld[i].buf = NULL;
   m->fld[i].len = 0;
  }
 }
}
