//---------------------------------------------------------------------------



#include <windows.h>

#pragma htrstop

#include "wbpycode.h"

//#include <fstream>

#pragma argsused

/*

using namespace std;

static ofstream logfile("wplog.txt");

*/

// GBK �ַ���

//{{{

const char HstrA [] = 

"߹ � �� �� �� �� �� �� �� �� �� � �� �� �� �� ��" \

        "� �� �� �� �� � �� �� �� �� �� �� �� �� � �� ��";



const char HstrB [] =

"� �� �� �� �� �� � �� �� �� � � �� �� �� �� �" \

        "�� �� �� �� �� � �� �� �� �� �� �� � �� �� �� ��"\

        "�� �� � �� �� �� � ݩ ذ �� �� �� �� �� � �� ��"\

        "�� �� � �� �� �� � �� �� �� �� �� �� �� ޵ � ��"\

        "� �� � �� �� �� �� � �� �� �� �� �� �� �� �� �"\

        "�� �� � �� � � �� � �� �� �� �� �� �� �� �� ��"\

        "�� �� �� �� �� �� �� � �� �� �� � �� �� �� �� �"\

        "�� �� �� �� �� ߲ �� � �� � ��";



const char HstrC [] = 

"�� �� �� �� �� � �� �� �� �� � ܳ �� � � �� � �� �� � � �� ��" \

        "�� �� � �� ٭ � �� �� � �� �� �� �� �� � �� �� �� �� �� �� �� � ��" \

        "�� �� �� �� �� �� � � �� �� �� �� �� �� � �� �� �� � �� � �� �� ��" \

        "� �� �� �� �� � ة �� �� �� �� �� �� �� � � �� �� �� �� � �� �� ܯ" \

        "�� �� �� �� �� ߳ �� � � �� � �� �� �� � �� � � ٱ �� � �� �� ۻ" \

        "�� �� �� �� �� ء �� � �� �� �� � �� �� �� � �� �� � �� �� �� � �" \

        "�� ݻ �� �� � �� �� �� �� �� �� �� �� �� � �� �� � �� � �� �� � ��" \

        "�� �� ��";



const char HstrD [] = 

"�� �� � �� � �� �� �� �� � ߰ � �� �� ܤ �� �� �� �� �� �� �� �� �" \

        "�� � �� �� �� � � �� ߶ �� � �� � �� �� � �� �� �� �� �� �� �� ݶ ��" \

        "ص ڮ ۡ �� �� �� �� � �� � �� �� �� �� � �� �� �� �� �� � �� �� �� ��" \

        "�� � ܦ �� �� � �� �� �� �� �� �� �� � �� �� �� �� � � � �� � �� ��" \

        "�� �� �� � � � �� �� � �� �� �� ܶ � � �� �� � �� � �� �� �� �� ��" \

        "�� � �� �� �� �� �� � �� �� �� �� � � �� � ؼ";



const char HstrE [] =

"�� ݭ � � �� �� �� �� �� �� � �� �� �� �� � ج �� �� �� � �� �� ��" \

        "�� ٦ �� �� ��";



const char HstrF [] = 

"�� �� � ެ �� �� �� � �� �� �� �� �� �� �� � �� �� �� �� �� �� � �" \

        "� �� �� �� �� �� �� �� �� �� � �� � �� ۺ �� ٺ � ߻ �� �� �� �� �� ��" \

        "ܽ �� �� � � �� �� � �� ۮ �� ݳ � �� �� �� �� �� � �� �� �� �� �� ��" \

        "�� �� �� �� � � ��";



const char HstrG [] = 

"� ٤ �� �� �� �� �� �� �� ؤ � �� �� �� �� �� �� �� �� ߦ � � � ��" \

        "� �� � �� غ � �� �� ޻ ھ ۬ � �� �� �� ت �� ܪ � �� �� �� �� �� �" \

        "�� �� ب �� ݢ �� �� � �� �� � �� �� �� �� �� �� � �� �� ڸ �� � �� ��" \

        "�� � �� �� �� �� � �� �� ڬ �� � �� �� �� � �� �� �� �� �� �� �� � ��" \

        "�� ڴ �� �� �� �� �� �� �� �� �� �� � � �� � �� �� �� �� �� �� �� �� �" \

        "�� �� �� �� �� �� �� �� �� � �� � � �� �� ݸ ��";



const char HstrH [] = 

"�� �� �� �� �� �� �� �� �� �� �� �� � �� � � �� �� �� �� ޶ � �� �" \

        "� � � � ڭ �� �� �� �� � �� �� �� �� �� ޿ �� ް �� �� ݦ ޮ �� ڧ ��" \

        "�� �� �� �� �� ܩ �� � �� �� �� � �� �� �� � �� �� �� �� � � �� �� �" \

        "�� �� �� �� �� � �� �� �� �� �� � � �� �� � �� �� ۼ � �� �� �� ߧ ��" \

        "�� �� �� �� �� � �� � � �� ڶ �� � �� �� �� �� � �� �� � �� � �� �" \

        "�� ޥ � �� �� ڻ �� �� �� �� ߫ �� � �� �� ޽ � � ��";



//hstrI [] =



const char HstrJ [] =

"آ ߴ �� �� ܸ � �� �� �� �� �� �� �� �� �� �� � �� � � ؽ ٥ �� �"\

        "�� � �� � ު � �� � �� �� �� �� � �� �� �� �� �� �� � �� �� �� �� �"\

        "�� �� �� �� �� �� � ۣ � � �� �� �� �� � �� ��" \

        "�� �� �� �� �� �� �� �� �� �� �� �� �� � �� � �� �� � �� �� � � �� �� ��"\

        "�� �� �� �� �� � � �� �� ܴ � �� �� �� �� �� �� ٮ �� � � �� �� �� ��" \

        "� �� ڦ ڵ �� �� � � �� �� �� � �� �� �� ��" \

        "�� �� �� �� �� � � ݣ �� �� �� �� �� � ݼ �� �� �� �� �� � �� �� �� � �"\

        "�� �� � �� �� � �� �� �� �� �� �� �� �� �� �� �� �� � ާ �� �� �� �� �� ��"\

        "�� �� �� �� �� ۲ ��";



const char HstrK [] = 

"�� �� �� �� � �� �� �� �� �� �� �� �� � ٩ ݨ �� � �� �� �� �� �� ��"\

        "�� �� �� �� �� � �� � � �� �� � � � �� � � �� � �� � �� �� �� ��"\

        "ߵ �� ޢ �� ܥ �� � � ٨ �� ۦ �� �� �� �� ڲ ��" \

        "ڿ �� �� �� �� �� � �� ظ � �� �� � �� �� �� �� � � �� �� �� �� � �� ��"\

        "�� � �� �� ��";



const char HstrL [] =

" �� �� �� � �� �� �� �� �� � � �� �� �� � �� � �� � �� � �� � �"\

        "ݹ �� � �� �� �� �� �� �� � �� �� �� �� �� ߷ �� �� �� �� �� �� �� ڳ �� ��"\

        "ܨ � �� � � �� �� �� �� �� � ޼ �� � ٵ � ��" \

        "� � �� �� ߿ �� �� �� �� �� ٳ �� �� �� ۪ �� �� ݰ � �� �� �� � �� �� ��"\

        " �� �� �� �� � � � �� �� �� � �� � �� � ܮ �� �� �� � � �� �� �� ޤ" \

        " �� �� � �� �� �� �� �� �� �� �� �� � � �� ��" \

        "�� �� �� � �� �� �� �� �� � �� � �� �� �� �� ۹ �� �� � � �� �� �� �� �"\

        " � �� �� �� �� �� �� �� � �� ��";



const char HstrM [] = 

"�� �� �� � �� �� � �� �� � �� � �� �� � �� �� �� �� �� �� �� ߼ �� "\

        "� �� � �� �� ݤ ۽ � �� �� �� ܬ � �� �� �� �� �� �� �� �� � �� �� �� �"\

        " � �� �� �� � �� � � � ݮ �� �� � � �� �� � "\

        "�� �� �� �� �� � � �� ޫ �� �� �� �� �� �� �� � �� �� � �� �� �� �� �� ��"\

        " �� �� �� � �� �� �� �� �� �� �� �� �� �� �� � � �� �� �� � � �� �� �� ��"\

        "�� �� � �� �� ڤ �� �� � �� �� �� �� �� �� �� �� �� �� �� � �� �� �� �� ٰ"\

        "�� �� � �� �� �� �� �� ��";



const char HstrN [] = 

"�� �� ؿ �� �� �� �� ܵ �� �� ؾ �� � � �� �� �� �� �� �� ߭ ث �� ��"\

        " �� � �� �� � ګ �� �� �� � �� ٣ � �� �� �� �� � �� إ �� �� �� �� �� ��"\

        "�� � � �� �� �� �� �� � � �� �� ٯ �� �� �� ��" \

        "�� �� �� � �� �� �� �� � �";



const char HstrO [] = "�� ک � �� ��";



const char HstrP [] =

" �� �� �� ڢ �� �� �� ٽ �� �� �� �� � �� �� �� �� �� � �� �� �� �� ��"\

        "�� �� �� � �� �� �� �� �� ܡ � ا � �� �� �� �� �� � ۯ �� �� � �� �� ܱ"\

        "�� �� �� ߨ � �� �� � � �� �� �� �� �� �� �� ��" \

        "� �� � �� �� � د �� � �� � � �� � ٷ �� �� �� ۶ � �� �� �� �� �� ��"\

        " � �� �� � � �� �� � �� ��";



const char HstrQ [] =

" �� �� �� � �� �� �� �� �� �� �� �� �� � �� �� �� � ݽ �� �� �� �� ��"\

        "�� �� ޭ �� �� � ܻ � � �� �� �� �� �� � �� �� �� ܷ �� � � � � � �"\

        " �� � �� �� �� � �� �� �� ٻ �� �� � �� �� � ��" \

        "�� �� �� �� �� �� �� �� �� �� �� �� � �� �� � ڽ � �� � �� �� �� �� � ��"\

        " �� �� �� � �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� � �� �� �� �� � ��"\

        " �� � ٴ �� �� �� �� �� �� �� �� � ڰ �� �� �� "\

        "�� ۾ �� � ޡ �� � ޾ � � �� � �� �� � ڹ �� �� �� �� �� �� � � � ��"\

        "�� �� ۧ";



const char HstrR [] = 

"�� �� �� �� � �� �� � �� �� �� �� � �� �� �� �� �� �� �� �� �� � ��"\

        " � ޸ �� � � �� �� �� �� ި �� �� � � ټ ��";



const char HstrS [] =

" �� � ح �� �� �� ئ � �� �� � �� �� �� �� � �� �� �� ܣ �� �� � �"\

        "� �� �� �� �� � �� �� �� � �� �� �� �� �� �� ڨ �� �� ۷ �� � �� �� �� ��"\

        "�� � �� �� �� ۿ �� � � �� �� �� �� ڷ �� �� �� "\

        "�� �� � �� �� �� �� �� �� �� �� � �� �� ݪ �� �� �� �� �� �� �� ߱ �� �� �"\

        "�� �� � � � � ٿ �� �� � �� �� �� �� �� � � �� �� �� �� �� �� �� �� ��"\

        "�� �� �� � �� �� �� �� �� �� �� � �� �� �� ٹ" \

        "�� �� �� ڡ �� �� ݿ �� � � � �� �� � �� �� �� �� � ޴ �� �� � �� � �"\

        "�� �� �� � ݴ �� � � �� ݷ";



const char HstrT [] = 

"� ߾ �� �� �� �� �� �� �� �� �� �� �� � �� ۢ �� �� �� ޷ �� �� � ۰"\

        "�� �� �� �� � �� �� � �� � �� � � �� �� �� �� � �� � �� ػ �� ߯ � �"\

        "�� � � �� �� �� � �� �� � �� �� �� �� ٬ �� �� "\

        "�� �� �� �� � �� �� �� �� �� �� �� �� �� �� �� ١ �� �� �� �� �� �� ݱ �� ��"\

        " ܢ �� �� � �� �� �� � �� �� ر ٢ �� �� �� �� �� �� �� �� �� �� ��";



//hstrU [] =



//hstrV [] =



const char HstrW [] =

" �� � �� �� �� �� �� �� ܹ � �� �� �� � �� � �� �� �� �� �� �� �� ޱ"\

        "�� �� �� �� � � �� � �� � � �� �� � �� �� � �� � � �� �� �� �� � ��"\

        "޳ �� ݫ � � � �� �� �� �� �� � �� �� �� �� �� �� �� �� �� �� أ �� � ��"\

        "�� �� �� �� � �� ��";



const char HstrX [] =

" ۨ �� �� ݡ �� �� � ۭ �� �� � � �� ݾ �� �� �� � �� �� �� �� � ��"\

        "�� � � �� �� �� �� �� �� �� �� �� �� �� � �� �� �� �� �� �� �� � �� �� �"\

        "�� �� ݲ �� �� �� � �� �� �� �� � �� �� ޺ �� � �� �� ܼ � �� �� �� �� ��"\

        "�� � �� �� �� �� � �� �� �� �� �� �� ��" \

        "�� ߢ �� � �� �� �� � �� � ޯ �� �� � �� � � ܰ �� ض �� �� ߩ �� � ܺ"\

        " �� �� � �� �� �� � �� �� �� �� ڼ �� �� �� � �� �� �� ޣ �� �� �� �� �� ��" \

        "�� �� � �� �� �� �� � �� �� � �� �� �� �� � � ޹ �� �� � �� � � �� ��"\

        " �� �� ";



const char HstrY [] =

" � �� �� �� � �� �� �� �� �� � � � �� �� �� �� �� �� �� ۳ �� ڥ ��"\

        "�� ܾ �� �� �� ٲ �� �� ۱ �� � �� �� �� �� �� �� �� �� �� �� �� � �� �� ��"\

        "�� � �� ز ߺ س �� �� �� �� �� �� �� � �� �� �� �� �� �� �� �� �� �� �� ��" \

        "� � �� �� �� �� ڱ �� �� �� �� �� �� ��" \

        "�� �� �� �� �� �� � ߮ �� �� �� ߽ ٫ � �� �� �� �� �� �� � �� �� � �� ��" \

        "�� �� �� �� �� ޲ �� � �� ܲ � � �� � ܧ �� �� ۴ � �� �� �� � � �� ط" \

        "ݺ �� �� �� � � �� �� �� �� �� � �� �� �� �� � ۫ � � �� � �� ܭ � ��"\

        "�� �� �� �� �� �� �� �� �� �� � �� � �� �� ٶ �� �� �� �� �� �� � �� �� ��"\

        " �� �� �� �� �� �� ع �� �� �� �� � �� �� �� � �� ܫ �� � �� �� �� � � ��"\

        "�� �� � � ܿ �� � �� �� ۩ � � � �� �� خ";



const char HstrZ [] =

" �� �� � �� �� �� �� �� �� �� �� �� �� � � �� �� �� �� �� �� �� �� ��"\

        " �� �� � �� �� �� � � ߸ �� �� � �� �� �� �� �� �� � � �� �� ۵ �� � �"\

        " � �� �� � �� �� گ �� �� �� �� �� ߡ �� �� �� �� �� � �� �� �� � �� �� ��"\

        " � �� � �� � �� �� � �� � �� �� ں ش" \

        "�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ۤ �� �� �� �� �� � ��"\

        "�� �� �� �� �� �� �� �� �� � ڣ �� � �� �� � �� ݧ �� �� ٪ ۥ � �� �� ��"\

        "�� �� �� �� �� �� � �� �� �� �� �� �� �� �� � �� �� �� �� �� � �� �� � پ"\

        " �� � �� �� �� �� �� ߬ ީ �� �� ߤ �� �� �� �� �� �� �� ��";

//}}}

// GBK �ַ�������

// {{{

const char * g_GBK_Table [] =

{

    HstrA,

    HstrB,

    HstrC,

    HstrD,

    HstrE,

    HstrF,

    HstrG,

    HstrH,

    NULL, //HstrI,

    HstrJ,

    HstrK,

    HstrL,

    HstrM,

    HstrN,

    HstrO,

    HstrP,

    HstrQ,

    HstrR,

    HstrS,

    HstrT,

    NULL,//HstrU,

    NULL,//HstrV,

    HstrW,

    HstrX,

    HstrY,

    HstrZ,

};

//}}}



//{{{ DllEntryPoint() method

/** 

  * @brief ��ں���

  * 

  * @param hinst 

  * @param reason 

  * @param lpReserved 

  * 

  * @return 

  */

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)

{

    return 1;

}

//}}}



//{{{ readline() method

/** 

  * @brief ���ļ��ж�ȡһ��

  * 

  * @param fp - ��ȡ���ļ�ָ��

  * @param buf - �����ȡ�����ݵĻ���

  * @param maxlen - ����Ĵ�С

  * 

  */

void __stdcall readline(FILE * fp , char * buf , int maxlen)

{

    if(fp != NULL)

    {

        int i = 0;

        int c = fgetc(fp);

        while( i < maxlen && (feof(fp) ==0) && c != '\n')

        {

            buf[i++] = (char)c;

            c = fgetc(fp);

        }

        buf[i] = '\0';

    }

}

//}}}



//{{{ LoadWbCodeTable() method

/** 

  * @brief �����������ַ���

  * 

  * @param TablePath - �ַ����·��

  * 

  */

void __stdcall LoadWbCodeTable(const char * TablePath)

{

    if( TablePath == NULL )

    {

        return;

    }

    LPVOID lpAddr = AllocateMemory(BufLen);

    if (lpAddr == NULL)

        return;



    HeadWB = (PWBCodeTable)lpAddr;

    TailWB= HeadWB;



    FILE * table = fopen(TablePath,"r");

    if ( table == NULL )

        return;

        

    char line[100];

    readline(table,line,100);

    while( strlen(line) > 0 )

    {

        memset(TailWB , 0 , sizeof(WBCodeTable));

        ParseLine(TailWB, line);

        TailWB++;

        readline(table,line,100);

    }

    fclose(table);

}

//}}}



//{{{ ParseLine() method

/** 

  * @brief ������ȡ��һ������,���浽�ַ���

  * 

  * @param lpTbl - ���浽���ַ���

  * @param line - һ������

  * 

  */

void __stdcall ParseLine(PWBCodeTable lpTbl , const char * line)

{

    if (line == NULL)

        return;



    const char * start = line;

    const char * pos = line;

    int nonascii = 0;

    while(1)

    {

        if (*pos == ' ' || * pos == '\t' || *pos == '\0')

        {

            if (nonascii == 1)

            {

                int len = ((pos - start) < WB_CODE_MAX_LEN) ?

                    (pos - start) : WB_CODE_MAX_LEN;

                strncpy(lpTbl->szCode,start , len);

            }

            else if(nonascii == 2)

            {

                int len = (pos - start < WB_HZ_MAX_LEN) ?

                    (pos - start) : WB_HZ_MAX_LEN;

                strncpy(lpTbl->szHz , start , len);

                return;

            }   

            start = ++pos;

            continue;

        }

        if(isascii(*pos))

        {

            if(nonascii == 0)

            {

                start = pos;

                nonascii = 1;

            }

        }

        else

            nonascii = 2;

        pos++;

    }

}

//}}}



//{{{ GetWbCoden() method

/** 

  * @brief ����ָ�������ַ����������

  * 

  * @param value - Ҫ�����������ַ���

  * @param code - �����������������

  * @param ctype - ��־λ

  * @param len - �ַ����ĳ���

  * 

  * ��־λ : 

  * CONVERT_ALL                         ---ȫ������

  * CONVERT_NO_LETTER_DIGEST            ---ȥ����ĸ,����

  * CONVERT_NO_SPACE_TAB                ---ȥ���ո�

  * CONVERT_NO_HZ_CHAR                  ---ȥ������

  * CONVERT_NO_ASCII                    ---ȥ������ ASCII �ַ�

  */

void __stdcall GetWbCoden(const char * value, char * code ,WORD ctype, int len)

{

    if ( value == NULL )

        return;

    int i = 0;

    while( i < len)

    {

        if(isascii(value[i]))

        {

            if(value[i] == ' ' || value[i] == '\t')

            {

                if(!(ctype & CONVERT_NO_SPACE_TAB))

                    *code++ = value[i];

            }

            else

            {

                if(!(ctype & CONVERT_NO_LETTER_DIGEST))

                    *code++ = value[i];

            }

        }

        else

        {

            PWBCodeTable curr = HeadWB;

            while( curr != NULL && curr < TailWB)

            {

                if( strncmp(&value[i] , curr->szHz,2) == 0 )

                {

                    strncpy(code++, curr->szCode,1);

                    i++;

                    break;

                }

                curr++;

            }

            if( curr == TailWB && !(ctype & CONVERT_NO_HZ_CHAR))

            {

                strncpy(code, &value[i], 2);

                code += 2;

                ++i;

            }

        }

        ++i;

    }

    *code = '\0';

}

//}}}



//{{{ GetWbCode() method

/** 

  * @brief ����һ���ַ����������

  * 

  * @param value - Ҫ������ַ���

  * @param code - ���������������

  * @param ctype - ��־λ

  * 

  */

void __stdcall GetWbCode(const char * value, char * code, WORD ctype)

{

    GetWbCoden(value,code,ctype,strlen(value));

}

//}}}



//{{{ GetPyCode() method

/** 

  * @brief ����һ���ַ�����ƴ����

  * 

  * @param value - Ҫ������ַ���

  * @param code - ��������ƴ����

  * @param ctype - ��־λ

  * 

  */

void __stdcall GetPyCode(const char * value, char * code,WORD ctype)

{

    GetPyCoden(value,code,ctype,strlen(value));

}

//}}}



//{{{ GetPyCoden() method

/** 

  * @brief ����һ��ָ�����ȵ��ַ�����ƴ����

  * 

  * @param value - Ҫ������ַ���

  * @param code - ��������ƴ����

  * @param ctype - ��־λ

  * @param len - �ַ����ĳ���

  * 

  */

void __stdcall GetPyCoden(const char * value, char * code,WORD ctype, int len)

{

    if ( value == NULL )

        return;

    int i = 0;

    while( i < len)

    {

        if(isascii(value[i]))

        {

            if(value[i] == ' ' || value[i] == '\t')

            {

                if(!(ctype & CONVERT_NO_SPACE_TAB))

                    *code++ = value[i];

            }

            else

            {

                if(!(ctype & CONVERT_NO_LETTER_DIGEST))

                    *code++ = value[i];

            }

        }

        else

        {

            WORD h = value[i++];

            WORD l = value[i];

            char saveCode;

            if (h > 0x80)

            {

                WORD v = MAKEWORD(l,h);

                if( v >= 0xB0A1 && v <= 0xB0C4)

                    *code++ = 'a';

                else if (v >= 0xB0C5 && v <= 0xB2C0)

                    *code++ = 'b';

                else if (v >= 0xB2C1 && v <= 0xB4ED)

                    *code++ = 'c';

                else if (v >= 0xB4EE && v <= 0xB6E9)

                    *code++ = 'd';

                else if (v >= 0xB6EA && v <= 0xB7A1)

                    *code++ = 'e';

                else if (v >= 0xB7A2 && v <= 0xB8C0)

                    *code++ = 'f';

                else if (v >= 0xB8C1 && v <= 0xB9FD)

                    *code++ = 'g';

                else if (v >= 0xB9FE && v <= 0xBBF6)

                    *code++ = 'h';

                else if (v >= 0xBBF7 && v <= 0xBFA5)

                    *code++ = 'j';

                else if (v >= 0xBFA6 && v <= 0xC0AB)

                    *code++ = 'k';

                else if (v >= 0xC0AC && v <= 0xC2E7)

                    *code++ = 'l';

                else if (v >= 0xC2E8 && v <= 0xC4C2)

                    *code++ = 'm';

                else if (v >= 0xC4C3 && v <= 0xC5B5)

                    *code++ = 'n';

                else if (v >= 0xC5B6 && v <= 0xC5BD)

                    *code++ = 'o';

                else if (v >= 0xC5BE && v <= 0xC6D9)

                    *code++ = 'p';

                else if (v >= 0xC6DA && v <= 0xC8BA)

                    *code++ = 'q';

                else if (v >= 0xC8BB && v <= 0xC8F5)

                    *code++ = 'r';

                else if (v >= 0xC8F6 && v <= 0xCBF9)

                    *code++ = 's';

                else if (v >= 0xCBFA && v <= 0xCDD9)

                    *code++ = 't';

                else if (v >= 0xCDDA && v <= 0xCEF3)

                    *code++ = 'w';

                else if (v >= 0xCEF4 && v <= 0xD188)

                    *code++ = 'x';

                else if (v >= 0xD1B9 && v <= 0xD4D0)

                    *code++ = 'y';

                else if (v >= 0xD4D1 && v <= 0xD7F9)

                    *code++ = 'z';

                else if ( findInGBK(v,&saveCode) ) // �ж��Ƿ�ΪGBK�ַ�

                {

                    *code++ = saveCode;

                }

                else if (!(ctype & CONVERT_NO_HZ_CHAR))

                {

                    *code++ = (byte)h;

                    *code++ = (byte)l;

                }

            }

            else if(!(ctype & CONVERT_NO_HZ_CHAR))

            {

                *code++ = (byte)h;

                *code++ = (byte)l;

            }

        }

        ++i;

    }

    *code = '\0';

}

//}}}



//{{{ findInGBK() method

/** 

  * @brief �ж�һ���ַ��Ƿ�Ϊ GBK ����

  * 

  * @param hz - �ַ� ( ˫�ֽ� )

  * @param py - ����� GBK ���� , ���溺�ֵ���ĸ

  * 

  * @return - ����� GBK ���� ����ֵ���� 0 , ���򷵻�ֵ�� 0

  */

int __stdcall findInGBK(WORD hz , char * py)

{

    for( int i = 0;i < sizeof(g_GBK_Table) / sizeof( wchar_t * );++i )

    {

        const char * pyTbl = g_GBK_Table[i];

        const char * character = pyTbl;

        if( pyTbl == NULL )

            continue;

        while( *character != '\0' )

        {

            WORD charValue = (WORD)(*character);

            if( charValue != ' ' )

            {

                WORD lowValue = (WORD)(*(character+1));

                if( lowValue == '\0' )

                    return 0;

                charValue = MAKEWORD(lowValue,charValue);

                if( charValue == hz )

                {

                    *py = 'a' + i;

                    return 1;

                }

                character++;   

            }

            character++;

        }

        //logfile<<"find in "<<i<<endl;

    }

    return 0;

}

//}}}



//{{{ ReleaseWbCodeTable() method

/** 

  * @brief �ͷ�������ַ���

  * 

  * @return - ����ɹ����� TRUE

  */

BOOL __stdcall ReleaseWbCodeTable()

{

    CloseHandle(hGlobalFile);

    return TRUE;

}

//}}}



//{{{ AllocateMemory() method

/** 

  * @brief ��ȫ���ڴ�������һ���ڴ�ռ�

  * 

  * @param size - Ҫ����Ŀռ�Ĵ�С( byte )

  * 

  * @return - ����ָ���ڴ�ռ��ָ�� , ��������ڴ�ʧ�ܷ��� NULL

  */

LPVOID __stdcall AllocateMemory(DWORD size)

{

    HANDLE hHandle = CreateFileMapping(INVALID_HANDLE_VALUE,

        NULL,

        PAGE_READWRITE,

        0,

        size,

        GlobalFileName);

    if( GetLastError() == ERROR_ALREADY_EXISTS)

    {

        return GetMemoryAddress();

    }



    if( hHandle != NULL )

    {

        hGlobalFile = hHandle;

        return GetMemoryAddress();

    }

    return NULL;

}

//}}}



//{{{ GetMemoryAddress() method

/** 

  * @brief ����ȫ���ڴ��ļ���ָ���ַ

  * 

  * @return - ��ַ , ���û�������ڴ淵�� NULL

  */

LPVOID __stdcall GetMemoryAddress()

{

    if (hGlobalFile != NULL)

    {

        LPVOID lpAdd = MapViewOfFile(hGlobalFile,

            FILE_MAP_ALL_ACCESS,

            0,

            0,

            0);

        return lpAdd;

    }

    return NULL;

}

//}}}

 

