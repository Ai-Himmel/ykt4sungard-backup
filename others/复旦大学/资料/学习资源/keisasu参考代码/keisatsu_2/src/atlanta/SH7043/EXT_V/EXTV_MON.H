/*--------------------------------------------------------------------------*/
/*  ƒvƒƒWƒFƒNƒg : POPLAR/ANZU_L                                            */
/*  ƒtƒ@ƒCƒ‹–¼   : extv_mon.h                                               */
/*  ì¬Ò       : –ì£•qO                                                 */
/*  “ú  •t       : 96/10/11                                                 */
/*  ŠT  —v       : ƒ‚ƒjƒ^ƒe[ƒuƒ‹                                           */
/*  C³—š—ğ     :                                                          */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚ÍAƒ}ƒXƒNƒvƒƒOƒ‰ƒ€•ÏX
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
#else

#include "\src\atlanta\sh7043\define\def_mon.h"
#include "\src\atlanta\sh7043\define\def_tcb.h"
#include "\src\atlanta\sh7043\define\def_scb.h"
#include "\src\atlanta\sh7043\define\def_tib.h"

extern UBYTE real_run_tid;
extern UBYTE top_ready_tid;
extern UBYTE wai_tsk_tid;
extern UBYTE wai_1shot_tid;
extern struct tcb_table_data_t tcb[];
extern struct tib_table_data_t tib[];
extern struct scb_table_data_t scb[];
extern UBYTE mcb[];
extern UBYTE ecb[];

extern UDWORD MON_StackCheckTable[];

extern UDWORD small_stack_area[][SMALL_STACK/4];
extern UDWORD large_stack_area[][LARGE_STACK/4];

#endif
