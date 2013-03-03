#ifndef buzzer_h
    #define buzzer_h

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/08/20 H.Yoshikawa */
#include "\src\atlanta\sakaki\define\md9402.h"	/* SCN_BUZZER_1950HZ */
#else
#include "\src\atlanta\define\scn_def.h"
#endif

/*-------------------------------------------------------------------------
** SAKAKI用とそれ以外の#defineを同じにしようとする、Duplicateが多発します。
** いろんなところで、"\src\atlanta\define\scn_def.h"がインクルードされているためです。
** 全てのSCN_BUZZER_1950HZをBUZZER_1950HZに書き換えました。
** 1998/09/14 H.Yoshikawa
*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/09/14 H.Yoshikawa */
#define BUZZER_1950HZ						BUZZER_FREQ		/* 約2000Hz */
#else
#define BUZZER_1950HZ						SCN_BUZZER_1950HZ		/* 約2000Hz */
#endif

/************************************************************************
 * ブザー・アラームには2パターンがあります								*
 * <パターン１>															*
 * 1.対象ブザー・アラーム												*
 *   ①アックブザー														*
 *   ②ナックブザー														*
 * 2.鳴動方法															*
 *   CMN_BuzzerTask()に対し、Msg.Messageに#define値をセットし、snd_msg()*
 *   する																*
 *																		*
 * <パターン２>															*
 * 1.対象ブザー・アラーム												*
 *   ①エンドブザー														*
 *   ②保留アラーム														*
 *   ③4秒間鳴動エラーアラーム											*
 *   ④無限エラーアラーム 												*
 *　 ⑤会話予約アラーム													*
 * 2.鳴動方法															*
 *   各タスクをcre_tsk()し、鳴動停止する場合は、del_tsk()する			*
 *																		*
 * <ブザーパラメータ>													*
 * BUZZER_LENGTH = ON時間 = OFF時間										*
 * BUZZER_CYCLE  = 鳴動回数												*
 * BUZZER_FREQ   = 周波数(GAに準じた値)									*
 ************************************************************************/

/************************************************************************
 * ブザー																*
 * CMN_BuzzerTask()														*
 * 1994/06/23															*
 * 吉川弘康																*
 ************************************************************************/
/*
 * Messageに下記値を設定してsnd_msg()するとブザーが鳴動する
 */
#define ACK_BUZZER          			1		/* 2000Hzを50m秒ON+50m秒OFFする */
#define NACK_BUZZER         			2		/* 2000Hzを40m秒ON+40m秒OFF+40m秒ON+40m秒OFFする */

/*
 * ブザーの鳴動パターン
 * BUZZER_LENGTH = ON時間 = OFF時間
 * BUZZER_CYCLE  = 鳴動回数
 * BUZZER_FREQ   = 周波数(GAに準じた値)
 */
#define ACK_BUZZER_LENGTH   			5		/* 10m秒単位で50m秒ON+50m秒OFF */
#define ACK_BUZZER_CYCLE    			1		/* 1回鳴動 */
#define ACK_BUZZER_FREQ     			BUZZER_1950HZ		/* 約2000Hz */
#define NACK_BUZZER_LENGTH  			4		/* 10m秒単位で40m秒ON+40m秒OFF*/
#define NACK_BUZZER_CYCLE    			2		/* 2回鳴動 */
#define NACK_BUZZER_FREQ     			BUZZER_1950HZ		/* 約2000Hz */

/************************************************************************
 * アラーム																*
 * CMN_EndBuzzerTask()													*
 * CMN_HoldAlarmTask()													*
 * CMN_ErrorAlarmTask()													*
 * CMN_ErrorEndlessAlarmTask()											*
 * CMN_VoiceAlarmTask()													*
 * 1994/06/23															*
 * 吉川弘康																*
 ************************************************************************/
#define END_BUZZER_LENGTH  	    		100		/* 10m秒単位で1秒ON+1秒OFF */
#define END_BUZZER_CYCLE    			1		/* 1回鳴動 */
#define END_BUZZER_FREQ     			BUZZER_1950HZ 	/* 約2000Hz */
#define HOLD_ALARM_LENGTH  	    		4		/* 10m秒単位で40m秒ON+40m秒OFF */
#define HOLD_ALARM_CYCLE    			19		/* 19回鳴動 */
#define HOLD_ALARM_FREQ     			BUZZER_1950HZ 	/* 約2000Hz */
#define ERROR_ALARM_LENGTH  			10		/* 10m秒単位で100m秒+100m秒OFF */
#define ERROR_ALARM_CYCLE    			20  	/* 20回鳴動で合計4秒 */
#define ERROR_ALARM_FREQ     			BUZZER_1950HZ 	/* 約2000Hz */
#define ERROR_ENDLESS_ALARM_LENGTH  	10		/* 100m秒 */
#define ERROR_ENDLESS_ALARM_CYCLE    	0xFF	/* Endles */
#define ERROR_ENDLESS_ALARM_FREQ     	BUZZER_1950HZ	/* 約2000Hz */
#define VOICE_ALARM_LENGTH				20		/* 10m秒単位で20m秒ON+20m秒OFF */
#define VOICE_ALARM_CYCLE				1499	/* 30秒 (max 1310秒) */
#define VOICE_ALARM_FREQ     			BUZZER_1950HZ		/* 約2000Hz */

/* POPLARで使用 By M.Tachibana 1997/06/04 */
#define PAPER_SUPPLY_BUZZER_LENGTH 		5		/* 10m秒単位で1秒ON+1秒OFF */
#define PAPER_SUPPLY_BUZZER_CYCLE		2		/* 1回鳴動 */
#define PAPER_SUPPLY_BUZZER_FREQ		BUZZER_1950HZ 	/* 約2000Hz */


#endif
